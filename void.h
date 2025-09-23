 /* this allows concrete data type elements. */

#ifndef VOID_H

#define VOID_H

struct V_Darray;
typedef struct V_Darray V_Darray;

V_Darray *v_create(int capacity, int element_size);
void v_destroy(V_Darray *darray);

int v_length(const V_Darray *darray);

void v_push(const void *value, V_Darray *darray);
void v_pop(void *value, V_Darray *darray);

void v_insert(const void *value, int index, V_Darray *darray);
void v_delete(void *value, int index, V_Darray *darray);

void v_get(void *value, int index, const V_Darray *darray);

#endif
