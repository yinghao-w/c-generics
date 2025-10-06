/* Generic dynamic array implementation with code generation macros.
 *
 * Use:
 *
 * 		#include "code_gen.h"
 *
 * 	Generate all definitions necessary for a specific type, with definitions
 * and functions prefixed:
 *
 * 		CG_INIT(int, i)
 *
 * 	Initialise array:
 *
 * 		i_darray *a = i_create(10);
 */

#ifndef CODE_GEN_H

#define CODE_GEN_H

#include <stdlib.h>
#include <string.h>

/* declares and defines all necessary functions for a dynamic array structure
 * specific to the given type */
#define CG_INIT(TYPE, PREFIX)                                                  \
  MAKE_STRUCT(TYPE, PREFIX)                                                    \
  MAKE_CREATE(TYPE, PREFIX)                                                    \
  MAKE_DESTROY(TYPE, PREFIX)                                                   \
  MAKE_LENGTH(TYPE, PREFIX)                                                    \
  MAKE_PUSH(TYPE, PREFIX)                                                      \
  MAKE_POP(TYPE, PREFIX)                                                       \
  MAKE_INSERT(TYPE, PREFIX)                                                    \
  MAKE_DELETE(TYPE, PREFIX)                                                    \
  MAKE_GET(TYPE, PREFIX)

#define MAKE_STRUCT(TYPE, PREFIX)                                              \
  typedef struct {                                                             \
    size_t length;                                                             \
    size_t capacity;                                                           \
    TYPE *data;                                                                \
  } PREFIX##_darray;

#define MAKE_CREATE(TYPE, PREFIX)                                              \
  static PREFIX##_darray *PREFIX##_create(size_t capacity) {                   \
    PREFIX##_darray *p = malloc(sizeof(*p));                                   \
    p->length = 0;                                                             \
    p->capacity = capacity;                                                    \
    p->data = malloc(capacity * sizeof(TYPE));                                 \
    return p;                                                                  \
  }

#define MAKE_DESTROY(TYPE, PREFIX)                                             \
  static void PREFIX##_destroy(PREFIX##_darray *darray) {                      \
    free(darray->data);                                                        \
    free(darray);                                                              \
  }

#define MAKE_LENGTH(TYPE, PREFIX)                                              \
  static size_t PREFIX##_length(const PREFIX##_darray *darray) {               \
    return darray->length;                                                     \
  }

#define CG_IS_FULL(DARRAY) (DARRAY->length >= DARRAY->capacity ? 1 : 0)

#define CG_ENLARGE(DARRAY, TYPE)                                               \
  if (DARRAY->capacity == 0) {                                                 \
    DARRAY->data = malloc(sizeof(TYPE));                                       \
    DARRAY->capacity = 1;                                                      \
  } else {                                                                     \
    DARRAY->data = realloc(DARRAY->data, sizeof(TYPE) * DARRAY->capacity * 2); \
    DARRAY->capacity *= 2;                                                     \
  }

#define MAKE_PUSH(TYPE, PREFIX)                                                \
  static void PREFIX##_push(TYPE value, PREFIX##_darray *darray) {             \
    if (CG_IS_FULL(darray)) {                                                  \
      CG_ENLARGE(darray, TYPE)                                                 \
    }                                                                          \
    darray->data[darray->length++] = value;                                    \
  }

#define MAKE_POP(TYPE, PREFIX)                                                 \
  static TYPE PREFIX##_pop(PREFIX##_darray *darray) {                          \
    return darray->data[--darray->length];                                     \
  }

#define MAKE_INSERT(TYPE, PREFIX)                                              \
  static void PREFIX##_insert(TYPE value, size_t index,                        \
                              PREFIX##_darray *darray) {                       \
    if (CG_IS_FULL(darray)) {                                                  \
      CG_ENLARGE(darray, TYPE);                                                \
    }                                                                          \
    memmove(darray->data + index + 1, darray->data + index,                    \
            sizeof(TYPE) * (darray->length - index));                          \
    darray->length++;                                                          \
    darray->data[index] = value;                                               \
  }

#define MAKE_DELETE(TYPE, PREFIX)                                              \
  static TYPE PREFIX##_delete(size_t index, PREFIX##_darray *darray) {         \
    TYPE value = darray->data[index];                                          \
    memmove(darray->data + index, darray->data + index + 1,                    \
            sizeof(TYPE) * (darray->length - index - 1));                      \
    darray->length--;                                                          \
    return value;                                                              \
  }

#define MAKE_GET(TYPE, PREFIX)                                                 \
  static TYPE PREFIX##_get(size_t index, const PREFIX##_darray *darray) {      \
    return darray->data[index];                                                \
  }

#endif
