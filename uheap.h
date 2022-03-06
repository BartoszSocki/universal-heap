#ifndef _UHEAP_IS_INCLUDED_
#define _UHEAP_IS_INCLUDED_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


#define DEFINE_HEAP_OF(type, prefix) \
typedef struct prefix##_heap_t { \
	type** arr; \
	uint32_t max_size; \
	uint32_t cur_size; \
	uint8_t (*cmp)(type*, type*); \
} prefix##_heap; \
\
static void _##prefix##_swap(type** a, type** b) { \
	type* tmp = *a; \
	*a = *b; \
	*b = tmp; \
} \
static void _##prefix##_heapify(prefix##_heap* self, uint32_t cur_size, uint32_t i) { \
	if (self->arr == NULL) \
		abort(); \
	\
	uint32_t elem_index = i; \
	uint32_t left = 2 * i + 1; \
	uint32_t right = 2 * i + 2; \
	\
	if (left < cur_size && self->cmp(self->arr[left], self->arr[elem_index])) { \
		elem_index = left; \
	} \
	if (right < cur_size && self->cmp(self->arr[right], self->arr[elem_index])) { \
		elem_index = right; \
	} \
	\
	if (elem_index != i) { \
		_##prefix##_swap(&self->arr[i], &self->arr[elem_index]); \
		_##prefix##_heapify(self, cur_size, elem_index); \
	} \
} \
prefix##_heap* prefix##_heapInit(uint32_t max_size, uint8_t (*cmp)(type*, type*)) { \
	if (max_size == 0) \
		return NULL; \
	\
	prefix##_heap* self = malloc(sizeof(*self)); \
	self->arr = malloc(max_size * sizeof(*(self->arr))); \
	self->max_size = max_size; \
	self->cur_size = 0; \
	self->cmp = cmp; \
	\
	return self; \
} \
uint8_t prefix##_heapIsFull(prefix##_heap* self) { \
	return self->cur_size == self->max_size; \
} \
uint8_t prefix##_heapIsEmpty(prefix##_heap* self) { \
	return self->cur_size == 0; \
} \
static uint8_t _##prefix##_heapDoubleMaxSizeFailed(prefix##_heap* self) { \
	if (self == NULL || self->arr == NULL) \
		abort(); \
	\
	type** arr = realloc(self->arr, sizeof(*(self->arr)) * (self->max_size << 1)); \
	if (arr == NULL) \
		return 1; \
	self->max_size <<= 1; \
	self->arr = arr; \
	\
	return 0; \
} \
void prefix##_heapPush(prefix##_heap* self, type* value) { \
	if (self == NULL || self->arr == NULL) \
		abort(); \
	if (prefix##_heapIsFull(self)) \
		if (_##prefix##_heapDoubleMaxSizeFailed(self)) \
			abort(); \
	\
	uint32_t child = self->cur_size; \
	\
	self->arr[child] = value; \
	while (child > 0 && self->cmp(self->arr[child], self->arr[child >> 1])) { \
		_##prefix##_swap(&self->arr[child], &self->arr[child >> 1]); \
		child >>= 1; \
	} \
	self->cur_size += 1; \
} \
type* prefix##_heapPop(prefix##_heap* self) { \
	if (self == NULL || self->arr == NULL || prefix##_heapIsEmpty(self)) \
		abort(); \
	\
	type* value = self->arr[0]; \
	\
	self->cur_size -= 1; \
	self->arr[0] = self->arr[self->cur_size]; \
	_##prefix##_heapify(self, self->cur_size, 0); \
	\
	return value; \
}

#endif
