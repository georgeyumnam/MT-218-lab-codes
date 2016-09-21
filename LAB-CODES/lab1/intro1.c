#include<stdio.h> // standard input output library
#include<stdlib.h> // standard library

void main () {  // void is the return type of the function - void returns nothing
                // there can be one main - any function named 'main' is compiled first by the compiler.
//	int i, j ; // initialization as integer variables // Use double type to convert the variable tye to float
	double i, j;
	i = 15; //Assignment of values to integers
	j = 10;
	double sum, diff, quote, rem ;
	sum = i + j ;
	diff = i - j ;
	quote = i/j ;
//	rem = i%j ;

	printf("The sum is	 %le\n", sum);
        printf("The difference is %le\n", diff);
        printf("The quotient is %le\n", quote);  // Use %d for integers
//        printf("The remainder is %d\n", rem);   // Use %le for floats-double
						// Remainder dont work in double

}
