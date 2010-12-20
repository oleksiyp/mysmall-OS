#include <xp/testing.h>
#include <structures/containers/map.h>

#ifdef TESTING
#include <stdio.h>

namespace tests
{
	using namespace structures::containers;
	class MapTU : public TestUnit
	{
	public:
		MapTU()
			: TestUnit("Map test unit")
		{
		}

		virtual void test()
		{
			Map<int, int> amap;
			for (int i = 0;	i < 100; i++)
				amap[i] = i * i;
			assert(amap.contains(5), "array failure");
			assert(amap[5] == 25, "array failure");
		}
	};
	static RegisterTestUnit unit(new MapTU());
}


#endif