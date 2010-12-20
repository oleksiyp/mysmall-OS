#include <windows.h>
#include <stdio.h>

char bufName[30] = "intercept.dll";

void main(int argc, char *argv[])
{
	try
	{
		if (argc == 1)
			throw "Not enough arguments";
		STARTUPINFO si;
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		si.wShowWindow = SW_SHOW;
		PROCESS_INFORMATION pi;
		if (!CreateProcess(argv[1], 0, 0, 0, 0, CREATE_SUSPENDED | DETACHED_PROCESS, 0, 0, &si, &pi))
			throw "Failed to create process";
		

		HANDLE hProc = pi.hProcess;
		LPVOID ptr = VirtualAllocEx(hProc, 0, 4096, MEM_COMMIT, PAGE_READWRITE);
		if (!ptr)
			throw "Failed to allocate memory in it";
		
		DWORD written = 0;
		BOOL ret = WriteProcessMemory(hProc, ptr, bufName, sizeof(bufName), &written);
		if (!ret || written != sizeof(bufName))
			throw "Failed to write to memory";
		HMODULE hKernel = GetModuleHandle("kernel32.dll");
		
		void *loadLib = GetProcAddress(hKernel, "LoadLibraryA");
		DWORD id;
		HANDLE hThread = CreateRemoteThread(hProc, 0, 0, (LPTHREAD_START_ROUTINE) loadLib, ptr, 0, &id);
		
		if(hThread == INVALID_HANDLE_VALUE)
			throw "Failed to create remote thread";

		WaitForSingleObject(hThread, INFINITE);

		ResumeThread(pi.hThread);
		
		CloseHandle(hThread);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	} catch(char *message) {
			printf("error: %s\n", message);
	}
}