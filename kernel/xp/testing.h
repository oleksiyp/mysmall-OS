#ifndef _TESTING_H_
#define _TESTING_H_

#ifdef TESTING

class TestUnit
{
	char *testName;
public:
	TestUnit(char *testName);
	virtual ~TestUnit();
	class AssertionFault
	{
		char *reason;
	public:
		AssertionFault(char *reason);
		char *getReason();
	};
	virtual void test(void) = 0;
	void assert(bool expression, char *string = 0);
	void fail(char *string = 0);
	char *name();
};

class RegisterTestUnit
{
public:
	RegisterTestUnit(TestUnit *unit);
};

#endif

#endif