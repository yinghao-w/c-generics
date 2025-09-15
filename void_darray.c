#include <stdlib.h>
#include "void_darray.h"

struct Darray {
	int size;
	int capacity;
	void **data;
};

int size(const Darray *darray) {
	return darray -> size;
}
int is_in(void *value, const Darray *darray) {
	for (int i = 0; i < size(darray); i++) {
		if (value == darray -> data[i]) {
			return 1;
		}
	}
	return 0;
}

void *get(int index, const Darray *darray) {
	if (index < size(darray)) {
		return darray -> data[index];
	} else {
		return NULL;
	}
}

static int is_full(Darray *darray) {
	return (darray->size >= darray->capacity) ? 1 : 0;
}

static void enlarge(Darray *darray) {
	;
}

/* copies index+1, index+2, ... to index, index+1, ... */
static void shift_down (int index, Darray *darray) {
	for (int i = index; i < size(darray) - 1; i++) {
		darray -> data[i] = darray -> data[i+1];
	}
	darray -> size--;
}
/* copies index, index+1, ... to index+1, index+2, ... */
static void shift_up (int index, Darray *darray) {
	void *temp;
	for (int i = index; i < size(darray) - 1; i++) {
		temp = darray -> data[i];
		darray -> data[i+1] = temp;
	}
	darray -> size++;
}

void insert(void *value, int index, Darray *darray) {
	if (is_full(darray)) {
		enlarge(darray);
	}
	shift_up(index, darray);
	darray -> data[index] = value;
}

void append(void *value, Darray *darray) {
	insert(value, size(darray), darray);
}

void remove(int index, Darray *darray) {
	shift_down(index, darray);
}
