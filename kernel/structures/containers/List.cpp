#include <xp/testing.h>
#include <structures/containers/list.h>

#ifdef TESTING
#include <stdio.h>

namespace tests
{
	using namespace structures::containers;
	class ListTU : public TestUnit
	{
	public:
		ListTU()
			: TestUnit("List test unit")
		{
		}

		virtual void test()
		{
			List<int> aList;
			aList.insertTail(10);
			aList.insertTail(20);
			aList.insertTail(30);
			aList.insertTail(40);
			aList.insertTail(50);
			aList.insertTail(60);
			aList.insertAfter(aList.getTail(), 80);
			aList.insertBefore(aList.getTail(), 70);
			typedef List<int>::Iterator MyIt;
			MyIt it = aList.getHead();
			int i = 0;
			while(it)
			{
				aList[it] = i++;
				it = aList.next(it);
			}
			it = aList.getTail();
			while(it)
			{
				assert(aList[it] == --i, "failed");
				it = aList.prev(it);
			}
			it = aList.getTail();
			while(it)
			{
				MyIt previt = aList.prev(it);
				aList.remove(it);
				it = previt;
			}
			assert(aList.getSize() == 0, "not all elements deleted");
		}
	};
	static RegisterTestUnit unit(new ListTU());
}
#endif