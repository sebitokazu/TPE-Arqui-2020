GLOBAL draw_rect

section .text

draw_rect:
    push rbp
	mov rbp, rsp

	mov rax,2
	int 0x80

	mov rsp, rbp
	pop rbp
	ret