 /* this allows concrete data type elements. */

#ifndef VOID_H

#define VOID_H

struct V_Stack;
typedef struct V_Stack V_Stack;

V_Stack *v_create(int capacity, int element_size);
void v_destroy(V_Stack *stack);

int v_length(const V_Stack *stack);

void v_push(const void *value, V_Stack *stack);
void v_pop(void *value, V_Stack *stack);

#endif
