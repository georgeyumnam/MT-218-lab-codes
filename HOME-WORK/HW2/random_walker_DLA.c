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
    }
  }
  status[MESHX/2][MESHY/2] = 1;  // The seed of the nucleation growth
  
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
    
    rnew = rm + 5;  // radius of 5 
    
    ang   = 2.0*M_PI*drand48(); // a random angle 
    xc = rnew*cos(ang);         // the resolved x direction of the angle
    yc = rnew*sin(ang);         // ------------ y ---------------------
    
    if ( ((xc > -(MESHX/2)) && (xc < (MESHX/2-1))) 
      && ((yc > -(MESHY/2)) && (yc < (MESHY/2-1))) ) {
      x = xc + MESHX/2;         // the final x 
      y = yc + MESHY/2;         // --------- y
    }
    
    while((sqrt(xc*xc+yc*yc) < (rm + 50)) &&  // if within the circle for nucleation growth
          (status[x][y]==0)) {                // if the lattices are not updated then---
      
      rv = drand48();    // creation of the random variable
      if ((rv>=0) && (rv <=0.25)) {      // this is for the traversal of the grain growth
        xc++;                            // equally randomly moving towards all 4 directions
      }
      if ((rv>0.25) && (rv <=0.5)) {
        xc--;
      }
      if ((rv>0.5) && (rv <=0.75)) {
        yc++;
      }
      if ((rv>0.75) && (rv <=1.0)) {
        yc--;
      }
      
      if (((xc > -(MESHX/2)) && xc < (MESHX/2-1)) 
        && (yc > -(MESHY/2)) && (yc < (MESHY/2-1))) {
        x = xc + MESHX/2;
        y = yc + MESHY/2;
      }
      
      printf("x=%ld, y=%ld\n",x,y);
      
      if((x > 0) &&
         (x < (MESHX-1)) &&
         (y > 0) && 
         (y < (MESHY-1)) && 
         ((status[x+1][y]==1) || (status[x-1][y]==1) || (status[x][y-1]==1) || (status[x][y+1]==1)) ) {
        status[x][y] = 1;
      
        if (xc*xc + yc*yc > rm*rm) {
          rm = sqrt(xc*xc + yc*yc);
        }
        npart++;
        printf("Number of particles=%ld\n",npart);
      }
    }
  }
  FILE *fp;
  
  fp= fopen("solid.dat","w");
  for (x=0; x < MESHX; x++) {
    for (y=0; y < MESHY; y++) {
      fprintf(fp, "%ld %ld %le\n", x, y, status[x][y]*
      sqrt((x-(MESHX/2))*(x-(MESHX/2)) + (y-(MESHY/2))*(y-(MESHY/2))));
    }
    fprintf(fp, "\n");
  }
  fclose(fp);
}