GLOBAL draw_rect
GLOBAL get_screen_width
GLOBAL get_screen_height

section .text

draw_rect:
    push rbp
	mov rbp, rsp

	mov rax,2
	int 0x80

	mov rsp, rbp
	pop rbp
	ret

get_screen_width:
    push rbp
	mov rbp, rsp

	mov rax,3
	int 0x80

	mov rsp, rbp
	pop rbp
	ret

get_screen_height:
	push rbp
	mov rbp, rsp

	mov rax,4
	int 0x80

	mov rsp, rbp
	pop rbp
	ret