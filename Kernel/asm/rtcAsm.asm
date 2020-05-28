GLOBAL cpuHours
GLOBAL cpuMins
GLOBAL cpuSecs

cpuHours:
	push rbp
	mov rbp,rsp
	mov rax,0
	mov al, 4
	out 70h, al
	in al, 71h
	leave
	ret

cpuMins:
	push rbp
	mov rbp,rsp
	mov rax,0
	mov al, 2
	out 70h, al
	in al, 71h
	leave
	ret

cpuSecs:
	push rbp
	mov rbp,rsp
	mov rax,0
	mov al, 0
	out 70h, al
	in al, 71h
	leave
	ret