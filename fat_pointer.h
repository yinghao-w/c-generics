/* stack implementation with the 'fat pointer' or 'stretchy buffer' method
 *
 * the data is stored in a regular array owned by the handle pointer, while the
 * metadata of size and capacity is stored in the memory location behind the
 * pointer */

#ifndef FAT_POINTER_H

#define FAT_POINTER_H

#include <stdlib.h>

struct header {
	int length;
	int capacity;

};
typedef struct header header;

#define destroy(stack) (													\
		free (HEADER(stack))												\
		)

#define HEADER(stack) (														\
		(header *)stack - 1													\
		)

#define FP_IS_FULL(stack) (													\
		(HEADER(stack)->length >= HEADER(stack)->capacity) ? (1) : (0)		\
		)

#define push(value, stack) (												\
		((stack == NULL) ?													\
				(FP_INIT(stack)) :											\
				((FP_IS_FULL(stack)) ?										\
						(FP_ENLARGE(stack)) :								\
						(0)													\
				)															\
		),																	\
		stack[HEADER(stack) -> length++] = value							\
		)

void *fp_enlarge(void *stack, int element_size) {
	int length = HEADER(stack) -> length;
	int capacity = HEADER(stack) -> capacity;
	void *p = realloc(HEADER(stack), 2 * capacity * element_size + sizeof(header));
	((header *)p) -> length = length;
	((header *)p) -> capacity = 2 * capacity;
	p = (char *)p + sizeof(header);
	return p;
}

void *fp_init(void *stack, int element_size) {
	void *p = malloc(element_size + sizeof(header));
	((header *)p) -> length = 0;
	((header *)p) -> capacity = 1;
	p = (char *)p + sizeof(header);
	return p;
}

#define FP_INIT(stack)	(													\
		stack = fp_init(stack, sizeof(*stack))								\
		)

#define FP_ENLARGE(stack) (													\
		stack = fp_enlarge(stack, sizeof(*stack))							\
		)

<<<<<<< HEAD
#define pop(stack) (														\
	stack[--HEADER(stack) -> length]										\
=======
/* TODO: consider empty stack case */
#define fp_pop(stack) (														\
	stack[--FP_HEADER(stack) -> length]										\
>>>>>>> 1bcb8bf (Add TODO comment)
		)

#endif
