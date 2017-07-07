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
      MCGeneric value;
      MCObject* object;
      struct MCItemStruct* prevItem;
      struct MCItemStruct* nextItem);

method(MCItem, void, bye, voida);
method(MCItem, MCItem*, initWithContentObject, MCObject* content);
method(MCItem, void, linkNextItem, MCItem* next);
method(MCItem, void, linkPrevItem, MCItem* prev);

utility(MCItem, MCItem*, itemWithObject, MCObject* content);

//List

class(MCLinkedList, MCObject,
      MCItem* headItem;
      MCItem* tailItem;
      
      MCBool countChanged;
      unsigned countCache;
      computing(unsigned, count);
      computing(MCItem*, cycle));

method(MCLinkedList, void, bye, voida);
method(MCLinkedList, void, addItem, MCItem* item);
method(MCLinkedList, void, delItem, MCItem* item);
method(MCLinkedList, void, addAndRetainObject, MCObject* object);
method(MCLinkedList, void, pushItem, MCItem* item);
method(MCLinkedList, MCItem*, popItem, voida);
method(MCLinkedList, MCItem*, itemAtIndex, int index);
method(MCLinkedList, void, addItemAtIndex, int index, MCItem* item);
method(MCLinkedList, void, replaceItemAtIndex, int index, MCItem* withitem);
method(MCLinkedList, void, insertAfterItem, MCItem* anchor, MCItem* item);
method(MCLinkedList, void, insertBeforeItem, MCItem* anchor, MCItem* item);
method(MCLinkedList, MCLinkedList*, connectList, MCLinkedList* otherlist);
method(MCLinkedList, void, forEach, mc_message callback, void* userdata);

#define MCLinkedListForEach(list, code) \
{MCItem* item = list->headItem;         \
while (item != null) {                  \
    code                                \
    item = item->nextItem;              \
}}

#endif /* MCLinkedList_h */
