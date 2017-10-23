//
// Created by josoder on 23.10.17.
// This is a c adaption of the implementation at : http://www.geeksforgeeks.org/binary-heap/
//

#ifndef DATASTRUCTURES_MIN_HEAP_H
#define DATASTRUCTURES_MIN_HEAP_H

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

typedef struct min_heap {
    int *heapArray;
    int capacity;
    int heapSize;
} min_heap;

min_heap* CreateMinHeap(int capacity);

void MinHeapify(min_heap* mh ,int i);

int ExtractMin(min_heap* mh);

int GetMin(min_heap* mh);

void MinHeapInsert(min_heap* mh, int k);

void DestroyMinHeap(min_heap* mh);

#endif //DATASTRUCTURES_MIN_HEAP_H
