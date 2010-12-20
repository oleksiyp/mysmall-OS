#ifndef _CSTRING_H_
#define _CSTRING_H_

#include <basic/memory.h>
#include <basic/character.h>

namespace basic
{
	namespace cstring
	{	
		template <class character>
		dword length(const character *string)
		{
			dword len = 0;
			while(*string++)
				len++;
			return len;
		}
		template <class character>
		void copy(character *dest, const character *src)
		{
			dword len = length(src);
			memory::copy(dest, src, sizeof(character)*(len + 1));
		}
		template <class character>
		int compare(character *arg1, character *arg2)
		{
			dword i = 0;
			while (1)
			{
				if (arg1[i] == 0 && arg2[i] == 0) return 0;
				if (arg1[i] == 0 && arg2[i] != 0) return -1;
				if (arg1[i] != 0 && arg2[i] == 0) return 1;

				int r = character::compare(arg1[i], arg2[i]);
				if (r != 0)
					return r;
				i++;
			}
		}
		template <class character>
		void reverse(character *str)
		{
			memory::reverse(str, length(str));
		}
		template <class character>
		void fill(character *str, character c, dword len)
		{
			for (dword i = 0; i < len; i++)
				str[i] = c;
		}
	}
}

#endif