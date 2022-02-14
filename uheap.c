#include <stdio.h>
#include <stdlib.h>
#include "uheap.h"

DEFINE_HEAP_OF(int, int)

uint8_t cmp(int *a, int *b) {
	return *a > *b;
}

int main() {
	int_heap* iheap = int_heapInit(10, cmp);
	for (int i = 19; i >= 0; i--) {
	     int* a = malloc(sizeof(*a));
	     *a = i + 1;
	     int_heapPush(iheap, a);
	}

	printf("inner arr\n");
	for (int i = 0; i < 20; i++) {
	     printf("%d\n", *(iheap->arr[i]));
	}

	while(!int_heapIsEmpty(iheap)) {
	     printf("%d\n", *int_heapPop(iheap));
	}
}
