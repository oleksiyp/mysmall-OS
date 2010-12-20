@echo off
set PATH=%PATH%;"D:\Program Files\Nasm\"

nasmw boot.asm -fbin -o boot.sec
