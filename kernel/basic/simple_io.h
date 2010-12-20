#ifndef _SIMPLE_IO_H_
#define _SIMPLE_IO_H_

class SimpleIO
{
	int row, col;	
public:
	SimpleIO();
	void putc(int row, int col, char c);
	void putc(char c);
	void puts(char *c);
	void clear();
};

extern SimpleIO gSimpleIO;

#endif _SIMPLE_IO_H_