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
void initialize();
void writetofile(FILE *fp);

void main() {
  
  printf("###########################################################\n");
  printf("#   This is the code for Homework - 1\n");
  printf("#   Implementation of 2D diffusion using the\n");
  printf("#   Gauss-siedal scheme of iterations\n");
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
  
  FILE *fp;
  double inv_deltax2 = 1.0/(deltax*deltax); // assuming that deltax = deltay , we have a common alpha
  double alpha = deltat*inv_deltax2;  
  
  printf("###########################################################\n");
  printf("Begin the intialization step by calling the aux-function\n");
  printf("###########################################################\n");
  initialize() ; //  this gives the intial state of the concentration
		  // i.e. 0.9 within the radius and 0.1 away from the radius
  printf("From this initialization step, we can fixed the intial \n");
  printf("concentration profile as:\n");
  printf("[1] - c[R < 2.0] = 0.9 \n");
  printf("[2] - c[R > 2.0] = 0.1 \n");
  printf("###########################################################\n\n");
  
  printf("Now defining the coefficients of the matrix form!!!!\n");
  printf("and solving it iteratively using Gauss-siedal scheme\n\n\n ");

  
printf(" Beginning the Gauss - Seidel red-green iteration process\n "
"    Consider - * = Red points\n"
"               # = Green points\n"
"Then we have the array:\n"
"\n"
"Y/X -->  0 1 2 3 4 5 6 7 8 9 . . . \n"
"      0  * # * # * # * # * # * # * # * # * # * # * # * # * # * # \n"
"      1  # * # * # * # * # * # * # * # * # * # * # * # * # * # * \n"
"      2  * # * # * # * # * # * # * # * # * # * # * # * # * # * # \n"
"      3  # * # * # * # * # * # * # * # * # * # * # * # * # * # * \n"
"      4  * # * # * # * # * # * # * # * # * # * # * # * # * # * # \n"
"      5  # * # * # * # * # * # * # * # * # * # * # * # * # * # * \n"
"      6  * # * # * # * # * # * # * # * # * # * # * # * # * # * # \n"
"      7  # * # * # * # * # * # * # * # * # * # * # * # * # * # * \n"
"      8  * # * # * # * # * # * # * # * # * # * # * # * # * # * # \n"
"      9  # * # * # * # * # * # * # * # * # * # * # * # * # * # * \n"
"      .  * # * # * # * # * # * # * # * # * # * # * # * # * # * # \n"
"      .  # * # * # * # * # * # * # * # * # * # * # * # * # * # * \n"
" \n" 
"We can see that the occurrence of every * is when (X+Y)=even \n" 
"            and the occurrence of every # is when (X+Y)=odd \n"
"\n"
"So, for updating the red-points and green-points alternatively, \n" 
"we are going to use this logic for identifying the red or green \n" 
"points. And accordingly, we will apply the Gauss-siedal scheme. \n" );

  
  
  for (t=0; t < ntimesteps; t++) {  // Initiating time steps
    for (y=0; y <= MESHY+1; y++){ // For all values of y 
      for (x=0; x <= MESHX+1; x++) { // For all values of x
        c_old[x][y] = c_now[x][y]; // Storing the current values of c before moving from t --> (t+1) 
       }// closing the x loop
    }// closing the y loop
      
      for (iter=0; iter <= 10; iter++) { // Iterations to convergence - for error minimization
	//RED-POINTS
          for (y=1; y < MESHY+1; y++) {
              for (x=2; x < MESHX+1; x++) {
                  if((x+y)%2==0){// This if loop is defined according to the above logic !!!
                      c_now[x][y] = (alpha*(c_now[x-1][y]+c_now[x+1][y]+c_now[x][y+1]+c_now[x][y-1])+c_old[x][y])/(1+4*alpha);
                  }// closing if loop
              }
	  }
	//GREEN-POINTS
          for (y=1; y < MESHY+1; y++) {
              for (x=2; x < MESHX+1; x++) {
                  if((x+y)%2!=0){ // Same argument for the green-points
                      c_now[x][y] = (alpha*(c_now[x-1][y]+c_now[x+1][y]+c_now[x][y+1]+c_now[x][y-1])+c_old[x][y])/(1+4*alpha);
                  }// closing if loop
              }
          }  
      }// ending the final calculation for gauss-siedal
    
    if (t%saveT == 0) {// For writing the data into output files
      sprintf(filename, "composition_%ld.dat",t);
      fp = fopen(filename, "w");
      writetofile(fp);
      fclose(fp);
    }// closing writer function loop
    
  }// closes the for loop in 't'
  
  printf("#########################################################\n");
  printf("Terminating the code at this point!!!\n");
  printf("Successful execution of the code\n");
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

// The beginning of auxiliary functions 

void initialize(){
  long x, y;
  for (x=0; x <=(MESHX+1); x++){
    for (y=0; y <=(MESHY+1); y++){
      if(((x-(MESHX+1)/2)*(x-(MESHX+1)/2) + (y-(MESHY+1)/2)*(y-(MESHY+1)/2)) < radius*radius){
        c_now[x][y] = 1.0;
      } 
      else {
        c_now[x][y] = 0.1;
      }
    } 
  } // Closes  the loop for 'for' loop 
} // CLoses initialize


void writetofile(FILE *fp){
  long x, y;
  for (x=0; x<=(MESHX+1); x++){
    for (y=0; y<=(MESHY+1); y++){
      fprintf(fp, "%le %le %le\n", x*deltax, y*deltay, c_now[x][y]);
    }
    fprintf(fp, "\n");
  }
}// CLoses writetofile
// ################################################################ //
