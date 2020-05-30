GLOBAL write
GLOBAL read

section .text

;int fwrite(int fd, char* buf, unsigned int count)
write:
	push rbp
	mov rbp, rsp
	push rdi
	push rsi
	push rdx

	mov rax,1
	;mov ecx,0
	int 0x80
	
	pop rdx
	pop rsi
	pop rdi

	mov rsp, rbp
	pop rbp
	ret

;int read(int fd, char* buf,unsigned int count)
read:
	push rbp
	mov rbp,rsp

	push rdi
	push rsi
	push rdx

	mov rax,0
	int 80h

	pop rdx
	pop rsi
	pop rdi

	mov rsp,rbp
	pop rbp
	ret


section .rodata
text dq "Hello"
len equ $ - text