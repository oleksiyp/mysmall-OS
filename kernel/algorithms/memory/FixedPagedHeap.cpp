#include <algorithms/memory/fixedpagedheap.h>
#include <basic/memory.h>
#include <xp/testing.h>

#ifdef TESTING

#pragma warning (disable : 4786)
#include <queue>

namespace tests
{
	using namespace std;

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
			freeCount--;
			if (freeCount == 0)
				return 0;
			void *ptr = nextFree;
			nextFree += pageSize;
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

	using namespace algorithms::memory;
	MyPageAllocator<10, 4096> a;
	FixedPagedHeap<1, 4096, MyPageAllocator<10, 4096> > fixedPageHeap(&a);
	
	class TimedBlock
	{
	public:
		int time;
		void *ptr;
	};
	bool operator <(const TimedBlock& a, const TimedBlock& b)
	{
		return a.time > b.time;
	}
	class FixedPagedHeapTU : public TestUnit
	{
	public:
		FixedPagedHeapTU()
			: TestUnit("Fixed paged heap test unit")
		{
		}
		

		virtual void test()
		{
			dword blockSize = fixedPageHeap.getSizeOfBlock();
			assert(blockSize <= 4096, "Block size greater than page size");

			priority_queue<TimedBlock> Q;

			int totalTime = 1000;
			int maxLatency = 100;
			for (int time = 0; time < totalTime + maxLatency; time++)
			{
				while (Q.size() && Q.top().time == time)
				{
					fixedPageHeap.deallocate(Q.top().ptr);
					Q.pop();
				}
				if (time < totalTime)
				{
					void *ptr = fixedPageHeap.allocate();
					if (ptr)
					{
						int deallocate_time = time + 1 + rand() % maxLatency;
						TimedBlock b;
						b.time = deallocate_time;
						b.ptr = ptr;
						Q.push(b);
					} else {
						dword space = fixedPageHeap.getAllocatedPages() * fixedPageHeap.getPageSize();
						dword filledSpace = fixedPageHeap.getAllocatedUnits() * fixedPageHeap.getUnitSize();
						char buf[100];
						sprintf(buf, "no free space, %.2f%% filled\n", 100. * (double)filledSpace / space);
						assert(false, buf);
					}
				}
			}
			dword unitsPerPage = fixedPageHeap.getUnitsPerPage();
			dword pages = fixedPageHeap.getAllocatedPages();
			dword units = fixedPageHeap.getAllocatedUnits();
			assert(units == 0, "Not all units were deallocated");

			fixedPageHeap.clear();
			vector<void *> v;
			while (1)
			{
				void *ptr = fixedPageHeap.allocate();
				if (!ptr)
				{
					dword space = fixedPageHeap.getAllocatedPages() * fixedPageHeap.getPageSize();
					dword filledSpace = fixedPageHeap.getAllocatedUnits() * fixedPageHeap.getUnitSize();
					break;
				}
				v.push_back(ptr);				
			}
			for (int i = 0; i < v.size(); i++)
				fixedPageHeap.deallocate(v[i]);

			v.clear();
			units = fixedPageHeap.getAllocatedUnits();
			assert(units == 0, "Not all units were deallocated");
		}
	};

	static RegisterTestUnit unit(new FixedPagedHeapTU());
}

#endif
