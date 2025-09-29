/* Darray implementation with the 'fat pointer' or 'stretchy buffer' method
 *
 * The data is stored in a regular array owned by the handle pointer, while the
 * metadata of size and capacity is stored in the memory location behind the
 * pointer.
 *
 * Usage:
 * int *darray = NULL;
 * fp_push(1, darray);
 * fp_push(2, darray);
 * fp_pop(darray);		<- returns 2
 * fp_destroy(darray);
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

#define fp_destroy(darray) ((darray == NULL) ? 0 : free(FP_HEADER(darray)))

#define FP_HEADER(darray) ((fp_header *)darray - 1)

/* TODO: Use this macro elsewhere in this file */
#define fp_length(darray) ((darray == NULL) ? (0) : (FP_HEADER(darray)->length))

#define FP_IS_FULL(darray)                                                     \
  ((FP_HEADER(darray)->length >= FP_HEADER(darray)->capacity) ? (1) : (0))

#define fp_push(value, darray)                                                 \
  (((darray == NULL) ? (FP_INIT(darray))                                       \
                     : ((FP_IS_FULL(darray)) ? (FP_ENLARGE(darray)) : (0))),   \
   darray[FP_HEADER(darray)->length++] = value)

/* TODO: unify enlarge and init into a single function */
static void *fp_enlarge(void *darray, int element_size) {
  int length = FP_HEADER(darray)->length;
  int capacity = FP_HEADER(darray)->capacity;
  fp_header *p = realloc(FP_HEADER(darray),
                         2 * capacity * element_size + sizeof(fp_header));
  p->length = length;
  p->capacity = 2 * capacity;
  return ++p;
}

static void *fp_init(int element_size) {
  fp_header *p = malloc(element_size + sizeof(fp_header));
  p->length = 0;
  p->capacity = 1;
  return ++p;
}

#define FP_INIT(darray) (darray = fp_init(sizeof(*darray)))

#define FP_ENLARGE(darray) (darray = fp_enlarge(darray, sizeof(*darray)))

#define fp_pop(darray) (darray[--(FP_HEADER(darray)->length)])

#define fp_insert(value, index, darray)                                        \
  (((darray == NULL) ? (FP_INIT(darray))                                       \
                     : ((FP_IS_FULL(darray)) ? (FP_ENLARGE(darray)) : 0)),     \
   memmove(darray + index + 1, darray + index,                                 \
           sizeof(*darray) * (FP_HEADER(darray)->length - index)),             \
   FP_HEADER(darray)->length++, darray[index] = value)

#define fp_delete(index, darray)                                               \
  (memmove(darray + index, darray + index + 1,                                 \
           sizeof(*darray) * (FP_HEADER(darray)->length - index - 1)),         \
   --FP_HEADER(darray)->length)

#endif
