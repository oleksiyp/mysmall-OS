#include "simple_io.h"

typedef struct
{
	char c;
	unsigned char a;
} CHAR_ATTR;

static CHAR_ATTR* const textVideoMemory = (CHAR_ATTR*)0xB8000;

SimpleIO gSimpleIO;

void SimpleIO::putc(int row, int col, char c)
{
	textVideoMemory[row * 80 + col].c = c;
	textVideoMemory[row * 80 + col].a = 0x7;
}

void SimpleIO::putc(char c)
{
	switch(c)
	{
		case '\n': row++; col = 0; break;
		case '\t': putc(' '); putc(' '); putc(' '); putc(' '); break;
		default:
			putc(row, col, c);
			col++;
			if (col >= 80)
				row++, col = 0;
	}
}

void SimpleIO::puts(char *c)
{
	while(*c)
		putc(*c++);
}

SimpleIO::SimpleIO()
{
	row = col = 0;
}

void SimpleIO::clear()
{
	for (int row = 0; row < 25; row++)
		for (int col = 0; col < 80; col++)
		{
			textVideoMemory[row * 80 + col].c = ' ';
			textVideoMemory[row * 80 + col].a = 0x7;
		}

}