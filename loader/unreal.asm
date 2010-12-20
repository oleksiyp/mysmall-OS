
section _TEXT PUBLIC CLASS=CODE USE16

global _switchUnreal
_switchUnreal:
		push ds
		push es
		push gs
		push fs
		pusha

		mov		ax, cs				; AX = номер сегмента PM_CODE
		mov		ds, ax

		mov		[SP_SAVE], sp
		mov		ax, ss
		mov		[SS_SAVE], ax

; открываем линию А20 (для 32-х битной адресации):
		in		AL,92h
		or		AL,2
		out		92h,AL

; вычисляем линейный адрес метки ENTRY_POINT (точка входа в защищенный режим, 
; находится в PM_CODE сегменте, поэтому от него и пляшем):
		mov		esi, real_entry
		mov		[real_off], esi
		mov		ax, cs
		mov		[real_seg], ax
		shl		eax, 4				; EAX = линейный адрес PM_CODE
		add		ax, entry_point 		; EAX = линейный адрес ENTRY_POINT
		mov		[entry], eax			; сохраняем его в переменной ENTRY_OFF  	
; (кстати, подобный "трюк" называется SMC или Self Modyfing Code - самомодифицирующийся код)

; теперь надо вычислить линейный адрес GDT (для загрузки регистра GDTR):
		xor		eax,eax
		mov		ax,cs     			; AX = номер сегмента RM_CODE
		shl		eax,4				; EAX = линейный адрес RM_CODE
		add		ax,GDT				; теперь EAX = линейный адрес GDT

; линейный адрес GDT кладем в заранее подготовленную переменную:
		mov		[GDTR+2], eax

; а подобный трюк назвать SMC уже нельзя, потому как по сути мы модифицируем данные :)

; собственно, загрузка регистра GDTR:
		lgdt		[GDTR]

; запрет маскируемых прерываний:
		cli

; запрет немаскируемых прерываний:
		in		al,70h
		or		al,80h
		out		70h,al

; переключение в защищенный режим:
		mov		eax, CR0
		or		al, 1
		mov		CR0, eax


; загрузить новый селектор в регистр CS
		db		66h				; префикс изменения разрядности операнда
		db		0EAh				; опкод команды JMP FAR
entry:		dd		0				; 32-битное смещение
		dw		00001000b			; селектор первого дескриптора (CODE_descr)

real_entry:
		sti

		in		al,70h
		xor		al,80h
		out		70h,al

		mov 		ax, cs
		mov		ds, ax

		mov		sp, [SP_SAVE]
		mov		ax, [SS_SAVE]
		mov		ss, ax
		popa
		pop fs
		pop gs
		pop es
		pop ds
		ret

; ТАБЛИЦА ГЛОБАЛЬНЫХ ДЕСКРИПТОРОВ:
GDT:  
; нулевой дескриптор (обязательно должен присутствовать в GDT!):
;                                                                         t
;                                                                         i
;                                                        L          B L   m
;                                                        P          / V   i
;                                                        D S        D A   L
;                               |LIMIT  |  |BASE      | P-- Type   G O ----   |B|
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
; загрузим сегментные регистры селекторами на соответствующие дескрипторы:
                mov	       AX,00010000b                ; селектор на второй дескриптор (DATA_descr)
	        mov	       DS,AX                       ; в DS его
	        mov	       ES,AX                       ; в ES его
	        mov	       FS,AX                       ; в FS его
	        mov	       GS,AX                       ; в GS его
	        mov	       SS,AX                       ; в SS его
	        mov	       ES,AX                       ; в ES его

		mov		eax, CR0
		xor		al,  1
		mov		CR0, eax

		db		0EAh				; опкод команды JMP FAR
real_off:	dd		0				; Off
real_seg:	dw		0				; Seg


SP_SAVE: dw	0
SS_SAVE: dw	0
