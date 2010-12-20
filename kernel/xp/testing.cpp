#include <xp/testing.h>

#ifdef TESTING

#include <list>
using namespace std;

TestUnit::TestUnit(char *testName) { this->testName = testName; }
TestUnit::~TestUnit() { }

TestUnit::AssertionFault::AssertionFault(char *reason) { this->reason = reason; }
char *TestUnit::AssertionFault::getReason() { return reason; }		

void TestUnit::assert(bool expression, char *string)
{
	if (!expression)
		throw AssertionFault(string);
}
void TestUnit::fail(char *string) { assert(false, string); }
char *TestUnit::name() { return testName; }

static list <TestUnit *> *gRegisteredUnits = 0;
static list <TestUnit *> &registeredUnits()
{
	if (!gRegisteredUnits)
		gRegisteredUnits = new list <TestUnit *>();
	return *gRegisteredUnits;
}

RegisterTestUnit::RegisterTestUnit(TestUnit *unit)
{
	registeredUnits().push_back(unit);
}


void main(void)
{
	list <TestUnit *> units = registeredUnits();

	printf("XPOS test suit\n ---- \n");
	for (list <TestUnit *>::iterator it = units.begin(); it != units.end(); it++)
	{
		TestUnit *unit = *it;
		try
		{
			unit->test();
			printf(" [+] %40s\n", unit->name());
		} catch(TestUnit::AssertionFault fault)
		{
			printf(" [-] %40s\n", unit->name());
			if (fault.getReason())
				printf("\tfault reason: %s\n", fault.getReason());
		}
	}
}

#endif TESTING
