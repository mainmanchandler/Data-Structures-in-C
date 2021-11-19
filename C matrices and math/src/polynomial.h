/*
 -------------------------------------
 File:    polynomial.h
 file description
 Methods for the polynomial_main, horners algorithm,
 -------------------------------------
 Author:  Chandler Mayberry
 Version  2021-01-28
 -------------------------------------
 */

#ifndef POLYNOMIAL_H_
#define POLYNOMIAL_H_
#include<stdio.h>
#include<math.h>

#define EPSILON 1e-6

//prints the polynomial in format like p[0]*x^{n-1} +  p[1]*x^{n-2} +...+ p[n-2]*x^1 + p[n-1]*x^0 with 2
//digits after the point, e.g., 1.00*10.00^3+2.00*10.00^2+3.00*10.00^1+4.00*10.00^0
void display_polynomial(float p[], int n, float x) {

	for (int i; i < n; i++) {
		if (i < n - 1) {
			printf("%.2f*%.2f^%d+", p[i], x, n - (i + 1));
		} else {
			printf("%.2f*%.2f^%d", p[i], x, n - (i + 1));
		}
	}

	return;
}

//computes and returns the value of the following polynomial P(x) of order n and coefficients p[0], …, p[n-1].
//P(x) = p[0] * xn − 1 + p[1] * xn − 2 + ... + p[n − 2] * x1 + p[n − 1] * x0
float horner(float p[], int n, float x) {

	float poly_value = 0;

	for (int i = 0; i < n; i++) {
		poly_value = poly_value * x + p[i];
	}

	if (poly_value > -0.00000382 && poly_value < 1e-6) { // to stop the -0.00 output, without the result is -0.0000038147
		poly_value = 0;
	}

	return poly_value;

}

//finds an approximate real root c in interval [a, b] of polynomial P(x), using the bisection
//method (supplementary link). Use the fault tolerant 1e-6 (or 0.000001) as a stop condition,
//i.e., if x0 is the actual root, stop the iteration if |c-x0|<1e-6 or |P(c)| < 1e-6.
float bisection(float p[], int n, float a, float b) {
	//trying to find the root at 0
	//or at the tolerance of epislon (within 0.000001 of 0)
	float root = 0; //the value that we are trying to find
	float c = a;

	while (root == 0) {
		c = (a + b) / 2; //finding the midpoint of the bisection formula

		if ((c - a) < 1e-6 && fabs(horner(p, b, c)) < 1e-6) { //is the midpoint at zero or close
			root = c;
		} else if (horner(p, n, c) * horner(p, n, a) < 0) { //swaps the a and b coordinates to approach the root
			b = c;
		} else {
			a = c;
		}

	}

	return root;
}

#endif /* POLYNOMIAL_H_ */

