#include <basic/memory.h>
#include <basic/utility.h>

namespace basic
{
	namespace memory
	{
		void copy(void *dest, const void *src, dword len)
		{
			if (src == dest)
				return;
			if (src < dest) { //go backward
				dword i = len;
				do
				{
					i--;
					((byte *)dest)[i] = ((byte *)src)[i];
				} while(i != 0);
			} else { // go forward
				for (dword i = 0; i < len; i++)
					((byte *)dest)[i] = ((byte *)src)[i];
			}
		}
		
		void reverse(void *buffer, dword len)
		{
			for (dword i = 0; i < len >> 1; i++)
				utility::swap(((char*)buffer)[i], ((char*)buffer)[len - i - 1]);
		}

		void fillZeros(void *buffer, dword len)
		{
			for (dword i = 0; i < len; i++)
				((char*)buffer)[i] = 0;
		}
		void setBit(void *buffer, dword idx, byte value)
		{
			byte *buf = (byte*)buffer;
			byte mask = 1 << (idx & 7);
			idx >>= 3;
			buf[idx] = (buf[idx] & ~mask) | (value ? mask : 0);
		}

		byte getBit(void *buffer, dword idx)
		{
			byte *buf = (byte*)buffer;
			byte mask = 1 << (idx & 7);
			idx >>= 3;
			return (buf[idx] & mask) == mask;
		}

	}
}
