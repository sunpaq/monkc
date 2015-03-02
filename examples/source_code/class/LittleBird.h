//
//  Bird.h
//  MonkCAppXcodeTemplete
//
//  Created by sun yuli on 2015/01/13.
//  Copyright (c) 2015年 sun yuli. All rights reserved.
//

#ifndef MonkCAppXcodeTemplete_Bird_h
#define MonkCAppXcodeTemplete_Bird_h

#include "monkc.h"
#include "LittleBirdFather.h"
#include "LittleBirdBase.h"

monkc(LittleBird);
	LittleBirdBase* _LittleBirdBase;
	char* name;
end(LittleBird);

method(LittleBird, LittleBird*, initWithName, char* aname);
method(LittleBird, void, yourName, xxx);
method(LittleBird, void, fly, xxx);
method(LittleBird, void, swim, xxx);
method(LittleBird, void, eat, xxx);
method(LittleBird, void, hello_imp, xxx);
#endif
