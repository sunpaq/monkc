
//
//  MCMap.c
//  Pods
//
//  Created by YuliSun on 01/06/2017.
//
//

#include "MCMap.h"

oninit(MCMap)
{
    if (init(MCObject)) {
        obj->table = new_table(MCHashTableLevel1);
        return obj;
    } else {
        return null;
    }
}

method(MCMap, void, setValueForKey, MCGeneric value, const char* key)
{
    mc_hashitem* item = new_item(key, value, hash(key));
    if (item) {
        set_item(&obj->table, item, false, "MCMap");
    }
}

method(MCMap, void, getValueForKey, MCGeneric* result, const char* key)
{
    mc_hashitem* item = get_item_bykey(obj->table, key);
    if (item) {
        (*result) = item->value;
        return;
    }
    (*result).mcvoidptr = null;
}

onload(MCMap)
{
    if (load(MCObject)) {
        binding(MCMap, void, setValueForKey, MCGeneric value, const char* key);
        binding(MCMap, void, getValueForKey, MCGeneric* result, const char* key);
        return cla;
    } else {
        return null;
    }
}
