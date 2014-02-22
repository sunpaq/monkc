//
//  BirdBase.c
//  example
//
//  Created by sun yuli on 2014/02/12.
//  Copyright (c) 2014年 sun yuli. All rights reserved.
//

#include "BirdBase.h"

initer(BirdBase)
{
    return obj;
}

loader(BirdBase)
{
    binding(BirdBase, void, land_abs, mo receiver);
    return claz;
}

//abs
method(BirdBase, void, land_abs, mo receiver)
{
    ff(receiver, land_imp, nil);
}