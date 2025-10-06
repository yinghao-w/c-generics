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

/* TODO: use size_t to ensure alignment. Tests haven't been able to find any odd
 * behaviour with strict alignment long doubles, but to be safe. */
struct fp_header {
  int length;
  int capacity;
};
typedef struct fp_header fp_header;

#define fp_destroy(darray) ((darray == NULL) ? 0 : (free(FP_HEADER(darray)), 0))

#define FP_HEADER(darray) ((fp_header *)darray - 1)

/* TODO: Use this macro elsewhere in this file */
#define fp_length(darray) ((darray == NULL) ? (0) : (FP_HEADER(darray)->length))

#define FP_LENGTH(darray) (FP_HEADER(darray)->length)
#define FP_CAPACITY(darray) (FP_HEADER(darray)->capacity)

#define FP_IS_FULL(darray)                                                     \
  ((FP_HEADER(darray)->length >= FP_HEADER(darray)->capacity) ? (1) : (0))

static void *fp_resize(void *darray, int element_size) {
  if (darray) {
    fp_header *p = realloc(FP_HEADER(darray),
                           2 * FP_HEADER(darray)->capacity * element_size +
                               sizeof(fp_header));
    p->capacity *= 2;
    return ++p;
  } else {
    fp_header *p = malloc(element_size + sizeof(fp_header));
    p->length = 0;
    p->capacity = 1;
    return ++p;
  }
}

#define FP_RESIZE(darray) (darray = fp_resize(darray, sizeof(*darray)))

#define fp_push(value, darray)                                                 \
  (!darray || FP_IS_FULL(darray) ? FP_RESIZE(darray) : 0,                      \
   darray[FP_HEADER(darray)->length++] = value)

#define fp_pop(darray) (darray[--(FP_HEADER(darray)->length)])

#define fp_insert(value, index, darray)                                        \
  (!darray || FP_IS_FULL(darray) ? FP_RESIZE(darray) : 0,                      \
   memmove(darray + index + 1, darray + index,                                 \
           sizeof(*darray) * (FP_HEADER(darray)->length - index)),             \
   FP_HEADER(darray)->length++, darray[index] = value)

#define fp_delete(index, darray)                                               \
  (memmove(darray + index, darray + index + 1,                                 \
           sizeof(*darray) * (FP_HEADER(darray)->length - index - 1)),         \
   --FP_HEADER(darray)->length)

#endif
