/* stack implementation by code generating macros
 * uses macro INIT(TYPE, PREFIX to generate all the definitions for a
 * dynamic array structure and stack operations for the specific TYPE, label the
 * structure and operation with PREFIX */

/*
 * example stack for type 'point':
 *
 * generate all necessary code:
 *
 * INIT(point, pt)
 *
 * initialise stack:
 *
 * pt_stack *my_stack = pt_create(10);
 *
 * operations:
 *
 * point p, q;
 * pt_push(p, my_stack);
 * pt_push(q, my_stack);
 * pt r = pt_pop(my_stack);
*/

#ifndef CODE_GEN_H

#define CODE_GEN_H

#include <stdlib.h>

/* declares and defines all necessary functions for a dynamic array structure
 * specific to the given type */
#define INIT(TYPE, PREFIX)													\
	MAKE_STRUCT(TYPE, PREFIX)												\
	MAKE_CREATE(TYPE, PREFIX)												\
	MAKE_DESTROY(TYPE, PREFIX)												\
	MAKE_SIZE(TYPE, PREFIX)													\
	MAKE_PUSH(TYPE, PREFIX)													\
	MAKE_POP(TYPE, PREFIX)

#define MAKE_STRUCT(TYPE, PREFIX)											\
	struct PREFIX##_stack {													\
		int SIZE;															\
		int CAP;															\
		TYPE *DATA;															\
	};																		\
typedef struct PREFIX##_stack PREFIX##_stack;

#define MAKE_CREATE(TYPE, PREFIX)											\
	PREFIX##_stack *PREFIX##_create(int CAP) {								\
		PREFIX##_stack *p = malloc(sizeof(*p));								\
		p -> SIZE = 0;														\
		p -> CAP = CAP;														\
		p -> DATA = malloc(CAP * sizeof(TYPE));								\
		return p;															\
	}

/* If the data consists of pointers, the underlying memory to which are
 * pointed are not freed. For wide applicablity need the user to supply
 * custom destructors TODO: */
#define MAKE_DESTROY(TYPE, PREFIX)											\
	void PREFIX##_destroy(PREFIX##_stack *stack) {							\
		free (stack -> DATA);												\
		free (stack);														\
	}

#define MAKE_SIZE(TYPE, PREFIX)												\
	int PREFIX##_size(const PREFIX##_stack *stack) {						\
		return stack -> SIZE; 												\
	}

#define CG_IS_FULL(STACK)														\
	(STACK -> SIZE >= STACK -> CAP ? 1 : 0)

#define CG_ENLARGE(STACK, TYPE)												\
	STACK -> DATA = realloc(STACK->DATA, sizeof(TYPE) * STACK->CAP * 2);	\
	STACK -> CAP *= 2;

#define MAKE_PUSH(TYPE, PREFIX)												\
		void PREFIX##_push(TYPE value, PREFIX##_stack *stack) {				\
			if (IS_FULL(stack)) {											\
				ENLARGE(stack, TYPE)										\
			}																\
			stack -> DATA[stack -> SIZE++] = value;							\
		}

/* TODO: consider empty stack case */
#define MAKE_POP(TYPE, PREFIX)												\
	TYPE PREFIX##_pop(PREFIX##_stack *stack) {								\
		return stack -> DATA[--stack -> SIZE];								\
	}								

#endif
