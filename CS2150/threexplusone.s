	;; Reid Bixler
	;; rmb3yz
	;; CS 2150 Pre-Lab 9  threexplusone.s
	;; November 18, 2014
	global threexplusone
	section .text
	;; Optimizations: Original # of Lines 52 (with spaces & header), 31 (w/out spaces & header)
	;; Instruction Scheduling: Move Even and Odd around so Even is automatically called if not Odd
	;; Redundant Code & Dead Code Elimination & Peephole Optimization: # of Lines 43 (S&H), 24 (W/O S&H) Deleted unecessary instructions that could be shortened, made instruction calls much quicker, minimized use of unecessary registers and register calls

threexplusone:
	push	ebp		;Save the old base pointer
	mov	ebp, esp	;Set new value of base pointer
	
	mov	eax, esi	;For keeping track of the number of steps (esi original = 0)
	mov 	ebx, [ebp+8]	;Move first param to EBX (number)

	cmp	ebx, 1		;If it is the base case, 1st param = 1
	je	x_base		;Go to the base case

	mov	edx, ebx	;Test if even, put EBX into EDX (Also prepares new number if even)
	shr	edx, 1		;Shift EDX by one bit right (Effectively divide by two)
	jc	x_odd		;If there is a carry bit, it is odd, jump past even
	
				;Number is not odd, therefore it's even
	mov	ebx, edx	;Move new divided value into EBX (EBX = EBX/2)
	jmp	x_back		;Skip past odd, prepare for recursion
	
x_odd:	
	lea	ebx, [3*ebx+1]	;Multiply EBX by 3 and add 1, store into EBX

x_back:
	inc	eax	 	;Increment eax for steps
	mov 	esi, eax	;Store EAX into ESI so that it can be remembered in the next call
	push	ebx		;Push new number for new call for recursion

	call	threexplusone	;Recursive call on new number EBX

	pop	ebx		;Fix for the 1 push instructions (pops = pushes)

x_base:		 		;Base case/Return: return steps = eax (if #init = 1 then 0 steps)
	mov	esi, eax	;EAX has incremented (or not), store in ESI for remembering next
	pop	ebp		;Reset base pointer
	ret			;Return EAX
