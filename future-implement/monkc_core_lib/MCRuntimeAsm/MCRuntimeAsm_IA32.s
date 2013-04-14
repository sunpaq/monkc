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
.align 4, 0x90	;4 byte align, fill the unaligned parts with "nop" instrucment
_ff:
				;we can get the argument by esp+4n at the very first
				;caller of _ff() will prepare the argumnets in reverse order
				;here is the meaning of c-language arguments copy-in-copy-out
				;save stack pointers
	pushl %ebp
	movl %esp, %ebp
	pushl 12(%ebp)	;pass parameters
	pushl 8(%ebp)
	call _response_to
	addl $8, %esp
	movl %ebp, %esp	;restore stack pointers
	popl %ebp
	cmpl $0, %eax	;confirm return address not nil
	je 0f
				;jump to the method with current stack frame. and did not return back here.
				;this code made the method() call just like the ff() call. it takes what arguments
				;ff() take. and return values at where ff() called. 
				;stack frame of method() is prepared by caller of ff() and cleaned by it.
	jmp	*%eax
0:
	ret


;declares:
;void* _push_jump(id const obj, void* addr, ...);
;void* _clean_jump2(id const obj, void* addr, ...);

.text
.globl _push_jump
.align 4, 0x90
_push_jump:
	cmpl $0, 8(%esp)		; confirm return address not nil
	je 0f
	jmp *8(%esp)
0:
	ret

.text
.globl _clean_jump2
.align 4, 0x90
_clean_jump2:
	pushl %esp				; align to make the same offset as BP
	;movl 4(%esp), %eax		; no need to change address
	;movl %eax, 4(%ebp)		;
	movl 8(%esp), %eax		; this ptr
	movl %eax, 8(%ebp)		;
	movl 12(%esp), %eax		; entry addr
	movl %eax, 12(%ebp)		; 
	movl 16(%esp), %eax		; arg1
	movl %eax, 16(%ebp)		;
	movl 20(%esp), %eax		; arg2
	movl %eax, 20(%ebp)		;
	movl %ebp, %esp			; unwind the current start frame
	popl %ebp				;
	cmpl $0, 8(%esp)		
	je 0f
	jmp *8(%esp)
0:
	ret


.text
.globl	mc_compareAndSwap
.align	16, 0x90
.type	mc_compareAndSwap, @function

mc_compareAndSwap:

#start
	pushl %ebp
	movl %esp, %ebp
	#8(%ebp)  addr
	#12(%ebp) oldval
	#16(%ebp) newval

	#dest addr in edx
	movl 8(%ebp), %edx
	#old value in eax
	movl 12(%ebp), %eax
	#new value in ecx
	movl 16(%ebp), %ecx
	#atomic compare and swap
	lock cmpxchgl %ecx, (%edx)
	jne	.false

#true
	movl $0, %eax

	movl %ebp, %esp
	popl %ebp
	ret
.false:
	movl $-1, %eax

	movl %ebp, %esp
	popl %ebp
	ret
