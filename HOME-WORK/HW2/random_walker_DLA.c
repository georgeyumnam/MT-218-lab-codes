#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

#define MESHX 100
#define MESHY 100

int status[MESHX][MESHY];

void main() {
  
  long x, y;    // For initial iterations
  
  for (x=0; x<MESHX; x++) {
    for (y=0; y<MESHY; y++) { 
      status[x][y] = 0;   // initialization of status
      if (x == MESHX/2){
            status[x][y] = 1;  // The seed for nucleation is a line
      }
    }
  }
  //status[MESHX/2][MESHY/2] = 1;  // The seed of the nucleation growth
  
  long xc, yc;     // 
  
  double rm;       // radius of growth
  double rnew;     // newly updated radius
  double rv;       // random variable
  
  double ang;      // angle --- going to be randomly determined
  
  long npart=0;    
  rm = 0;
  x=0; 
  y=0;
  
  while(rm < (MESHX/2)) {
    
    rnew = rm + 5;  // traersal of 5 points
    
    ang   = 2.0*M_PI*drand48(); // a random angle 
    xc = rnew*cos(ang);         // the resolved x direction of the angle
    yc = rnew*sin(ang);         // ------------ y ---------------------
    
    if ( ((xc > -(MESHX/2)) && (xc < (MESHX/2-1))) 
      && ((yc > -(MESHY/2)) && (yc < (MESHY-1))) ) { // increasing the max possible distance of traversal along y+
      x = xc + MESHX/2;         // the final x 
      y = yc + MESHY/2;         // --------- y
    }
    
    while((sqrt(((xc*xc)/2500)+((yc*yc)/10000)) < 1) &&  // if within the boundary for nucleation growth
          (status[x][y]==0)) {                // if the lattices are not updated then---
      
      rv = drand48();                    // creation of the random variable
      if ((rv>=0) && (rv <=0.1)) {      // this is for the traversal of the grain growth
        xc++;                            // equally ranodomly moving towards all 3 directions (x+, x-, y-)
      }                                  // y+ direction grain growth is enhanced
      if ((rv>0.1) && (rv <=0.2)) {     // 
        xc--;
      }
      if ((rv>0.2) && (rv <=0.3)) {
        yc--;
      }
      if ((rv>0.3) && (rv <=1.0)) {    // Here I am enhancing/biasing the nucleation growth along y+
        yc++;                          // direction of the MESH grid by this comment.
      }
      
      if ( ( (xc > -(MESHX/2)) && (xc < (MESHX/2-1)) )       // Checking if the growth has not exceeded the range.
        && ( (yc > -(MESHY/2)) && (yc < (MESHY-1)) ) ) {   // if still within the range, then update x, y.
        x = xc + MESHX/2;                                   // in this if condition, yc+ is biased for longer traversal
        y = yc + MESHY/2;
      }
      
      printf("x=%ld, y=%ld\n",x,y);
      
      if((y==MESHY/2) && (x > 0) &&            // if not the seed (x coordinate)
         (x < (MESHX-1)) &&    // if within mesh grid of x
         (y > 0) &&            // if not the seed (y coordinate)
         (y < ((2*MESHY)-1)) &&    // if within mesh grid of y
         ((status[x+1][y]==1) || (status[x-1][y]==1) /*|| (status[x][y-1]==1) || (status[x][y+1]==1))*/ ) {
                               // if any of the neighbours of (x,y) are populated  ----> then --> do the following:
        status[x][y] = 1;  // nucleate the (x,y) point
      
        if (((xc*xc)/(rm*rm)) + ((yc*yc)/(4*rm*rm)) > 1) { // parameter for when to stop the nucleation
          rm = sqrt(xc*xc + ((yc*yc)/4));                  //
        }
        npart++;
        printf("Number of particles=%ld\n",npart);
      }
    }
  }
  FILE *fp;
  
  fp= fopen("solid.dat","w");
  for (x=0; x < MESHX; x++) {
    for (y=0; y < 2*MESHY; y++) {
      fprintf(fp, "%ld %ld %le\n", x, y, status[x][y]*sqrt( ((x-(MESHX/2))*(x-(MESHX/2))) + ((y-(MESHY))*(y-(MESHY))) );
    }
    fprintf(fp, "\n");
  }
  fclose(fp);
}
