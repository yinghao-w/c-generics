/* Calculator program for behaviour testing the stack implementations. */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "code_gen.h"
CG_INIT(int, i)

/* Create uniform stack interface */

#define CALC_PUSH i_push
#define CALC_POP i_pop
#define CALC_CREATE() i_create(2)
#define CALC_DESTROY i_destroy
#define CALC_STACK i_stack

/* Calculator */

#define NUMBER 0

char type(char *token) {
	return isdigit(token[0]) ? NUMBER : token[0];

}

int calc(char *input, CALC_STACK *stack) { 

	char *token;
	token = strtok(input, " ");
	while (token != NULL) {
		int temp1;
		int temp2;
		switch (type(token)) {
		int x;
		case NUMBER:
			CALC_PUSH(atoi(token), stack);
			break;
		case '+':
			temp1 = CALC_POP(stack) + CALC_POP(stack);
			CALC_PUSH(temp1, stack);
			break;
		case '-':
			/* subtracts top of stack from second top */
			temp1 = CALC_POP(stack);
			temp2 = CALC_POP(stack);
			temp2 -= temp1;
			CALC_PUSH(temp2, stack);
			break;
		case '*':
			temp1 = CALC_POP(stack) * CALC_POP(stack);
			CALC_PUSH(temp1, stack);
			break;
		case '/':
			temp1 = CALC_POP(stack);
			if (temp1 == 0) {
				printf("Error: division by 0\n");
				fprintf(stderr, "Error: division by 0\n");
			}
			temp2 = CALC_POP(stack);
			temp2 /= temp1;
			CALC_PUSH(temp2, stack);
			break;
		default:
			break;
		}
		token = strtok(NULL, " ");
	}
	return CALC_POP(stack);
}

int main(int argc, char *argv[]) {
	CALC_STACK *stack = CALC_CREATE();
	int result = calc(argv[1], stack);
	printf("Result: %d\n", result);
	CALC_DESTROY(stack);

	return 0;
}
