
namespace crt
{
	typedef void (__cdecl *_PVFV)(void);

	#pragma data_seg(".CRT$XIA")
	_PVFV __xi_a[] = { 0 };
	#pragma data_seg(".CRT$XIZ")
	_PVFV __xi_z[] = { 0 };
	#pragma data_seg(".CRT$XCA")
	_PVFV __xc_a[] = { 0 };
	#pragma data_seg(".CRT$XCZ")
	_PVFV __xc_z[] = { 0 };
	#pragma data_seg(".CRT$XPA")
	_PVFV __xp_a[] = { 0 };
	#pragma data_seg(".CRT$XPZ")
	_PVFV __xp_z[] = { 0 };
	#pragma data_seg(".CRT$XTA")
	_PVFV __xt_a[] = { 0 };
	#pragma data_seg(".CRT$XTZ")
	_PVFV __xt_z[] = { 0 };
	#pragma data_seg()  /* reset */

	#pragma comment(linker, "/merge:.CRT=.data")

	static void run(_PVFV * pfbegin,_PVFV * pfend)
	{
		for (_PVFV *p = pfbegin; p != pfend; p++)
		{
			if (*p)
				(**p)();
		}
	}

	void initialize()
	{
		run(__xi_a, __xi_z);
		run(__xc_a, __xc_z);
	}
	
	void deinitialize()
	{
		run(__xp_a, __xp_z);
		run(__xt_a, __xt_z);
	}
}