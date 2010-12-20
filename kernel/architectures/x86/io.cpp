#include <basic/types.h>

namespace architecture
{
	namespace x86
	{
		namespace io
		{
#pragma warning(disable : 4035)
			byte inb(word port)
			{
				_asm
				{
					mov dx, port
					in al, dx
				}
			}
			word inw(word port)
			{
				_asm
				{
					mov dx, port
					in ax, dx
				}
			}
			dword indw(word port)
			{
				_asm
				{
					mov dx, port
					in eax, dx
				}
			}
			void outb(word port, byte data)
			{
				_asm {
					mov al, data;
					mov dx, port
					out dx, al
				}
			}
			void outw(word port, word data)
			{
				_asm {
					mov ax, data;
					mov dx, port
					out dx, ax
				}
			}
			void outdw(word port, dword data)
			{
				_asm {
					mov eax, data;
					mov dx, port
					out dx, eax
				}
			}
		}
	}
}
