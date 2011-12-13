section .text
global atod

atod:
	push	ebp
	mov	ebp, esp
	mov	edx, [ebp+8]     ;[ebp+8] is the value of the first parameter
	;dec	edx	
	mov 	ebx, 0		;the ans


loop:

	;mov	edx, [ebp+8]     ;[ebp+8] is the value of the first parameter
	;inc	edx


	cmp 	edx, 0
	je	exit
	mov	eax, 10	;factor
	mov	ecx, [edx]	;the char

	;sub	ecx, 48	;the "int"


	movzx	ecx,cl
	sub	ecx, 48
	add	ebx, ecx	;add to the ans
	mul	ebx		;multiply the ans by factor

	mov	eax, ebx
	pop	ebp
	ret

;add	DWORD [ebp+8], 1
;mov	edx, DWORD [ebp+8]
add edx,DWORD [ebp+8]
;mov [ebp+8],[ebp+8]+4
add edx,1

	jmp	loop


exit:

	mov	eax, 10
	div	ebx
	mov	eax, ebx
	pop	ebp
	ret