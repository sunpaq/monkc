//
//  BirdBase.h
//  example
//
//  Created by sun yuli on 2015/02/12.
//  Copyright (c) 2015年 sun yuli. All rights reserved.
//

#ifndef example_BirdBase_h
#define example_BirdBase_h

#include "monkc.h"

monkc(LittleBirdBase);
	const char* commonName;
end(LittleBirdBase);

//abs
method(LittleBirdBase, void, land_abs, mo receiver);

#endif
