#ifndef _MEMORY_H_
#define _MEMORY_H_

#include <basic/types.h>

namespace basic
{
	namespace memory
	{
		void copy(void *dest, const void *src, dword len);
		void reverse(void *buffer, dword len);
		void fillZeros(void *buffer, dword len);
		void setBit(void *buffer, dword idx, byte value);
		byte getBit(void *buffer, dword idx);
	}
}

#endif