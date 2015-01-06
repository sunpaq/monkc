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

#;System V AMD64 ABI

#;integer parameters will pass on these registers
#;define int_arg1 %rdi
#;define int_arg2 %rsi
#;define int_arg3 %rdx
#;define int_arg4 %rcx
#;define int_arg5 %r8
#;define int_arg6 %r9

#;registers must preserved across function calls(without stack pointer %rbp %rsp)
#;define preserved_reg1 %rbx
#;define preserved_reg2 %r12
#;define preserved_reg3 %r13
#;define preserved_reg4 %r14
#;define preserved_reg5 %r15


#;void* _push_jump(id const obj, void* addr, ...);

.text
.globl _push_jump
.p2align 4, 0x90
_push_jump:
	cmpq $0, %rsi		#; confirm return address not nil
	je 0f
	jmp *%rsi
0:
	ret

#;void* _clean_jump2(id const obj, void* addr, ...);

.text
.globl _clean_jump1
.p2align 4, 0x90
_clean_jump1:
	movq %rbp, %rsp			#; unwind the current start frame
	popq %rbp				#;
	cmpq $0, %rsi		
	je 0f
	jmp *%rsi
0:
	ret


.text
.globl _clean_jump2
.p2align 4, 0x90
_clean_jump2:
	movq %rbp, %rsp			#; unwind the current start frame
	popq %rbp				#;
	cmpq $0, %rsi		
	je 0f
	jmp *%rsi
0:
	ret


.text
.globl _clean_jump3
.p2align 4, 0x90
_clean_jump3:
	movq %rbp, %rsp			#; unwind the current start frame
	popq %rbp				#;
	cmpq $0, %rsi		
	je 0f
	jmp *%rsi
0:
	ret


.text
.globl _clean_jump4
.p2align 4, 0x90
_clean_jump4:
	movq %rbp, %rsp			#; unwind the current start frame
	popq %rbp				#;
	cmpq $0, %rsi		
	je 0f
	jmp *%rsi
0:
	ret



#;define int_arg1 %rdi
#;define int_arg2 %rsi
#;define int_arg3 %rdx

#;int mc_atomic_get_integer(volatile int* target);
#;void* mc_atomic_get_pointer(volatile void** target);
#;int mc_atomic_set_integer(volatile int* target, volatile int old, volatile int value);
#;int mc_atomic_set_pointer(volatile void** target, volatile void* old, volatile void* value);

.text
.globl mc_atomic_get_integer
.p2align 4, 0x90
mc_atomic_get_integer:
	pushq %rbp				
	movq %rsp, %rbp
								#; %rdi addr
	xorq %rax, %rax
	movq (%rdi), %rax
	movq %rbp, %rsp				
	popq %rbp
	ret


.text
.globl mc_atomic_get_pointer
.p2align 4, 0x90
mc_atomic_get_pointer:
	pushq %rbp				
	movq %rsp, %rbp
								#; %rdi addr
	xorq %rax, %rax
	movq (%rdi), %rax
	movq %rbp, %rsp				
	popq %rbp
	ret


.text
.globl mc_atomic_set_integer
.p2align 4, 0x90
mc_atomic_set_integer:
	pushq %rbp				
	movq %rsp, %rbp
	 							#; %rdi addr
								#; %rsi oldval
								#; %rdx newval
	xorq %rax, %rax
	movq %rsi, %rax

	lock cmpxchgq %rdx, (%rdi) 	#; atomic compare and swap
	xorq %rax, %rax				#; clear rax to 0
	jne	0b
	movq %rbp, %rsp				#; successed return 0
	popq %rbp
	ret
0:
	movq $1, %rax				#; failed return 1
	movq %rbp, %rsp				
	popq %rbp
	ret


.text
.globl mc_atomic_set_pointer
.p2align 4, 0x90
mc_atomic_set_pointer:
	pushq %rbp				
	movq %rsp, %rbp
	 							#; %rdi addr
								#; %rsi oldval
								#; %rdx newval
	xorq %rax, %rax
	movq %rsi, %rax

	lock cmpxchgq %rdx, (%rdi) 	#; atomic compare and swap
	xorq %rax, %rax				#; clear rax to 0
	jne	0b
	movq %rbp, %rsp				#; successed return 0
	popq %rbp
	ret
0:
	movq $1, %rax				#; failed return 1
	movq %rbp, %rsp				
	popq %rbp
	ret


