/* dynamic array implementation by code generating macros
 * uses macro INIT(TYPE, PREFIX to generate all the definitions for a
 * dynamic array structure and operations for the specific TYPE, label the
 * structure and operation with PREFIX */

/*
 * example dynamic array for type 'point':
 *
 * generate all necessary code:
 *
 * INIT(point, pt)
 *
 * initialise array:
 *
 * pt_darray *my_darray = pt_create(10);
 *
 * operations:
 *
 * point p, q, r;
 * pt_append(p, my_darray);
 * pt_insert(q, 1, my_darray);
 * pt_is_in(r, my_darray);
*/


#include "void_darray.h"
#include <stdlib.h>

/* declares and defines all necessary functions for a dynamic array structure
 * specific to the given type */
#define INIT(TYPE, PREFIX)													\
	MAKE_STRUCT(TYPE, PREFIX)												\
	MAKE_CREATE(TYPE, PREFIX)												\
	MAKE_SIZE(TYPE, PREFIX)													\
	MAKE_IS_IN(TYPE, PREFIX)												\
	MAKE_GET(TYPE, PREFIX)													\
	MAKE_INSERT(TYPE, PREFIX)												\
	MAKE_APPEND(TYPE, PREFIX)												\
	MAKE_OMIT(TYPE, PREFIX)

#define MAKE_STRUCT(TYPE, PREFIX)											\
	struct PREFIX##_darray {												\
		int SIZE;															\
		int CAP;															\
		TYPE *DATA;															\
	};																		\
	typedef struct PREFIX##_darray PREFIX##_darray;

#define MAKE_CREATE(TYPE, PREFIX)											\
	PREFIX##_darray *PREFIX##_create(int CAP) {								\
		PREFIX##_darray *p = malloc(sizeof(*p));							\
		p -> SIZE = 0;														\
		p -> CAP = CAP;														\
		p -> DATA = malloc(CAP * sizeof(TYPE));								\
		return p;															\
	}

#define MAKE_DESTROY(TYPE, PREFIX)											\
	void PREFIX##_destroy(PREFIX##_darray *darray) {						\
		while (darray -> SIZE--) {											\
			free(darray -> DATA[darray -> SIZE])							\
		}																	\
		free (darray -> DATA);												\
		free (darray);														\
	}


#define MAKE_SIZE(TYPE, PREFIX)												\
	int PREFIX##_size(const PREFIX##_darray *darray) {						\
		return darray -> SIZE; 												\
	}

#define MAKE_IS_IN(TYPE, PREFIX)											\
	int PREFIX##_is_in(TYPE value, const PREFIX##_darray *darray) {			\
		for (int i = 0; i < darray->SIZE; i++) {							\
			if (value == darray -> DATA[i]) {								\
				return 1;													\
			}																\
		}																	\
		return 0;															\
	}

#define MAKE_GET(TYPE, PREFIX)												\
	TYPE PREFIX##_get(int index, const PREFIX##_darray *darray) {			\
		return darray -> DATA[index];

#define IS_FULL(DARRAY)														\
	(DARRAY -> SIZE >= DARRAY -> CAP ? 1 : 0);

#define ENLARGE(DARRAY, TYPE)												\
	DARRAY -> DATA = realloc(DARRAY->DATA, sizeof(TYPE) * DARRAY->CAP * 2);	\
	DARRAY -> CAP *= 2;

#define SHIFT_DOWN(INDEX, DARRAY, TYPE)										\
		for (int i = INDEX, i < DARRAY->SIZE, i++) {						\
			DARRAY -> DATA[i] = darray -> data[i+1];						\
		}																	\
		darray -> size--;

#define SHIFT_UP(INDEX, DARRAY, TYPE)										\
		for (int i = DARRAY->SIZE, i > index, i--) {						\
			DARRAY -> DATA[i] = darray -> data[i-1];						\
		}																	\
		darray -> size++;

#define MAKE_INSERT(TYPE, PREFIX)											\
		void PREFIX##_insert(TYPE value, int index, PREFIX##_darray *darray) {\
			if (IS_FULL(darray)) {											\
				ENLARGE(darray, TYPE)										\
			}																\
			darray -> DATA[index] = value;									\
		}

#define MAKE_APPEND(TYPE, PREFIX)											\
		void PREFIX##_append(TYPE value, PREFIX##_darray *darray) {			\
			PREFIX##_insert(value, darray -> SIZE, darray)					\
		}

#define MAKE_OMIT(TYPE, PREFIX)												\
		void PREFIX##_omit(int index, PREFIX##_darray *darray) {			\
			SHIFT_DOWN(index, darray, TYPE)									\
		}
