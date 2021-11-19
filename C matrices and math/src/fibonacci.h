/*
 -------------------------------------
 File:    fibonacci.h
 file description
 calculates the fibonacci  series
 -------------------------------------
 Author:  Chandler Mayberry
 Version  2021-01-26
 -------------------------------------
 */

#ifndef FIBONACCI_H_
#define FIBONACCI_H_

extern int *la; //global pointer variable to get local variable address

int recursive_fibonacci(int n) {

	if (&n < la)
		la = &n;

	int value; //the resulting fib number

	if (n == 0) {
		value = 0;
	} else if (n < 2) {
		value = 1;
	} else {
		value = recursive_fibonacci(n - 1) + recursive_fibonacci(n - 2);
	}

	return value;
}

int iterative_fibonacci(int n) {

	if (&n < la)
		la = &n;

	int fib1 = 1, fib2 = 1, i = 1, temp;

	for (; i < n; i++) {
		temp = fib1;
		fib1 = fib1 + fib2;
		fib2 = temp;
	}

	return fib2;
}

#endif /* FIBONACCI_H_ */
