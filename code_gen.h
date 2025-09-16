/* dynamic array implementation by code generating macros
 * uses macro INIT(TYPE, PREFIX to generate all the definitions for a
 * dynamic array structure and operations for the specific TYPE, label the
 * structure and operation with PREFIX */

#include <stdlib.h>

#define INIT(TYPE, PREFIX)													\
	MAKE_STRUCT(TYPE, PREFIX)												\
	MAKE_CREATE(TYPE, PREFIX)												\
	MAKE_SIZE(TYPE, PREFIX)													\
	MAKE_IS_IN(TYPE, PREFIX)	\
	MAKE_GET(TYPE, PREFIX)

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
	PREFIX##darray *PREFIX##create (int capacity) {							\
		PREFIX##darray *p = malloc(sizeof(*p));								\
		p -> size = 0;														\
		p -> capacity = capacity;											\
		p -> data = malloc(capacity * sizeof(TYPE));						\
		return p;															\
	}

#define MAKE_DESTROY(TYPE, PREFIX)											\
	

#define MAKE_SIZE(TYPE, PREFIX)												\
	int PREFIX##size(const PREFIX##darray *DARRAY) {						\
		return DARRAY -> size; 												\
	}

#define MAKE_IS_IN(TYPE, PREFIX)											\
	int PREFIX##is_in(TYPE value, const PREFIX##darray *darray) {			\
		for (int i=0; i<DARRAY->size; i++) {								\
			if (value == darray -> data[i]) {								\
				return 1;													\
			}																\
		}																	\
		return 0;															\
	}

#define MAKE_GET(TYPE, PREFIX)												\
	TYPE PREFIX##get(int index, const PREFIX##darray *darray) {				\
		return darray -> data[index];

#define IS_FULL(DARRAY_PTR)													\
	(DARRAY_PTR -> size >= DARRAY_PTR -> capacity ? 1 : 0) 

#define MAKE_INSERT(TYPE, PREFIX) \
		void PREFIX##insert(TYPE )
