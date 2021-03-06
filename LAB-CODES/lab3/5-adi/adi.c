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

void main(){
  long t;	// define the time steps
  long x, y;    // define the space variable in 2D
  
  //void initialize();
  //void writetofile(FILE *fp);
  
  double A_x[MESHX+1];
  double B_x[MESHX+1];
  double C_x[MESHX+1];
  double D_x[MESHX+1];
  
  double A_y[MESHY+1];
  double B_y[MESHY+1];
  double C_y[MESHY+1];
  double D_y[MESHY+1];
  
  char filename[1000];
  FILE *fp;
  
  double inv_deltax2 = 1.0/(deltax*deltax);
  double alpha = deltat*inv_deltax2;
  
  initialize();
  
  for (t=0; t<ntimesteps; t++){
    // Starting the case for implicit in x
    for (y=1; y<MESHY; y++){ // We cannot write for x=0, since it is 
      B_x[1]=1.0 + 2*alpha;
      C_x[1]=-alpha;
      A_x[1]=0.0;
      D_x[1]=c_old[1][y] + alpha*c_old[0][y] 
      + alpha*(c_old[1][y-1] - 2.0*c_old[1][y] + c_old[1][y+1]);
      
      for (x=2; x<MESHX+1; x++){ // We cannot write for x=0, since it is 
	B_x[x]=1.0 + 2.0*alpha;
	C_x[x]=-alpha;
	A_x[x]=-alpha;
	D_x[x]=c_old[x][y] + alpha*(c_old[x][y-1] - 2.0*c_old[x][y] + c_old[x][y+1]);
      }
      C_x[MESHX] = 0.0;
      D_x[MESHX] = c_old[MESHX][y] + alpha*c_old[MESHX+1][y]
      + alpha*(c_old[MESHX][y-1] - 2.0*c_old[MESHX][y] + c_old[MESHX][y+1]);

      // Transform matrix 
      for (x=2; x<=MESHX; x++){
	B_x[x] = -C_x[x-1]*(A_x[x]/B_x[x-1]) + B_x[x];
	D_x[x] = -D_x[x-1]*(A_x[x]/B_x[x-1]) + D_x[x];
	}
	  
	// Backward substitution
	c_old[MESHX][y] = D_x[MESHX]/B_x[MESHX];
	 
	for (x=MESHX-1; x>=1; x--){
	c_old[x][y] = (D_x[x] - C_x[x]*c_old[x+1][y])/B_x[x];
	}
    }// Closes the for loop for implicit in x case
    
    // Starting the part of implicit in y
    for (x=1; x<MESHX; x++){ // We cannot write for x=0, since it is 
      B_y[1]=1.0 + 2*alpha;
      C_y[1]=-alpha;
      A_y[1]=0.0;
      D_y[1]=c_old[x][1] + alpha*c_old[x][0] 
      + alpha*(c_old[x-1][1] - 2.0*c_old[x][1] + c_old[x+1][1]);
      
      for (y=2; y<MESHY+1; y++){ // We cannot write for x=0, since it is 
	B_y[y]=1.0 + 2*alpha;
	C_y[y]=-alpha;
	A_y[y]=-alpha;
	D_y[y]=c_old[x][y] + alpha*(c_old[x+1][y] - 2.0*c_old[x][y] + c_old[x-1][y]);
      }
      C_y[MESHY] = 0.0;
      D_y[MESHY] = c_old[x][MESHY] + alpha*c_old[x][MESHY+1]
      + alpha*(c_old[x-1][MESHY] - 2.0*c_old[x][MESHY] + c_old[x+1][MESHY]);
      
      // Transform matrix 
      for (y=2; y<=MESHX; y++){
	B_y[y] = -C_y[y-1]*(A_y[y]/B_y[y-1]) + B_y[y];
	D_y[y] = -D_y[y-1]*(A_y[y]/B_y[y-1]) + D_y[y];
	}
	  
	// Backward substitution
	c_old[x][MESHY] = D_y[MESHY]/B_y[MESHY];
	 
	for (y=MESHY-1; y>=1; y--){
	c_old[x][y] = (D_y[y] - C_y[y]*c_old[x][y+1])/B_y[y];
	}
    }// Closes the for loop for implicit in y case
    
    if (t%saveT == 0){
	    sprintf(filename, "composition%ld.dat", t);
	    fp = fopen(filename, "w");
	    writetofile(fp);	  
	    fclose(fp);
	  }
    }// closes the timestep loop
}// closes main function

    void initialize(){
      long x, y;
      for (x=0; x <=MESHX+1; x++){
	for (y=0; y <=MESHY+1; y++){
	  if((x-(MESHX+1)/2)*(x-(MESHX+1)/2) + (y-(MESHY+1)/2)*(y-(MESHY+1)/2) < radius*radius){
	    c_old[x][y] = 0.5;
	  } else {
	    c_old[x][y] = 0.0;
	  }
	  } 
	} // Closes  the loop for for loop 
      } // CLoses initialize
      
    void writetofile(FILE *fp){
      long x, y;
      for (x=0; x<=MESHX+1; x++){
	for (y=0; y<=MESHY+1; y++){
	  fprintf(fp, "%le %le %le\n", x*deltax, y*deltay, c_old[x][y]);
	}
	fprintf(fp, "\n");
      }
    }// CLoses writetofile