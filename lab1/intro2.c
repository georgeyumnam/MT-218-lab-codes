// To write a loop 
#include<stdio.h> // standard input output library
#include<stdlib.h> // standard library

void main () {  // void is the return type of the function - void returns nothing
                // there can be one main - any function named 'main' is compiled first by the compiler.
//	int i, j ; // initialization as integer variables // Use double type to convert the variable tye to float
	double i, j;
	int k;
	i = 15; //Assignment of values to integers
	j = 10;
	double sum, diff, quote, rem ;
	sum = i + j ;
	diff = i - j ;
	quote = i/j ;
//	rem = i%j ;

//	for (k=0;k<1000; k++){   // Using for loops
//		if ((k%2) == 0) {   // gives the condition to the loop	
//		printf("k=%d\n", k);
//		}
//	}
	k=0;
	while (k<1000) { // Using while loops
	if (!(k%2))	{
	printf("k=%d\n", k);
	}
	k++;
	}
	k=0;
	do {
	if (!(k%2)) {
	 printf("k=%d\n", k);
	}
	else {
	printf("k=%d\n", (k+1)/2);
	}
	k++;
	} while (k<1000);

}
