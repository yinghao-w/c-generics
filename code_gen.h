/* stack implementation by code generating macros
 * uses macro CG_INIT(TYPE, PREFIX to generate all the definitions for a
 * dynamic array structure and stack operations for the specific TYPE, label the
 * structure and operation with PREFIX */

/*
 * example stack for type 'point':
 *
 * generate all necessary code:
 *
 * CG_INIT(point, pt)
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
#define CG_INIT(TYPE, PREFIX)												\
	MAKE_STRUCT(TYPE, PREFIX)												\
	MAKE_CREATE(TYPE, PREFIX)												\
	MAKE_DESTROY(TYPE, PREFIX)												\
	MAKE_LENGTH(TYPE, PREFIX)												\
	MAKE_PUSH(TYPE, PREFIX)													\
	MAKE_POP(TYPE, PREFIX)

#define MAKE_STRUCT(TYPE, PREFIX)											\
	struct PREFIX##_stack {													\
		int LENGTH;															\
		int CAPACITY;														\
		TYPE *DATA;															\
	};																		\
typedef struct PREFIX##_stack PREFIX##_stack;

#define MAKE_CREATE(TYPE, PREFIX)											\
	PREFIX##_stack *PREFIX##_create(int CAPACITY) {							\
		PREFIX##_stack *p = malloc(sizeof(*p));								\
		p -> LENGTH = 0;													\
		p -> CAPACITY = CAPACITY;											\
		p -> DATA = malloc(CAPACITY * sizeof(TYPE));						\
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

#define MAKE_LENGTH(TYPE, PREFIX)											\
	int PREFIX##_size(const PREFIX##_stack *stack) {						\
		return stack -> LENGTH; 											\
	}

#define CG_IS_FULL(STACK)													\
	(STACK -> LENGTH >= STACK -> CAPACITY ? 1 : 0)

#define CG_ENLARGE(STACK, TYPE)												\
	STACK -> DATA = realloc(STACK->DATA, sizeof(TYPE)*STACK->CAPACITY*2);	\
	STACK -> CAPACITY *= 2;

#define MAKE_PUSH(TYPE, PREFIX)												\
		void PREFIX##_push(TYPE value, PREFIX##_stack *stack) {				\
			if (CG_IS_FULL(stack)) {										\
				CG_ENLARGE(stack, TYPE)										\
			}																\
			stack -> DATA[stack -> LENGTH++] = value;						\
		}

/* If the stack is empty, return the empty initialisation of the given
 * type */
#define MAKE_POP(TYPE, PREFIX)												\
	TYPE PREFIX##_pop(PREFIX##_stack *stack) {								\
		if (stack -> LENGTH == 0) {											\
			return (TYPE) {};												\
		}																	\
		return stack -> DATA[--stack -> LENGTH];							\
	}								

#endif
