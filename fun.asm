global fun

section .data
%define tam_elem 4
%define pack_size 4
one: dd 1.0

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

XORPD xmm10, xmm10
movss xmm10, [one]
shufps xmm10, xmm10, 0x0 ; xmm10 tiene todos 1.0s (float)

XORPD xmm11, xmm11 ; xmm11 tiene todos 0s (lo uso para comparar)

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
		imul r10, tam_elem
		; r10 = (i_row * cols + i_col) * tam_elem

		movdqa xmm2, [rdi + r10] ; xmm2 influencia
		movdqa xmm3, xmm2 ; xmm3 para cant montanias

		;en xmm3 dejo 1 si hay montania 0 si no
		cmpps xmm3, xmm11, 4 ; xmm3= en cada float: 1..1 si > 0, 0s cc
		pand xmm3, xmm10 ; xmm3= en cada float: 1 si > 0, 0 cc

		;siguiente fila de elems
		inc r8
		mov r10, r9
		mov r11, r8
		imul r11, rdx
		add r10, r11
		imul r10, tam_elem

		movdqa xmm4, [rdi + r10] ; xmm4 influencia
		movdqa xmm5, xmm4 ; xmm5 para cant montanias

		;en xmm5 dejo 1 si hay montania 0 si no
		cmpps xmm5, xmm11, 4 ; xmm5= en cada float: 1..1 si > 0, 0s cc
		pand xmm5, xmm10 ; xmm5= en cada float: 1 si > 0, 0 cc

		;Datos obtenidos
		;suma de influencias
		addps xmm2, xmm4

		;suma de montanias
		addps xmm3, xmm5

		;agregar todo a los acumuladores
		;xmm0 para influencia
		addps xmm0, xmm2 
		;xmm1 para cant montanias
		addps xmm1, xmm3 

		;ir al sig:
		inc r8
		cmp r8, rsi
		jne .rows

	;calculo final del terreno (influencia/cant picos)

	movdqa [rdi + r9 * tam_elem], xmm1

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
