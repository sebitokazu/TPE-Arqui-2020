GLOBAL getcpuVendor
GLOBAL getcpuModel

section .text
getcpuVendor:
	push rbp
	mov rbp,rsp

	mov rax,6
	int 80h
	
	mov rax,rdi

	leave
	ret

getcpuModel:
	push rbp
	mov rbp,rsp

	mov rax,7
	int 80h

	mov rax,rdi

	leave
	ret