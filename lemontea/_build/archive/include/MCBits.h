//
//  MCBits.h
//  Sapindus
//
//  Created by Sun YuLi on 2016/12/4.
//  Copyright © 2016年 oreisoft. All rights reserved.
//

#ifndef MCBits_h
#define MCBits_h

#include "monkc.h"

typedef unsigned MCBits;

MCBits MCBitsMask(MCUInt bitIndex);
MCBool MCBitsIsSetAt(MCBits bits, MCUInt bitIndex);
MCUInt MCBitsSetBitNum(MCBits bits);
MCBits MCBitsXORFindOddInPairs(const MCBits* pairs, size_t count);

#endif /* MCBits_h */
