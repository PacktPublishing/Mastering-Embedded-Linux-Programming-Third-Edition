#include <stdio.h>
#include <stdlib.h>
#include <testlib.h>

int main (int argc, char *argv[])
{
	int n1 = 4;
	int n2 = 5;

	printf("Hello from ARM\n");
	printf("%d + %d = %d\n", n1, n2, add_ints(n1, n2)); 
	printf("%d * %d = %d\n", n1, n2, multiply_ints(n1, n2)); 
	return 0;
}

