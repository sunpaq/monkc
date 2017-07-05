//
//  MCHeap.c
//  Sapindus
//
//  Created by YuliSun on 17/11/2016.
//  Copyright © 2016 oreisoft. All rights reserved.
//

#include "MCHeap.h"

static size_t leftChildIndex(size_t i) {
    return i*2;
}

static size_t rightChildIndex(size_t i) {
    return i*2 + 1;
}

static size_t parentIndex(size_t i) {
    return i / 2;
}

static void swapNode(MCHeap* heap, size_t i, size_t j) {
    if (i <= heap->count && j <= heap->count) {
        MCGeneric temp = heap->values[i];
        heap->values[i] = heap->values[j];
        heap->values[j] = temp;
    }
}

static void shiftup(MCHeap* heap, size_t index)
{
    size_t i = index, p;
    while (1) {
        if (i == 1)
            break;
        p = parentIndex(i);
        if (MCGenericCompare(heap->values[p], heap->values[i]) <= 0)
            break;
        swapNode(heap, p, i);
        i = p;
    }
}

static void shiftdown(MCHeap* heap, size_t index)
{
    size_t i = index, l, r;
    while (1) {
        l = leftChildIndex(i);
        r = rightChildIndex(i);
        if (MCGenericCompare(heap->values[i], heap->values[l]) > 0) {
            swapNode(heap, i, l);
            i = l;
        }
        else if (MCGenericCompare(heap->values[i], heap->values[r]) > 0) {
            swapNode(heap, i, r);
            i = r;
        }else{
            break;
        }
    }
}

static MCGeneric deleteRoot(MCHeap* heap)
{
    MCGeneric root = heap->values[1];
    heap->values[1] = heap->values[heap->count];
    heap->count--;
    shiftdown(heap, 1);
    return root;
}

//static void printNode(MCHeap* heap, size_t index)
//{
//    int indent = (int)(heap->maxheight-(size_t)log2(index));
//    if (index == 1) {
//        printf("%*s%lf\n", (int)heap->maxheight, "", (float)heap->values[1].mcfloat);
//    }
//
//    size_t l = leftChildIndex(index);
//    size_t r = rightChildIndex(index);
//    
//    if (l <= heap->count && r <= heap->count) {
//        if (indent < 0) {
//            indent = 0;
//        }
//        printf("%*s%lf", indent, "", (float)heap->values[l].mcfloat);
//        printf("%*s%lf", indent+1, "", (float)heap->values[r].mcfloat);
//
//        size_t H = computed(heap, height) - 1;
//        
//        if (r == exp2(H) - 1) {
//            //edge
//            printf("\n");
//        }
//        
//        printNode(heap, l);
//        printNode(heap, r);
//    }
//    
//    //printf("%*s%d %d\n", indent, "", heap->values[L], heap->values[R]);
//}

compute(size_t, height)
{
    as(MCHeap);
    //log2(x) = log10(x) / log10(2)
    //log2(x) = logE(x) / logE(2)
    if (obj->count) {
        return (size_t)log2(obj->count);
    }
    return 0;
}

compute(size_t, width)
{
    as(MCHeap);
    size_t height = cpt(height);
    return (size_t)exp2(height-1);
}

oninit(MCHeap)
{
    if (init(MCObject)) {
        var(count) = 0;
        var(values) = null;
        var(height) = height;
        var(width) = width;
        return obj;
    }else{
        return null;
    }
}

method(MCHeap, void, bye, voida)
{
    if (obj->values) {
        free(obj->values);
    }
}

method(MCHeap, MCHeap*, initWithCopy, MCHeap* ref)
{
    MCHeap_initWithMaxcount(obj, ref->maxcount);
    memcpy(obj->values, ref->values, sizeof(MCGeneric) * ref->maxcount);
    obj->count = ref->count;
    return obj;
}

method(MCHeap, MCHeap*, initWithMaxcount, size_t maxcount)
{
    //index 0 is reserved
    obj->values = (MCGeneric*)malloc(sizeof(MCGeneric) * maxcount);
    obj->maxcount = maxcount;
    obj->maxheight = (size_t)log2(maxcount);
    return obj;
}

method(MCHeap, size_t, insertValue, MCGeneric newval)
{
    MCHeap* heap = obj;
    heap->values[++heap->count] = newval;
    shiftup(heap, heap->count);
    return 0;
}

method(MCHeap, MCArray*, copySortAscend, voida)
{
    MCHeap* hcopy = MCHeap_initWithCopy(new(MCHeap), obj);
    MCArray* array = MCArray_initWithMaxCount(new(MCArray), obj->maxcount);
    while (hcopy->count > 0) {
        MCArray_addItem(array, deleteRoot(hcopy));
    }
    release(hcopy);
    return array;
}

method(MCHeap, void, printAll, voida)
{
    for (int i=1; i<obj->count; i++) {
        printf("%.2f ", obj->values[i].mcfloat);
    }
    printf("\n");

    //printNode(heap, 1);
}

onload(MCHeap)
{
    if (load(MCObject)) {
        binding(MCHeap, void, bye, voida);
        binding(MCHeap, MCHeap*, initWithCopy, MCHeap* ref);
        binding(MCHeap, MCHeap*, initWithMaxcount, size_t maxcount);
        binding(MCHeap, size_t, insertValue, int newval);
        binding(MCHeap, MCArray*, copySortAscend, voida);
        binding(MCHeap, void, printAll, voida);
        return cla;
    } else {
        return null;
    }
}
