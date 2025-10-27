/* Applies a pseudo-random series of pushes, pops, inserts, and deletes on each
 * array. The operation and value of each array is the same. After each
 * operation the arrays are compared to one another. */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "code_gen.h"
#include "fat_pointer.h"
#include "void.h"

CG_INIT(int, i)

void fuzz_test(void) {
  srand(1444 * 1337);
  int M = 5;
  int N = 2000;

  for (int i = 0; i < M; i++) {
    i_darray *cg_darray = i_create(1);
    int *fp_darray = NULL;
    V_Darray *v_darray = v_create(1, sizeof(int));

    for (int j = 0; j < N; j++) {
      int op = rand() % 4;

      if (i_length(cg_darray) == 0 || op == 0) {
        i_push(j, cg_darray);
        fp_push(fp_darray, j);
        v_push(&j, v_darray);
      } else if (op == 1) {
        int cg, fp, v;
        cg = i_pop(cg_darray);
        fp = fp_pop(fp_darray);
        v_pop(&v, v_darray);
        assert(cg == fp);
        assert(cg == v);
      } else if (op == 2) {
        int index = rand() % i_length(cg_darray);
        i_insert(j, index, cg_darray);
        fp_insert(fp_darray, j, index);
        v_insert(&j, index, v_darray);
      } else {
        int index = rand() % i_length(cg_darray);
        i_delete(index, cg_darray);
        fp_delete(fp_darray, index);
        v_delete(NULL, index, v_darray);
      }

      assert(i_length(cg_darray) == fp_length(fp_darray));
      assert(i_length(cg_darray) == v_length(v_darray));

      for (int k = 0; k < i_length(cg_darray); k++) {
        assert(i_get(k, cg_darray) == fp_darray[k]);
        int v;
        v_get(&v, k, v_darray);
        assert(i_get(k, cg_darray) == v);
      }
    }

    i_destroy(cg_darray);
    fp_destroy(fp_darray);
    v_destroy(v_darray);
  }
  printf("Successful random operations test.\n");
}

int main(void) {
  fuzz_test();
  return 0;
}
