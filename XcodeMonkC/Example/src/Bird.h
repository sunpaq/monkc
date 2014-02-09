//
//  Bird.h
//  MonkCAppXcodeTemplete
//
//  Created by sun yuli on 2014/01/13.
//  Copyright (c) 2014年 sun yuli. All rights reserved.
//

#ifndef MonkCAppXcodeTemplete_Bird_h
#define MonkCAppXcodeTemplete_Bird_h

#include "monkc.h"

monkc(Bird);
char* name;
end(Bird);

method(Bird, Bird*, initWithName, char* aname);
method(Bird, void, yourName, xxx);
method(Bird, void, fly, xxx);
method(Bird, void, swim, xxx);
method(Bird, void, eat, xxx);

#endif
