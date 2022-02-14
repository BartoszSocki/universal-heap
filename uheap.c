#include <stdio.h>
#include <stdlib.h>
#include "uheap.h"

DEFINE_HEAP_OF(int, int)

uint8_t cmp(void* a, void* b) {
	return *(int*)a > *(int*)b;
}

int main() {
	int_heap* iheap = int_heapInit(3, cmp);
	for (int i = 0; i < 30; i++) {
		int* a = malloc(sizeof(*a));
		*a = i + 1;
		int_heapPush(iheap, a);
	}
	for (int i = 0; i < 30; i++) {
		printf("%d\n", *(iheap->arr[i]));
	}
}
