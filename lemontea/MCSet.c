//
//  MCSet.c
//  Sapindus
//
//  Created by Sun YuLi on 2016/11/12.
//  Copyright © 2016年 oreisoft. All rights reserved.
//

#include "MCSet.h"

//class(MCSet, MCObject,
//      MCGeneric* values;
//      size_t maxcount);

oninit(MCSet)
{
    if (init(MCObject)) {
        var(values) = null;
        var(maxcount) = 0;
        var(count) = 0;
        return obj;
    } else {
        return null;
    }
}

method(MCSet, void, bye, voida)
{
    if (var(values)) {
        free(var(values));
    }
}

method(MCSet, MCSet*, initWithMaxCount, size_t maxcount)
{
    var(values) = (MCGeneric*)malloc(sizeof(MCGeneric)*maxcount);
    var(maxcount) = maxcount;
    return obj;
}

method(MCSet, MCSet*, insertValue, MCGeneric value)
{
    if (obj->count < obj->maxcount) {
        obj->values[obj->count++] = value;
    }
    return obj;
}

onload(MCSet)
{
    if (load(MCObject)) {
        binding(MCSet, void, bye, voida);
        binding(MCSet, MCSet*, initWithMaxCount, size_t maxcount);
        binding(MCSet, MCSet*, insertValue, MCGeneric value);
        return cla;
    } else {
        return null;
    }
}
