#ifndef _FIXED_PAGED_HEAP_H_
#define _FIXED_PAGED_HEAP_H_
#include <basic/types.h>
#include <basic/memory.h>

namespace algorithms
{
	namespace memory
	{
		template <int unitSize, int pageSize, class AllocatorType>
		class FixedPagedHeap
		{
			AllocatorType *allocator;
#define unitsPerBlock (((pageSize - 12) * 8 / (8 * unitSize + 1)))
			typedef byte Unit[unitSize];
			typedef struct _Block
			{
				void *heapPtr;
				struct _Block *prev, *next;
				byte filledBitMap[(unitsPerBlock+7) / 8];
				Unit units[unitsPerBlock];
				
				void *allocate()
				{
					for (dword i = 0; i < sizeof(filledBitMap); i++)
					{
						byte b = filledBitMap[i];
						if (b != 0xFF)
						{
							byte mask = 1;
							for (int j = 0; j < 8 && ((i << 3) + j < unitsPerBlock); j++)
							{
								if (!(b & 1))
								{
									filledBitMap[i] |= mask;
									return (void *)&units[(i << 3) + j];
								}
								b >>= 1;
								mask <<= 1;
							}
						}
					}
					return 0;
				}
				
				void deallocate(void *ptr)
				{
					dword idx = (Unit *)ptr - units;
					if (idx >= 0 && idx < unitsPerBlock && basic::memory::getBit(filledBitMap, idx) == 1)
					{
						basic::memory::setBit(filledBitMap, idx, 0);
						basic::memory::fillZeros(&units[idx], unitSize);			
					}
				}
				
				void initialize(void *heapPtr)
				{
					basic::memory::fillZeros(this, pageSize);			
					this->heapPtr = heapPtr;
				}
			} Block;
			Block *firstBlock;
			Block *currentBlock;
			
			dword statUnits, statPages;
public:
			FixedPagedHeap(AllocatorType *allocator)
			{
				firstBlock = 0;
				currentBlock = 0;
				statUnits = 0;
				statPages = 0;
				this->allocator = allocator;
			}
			~FixedPagedHeap()
			{
				clear();
			}
			
			void clear()
			{
				if (currentBlock)
				{
					void *sentinel = currentBlock;
					do
					{
						Block *next = currentBlock->next;
						allocator->deallocate(currentBlock);
						currentBlock = next;
					} while(sentinel != currentBlock);
				}
				allocator->clear();
				currentBlock = 0;
				firstBlock = 0;
				statUnits = 0;
				statPages = 0;
			}
			void *allocate()
			{
				if (currentBlock)
				{
					void *sentinel = currentBlock;
					do
					{
						void *ptr = currentBlock->allocate();
						if (ptr)
						{
							statUnits++;
							return ptr;
						}
						currentBlock = currentBlock->next;
					} while(sentinel != currentBlock);
				}
				
				void *page = allocator->allocate();
				if (!page)
					return 0;
				
				statPages++;
				
				currentBlock = (Block *)page;
				currentBlock->initialize(this);
				void *ptr = currentBlock->allocate();
				if (!ptr)
					return 0;
				
				Block *last = firstBlock ? firstBlock->prev : 0;
				
				currentBlock->next = firstBlock;
				currentBlock->prev = last;
				
				if (firstBlock)
				{
					last->next = currentBlock;
					firstBlock->prev = currentBlock;
				} else {
					firstBlock = currentBlock;
					currentBlock->next = currentBlock;
					currentBlock->prev = currentBlock;
				}
				
				statUnits++;
				return ptr;
			}
			
			bool deallocate(void *ptr)
			{
				dword page = (dword)ptr;
				page /= pageSize;
				page *= pageSize;		
				Block *b = (Block*)page;
				if (b->heapPtr == (void*)this)
				{
					b->deallocate(ptr);
					statUnits--;
					return true;
				}
				return false;
			}
			
			dword getAllocatedUnits()
			{
				return statUnits;
			}
			dword getAllocatedPages()
			{
				return statPages;
			}
			dword getUnitsPerPage()
			{
				return unitsPerBlock;
			}
			dword getSizeOfBlock()
			{
				return sizeof(Block);
			}
			
			dword getUnitSize()
			{
				return unitSize;
			}
			
			dword getPageSize()
			{
				return pageSize;
			}
#ifdef TESTING
			void memoryStat()
			{
				if (firstBlock)
				{
					printf("Fixed blocks(size = %d):\n", unitSize);
					void *sentinel = firstBlock;
					Block *block = firstBlock;
					do
					{
						for (dword i = 0; i < unitsPerBlock; i++)
						{
							if (basic::memory::getBit(block->filledBitMap, i))
							{
								dword ptr = (dword)&(block->units[i]);
								dword size = unitSize;
								printf("0x%08X - 0x%08X (%d bytes)\n", 
									ptr, ptr + size, size);
							}
						}
						block = block->next;
					} while(sentinel != block);
				}
			}
#endif
		};
	}
}

#endif