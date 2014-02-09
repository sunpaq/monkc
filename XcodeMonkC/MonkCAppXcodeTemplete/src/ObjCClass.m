//
//  ObjCClass.m
//  MonkCAppXcodeTemplete
//
//  Created by sun yuli on 2014/02/09.
//  Copyright (c) 2014年 sun yuli. All rights reserved.
//

#import "ObjCClass.h"
#import "Bird.h"

@implementation ObjCClass

-(void) callMonkCMethod
{
    Bird* abird = ff(new(Bird), initWithName, "fat bird");
    printf("my name is: %s\n", abird->name);
    ff(abird, fly, nil);
    
    release(abird);
}

@end
