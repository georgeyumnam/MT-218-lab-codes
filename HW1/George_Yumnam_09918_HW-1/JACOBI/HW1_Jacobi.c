#include<stdio.h> 
#include<stdlib.h>

#define MESHX 100
#define MESHY 100

#define ntimesteps 2000
#define deltat 0.1
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
long iter;
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
  printf("###########################################################\n");
  printf("#   This is the code for Homework - 1\n");
  printf("#   Implementation of 2D diffusion using the\n");
  printf("#   Jacobi scheme of iterations\n");
  printf("###########################################################\n\n");
  printf("#   The given problem is to solve the following equation:\n");
  printf("#   dC    ( d^2C   d^2C )\n");
  printf("#   -- = D( ---- + ---- )\n");
  printf("#   dt    ( dx^2   dy^2 )\n");
  printf("###########################################################\n\n");
  printf("#           These are the defined variables::               \n");
  printf("#1) MESHX = %d  and  MESHY = %d  \n", MESHX, MESHY);
  printf("#2) ntimesteps = %d\n", ntimesteps);
  printf("#3) deltat = %le , deltax = %le , deltay = %le \n", deltat, deltax, deltay);
  printf("###########################################################\n");
  printf("###########################################################\n\n");
  
  FILE *fp;
  double inv_deltax2 = 1.0/(deltax*deltax); // assuming that deltax = deltay , we have a common alpha
  double alpha = deltat*inv_deltax2;
  
  printf("###########################################################\n");
  printf("Begin the intialization step by calling the aux-function\n");
  printf("###########################################################\n");
  
  initialize ();// start the initialization
  
  printf("From this initialization step, we can fixed the intial \n");
  printf("concentration profile as:\n");
  printf("[1] - c[R < 2.0] = 0.9 \n");
  printf("[2] - c[R > 2.0] = 0.1 \n");
  printf("###########################################################\n\n");  
  
  printf("Now we begin the calculations using Jacobi scheme!!!\n\n");
//////////////////////////////////////////////////////////////
  
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
      if (t%saveT == 0){
          sprintf(filename,"composition_%ld.dat", t);
          fp=fopen (filename,"w");
          writetofile (fp);
          fclose (fp);
      }// closes the writer function loop
  }// closes the loop in 't'
  printf("Now the code is completed successfully!!!!\n");
  printf("#########################################################\n");
  printf("Now you can plot the concentration profile using gnuplot\n");
  printf("Here is the command for t=0, 600, 1200, 1800:::\n\n");
  printf("set pm3d\n");
  printf("set multiplot layout 2,2\n");
  printf("set xtics rotate\n");
  printf("set bmargin 5\n");
  printf("set title 'composition-0' \n");
  printf("unset key\n");
  printf("splot 'composition_0.dat' us 1:2:3\n");
  printf("set title 'composition-600' \n");
  printf("unset key\n");
  printf("splot 'composition_600.dat' us 1:2:3\n");
  printf("set title 'composition-1200' \n");
  printf("unset key\n");
  printf("splot 'composition_1200.dat' us 1:2:3\n");
  printf("set title 'composition-1800' \n");
  printf("unset key\n");
  printf("splot 'composition_1800.dat' us 1:2:3\n");
  printf("\n");
  printf("[You can copy-paste the above code in gnuplot]\n");
  printf("#########################################################\n");
}// closes the main function

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