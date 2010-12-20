@echo off
set PATH=%PATH%;"D:\Program Files\Nasm\"
del *.obj

@echo on
nasmw memcpy.asm -fobj -o memcpy.obj
nasmw unreal3.asm -fobj -o unreal.obj
nasmw protected.asm -fobj -o prot32.obj
@echo off
pause
call D:\Compilers\BC31\BIN\bcc.bat -c loader.cpp
call D:\Compilers\BC31\BIN\bcc.bat -c dll.cpp
call D:\Compilers\BC31\BIN\link.bat c0fs.obj loader.obj memcpy.obj unreal.obj dll.obj prot32.obj, loader.exe,,cs.lib