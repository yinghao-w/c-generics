#include "void.h"
#include <stdlib.h>
#include <string.h>

struct V_Darray {
  int length;
  int capacity;
  int element_size;
  char *data;
};

V_Darray *v_create(int capacity, int element_size) {
  V_Darray *p = malloc(sizeof(*p));
  p->capacity = capacity;
  p->length = 0;
  p->element_size = element_size;
  p->data = malloc(capacity * element_size);
  return p;
}

/* destroys the darray  and the objects to which its data pointed */
void v_destroy(V_Darray *darray) {
  free(darray->data);
  free(darray);
}

int v_length(const V_Darray *darray) { return darray->length; }

static int v_is_full(const V_Darray *darray) {
  return (darray->length >= darray->capacity) ? 1 : 0;
}

static void v_enlarge(V_Darray *darray) {
  darray->data =
      realloc(darray->data, 2 * darray->capacity * darray->element_size);
  darray->capacity *= 2;
}

void v_push(const void *value, V_Darray *darray) {
  if (v_is_full(darray)) {
    v_enlarge(darray);
  }
  memcpy(darray->data + darray->element_size * darray->length, value,
         darray->element_size);
  darray->length++;
}

void v_pop(void *value, V_Darray *darray) {
  if (value) {
    memcpy(value, darray->data + darray->element_size * (darray->length - 1),
           darray->element_size);
  }
  darray->length--;
}

void v_insert(const void *value, int index, V_Darray *darray) {
  if (v_is_full(darray)) {
    v_enlarge(darray);
  }
  memmove(darray->data + darray->element_size * (index + 1),
          darray->data + darray->element_size * index,
          darray->element_size * darray->length - index);
  darray->length++;
  memcpy(darray->data + darray->element_size * index, value,
         darray->element_size);
}

void v_delete(void *value, int index, V_Darray *darray) {
  if (value) {
    memcpy(value, darray->data + darray->element_size * index,
           darray->element_size);
  }
  memmove(darray->data + darray->element_size * index,
          darray->data + darray->element_size * (index + 1),
          darray->element_size * darray->length - index - 1);
  darray->length--;
}

void v_get(void *value, int index, const V_Darray *darray) {
  memcpy(value, darray->data + darray->element_size * index,
         darray->element_size);
}
