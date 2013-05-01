/*
Copyright (c) <2013>, <Sun Yuli>
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



.text
.globl _ff
.p2align 3
_ff:
	stmfd sp!, {a1-a4,fp,lr}
	bl _response_to
	mov ip, a1
	ldmfd sp!, {a1-a4,fp,lr}
	cmp ip, #0
	beq 0f	
	bx ip
0:
	bx lr



.text
.globl _push_jump
.p2align 3 			
_push_jump:
	cmp a2, #0		
	beq 0f
	bx a2
0:
	bx lr



.text
.globl _clean_jump1
.p2align 3, 0x90
_clean_jump1:
	mov sp, r11	
	ldr r11, [sp]		
	cmp a2, #0		
	beq 0f
	bx a2
0:
	bx lr


.text
.globl _clean_jump2
.p2align 3, 0x90
_clean_jump2:
	mov sp, r11		
	ldr r11, [sp]		
	cmp a2, #0		
	beq 0f
	bx a2
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
	cmp a2, #0		
	beq 0f
	bx a2
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
	cmp a2, #0		
	beq 0f
	bx a2
0:
	bx lr


.text
.globl mc_getIntegerForCAS
.p2align 3, 0x90
mc_getIntegerForCAS:
	ldrex v1, [a1]
	mov r0, v1
	bx lr

.text
.globl mc_getPointerForCAS
.p2align 3, 0x90
mc_getPointerForCAS:
	ldrex v1, [a1]
	mov r0, v1
	bx lr


.text
.globl	mc_compareAndSwapInteger
.p2align 3, 0x90
mc_compareAndSwapInteger:
	strex a2, a3, [a1]
	cmp a2, #0
	beq 0f
	mov r0, #0
	bx lr
0:
	mov r0, #-1
	bx lr


.text
.globl	mc_compareAndSwapPointer
.p2align 4, 0x90
mc_compareAndSwapPointer:
	strex a2, a3, [a1]
	cmp a2, #0
	beq 0f
	mov r0, #0
	bx lr
0:
	mov r0, #-1
	bx lr
	
