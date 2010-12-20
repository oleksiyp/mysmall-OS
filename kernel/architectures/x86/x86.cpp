#include <architectures/x86/x86.h>
#include <basic/formater.h>
#include <basic/simple_io.h>

namespace architecture
{
	namespace x86
	{
		x86SubSystem::x86SubSystem()
		{
			physicalMemorySize = 0;
		}
		void x86SubSystem::initialize()
		{
			interruptManager.initialize();
			physicalMemorySize = 32 * 1024 * 1024;
			gSimpleIO.puts("hi");
		}
		x86SubSystem gX86;
	}
}
