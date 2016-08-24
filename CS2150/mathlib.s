	;; Reid Bixler
	;; rmb3yz
	;; CS 2150 Pre-Lab 8 mathlib.s
	;; November 4, 2014
	global product
	global power
	section .text

product:
	push	ebp		;Save the old base pointer
	mov	ebp, esp	;Set new value of base pointer
	
	mov	ecx, [ebp+8]	;Move first param to ECX
	mov	edx, [ebp+12]	;Move second param to EDX

       	mov 	edi, 0	   	;Place zero in EDI, to be used for product
	mov 	esi, 0		;Place zero in ESI for comparing in loop

product_loop:
	add	edi, ecx	;Add param 1 to EDI, multiple times
	inc	esi		;Increment ESI
	cmp	esi, edx	;If ESI < second parameter continue
	jl	product_loop	;Go back to loop

product_done:
	pop	ebp		;Reset base pointer
	mov	eax, edi	;Move product to EAX for returning
	ret

power:
	push	ebp		;Save the old base pointer
	mov	ebp, esp	;Set new value of base pointer
	
	mov 	ebx,[ebp+8]	;Move first param to EBX (base)
	mov	edx,[ebp+12]	;Move second param to EDX (exponent)

	cmp	edx, 1		;If it is the base case, 2nd param = 1
	je	power_base	;Go to the base case

	dec	edx		;Decrement EDX (exponent)
	push	edx		;Push exponent for call on exponent
	push 	ebx 		;Push base for call on exponent

	call	power		;Recursive call on exponent(x,y-1)

	add	esp, 8		;Fix for the 2 push instructions
	
	push	eax		;Push the exponential to multiply (x^(y-1))
	push	ebx		;Push the base to multiply x
	
	call	product		;Run the product function (x^(y-1) * x)

	add	esp, 8		;Fix for the 2 push instructions
	
	pop ebp			;Reset base pointer
	
	ret			;Return exponential(x,y)

power_base:
	mov	eax, ecx 	;Base case exp(x,1)
	pop	ebp		;Reset base pointer
	ret			;Return exp(x,1)
