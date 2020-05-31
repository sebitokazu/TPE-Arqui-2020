GLOBAL cpuVendor
GLOBAL sys_write
GLOBAL sys_read

section .text
	
cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret

;int fwrite(int fd, char* buf, unsigned int count)
sys_write:
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
sys_read:
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