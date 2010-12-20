#ifndef _FORMATER_H_
#define _FORMATER_H_

#include <basic/types.h>

namespace basic
{
	class Formater
	{
		char *buffer;
		char *format;
		int currentArg;
		dword bufferLen;
	public:
		class FormatingException {};

		Formater(char *buffer, char *format);
		Formater &text(char *text, dword width = 0, int align = -1);
		Formater &numeric(dword num, int width = 0, int system = 10, int align = -1);
		Formater &numeric(int num, int width = 0, int system = 10, int align = -1);
		Formater &numeric(double d, int width = 0, int precision = 0, int align = -1);
		Formater &character(char c, int width = 0, int align = -1);
	};
}

#endif