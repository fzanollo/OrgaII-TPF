global fun

%define tam_short 2
%define pack_size 8

section .text

fun:
push rbp
mov rbp, rsp
sub rsp, 24
push rbx
push r12
push r13
push r14
push r15
; codigo abajo

;rdi = puntero a matrizPicos
;rsi = rows
;rdx = cols

mov r9, 0
.cols:
	;se hace algo
	mov r8, 0


	XORPD xmm0, xmm0
	XORPD xmm1, xmm1
	.rows:
		;se hace algo
		;indice para agarrar elems
		mov r10, r9
		mov r11, r8
		imul r11, rdx
		add r10, r11
		imul r10, tam_short
		; r10 = (i_row * cols + i_col) * tam_short

		movdqa xmm2, [rdi + r10]
		movdqa xmm3, xmm0

		;siguiente fila de elems
		inc r8
		mov r10, r9
		mov r11, r8
		imul r11, rdx
		add r10, r11
		imul r10, tam_short

		movdqa xmm4, [rdi + r10]
		movdqa xmm5, xmm2

		;datos obtenidos
		;suma de influencias
		paddw xmm2, xmm4
		;contar cant de montanias

		;agregar todo a los acumuladores
		;xmm0 para influencia
		PADDW xmm0, xmm2 
		;xmm1 para cant montanias
		PADDW xmm1, xmm3 

		;ir al sig:
		inc r8
		cmp r8, rsi
		jne .rows
	;hacer la cuenta y guardarlo
	movdqa [rdi + r9 * tam_short], xmm0
	;ir al sig:
	add r9, pack_size
	cmp r9, rdx
	jne .cols

;fin codigo
pop r15
pop r14
pop r13
pop r12
pop  rbx
add rsp, 24
pop  rbp
ret
