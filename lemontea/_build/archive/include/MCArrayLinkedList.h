//
//  MCArrayLinkedList.h
//  Sapindus
//
//  Created by YuliSun on 8/3/16.
//  Copyright © 2016 oreisoft. All rights reserved.
//

#ifndef MCArrayLinkedList_h
#define MCArrayLinkedList_h

#include "monkc.h"

//MC array linked list
typedef struct MCALItemStruct {
    struct MCALItemStruct* next;
    struct MCALItemStruct* prev;
    MCGeneric value;
    MCGeneric userdata;
} MCALItem;

MCInline MCALItem MCALItemMake(MCGeneric val)
{
    return (MCALItem){mull, mull, val};
}

MCInline void MCALItemLink(MCALItem* A, MCALItem* B)
{
    A->next = B;
    B->prev = A;
}

MCInline MCBool MCALItemIsHead(MCALItem* item)
{
    return (item->prev == mull);
}

MCInline MCBool MCALItemIsTail(MCALItem* item)
{
    return (item->next == mull);
}

#define MCArrayLinkedListMax 1024
typedef struct {
    MCBool isCircle;
    size_t count;
    size_t index;
    MCALItem* head;
    MCALItem array[MCArrayLinkedListMax];
} MCArrayLinkedList;

MCInline void MCALSetHead(MCArrayLinkedList* list, MCALItem* item)
{
    item->prev = mull;
    list->head = item;
}

MCInline void MCALSetTail(MCArrayLinkedList* list, MCALItem* item)
{
    item->next = mull;
}

MCInline MCBool MCALIsEmpty(MCArrayLinkedList* list)
{
    return (list->head == mull);
}

MCArrayLinkedList* MCArrayLinkedListInit(MCArrayLinkedList* list, MCGeneric values[], const size_t count);
MCArrayLinkedList* MCArrayLinkedListInitCircle(MCArrayLinkedList* list, MCGeneric values[], const size_t count);

MCALItem* MCALDeleteItem(MCArrayLinkedList* list, MCALItem* item);

#endif /* MCArrayLinkedList_h */
