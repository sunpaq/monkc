//
//  MCSort.h
//  Sapindus
//
//  Created by Sun YuLi on 2016/11/5.
//  Copyright © 2016年 oreisoft. All rights reserved.
//

#ifndef MCSort_h
#define MCSort_h

#include "monkc.h"

class(MCSort, MCObject,
      MCGeneric* array;
      size_t length);

method(MCSort, void, bye, voida);
method(MCSort, MCSort*, initWithArray, MCGeneric* array, size_t length);
method(MCSort, void, insertionSort, voida);
method(MCSort, void, quickSort, voida);
method(MCSort, void, printArray, voida);

#endif /* MCSort_h */
