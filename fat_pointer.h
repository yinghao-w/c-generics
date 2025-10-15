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
 * 		int *arr = NULL;
 *
 * Resize the array to hold at least cap many elements:
 *
 * 		fp_resize(cap, arr);
 *
 * Note that when the array is resized, either explicitly as above or by
 * push/insert operations, the new array address is assigned back to arr
 * through the macro. Be careful when offloading element adding operations to
 * other functions:
 *
 * 		void add_one(int arr[]) {
 * 			fp_push(1, arr);
 * 		}
 * 		{
 * 			...
 * 			int *my_arr = NULL;
 * 			fp_push(5, my_arr);
 * 			fp_push(2, my_arr);
 * 			add_one(my_arr);
 *
 * 			...
 * 		}
 *
 * If the array gets resized to a different location, only the arr parameter in
 * add_one will be updated, my_arr will still hold the outdated address. One
 * must return the updated address and assign it back to my_arr.
 *
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

static void *fp_enlarge(void *darray, size_t element_size) {
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

#define FP_ENLARGE(darray) (darray = fp_enlarge(darray, sizeof(*darray)))

#define fp_destroy(darray) (darray ? free(FP_HEADER(darray)), 0 : 0)

#define fp_length(darray) (darray ? FP_LENGTH(darray) : 0)

#define fp_resize(cap, darray)                                                 \
  while (!darray || cap > FP_CAPACITY(darray)) {                               \
    FP_ENLARGE(darray);                                                        \
  }

#define fp_push(value, darray)                                                 \
  (!darray || FP_IS_FULL(darray) ? FP_ENLARGE(darray) : 0,                     \
   darray[FP_LENGTH(darray)++] = value)

#define fp_pop(darray) (darray[--FP_LENGTH(darray)])

#define fp_insert(value, index, darray)                                        \
  (!darray || FP_IS_FULL(darray) ? FP_ENLARGE(darray) : 0,                     \
   memmove(darray + index + 1, darray + index,                                 \
           sizeof(*darray) * (FP_LENGTH(darray) - index)),                     \
   FP_LENGTH(darray)++, darray[index] = value)

#define fp_delete(index, darray)                                               \
  (memmove(darray + index, darray + index + 1,                                 \
           sizeof(*darray) * (FP_LENGTH(darray) - index - 1)),                 \
   --FP_LENGTH(darray))

#endif
