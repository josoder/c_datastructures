//
// Created by josoder on 23.10.17.
//
#include <assert.h>
#include "../interfaces/min_heap.h"
#include "min_heap_test.h"

void MinHeapTest(){
    TestCreate();
    TestInsert();
}

void TestCreate(){
    min_heap* m = CreateMinHeap(5);
    assert(m!=NULL);
    DestroyMinHeap(m);
}

void TestInsert(){
    min_heap* m = CreateMinHeap(2);
    assert(m!=NULL);
    MinHeapInsert(m, 2);
    assert(m->heapSize == 1);
}

void TestGetMin() {
    min_heap* m = CreateMinHeap(20);
    for (int i = 0; i<20; i++){
        MinHeapInsert(m, i);
    }

    assert(GetMin(m) == 0);
    int i = ExtractMin(m);
    assert(i == 0);
    assert(m->heapSize = 19);
}
