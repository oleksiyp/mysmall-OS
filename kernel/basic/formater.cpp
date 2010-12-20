#include <xp/testing.h>
#include <basic/types.h>
#include <basic/memory.h>
#include <basic/cstring.h>
#include <basic/character.h>
#include <basic/formater.h>

namespace basic
{
	Formater::Formater(char *buffer, char *format)
	{
		this->buffer = buffer;
		this->format = format;
		cstring::copy(buffer, format);
		bufferLen = cstring::length(buffer);
		currentArg = 1;
	}
	
	Formater &Formater::text(char *text, dword width, int align)
	{
		dword len = cstring::length(text);
		for (dword i = 0; i < bufferLen; i++)
		{
			if (buffer[i] == '%')
			{
				dword j = i + 1;
				int argnum = 0;
				if (buffer[j] == '{')
				{
					j++;
					while(character::isDigit(buffer[j]))
					{
						argnum = argnum * 10 + int(buffer[j] - '0');
						j++;
					}
					//if (buffer[j] != '}')
//						throw FormatingException();
				} else if (character::isDigit(buffer[j])) {
					argnum = buffer[j] - '0';
				} else if (buffer[j] == '%') {
					continue;
				} else {
				//	throw FormatingException();
				}
				j++;
				if (argnum == currentArg)
				{
					dword myLen = (len < width) ? width : len;

					memory::copy(buffer + i + myLen, buffer + j, bufferLen - j + 1);
					int dif = myLen - len;
					if (align > 0)
					{
						memory::copy(buffer + i, text, len);
						cstring::fill(buffer + i + len, ' ', dif);
					} else if(align < 0) {
						memory::copy(buffer + i + dif, text, len);
						cstring::fill(buffer + i, ' ', dif);
					} else if(align == 0) {
						dif /= 2;
						memory::copy(buffer + i + dif, text, len);
						int dif2 = myLen - len - dif;
						cstring::fill(buffer + i + dif + len, ' ', dif2);
						cstring::fill(buffer + i, ' ', dif);
					}

					bufferLen += myLen - (j - i);
					i += myLen - 1;
				} else {
					i = j - 1;
				}
			}
		}
		currentArg++;
		return *this;
	}
	
	Formater &Formater::numeric(dword num, int width, int system, int align)
	{
		char buf[50];
		if (num == 0)
		{
			buf[0] = '0';
			buf[1] = 0;
		} else {
			int i = 0;
			while(num)
			{
				buf[i] = character::toDigit<char>(num % system);
				num /= system;
				i++;
			}
			buf[i] = 0;
		}
		cstring::reverse(buf);
		return text(buf, width, align);
	}

	Formater &Formater::numeric(int num, int width, int system, int align)
	{ 
		char buf[50];
		if (num == 0)
		{
			buf[0] = '0';
			buf[1] = 0;
		} else {
			bool sign = num < 0;
			if (sign) num = -num;

			int i = 0;
			while(num)
			{
				buf[i] = character::toDigit<char>(num % system);
				num /= system;
				i++;
			}
			if (sign) buf[i++] = '-';
			buf[i] = 0;
		}
		cstring::reverse(buf);
		return text(buf, width, align);
	}

	Formater &Formater::numeric(double d, int width, int precision, int align)
	{
		return text("", width, align);
	}

	Formater &Formater::character(char c, int width, int align)
	{
		char buf[2] = {c, 0};
		return text(buf, width, align);
	}
}

#ifdef TESTING

namespace tests
{
	using namespace basic;

	class FormaterTU : public TestUnit
	{
	public:
		FormaterTU()
			: TestUnit("String formating test unit")
		{

		}
		virtual void test()
		{
			char buf[100];
			
			Formater(buf, "Hello world").text("test");
			assert(cstring::compare(buf, "Hello world") == 0);

			Formater(buf, "Hello world, %1").text("test");
			assert(cstring::compare(buf, "Hello world, test") == 0);

			Formater(buf, "%{1} %2 %{1} %1").text("test").numeric(-3423);
			assert(cstring::compare(buf, "test -3423 test test") == 0);
			
			Formater(buf, "%{1}%2").numeric(-3423).numeric(532).numeric(6666);
			assert(cstring::compare(buf, "-3423532") == 0);

			Formater(buf, "--%{1}--").text("hello world", 20, 0);
			assert(cstring::compare(buf, "--    hello world     --") == 0);

			Formater(buf, "--%{1}--").text("hello world", 20, -1);
			assert(cstring::compare(buf, "--         hello world--") == 0);

			Formater(buf, "--%{1}--").text("hello world", 20, 1);
			assert(cstring::compare(buf, "--hello world         --") == 0);

			Formater(buf, "0x%{1} = %2b").numeric(255, 0, 16).numeric(255, 0, 2);
			assert(cstring::compare(buf, "0xFF = 11111111b") == 0);

			Formater(buf, "%{1}%1%{1}").character('x');
			assert(cstring::compare(buf, "xxx") == 0);

			Formater(buf, "%{1}%1%{1}").character('x', 9, -1);
			assert(cstring::compare(buf, "        x        x        x") == 0);

			Formater(buf, "%{1}%1%{1}").character('x', 9, 0);
			assert(cstring::compare(buf, "    x        x        x    ") == 0);

			Formater(buf, "%{1}%1%{1}").character('x', 9, 1);
			assert(cstring::compare(buf, "x        x        x        ") == 0);
		}
	};

	static RegisterTestUnit unit(new FormaterTU());
}

#endif