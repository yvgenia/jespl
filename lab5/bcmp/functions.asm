section .text
global open
global write
global read

open:
	push	ebp
	mov	ebp, esp
	mov	ecx, [ebp+12] 
	mov	ebx, [ebp+8]  
	mov	edx, 0
	
	mov	eax,5	;system call number (sys_write)
	int	0x80	;call kernel

	pop	ebp
	ret

      ; FILE *fopen(const char *path, const char *mode);


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


read:
	push	ebp
	mov	ebp, esp
	mov	edx, [ebp+16] 
	mov	ecx, [ebp+12] 
	mov	ebx, [ebp+8]  
	
	mov	eax,3	;system call number (sys_write)
	int	0x80	;call kernel

	pop	ebp
	ret