GLOBAL write
GLOBAL read
GLOBAL time
GLOBAL invalidopcode
GLOBAL keyboard_status
GLOBAL inforeg

section .text

write:
	push rbp
	mov rbp, rsp

	mov rax,1
	int 0x80

	mov rsp, rbp
	pop rbp
	ret

read:
	push rbp
	mov rbp,rsp

	mov rax,0
	int 80h

	mov rsp,rbp
	pop rbp
	ret

time:
	push rbp
	mov rbp,rsp

	mov rax,5
	int 80h

	leave
	ret

invalidopcode:
	push rbp
	mov rbp,rsp

	UD2 ;opcode 0F 0B

	leave
	ret

keyboard_status:
	push rbp
	mov rbp,rsp

	mov rax,9
	int 80h

	leave
	ret

inforeg:
	push rbp
	mov rbp,rsp

	mov rax,10
	int 80h

	leave
	ret