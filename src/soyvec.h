#ifndef SOYVEC_H
#define SOYVEC_H

#define VECTOR_INIT_SIZE 8
#define VECTOR_GROWTH_RATE 1.5
#define VDATA void**

#include "soycore.h"

typedef struct tag_vectordata {
	VDATA data;
	unsigned int size;
	unsigned int count;
} vector;

flag soy_vector_resize(vector* vec, int size) {
	flag ret = UNDEF;
	if(vec) {
		VDATA newdata = (VDATA)realloc(vec->data, size*sizeof(void*));
		if(newdata) {
			vec->data = newdata;
			vec->size = size;
			ret = TRUE;
		}
	}
	return ret;
}

flag soy_vector_add(vector* vec, void* data) {
	flag ret = UNDEF;
	if(vec) {
		if(vec->size == vec->count) {
			ret = soy_vector_resize(vec, vec->size*VECTOR_GROWTH_RATE);
		}
		vec->data[vec->count] = data;
		vec->count++;
		ret = TRUE;
	}
	return ret;
}

flag soy_vector_set(vector* vec, unsigned int index, void* value) {
	flag ret = UNDEF;
	if(vec && vec->count > index && index > 0) {
		vec->data[index] = value;
		ret = TRUE;
	}
	return ret;
}

void* soy_vector_get(vector* vec, unsigned int index) {
	void* ret = NULL;
	if(vec && vec->count > index && index > 0) {
		ret = vec->data[index];
	}
	return ret;
}

flag soy_vector_delete(vector* vec, unsigned int index) {
	flag ret = UNDEF;
	if(vec && vec->count >= index) {
		vec->data[index] = NULL;
		ret = TRUE;
	}
	return ret;
}

flag soy_vector_shiftdelete(vector* vec, unsigned int index) {
	flag ret = UNDEF;
	unsigned int o = index;
	if(vec && vec->count >= index && vec->count > 0) {
		vec->data[index] = NULL;
		while(o < vec->count-1) {
			o++;
			vec->data[o] = vec->data[o+1];
			vec->data[o+1] = NULL;
		}
		vec->count--;
		if(vec->count == vec->size/4) {
			soy_vector_resize(vec, vec->size/2);
		}
		ret = TRUE;
	}
	return ret;
}

flag soy_vector_swapdelete(vector* vec, unsigned int index) {
	flag ret = UNDEF;
	void* temp = NULL;
	unsigned int end = vec->count-1;
	if(vec && vec->count >= index && vec->count > 0) {
		temp = vec->data[end];
		vec->data[end] = vec->data[index];
		vec->data[index] = temp;
		vec->data[end] = NULL;
		vec->count--;
		if(vec->count == vec->size/4) {
			soy_vector_resize(vec, vec->size/2);
		}
		ret = TRUE;
	}
	return ret;
}

flag soy_vector_free(vector* vec) {
	flag ret = UNDEF;
	if(vec) {
		free(vec->data);
		vec->data = NULL;
		ret = TRUE;
	}
	return ret;
}

unsigned int soy_vector_count(vector* vec) {
	return vec->count;
}

unsigned int soy_vector_total(vector* vec) {
	return vec->size;
}

flag soy_vector_new(vector* vec) {
	flag ret = UNDEF;
	vec->size = VECTOR_INIT_SIZE;
	vec->count = 0;
	vec->data = (VDATA)malloc(vec->size*sizeof(void*));
	if(vec->data) {
		ret = TRUE;
	}
	return ret;
}

#endif
