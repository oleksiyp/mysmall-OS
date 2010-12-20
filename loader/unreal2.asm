nable_A20 proc near
        call    Wait8042BufferEmpty
        mov     AL,0D1h ;команда управления линий A20
        out     64h,AL
        call    Wait8042BufferEmpty
        mov     AL,0DFh ;разрешить работу линии
        out     60h,AL
        call    Wait8042BufferEmpty
        ret
Enable_A20 endp

Wait8042BufferEmpty proc near
        push    CX
        mov     CX,0FFFFh  ;задать число циклов
@@kb:   in      AL,64h     ;получить статус
        test    AL,10b     ;буфер i8042 свободен?
        loopnz  @@kb       ;если нет, то цикл
        pop     CX
        ret
Wait8042BufferEmpty endp


Много места для кода - лучше так 
Enable_A20:;push ax ;исли нужно сохранить значение AX
                    ;то это и в конце мона раскоментировать
            in al,92h ;См.-  http://wasm.ru/forum/files/_625753930__ports.zip
            or al,02h ;Бит 1(счет с нулевого) - Индикатор линии A 20
            out 92h,al
           ;pop ax
           ret
