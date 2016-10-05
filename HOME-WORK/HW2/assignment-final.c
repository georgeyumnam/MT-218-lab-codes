#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

#define MESHX 100
#define MESHY 100

int status[MESHX][MESHY];

void main() {
  FILE *fpp;
  long x, y; // For initial iterations
  fpp= fopen("init_solid.dat","w");
  for (x=0; x<MESHX; x++) {
    for (y=0; y<MESHY; y++) { 
      status[x][y] = 0;         // initialization of status
      if (x == 0){
            status[x][y] = 1;  // The seed for nucleation is a line
      }
      fprintf(fpp, "%ld %ld %le\n", x, y, status[x][y]*((sqrt((x-(MESHX/2))*(x-(MESHX/2))) + sqrt((y-(MESHY/2))*(y-(MESHY/2))))/2));
    }
    fprintf(fpp, "\n");
  }
    fclose(fpp);
 // status[MESHX/2][MESHY/2] = 1;
  
  long xc, yc;
  
  double rm;           // radius of growth
  double rnew;     // newly updated radius
  double rv;       // random variable
  
  double ang;        // angle --- going to be randomly determined
  int checker_stat;
  long npart=0;     
  rm = 0;
  x=0; 
  y=0;
  
  
  // This starts the nucleation step --- > start nucleation along the biased direction.
  while(rm < (MESHX - 2)) {
    
    rnew = rm + 2;              // 
    
 //   ang = 2.0*M_PI*drand48(); // a random angle 
    xc = (rnew-4)+ 6*drand48();
//    xc = rnew*cos(ang);         // the resolved x direction of the angle
 //   yc = rnew*sin(ang);         // ------------ y ---------------------
    yc = -(MESHY/10) + (MESHY+20)*drand48();
    checker_stat = 0; // initialize the checker to 0
    if ((xc < MESHX) && (yc < MESHY)){
        //( (xc > -(MESHX/2)) && (xc < (MESHX/2-1))       
        //&& (yc > -(MESHY/2)) && (yc < (MESHY/2-1)) ) {
      x = xc;// + MESHX/2;         
      y = yc;// + MESHY/2;
    }
    
    if (xc < 2)
    {
      checker_stat = 1; 
    }
    
    
   // while((sqrt(xc*xc+yc*yc) < (rm + 50)) && 
    //while( ((xc+yc) < (rm + (MESHX+MESHY)/4)) &&  (status[x][y] == 0)) {
      while ((xc > 0) && (xc < (rm + 10)) && (yc > -10) && (yc < (MESHY+10)) && (checker_stat == 0) && (status[x][y] == 0)){
      rv = drand48();
      
      if ((rv>=0) && (rv <=0.25)) {
        xc++;
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
      
      if ((xc > 0) && (xc < (MESHX-1)) && (yc > 0) && (yc < (MESHY-1))){
      //if (((xc > -(MESHX/2)) && (xc < (MESHX/2-1))) 
        //&& (yc > -(MESHY/2)) && (yc < (MESHY/2-1))) {
        x = xc;// + MESHX/2;
        y = yc;// + MESHY/2;
      }
      
      printf("x=%ld, y=%ld\n",x,y);
      
      
      if( (x > 0) && (x < (MESHX-1)) && (y > 0) && (y < (MESHY-1)) \
          && ((status[x+1][y]==1) || (status[x-1][y]==1)  \
          ||  (status[x][y-1]==1) || (status[x][y+1]==1)) ) {   // The selection crteria is same i.e. to update if the neighbours are updated
        status[x][y] = 1;
      checker_stat = 1;
      
        if (xc > rm) {
          rm = xc;
        }
       // npart++;
        printf("Number of particles=%ld\n",npart);
      }
    }
  }
  FILE *fp;
  
  fp= fopen("solid.dat","w");
  for (x=0; x < MESHX; x++) {
    for (y=0; y < MESHY; y++) {
      fprintf(fp, "%ld %ld %le\n", x, y, status[x][y]*((sqrt((x-(MESHX/2))*(x-(MESHX/2))) + sqrt((y-(MESHY/2))*(y-(MESHY/2))))/2));
    }
    fprintf(fp, "\n");
  }
  fclose(fp);
}