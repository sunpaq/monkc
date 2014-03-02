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
    hinding(BirdBase, void, land_abs, 2677951518, xxx);
    return claz;
}

//abs
method(BirdBase, void, land_abs, mo receiver)
{
    fh(receiver,land_imp, 2677959544, nil);
}