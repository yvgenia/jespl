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



puts:	push	ebp
	mov	ebp, esp
	mov	edx, [ebp+8] 
	push	edx
	call	length 
	push	eax
	push	1
	call	write
	pop	;1
	pop	;eax
	pop	;edx

write:
	push	ebp
	mov	ebp, esp
	mov	edx, [ebp+16] 		;length
	mov	ecx, [ebp+12] 		;s
	mov	ebx, [ebp+8]  		;1
	
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
	


length:
	push	ebp
	mov	ebp, esp
	mov	eax, [ebp+8] 
	mov	eax, [eax] 
	mov	ebx, -1
.Loo:   
	inc	ebx
	movzx	eax, al  ;al is the first byte of eax, second byte is ah    -> first char of the first string 
	test	eax,eax
	jne	.Loo
	jmp	.exit
	
.exit:	
	mov 	eax, ebx
	pop	ebp
	ret
	
	