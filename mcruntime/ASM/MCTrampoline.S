//
//  MCRuntimeAsmIOS.s
//  monkcGame
//
//  Created by SunYuLi on 5/21/15.
//  Copyright (c) 2015-2016 oreisoft. All rights reserved.
//

/*
 ABI links:
 https://developer.apple.com/library/ios/documentation/Xcode/Conceptual/iPhoneOSABIReference/Articles/ARM64FunctionCallingConventions.html
 
 infos about ARM 32 platform (armv6 armv7):
 
 stack-align: 	method(8byte) non-method(4byte)
 frame-pointer:  fp is r11 in ARM mode / r7 in thumb mode
 keep-fp:		-mapcs-frame will keep the fp not to be optimized out
 
 iOS exception:
 stack-align: 	method(4byte)

 infos about ARM 64 platform (arm64):
 
 stack-align: 	public (16byte) non-public (16byte)
 frame-pointer: 	fp is r11 in ARM mode / r7 in thumb mode
 keep-fp:		-mapcs-frame will keep the fp not to be optimized out
 
 r0 r1 r2 r3 r4 r5 r6 r7 r8 r9 r10 r11   r30
 w0 w1 w2 w3 w4 w5 w6 w7 w8 w9 w10 w11   w30 (32bit context)
 x0 x1 x2 x3 x4 x5 x6 x7 x8 x9 x10 x11   x30 (64bit context)
 a1 a2 a3 a4 v1 v2 v3 v4 v5 v6 v7  v8    lr
 
 .p2align 4 : 16-byte aligned
 
 machine architecher macros:
 
 Apple: __APPLE__ && __MACH__
 Mac OSX: TARGET_OS_MAC == 1
 iOS sim: TARGET_IPHONE_SIMULATOR == 1
 iOS dev: TARGET_OS_IPHONE == 1
 
 iOS simulator >= iPhone6:   __x86_64__
 iOS simulator <= iPhone5:   __i386__
 
 iOS device    >= iPhone5s:  __arm64__
 iOS device    >= iPhone5:   __armv7s__
 iOS device    >= iPhone3Gs: __armv7__
 iOS device    <= iPhone3G:  __armv6__
 
 keep the code in above order
 can override the higher arch with an lower one
 and keep the code runable on old device
 */

#if defined(__x86_64__)
.text
#if defined(__MACH__)
.globl __push_jump
.p2align 4, 0x00
__push_jump:
#else
.globl _push_jump
.p2align 4, 0x00
_push_jump:
#endif
	cmpq $0, %rdi
	je 0f
	jmp *%rdi
0:
	ret
#endif

#if defined(__i386__)
.text
#if defined(__MACH__)
.globl __push_jump
.p2align 4, 0x00
__push_jump:
#else
.globl _push_jump
.p2align 4, 0x00
_push_jump:
#endif
    cmpl $0, 0(%esp)
    je 0f
    jmp *0(%esp)
0:
    ret
#endif

#if defined(__arm64__)
.text
#if defined(__MACH__)
.globl __push_jump
.p2align 4, 0x00
__push_jump:
#else
.globl _push_jump
.p2align 4, 0x00
_push_jump:
#endif
	cmp x0, #0
	beq 0f
    ldr x2, [sp]
    ldr x3, [sp, #8]
    ldr x4, [sp, #16]
    ldr x5, [sp, #24]
    ldr x6, [sp, #32]
    ldr x7, [sp, #40]
	br x0
0:
	ret
#endif

#if defined(__armv7s__) || defined(__armv7__) || defined(__armv6__)
.text
#if defined(__MACH__)
.globl __push_jump
.p2align 2, 0x00
__push_jump:
#else
.globl _push_jump
.p2align 2, 0x00
_push_jump:
#endif
    cmp r0, #0
    beq 0f
    bx r0
0:
    bx lr
#endif
