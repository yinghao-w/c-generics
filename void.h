/* this allows concrete data type elements. */
/* Generic dynamic array implementation with void pointers. No type safety, but
 * a unified interface for all element types.
 *
 * Use:
 *
 * 		#include "void.h"
 *
 * Create a array for a type:
 *
 * 		V_Darray *a = v_create(8, sizeof(int));
 *
 * Push and insert elements:
 *
 *		int i = 5;
 *		v_push(&i, a);
 *		v_push(&i, a);
 *		v_insert(&i, 1, a);
 *
 * To pop or retrieve elements, supply a variable as destination for the value:
 *
 * 		int j;
 * 		v_get(&j, 2, a);
 * 		v_pop(&j, a);
 *
 * Pass NULL if the value is not needed. Element deletion also allows a optional
 * "return" value in the same way:
 *
 * 		v_delete(&j, 0, a);
 * 		v_delete(NULL, 1, a);
 *
 * The deleted value is copied into j in the first instance, and simply just
 * deleted in the second.
 */

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
