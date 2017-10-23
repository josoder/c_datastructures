//
// Created by josoder on 23.10.17.
// This is a c adaption of the implementation at : http://www.geeksforgeeks.org/binary-heap/

#include "../interfaces/min_heap.h"

min_heap* CreateMinHeap(int capacity){
    min_heap* mh = (min_heap*) malloc(sizeof(min_heap));
    mh->heapArray = (int*) malloc(capacity*sizeof(int));
    mh->heapSize = 0;
    mh->capacity = capacity;
    mh->heapSize = 0;
}

void MinHeapInsert(min_heap* mh, int k){
    if(mh->heapSize==mh->capacity){
        puts("overflow, reached capacity");
        return;
    }

    mh->heapSize++;
    int i = mh->heapSize -1;
    mh->heapArray[i] = k;

    // Fix the heap if property(no child node is greater than its parent) is violated.
    while(i != 0 && mh->heapArray[Parent(i)] > mh->heapArray[i]){
        Swap(&mh->heapArray[i], &mh->heapArray[Parent(i)]);
        i = Parent(i);
    }
}

int ExtractMin(min_heap* mh){
    if(mh->heapSize==0){
        puts("no elements int heap..");
        return INT_MAX;
    }
    if(mh->heapSize == 1){
        mh->heapSize--;
        return mh->heapArray[0];
    }

    int root = mh->heapArray[0];
    mh->heapArray[0] = mh->heapArray[mh->heapSize-1];
    MinHeapify(mh, 0);
}

void DestroyMinHeap(min_heap* mh){
    free(mh->heapArray);

    free(mh);
    mh = NULL;
}

int GetMin(min_heap * mh){
    return mh->heapArray[0];
}

void MinHeapify(min_heap* mh ,int i){
    int l = Left(i);
    int r = Right(i);
    int smallest = i;

    if(l < mh->heapSize && mh->heapArray[l] < mh->heapArray[i]) {
        smallest = l;
    }
    if(r< mh->heapSize && mh->heapArray[r] < mh->heapArray[smallest]){
        smallest = r;
    }
    if(smallest != i)
    {
        Swap(&mh->heapArray[i], &mh->heapArray[smallest]);
        MinHeapify(mh ,smallest);
    }

}

// Util

int Parent(int i){
    return (i-1)/2;
}

int Left(int i){
    return i*2+1;
}

int Right(int i){
    return i*2+2;
}

void Swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}