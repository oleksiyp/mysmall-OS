#include <basic/hints.h>
#include <architectures/x86/idt.h>

namespace architecture
{
	namespace x86{
		class InterruptManager
		{
			IDT_DESCRIPTOR idtTable[256];
			int disableCount;
#pragma pack (push)
#pragma pack (1)
			struct {
				word limit;
				dword base;
			} idtr;
#pragma pack (pop)
			
			void initializePIC(int pic1MappingStart, int pic2MappingStart);
		public:
			InterruptManager();
			void initialize();
			void HINT_INLINE disableInterrupts();
			void HINT_INLINE enableInterrupts();
			void maskInterrupts();
			void registerTrapHandler(byte interrupt, word selector, dword offset);
		};
	}
}