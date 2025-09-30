/* TODO: does not allow creating an arrow with 0 capacity, no init checking in
 * push */

#define TI_TYPE int
#define TI_PREFIX i

#define TI_CONCAT_2(A, B) A##_##B
#define TI_CONCAT(A, B) TI_CONCAT_2(A, B)

#include <stdlib.h>
#include <string.h>

struct TI_CONCAT(TI_PREFIX, darray) {
  int LENGTH;
  int CAPACITY;
  TI_TYPE *DATA;
};
typedef struct TI_CONCAT(TI_PREFIX, darray) TI_CONCAT(TI_PREFIX, darray);

static TI_CONCAT(TI_PREFIX, darray) *
    TI_CONCAT(TI_PREFIX, create)(int CAPACITY) {
  TI_CONCAT(TI_PREFIX, darray) *p = malloc(sizeof(*p));
  p->LENGTH = 0;
  p->CAPACITY = CAPACITY;
  p->DATA = malloc(CAPACITY * sizeof(TI_TYPE));
  return p;
}

static void TI_CONCAT(TI_PREFIX,
                      destroy)(TI_CONCAT(TI_PREFIX, darray) * darray) {
  free(darray->DATA);
  free(darray);
}

static int TI_CONCAT(TI_PREFIX,
                     length)(const TI_CONCAT(TI_PREFIX, darray) * darray) {
  return darray->LENGTH;
}

static void TI_CONCAT(TI_PREFIX, push)(TI_TYPE value,
                                       TI_CONCAT(TI_PREFIX, darray) * darray) {
  if (darray->LENGTH >= darray->CAPACITY) {
    darray->DATA =
        realloc(darray->DATA, sizeof(TI_TYPE) * darray->CAPACITY * 2);
    darray->CAPACITY *= 2;
  }
  darray->DATA[darray->LENGTH++] = value;
}

static TI_TYPE TI_CONCAT(TI_PREFIX,
                         pop)(TI_CONCAT(TI_PREFIX, darray) * darray) {
  return darray->DATA[--darray->LENGTH];
}

static void TI_CONCAT(TI_PREFIX,
                      insert)(TI_TYPE value, int index,
                              TI_CONCAT(TI_PREFIX, darray) * darray) {
  if (darray->LENGTH >= darray->CAPACITY) {
    darray->DATA =
        realloc(darray->DATA, sizeof(TI_TYPE) * darray->CAPACITY * 2);
    darray->CAPACITY *= 2;
  }
  memmove(darray->DATA + index + 1, darray->DATA + index,
          sizeof(TI_TYPE) * (darray->LENGTH - index));
  darray->LENGTH++;
  darray->DATA[index] = value;
}

static TI_TYPE
TI_CONCAT(TI_PREFIX, delete)(int index, TI_CONCAT(TI_PREFIX, darray) * darray) {
  TI_TYPE value = darray->DATA[index];
  memmove(darray->DATA + index, darray->DATA + index + 1,
          sizeof(TI_TYPE) * (darray->LENGTH - index - 1));
  darray->LENGTH--;
  return value;
}

static TI_TYPE TI_CONCAT(TI_PREFIX,
                         get)(int index,
                              const TI_CONCAT(TI_PREFIX, darray) * darray) {
  return darray->DATA[index];
}

#undef TI_TYPE
#undef TI_PREFIX

#undef TI_CONCAT_2
#undef TI_CONCAT
