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
    size_t LENGTH;                                                             \
    size_t CAPACITY;                                                           \
    TYPE *DATA;                                                                \
  } PREFIX##_darray;

#define MAKE_CREATE(TYPE, PREFIX)                                              \
  static PREFIX##_darray *PREFIX##_create(size_t CAPACITY) {                   \
    PREFIX##_darray *p = malloc(sizeof(*p));                                   \
    p->LENGTH = 0;                                                             \
    p->CAPACITY = CAPACITY;                                                    \
    p->DATA = malloc(CAPACITY * sizeof(TYPE));                                 \
    return p;                                                                  \
  }

#define MAKE_DESTROY(TYPE, PREFIX)                                             \
  static void PREFIX##_destroy(PREFIX##_darray *darray) {                      \
    free(darray->DATA);                                                        \
    free(darray);                                                              \
  }

#define MAKE_LENGTH(TYPE, PREFIX)                                              \
  static size_t PREFIX##_length(const PREFIX##_darray *darray) {               \
    return darray->LENGTH;                                                     \
  }

#define CG_IS_FULL(DARRAY) (DARRAY->LENGTH >= DARRAY->CAPACITY ? 1 : 0)

#define CG_ENLARGE(DARRAY, TYPE)                                               \
  if (DARRAY->CAPACITY == 0) {                                                 \
    DARRAY->DATA = malloc(sizeof(TYPE));                                       \
    DARRAY->CAPACITY = 1;                                                      \
  } else {                                                                     \
    DARRAY->DATA = realloc(DARRAY->DATA, sizeof(TYPE) * DARRAY->CAPACITY * 2); \
    DARRAY->CAPACITY *= 2;                                                     \
  }

#define MAKE_PUSH(TYPE, PREFIX)                                                \
  static void PREFIX##_push(TYPE value, PREFIX##_darray *darray) {             \
    if (CG_IS_FULL(darray)) {                                                  \
      CG_ENLARGE(darray, TYPE)                                                 \
    }                                                                          \
    darray->DATA[darray->LENGTH++] = value;                                    \
  }

#define MAKE_POP(TYPE, PREFIX)                                                 \
  static TYPE PREFIX##_pop(PREFIX##_darray *darray) {                          \
    return darray->DATA[--darray->LENGTH];                                     \
  }

#define MAKE_INSERT(TYPE, PREFIX)                                              \
  static void PREFIX##_insert(TYPE value, size_t index,                        \
                              PREFIX##_darray *darray) {                       \
    if (CG_IS_FULL(darray)) {                                                  \
      CG_ENLARGE(darray, TYPE);                                                \
    }                                                                          \
    memmove(darray->DATA + index + 1, darray->DATA + index,                    \
            sizeof(TYPE) * (darray->LENGTH - index));                          \
    darray->LENGTH++;                                                          \
    darray->DATA[index] = value;                                               \
  }

#define MAKE_DELETE(TYPE, PREFIX)                                              \
  static TYPE PREFIX##_delete(size_t index, PREFIX##_darray *darray) {         \
    TYPE value = darray->DATA[index];                                          \
    memmove(darray->DATA + index, darray->DATA + index + 1,                    \
            sizeof(TYPE) * (darray->LENGTH - index - 1));                      \
    darray->LENGTH--;                                                          \
    return value;                                                              \
  }

#define MAKE_GET(TYPE, PREFIX)                                                 \
  static TYPE PREFIX##_get(size_t index, const PREFIX##_darray *darray) {      \
    return darray->DATA[index];                                                \
  }

#endif
