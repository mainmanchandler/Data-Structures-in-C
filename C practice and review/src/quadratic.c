/*
 -------------------------------------
 File:    quadratic.c
 file description
 performing math with C
 -------------------------------------
 Author:  Chandler Mayberry
 Version  2021-01-18
 -------------------------------------
 */

#include <stdio.h>
#include <math.h> //need this library for maths functions fabs() and sqrt()

#define EPSILON 0.000001

int main() {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	//variable init
	float a, b, c, d, x1, x2;
	int inn;
	char temp;

	do { // do-while for new input problem
//do-while loop to get correct input of three floating numbers

		do {
			printf("Please enter the coefficients a,b,c\n");
			inn = scanf("%f,%f,%f", &a, &b, &c);

			if (inn != 3) {
				printf("input:Invalid Input \n");
			} else
				break;

			do { //flush the input buffer
				scanf("%c", &temp);
				if (temp == '\n')
					break;
			} while (1);

		} while (1);

		if (fabs(a) < EPSILON && fabs(b) < EPSILON && fabs(c) < EPSILON) {
			printf("input:quit\n");
			break;
		} else if (fabs(a) < EPSILON) {
			printf("input:not a quadratic equation\n");
		} else {
			d = b * b - 4 * a * c; //compute the discriminant

			if (d > 0) { //distinct roots
				x1 = (-b + sqrt(d)) / (2 * a);
				x2 = (-b - sqrt(d)) / (2 * a);
				printf("The equation has two distinct real roots\n");
				printf("x1:%f\n", x1);
				printf("x2:%f\n", x2);

			} else if (d < 0) { //complex roots
				x1 = -b / (2 * a);  //real #
				x2 = sqrt(fabs(d)) / (2 * a);   //imaginary #
				printf("The equation has two complex roots\n");
				printf("real:%f\n", x1);
				printf("imaginary:%f\n", x2);

			} else { //equal roots
				x1 = -b / (2 * a);
				printf("The equation has two equal real roots\n");
				printf("x:%f\n", x1);
			}

		}

	} while (1);

	return 0;
}

