//
//  BirdBase.c
//  example
//
//  Created by sun yuli on 2015/02/12.
//  Copyright (c) 2015年 sun yuli. All rights reserved.
//

#include "LittleBirdBase.h"

initer(LittleBirdBase)
{
    obj->super = nil;
    obj->commonName = "Bird";
    return obj;
}

loader(LittleBirdBase)
{
    binding(LittleBirdBase, void, land_abs, xxx);
    return claz;
}

//abs
method(LittleBirdBase, void, land_abs, mo receiver)
{
    ff(receiver, land_imp, nil);
}