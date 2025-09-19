/* stack implementation with the 'fat pointer' or 'stretchy buffer' method
 *
 * the data is stored in a regular array owned by the handle pointer, while the
 * metadata of size and capacity is stored in the memory location behind the
 * pointer */

#ifndef FAT_POINTER_H

#define FAT_POINTER_H

#include <stdlib.h>

struct fp_header {
	int length;
	int capacity;

};
typedef struct fp_header fp_header;

#define fp_destroy(stack) (													\
		free (FP_HEADER(stack))												\
		)

#define FP_HEADER(stack) (														\
		(fp_header *)stack - 1													\
		)

#define FP_IS_FULL(stack) (													\
		(FP_HEADER(stack)->length >= FP_HEADER(stack)->capacity) ? (1) : (0)		\
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

void *fp_enlarge(void *stack, int element_size) {
	int length = FP_HEADER(stack) -> length;
	int capacity = FP_HEADER(stack) -> capacity;
	void *p = realloc(FP_HEADER(stack), 2 * capacity * element_size + sizeof(fp_header));
	((fp_header *)p) -> length = length;
	((fp_header *)p) -> capacity = 2 * capacity;
	p = (char *)p + sizeof(fp_header);
	return p;
}

void *fp_init(void *stack, int element_size) {
	void *p = malloc(element_size + sizeof(fp_header));
	((fp_header *)p) -> length = 0;
	((fp_header *)p) -> capacity = 1;
	p = (char *)p + sizeof(fp_header);
	return p;
}

#define FP_INIT(stack)	(													\
		stack = fp_init(stack, sizeof(*stack))								\
		)

#define FP_ENLARGE(stack) (													\
		stack = fp_enlarge(stack, sizeof(*stack))							\
		)

/* TODO: consider empty stack case */
#define fp_pop(stack) (														\
		stack[--FP_HEADER(stack) -> length]										

#endif
