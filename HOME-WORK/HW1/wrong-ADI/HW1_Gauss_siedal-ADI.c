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

double c_old[MESHX+2][MESHY+2]; // Define the array
void initialize();
void writetofile(FILE *fp);

void main() {
  
  printf("###########################################################\n");
  printf("   This is the code for Homework - 1\n");
  printf("   Implementation of 2D diffusion using the\n");
  printf("   Gauss-siedal scheme of iterations\n");
  printf("###########################################################\n\n");
  printf("   The given problem is to solve the following equation:\n");
  printf("   dC    ( d^2C   d^2C )\n");
  printf("   -- = D( ---- + ---- )\n");
  printf("   dt    ( dx^2   dy^2 )\n");
  printf("###########################################################\n\n");
  printf("           These are the defined variables::               \n");
  printf("1) MESHX = %d  and  MESHY = %d  \n", MESHX, MESHY);
  printf("2) ntimesteps = %d\n", ntimesteps);
  printf("3) deltat = %le , deltax = %le , deltay = %le \n", deltat, deltax, deltay);
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
  c_old[MESHX+2][MESHY+2]; // Define the array 
  double inv_deltax2 = 1.0/(deltax*deltax);
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
  printf("and solving it iteratively using Gauss-siedal scheme\n\n ");

  for (t=0; t < ntimesteps; t++) {  
    // Starting the case for implicit in x
    for (y=1; y<MESHY+1; y++){
      B_x[1] = 1.0 + 2.0*alpha;
      C_x[1] = -alpha;
      A_x[1] = 0.0;
      D_x[1] = c_old[1][y] + alpha*c_old[0][y] + 
	       alpha*(c_old[1][y-1] - 2.0*c_old[1][y] + c_old[1][y+1] ) ;
    
      for (x=2; x < MESHX+1; x++) {
	A_x[x] = -alpha;
	B_x[x] = 1.0 + 2.0*alpha;
	C_x[x] = -alpha;
	D_x[x] = c_old[x][y] + alpha*(c_old[x][y-1] - 2.0*c_old[x][y]
		+ c_old[x][y+1] );
	}
      C_x[MESHX] = 0.0;
      D_x[MESHX] = c_old[MESHX][y] + alpha*c_old[MESHX+1][y] 
                 + alpha*(c_old[MESHX][y-1] - 2.0*c_old[MESHX][y] 
		 + c_old[MESHX][y+1] );
      iter=0;
      for (iter=0; iter <= 10; iter++) { // Initiating the final calculation for gauss siedal
	//RED-POINTS
	  for (x=1; x <= MESHX; x+=2) {
	    c_old[x][y] = (D_x[x] - A_x[x]*c_old[x-1][y] - C_x[x]*c_old[x+1][y])/B_x[x];
	  }
	//GREEN-POINTS
	  for (x=2; x <= MESHX; x+=2) {
	    c_old[x][y] = (D_x[x] - A_x[x]*c_old[x-1][y] - C_x[x]*c_old[x+1][y])/B_x[x];
	  }
      }// ending the final calculation for gauss-siedal
    } // Ending the for loop on y for implicit in 'x' 
    
    // Starting the case for implicit in y
    for (x=1; x<MESHX+1; x++){
      B_y[1] = 1.0 + 2.0*alpha;
      C_y[1] = -alpha;
      A_y[1] = 0.0;
      D_y[1] = c_old[x][1] + alpha*c_old[x][0] + 
	       alpha*(c_old[x-1][1] - 2.0*c_old[x][1] + c_old[x+1][1] ) ;
    
      for (y=2; y < MESHY+1; y++) {
	A_y[y] = -alpha;
	B_y[y] = 1.0 + 2.0*alpha;
	C_y[y] = -alpha;
	D_y[y] = c_old[x][y] + alpha*(c_old[x-1][y] - 2.0*c_old[x][y]
		+ c_old[x+1][y] );
	}
        C_y[MESHY] = 0.0;
        D_y[MESHY] = c_old[x][MESHY] + alpha*c_old[x][MESHY+1] 
                   + alpha*(c_old[x-1][MESHY] - 2.0*c_old[x][MESHY] 
	  	   + c_old[x+1][MESHY] );
        iter=0;
        for (iter=0; iter <= 10; iter++) { // Initiating the final calculation for gauss siedal
	  //RED-POINTS
	    for (y=1; y <= MESHY; y+=2) {
	      c_old[x][y] = (D_y[y] - A_y[y]*c_old[x][y-1] - C_y[y]*c_old[x][y+1])/B_y[y];
	    }
          //GREEN-POINTS
	    for (y=2; y <= MESHY; y+=2) {
	      c_old[x][y] = (D_y[y] - A_y[y]*c_old[x][y-1] - C_y[y]*c_old[x][y+1])/B_y[y];
	    }
        }// terminating loop for final calculation of gauss siedal
      } // Ending the loop for implicit in 'y'


    if (t%saveT == 0) {
      sprintf(filename, "composition_%ld.dat",t);
      fp = fopen(filename, "w");
      writetofile(fp);
      fclose(fp);
    }
  }// closes the for loop in 't'
  printf("#########################################################\n");
  printf("Terminating the code at this point!!!\n");
  printf("Successful execution of the code\n");
  printf("Now you can plot the concentration profile using gnuplot\n");
  printf("Here is the command:::\n\n");
  printf("set pm3d\n");
  printf("set multiplot layout 2,2\n");
  printf("set xtics rotate\n");
  printf("set bmargin 5\n");
  printf("set title 'composition-A' \n");
  printf("unset key\n");
  printf("splot 'composition_A.dat' us 1:2:3\n");
  printf("set title 'composition-B' \n");
  printf("unset key\n");
  printf("splot 'composition_B.dat' us 1:2:3\n");
  printf("set title 'composition-C' \n");
  printf("unset key\n");
  printf("splot 'composition_C.dat' us 1:2:3\n");
  printf("set title 'composition-D' \n");
  printf("unset key\n");
  printf("splot 'composition_D.dat' us 1:2:3\n");
  printf("#########################################################\n"); 
}// closes the main function 

// The beginning of auxiliary functions 

void initialize(){
  long x, y;
  for (x=0; x <=(MESHX+1); x++){
    for (y=0; y <=(MESHY+1); y++){
      if(((x-(MESHX+1)/2)*(x-(MESHX+1)/2) + (y-(MESHY+1)/2)*(y-(MESHY+1)/2)) < radius*radius){
        c_old[x][y] = 0.9;
      } 
      else {
        c_old[x][y] = 0.1;
      }
    } 
  } // Closes  the loop for for loop 
} // CLoses initialize


void writetofile(FILE *fp){
  long x, y;
  for (x=0; x<=(MESHX+1); x++){
    for (y=0; y<=(MESHY+1); y++){
      fprintf(fp, "%le %le %le\n", x*deltax, y*deltay, c_old[x][y]);
    }
    fprintf(fp, "\n");
  }
}// CLoses writetofile

// ################################################################ //
