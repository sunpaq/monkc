//
//  ObjCClass.m
//  MonkCAppXcodeTemplete
//
//  Created by sun yuli on 2014/02/09.
//  Copyright (c) 2014年 sun yuli. All rights reserved.
//

#import "ObjCClass.h"
#import "LittleBird.h"

@implementation ObjCClass

-(void) callMonkCMethod
{
    LittleBird* abird = ff(new(LittleBird), initWithName, "fat bird");
    printf("my name is: %s\n", abird->name);
    ff(abird, fly, nil);
    
    release(abird);
}

@end
