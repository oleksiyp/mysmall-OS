#ifndef _UTILITY_H_
#define _UTILITY_H_

namespace utility
{
	template <class type>
	void swap(type &arg1, type &arg2)
	{
		type arg = arg1;
		arg1 = arg2;
		arg2 = arg;
	}
}

#endif