#ifndef _X86_IO_H_
#define _X86_IO_H_

#include <basic/types.h>

namespace architecture
{
	namespace x86
	{
		namespace io
		{
			byte inb(word port);
			word inw(word port);
			dword indw(word port);
			void outb(word port, byte data);
			void outw(word port, word data);
			void outdw(word port, dword data);
		}
	}
}

#endif