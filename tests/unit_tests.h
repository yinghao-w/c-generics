/* Unified API for all three dynamic array implementations. Main use is to aid
 * in writing tests. */

#ifdef POINT
struct point {
  int x;
  int y;
};
#define U_TYPE struct point
#define U_MAKE(I) ((U_TYPE){.x = I, .y = I})
#define U_POP_INT(I) U_POP(I).x
#define U_GET_INT(I, A) U_GET(I, A).x
#endif

#ifdef LONG_DOUBLE
#define U_TYPE long double
#define U_MAKE(I) I
#define U_POP_INT(A) U_POP(A)
#define U_GET_INT(I, A) U_GET(I, A)
#endif

#ifndef U_TYPE
#define U_TYPE int
#define U_MAKE(I) I
#define U_POP_INT(A) U_POP(A)
#define U_GET_INT(I, A) U_GET(I, A)
#endif

#define STR_0(x) #x
#define STR(x) STR_0(x)

char type[] = STR(U_TYPE);
char to_type[] = STR(U_MAKE);
char type_pop[] = STR(U_POP_INT(A));
char type_get[] = STR(U_GET_INT(I, A));

#ifdef USE_CODE_GEN

char impl[] = "code_gen.h";

#include "code_gen.h"

CG_INIT(U_TYPE, u)

#define U_CREATE(A, C) u_darray *A = u_create(C)
#define U_DESTROY(A) u_destroy(A)
#define U_PUSH(V, A) u_push(V, A)
#define U_POP(A) u_pop(A)
#define U_INS(V, I, A) u_insert(V, I, A)
#define U_DEL(I, A) u_delete(I, A)
#define U_GET(I, A) u_get(I, A)
#define U_LEN(A) u_length(A)

#endif

#ifdef USE_FAT_POINTER

char impl[] = "fat_pointer.h";

#include "fat_pointer.h"

#define U_CREATE(A, C) U_TYPE *A = NULL
#define U_DESTROY(A) fp_destroy(A)
#define U_PUSH(V, A) fp_push(A, V)
#define U_POP(A) fp_pop(A)
#define U_INS(V, I, A) fp_insert(A, V, I)
#define U_DEL(I, A) fp_delete(A, I)
#define U_GET(I, A) A[I]
#define U_LEN(A) fp_length(A)

#endif

#ifdef USE_VOID

char impl[] = "void.c";

#include "void.h"

U_TYPE T;

#define U_CREATE(A, C) V_Darray *A = v_create(C, sizeof(U_TYPE))
#define U_DESTROY(A) v_destroy(A)
#define U_PUSH(V, A)                                                           \
  T = V;                                                                       \
  v_push(&T, A)
#define U_POP(A) (v_pop(&T, A), T)
#define U_INS(V, I, A)                                                         \
  T = V;                                                                       \
  v_insert(&T, I, A)
#define U_DEL(I, A) v_delete(NULL, I, A)
#define U_GET(I, A) (v_get(&T, I, A), T)
#define U_LEN(A) v_length(A)

#endif
