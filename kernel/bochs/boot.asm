use16

%macro masm_org 1
	times %1-($-$$) db 0
%endmacro
	org 0x7c00
	masm_org 0
	
	jmp start

	masm_org 0x0b
	dw 512
	db 0
	dw 0		; reserved sectors
	db 0		; number of FATs
	dw 0		; root entries
	dw 0		; small sectors
	db 0		; media type (W)
	dw 0		; sectors/fat
	dw 18		; sectors per track (T)
	dw 2		; number of heads (T)
	dd 0		; hidden sectors (W)
	dd 0		; large sectors

	masm_org 0x24
	db	0		; BIOS physical drive number (W)


start:
	xor ax, ax
	mov ds, ax

	in al, 92h
	or al, 2
	out 92h, al

	xor eax, eax
	mov ax, cs
	shl eax, 4
	add ax, entry_point
	mov [entry], eax

	xor eax, eax
	mov ax, cs
	shl eax, 4
	add ax, GDT

	mov [GDTR+2], eax
	lgdt [GDTR]

	cli

	in al,70h
	or al,80h
	out 70h,al

	mov eax, CR0
	or al, 1
	mov CR0, eax

	db 66h
	db 0EAh
entry:	dd 0
	dw 00001000b

; ТАБЛИЦА ГЛОБАЛЬНЫХ ДЕСКРИПТОРОВ:
GDT:  
; нулевой дескриптор (обязательно должен присутствовать в GDT!):
;                                                                         t
;                                                                         i
;                                                                   B L   m
;                                                                   / V   i
;                                                        DPL        D A   L
;                               |LIMIT  |  |BASE      | P---Type   G O ----   |B|
NULL_descr	db		000h,000h, 00h,00h,00h, 00000000b, 00000000b, 00h
CODE_descr	db		0FFh,0FFh, 00h,00h,00h, 10011010b, 11001111b, 00h
DATA_descr	db		0FFh,0FFh, 00h,00h,00h, 10010010b, 11001111b, 00h
GDT_size	equ 		$-GDT				; размер GDT

GDTR		dw		GDT_size-1			; 16-битный лимит GDT
		dd		0				; здесь будет 32-битный линейный адрес GDT

; ---------------------------------------------------------------------------------------------------------


use32
; СЕГМЕНТ КОДА (для Protected Mode)
; ---------------------------------------------------------------------------------------------------------
entry_point:
                mov	       AX,00010000b                ; селектор на второй дескриптор (DATA_descr)
	        mov	       DS,AX                       ; в DS его
	        mov	       ES,AX                       ; в ES его
	        mov	       FS,AX                       ; в FS его
	        mov	       GS,AX                       ; в GS его
	        mov	       SS,AX                       ; в SS его
	        mov	       ES,AX                       ; в ES его

		mov		ESP, 0x400000
		mov		eax, 0x200000
		mov		ebx, [eax]
		add		eax, ebx
		jmp		eax
	

	masm_org 510
	dw 0xaa55
	masm_org 1474558
	dw 0