/* stack implementation with void pointers
 * values are not stored contiguously, poor performance
 * stack elements are pointers*/

#ifndef VOID_DARRAY_H

#define VOID_DARRAY_H

struct Stack;
typedef struct Stack Stack;

/* destroy all destroys the objects to which are pointed by data */
Stack *create(int capacity);
void destroy(Stack *stack);

int size(const Stack *stack);

void push(void *value, Stack *stack);
void *pop(Stack *stack);

#endif
