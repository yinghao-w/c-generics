/* Generic dynamic array implementation with the 'fat pointer' or 'stretchy
 * buffer' method. The data is stored in a regular array owned by the handle
 * pointer, while the metadata of size and capacity is stored in the memory
 * location behind the pointer.
 *
 * Use:
 *
 * 		#include "fat_pointer.h"
 *
 * Initialise:
 *
 * 		int *darray = NULL;
 */

#ifndef FAT_POINTER_H

#define FAT_POINTER_H

#include <stdlib.h>
#include <string.h>

typedef struct {
  size_t length;
  size_t capacity;
} fp_header;

#define FP_HEADER(darray) ((fp_header *)darray - 1)

#define FP_LENGTH(darray) (FP_HEADER(darray)->length)

#define FP_CAPACITY(darray) (FP_HEADER(darray)->capacity)

#define FP_IS_FULL(darray) (FP_LENGTH(darray) >= FP_CAPACITY(darray) ? 1 : 0)

static void *fp_resize(void *darray, size_t element_size) {
  fp_header *p;
  if (darray) {
    p = realloc(FP_HEADER(darray),
                2 * FP_CAPACITY(darray) * element_size + sizeof(fp_header));
    p->capacity *= 2;
  } else {
    p = malloc(element_size + sizeof(fp_header));
    p->length = 0;
    p->capacity = 1;
  }
  return ++p;
}

#define FP_RESIZE(darray) (darray = fp_resize(darray, sizeof(*darray)))

#define fp_destroy(darray) (darray ? free(FP_HEADER(darray)) : 0)

#define fp_length(darray) (darray ? FP_LENGTH(darray) : 0)

#define fp_push(value, darray)                                                 \
  (!darray || FP_IS_FULL(darray) ? FP_RESIZE(darray) : 0,                      \
   darray[FP_LENGTH(darray)++] = value)

#define fp_pop(darray) (darray[--FP_LENGTH(darray)])

#define fp_insert(value, index, darray)                                        \
  (!darray || FP_IS_FULL(darray) ? FP_RESIZE(darray) : 0,                      \
   memmove(darray + index + 1, darray + index,                                 \
           sizeof(*darray) * (FP_LENGTH(darray) - index)),                     \
   FP_LENGTH(darray)++, darray[index] = value)

#define fp_delete(index, darray)                                               \
  (memmove(darray + index, darray + index + 1,                                 \
           sizeof(*darray) * (FP_LENGTH(darray) - index - 1)),                 \
   --FP_LENGTH(darray))

#endif
