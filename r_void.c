#include <stdlib.h>
#include <string.h>
#include "r_void.h"

struct V_Stack {
	int length;
	int capacity;
	int element_size;
	char *data;
};

V_Stack *v_create(int capacity, int element_size) {
	V_Stack *p = malloc(sizeof(*p));
	p -> capacity = capacity;
	p -> length = 0;
	p -> element_size = element_size;
	p -> data = malloc(capacity * element_size);
	return p;
}

/* destroys the stack  and the objects to which its data pointed */
void v_destroy(V_Stack *stack) {
	free (stack -> data);
	free (stack);
}

int v_length(const V_Stack *stack) {
	return stack -> length;
}

static int v_is_full(V_Stack *stack) {
	return (stack->length >= stack->capacity) ? 1 : 0;
}

static void v_enlarge(V_Stack *stack) {
	stack -> data = realloc(stack -> data, 2 * stack->capacity * stack->element_size);
	stack -> capacity *= 2;
}


void v_push(const void *value, V_Stack *stack) {
	if (v_is_full(stack)) {
		v_enlarge(stack);
	}
	memcpy(stack->data + stack->element_size * stack->length, value, stack->element_size);
	stack->length++;
}

void v_pop(void *value, V_Stack *stack) {
	if (stack->length == 0) {
		memset(value, 0, stack->element_size);
	} else {
		memcpy(value, stack->data + stack->element_size * (stack->length - 1), stack->element_size);
		stack->length--;
	}
}
