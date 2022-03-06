# universal-heap
I needed a generic heap in c, so I decided to create this small heap library.
Implementing heap is done by a macro which generate code for heap structure and its functions.

Example usage: 
```c
// DEFINE_HEAP_OF(data_type, functions_prefix)
DEFINE_HEAP_OF(int, myInt)
```

What will generate:
```c
typedef struct myInt_heap_t {
  ...
} myInt_heap;

myInt_heap *myInt_heapInit(uint32_t max_size, uint8_t(*cmp) (int *, int *)) { ... }
void myInt_heapPush(myInt_heap * self, int *value) { ... }
int *myInt_heapPop(myInt_heap * self) { ... }
uint8_t myInt_heapIsFull(myInt_heap * self) { ... }
uint8_t myInt_heapIsEmpty(myInt_heap * self) { ... }

// and some helper functions

```
When using:
```c
uint8_t myCmp(int *a, int *b) {
  ...
}
// ...
// when creating your own heap you need to pass comparator funcion
myInt* heap = myInt_heapInit(10, myCmp);
// ...
```
