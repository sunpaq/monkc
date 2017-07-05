//
//  MCBits.c
//  Sapindus
//
//  Created by Sun YuLi on 2016/12/4.
//  Copyright © 2016年 oreisoft. All rights reserved.
//

#include "MCBits.h"

MCBits MCBitsMask(MCUInt bitIndex)
{
    return (0x01 << bitIndex);
}

MCBool MCBitsIsSetAt(MCBits bits, MCUInt bitIndex)
{
    if (bits & MCBitsMask(bitIndex)) {
        return true;
    }
    return false;
}

MCUInt MCBitsSetBitNum(MCBits bits) {
    MCBits mask = 0x01;
    unsigned bitsCount = sizeof(MCBits) * 8;
    
    unsigned i, count=0;
    for(i=0; i<bitsCount; i++) {
        if((bits & mask) != 0)
            count++;
        mask <<= 1;
    }
    
    return count;
}

MCBits MCBitsXORFindOddInPairs(const MCBits* pairs, size_t count) {
    MCBits xor = 0;
    for (int i=0; i<count; i++) {
        xor = xor^pairs[i];
    }
    return xor;
}
