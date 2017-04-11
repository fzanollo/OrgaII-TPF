global fun

section .data
%define tam_elem 4
%define pack_size 4

onesPS: dd 1.0, 1.0, 1.0, 1.0
onesINT: dd 1, 1, 1, 1
positions_aux: dd 0, 1, 2, 3

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

;rdi = puntero a peaksPos
;rsi = puntero a peaksSize
;rdx = nroPeaks
;rcx = divisions
;r8 = puntero a terrainArray

pxor xmm0, xmm0 ; xmm0 = 0s
movdqa xmm13, [positions_aux] ; xmm13 = 0 | 1 | 2 | 3

mov r10, 0
.terrain:

	movd xmm10, r10d
	pshufd xmm10, xmm10, 0x0 ; xmm10 = posActual | posActual | posActual | posActual 
	paddd xmm10, xmm13 ; xmm10 = posActual | posActual+1 | posActual+2 | posActual+3 

	pxor xmm14, xmm14 ;acumulador para la influencia
	pxor xmm15, xmm15 ;acumulador para la cant de picos
	
	mov r11, 0
	.peaks:
		;leer peaksPos
		movdqu xmm1, [rdi + r11 * tam_elem]
		
		;leer peaksSize
		movdqu xmm2, [rsi + r11 * tam_elem]

		; PARA EL PRIMER PICO*****************
			;datos
			pshufd xmm3, xmm1, 0xFF ; xmm3 = posP1 | posP1 | posP1 | posP1 
			pshufd xmm7, xmm2, 0xFF ; xmm7 = sizeP1 | sizeP1 | sizeP1 | sizeP1 

			;Calcular influencia p/c pos, es decir: peakSize - Abs(peakPos - posActual)
			psubd xmm3, xmm10 ; xmm3 = peakPos - posActual
			pabsd xmm3, xmm3 ; xmm3 = Abs(peakPos - posActual)
			psubd xmm7, xmm3 ; xmm7 (influencia) = peakSize - Abs(peakPos - posActual)

			;Calcular cantidad de picos p/c pos
			movdqa xmm3, xmm7
			pcmpgtd xmm3, xmm0 ; xmm3= en cada int: 1..1 si > 0, 0s cc
			movdqa xmm12, [onesINT] ; xmm12 = 1 | 1 | 1 | 1
			pand xmm3, xmm12 ; xmm3 (cant de picos) = en cada int: 1 si > 0, 0 cc

			;Acumular
			paddd xmm14, xmm7 ; influencia
			paddd xmm15, xmm3 ; cant de picos
		;*************************************

		; PARA EL SEGUNDO PICO*****************
			;datos
			pshufd xmm3, xmm1, 0xAA ; xmm3 = posP2 | posP2 | posP2 | posP2 
			pshufd xmm7, xmm2, 0xAA ; xmm7 = sizeP2 | sizeP2 | sizeP2 | sizeP2 

			;Calcular influencia p/c pos, es decir: peakSize - Abs(peakPos - posActual)
			psubd xmm3, xmm10 ; xmm3 = peakPos - posActual
			pabsd xmm3, xmm3 ; xmm3 = Abs(peakPos - posActual)
			psubd xmm7, xmm3 ; xmm7 (influencia) = peakSize - Abs(peakPos - posActual)

			;Calcular cantidad de picos p/c pos
			movdqa xmm3, xmm7
			pcmpgtd xmm3, xmm0 ; xmm3= en cada int: 1..1 si > 0, 0s cc
			movdqa xmm12, [onesINT] ; xmm12 = 1 | 1 | 1 | 1
			pand xmm3, xmm12 ; xmm3 (cant de picos) = en cada int: 1 si > 0, 0 cc

			;Acumular
			paddd xmm14, xmm7 ; influencia
			paddd xmm15, xmm3 ; cant de picos
		;*************************************

		; PARA EL TERCER PICO*****************
			;datos
			pshufd xmm3, xmm1, 0x55 ; xmm3 = posP3 | posP3 | posP3 | posP3 
			pshufd xmm7, xmm2, 0x55 ; xmm7 = sizeP3 | sizeP3 | sizeP3 | sizeP3 

			;Calcular influencia p/c pos, es decir: peakSize - Abs(peakPos - posActual)
			psubd xmm3, xmm10 ; xmm3 = peakPos - posActual
			pabsd xmm3, xmm3 ; xmm3 = Abs(peakPos - posActual)
			psubd xmm7, xmm3 ; xmm7 (influencia) = peakSize - Abs(peakPos - posActual)

			;Calcular cantidad de picos p/c pos
			movdqa xmm3, xmm7
			pcmpgtd xmm3, xmm0 ; xmm3= en cada int: 1..1 si > 0, 0s cc
			movdqa xmm12, [onesINT] ; xmm12 = 1 | 1 | 1 | 1
			pand xmm3, xmm12 ; xmm3 (cant de picos) = en cada int: 1 si > 0, 0 cc

			;Acumular
			paddd xmm14, xmm7 ; influencia
			paddd xmm15, xmm3 ; cant de picos
		;*************************************

		; PARA EL CUARTO PICO*****************
			;datos
			pshufd xmm3, xmm1, 0x0 ; xmm3 = posP4 | posP4 | posP4 | posP4 
			pshufd xmm7, xmm2, 0x0 ; xmm7 = sizeP4 | sizeP4 | sizeP4 | sizeP4 

			;Calcular influencia p/c pos, es decir: peakSize - Abs(peakPos - posActual)
			psubd xmm3, xmm10 ; xmm3 = peakPos - posActual
			pabsd xmm3, xmm3 ; xmm3 = Abs(peakPos - posActual)
			psubd xmm7, xmm3 ; xmm7 (influencia) = peakSize - Abs(peakPos - posActual)

			;Calcular cantidad de picos p/c pos
			movdqa xmm3, xmm7
			pcmpgtd xmm3, xmm0 ; xmm3= en cada int: 1..1 si > 0, 0s cc
			movdqa xmm12, [onesINT] ; xmm12 = 1 | 1 | 1 | 1
			pand xmm3, xmm12 ; xmm3 (cant de picos) = en cada int: 1 si > 0, 0 cc

			;Acumular
			paddd xmm14, xmm7 ; influencia
			paddd xmm15, xmm3 ; cant de picos
		;*************************************

		;siguiente batch de peaks
		add r11, pack_size
		cmp r11, rdx
		; jg .alignPeaks
		jne .peaks

	;se terminaron de recorrer los picos

	;castear los int de los acumuladores a float
	cvtdq2ps xmm14, xmm14 ; influencia
	cvtdq2ps xmm15, xmm15 ; cant de picos

	;Corregir la cant de picos para no dividir por cero y en caso de un solo pico dividir por dos
	movdqa xmm12, [onesPS] ; xmm12 = 1.0 | 1.0 | 1.0 | 1.0
	
	movdqa xmm1, xmm15
	cmpps xmm1, xmm12, 2 ; xmm1 = en cada float: 1..1 si <= 1, 0s cc
	pand xmm1, xmm12 ; xmm1 = en cada float: 1 si antes == 0 o == 1, 0 cc

	addps xmm15, xmm1 ; xmm15 = 1 si antes == 0, xmm15 = 2 si antes == 1, sin cambios (valor anterior) cc

	;calculo final del terreno (influencia/cant picos == xmm14/xmm15)
	divps xmm14, xmm15
	movdqu [r8 + r10 * tam_elem], xmm14 ;r8 = puntero a terrainArray

	;siguiente batch de terrain
	add r10, pack_size
	cmp r10, rcx
	; jg .alignTerrain
	jne .terrain

;fin codigo
pop r15
pop r14
pop r13
pop r12
pop  rbx
add rsp, 24
pop  rbp
ret
