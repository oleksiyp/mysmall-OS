#include <windows.h>

void main(void)
{
	LoadLibrary("intercept.dll");
	MessageBox(0, "Герыч - хороший челевек", "Дифуры - классно", MB_ICONSTOP);
	ExitProcess(0);
}

void EntryPoint(void) { main(); }