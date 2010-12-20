#include "stdafx.h"
#include "intercept.h"

SOCKET debugEventSocket = 0;

class SocketException {};
class ReadSocketException : public SocketException {};
class WriteSocketException : public SocketException {};

extern FILE *log;

void Recv(SOCKET socket, LPVOID data, int count)
{
	char *buf = (char *)data;
	int read = 0;
	while(read < count)
	{
		int c = recv(socket, buf, count - read, 0);
		if (c == -1)
			throw ReadSocketException();
		buf += c;
		read += c;
	}
}

void Send(SOCKET socket, LPCVOID data, int count)
{
	int c = send(socket, (char*)data, count, 0);
	if (c <= 0) throw WriteSocketException();
	if (!c == count)
		throw WriteSocketException();
}

SOCKET connectServer(char *ip, int port)
{
	SOCKET s;
	s = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addr = {AF_INET, htons(port)};
	addr.sin_addr.S_un.S_addr = inet_addr(ip);
	if (connect(s, (sockaddr *)&addr, sizeof(addr)) != 0)
	{
		fprintf(log, "Failed to connect %s:%d\n", ip, port);
		fflush(log);
		closesocket(s);
		return 0;
	}
	
	return s;
}

void initRemoteDebugging()
{
	WORD ver = MAKEWORD(1, 1);
	WSADATA data;
	WSAStartup(ver, &data);

	debugEventSocket = connectServer("127.0.0.1", 1523);
	if (debugEventSocket < 0)
		debugEventSocket = 0;
}

#define S(data) Send(s, &data, sizeof(data))
#define R(data) Recv(s, &data, sizeof(data))
void SConst(SOCKET s, DWORD c)
{
	S(c);
}
DWORD RConst(SOCKET s)
{
	DWORD dw;
	R(dw);
	return dw;
}

void SendZString(SOCKET s, const char *str)
{
	if (!str)
	{
		SConst(s, 0);
		return;
	}
	SConst(s, 1);
	DWORD len = strlen(str);
	SConst(s, len);
	Send(s, str, len);
}

#define TESTPROTOIN(param) if (RConst(s) != param) { fprintf(log, "prtotcol failure\n"); fflush(log); }
#define TESTPROTOOUT(param) SConst(s, param)

#define Sq(pdata) if (pdata) SConst(s, 0); else { SConst(s, 1); S(*pdata); }
#define Szs(str) SendZString(s, str);

#define DRPC_WAIT_FOR_DEBUG_EVENT      0x666001
#define DRPC_WRITE_PROCESS_MEMORY      0x666002
#define DRPC_DEBUG_ACTIVE_PROCESS      0x666003
#define DRPC_CONTINUE_DEBUG_EVENT      0x666004
#define DRPC_GET_THREAD_CONTEXT        0x666005
#define DRPC_GET_THREAD_SELECTOR_ENTRY 0x666006
#define DRPC_READ_PROCESS_MEMORY       0x666007
#define DRPC_SET_THREAD_CONTEXT        0x666008
#define DRPC_CREATE_PROCESS            0x666009
#define DRPC_CLOSE_HANDLE              0x66600A
#define DRPC_OPEN_PROCESS              0x66600B

BOOL (WINAPI *oldWaitForDebugEvent)(LPDEBUG_EVENT lpDebugEvent, DWORD dwMilliseconds);

BOOL (WINAPI *oldWriteProcessMemory)(
  HANDLE hProcess,                // handle to process
  LPVOID lpBaseAddress,           // base of memory area
  LPVOID lpBuffer,                // data buffer
  DWORD nSize,                    // number of bytes to write
  LPDWORD lpNumberOfBytesWritten); // number of bytes written

BOOL (WINAPI *oldContinueDebugEvent)(
  DWORD dwProcessId,       // process to continue
  DWORD dwThreadId,        // thread to continue
  DWORD dwContinueStatus);  // continuation status

BOOL (WINAPI *oldGetThreadContext)(
  HANDLE hThread,       // handle to thread with context
  LPCONTEXT lpContext); // context structure

BOOL (WINAPI *oldGetThreadSelectorEntry)(
  HANDLE hThread,              // handle to thread
  DWORD dwSelector,            // number of selector value
  LPLDT_ENTRY lpSelectorEntry);// descriptor table entry

BOOL (WINAPI *oldReadProcessMemory)(
  HANDLE hProcess,             // handle to the process
  LPCVOID lpBaseAddress,       // base of memory area
  LPVOID lpBuffer,             // data buffer
  DWORD nSize,                 // number of bytes to read
  LPDWORD lpNumberOfBytesRead);// number of bytes read

BOOL (WINAPI * oldSetThreadContext)(
  HANDLE hThread,            // handle to thread
  CONST CONTEXT *lpContext); // context structure

BOOL (WINAPI* oldDebugActiveProcess)(DWORD dwProcessId);

BOOL (WINAPI* oldCloseHandle)(HANDLE hObject);

BOOL WINAPI myDebugActiveProcess(DWORD dwProcessId)
{
	if (debugEventSocket)
	{
		SOCKET s = debugEventSocket;
		TESTPROTOIN(0x12345678);
		TESTPROTOOUT(0x12345678);
		DWORD dwCode = DRPC_DEBUG_ACTIVE_PROCESS;
		S(dwCode);
		S(dwProcessId);
		DWORD dwRet = 0;
		R(dwRet);
		TESTPROTOIN(0xFEDCBA98);
		TESTPROTOOUT(0xFEDCBA98);
		return dwRet;
	}
	fprintf(log, "WaitForDebugEvent(%08X)\n", oldWaitForDebugEvent);
	fflush(log);
	return (*oldDebugActiveProcess)(dwProcessId);
}

BOOL WINAPI myWaitForDebugEvent(LPDEBUG_EVENT lpDebugEvent,
  DWORD dwMilliseconds)
{
	if (debugEventSocket)
	{
		SOCKET s = debugEventSocket;
		TESTPROTOIN(0x12345678);
		TESTPROTOOUT(0x12345678);
		DWORD dwCode = DRPC_WAIT_FOR_DEBUG_EVENT;
		S(dwCode);
		S(dwMilliseconds);
		DWORD dwRet = 0;
		R(dwRet);
		if (dwRet)
			R(*lpDebugEvent);
		TESTPROTOIN(0xFEDCBA98);
		TESTPROTOOUT(0xFEDCBA98);
		return dwRet;
	}
	fprintf(log, "WaitForDebugEvent(%08X)\n", oldWaitForDebugEvent);
	fflush(log);
	return (*oldWaitForDebugEvent)(lpDebugEvent, dwMilliseconds);
}


BOOL WINAPI myWriteProcessMemory(
  HANDLE hProcess,                // handle to process
  LPVOID lpBaseAddress,           // base of memory area
  LPVOID lpBuffer,                // data buffer
  DWORD nSize,                    // number of bytes to write
  LPDWORD lpNumberOfBytesWritten) // number of bytes written
{
	if (debugEventSocket)
	{
		SOCKET s = debugEventSocket;
		TESTPROTOIN(0x12345678);
		TESTPROTOOUT(0x12345678);
		DWORD dwCode = DRPC_WRITE_PROCESS_MEMORY;
		S(dwCode);
		S(hProcess);
		S(lpBaseAddress);
		S(nSize);
		Send(s, lpBuffer, nSize);
		
		DWORD written = 0;		
		R(written);
		if (lpNumberOfBytesWritten != 0)
			*lpNumberOfBytesWritten = written;

		DWORD dwRet = 0;
		R(dwRet);
		TESTPROTOIN(0xFEDCBA98);
		TESTPROTOOUT(0xFEDCBA98);
		return dwRet;
	}
	fprintf(log, "WriteProcessMemory()\n");
	fflush(log);
	return oldWriteProcessMemory(hProcess, lpBaseAddress, lpBuffer, nSize, lpNumberOfBytesWritten);
}



BOOL WINAPI myContinueDebugEvent(
  DWORD dwProcessId,       // process to continue
  DWORD dwThreadId,        // thread to continue
  DWORD dwContinueStatus)  // continuation status
{
	if (debugEventSocket)
	{
		SOCKET s = debugEventSocket;
		TESTPROTOIN(0x12345678);
		TESTPROTOOUT(0x12345678);
		DWORD dwCode = DRPC_CONTINUE_DEBUG_EVENT;
		S(dwCode);
		S(dwProcessId);
		S(dwThreadId);
		S(dwContinueStatus);
		DWORD dwRet = 0;
		R(dwRet);
		TESTPROTOIN(0xFEDCBA98);
		TESTPROTOOUT(0xFEDCBA98);
		return dwRet;
	}
	fprintf(log, "ContinueDebugEvent()\n");
	fflush(log);
	return oldContinueDebugEvent(dwProcessId, dwThreadId, dwContinueStatus);
}
/*
BOOL myFlushInstructionCache(
  HANDLE hProcess,        // handle to process 
  LPCVOID lpBaseAddress,  // base of region to flush
  DWORD dwSize            // length of region to flush
);
*/


BOOL WINAPI myGetThreadContext(
  HANDLE hThread,       // handle to thread with context
  LPCONTEXT lpContext)  // context structure
{
	if (debugEventSocket)
	{
		SOCKET s = debugEventSocket;
		TESTPROTOIN(0x12345678);
		TESTPROTOOUT(0x12345678);
		DWORD dwCode = DRPC_GET_THREAD_CONTEXT;
		S(dwCode);
		S(hThread);
		DWORD dwRet = 0;
		R(dwRet);
		if (dwRet)
			R(*lpContext);
		TESTPROTOIN(0xFEDCBA98);
		TESTPROTOOUT(0xFEDCBA98);
		return dwRet;
	}
	fprintf(log, "GetThreadContext()\n");
	fflush(log);
	return oldGetThreadContext(hThread, lpContext);
}

BOOL WINAPI myGetThreadSelectorEntry(
  HANDLE hThread,              // handle to thread
  DWORD dwSelector,            // number of selector value
  LPLDT_ENTRY lpSelectorEntry) // descriptor table entry
{
	if (debugEventSocket)
	{
		SOCKET s = debugEventSocket;
		TESTPROTOIN(0x12345678);
		TESTPROTOOUT(0x12345678);
		DWORD dwCode = DRPC_GET_THREAD_SELECTOR_ENTRY;
		S(dwCode);
		S(hThread);
		S(dwSelector);
		R(*lpSelectorEntry);
		DWORD dwRet = 0;
		R(dwRet);
		TESTPROTOIN(0xFEDCBA98);
		TESTPROTOOUT(0xFEDCBA98);
		return dwRet;
	}
	fprintf(log, "GetThreadSelectorEntry()\n");
	fflush(log);
	return oldGetThreadSelectorEntry(hThread, dwSelector, lpSelectorEntry);
}

BOOL WINAPI myReadProcessMemory(
  HANDLE hProcess,             // handle to the process
  LPCVOID lpBaseAddress,       // base of memory area
  LPVOID lpBuffer,             // data buffer
  DWORD nSize,                 // number of bytes to read
  LPDWORD lpNumberOfBytesRead) // number of bytes read
{
	if (debugEventSocket)
	{
		SOCKET s = debugEventSocket;
		TESTPROTOIN(0x12345678);
		TESTPROTOOUT(0x12345678);
		DWORD dwCode = DRPC_READ_PROCESS_MEMORY;
		S(dwCode);
		S(hProcess);
		S(lpBaseAddress);
		S(nSize);
		DWORD dwRet = 0;
		R(dwRet);
		DWORD read;
		R(read);
		if(lpNumberOfBytesRead)
			*lpNumberOfBytesRead = read;
		if (dwRet)
		{
			Recv(s, lpBuffer, nSize);
		}
		TESTPROTOIN(0xFEDCBA98);
		TESTPROTOOUT(0xFEDCBA98);
		return dwRet;
	}
	fprintf(log, "ReadProcessMemory()\n");
	fflush(log);
	return oldReadProcessMemory(hProcess, lpBaseAddress, lpBuffer, nSize, lpNumberOfBytesRead);
}

BOOL WINAPI mySetThreadContext(
  HANDLE hThread,            // handle to thread
  CONST CONTEXT *lpContext)  // context structure
{
	if (debugEventSocket)
	{
		SOCKET s = debugEventSocket;
		TESTPROTOIN(0x12345678);
		TESTPROTOOUT(0x12345678);
		DWORD dwCode = DRPC_SET_THREAD_CONTEXT;
		S(dwCode);
		S(hThread);
		S(*lpContext);

		DWORD dwRet = 0;
		R(dwRet);
		TESTPROTOIN(0xFEDCBA98);
		TESTPROTOOUT(0xFEDCBA98);
		return dwRet;
	}
	fprintf(log, "SetThreadContext()\n");
	fflush(log);
	return oldSetThreadContext(hThread, lpContext);
}


BOOL (WINAPI* oldCreateProcessA)(
    LPCSTR lpApplicationName,
    LPSTR lpCommandLine,
    LPSECURITY_ATTRIBUTES lpProcessAttributes,
    LPSECURITY_ATTRIBUTES lpThreadAttributes,
    BOOL bInheritHandles,
    DWORD dwCreationFlags,
    LPVOID lpEnvironment,
    LPCSTR lpCurrentDirectory,
    LPSTARTUPINFOA lpStartupInfo,
    LPPROCESS_INFORMATION lpProcessInformation);

BOOL
WINAPI
myCreateProcessA(
    LPCSTR lpApplicationName,
    LPSTR lpCommandLine,
    LPSECURITY_ATTRIBUTES lpProcessAttributes,
    LPSECURITY_ATTRIBUTES lpThreadAttributes,
    BOOL bInheritHandles,
    DWORD dwCreationFlags,
    LPVOID lpEnvironment,
    LPCSTR lpCurrentDirectory,
    LPSTARTUPINFOA lpStartupInfo,
    LPPROCESS_INFORMATION lpProcessInformation)
{
	if (debugEventSocket)
	{
		_asm int 3;
		SOCKET s = debugEventSocket;
		TESTPROTOIN(0x12345678);
		TESTPROTOOUT(0x12345678);
		DWORD dwCode = DRPC_CREATE_PROCESS;
		S(dwCode);
		Szs(lpApplicationName);
		Szs(lpCommandLine);
//    Sq(lpProcessAttributes);
//    Sq(lpThreadAttributes);
		S(bInheritHandles);
		S(dwCreationFlags);
//TODO    Senv(lpEnvironment);
		Szs(lpCurrentDirectory);
		S(*lpStartupInfo);
	
		DWORD dwHandled;
		R(dwHandled);
		if (dwHandled)
		{
			DWORD dwRet = 0;
			R(dwRet); 

			PROCESS_INFORMATION info;
			R(info);
			if (lpProcessInformation)
				*lpProcessInformation = info;

			TESTPROTOIN(0xFEDCBA98);
			TESTPROTOOUT(0xFEDCBA98);
			return dwRet;
		}
		TESTPROTOIN(0xFEDCBA98);
		TESTPROTOOUT(0xFEDCBA98);
	}
	fprintf(log, "CreateProcess(%s, %s)\n", lpApplicationName, lpCommandLine);
	fflush(log);
	return oldCreateProcessA(lpApplicationName,
		lpCommandLine,
		lpProcessAttributes,
		lpThreadAttributes,
		bInheritHandles,
		dwCreationFlags,
		lpEnvironment,
		lpCurrentDirectory,
		lpStartupInfo,
		lpProcessInformation);
}

BOOL WINAPI myCloseHandle(HANDLE hObject)
{
	if (debugEventSocket)
	{
		SOCKET s = debugEventSocket;
		TESTPROTOIN(0x12345678);
		TESTPROTOOUT(0x12345678);
		DWORD dwCode = DRPC_CLOSE_HANDLE;
		S(dwCode);
		S(hObject);		

		DWORD dwRet = 0, dwHandled = 0;
		R(dwHandled);
		R(dwRet);
		TESTPROTOIN(0xFEDCBA98);
		TESTPROTOOUT(0xFEDCBA98);
		if (dwHandled)
			return dwRet;
	}
	fprintf(log, "SetThreadContext()\n");
	fflush(log);
	return oldCloseHandle(hObject);
}

HANDLE (WINAPI *oldOpenProcess)(DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwProcessId);

HANDLE WINAPI myOpenProcess(DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwProcessId)
{
	if (debugEventSocket)
	{
		SOCKET s = debugEventSocket;
		TESTPROTOIN(0x12345678);
		TESTPROTOOUT(0x12345678);
		DWORD dwCode = DRPC_OPEN_PROCESS;
		S(dwCode);
		S(dwDesiredAccess);
		S(bInheritHandle);
		S(dwProcessId);

		DWORD dwHandled = 0;
		R(dwHandled);
		HANDLE hRet;
		R(hRet);
		TESTPROTOIN(0xFEDCBA98);
		TESTPROTOOUT(0xFEDCBA98);
		if (dwHandled)
			return hRet;
	}
	fprintf(log, "OpenProcess()\n");
	fflush(log);
	return oldOpenProcess(dwDesiredAccess, bInheritHandle, dwProcessId);
}

/*
TerminateProcess
SuspendThread 
ResumeThread
*/

PATCH debug_patches[] =
{
	{"kernel32.dll", "WaitForDebugEvent",		(LPVOID)myWaitForDebugEvent, (LPVOID*)&oldWaitForDebugEvent},
	{"kernel32.dll", "WriteProcessMemory",	(LPVOID)myWriteProcessMemory,(LPVOID*)&oldWriteProcessMemory},
	{"kernel32.dll", "ContinueDebugEvent",	(LPVOID)myContinueDebugEvent, (LPVOID*)&oldContinueDebugEvent},
	{"kernel32.dll", "GetThreadContext",		(LPVOID)myGetThreadContext, (LPVOID*)&oldGetThreadContext},
	{"kernel32.dll", "GetThreadSelectorEntry",(LPVOID)myGetThreadSelectorEntry, (LPVOID*)&oldGetThreadSelectorEntry},
	{"kernel32.dll", "ReadProcessMemory",		(LPVOID)myReadProcessMemory, (LPVOID*)&oldReadProcessMemory},
	{"kernel32.dll", "SetThreadContext",		(LPVOID)mySetThreadContext, (LPVOID*)&oldSetThreadContext},
	{"kernel32.dll", "CreateProcessA",			(LPVOID)myCreateProcessA, (LPVOID *)&oldCreateProcessA},
	{"kernel32.dll", "DebugActiveProcess",	(LPVOID)myDebugActiveProcess, (LPVOID *)&oldDebugActiveProcess},
	{"kernel32.dll", "CloseHandle",					(LPVOID)myCloseHandle,  (LPVOID *)&oldCloseHandle},
	{"kernel32.dll", "OpenProcess",					(LPVOID)myOpenProcess,  (LPVOID *)&oldOpenProcess},
};

int debug_patches_sz = sizeof(debug_patches) / sizeof(debug_patches[0]);
