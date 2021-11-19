/*
 -------------------------------------
 File:    bigint.c
 file description
 Bigint methods, storing a huge integer in C
 -------------------------------------
 Author:  Chandler Mayberry
 Version  2021-02-15
 -------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bigint.h"
#include "dllist.h"

BIGINT bigint(char *p) {
	BIGINT bn = { 0 };
	if (p == NULL)
		return bn;
	else if (!(*p >= '0' && *p <= '9')) { // not begin with digits
		return bn;
	} else if (*p == '0' && *(p + 1) == '\0') { // just "0"
		insert_end(&bn.start, &bn.end, new_node(*p - '0'));
		return bn;
	} else {
		while (*p) {
			if (*p >= '0' && *p <= '9') {
				insert_end(&bn.start, &bn.end, new_node(*p - '0'));
			} else {
				clean_bigint(&bn);
				break;
			}
			p++;
		}
		return bn;
	}
}

void display_bigint(BIGINT bignumber) {
	NODE *ptr = bignumber.start;
	while (ptr != NULL) {
		printf("%d", ptr->value);
		ptr = ptr->next;
	}
}

void clean_bigint(BIGINT *bignumberp) {
	clean(&bignumberp->start, &bignumberp->end);
}

/**
 * inserts new node at the front of the list
 * @param op1 the first large char integer
 * @param op2 the second large char integer
 * @return sum, the bigint sum, calculated with simple addition logic
 */
BIGINT add(BIGINT op1, BIGINT op2) {
	BIGINT sum = bigint(NULL);

	//as long as those numbers exist to use
	if (op1.start != NULL && op2.start != NULL) {

		int small_sum = 0; //this gets re-written every iteration through the loop
		int carry_value = 0; //carry value during simple addition, if >=10 then carry_value = 1

		NODE *num1 = op1.end;
		NODE *num2 = op2.end;

		//run as long as one number isnt finished its addition
		while (num1 != NULL || num2 != NULL) {

			small_sum = carry_value + (num1 != NULL ? num1->value : 0) + (num2 != NULL ? num2->value : 0);

			carry_value = small_sum;
			//account for the carry value, leave the remainder
			if (carry_value >= 10) {
				carry_value = 1;
				small_sum = small_sum - 10;
			} else {
				carry_value = 0;
			}

			//add the small_sum value to the start of the sum bigint list
			insert_start(&sum.start, &sum.end, new_node(small_sum));

			//we are moving from right to left, like we would in binary addition
			if (num1 != NULL)
				num1 = num1->prev;
			if (num2 != NULL)
				num2 = num2->prev;

		}

		//carry_value at the end might get forgotten, here, we dont leave homies behind
		if (carry_value > 0)
			insert_start(&sum.start, &sum.end, new_node(carry_value));

	}

	//we want the sum 10000000000000000000
	return sum;

}

BIGINT Fibonacci(int n) {
	if (n <= 2) {
		return bigint("1");
	} else {
		BIGINT temp = bigint(NULL); //the prev previous number
		BIGINT fib_1 = bigint("1"); //the previous number
		BIGINT fib_2 = bigint("1"); //running total

		//add all of the numbers in a running total to 100
		for (int i = 3; i <= n; i++) {
			temp = fib_2;
			fib_2 = add(fib_1, fib_2); //perform fibonacci addition sequence
			fib_1 = temp;
		}

		//the default output should be 354224848179261915075
		return fib_2;
	}
}

