section _TEXT PUBLIC CLASS=CODE USE16

use16

global _highMemCopy
global _to_la

argFrom equ 4
argTo equ 8
argCount equ 12
_highMemCopy:
	push bp
	mov bp, sp
	
	push si
	push di
	push cx
	push ax

	; save es
	push es

	; es=0
	xor ax, ax
	mov es, ax
	
	; reading arguments
	mov esi, dword [bp + argFrom]
	mov edi, dword [bp + argTo]
	mov ecx, dword [bp + argCount]
	
next_byte:
	mov	al, [es:esi]
	mov	[es:edi], al
	inc esi
	inc edi
	loop next_byte
	
	pop es

	pop ax
	pop cx
	pop di
	pop si

	pop bp
	ret

_to_la:
	push bp
	mov bp, sp
	push ebx
	push ecx

	xor ebx, ebx
	xor ecx, ecx
	mov bx, [bp + 4]
	shl ebx, 4
	mov cx, [bp + 6]
	add ebx, ecx
	mov ax, bx
	shr ebx, 16
	mov dx, bx
	
	pop ecx
	pop ebx
	pop bp
	ret
