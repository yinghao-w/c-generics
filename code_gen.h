/* dynamic array implementation by code generating macros
 * uses macro INIT(TYPE, PREFIX to generate all the definitions for a
 * dynamic array structure and operations for the specific TYPE, label the
 * structure and operation with PREFIX */

#include "stdlib.h"
#define INIT(TYPE, PREFIX)													\
	MAKE_STRUCT(TYPE, PREFIX)												\
	MAKE_CREATE(TYPE, PREFIX)

/* struct s { */
/* 	int a; char b; */
/* }; */
/* typedef struct s s; */

#define MAKE_STRUCT(TYPE, PREFIX)											\
	struct PREFIX##darray {													\
		int size;															\
		int capacity;														\
		TYPE *data;															\
	};																		\
	typedef struct PREFIX##darray PREFIX##darray;

#define MAKE_CREATE(TYPE, PREFIX)											\
	PREFIX##darray *PREFIX##create (int capacity){							\
		PREFIX##darray *p = malloc(sizeof(*p));								\
		p -> size = 0;														\
		p -> capacity = capacity;											\
		p -> data = malloc(capacity * sizeof(TYPE));						\
		return p;															\
	}
