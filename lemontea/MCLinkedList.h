//
//  MCLinkedList.h
//  Sapindus
//
//  Created by Sun YuLi on 16/6/1.
//  Copyright © 2016年 oreisoft. All rights reserved.
//

#ifndef MCLinkedList_h
#define MCLinkedList_h

#include <stdio.h>
#include "MCContext.h"

//Item

class(MCItem, MCObject,
      struct MCItemStruct* prevItem;
      struct MCItemStruct* nextItem)

method(MCItem, void, linkNextItem, MCItem* next);
method(MCItem, void, linkPrevItem, MCItem* prev);

//List

class(MCLinkedList, MCObject,
      MCItem* headItem;
      MCItem* tailItem;
      
      MCBool countChanged;
      unsigned countCache;
      computing(unsigned, count))

method(MCLinkedList, void, bye, voida);
method(MCLinkedList, void, addItem, MCItem* item);
method(MCLinkedList, void, delItem, MCItem* item);
method(MCLinkedList, void, insertAfterItem, MCItem* anchor, MCItem* item);
method(MCLinkedList, void, insertBeforeItem, MCItem* anchor, MCItem* item);
method(MCLinkedList, MCLinkedList*, connectList, MCLinkedList* otherlist);
method(MCLinkedList, void, forEach, mc_message callback, void* userdata);

#define MCLinkedListForEach(list, code) \
{MCItem* item = list->headItem;         \
while (item != mull) {                  \
    code                                \
    item = item->nextItem;              \
}}

#endif /* MCLinkedList_h */
