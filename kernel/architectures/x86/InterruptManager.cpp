#include <architectures/x86/InterruptManager.h>
#include <architectures/x86/io.h>
#include <basic/types.h>
#include <main/bsod.h>

namespace architecture
{
	namespace x86
	{
		static void _declspec(naked) generalBSODHandler()
		{
			_asm { // restore segments and stack
				mov ax, 16
				mov ds, ax
				mov es, ax
				mov ss, ax
				mov sp, 0x300000
			}
			main::bsod("Unknown interrupt happend");
		}

		extern "C" void c_x86_int_timerHandler()
		{
		}

		extern "C" void x86_int_timerHandler();

		InterruptManager::InterruptManager()
		{
			disableCount = 1;
		}
		void InterruptManager::initialize()
		{
			idtr.limit = 256;
			idtr.base = (dword)idtTable;
			
			for (int i = 0; i < 255; i++)
				registerTrapHandler(i, 8, (dword)generalBSODHandler);
			
			for (i = 0; i < 255; i++)
				registerTrapHandler(i, 8, (dword)x86_int_timerHandler);

			dword pidtr = (dword)&idtr;
			_asm 
			{
				mov eax, pidtr
				lidt [eax]
			}
			initializePIC(0x20, 0x28);
			_asm sti
		}
		void HINT_INLINE InterruptManager::disableInterrupts()
		{
			disableCount++;
			if (disableCount == 1)
			{
				_asm int 3
				_asm cli;
			}
		}

		void HINT_INLINE InterruptManager::enableInterrupts()
		{
			disableCount--;
			if (disableCount == 0)
			{
				_asm sti;
			}
		}

		void InterruptManager::maskInterrupts()
		{
			
		}

		void InterruptManager::registerTrapHandler(byte interrupt, word selector, dword offset)
		{
			INTERRUPT_DESCRIPTOR descr;
			descr.type = INERRUPT_DESCRIPTOR_TYPE;
			descr.null = 0;
			descr.dpl = 0;
			descr.p = 1;
			descr.reserved1 = 0;
			descr.offset1 = (word)(offset);
			descr.offset2 = (word)(offset >> 16);
			descr.segmentSelector = selector;

			disableInterrupts();
			idtTable[interrupt].interrupt = descr;
			enableInterrupts();
		}
			
		void InterruptManager::initializePIC(int pic1MappingStart, int pic2MappingStart)
		{
			const int ICW1 = 0x11, ICW4 = 0x01;
			const int PIC1 = 0x20, PIC2 = 0xA0;
			/* send ICW1 */
			io::outb(PIC1, ICW1);
			io::outb(PIC2, ICW1);

			/* send ICW2 */
			io::outb(PIC1 + 1, pic1MappingStart);	/* remap */
			io::outb(PIC2 + 1, pic2MappingStart);	/*  pics */

			/* send ICW3 */
			io::outb(PIC1 + 1, 4);	/* IRQ2 -> connection to slave */
			io::outb(PIC2 + 1, 2);

			/* send ICW4 */
			io::outb(PIC1 + 1, ICW4);
			io::outb(PIC2 + 1, ICW4);

			/* disable all IRQs */
			io::outb(PIC1 + 1, 0xFE);
		}
	}
}