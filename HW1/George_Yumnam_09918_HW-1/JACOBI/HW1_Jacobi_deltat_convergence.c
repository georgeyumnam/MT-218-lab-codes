#include<stdio.h> 
#include<stdlib.h>
#include<math.h>  // This is required for using absolute values of floats

#define MESHX 100
#define MESHY 100

#define ntimesteps 2000
#define deltax 1.0
#define deltay 1.0
#define saveT 100
#define radius 20

double c_now[MESHX+2][MESHY+2]; // Define the array (for t' = t + 1 )
double c_old[MESHX+2][MESHY+2]; // Define the array (for t' = t )
double c_swap[MESHX+2][MESHY+2];
void initialize();
void writetofile(FILE *fp);
void update();

long x, y, t;
long iter, del;
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
  
  printf("We want to compare the deltat_max upto which accuracy is maintained in this method\n");  
  printf("To verify the convergence of deltat....\n");
  printf("We need to check the 2D plot and see at which value of\n");
  printf("deltat, the plot becomes very sparse!!!!");
  printf("In order to implement this, it is sufficient to check for \n");
  printf("the plot at any 't' timestep in the Iterations!!!!\n");
  printf("We set this t_select = 1200 for this case !!!\n");
  
  int t_select = 1200; // The user can change this value 
  
 for (del=1; del<20; del++){
  double deltat = del/20.0;
  double inv_deltax2 = 1.0/(deltax*deltax); // assuming that deltax = deltay , we have a common alpha
  double alpha = deltat*inv_deltax2;
  
  initialize ();// start the initialization
  update(); // update the composition values of c_now to c_swap
  
  for (t=0;t<ntimesteps;t++){
      for (y=0;y<=MESHY+1;y++){
          for (x=0;x<=MESHX+1;x++){
              c_old[x][y] = c_now[x][y]; //store values of previous time step before moving on to new time-step
          }
      }
      for (iter=0;iter<=20; iter++){
          for (y=1;y<MESHY+1;y++){
              for (x=1;x<MESHX+1;x++){
                  c_now[x][y] = (alpha*(c_swap[x-1][y]+c_swap[x+1][y]+c_swap[x][y+1]+c_swap[x][y-1])+c_old[x][y])/(1+4*alpha);
              }
          }
          update();
      }
      if (t == t_select){
          sprintf(filename,"composition_%le_%d.dat", deltat, t_select);
          fp=fopen(filename,"w");
          writetofile(fp);
          fclose(fp);
      }// closes the writer function loop
  }// closes the loop in 't'
  
  printf("Completed the calculation for deltat = %le\n", deltat);
  
 }// closes loop in 'del'

   printf("The calculations are completed now!!!\n");
  printf("Use gnuplot to plot the composition for each deltat\n\n");
  
  printf("You can use these codes for plotting:\n");
  printf("#########################################################\n");
  printf("set pm3d\n");
  printf("set multiplot layout 2,2\n");
  printf("set xtics rotate\n");
  printf("set bmargin 5\n");
  printf("set title 'deltat = 0.05' \n");
  printf("unset key\n");
  printf("splot 'composition_%le_%d.dat' us 1:2:3\n", 5.000000e-02, 1200);
  printf("set title 'deltat = 0.3' \n");
  printf("unset key\n");
  printf("splot 'composition_%le_%d.dat' us 1:2:3\n", 3.000000e-01, 1200);
  printf("set title 'deltat = 0.4' \n");
  printf("unset key\n");
  printf("splot 'composition_%le_%d.dat' us 1:2:3\n", 4.000000e-01, 1200);
  printf("set title 'deltat = 0.5' \n");
  printf("unset key\n");
  printf("splot 'composition_%le_%d.dat' us 1:2:3\n", 5.000000e-01, 1200);
  printf("\n");
  printf("[You can copy-paste the above code in gnuplot]\n");
  printf("You can also try for different deltat values other than these!!!\n");
  printf("#########################################################\n\n"); 
  
  printf("As you can see that by deltat = 0.5, the maximum composition \n");
  printf("at the grid is 0.2... whereas, for deltat = 0.02 is >0.8 \n");
  printf("Therefore, deltat_max = 0.5 (independent of the choice of t_select)\n\n");
 
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
