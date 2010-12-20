#include <basic/simple_io.h>
#include <basic/crt.h>
#include <basic/cstring.h>
#include <basic/formater.h>
#include <architectures/main.h>


void __declspec(dllexport) EntryPoint(void)
{
	crt::initialize();

	gSimpleIO.clear();
	gSimpleIO.puts("hi!\n");
	architecture::initialize();



	__asm {
		hlt
x:	jmp x
	}
}