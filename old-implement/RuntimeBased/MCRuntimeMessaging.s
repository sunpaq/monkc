#include "MCRuntime.h"

//void* findMethod(id const self_in, char *key);
//id ff(id const self_in, char *key, ...);

.text
.globl ff
.align 4
ff:
	movl 4(%esp), %ecx
	movl 8(%esp), %edx
	
	pushl %edx
	pushl %ecx
	call findMethod
	addl $8, %esp

	jmp	*%eax
	ret



