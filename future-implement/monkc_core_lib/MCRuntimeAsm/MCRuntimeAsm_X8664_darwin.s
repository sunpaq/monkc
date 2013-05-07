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
.globl __push_jump
.p2align 4, 0x90
__push_jump:
	cmpq $0, %rsi		#; confirm return address not nil
	je 0f
	jmp *%rsi
0:
	ret

#;void* _clean_jump2(id const obj, void* addr, ...);

.text
.globl __clean_jump1
.p2align 4, 0x90
__clean_jump1:
	movq %rbp, %rsp			#; unwind the current start frame
	popq %rbp				#;
	cmpq $0, %rsi		
	je 0f
	jmp *%rsi
0:
	ret


.text
.globl __clean_jump2
.p2align 4, 0x90
__clean_jump2:
	movq %rbp, %rsp			#; unwind the current start frame
	popq %rbp				#;
	cmpq $0, %rsi		
	je 0f
	jmp *%rsi
0:
	ret


.text
.globl __clean_jump3
.p2align 4, 0x90
__clean_jump3:
	movq %rbp, %rsp			#; unwind the current start frame
	popq %rbp				#;
	cmpq $0, %rsi		
	je 0f
	jmp *%rsi
0:
	ret


.text
.globl __clean_jump4
.p2align 4, 0x90
__clean_jump4:
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

.text
.globl	_mc_atomic_set_integer
.p2align 4, 0x90
_mc_atomic_set_integer:
0:
	movq (%rdi), %rax
	lock cmpxchgq %rsi, (%rdi)
	jne	0b
	ret


.text
.globl	_mc_atomic_set_pointer
.p2align 4, 0x90
_mc_atomic_set_pointer:
0:
	movq (%rdi), %rax
	lock cmpxchgq %rsi, (%rdi)
	jne	0b
	ret