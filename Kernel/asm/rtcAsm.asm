GLOBAL cpuHours
GLOBAL cpuMins
GLOBAL cpuSecs
GLOBAL cpuWeekday
GLOBAL cpuDay
GLOBAL cpuMonth
GLOBAL cpuYear

section .text

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

cpuWeekday:
	push rbp
	mov rbp,rsp
	mov rax,0
	mov al, 6
	out 70h, al
	in al, 71h
	leave
	ret

cpuDay:
	push rbp
	mov rbp,rsp
	mov rax,0
	mov al, 7
	out 70h, al
	in al, 71h
	leave
	ret

cpuMonth:
	push rbp
	mov rbp,rsp
	mov rax,0
	mov al, 8
	out 70h, al
	in al, 71h
	leave
	ret

cpuYear:
	push rbp
	mov rbp,rsp
	mov rax,0
	mov al, 9
	out 70h, al
	in al, 71h
	leave
	ret