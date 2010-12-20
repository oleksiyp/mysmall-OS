#ifndef _CHARACTER_H_
#define _CHARACTER_H_

namespace character
{
	template <class character>
	static bool isDigit(character c)
	{
		return (c >= '0' && c <= '9');
	}
	template <class character>
	static int compare(character c1, character c2)
	{
		if (c1 > c2)
			return 1;
		if (c1 < c2)
			return -1;
		return 0;
	}

	template <class character>
	static character toDigit(dword digit)
	{
		if (digit >= 0 && digit <= 9)
			return (character)(digit + '0');
		return (character)(digit - 10 + 'A');
	}
};

#endif