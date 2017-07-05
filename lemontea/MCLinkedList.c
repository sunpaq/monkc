//
//  MCLinkedList.c
//  Sapindus
//
//  Created by Sun YuLi on 16/6/1.
//  Copyright © 2016年 oreisoft. All rights reserved.
//

#include "MCLinkedList.h"

//MCItem

oninit(MCItem)
{
    if (init(MCObject)) {
        var(prevItem) = mull;
        var(nextItem) = mull;
        return obj;
    }else{
        return mull;
    }
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
        binding(MCItem, void, linkNextItem, MCItem* next);
        binding(MCItem, void, linkPrevItem, MCItem* prev);
        return cla;
    }else{
        return mull;
    }
}

//MCLinkedList

compute(unsigned, getCount)
{
    as(MCLinkedList);
    if (var(countChanged) == MCTrue) {
        int i = 0;
        MCItem* iter = var(headItem);
        while (iter != mull) {
            iter = iter->nextItem;
            i++;
        }
        var(countChanged) = MCFalse;
        return i;
    }else{
        return var(countCache);
    }
}

oninit(MCLinkedList)
{
    if (init(MCObject)) {
        var(headItem) = mull;
        var(tailItem) = var(headItem);
        
        var(countChanged) = MCTrue;
        var(countCache) = 0;
        var(count) = getCount;
        return obj;
    }else{
        return mull;
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
    if (item != mull) {
        var(countChanged) = MCTrue;
        if (var(tailItem) == mull) {
            var(tailItem) = item;
            var(headItem) = item;
        }else{
            MCItem_linkNextItem(0, var(tailItem), item);
            var(tailItem) = item;
        }
    }
}

method(MCLinkedList, void, delItem, MCItem* item)
{
    if (item != mull) {
        var(countChanged) = MCTrue;
        if (item == var(headItem)) {
            var(headItem) = mull;
            var(tailItem) = mull;
            release(item);
        }
        else if (item == var(tailItem)){
            MCItem* tail = var(tailItem)->prevItem;
            tail->nextItem = mull;
            release(var(tailItem));
            var(tailItem) = tail;
        }
        else {
            MCItem* prev = item->prevItem;
            MCItem* next = item->nextItem;
            MCItem_linkNextItem(0, prev, next);
            release(item);
        }
    }
}

method(MCLinkedList, void, insertAfterItem, MCItem* anchor, MCItem* item)
{
    if (anchor != mull && item != mull) {
        var(countChanged) = MCTrue;
        MCItem* next = anchor->nextItem;
        MCItem_linkNextItem(0, anchor, item);
        MCItem_linkNextItem(0, item, next);
    }
}

method(MCLinkedList, void, insertBeforeItem, MCItem* anchor, MCItem* item)
{
    if (anchor != mull && item != mull) {
        var(countChanged) = MCTrue;
        MCItem* prev = anchor->prevItem;
        MCItem_linkPrevItem(0, anchor, item);
        MCItem_linkPrevItem(0, item, prev);
    }
}

method(MCLinkedList, MCLinkedList*, connectList, MCLinkedList* otherlist)
{
    retain(otherlist);
    MCItem_linkNextItem(0, var(tailItem), otherlist->headItem);
    return obj;
}

method(MCLinkedList, void, forEach, mc_message callback, void* userdata)
{
    MCItem* item = obj->headItem;
    while (item != mull) {
        _push_jump(callback, item, userdata);
        item = item->nextItem;
    }
}

onload(MCLinkedList)
{
    if (load(MCObject)) {
        binding(MCLinkedList, void, bye, voida);
        binding(MCLinkedList, void, addItem, MCItem* item);
        binding(MCLinkedList, void, delItem, MCItem* item);
        binding(MCLinkedList, void, insertAfterItem, MCItem* anchor, MCItem* item);
        binding(MCLinkedList, void, insertBeforeItem, MCItem* anchor, MCItem* item);
        binding(MCLinkedList, MCLinkedList*, connectList, MCLinkedList* otherlist);
        binding(MCLinkedList, void, forEach, mc_message callback, void* userdata);
        return cla;
    }else{
        return mull;
    }
}



