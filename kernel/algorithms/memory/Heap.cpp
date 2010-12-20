#include <config.h>
#include <xp/testing.h>
#include <algorithms/memory/heap.h>

#ifndef TESTING

const int pageSize = 4096;

class KernelAllocator
{
	dword ptr;
public:
	KernelAllocator()
	{
		clear();
	}
	void *allocate()
	{
		return (void *)(ptr += pageSize);
	}
	void *allocate(dword pages)
	{
		return (void *)(ptr += pages * pageSize);
	}
	void deallocate(void *ptr)
	{
	}
	void clear()
	{
		ptr = 0x300000;
	}	
};

using namespace algorithms::memory;
static KernelAllocator gKernelAllocator;
static Heap<pageSize, KernelAllocator> gHeap(&gKernelAllocator);

void* operator new[](unsigned int size)
{
	return gHeap.allocate(size);
}

void* operator new(unsigned int size)
{
	return gHeap.allocate(size);
}

void operator delete[](void *ptr)
{
	gHeap.deallocate(ptr);
}

void operator delete[](void *ptr, dword)
{
	gHeap.deallocate(ptr);
}

void operator delete(void *ptr)
{
	gHeap.deallocate(ptr);
}

void operator delete(void *ptr, dword)
{
	gHeap.deallocate(ptr);
}

#endif

#ifdef TESTING

#include <queue>

namespace tests
{
	template <int pages, int pageSize>
	class MyPageAllocator
	{
		byte *memory;
		byte *nextFree;
		int freeCount;
	public:
		MyPageAllocator()
		{
			memory = new byte[(pages + 1) * pageSize];
			dword ptr = (dword) memory;
			ptr = (ptr + pageSize) / pageSize;
			ptr *= pageSize;
			nextFree = (byte*)ptr;
			freeCount = pages;
		}
		void *allocate()
		{
			if (freeCount == 0)
				return 0;
			void *ptr = nextFree;
			nextFree += pageSize;
			freeCount--;
			return ptr;
		}
		void *allocate(int pages)
		{
			if (freeCount < pages)
				return 0;
			void *ptr = nextFree;
			nextFree += pageSize * pages;
			freeCount -= 
				pages;
			return ptr;
		}

		void deallocate(void *ptr)
		{
		}

		void clear()
		{
			dword ptr = (dword) memory;
			ptr = (ptr + pageSize) / pageSize;
			ptr *= pageSize;
			nextFree = (byte*)ptr;
			freeCount = pages;
		}

		~MyPageAllocator()
		{
			delete memory;
		}
	};

	class TimedBlock
	{
	public:
		int time;
		void *ptr;
	};
	bool operator <(const TimedBlock& a, const TimedBlock& b);

	using namespace std;
	using namespace algorithms::memory;

	class HeapTU : public TestUnit
	{
	public:
		HeapTU()
			: TestUnit("Heap test unit")
		{
		}
		

		virtual void test()
		{
			Heap<4096, MyPageAllocator<10000, 4096> > heap(new MyPageAllocator<10000, 4096>());

			priority_queue<TimedBlock> Q;

			int totalTime = 1000;
			int maxLatency = 100;
			for (int time = 0; time < totalTime + maxLatency; time++)
			{
				while (Q.size() && Q.top().time == time)
				{
					heap.deallocate(Q.top().ptr);
					Q.pop();
				}
				if (time < totalTime)
				{
					dword size = rand() + 1;
					void *ptr = heap.allocate(size);
					if (ptr)
					{
						int deallocate_time = time + 1 + rand() % maxLatency;
						TimedBlock b;
						b.time = deallocate_time;
						b.ptr = ptr;
						Q.push(b);
					}
				}
			}
		}
	};

	static RegisterTestUnit unit(new HeapTU());
}
#endif