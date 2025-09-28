/* darray implementation by code generating macros
 * uses macro CG_INIT(TYPE, PREFIX to generate all the definitions for a
 * dynamic array structure and darray operations for the specific TYPE, label
 * the structure and operation with PREFIX */

/*
 * example darray for type 'point':
 *
 * generate all necessary code:
 *
 * CG_INIT(point, pt)
 *
 * initialise darray:
 *
 * pt_darray *my_darray = pt_create(10);
 *
 * operations:
 *
 * point p, q;
 * pt_push(p, my_darray);
 * pt_push(q, my_darray);
 * pt r = pt_pop(my_darray);
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
  struct PREFIX##_darray {                                                     \
    int LENGTH;                                                                \
    int CAPACITY;                                                              \
    TYPE *DATA;                                                                \
  };                                                                           \
  typedef struct PREFIX##_darray PREFIX##_darray;

#define MAKE_CREATE(TYPE, PREFIX)                                              \
  static PREFIX##_darray *PREFIX##_create(int CAPACITY) {                      \
    PREFIX##_darray *p = malloc(sizeof(*p));                                   \
    p->LENGTH = 0;                                                             \
    p->CAPACITY = CAPACITY;                                                    \
    p->DATA = malloc(CAPACITY * sizeof(TYPE));                                 \
    return p;                                                                  \
  }

/* If the data consists of pointers, the underlying memory to which are
 * pointed are not freed. For wide applicablity need the user to supply
 * custom destructors TODO: */
#define MAKE_DESTROY(TYPE, PREFIX)                                             \
  static void PREFIX##_destroy(PREFIX##_darray *darray) {                      \
    free(darray->DATA);                                                        \
    free(darray);                                                              \
  }

#define MAKE_LENGTH(TYPE, PREFIX)                                              \
  static int PREFIX##_length(const PREFIX##_darray *darray) {                  \
    return darray->LENGTH;                                                     \
  }

#define CG_IS_FULL(DARRAY) (DARRAY->LENGTH >= DARRAY->CAPACITY ? 1 : 0)

#define CG_ENLARGE(DARRAY, TYPE)                                               \
  DARRAY->DATA = realloc(DARRAY->DATA, sizeof(TYPE) * DARRAY->CAPACITY * 2);   \
  DARRAY->CAPACITY *= 2;

#define MAKE_PUSH(TYPE, PREFIX)                                                \
  static void PREFIX##_push(TYPE value, PREFIX##_darray *darray) {             \
    if (CG_IS_FULL(darray)) {                                                  \
      CG_ENLARGE(darray, TYPE)                                                 \
    }                                                                          \
    darray->DATA[darray->LENGTH++] = value;                                    \
  }

/* If the darray is empty, return the empty initialisation of the given
 * type */
#define MAKE_POP(TYPE, PREFIX)                                                 \
  static TYPE PREFIX##_pop(PREFIX##_darray *darray) {                          \
    if (darray->LENGTH == 0) {                                                 \
      return (TYPE){0};                                                        \
    }                                                                          \
    return darray->DATA[--darray->LENGTH];                                     \
  }

/* TODO: decide on behaviour when index > length */
#define MAKE_INSERT(TYPE, PREFIX)                                              \
  static void PREFIX##_insert(TYPE value, int index,                           \
                              PREFIX##_darray *darray) {                       \
    if (CG_IS_FULL(darray)) {                                                  \
      CG_ENLARGE(darray, TYPE);                                                \
    }                                                                          \
    memmove(darray->DATA + index + 1, darray->DATA + index,                    \
            sizeof(TYPE) * (darray->LENGTH - index));                          \
    darray->LENGTH++;                                                          \
    darray->DATA[index] = value;                                               \
  }

/* TODO: decide on behaviour when index > length */
#define MAKE_DELETE(TYPE, PREFIX)                                              \
  static TYPE PREFIX##_delete(int index, PREFIX##_darray *darray) {            \
    TYPE value = darray->DATA[index];                                          \
    memmove(darray->DATA + index, darray->DATA + index + 1,                    \
            sizeof(TYPE) * (darray->LENGTH - index - 1));                      \
    darray->LENGTH--;                                                          \
    return value;                                                              \
  }

/* TODO: decide on behaviour when index > length */
#define MAKE_GET(TYPE, PREFIX)                                                 \
  static TYPE PREFIX##_get(int index, const PREFIX##_darray *darray) {         \
    return darray->DATA[index];                                                \
  }

#endif
