/*
Copyright (c) <2013-2015>, <Sun Yuli>
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the <Monk-C> nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*
infos about PowerPC 64 platform: (from IBM Knowledge Center)
	
link register --> 
r3 r4 

ldarx  RT, RA, RB --> data, RA+RB=EA (effective-address)
stdcx. RS, RA, RB --> data, RA+RB=EA

cmpi BF, L, RA, SI --> ConditionField, (32bit=0), reg, immidiate
*/

.text
.globl _push_jump
.align 8
_push_jump:
	cmpi 0,0,3,0
	beq 0f
	ldu 12, 0(4)
        mtctr 12
        bctr
0:
	blr


/*
.text
.globl _clean_jump1
.p2align 4, 0x90
_clean_jump1:
	mr sp, r11	
	ldr r11, [sp]		
	cmp 0,0,a2,0		
	b 0f
	b a2
0:
	b lr


.text
.globl _clean_jump2
.p2align 4, 0x90
_clean_jump2:
	mr sp, r11		
	ldr r11, [sp]		
	cmp 0,0,a2,0		
	b 0f
	b a2
0:
	b lr


.text
.globl _clean_jump3
.p2align 4, 0x90
_clean_jump3:
	ldmfd sp, {v1-v2}		
	mr r12, r11
	add r12, r12, 8
	mr r12, v2 	
	mr sp, r11
	ldr r11, [sp]		
	cmp 0,0,a2,0		
	b 0f
	b a2
0:
	b lr


.text
.globl _clean_jump4
.p2align 4, 0x90
_clean_jump4:
	ldmfd sp, {v1-v3}	
	mr r12, r11
	add r12, r12, 8
	mr r12, v2 	
	add r12, r12, 4
	mr r12, v3 
	mr sp, r11		
	ldr r11, [sp] 		
	cmp 0,0,a2,0		
	b 0f
	b a2
0:
	b lr
*/

/*
int mc_atomic_get_integer(volatile int* target);
void* mc_atomic_get_pointer(volatile void** target);
int mc_atomic_set_integer(volatile int* target, volatile int old, volatile int value);
int mc_atomic_set_pointer(volatile void** target, volatile void* old, volatile void* value);

a1 addr
a2 oldval
a3 newval
return 0 success
*/

.text
.globl	mc_atomic_get_integer
.align 4
mc_atomic_get_integer:
	lwarx 5,0,3
	mr 3, 5
	blr

.text
.globl	mc_atomic_get_pointer
.align 8
mc_atomic_get_pointer:
	ldarx 5,0,3
	mr 3, 5
	blr

.text
.globl	mc_atomic_set_integer
.align 4
mc_atomic_set_integer:
	stwcx. 5,0,3
	bne 0f
	li 3, 0
	blr
0:
	li 3, 1
	blr


.text
.globl	mc_atomic_set_pointer
.align 8
mc_atomic_set_pointer:
	stdcx. 5,0,3
	bne 1f
	li 3, 0
1:
	li 3, 1
	blr

