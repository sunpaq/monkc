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
    return (MCALItem){null, null, val};
}

MCInline void MCALItemLink(MCALItem* A, MCALItem* B)
{
    A->next = B;
    B->prev = A;
}

MCInline MCBool MCALItemIsHead(MCALItem* item)
{
    return (item->prev == null);
}

MCInline MCBool MCALItemIsTail(MCALItem* item)
{
    return (item->next == null);
}

#define MCArrayLinkedListMax 1024
typedef struct {
    MCBool isCircle;
    size_t count;
    MCALItem* head;
    MCALItem array[MCArrayLinkedListMax];
} MCArrayLinkedList;

MCInline void MCALSetHead(MCArrayLinkedList* list, MCALItem* item)
{
    item->prev = null;
    list->head = item;
}

MCInline void MCALSetTail(MCArrayLinkedList* list, MCALItem* item)
{
    item->next = null;
}

MCInline MCBool MCALIsEmpty(MCArrayLinkedList* list)
{
    return (list->head == null);
}

MCArrayLinkedList* MCArrayLinkedListInit(MCArrayLinkedList* list, MCGeneric values[], const size_t count);
MCArrayLinkedList* MCArrayLinkedListInitCircle(MCArrayLinkedList* list, MCGeneric values[], const size_t count);

MCALItem* MCALDeleteItem(MCArrayLinkedList* list, MCALItem* item);


typedef struct {
    MCGeneric data[MCArrayLinkedListMax];
    int nexti[MCArrayLinkedListMax];
    int previ[MCArrayLinkedListMax];
    int count;
} MCArrayList;

MCArrayList* MCArrayListInit(MCArrayList* list);
MCArrayList* MCArrayListAdd(MCArrayList* list, MCGeneric data);


#endif /* MCArrayLinkedList_h */
