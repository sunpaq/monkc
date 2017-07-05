//
//  MCLinkedList.c
//  Sapindus
//
//  Created by Sun YuLi on 16/6/1.
//  Copyright © 2016年 oreisoft. All rights reserved.
//

#include "MCLinkedList.h"

/*
 Floyd Cycle Detection (Tortoise and Hare)
 Ot(Nl+Nc) -> fast only go max one loop
 Os(1)
 */

static int detectCycle(MCItem* A, MCItem** start) {
    MCItem *slow = A, *fast = A;
    int slowstep = 0, iscycle = 0;
    while(slow && fast && fast->nextItem) {
        slow = slow->nextItem;
        fast = fast->nextItem->nextItem;
        slowstep++;
        if(slow == fast) {
            iscycle = 1;
            break;
        }
    }
    if(iscycle == 0) {
        start = NULL;
        return 0;
    }
    
    slow = A;
    while(slow!=fast) {
        slow = slow->nextItem;
        fast = fast->nextItem;
    }
    
    *start = slow;
    return slowstep;
}

//MCItem

oninit(MCItem)
{
    if (init(MCObject)) {
        var(value) = MCGenericVp(null);
        var(object)   = null;
        var(prevItem) = null;
        var(nextItem) = null;
        return obj;
    }else{
        return null;
    }
}

method(MCItem, void, bye, voida)
{
    release(obj->object);
}

method(MCItem, MCItem*, initWithContentObject, MCObject* content)
{
    var(object) = content;
    retain(content);
    return obj;
}

method(MCItem, void, linkNextItem, MCItem* next)
{
    var(nextItem) = next;
    next->prevItem = obj;
}

method(MCItem, void, linkPrevItem, MCItem* prev)
{
    var(prevItem) = prev;
    prev->nextItem = obj;
}

onload(MCItem)
{
    if (load(MCObject)) {
        binding(MCItem, void, bye, voida);
        binding(MCItem, MCItem*, initWithContentObject, MCObject* content);
        binding(MCItem, void, linkNextItem, MCItem* next);
        binding(MCItem, void, linkPrevItem, MCItem* prev);
        return cla;
    }else{
        return null;
    }
}

utility(MCItem, MCItem*, itemWithObject, MCObject* content)
{
    return MCItem_initWithContentObject(new(MCItem), content);
}

//MCLinkedList

compute(unsigned, getCount)
{
    as(MCLinkedList);
    if (var(countChanged) == true) {
        int i = 0;
        MCItem* iter = var(headItem);
        while (iter != null) {
            iter = iter->nextItem;
            i++;
        }
        var(countChanged) = false;
        var(countCache) = i;
        return i;
    }else{
        return var(countCache);
    }
}

compute(MCItem*, cycleStart)
{
    as(MCLinkedList);
    MCItem* start = null;
    detectCycle(obj->headItem, &start);
    if (start) {
        return start;
    }
    return null;
}

oninit(MCLinkedList)
{
    if (init(MCObject)) {
        var(headItem) = null;
        var(tailItem) = var(headItem);
        
        var(countChanged) = true;
        var(countCache) = 0;
        var(count) = getCount;
        var(cycle) = cycleStart;
        return obj;
    }else{
        return null;
    }
}

method(MCLinkedList, void, bye, voida)
{
    MCLinkedListForEach(obj,
        release(item);
    );
}

method(MCLinkedList, void, addItem, MCItem* item)
{
    if (item != null) {
        var(countChanged) = true;
        if (var(tailItem) == null) {
            var(tailItem) = item;
            var(headItem) = item;
        }else{
            MCItem_linkNextItem(var(tailItem), item);
            var(tailItem) = item;
        }
    }
}

method(MCLinkedList, void, delItem, MCItem* item)
{
    if (item != null) {
        var(countChanged) = true;
        if (item == var(headItem)) {
            var(headItem) = null;
            var(tailItem) = null;
            release(item);
        }
        else if (item == var(tailItem)){
            MCItem* tail = var(tailItem)->prevItem;
            tail->nextItem = null;
            release(var(tailItem));
            var(tailItem) = tail;
        }
        else {
            MCItem* prev = item->prevItem;
            MCItem* next = item->nextItem;
            MCItem_linkNextItem(prev, next);
            release(item);
        }
    }
}

method(MCLinkedList, void, addAndRetainObject, MCObject* object)
{
    MCLinkedList_addItem(obj, MCItem_itemWithObject(object));
}

method(MCLinkedList, void, pushItem, MCItem* item)
{
    MCLinkedList_addItem(obj, item);
}

method(MCLinkedList, MCItem*, popItem, voida)
{
    if (cpt(count) > 0 && var(headItem)) {
        MCLinkedList_delItem(obj, var(headItem));
        return var(headItem);
    }
    return null;
}

method(MCLinkedList, void, insertAfterItem, MCItem* anchor, MCItem* item)
{
    if (anchor != null && item != null) {
        var(countChanged) = true;
        MCItem* next = anchor->nextItem;
        MCItem_linkNextItem(anchor, item);
        MCItem_linkNextItem(item, next);
    }
}

method(MCLinkedList, void, insertBeforeItem, MCItem* anchor, MCItem* item)
{
    if (anchor != null && item != null) {
        var(countChanged) = true;
        MCItem* prev = anchor->prevItem;
        MCItem_linkPrevItem(anchor, item);
        MCItem_linkPrevItem(item, prev);
    }
}

method(MCLinkedList, MCLinkedList*, connectList, MCLinkedList* otherlist)
{
    retain(otherlist);
    MCItem_linkNextItem(var(tailItem), otherlist->headItem);
    return obj;
}

method(MCLinkedList, void, forEach, mc_message callback, void* userdata)
{
    MCItem* item = obj->headItem;
    while (item != null) {
        _push_jump(response_to(callback.object, callback.message), item, userdata);
        item = item->nextItem;
    }
}

method(MCLinkedList, MCItem*, itemAtIndex, int index)
{
    MCItem* item = obj->headItem;
    int i = 0;
    while (item != null) {
        if (index == i) {
            return item;
        }
        item = item->nextItem;
        i++;
    }
    return null;
}

method(MCLinkedList, void, replaceItemAtIndex, int index, MCItem* withitem)
{
    MCItem* item = MCLinkedList_itemAtIndex(obj, index);
    if (item) {
        withitem->prevItem = item->prevItem;
        withitem->nextItem = item->nextItem;
        release(item);
    }
}

method(MCLinkedList, void, addItemAtIndex, int index, MCItem* item)
{
    MCItem* iter = obj->headItem;
    //build list until reach index
    int i = 0;
    while (i < index) {
        if (iter) {
            if (iter->nextItem == null) {
                MCItem* item = new(MCItem);
                MCLinkedList_pushItem(obj, item);
            }
            iter = iter->nextItem;
        }
        i++;
    }
    //replace the item at index
    MCLinkedList_replaceItemAtIndex(obj, index, item);
}

onload(MCLinkedList)
{
    if (load(MCObject)) {
        binding(MCLinkedList, void, bye, voida);
        binding(MCLinkedList, void, addItem, MCItem* item);
        binding(MCLinkedList, void, delItem, MCItem* item);
        binding(MCLinkedList, void, addAndRetainObject, MCObject* object);
        binding(MCLinkedList, void, pushItem, MCItem* item);
        binding(MCLinkedList, MCItem*, popItem, voida);
        binding(MCLinkedList, void, insertAfterItem, MCItem* anchor, MCItem* item);
        binding(MCLinkedList, void, insertBeforeItem, MCItem* anchor, MCItem* item);
        binding(MCLinkedList, MCLinkedList*, connectList, MCLinkedList* otherlist);
        binding(MCLinkedList, void, forEach, mc_message callback, void* userdata);
        binding(MCLinkedList, MCItem*, itemAtIndex, int index);
        binding(MCLinkedList, void, addItemAtIndex, int index, MCItem* item);
        binding(MCLinkedList, void, replaceItemAtIndex, int index, MCItem* withitem);
        return cla;
    }else{
        return null;
    }
}



