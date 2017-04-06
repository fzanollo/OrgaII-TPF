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
	mov r8, 0

	;reinicio acums
	XORPD xmm0, xmm0
	XORPD xmm1, xmm1
	.rows:
		;indice para agarrar elems
		mov r10, r9
		mov r11, r8
		imul r11, rdx
		add r10, r11
		imul r10, tam_elem
		; r10 = (i_row * cols + i_col) * tam_elem

		movdqu xmm2, [rdi + r10] ; xmm2 influencia
		movdqa xmm3, xmm2 ; xmm3 para cant picos

		;en xmm3 dejo 1 si hay pico 0 si no
		cmpps xmm3, xmm11, 4 ; xmm3= en cada float: 1..1 si > 0, 0s cc
		pand xmm3, xmm10 ; xmm3= en cada float: 1 si > 0, 0 cc

		;agregar a los acumuladores
		;xmm0 para influencia
		addps xmm0, xmm2 
		;xmm1 para cant picos
		addps xmm1, xmm3 
		;ir al sig:
		inc r8
		cmp r8, rsi
		jne .rows

	;fix por si no hay ningun pico en un lugar (no se puede div por cero)
	movdqa xmm4, xmm1
	cmpps xmm4, xmm11, 0 ; xmm4 = en cada float: 1..1 si == 0, 0s cc
	pand xmm4, xmm10 ; xmm4 = en cada float: 1 si == 0, 0 cc

	addps xmm1, xmm4 ; xmm1 = 1 si == 0, el valor anterior cc

	;calculo final del terreno (influencia/cant picos == xmm0/xmm1)
	divps xmm0, xmm1
	movdqu [rdi + r9 * tam_elem], xmm0

	;ir al sig:
	add r9, pack_size
	cmp r9, rdx
	
	jg .alignCol

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

;reacomodo si al final no llega justo
.alignCol:
mov r9, rdx
sub r9, pack_size
jmp .cols