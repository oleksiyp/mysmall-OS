#ifndef _STRING_H_
#define _STRING_H_

#include <basic/types.h>
#include <structures/containers/list.h>
#include <basic/cstring.h>
#include <basic/memory.h>

namespace structures
{
	namespace strings
	{
		using namespace basic;
		using namespace structures::containers;
		class String
		{
			typedef word wchar;

			class StringShared
			{
				dword refCount;
				wchar *block;
				dword size;
				dword length;
			public:
				StringShared(dword size = 0)
				{
					refCount = 1;
					if (size != 0)
						block = new wchar[size];
					else
						block = 0;
					this->size = size;
				}
				~StringShared()
				{
					if (block)
						delete block;
				}
				
				void incRefCount()
				{
					refCount++;
				}

				bool decRefCount()
				{
					refCount--;
					return (refCount == 0);
				}

				wchar *data()
				{
					return block;
				}

				void setLength(dword len)
				{
					length = len;
				}

				dword getLength()
				{
					return length;
				}
			};

			typedef List<StringShared *> SStrList;
			typedef SStrList::Iterator SSListIt;
			SStrList subStrings;
			dword length;
		public:
			String()
			{
			}

			String(const String& str)
			{
				append(str);
			}

			String(char *str)
			{
				dword len = cstring::length(str);
				StringShared *s = new StringShared(len+1);
				for (dword i = 0; i <= len; i++)
					s->data()[i] = str[i];
				s->setLength(len);
				subStrings.insertTail(s);
				length = len;
			}
			
			String(wchar *str)
			{
				dword len = cstring::length(str);
				StringShared *s = new StringShared(len+1);
				memory::copy(s->data(), str, (len+1) * sizeof(wchar));
				s->setLength(len);
				subStrings.insertTail(s);
				length = len;
			}

			~String()
			{
				clear();
			}

			void clear()
			{
				for(SSListIt it = subStrings.getHead(); it; it = subStrings.next(it))
				{
					if (subStrings[it]->decRefCount())
						delete subStrings[it];
				}
				subStrings.clear();
				length = 0;
			}


			void append(const String &str)
			{
				SStrList list = str.subStrings.copy();
				SSListIt it = subStrings.insertTail(list);
				while (it)
				{
					subStrings[it]->incRefCount();
					it = subStrings.next(it);
				}
				length += str.length;
			}
			friend String operator +(const String &a, const String &b);
			String &operator +=(const String &a)
			{
				append(a);
				return *this;
			}

			void pack(void)
			{
				if (subStrings.getSize() <= 1)
					return;
				StringShared *s = new StringShared(length+1);
				SSListIt it = subStrings.getHead();
				dword l = 0;
				while (it)
				{
					StringShared *str = subStrings[it];
					dword len = str->getLength();
					memory::copy(s->data()+l, str->data(), len * sizeof(wchar));
					l += len;
					if (str->decRefCount())
						delete str;
					it = subStrings.next(it);
				}
				s->data()[l] = 0;
				s->setLength(l);
				subStrings.clear();
				length = l;
				subStrings.insertTail(s);
			}
			wchar *cStr()
			{
				pack();
				if (subStrings.getHead() == 0)
					return L"";
				StringShared *s = subStrings[subStrings.getHead()];
				return s->data();
			}
			wchar &at(dword pos)
			{
				pack();
				return cStr()[pos];
			}
			int compare(const String &bstr) const
			{
				String *nonConstA = const_cast<String *>(this);
				String *nonConstB = const_cast<String *>(&bstr);
				wchar *a = nonConstA->cStr();
				wchar *b = nonConstB->cStr();
				
				for(dword i = 0; a[i] && b[i]; i++)
				{
					if (a[i] > b[i])
						return 1;
					if (a[i] < b[i])
						return -1;
				}
				if (a[i] && !b[i])
					return 1;
				if (!a[i] && b[i])
					return -1;
				return 0;
			}

			String &operator =(const String &b)
			{
				if (&b == this)
					return *this;
				clear();
				append(b);
				return *this;
			}
		};

		String operator +(const String &a, const String &b)
		{
			String s;
			s.append(a);
			s.append(b);
			return s;
		}

		bool operator <(const String &a, const String &b)
		{
			return a.compare(b) == -1;
		}

		bool operator >(const String &a, const String &b)
		{
			return a.compare(b) == 1;
		}

		bool operator ==(const String &a, const String &b)
		{
			return a.compare(b) == 0;
		}
	}
}

#endif
