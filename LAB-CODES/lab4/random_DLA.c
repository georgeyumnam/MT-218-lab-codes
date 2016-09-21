#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<time.h>

#define MESHX 100  // To define a grid
#define MESHY 100

// to define whether a material is solid or not
int status[MESHX][MESHY];

void main(){
  
  long x, y;
  
  for (x=0; x<MESHX; x++){
    for (x=0; x<MESHX; x++){
      status[x][y] = 0;
    }
  }
  status[MESHX/2][MESHY/2];
  
  long xc, yc; // measured from the centre of the grid 
	       // at the centre, these variable are zero
  double rm, rnew; // maximum distance from the centre
  double rv; // random variable
  double ang;
  long npart=0;
  
  rm = 0.0;
  
  while (rm < (MESHX/2)){
    
    rnew = rm + 5;
    
    ang = 2.0*M_PI*drand48();
    
    xc = rnew*cos(ang);  // x coordinate of rnew
    yc = rnew*sin(ang);  // y - - - -
    
    while ((sqrt(xc*xc+ yc*yc) < (rm + 50)) &&  // why are u within a range // conditions for being inside the wall 
      ((xc > MESHX/2) || xc < (-MESHX/2)) && ((yc > MESHY/2) || yc < (-MESHY/2) ) // conditions for stopping the growth
      && (status[xc+MESHX/2][xc+MESHY/2] == 0)){
	
      rv = drand48();
    
	if ((rv >0) && (rv <=0.25)) {  
	  xc++;
	}
	if ((rv >0.25) && (rv <=0.5)) {
	  xc--;
	}
	if ((rv >0.5) && (rv <=0.75)) {
	  yc++;
	}
	if ((rv >0.75) && (rv <=1.0)) {
	  yc--;
	}
	
	x = xc + MESHX/2 ;
	y = yc + MESHY/2 ;
	
	
	
	if ((status[x+1][y]==1) || (status[x-1][y] == 1) || (status[x][y-1]==1) || (status[x][y+1] == 1) ){
	  status[x][y] = 1;
	}
	if (xc*xc + yc*yc > rm){
	  rm = xc*xc + yc*yc ;
	}
      }
    }
    
    FILE *fp;
    fp = fopen("solid.dat", "w");
    
    for (x=0; x< MESHX; x++){
      for (y=0; y< MESHY; y++){
	fprintf(fp, "%ld %ld %le\n", x, y, status[x][y]*sqrt((x-(MESHX/2))*(x-(MESHX/2))+(y-(MESHY/2))*(y-(MESHY/2))));
      }
      fprintf(fp, "\n");
    }
    fclose(fp);
  }
  
  
  
  // Compile using gcc <code.c> -o <output> -lm // -lm to link the math library