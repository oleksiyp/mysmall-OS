#include <xp/testing.h>
#include <structures/strings/string.h>
#include <structures/containers/map.h>

#ifdef TESTING
#include <stdio.h>

namespace tests
{
	using namespace structures::strings;
	using namespace structures::containers;
	class StringTU : public TestUnit
	{
	public:
		StringTU()
			: TestUnit("String test unit")
		{
		}
		virtual void test()
		{
			String s = "Hello, ";
			s += "world";
			s += "!";
			assert(s == L"Hello, world!", "string failed");
			Map<String, String> strMap;
			strMap["hello"] = "wo";
			strMap["hello"] += "rl";
			strMap["hello"] += "d";
			strMap["kernel"] = "test";
			strMap["microsoft"] = "suxx";
			assert(strMap["hello"] == "world", "sting map failed");
		}
	};
	static RegisterTestUnit unit(new StringTU());
}
#endif
