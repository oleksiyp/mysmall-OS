section _TEXT PUBLIC CLASS=CODE USE16

global _switchUnreal

GDT:
;                                                                 t
;                                                                 i
;                                                L          B L   m
;                                                P          / V   i
;                                                D S        D A   L
;                       |LIMIT  |  |BASE      | P-- Type   G O ----   |B|
NULL_descr	db	000h,000h, 00h,00h,00h, 00000000b, 00000000b, 00h
		db	0ffh,0ffh, 00h,00h,00h, 10010010b, 11001111b, 00h
gdtr		dw	16
gdt_base	dd	0
_switchUnreal:
	push	ds
	push	es
	push	gs
	push	fs
	pusha

	mov	ax, cs
	mov	ds, ax
        mov	[SP_SAVE], sp
	mov	ax, ss
	mov	[SS_SAVE], ax
        	
	xor	eax,eax
        mov	ax,cs
        shl	eax,4
        add	ax, GDT
        mov	[gdt_base], eax
        lgdt	[gdtr]
        cli

        in	al,70h
        or	al,80h
        out	70h,al

	in	AL,92h
	or	AL,2
	out	92h,AL

        mov	eax,cr0
        or	al,1
        mov	cr0,eax

        jmp    start_PM
start_PM:
        mov	ax,8
        mov	ds,ax
        mov	ss,ax
        mov	es,ax
        mov	fs,ax
        mov	gs,ax
        mov	eax,cr0
        xor	al,1
        mov	cr0,eax
        jmp	exit_PM
exit_PM:
        in	al,70h
        and	al,07fh
        out	70h,al
	
	sti

	mov 	ax, cs
	mov	ds, ax

	mov	sp, [SP_SAVE]
	mov	ax, [SS_SAVE]
	mov	ss, ax
	popa
	pop	fs
	pop	gs
	pop	es
	pop	ds
	ret

SP_SAVE: dw	0
SS_SAVE: dw	0
