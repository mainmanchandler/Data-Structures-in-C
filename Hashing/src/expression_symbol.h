/*
-------------------------------------
File:    expression_symbol.h
file description
-------------------------------------
Author:  Chandler Mayberry
Version  2021-03-31
-------------------------------------
 */

#ifndef EXPRESSION_SYMBOL_H_
#define EXPRESSION_SYMBOL_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"
#include "queue.h"
#include "stack.h"
#include "hash.h"

/* 
 * convert infix expression string to postfix expression queue, 
 * getting symbol values from the hash table
*/
QUEUE infix_to_postfix_symbol(char *infixstr, HASHTABLE *ht);

/*
 * evaluate symbolic infix expression, 
 * call queue = infix_to_postfix_symbol(char *infixstr, HASHTABLE *ht); 
 * then call evaluate_postfix(QUEUE queue);
*/ 
int evaluate_infix_symbol(char *infixstr, HASHTABLE *ht);

// A6Q3
int evaluate_postfix(QUEUE queue);

// provided for your reference
int resolve_symbol(char* statement, HASHTABLE *ht);


#endif /* EXPRESSION_SYMBOL_H_ */
