#include<stdio.h>
#include<stdlib.h>
#include<math.h>
//we define sqquare bw -3,-3 and 3,3 to intgrate area of circle

#define xrange (6.0)
#define yrange (3.0)
#define RADIUS (0.98)

#define NRAM 100000000

void main(){
	double x, y ;
	
	long iter;
	long one_intersection=0;
	long two_intersection=0;
	long three_intersection=0;
	
	for(iter = 0; iter<NRAM; iter++){
		x = -3.0 + xrange*drand48();
		y = -1.0 + yrange*drand48();
		
		if ( ( (x + 2)*(x + 2) + (y - 1)*(y - 1) <= RADIUS*RADIUS &&      // circle of center --> (-2, 1) 
		       (x)*(x) + (y - 1)*(y - 1)         <= RADIUS*RADIUS &&      // circle of center --> ( 0, 1)
		       (x + 1)*(x + 1) + (y)*(y)         <= RADIUS*RADIUS ) ||    // circle of center --> (-1, 0) ----||
		     ( (x + 1)*(x + 1) + (y)*(y)         <= RADIUS*RADIUS &&      //  --> (-1, 0)
		       (x)*(x) + (y - 1)*(y - 1)         <= RADIUS*RADIUS &&      //  --> ( 0, 1)
		       (x - 1)*(x - 1) + (y)*(y) 	 <= RADIUS*RADIUS ) ||    //  --> ( 1, 0)  ----||
		     ( (x)*(x) + (y - 1)*(y - 1)         <= RADIUS*RADIUS &&      //  --> ( 0, 1)
		       (x -1)*(x - 1) + (y)*(y)   	 <= RADIUS*RADIUS &&      //  --> ( 1, 0)
		       (x - 2)*(x - 2) + (y - 1)*(y - 1) <= RADIUS*RADIUS ) ||    //  --> ( 2, 1)  ----||
		     ( (x + 2)*(x + 2) + (y - 1)*(y - 1) <= RADIUS*RADIUS &&      //  --> (-2, 1)
		       (x)*(x) + (y - 1)*(y - 1)         <= RADIUS*RADIUS &&      //  --> ( 0, 1)
		       (x - 2)*(x - 2) + (y - 1)*(y - 1) <= RADIUS*RADIUS )       //  --> ( 2, 1)
		   ){
			three_intersection++;
		}
		if ( ( (x + 2)*(x + 2) + (y - 1)*(y - 1) <= RADIUS*RADIUS && 
		       (x + 1)*(x + 1) + (y)*(y)         <= RADIUS*RADIUS ) ||    //-------- ||
		     ( (x + 1)*(x + 1) + (y)*(y)         <= RADIUS*RADIUS && 
		       (x)*(x) + (y - 1)*(y - 1)         <= RADIUS*RADIUS ) ||    //-------- ||
		     ( (x)*(x) + (y - 1)*(y - 1)         <= RADIUS*RADIUS && 
		       (x-1)*(x-1) + (y)*(y)             <= RADIUS*RADIUS ) ||    //-------- ||
		     ( (x - 1)*(x - 1) + (y)*(y)         <= RADIUS*RADIUS && 
		       (x-2)*(x-2) + (y - 1)*(y - 1)     <= RADIUS*RADIUS )     //-------- ||
		   ) {
			two_intersection++;
		}
		if ( (x + 2)*(x + 2) + (y - 1)*(y - 1)   <= RADIUS*RADIUS || 
		     (x + 1)*(x + 1) + (y)*(y)           <= RADIUS*RADIUS || 
		     (x)*(x) + (y - 1)*(y - 1)           <= RADIUS*RADIUS || 
		     (x - 1)*(x - 1) + (y)*(y)           <= RADIUS*RADIUS || 
		     (x - 2)*(x - 2) + (y - 1)*(y - 1)   <= RADIUS*RADIUS
		   ){
			one_intersection++;
		}
	}
	printf("\n");
	printf("Area of one circle.......................... = %.4le\n", M_PI*RADIUS*RADIUS);                            // pi*r^2
	printf("Area of 3 junction.......................... = %.4le\n", ((double)(three_intersection)/(double)(NRAM))*xrange*yrange);        // 
	printf("Area of 2 junction.......................... = %.4le\n", 
					((double)(two_intersection - three_intersection)/(double)(NRAM))*xrange*yrange); 
	printf("Area of no intersection..................... = %.4le\n\n", 
	 				((double)(one_intersection - two_intersection)/(double)(NRAM))*xrange*yrange);
	printf("Total area (ANALYTIC) with double counting.. = %.4le\n", 5*M_PI*RADIUS*RADIUS );
/*	printf("Total area (COMPUTED) with double counting.. = %.4le\n", 
					((double)(three_intersection)/(double)(NRAM))*48.0 				+ 
					((double)(two_intersection - three_intersection)/(double)(NRAM))*48.0*4 	+ 
					((double)(one_intersection - two_intersection)/(double)(NRAM))*48.0 			);
*/
	printf("Total area (COMPUTED) with double counting.. = %.4le\n", ( ((double)(one_intersection)/(double)(NRAM))*xrange*yrange + ((double)(two_intersection - three_intersection)/(double)(NRAM))*xrange*yrange ) );
}
