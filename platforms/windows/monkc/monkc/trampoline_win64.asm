.CODE

_push_jump PROC
    mov r11, [rcx]
	cmp r11, 0
	je label_ret
	jmp r11
label_ret:
    ret
_push_jump ENDP

END