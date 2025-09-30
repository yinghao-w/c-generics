#include <assert.h>
#include <stdio.h>

/* Define *one* of these:

        #define USE_CODE_GEN
        #define USE_FAT_POINTER
        #define USE_VOID

*/

#include "unified.h"

void create_destroy_test(void) {
  for (int i = 0; i < 1000; i++) {
    U_CREATE(A, i);
    assert(U_LEN(A) == 0);
    U_DESTROY(A);
  }
  printf("\tSuccessful create and destroy test.\n");
}

void push_pop_test(void) {
  U_CREATE(A, 1);
  for (int i = 0; i < 10; i++) {
    U_PUSH(U_MAKE(i), A);
  }
  assert(U_LEN(A) == 10);
  for (int i = 0; i < 10; i++) {
    assert(U_GET_INT(i, A) == i);
  }
  for (int i = 0; i < 10; i++) {
    assert(U_POP_INT(A) == 10 - i - 1);
  }
  assert(U_LEN(A) == 0);
  U_DESTROY(A);
  printf("\tSuccessful push and pop test.\n");
}

void insert_test(void) {
  U_CREATE(A, 1);
  U_INS(U_MAKE(0), 0, A);
  U_INS(U_MAKE(1), 1, A);
  U_INS(U_MAKE(2), 2, A);
  U_INS(U_MAKE(3), 0, A);
  U_INS(U_MAKE(4), 1, A);
  assert(U_GET_INT(0, A) == 3);
  assert(U_GET_INT(2, A) == 0);
  assert(U_GET_INT(4, A) == 2);
  assert(U_LEN(A) == 5);
  U_DESTROY(A);
  printf("\tSuccessful insert test.\n");
}

void delete_test(void) {
  U_CREATE(A, 1);
  for (int i = 0; i < 10; i++) {
    U_PUSH(U_MAKE(i), A);
  }
  U_DEL(9, A);
  U_DEL(0, A);
  U_DEL(4, A);
  assert(U_GET_INT(0, A) == 1);
  assert(U_GET_INT(4, A) == 6);
  assert(U_GET_INT(6, A) == 8);
  assert(U_LEN(A) == 7);
  U_DESTROY(A);
  printf("\tSuccessful delete test.\n");
}

void tests(void) {
  printf("Type: %s\nImplementation: %s\n", type, impl);
  create_destroy_test();
  push_pop_test();
  insert_test();
  delete_test();
  printf("\n");
}

int main(void) {
  tests();
  return 0;
}
