/*
 -------------------------------------
 File:    factorial.c
 file description
 performing math with C
 -------------------------------------
 Author:  Chandler Mayberry
 Version  2021-01-18
 -------------------------------------
 */

//overflow at 13
//all variables should be int
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *args[]) {

	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	//variable init
	int n = 0, factorial = 1, previous; //is_overflow = 0;

	if (argc > 1) {
		n = atoi(args[1]); //converts the command line argument to an integer

		if (n >= 1) { //conversion is successful

			//use a loop to compute i!
			//assume prev = (i-1)!
			//then next = i! = i(i-1)! = iprev
			//if prev == next / i then next is a correct value, no overflow happens (otherwise overflow happens)

			for (int i = 1; i <= n; ++i) {
				previous = factorial;
				factorial *= i;

				if (previous != factorial / i) {
					printf("overflow:%d!\n", i);
					break;

				} else if (i == n) {
					printf("%11d", factorial);
					printf("\n%d!:%d\n", n, factorial);

				} else {
					printf("%11d", factorial);

					if (i % 4 == 0) {
						printf("\n");
					}

				}

			}

		} else {

			printf("%s:invalid argument\n", args[1]);

		}
	} else {
		printf("No Argument Given");
	}

	return 0;

}
