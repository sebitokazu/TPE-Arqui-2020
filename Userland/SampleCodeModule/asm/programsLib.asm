GLOBAL create_program
GLOBAL change_program

section .text

create_program:
	push rbp
	mov rbp, rsp

	mov rax,6
	int 0x80

	mov rsp, rbp
	pop rbp
	ret

change_program:
	push rbp
	mov rbp, rsp

	mov rax,7
	int 0x80

	mov rsp, rbp
	pop rbp
	ret
