GLOBAL cpuVendor
GLOBAL sys_write
GLOBAL sys_read
GLOBAL cpuModel
GLOBAL isCpuModelPresent

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

	leave
	ret

cpuModel:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, rdi
	cpuid


	mov [rsi], eax
	mov [rsi + 4], ebx
	mov [rsi + 8], ecx
	mov [rsi + 12],edx

	mov rax, rsi

	pop rbx

	leave
	ret


isCpuModelPresent:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0x80000000
	cpuid

	cmp eax,0x80000004
	jge present
	mov qword rax,0
	jmp end
present:
	mov qword rax,1
end:
	pop rbx

	leave
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
	