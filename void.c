#include "void.h"
#include <stdlib.h>
#include <string.h>

struct V_Darray {
  size_t length;
  size_t capacity;
  size_t element_size;
  char *data;
};

V_Darray *v_create(size_t capacity, size_t element_size) {
  V_Darray *p = malloc(sizeof(*p));
  p->capacity = capacity;
  p->length = 0;
  p->element_size = element_size;
  p->data = malloc(capacity * element_size);
  return p;
}

/* Destroys the darray  and the objects to which its data pointed. */
void v_destroy(V_Darray *darray) {
  free(darray->data);
  free(darray);
}

size_t v_length(const V_Darray *darray) { return darray->length; }

static int v_is_full(const V_Darray *darray) {
  return (darray->length >= darray->capacity) ? 1 : 0;
}

static void v_enlarge(V_Darray *darray) {
  if (darray->capacity == 0) {
    darray->data = malloc(darray->element_size);
    darray->capacity = 1;
  } else {
    darray->data =
        realloc(darray->data, 2 * darray->capacity * darray->element_size);
    darray->capacity *= 2;
  }
}
void v_push(V_Darray *darray, const void *value) {
  if (v_is_full(darray)) {
    v_enlarge(darray);
  }
  memcpy(darray->data + darray->element_size * darray->length, value,
         darray->element_size);
  darray->length++;
}

void v_pop(V_Darray *darray, void *value) {
  if (value) {
    memcpy(value, darray->data + darray->element_size * (darray->length - 1),
           darray->element_size);
  }
  darray->length--;
}

void v_insert(V_Darray *darray, const void *value, size_t index) {
  if (v_is_full(darray)) {
    v_enlarge(darray);
  }
  memmove(darray->data + darray->element_size * (index + 1),
          darray->data + darray->element_size * index,
          darray->element_size * (darray->length - index));
  darray->length++;
  memcpy(darray->data + darray->element_size * index, value,
         darray->element_size);
}

void v_delete(V_Darray *darray, void *value, size_t index) {
  if (value) {
    memcpy(value, darray->data + darray->element_size * index,
           darray->element_size);
  }
  memmove(darray->data + darray->element_size * index,
          darray->data + darray->element_size * (index + 1),
          darray->element_size * (darray->length - index - 1));
  darray->length--;
}

void v_get(const V_Darray *darray, void *value, size_t index) {
  memcpy(value, darray->data + darray->element_size * index,
         darray->element_size);
}
