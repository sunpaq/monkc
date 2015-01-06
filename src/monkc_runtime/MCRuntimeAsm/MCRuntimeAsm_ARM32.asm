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
infos about ARM 32 platform:

stack-align: 	public(8byte) non-public(4byte)
frame-pointer: fp is r11 in ARM mode / r7 in thumb mode
keep-fp:		-mapcs-frame will keep the fp not to be optimized out
*/

.text
.globl _push_jump
.p2align 3 			
_push_jump:
	cmp r1, #0
	beq 0f
	bx r1
0:
	bx lr



.text
.globl _clean_jump1
.p2align 3, 0x90
_clean_jump1:
	mov sp, r11	
	ldr r11, [sp]		
	cmp r1, #0
	beq 0f
	bx r1
0:
	bx lr


.text
.globl _clean_jump2
.p2align 3, 0x90
_clean_jump2:
	mov sp, r11		
	ldr r11, [sp]		
	cmp r1, #0
	beq 0f
	bx r1
0:
	bx lr


.text
.globl _clean_jump3
.p2align 3, 0x90
_clean_jump3:
	ldmfd sp, {v1-v2}		
	mov r12, r11
	add r12, #8
	mov r12, v2 	
	mov sp, r11
	ldr r11, [sp]		
	cmp r1, #0
	beq 0f
	bx r1
0:
	bx lr


.text
.globl _clean_jump4
.p2align 3, 0x90
_clean_jump4:
	ldmfd sp, {v1-v3}	
	mov r12, r11
	add r12, #8
	mov r12, v2 	
	add r12, #4
	mov r12, v3 
	mov sp, r11		
	ldr r11, [sp] 		
	cmp r1, #0
	beq 0f
	bx r1
0:
	bx lr


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
.p2align 3, 0x90
mc_atomic_get_integer:
	ldrex v1, [r0]
	mov r0, v1
	bx lr

.text
.globl	mc_atomic_get_pointer
.p2align 3, 0x90
mc_atomic_get_pointer:
	ldrex v1, [r0]
	mov r0, v1
	bx lr

.text
.globl	mc_atomic_set_integer
.p2align 3, 0x90
mc_atomic_set_integer:
	strex v1, r2, [r0]
	mov r0, v1
	bx lr


.text
.globl	mc_atomic_set_pointer
.p2align 3, 0x90
mc_atomic_set_pointer:
	strex v1, r2, [r0]
	mov r0, v1
	bx lr
	
