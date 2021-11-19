#include <stdio.h>
#include "queue.h"
#include "expression.h"

int main(int argc, char *args[]) {
	char *infixstr = "10-((3*4)+8)/4";
	//char *infixstr = "12 + 24*3";
	if (argc > 1)
		infixstr = args[1];

	printf("infix expression:%s\n", infixstr);
	QUEUE postfix_queue = infix_to_postfix(infixstr);

	printf("postfix expression:");
	display(postfix_queue.front);
	printf("\n");

	printf("postfix evaluation:%d\n", evaluate_postfix(postfix_queue));
	clean_queue(&postfix_queue);

	printf("prefix evaluation:%d\n", evaluate_prefix(infixstr));

	return 0;
}
