section .text
global hsvmhr
hsvmhr:
	push	ebp
	mov	ebp, esp
.L5:
	mov	eax, [ebp+8]     ;[ebp+8] is the value of the first parameter
	mov	eax, [eax]       ;[eax] is the value [ebp+8] is pointing at  (in this case [ebp+8] is a pointer)
	mov	edx, [ebp+12]    ;[ebp+12] is the value of the second parameter
	mov	edx, [edx]
	movzx eax, al  ;al is the first byte of eax, second byte is ah    -> first char of the first string 
	movzx edx, dl  ;dl is the first byte of edx       -> first char of the second string 
	sub	eax, edx    ;subtraction: eax-edx
	je	.L2
	jmp	.L3
.L2:
	test dl, dl    ;test = and without remembering the result, always true if dl!=0
	jne	.L4
	xor	eax, eax    ;if dl=0 put in eax 0     eax is the return value
	jmp	.L3
.L4:
	add	DWORD [ebp+8], 1
	add	DWORD [ebp+12], 1
	jmp	.L5
.L3:
	pop	ebp
	ret
