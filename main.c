#include <stdio.h>
#include <stdlib.h>
#include "uheap.h"

struct point_t {
	int x, y;
};

/* first goes type; then prefix of functions */
/* so function will look like this prefix##_heapSomething(type* self, ...) */
DEFINE_HEAP_OF(struct point_t, point)
DEFINE_HEAP_OF(int, int)

/* furthest to (0; 0) */
uint8_t furthestPoint(struct point_t* a, struct point_t* b) {
	int da = a->x * a->x + a->y * a->y;
	int db = b->x * b->x + b->y * b->y;
	return da > db;
}

uint8_t greatestInt(int *a, int *b) {
	return *a > *b;
}

int main() {
	/* when creating a heap you need to pass cmp function */
	point_heap* heap = point_heapInit(10, furthestPoint);

	for (int i = 0; i < 10; i++) {
		struct point_t* point = malloc(sizeof(*point));
		point->x = i;
		point->y = i * i;
		point_heapPush(heap, point);
	}

	for (int i = 0; i < 4; i++) {
		/* after you pop from heap remember to free memory */
		struct point_t* point = point_heapPop(heap);
		printf("(%d; %d)\n", point->x, point->y);
		free(point);
	}

	printf("is heap empty?: %s\n", point_heapIsEmpty(heap) == 1 ? "true" : "false");
	printf("is heap full?: %s\n", point_heapIsFull(heap) == 1 ? "true" : "false");

	/* memory deallocation is not supported, you need to take care of that*/
	while(!point_heapIsEmpty(heap)) {
		free(point_heapPop(heap));
	}
	free(heap);

	/* example with int max heap */
	int_heap* iheap = int_heapInit(10, greatestInt);
	for (int i = 19; i >= 0; i--) {
	     int* a = malloc(sizeof(*a));
	     *a = i + 1;
	     int_heapPush(iheap, a);
	}

	while(!int_heapIsEmpty(iheap)) {
		int* value = int_heapPop(iheap);
		printf("%2d ", *value);
		free(value);
	}
	putchar('\n');
	free(iheap);
}
