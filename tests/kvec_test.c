/* Darray speed test. Consists of 20 000 000 pushes of consecutive integers
 * or integral points, then pops each one. */

#include <stdio.h>
#include <time.h>

#include "code_gen.h"
#include "fat_pointer.h"
#include "void.h"

CG_INIT(int, i)

typedef struct point {
  int x;
  int y;
} point;
CG_INIT(point, pt)

void speed_test(void) {
  int M = 10, N = 20000000, i, j;
  clock_t t;

  t = clock();
  for (i = 0; i < M; ++i) {
    i_darray *darray = i_create(2);
    for (j = 0; j < N; ++j)
      i_push(j, darray);
    for (j = 0; j < N; ++j)
      i_pop(darray);
    i_destroy(darray);
  }
  printf("code generation darray (int): %.3f sec\n",
         (float)(clock() - t) / CLOCKS_PER_SEC);

  t = clock();
  for (i = 0; i < M; ++i) {
    pt_darray *darray = pt_create(2);
    for (j = 0; j < N; ++j)
      pt_push((point){j, j}, darray);
    for (j = 0; j < N; ++j)
      pt_pop(darray);
    pt_destroy(darray);
  }
  printf("code generation darray (point): %.3f sec\n",
         (float)(clock() - t) / CLOCKS_PER_SEC);

  t = clock();
  for (i = 0; i < M; ++i) {
    int *darray = NULL;
    for (j = 0; j < N; ++j)
      fp_push(j, darray);
    for (j = 0; j < N; ++j)
      fp_pop(darray);
    fp_destroy(darray);
  }
  printf("fat pointer darray (int): %.3f sec\n",
         (float)(clock() - t) / CLOCKS_PER_SEC);

  t = clock();
  for (i = 0; i < M; ++i) {
    point *darray = NULL;
    for (j = 0; j < N; ++j)
      fp_push(((point){j, j}), darray);
    for (j = 0; j < N; ++j)
      fp_pop(darray);
    fp_destroy(darray);
  }
  printf("fat pointer darray (point): %.3f sec\n",
         (float)(clock() - t) / CLOCKS_PER_SEC);

  t = clock();
  for (i = 0; i < M; ++i) {
    /* TODO: better handling of no wanting output */
    char junk[sizeof(int)];
    V_Darray *darray = v_create(2, sizeof(int));
    for (j = 0; j < N; ++j)
      v_push(&j, darray);
    for (j = 0; j < N; ++j)
      v_pop(&junk, darray);
    v_destroy(darray);
  }
  printf("void * darray (int): %.3f sec\n",
         (float)(clock() - t) / CLOCKS_PER_SEC);

  t = clock();
  for (i = 0; i < M; ++i) {
    /* TODO: better handling of no wanting output */
    char junk[sizeof(point)];
    point jj;
    V_Darray *darray = v_create(2, sizeof(point));
    for (j = 0; j < N; ++j) {
      jj = (point){j, j};
      v_push(&jj, darray);
    }
    for (j = 0; j < N; ++j)
      v_pop(&junk, darray);
    v_destroy(darray);
  }
  printf("void * darray (point): %.3f sec\n",
         (float)(clock() - t) / CLOCKS_PER_SEC);
}
