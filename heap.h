#ifndef HEAP
#define HEAP
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct Heap_Level{
    int level;    
    int *data_array;
    struct Heap_Level *next_level;
    struct Heap_Level *prev_level;
} Heap_Level;

typedef struct Heap{
    struct Heap_Level *head;
    struct Heap_Level *insert_level;
    int insert_index;
} Heap;

Heap* create_heap();
int delete_heap(Heap *h);
int add(Heap *h, int data);
int pop(Heap *h);
int print_heap(Heap *h);

#endif
