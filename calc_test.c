/* Calculator program for behaviour testing the stack implementations. */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "code_gen.h"
#include "fat_pointer.h"

/* Calculator */

#define NUMBER 0

char type(char *token) {

	return isdigit(token[0]) ? NUMBER : token[0];

}

/* Macro to generate calc function for each stack implementation */
#define MAKE_CALC(CALC_CREATE, CALC_PUSH, CALC_POP, CALC_DESTROY, PREFIX)	\
		int PREFIX##_calc(const char *input) {								\
																			\
			/* Note: strtok modifies its input_copy, so to call calc on
			 * argv[1] multiple times, a copy of argv[1] should be passed */\
			int input_length = strlen(input);								\
			char input_copy[input_length];									\
			strncpy(input_copy, input, input_length);						\
																			\
			CALC_CREATE														\
			char *token;													\
			token = strtok(input_copy, " ");								\
																			\
			while (token != NULL) {											\
				int temp1;													\
				int temp2;													\
				switch (type(token)) {										\
				int x;														\
				case NUMBER:												\
					CALC_PUSH(atoi(token), stack);							\
					break;													\
				case '+':													\
					temp1 = CALC_POP(stack) + CALC_POP(stack);				\
					CALC_PUSH(temp1, stack);								\
					break;													\
				case '-':													\
					/* subtracts top of stack from second top */			\
					temp1 = CALC_POP(stack);								\
					temp2 = CALC_POP(stack);								\
					temp2 -= temp1;											\
					CALC_PUSH(temp2, stack);								\
					break;													\
				case '*':													\
					temp1 = CALC_POP(stack) * CALC_POP(stack);				\
					CALC_PUSH(temp1, stack);								\
					break;													\
				case '/':													\
					temp1 = CALC_POP(stack);								\
					if (temp1 == 0) {										\
						printf("Error: division by 0\n");					\
						fprintf(stderr, "Error: division by 0\n");			\
					}														\
					temp2 = CALC_POP(stack);								\
					temp2 /= temp1;											\
					CALC_PUSH(temp2, stack);								\
					break;													\
				default:													\
					break;													\
				}															\
				token = strtok(NULL, " ");									\
			}																\
			int result = CALC_POP(stack);									\
			CALC_DESTROY(stack);											\
			return result;													\
		}

/* Generate calc functions */

CG_INIT(int, i)
#define CALC_CREATE i_stack *stack = i_create(2);
MAKE_CALC(CALC_CREATE, i_push, i_pop, i_destroy, cg)
#undef CALC_CREATE

#define CALC_CREATE int *stack = NULL;
MAKE_CALC(CALC_CREATE, fp_push, fp_pop, fp_destroy, fp)
#undef CALC_CREATE

void calc_test(void) {

	char s[] = "1 2 + 3 4 * 5 6 - * +";
	
	int cg_result = cg_calc(s);
	int fp_result = fp_calc(s);

	assert(fp_result == cg_result);
	assert(fp_result == -9);

	printf("Results:\nCG: %d\nFP: %d\n", cg_result, fp_result);

	char r[] = "+";

	cg_result = cg_calc(r);
	fp_result = fp_calc(r);

	assert(fp_result == cg_result);
	assert(fp_result == 0);

	printf("Results:\nCG: %d\nFP: %d\n", cg_result, fp_result);
}
