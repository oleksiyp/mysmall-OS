#ifndef _X86_H_
#define _X86_H_

#include <basic/types.h>
#include <architectures/x86/InterruptManager.h>

namespace architecture
{
	namespace x86{
		class x86SubSystem
		{
			dword physicalMemorySize;
			InterruptManager interruptManager;
		public:
			x86SubSystem();
			void initialize();
		};
		extern x86SubSystem gX86;
	}
}

#endif