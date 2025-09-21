/* Stack implementation with the 'fat pointer' or 'stretchy buffer' method
 *
 * The data is stored in a regular array owned by the handle pointer, while the
 * metadata of size and capacity is stored in the memory location behind the
 * pointer.
 *
 * Usage:
 * int *stack = NULL;
 * fp_push(1, stack);
 * fp_push(2, stack);
 * fp_pop(stack);		<- returns 2
 * fp_destroy(stack);
 */

#ifndef FAT_POINTER_H

#define FAT_POINTER_H

#include <stdlib.h>
#include <string.h>

struct fp_header {
	int length;
	int capacity;

};
typedef struct fp_header fp_header;

#define fp_destroy(stack) (													\
		free (FP_HEADER(stack))												\
		)

#define FP_HEADER(stack) (													\
		(fp_header *)stack - 1												\
		)

#define FP_IS_FULL(stack) (													\
		(FP_HEADER(stack)->length >= FP_HEADER(stack)->capacity) ? (1) : (0)\
		)

#define fp_push(value, stack) (												\
		((stack == NULL) ?													\
				(FP_INIT(stack)) :											\
				((FP_IS_FULL(stack)) ?										\
						(FP_ENLARGE(stack)) :								\
						(0)													\
				)															\
		),																	\
		stack[FP_HEADER(stack) -> length++] = value							\
		)

static void *fp_enlarge(void *stack, int element_size) {
	int length = FP_HEADER(stack) -> length;
	int capacity = FP_HEADER(stack) -> capacity;
	void *p = realloc(FP_HEADER(stack), 2 * capacity * element_size + sizeof(fp_header));
	((fp_header *)p) -> length = length;
	((fp_header *)p) -> capacity = 2 * capacity;
	p = (char *)p + sizeof(fp_header);
	return p;
}

static void *fp_init(int element_size) {
	void *p = malloc(element_size + sizeof(fp_header));
	((fp_header *)p) -> length = 0;
	((fp_header *)p) -> capacity = 1;
	p = (char *)p + sizeof(fp_header);
	return p;
}

#define FP_INIT(stack)	(													\
		stack = fp_init(sizeof(*stack))										\
		)

#define FP_ENLARGE(stack) (													\
		stack = fp_enlarge(stack, sizeof(*stack))							\
		)

/* Initialises the stack as empty if required. If the stack is empty, zeroes
 * the first element of the array and evaluates it. */
#define fp_pop(stack) (														\
		((stack == NULL) ?													\
				FP_INIT(stack) : (0)										\
		),																	\
		((FP_HEADER(stack) -> length == 0) ?								\
				(memset(stack, 0, sizeof(*stack)), stack[0]) :				\
				(stack[--(FP_HEADER(stack) -> length)])						\
		)																	\
		)

#endif
