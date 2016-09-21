#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MESHX 100
#define MESHY 100

#define ntime 1000
#define deltat 0.1
#define deltax 1.0
#define deltay 1.0
#define saveT 200
#define radius 20
double c_old[MESHX+2][MESHY+2];
double c_k[MESHX+2][MESHY+2];

void initialize();
void update();
void writetofile (FILE *fp);

void main ()
{
	long t;
	long x,y;
	char filename [1000];
	
	double a_x[MESHX+1];
	double b_x[MESHX+1];
	double c_x[MESHX+1];
	double d_x[MESHX+1];
	
	double a_y[MESHY+1];
	double b_y[MESHY+1];
	double c_y[MESHY+1];
	double d_y[MESHY+1];
	double c_prev[MESHX+2][MESHY+2];
	
	double inv_deltax2 = 1/(deltax*deltax);
	long iter;
	long count;
	double diff = 0.0;
	
	double alpha = inv_deltax2*deltat;
	
	FILE *fp;
	fp=fopen ("plot.dat","w");
	fclose(fp);
	
	initialize();
	update();
	
for (count=5;count<=20;count++)
{
	for (y=0;y<MESHY+1;y++)
	{
		for (x=0;x<MESHX+1;x++)
		{
			c_prev[x][y] = c_old[x][y];
		}
	}
	for (t=0;t<ntime;t++)
	{
	
		//implicit in x using jacobi method
		for (y=1;y<MESHY+1;y++)
		{
			d_x[1] = c_old[1][y] + alpha*c_old[0][y] + alpha*(c_old[1][y-1] - 2.0*c_old[1][y] + c_old[1][y+1]);
			a_x[1] = 0.0;
			b_x[1] = 1.0+2.0*alpha;
			c_x[1] = -alpha;
			for (x=2;x<MESHX+1;x++)
			{
				a_x[x] = -alpha;
				b_x[x] = 1.0+2.0*alpha;
				c_x[x] = -alpha;
				d_x[x] = c_old[x][y] + alpha*(c_old[x][y-1] - 2.0*c_old[x][y] + c_old[x][y+1]);
			}
			c_x[MESHX]  = 0.0;
			d_x[MESHX] = c_old[MESHX][y] + alpha*c_old[MESHX+1][y] + alpha*(c_old[MESHX][y-1] - 2.0*c_old[MESHX][y] + c_old[MESHX][y+1]);
			iter=0;
			update(c_old,c_k);
			for(iter=0;iter<count;iter++)
			 { 
				for(x=1;x<MESHX+1; x++)
				{
					c_old[x][y] = (d_x[x] - a_x[x]*c_k[x-1][y] - c_x[x]*c_k[x+1][y])/b_x[x];
				}
				update(c_old,c_k);
			 }
	    }
	    
	    
	    
	    //implicit in y using jacobi method
	    for (x=1;x<MESHX+1;x++)
		{
			d_y[1] = c_old[x][1] + alpha*c_old[x][0] + alpha*(c_old[x-1][1] - 2.0*c_old[x][1] + c_old[x+1][1]);
			a_y[1] = 0.0;
			b_y[1] = 1.0+2.0*alpha;
			c_y[1] = -alpha;
			for (y=2;y<MESHY+1;y++)
			{
				a_y[y] = -alpha;
				b_y[y] = 1.0+2.0*alpha;
				c_y[y] = -alpha;
				d_y[y] = c_old[x][y] + alpha*(c_old[x-1][y] - 2.0*c_old[x][y] + c_old[x+1][y]);
			}
			c_y[MESHY]  = 0.0;
			d_y[MESHY] = c_old[x][MESHY] + alpha*c_old[x][MESHY+1] + alpha*(c_old[x-1][MESHY] - 2.0*c_old[x][MESHY] + c_old[x+1][MESHY]);
			iter=0;
			update(c_old,c_k);
			for(iter=0;iter<count;iter++)
			 { 
				for(y=1;y<MESHX+1; y++)
				{
					c_old[x][y] = (d_y[y] - a_y[y]*c_k[x][y-1] - c_y[y]*c_k[x][y+1])/b_y[y];
				}
				update(c_old,c_k);
			 }
	    }          	
	}
	
		diff = fabs(c_prev[45][25]-c_old[45][25]);
		fp=fopen ("plot.dat","a");
		fprintf (fp,"%ld %le\n",count,diff);
		fclose (fp);
  }	
}


void initialize()
{
	 long x,y;
	 for (x=0;x<=(MESHX+1);x++)
	 {
		 for(y=0;y<=(MESHY+1);y++)
		 {
			 if (((x-(MESHX+1)/2)*(x-(MESHX+1)/2) + (y-(MESHY+1)/2)*(y-(MESHY+1)/2)) < radius*radius)
				c_old[x][y] = 2.8;
			 else
				c_old[x][y] = 0.1;
		 }
	 }
}
void update ()
{
	long x,y;
	for (y=0;y<MESHY+1;y++)
	{
		for (x=0;x<MESHX+1;x++)
		{
			c_k[x][y] = c_old[x][y];
		}
	}
}
void writetofile (FILE *fp) 
{
 long x,y;
 for (x=0;x<=(MESHX+1);x++)
 {
	 for (y=0;y<=(MESHY+1);y++)
	 {
		 fprintf(fp, "%le %le %le\n", x*deltax, y*deltay, c_old[x][y]);
	 }
	 fprintf(fp,"\n");
 }	
}
