/*
 -------------------------------------
 File:    expression_symbol.c
 file description
 -------------------------------------
 Author:  Chandler Mayberry
 Version  2021-03-31
 -------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "queue.h"
#include "stack.h"
#include "expression_symbol.h"

/* aux function to find the type of symbol of char c*/
int type_of_symbol(char c) {
	if (c >= '0' && c <= '9')
		return 0;
	else if (c == '/' || c == '*' || c == '%' || c == '+' || c == '-')
		return 1;
	else if (c == '(')
		return 2;
	else if (c == ')')
		return 3;
	else
		return 4;
}

/*
 * convert infix expression string to postfix expression queue,
 * getting symbol values from the hash table
 */
QUEUE infix_to_postfix_symbol(char *infixstr, HASHTABLE *ht) {
	//need to create a queue to store the result, FIFO
	QUEUE rq = { 0 };

	//need to create a queue to store the variables, LIFO
	STACK st = { 0 };

	//need to grab one character
	char *curr = infixstr;

	int negative = 1; //for negative numbers
	int n = 0; //curr char n

	while (*curr) {

		if (*curr == '-' && (curr == infixstr || *(curr - 1) == '('))
			negative = -1;

		else if (*curr <= '9' && *curr >= '0') {
			n = *curr - '0'; //horners alg int to char

			//while loop accounts for numbers 10>
			while (*(curr + 1) <= '9' && *(curr + 1) >= '0') {
				n = n * 10 + (*(curr + 1) - '0');
				curr++;
			}

			enqueue(&rq, new_node(negative * n, 0)); //add the variable to the queue
			negative = 1; //resets the negative operator after negative is added

		} else if (*curr == '(') {
			push(&st, new_node(*curr, 2)); //declare type and store Lbracket for operation

		} else if (*curr == ')') {

			//operation must be queued between the brackets
			int found = 0;
			while (found == 0) {
				NODE *operation = pop(&st);
				if (operation->data != '(')
					enqueue(&rq, operation);
				else
					found = 1; //found (operation could not be performed in the loop, so break time

			}

		} else if (type_of_symbol(*curr) == 1) { //curr is operator
			push(&st, new_node(*curr, 1)); //store the operator for operation

			//This is what we need to implement for this assignment:
			//searches for the character, if the curr is a character in the hash table to perform algebra later
		} else if ((*curr >= 'a' && *curr <= 'z') || (*curr >= 'A' && *curr <= 'Z')) { //if value is a letter, check hash table
			char character[] = { *curr, '\0' };
			HTNODE *snode = search(ht, character); //search to see if value exists
			if (snode != NULL)
				enqueue(&rq, new_node(snode->value, 0)); //if it does add node to queue of the table determined value
		}

		curr++; //next character
	}

	// pop each node and insert it to queue
	while (st.top)
		enqueue(&rq, pop(&st));

	clean_stack(&st);
	return rq;
}

/*
 * evaluate symbolic infix expression,
 * call queue = infix_to_postfix_symbol(char *infixstr, HASHTABLE *ht);
 * then call evaluate_postfix(QUEUE queue);
 */
int evaluate_infix_symbol(char *infixstr, HASHTABLE *ht) {

	if ((*infixstr >= '0' && *infixstr <= '9') && *(infixstr + 1))
		return (*infixstr - '0');

	//perform the algebra
	else
		return evaluate_postfix(infix_to_postfix_symbol(infixstr, ht));
}

// same code as the previous assignment
int evaluate_postfix(QUEUE queue) {
	//grab the first character in the queue
	NODE *curr = queue.front;

	STACK st = { 0 }; //holder stack for evaluation

	int type = 0;

	//go through the postfix expression
	while (curr) {

		type = curr->type;
		char operator = curr->data;
		if (type == 0) {
			push(&st, new_node(curr->data, 0));
		} else if (type == 1) { //curr is operator
			int operand2 = pop(&st)->data; //second operand
			int operand1 = pop(&st)->data; //first operand

			int temp = 0; //operation value

			//perform operation
			if (operator == '/')
				temp = operand1 / operand2;
			else if (operator == '*')
				temp = operand1 * operand2;
			else if (operator == '%')
				temp = operand1 % operand2;
			else if (operator == '+')
				temp = operand1 + operand2;
			else if (operator == '-')
				temp = operand1 - operand2;

			//store for next operation
			push(&st, new_node(temp, 0));
		}

		curr = curr->next; //next node

	}

	//the result should be the last item on the stack
	int result = st.top->data;
	clean_stack(&st);
	return result;
}

/*
 * parse statement symbol=expression, to get left-side symbol string, and
 * evaluate the right side expression using evaluate_infix_symbol(char *infixstr, HASHTABLE *ht);
 * insert the symbol and its value into hash table
 */
// you can use this function in your program
int resolve_symbol(char *statement, HASHTABLE *ht) {
	char name[10] = { 0 };
	char *dest = strstr(statement, "=");
	if (dest)
		*dest = '\0';
	else
		dest = statement;
	strcpy(name, statement);

	if ((name[0] >= 'a' && name[0] <= 'z') || (name[0] >= 'A' && name[0] <= 'Z')) {

		int value = evaluate_infix_symbol(dest + 1, ht);

		if (value == 99999)  // escape value
			return 2;
		else {
			insert(ht, new_hashnode(name, value));
		}
		return 1;
	}
	return 0;
}

