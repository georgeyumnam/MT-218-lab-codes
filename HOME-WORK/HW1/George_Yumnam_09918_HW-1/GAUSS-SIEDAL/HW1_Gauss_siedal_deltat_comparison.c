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
void initialize();
void writetofile(FILE *fp);

void main() {
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
  
  initialize() ; // this gives the intial state of the concentration
                 // i.e. 1.0 within the radius and 0.1 away from the radius  
  
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
    
    if (t == t_select) {// For writing the data into output files
      sprintf(filename, "composition_%le_%ld.dat", deltat, t);
      fp = fopen(filename, "w");
      writetofile(fp);
      fclose(fp);
    }// closing writer function loop
  }// closes the for loop in 't'
  
  printf("Completed the calculation for deltat = %le\n", deltat);

  }// closes loop for deltat
  
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
  printf("set title 'deltat = 0.5' \n");
  printf("unset key\n");
  printf("splot 'composition_%le_%d.dat' us 1:2:3\n", 5.000000e-01, 1200);
  printf("set title 'deltat = 0.6' \n");
  printf("unset key\n");
  printf("splot 'composition_%le_%d.dat' us 1:2:3\n", 6.000000e-01, 1200);
  printf("\n");
  printf("[You can copy-paste the above code in gnuplot]\n");
  printf("You can also try for different deltat values other than these!!!\n");
  printf("#########################################################\n\n"); 
  
  printf("As you can see that by deltat = 0.6, the maximum composition \n");
  printf("at the grid is 0.2... whereas, for deltat = 0.02 is >0.8 \n");
  printf("Therefore, deltat_max = 0.6 (independent of the choice of t_select)\n\n");
  
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
  } // Closes  the loop for for loop 
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
