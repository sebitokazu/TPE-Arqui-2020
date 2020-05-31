GLOBAL write
GLOBAL read

section .text

;int fwrite(int fd, char* buf, unsigned int count)
write:
	push rbp
	mov rbp, rsp

	mov rax,1
	int 0x80

	mov rsp, rbp
	pop rbp
	ret

;int read(int fd, char* buf,unsigned int count)
read:
	push rbp
	mov rbp,rsp

	mov rax,0
	int 80h

	mov rsp,rbp
	pop rbp
	ret


section .rodata
text dq "Hello"
len equ $ - text