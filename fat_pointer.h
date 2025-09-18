/* stack implementation with the 'fat pointer' or 'stretchy buffer' method
 *
 * the data is stored in a regular array owned by the handle pointer, while the
 * metadata of size and capacity is stored in the memory location behind the
 * pointer */

#ifndef FAT_POINTER_H
#define FAT_POINTER_H

#include <bits/types/stack_t.h>
#include <complex.h>
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

#define IS_FULL(stack) (													\
		(HEADER(stack)->length >= HEADER(stack)->capacity) ? 1 : 0			\
		)

#define push(value, stack) (												\
		((stack == NULL) ?													\
				(stack = init(stack)) :										\
				((IS_FULL(stack)) ?											\
						(stack = resize(stack)) :							\
						(0)													\
				)															\
		),																	\
		stack[HEADER(stack) -> length++] = value							\
		)

void *resize(void *stack) {
	int length = HEADER(stack) -> length;
	int capacity = HEADER(stack) -> capacity;
	void *p = realloc(stack, 2* capacity + sizeof(header));
	HEADER(p) -> length = length;
	HEADER(p) -> capacity = 2 * capacity;
	p = (char *)p + sizeof(header);
	return p;
}
void *init(void *stack) {
	 void *p = malloc(1 + sizeof(header));
	 HEADER(p) -> length = 0;
	 HEADER(p) -> capacity = 1;
	 p = (char *)p + sizeof(header);
	 return p;

}

#define pop(stack) (														\
	HEADER(stack) -> length--,												\
	stack[HEADER(stack) -> length]											\
		)
	
#endif
