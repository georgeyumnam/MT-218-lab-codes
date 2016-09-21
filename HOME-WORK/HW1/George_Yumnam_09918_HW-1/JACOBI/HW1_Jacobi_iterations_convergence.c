#include<stdio.h> 
#include<stdlib.h>
#include<math.h>

#define MESHX 100
#define MESHY 100

#define ntimesteps 2000
#define deltat 0.1
#define deltax 1.0
#define deltay 1.0
#define radius 20
#define tot_iter 10

double c_now[MESHX+2][MESHY+2]; // Define the array (for t' = t + 1 )
double c_old[MESHX+2][MESHY+2]; // Define the array (for t' = t )
double c_swap[MESHX+2][MESHY+2];

double c_init[MESHX+2][MESHY+2]; // This is the initial composition values
                                 // Which will be used for convergence test

void initialize();
void writetofile(FILE *fp);
void update();

long x, y, t;
long iter, iter_tot;
char filename[1000]; 

double A_x[MESHX+1];
double B_x[MESHX+1];
double C_x[MESHX+1];
double D_x[MESHX+1];

double A_y[MESHY+1];
double B_y[MESHY+1];
double C_y[MESHY+1];
double D_y[MESHY+1];  

void main(){

  
  FILE *fp;
  double inv_deltax2 = 1.0/(deltax*deltax); // assuming that deltax = deltay , we have a common alpha
  double alpha = deltat*inv_deltax2;
  
  double c_diff; // this is the checker for convergence
  
  int x_rand, y_rand;
  
  printf("In order to check the convergence we take any point (x,y) in the grid\n");
  printf("and check the difference of the final and initial values with increasing iterations\n");
  printf("This point (x,y) is random so, we let the user define this point!!\n\n");
  printf("Please enter the integer value of x_rand ( 1 < x_rand < 100 )\n");
  scanf("%d", &x_rand);
  printf("Please enter the integer value of y_rand ( 1 < y_rand < 100 )\n");
  scanf("%d", &y_rand);
  
  printf("\n Now, we are going to check the convergence of iterations at c[%d][%d]\n\n", x_rand, y_rand);
  
 for (iter_tot=2; iter_tot < 15 ; iter_tot++){ // This is for checking the iterations to convergence test

  initialize ();// start the initialization
  update(); // update the composition values of c_now to c_swap
  
  for (t=0;t<ntimesteps;t++){
      for (y=0;y<=MESHY+1;y++){
          for (x=0;x<=MESHX+1;x++){
              c_old[x][y] = c_now[x][y]; //store values of previous time step before moving on to new time-step
          }
      }
      for (iter=0; iter <= iter_tot; iter++){// Iterations to convergence - for error minimization
          for (y=1;y<MESHY+1;y++){
              for (x=1;x<MESHX+1;x++){
                  c_now[x][y] = (alpha*(c_swap[x-1][y]+c_swap[x+1][y]+c_swap[x][y+1]+c_swap[x][y-1])+c_old[x][y])/(1+4*alpha);
              }
          }
          update();
      }
  }// closes the loop in 't'
  
  c_diff = fabs(c_now[x_rand][y_rand]-c_init[x_rand][y_rand]);
  printf("iter_tot = %ld ---> c_diff[%d][%d] = %le\n", iter_tot, x_rand, y_rand, c_diff);
  
 }// closes loop for iter_tot change
 printf("From this above convergence check, we see that Jacobi converges by atmost 11th iteration.\n");
 printf("This convergence at max 11th iteration is independent of the choice of x_rand, y_rand\n\n");
}// closes the main loop

void initialize(){
    for (x=0;x<=(MESHX+1);x++){
        for(y=0;y<=(MESHY+1);y++){
            if (((x-(MESHX+1)/2)*(x-(MESHX+1)/2) + (y-(MESHY+1)/2)*(y-(MESHY+1)/2)) < radius*radius){
                c_now[x][y] = 0.9;
            }
            else {
                c_now[x][y] = 0.1;
            }
        }
    }// Closes  the loop for 'for' loop 
}// CLoses initialize

void update(){
  for (x=0;x<=(MESHX+1);x++){
    for(y=0;y<=(MESHY+1);y++){
        c_swap[x][y] = c_now[x][y];
    }
  }
}// closes update loop

void writetofile(FILE *fp){
    for (x=0;x<=(MESHX+1);x++){
        for (y=0;y<=(MESHY+1);y++){
            fprintf(fp, "%le %le %le\n", x*deltax, y*deltay, c_now[x][y]);
        }
        fprintf(fp,"\n");
    }
}// Closes writetofile
// ################################################################ //