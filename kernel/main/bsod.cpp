#include <basic/simple_io.h>

namespace main
{
	void bsod(char *message)
	{
		gSimpleIO.clear();
		gSimpleIO.puts("\"BSOD\"\n");
		gSimpleIO.puts("\n");
		gSimpleIO.puts("message: ");
		gSimpleIO.puts(message);
		while(1) {}
	}
}