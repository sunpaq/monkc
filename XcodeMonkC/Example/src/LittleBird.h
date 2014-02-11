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

monkc(LittleBird);
char* name;
end(LittleBird);

method(LittleBird, LittleBird*, initWithName, char* aname);
method(LittleBird, void, yourName, xxx);
method(LittleBird, void, fly, xxx);
method(LittleBird, void, swim, xxx);
method(LittleBird, void, eat, xxx);
//implement abs
method(LittleBird, void, myHello, xxx);
#endif
