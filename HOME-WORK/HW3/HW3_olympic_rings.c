#include<stdio.h>
#include<stdlib.h>
#include<math.h>
//we define sqquare bw -3,-3 and 3,3 to intgrate area of circle

#define xrange (8.0)
#define yrange (6.0)
#define RADIUS_SQUARED (3.0)

#define NRAM 10000000

void main(){
	double x, y ;
	
	long iter;
	long one_intersection=0;
	long two_intersection=0;
	long three_intersection=0;
	
	for(iter = 0; iter<NRAM; iter++){
		x = -4 + xrange*drand48();
		y = -3 + yrange*drand48();
		
		if ( ( (x + 2)*(x + 2) + (y - 1)*(y - 1) <= RADIUS_SQUARED &&      // circle of center --> (-2, 1) 
		       (x)*(x) + (y - 1)*(y - 1)         <= RADIUS_SQUARED &&      // circle of center --> ( 0, 1)
		       (x + 1)*(x + 1) + (y + 1)*(y + 1) <= RADIUS_SQUARED )  ||   // circle of center --> (-1,-1) ----||
		     ( (x + 1)*(x + 1) + (y + 1)*(y + 1) <= RADIUS_SQUARED &&      //  --> (-1,-1)
		       (x)*(x) + (y - 1)*(y - 1)         <= RADIUS_SQUARED &&      //  --> ( 0, 1)
		       (x - 1)*(x - 1) + (y + 1)*(y + 1) <= RADIUS_SQUARED ) ||    //  --> ( 1,-1)  ----||
		     ( (x)*(x) + (y - 1)*(y - 1)         <= RADIUS_SQUARED &&      //  --> ( 0, 1)
		       (x -1)*(x - 1) + (y + 1)*(y + 1)  <= RADIUS_SQUARED &&       //  --> ( 1,-1)
		       (x - 2)*(x - 2) + (y - 1)*(y - 1) <= RADIUS_SQUARED ) ||    //  --> ( 2, 1)  ----||
		     ( (x + 2)*(x + 2) + (y - 1)*(y - 1) <= RADIUS_SQUARED &&      //  --> (-2, 1)
		       (x)*(x) + (y - 1)*(y - 1)         <= RADIUS_SQUARED &&              //  --> ( 0, 1)
		       (x - 2)*(x - 2) + (y - 1)*(y - 1) <= RADIUS_SQUARED )       //  --> ( 2, 1)
		   ){
			three_intersection++;
		}
		if ( ( (x + 2)*(x + 2) + (y - 1)*(y - 1) <= RADIUS_SQUARED &&      // 
		       (x)*(x) + (y - 1)*(y - 1)         <= RADIUS_SQUARED ) || 
		     ( (x + 2)*(x + 2) + (y - 1)*(y - 1) <= RADIUS_SQUARED && 
		       (x+1)*(x+1) + (y + 1)*(y +1)      <= RADIUS_SQUARED ) ||  
		     ( (x + 1)*(x + 1) + (y + 1)*(y + 1) <= RADIUS_SQUARED && 
		       (x)*(x) + (y - 1)*(y - 1)         <= RADIUS_SQUARED ) ||  
		     ( (x)*(x) + (y - 1)*(y - 1)         <= RADIUS_SQUARED && 
		       (x-1)*(x-1) + (y + 1)*(y +1)      <= RADIUS_SQUARED ) || 
		     ( (x)*(x) + (y - 1)*(y - 1)         <= RADIUS_SQUARED && 
		       (x - 2)*(x - 2) + (y - 1)*(y - 1) <= RADIUS_SQUARED) || 
		     ( (x - 1)*(x - 1) + (y + 1)*(y + 1) <= RADIUS_SQUARED && 
		       (x-2)*(x-2) + (y - 1)*(y - 1)     <= RADIUS_SQUARED ) ||  
		     ( (x + 1)*(x + 1) + (y + 1)*(y + 1) <= RADIUS_SQUARED && 
		       (x - 1)*(x - 1) + (y + 1)*(y + 1) <= RADIUS_SQUARED ) 
		   ) {
			two_intersection++;
		}
		if ( (x + 2)*(x + 2) + (y - 1)*(y - 1) <= RADIUS_SQUARED || 
		     (x + 1)*(x + 1) + (y + 1)*(y + 1) <= RADIUS_SQUARED || 
		     (x)*(x) + (y - 1)*(y - 1)         <= RADIUS_SQUARED || 
		     (x - 1)*(x - 1) + (y + 1)*(y + 1) <= RADIUS_SQUARED || 
		     (x - 2)*(x - 2) + (y - 1)*(y - 1) <= RADIUS_SQUARED
		   ){
			one_intersection++;
		}
	}
	printf("\n");
	printf("Area of circle............... = %.4le\n", M_PI*RADIUS_SQUARED*RADIUS);                            // pi*r^2
	printf("Area of 3 junction........... = %.4le\n", ((double)(three_intersection)/(double)(NRAM))*48.0 );        // 
	printf("Area of 2 junction........... = %.4le\n", ((double)(two_intersection-three_intersection)/(double)(NRAM))*48.0); 
	printf("Area of no intersection...... = %.4le\n", ((double)(one_intersection-two_intersection)/(double)(NRAM))*48.0);
	printf("\n");

}
