/* Darray speed test. Consists of 20 000 000 pushes of consecutive integers
 * or integral points, then pops each one. */

#include <stdio.h>
#include <time.h>

#include "code_gen.h"
CG_INIT(int, i)

#include "fat_pointer.h"
#include "void.h"

#include "kvec.h"

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

void speed_test(void) {
  int M = 10, N = 20000000, i, j;
  clock_t t;

  t = clock();
  for (i = 0; i < M; ++i) {
    i_darray *darray = i_create(2);
    for (j = 0; j < N; ++j)
      i_push(darray, j);
    for (j = 0; j < N; ++j)
      i_pop(darray);
    i_destroy(darray);
  }
  printf("code_gen.h : %.3f sec\n", (float)(clock() - t) / CLOCKS_PER_SEC);

  t = clock();
  for (i = 0; i < M; ++i) {
    int *darray = NULL;
    for (j = 0; j < N; ++j)
      fp_push(darray, j);
    for (j = 0; j < N; ++j)
      fp_pop(darray);
    fp_destroy(darray);
  }
  printf("fat_pointer.h : %.3f sec\n", (float)(clock() - t) / CLOCKS_PER_SEC);

  t = clock();
  for (i = 0; i < M; ++i) {
    V_Darray *darray = v_create(2, sizeof(int));
    for (j = 0; j < N; ++j)
      v_push(darray, &j);
    for (j = 0; j < N; ++j)
      v_pop(darray, NULL);
    v_destroy(darray);
  }
  printf("void.h : %.3f sec\n", (float)(clock() - t) / CLOCKS_PER_SEC);

  t = clock();
  for (i = 0; i < M; ++i) {
    kvec_t(int) darray;
    kv_init(darray);
    for (j = 0; j < N; ++j)
      kv_push(int, darray, j);
    for (j = 0; j < N; ++j)
      kv_pop(darray);
    kv_destroy(darray);
  }
  printf("kvec.h %.3f sec\n", (float)(clock() - t) / CLOCKS_PER_SEC);

  t = clock();
  for (i = 0; i < M; ++i) {
    int *darray = NULL;
    for (j = 0; j < N; ++j)
      arrput(darray, j);
    for (j = 0; j < N; ++j)
      arrpop(darray);
    arrfree(darray);
  }
  printf("stb_ds.h: %.3f sec\n", (float)(clock() - t) / CLOCKS_PER_SEC);
}

int main(void) {
  speed_test();
  return 0;
}
