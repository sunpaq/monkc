//
//  MCRuntimeAsmIOS.s
//  monkcGame
//
//  Created by SunYuLi on 5/21/15.
//  Copyright (c) 2015-2016 oreisoft. All rights reserved.
//

#if defined(__i386__)
.text
.globl	_mc_atomic_get_integer
.p2align 4, 0x00
_mc_atomic_get_integer:
	pushl %ebp				
	movl %esp, %ebp
								#; 8(%ebp) addr
	xorl %eax, %eax
	movl 8(%ebp), %edx
	movl (%edx), %eax
	movl %ebp, %esp				
	popl %ebp
	ret

.text
.globl	_mc_atomic_get_pointer
.p2align 4, 0x00
_mc_atomic_get_pointer:
	pushl %ebp				
	movl %esp, %ebp
								#; 8(%ebp) addr
	xorl %eax, %eax
	movl 8(%ebp), %edx
	movl (%edx), %eax
	movl %ebp, %esp				
	popl %ebp
	ret

.text
.globl	_mc_atomic_set_integer
.p2align 4, 0x00
_mc_atomic_set_integer:
	pushl %ebp				
	movl %esp, %ebp
	 							#; 8(%ebp)  addr
								#; 12(%ebp) oldval
								#; 16(%ebp) newval
	xorl %eax, %eax
	movl 8(%ebp), %edx			#; dest addr in edx
	movl 12(%ebp), %eax			#; old value in eax
	movl 16(%ebp), %ecx			#; new value in ecx

	lock cmpxchgl %ecx, (%edx) 	#; atomic compare and swap
	xorl %eax, %eax				#; clear eax to 0
	jne	0b
	movl %ebp, %esp				#; successed return 0
	popl %ebp
	ret
0:
	movl $1, %eax				#; failed return 1
	movl %ebp, %esp				
	popl %ebp
	ret

.text
.globl	_mc_atomic_set_pointer
.p2align 4, 0x00
_mc_atomic_set_pointer:
	pushl %ebp				
	movl %esp, %ebp
	 							#; 8(%ebp)  addr
								#; 12(%ebp) oldval
								#; 16(%ebp) newval
	xorl %eax, %eax
	movl 8(%ebp), %edx			#; dest addr in edx
	movl 12(%ebp), %eax			#; old value in eax
	movl 16(%ebp), %ecx			#; new value in ecx

	lock cmpxchgl %ecx, (%edx) 	#; atomic compare and swap
	xorl %eax, %eax				#; clear eax to 0
	jne	0b
	movl %ebp, %esp				#; successed return 0
	popl %ebp
	ret
0:
	movl $1, %eax				#; failed return 1
	movl %ebp, %esp				
	popl %ebp
	ret
#endif

#if defined(__x86_64__)
.text
.globl	_mc_atomic_get_integer
.p2align 4, 0x00
_mc_atomic_get_integer:
	pushq %rbp				
	movq %rsp, %rbp
								#; %rdi addr
	xorq %rax, %rax
	movq (%rdi), %rax
	movq %rbp, %rsp				
	popq %rbp
	ret

.text
.globl	_mc_atomic_get_pointer
.p2align 4, 0x00
_mc_atomic_get_pointer:
	pushq %rbp				
	movq %rsp, %rbp
								#; %rdi addr
	xorq %rax, %rax
	movq (%rdi), %rax
	movq %rbp, %rsp				
	popq %rbp
	ret

.text
.globl	_mc_atomic_set_integer
.p2align 4, 0x00
_mc_atomic_set_integer:
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
.globl	_mc_atomic_set_pointer
.p2align 4, 0x00
_mc_atomic_set_pointer:
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
#endif

#if defined(__armv7__)
.text
.globl	_mc_atomic_get_integer
.p2align 3, 0x00
_mc_atomic_get_integer:
	ldrex v1, [r0]
	mov r0, v1
	bx lr

.text
.globl	_mc_atomic_get_pointer
.p2align 3, 0x00
_mc_atomic_get_pointer:
	ldrex v1, [r0]
	mov r0, v1
	bx lr

.text
.globl	_mc_atomic_set_integer
.p2align 3, 0x00
_mc_atomic_set_integer:
	strex v1, r2, [r0]
	mov r0, v1
	bx lr

.text
.globl	_mc_atomic_set_pointer
.p2align 3, 0x00
_mc_atomic_set_pointer:
	strex v1, r2, [r0]
	mov r0, v1
	bx lr
#endif

#if defined(__arm64__)
.text
.globl	_mc_atomic_get_integer
.p2align 4, 0x00
_mc_atomic_get_integer:
	ldxr w4, [x0,#0]
	mov x0, x4
	blr lr

.text
.globl	_mc_atomic_get_pointer
.p2align 4, 0x00
_mc_atomic_get_pointer:
	ldxr w4, [x0,#0]
	mov x0, x4
	blr lr

.text
.globl	_mc_atomic_set_integer
.p2align 4, 0x00
_mc_atomic_set_integer:
	stxr w2, w4, [x0,#0]
	mov x0, x4
	blr lr

.text
.globl	_mc_atomic_set_pointer
.p2align 4, 0x00
_mc_atomic_set_pointer:
	stxr w2, w4, [x0,#0]
	mov x0, x4
	blr lr
#endif

#if defined(__powerpc__) || defined(__ppc__) || defined(__PPC__)
#if defined(__powerpc64__) || defined(__ppc64__) || defined(__PPC64__) || \
defined(__64BIT__) || defined(_LP64) || defined(__LP64__)
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

#endif
#endif