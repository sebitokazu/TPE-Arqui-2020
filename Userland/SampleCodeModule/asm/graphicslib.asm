GLOBAL draw_rect
GLOBAL get_screen_width
GLOBAL get_screen_height
GLOBAL clear_screen
GLOBAL scroll
GLOBAL graphics_info

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


clear_screen:
	push rbp
	mov rbp, rsp

	mov rax,8
	int 0x80

	mov rsp, rbp
	pop rbp
	ret	

scroll:
	push rbp
	mov rbp, rsp

	mov rax,11
	int 0x80

	mov rsp, rbp
	pop rbp
	ret

graphics_info:
	push rbp
	mov rbp, rsp

	mov rax,12
	int 0x80

	mov rsp, rbp
	pop rbp
	ret
