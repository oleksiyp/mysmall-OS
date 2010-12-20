// server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

class SocketException {};
class ReadSocketException : public SocketException {};
class WriteSocketException : public SocketException {};

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

#define S(data) Send(s, &data, sizeof(data))
#define R(data) Recv(s, &data, sizeof(data))
DWORD RConst(SOCKET s)
{
	DWORD dw;
	R(dw);
	return dw;
}

void SConst(SOCKET s, DWORD dw)
{
	S(dw);
}

char *RecvZString(SOCKET s, char *buf)
{
	if (!RConst(s))
		return 0;
	DWORD len = RConst(s);
	Recv(s, buf, len);
	buf[len] = 0;
	return buf;
}

template <class structType>
structType *RQ(SOCKET s, structType *pdata)
{
	if (RConst(s))
	{
		R(*pdata);
		return pdata;
	} else
		return 0;
}

#define Rq(pdata) RQ(s, pdata);
#define Rzs(str) RecvZString(s, str);


SOCKET serverSocket(int port)
{
	SOCKET s;
	s = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN sa;
	sa.sin_family = AF_INET;
	sa.sin_port = htons(port);
	sa.sin_addr.S_un.S_addr = INADDR_ANY;

	int r;
	r = bind(s, (sockaddr *)&sa, sizeof(sa));
	r = listen(s, 0);
	return s;
}

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

map<HANDLE, int> ownedHandle;

#define printstruct(s, fmt, d) printf("\t" #d " = " fmt "\n", s.d);

void registerHandle(HANDLE h)
{
	if (ownedHandle.find(h) == ownedHandle.end())
	{
		ownedHandle[h] = 1;
	} else {
		ownedHandle[h]++;
	}
}

void unregisterHandle(HANDLE h)
{
	if (ownedHandle.find(h) != ownedHandle.end())
	{
		ownedHandle[h]--;
		if (ownedHandle[h] == 0)
			ownedHandle.erase(h);
	}
}

bool isRegistered(HANDLE h)
{
	return ownedHandle.find(h) != ownedHandle.end();
}

#define MANGLE(xxx) xxx = (void *)((char *)(xxx) + 100);
#define DEMANGLE(xxx) xxx = (void *)((char *)(xxx) - 100);

BOOL DispatchWaitForDebugEvent(LPDEBUG_EVENT lpDebugEvent, DWORD dwMilliseconds)
{
	printf("WaitForDebugEvent(\n");
	DWORD dwRet = WaitForDebugEvent(lpDebugEvent, dwMilliseconds);
	if (dwRet)
	{
		printf("\tprocid = 0x%08X, threadid = 0x%08X\n", lpDebugEvent->dwProcessId,
			lpDebugEvent->dwThreadId);
		lpDebugEvent->dwProcessId += 100;
		lpDebugEvent->dwThreadId += 100;

		switch(lpDebugEvent->dwDebugEventCode)
		{
		case (CREATE_THREAD_DEBUG_EVENT):
			printf("\teventcode = CREATE_THREAD_DEBUG_EVENT\n");
			registerHandle(lpDebugEvent->u.CreateThread.hThread);
			
			printstruct(lpDebugEvent->u.CreateThread,"0x%08X",hThread);

			MANGLE(lpDebugEvent->u.CreateThread.hThread);
			break;
		case (CREATE_PROCESS_DEBUG_EVENT):
			printf("\teventcode = CREATE_PROCESS_DEBUG_EVENT\n");
			registerHandle(lpDebugEvent->u.CreateProcessInfo.hThread);
			registerHandle(lpDebugEvent->u.CreateProcessInfo.hProcess);
			
			printstruct(lpDebugEvent->u.CreateProcessInfo,"0x%08X",hThread);
			printstruct(lpDebugEvent->u.CreateProcessInfo,"0x%08X",hProcess);
			
			MANGLE(lpDebugEvent->u.CreateProcessInfo.hProcess);
			MANGLE(lpDebugEvent->u.CreateProcessInfo.hThread);
			break;
		default:
			printf("\teventcode  = other\n");
			break;
		}
	}
	printf(");\n");
	return dwRet;
}

BOOL DispatchWriteProcessMemory(
  HANDLE hProcess,                // handle to process
  LPVOID lpBaseAddress,           // base of memory area
  LPVOID lpBuffer,                // data buffer
  DWORD nSize,                    // number of bytes to write
  LPDWORD lpNumberOfBytesWritten)
{
	DEMANGLE(hProcess);
	printf("WriteProcMem(0x%08X, base = 0x%08X, sz = %d)\n", hProcess, lpBaseAddress, nSize);
	return WriteProcessMemory(hProcess, lpBaseAddress, 
		lpBuffer, nSize, lpNumberOfBytesWritten);
}


BOOL DisptachDebugActiveProcess(DWORD dwProcessId)
{
	dwProcessId -= 100;

	printf("DebugActiveProcess(procid = 0x%08X)\n", 
		dwProcessId);
	return DebugActiveProcess(dwProcessId);
}

BOOL DispatchContinueDebugEvent(
  DWORD dwProcessId,
  DWORD dwThreadId,
  DWORD dwContinueStatus)
{
	dwProcessId -= 100;
	dwThreadId -= 100;

	printf("ContinueDebugEvent(procid = 0x%08X, threadid = 0x%08X, status = 0x%08X)\n", 
		dwProcessId, dwThreadId, dwContinueStatus);
	return ContinueDebugEvent(dwProcessId,
		dwThreadId, dwContinueStatus);
}

BOOL DispatchGetThreadContext(
  HANDLE hThread,       // handle to thread with context
  LPCONTEXT lpContext)  // context structure
{
	DEMANGLE(hThread);
	printf("GetThreadContext(0x%08X)\n", hThread);
	return GetThreadContext(hThread, lpContext);
}

BOOL DispatchGetThreadSelectorEntry(
  HANDLE hThread,              // handle to thread
  DWORD dwSelector,            // number of selector value
  LPLDT_ENTRY lpSelectorEntry) // descriptor table entry
{
	hThread = (void *)((char *)hThread - 100);
	printf("GetThreadSelectorEntry(0x%08X, sel = 0x%08X)\n", hThread, dwSelector);
	return GetThreadSelectorEntry(hThread, dwSelector, lpSelectorEntry);
}


BOOL DispatchReadProcessMemory(
  HANDLE hProcess,             // handle to the process
  LPCVOID lpBaseAddress,       // base of memory area
  LPVOID lpBuffer,             // data buffer
  DWORD nSize,                 // number of bytes to read
  LPDWORD lpNumberOfBytesRead) // number of bytes read
{
	hProcess = (void *)((char *)hProcess - 100);
	printf("ReadProcMem(0x%08X, base = 0x%08X, sz = %d)\n", hProcess, lpBaseAddress, nSize);
	return 	ReadProcessMemory(hProcess, lpBaseAddress, 
		lpBuffer, nSize, lpNumberOfBytesRead);
}

BOOL DispatchSetThreadContext(
  HANDLE hThread,            // handle to thread
  CONST CONTEXT *lpContext)  // context structure
{
	DEMANGLE(hThread);
	printf("SetThreadContext(0x%08X)\n", hThread);
	return SetThreadContext(hThread, lpContext);
}


BOOL
WINAPI
DispatchCreateProcessA(
    LPCSTR lpApplicationName,
    LPSTR lpCommandLine,
    LPSECURITY_ATTRIBUTES lpProcessAttributes,
    LPSECURITY_ATTRIBUTES lpThreadAttributes,
    BOOL bInheritHandles,
    DWORD dwCreationFlags,
    LPVOID lpEnvironment,
    LPCSTR lpCurrentDirectory,
    LPSTARTUPINFOA lpStartupInfo,
    LPPROCESS_INFORMATION lpProcessInformation,
		DWORD *lpdwHandled)
{
	*lpdwHandled = 1;
	printf("CreateProcess('%s', '%s')\n", lpApplicationName, lpCommandLine);

	BOOL ret = CreateProcess(lpApplicationName,
		lpCommandLine,
		lpProcessAttributes,
		lpThreadAttributes,
		bInheritHandles,
		dwCreationFlags,
		lpEnvironment,
		lpCurrentDirectory,
		lpStartupInfo,
		lpProcessInformation);

	registerHandle(lpProcessInformation->hProcess);
	registerHandle(lpProcessInformation->hThread);

	printf("hProc = 0x%08X\n", lpProcessInformation->hProcess);
	printf("hThread = 0x%08X\n", lpProcessInformation->hThread);
	printf("idProc = 0x%08X\n", lpProcessInformation->dwProcessId);
	printf("idThread = 0x%08X\n", lpProcessInformation->dwThreadId);

	lpProcessInformation->dwProcessId += 100;
	lpProcessInformation->dwThreadId += 100;
	lpProcessInformation->hProcess = (void*)((char*)lpProcessInformation->hProcess + 100);
	lpProcessInformation->hThread = (void*)((char*)lpProcessInformation->hThread + 100);

	return ret;
}

BOOL DispatchCloseHandle(HANDLE hObject, DWORD *dwHandled)
{
	hObject = (void*)((char*)hObject - 100);
	if (isRegistered(hObject))
	{
		printf("CloseHandle(%08X)\n", hObject);
		unregisterHandle(hObject);
		*dwHandled = TRUE;
		return CloseHandle(hObject);		
	}
	printf("***CloseHandle(%08X)\n", hObject);
	*dwHandled = FALSE;
	return FALSE;
}

HANDLE DispatchOpenProcess(DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwProcessId, DWORD *dwHandled)
{
	dwProcessId -= 100;
	HANDLE h = OpenProcess(dwDesiredAccess, bInheritHandle, dwProcessId);
	printf("OpenProcess(%08X)=%08X\n", dwProcessId, h);
	*dwHandled = (h != 0);
	return h;
}

#define TESTPROTOIN(param) if (RConst(s) != param) printf("prtotcol failure\n")
#define TESTPROTOOUT(param) SConst(s, param)

void ProcessRemoteEvents(SOCKET s)
{
	while (1)
	{
		TESTPROTOOUT(0x12345678);
		TESTPROTOIN(0x12345678);
		DWORD dwCode = RConst(s);
		DWORD dwRet;
		switch(dwCode)
		{
			case (DRPC_WAIT_FOR_DEBUG_EVENT):
			{
				DEBUG_EVENT event;
				DWORD dwMilliseconds;
				R(dwMilliseconds);
				dwRet = DispatchWaitForDebugEvent(&event, dwMilliseconds);
				S(dwRet);
				if (dwRet)
					S(event);
				break;
			}
			case (DRPC_WRITE_PROCESS_MEMORY):
			{
				HANDLE hProcess;
				LPVOID lpBaseAddress;
				DWORD nSize;
				R(hProcess);
				R(lpBaseAddress);
				R(nSize);
				BYTE *buf = new BYTE[nSize];
				Recv(s, buf, nSize);
				DWORD written;
				dwRet = DispatchWriteProcessMemory(hProcess, lpBaseAddress, buf, nSize, &written);
				delete buf;
				S(written);
				S(dwRet);
				break;
			}
			case (DRPC_DEBUG_ACTIVE_PROCESS):
			{
				DWORD dwProcessId;
				R(dwProcessId);
				dwRet = DisptachDebugActiveProcess(dwProcessId);
				S(dwRet);
				break;
			}
			case (DRPC_CONTINUE_DEBUG_EVENT):
			{
				DWORD dwProcessId;
				DWORD dwThreadId;
				DWORD dwContinueStatus;
				R(dwProcessId);
				R(dwThreadId);
				R(dwContinueStatus);
				dwRet = DispatchContinueDebugEvent(dwProcessId, dwThreadId, dwContinueStatus);
				S(dwRet);
				break;
			}
			case (DRPC_GET_THREAD_CONTEXT):
			{
				HANDLE hThread;
				R(hThread);
				CONTEXT context;
				dwRet = DispatchGetThreadContext(hThread, &context);
				S(dwRet);
				if (dwRet)
					S(context);
				break;
			}
			case (DRPC_GET_THREAD_SELECTOR_ENTRY):
			{
				HANDLE hThread;
				DWORD dwSelector;
				LDT_ENTRY ldt;
				R(hThread);
				R(dwSelector);
				dwRet = DispatchGetThreadSelectorEntry(hThread, dwSelector, &ldt);
				S(ldt);
				S(dwRet);
				break;
			}
			case (DRPC_READ_PROCESS_MEMORY):
			{
				HANDLE hProcess;
				LPVOID lpBaseAddress;
				DWORD nSize;
				R(hProcess);
				R(lpBaseAddress);
				R(nSize);
				BYTE *buf = new BYTE[nSize];
				DWORD read;
				dwRet = DispatchReadProcessMemory(hProcess, lpBaseAddress, buf, nSize, &read);
				S(dwRet);
				S(read);
				if (dwRet)
					Send(s, buf, nSize);
				break;
			}
			case (DRPC_SET_THREAD_CONTEXT):
			{
				HANDLE hThread;
				CONTEXT context;
				R(hThread);
				R(context);
				dwRet = DispatchSetThreadContext(hThread, &context);
				S(dwRet);
				break;
			}
			case (DRPC_CREATE_PROCESS):
			{
				char appName[512], cmdLine[512], curDir[512];
				SECURITY_ATTRIBUTES procAttr, threadAttr;
				BOOL bInheritHandles;
				DWORD dwCreationFlags;

				char *lpApplicationName = Rzs(appName);
				char *lpCommandLine = Rzs(cmdLine);
				SECURITY_ATTRIBUTES *lpProcessAttributes = 0;//Rq(&procAttr);
				SECURITY_ATTRIBUTES *lpThreadAttributes = 0;//Rq(&threadAttr);
				R(bInheritHandles);
				R(dwCreationFlags);
//TODO    Renv(lpEnvironment);
		    char *lpCurrentDirectory = Rzs(curDir);
				STARTUPINFO sinfo;
		    R(sinfo);
				PROCESS_INFORMATION pinfo;
				DWORD dwHandled;
				dwRet = DispatchCreateProcessA(
					lpApplicationName,
					lpCommandLine,
					lpProcessAttributes,
					lpThreadAttributes,
					bInheritHandles,
					dwCreationFlags,
					0,
					lpCurrentDirectory,
					&sinfo,
					&pinfo,
					&dwHandled);
				S(dwHandled);
				if (dwHandled)
				{
					S(dwRet);
					S(pinfo);
				}
				break;
			}
			case (DRPC_CLOSE_HANDLE):
			{
				HANDLE hObject;
				DWORD dwHandled;
				R(hObject);
				dwRet = DispatchCloseHandle(hObject, &dwHandled);
			S(dwHandled);
				S(dwRet);
				break;
			}
			case (DRPC_OPEN_PROCESS):
			{
				DWORD dwDesiredAccess, dwProcessId;
				BOOL bInheritHandle;
				R(dwDesiredAccess);
				R(bInheritHandle);
				R(dwProcessId);
				DWORD dwHandled;
				HANDLE hRet = DispatchOpenProcess(dwDesiredAccess, bInheritHandle, dwProcessId, &dwHandled);
				S(dwHandled);
				S(hRet);
				break;
			}
			default:
				printf("wrong syscall\n");
		}
		TESTPROTOOUT(0xFEDCBA98);
		TESTPROTOIN(0xFEDCBA98);
	}
}

int main(int argc, char* argv[])
{
	WORD wVersionRequested = MAKEWORD(1, 1);
	WSADATA wsaData;
	WSAStartup( wVersionRequested, &wsaData );

	SOCKET server = serverSocket(1523), s;
	struct sockaddr_in addr;
	int len = sizeof(addr);
	while (s = accept(server, (sockaddr *)&addr, &len))
	{
		printf("connected\n");
		try
		{
			ProcessRemoteEvents(s);
		} catch (SocketException)
		{
			printf("disconnected\n");
		}
	}
	return 0;
}
