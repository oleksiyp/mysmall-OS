#ifndef _OPERATORS_H_
#define _OPERATORS_H_

namespace algorithms
{
	namespace utility
	{
		namespace operators
		{
			template <class T>
				class Less
			{
			public:
				bool operator() (const T& x, const T& y) const
				{
					return x < y;
				}
			};
			
			template <class T>
				class Greater
			{
			public:
				bool operator() (const T& x, const T& y) const
				{
					return x > y;
				}
			};
			
			template <class T>
				class Equal
			{
			public:
				bool operator() (const T& x, const T& y) const
				{
					return x == y;
				}
			};
			
			template <class T>
				class GreaterEqual
			{
			public:
				bool operator() (const T& x, const T& y) const
				{
					return x >= y;
				}
			};
			
			template <class T>
				class LessEqual
			{
			public:
				bool operator() (const T& x, const T& y) const
				{
					return x <= y;
				}
			};
		}		
	}
}

#endif