#include <stdlib.h>
#include "void.h"

struct Stack {
	int size;
	int capacity;
	void **data;
};

Stack *create(int capacity) {
	Stack *p = malloc(sizeof(*p));
	p -> capacity = capacity;
	p -> size = 0;
	p -> data = malloc(capacity * sizeof(void *));
	return p;
}

/* destroys the stack  and the objects to which its data pointed */
void destroy(Stack *stack) {
	while (stack -> size--) {
		free((stack -> data[stack -> size]));
	}
	free (stack -> data);
	free (stack);
}

int size(const Stack *stack) {
	return stack -> size;
}

static int is_full(Stack *stack) {
	return (stack->size >= stack->capacity) ? 1 : 0;
}

static void enlarge(Stack *stack) {
	stack -> data = realloc(stack -> data, sizeof(void *) * stack->capacity * 2);
	stack -> capacity *= 2;
}

void push(void *value, Stack *stack) {
	if (is_full(stack)) {
		enlarge(stack);
	}
	stack -> data[stack -> size] = value;
}

void *pop(Stack *stack) {
	if (stack -> size == 0) {
		return NULL;
	}
	return stack -> data[--(stack -> size)];
}
