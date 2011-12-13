section .text
global write
write:
	push	ebp
	mov	ebp, esp
	mov	edx, [ebp+16] 
	mov	ecx, [ebp+12] 
	mov	ebx, [ebp+8]  
	
	mov	eax,4	;system call number (sys_write)
	int	0x80	;call kernel

	pop	ebp
	ret
