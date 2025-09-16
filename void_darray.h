/* Dynamic array implementation with void pointers
 * values are not stored contiguously, poor performance
 * array elements are pointers*/

#ifndef VOID_DARRAY_H

#define VOID_DARRAY_H

struct Darray;
typedef struct Darray Darray;

/* destroy all destroys the objects to which are pointed by data */
Darray *create(int capacity);
void destroy(Darray *darray);

int size(const Darray *darray);
int is_in(void *value, const Darray *darray);

void *get(int index, const Darray *darray);

void insert(void *value, int index, Darray *darray);
void append(void *value, Darray *darray);
void omit(int index, Darray *darray);

#endif
