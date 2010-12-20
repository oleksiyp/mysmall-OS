/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Jan 20 17:09:59 2005
 */
/* Compiler settings for RemoteDebuggerServer.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RemoteDebuggerServer_h__
#define __RemoteDebuggerServer_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __RemoteDebuggerServer_INTERFACE_DEFINED__
#define __RemoteDebuggerServer_INTERFACE_DEFINED__

/* interface RemoteDebuggerServer */
/* [auto_handle][version][uuid] */ 

typedef unsigned long DWORD;

typedef unsigned long __RPC_FAR *LPDWORD;

typedef int BOOL;

typedef int __RPC_FAR *LPBOOL;

typedef unsigned char BYTE;

typedef unsigned char __RPC_FAR *LPBYTE;

typedef unsigned short WORD;

typedef unsigned short __RPC_FAR *UINT_PTR;

typedef DWORD LPVOID;

typedef DWORD HANDLE;

typedef /* [string] */ unsigned char __RPC_FAR *LPSTR;

typedef /* [string] */ const unsigned char __RPC_FAR *LPCSTR;

typedef struct  _SECURITY_ATTRIBUTES
    {
    DWORD nLength;
    LPVOID lpSecurityDescriptor;
    BOOL bInheritHandle;
    }	SECURITY_ATTRIBUTES;

typedef struct _SECURITY_ATTRIBUTES __RPC_FAR *PSECURITY_ATTRIBUTES;

typedef struct _SECURITY_ATTRIBUTES __RPC_FAR *LPSECURITY_ATTRIBUTES;

typedef struct  _STARTUPINFOA
    {
    DWORD cb;
    LPSTR lpReserved;
    LPSTR lpDesktop;
    LPSTR lpTitle;
    DWORD dwX;
    DWORD dwY;
    DWORD dwXSize;
    DWORD dwYSize;
    DWORD dwXCountChars;
    DWORD dwYCountChars;
    DWORD dwFillAttribute;
    DWORD dwFlags;
    WORD wShowWindow;
    WORD cbReserved2;
    LPBYTE lpReserved2;
    HANDLE hStdInput;
    HANDLE hStdOutput;
    HANDLE hStdError;
    }	STARTUPINFOA;

typedef struct _STARTUPINFOA __RPC_FAR *LPSTARTUPINFOA;

typedef struct  _PROCESS_INFORMATION
    {
    HANDLE hProcess;
    HANDLE hThread;
    DWORD dwProcessId;
    DWORD dwThreadId;
    }	PROCESS_INFORMATION;

typedef struct _PROCESS_INFORMATION __RPC_FAR *PPROCESS_INFORMATION;

typedef struct _PROCESS_INFORMATION __RPC_FAR *LPPROCESS_INFORMATION;

typedef struct  _FLOATING_SAVE_AREA
    {
    DWORD ControlWord;
    DWORD StatusWord;
    DWORD TagWord;
    DWORD ErrorOffset;
    DWORD ErrorSelector;
    DWORD DataOffset;
    DWORD DataSelector;
    BYTE RegisterArea[ 80 ];
    DWORD Cr0NpxState;
    }	FLOATING_SAVE_AREA;

typedef struct  _CONTEXT
    {
    DWORD ContextFlags;
    DWORD Dr0;
    DWORD Dr1;
    DWORD Dr2;
    DWORD Dr3;
    DWORD Dr6;
    DWORD Dr7;
    FLOATING_SAVE_AREA FloatSave;
    DWORD SegGs;
    DWORD SegFs;
    DWORD SegEs;
    DWORD SegDs;
    DWORD Edi;
    DWORD Esi;
    DWORD Ebx;
    DWORD Edx;
    DWORD Ecx;
    DWORD Eax;
    DWORD Ebp;
    DWORD Eip;
    DWORD SegCs;
    DWORD EFlags;
    DWORD Esp;
    DWORD SegSs;
    BYTE ExtendedRegisters[ 512 ];
    }	CONTEXT;

typedef struct _CONTEXT __RPC_FAR *LPCONTEXT;

typedef struct  _LDT_ENTRY
    {
    WORD LimitLow;
    WORD BaseLow;
    DWORD Flags;
    }	LDT_ENTRY;

typedef struct _LDT_ENTRY __RPC_FAR *LPLDT_ENTRY;

typedef struct  _EXCEPTION_RECORD
    {
    DWORD ExceptionCode;
    DWORD ExceptionFlags;
    /* [full] */ struct _EXCEPTION_RECORD __RPC_FAR *ExceptionRecord;
    LPVOID ExceptionAddress;
    DWORD NumberParameters;
    UINT_PTR ExceptionInformation[ 15 ];
    }	EXCEPTION_RECORD;

typedef struct  _EXCEPTION_DEBUG_INFO
    {
    EXCEPTION_RECORD ExceptionRecord;
    DWORD dwFirstChance;
    }	EXCEPTION_DEBUG_INFO;

typedef LPVOID LPTHREAD_START_ROUTINE;

typedef struct  _CREATE_THREAD_DEBUG_INFO
    {
    HANDLE hThread;
    LPVOID lpThreadLocalBase;
    LPTHREAD_START_ROUTINE lpStartAddress;
    }	CREATE_THREAD_DEBUG_INFO;

typedef struct  _CREATE_PROCESS_DEBUG_INFO
    {
    HANDLE hFile;
    HANDLE hProcess;
    HANDLE hThread;
    LPVOID lpBaseOfImage;
    DWORD dwDebugInfoFileOffset;
    DWORD nDebugInfoSize;
    LPVOID lpThreadLocalBase;
    LPTHREAD_START_ROUTINE lpStartAddress;
    LPVOID lpImageName;
    WORD fUnicode;
    }	CREATE_PROCESS_DEBUG_INFO;

typedef struct  _EXIT_THREAD_DEBUG_INFO
    {
    DWORD dwExitCode;
    }	EXIT_THREAD_DEBUG_INFO;

typedef struct  _EXIT_PROCESS_DEBUG_INFO
    {
    DWORD dwExitCode;
    }	EXIT_PROCESS_DEBUG_INFO;

typedef struct  _LOAD_DLL_DEBUG_INFO
    {
    HANDLE hFile;
    LPVOID lpBaseOfDll;
    DWORD dwDebugInfoFileOffset;
    DWORD nDebugInfoSize;
    LPVOID lpImageName;
    WORD fUnicode;
    }	LOAD_DLL_DEBUG_INFO;

typedef struct  _UNLOAD_DLL_DEBUG_INFO
    {
    LPVOID lpBaseOfDll;
    }	UNLOAD_DLL_DEBUG_INFO;

typedef struct  _OUTPUT_DEBUG_STRING_INFO
    {
    LPSTR lpDebugStringData;
    WORD fUnicode;
    WORD nDebugStringLength;
    }	OUTPUT_DEBUG_STRING_INFO;

typedef struct  _RIP_INFO
    {
    DWORD dwError;
    DWORD dwType;
    }	RIP_INFO;

typedef struct  _DEBUG_EVENT
    {
    DWORD dwDebugEventCode;
    DWORD dwProcessId;
    DWORD dwThreadId;
    /* [switch_is] */ /* [switch_type] */ union 
        {
        /* [case()] */ EXCEPTION_DEBUG_INFO Exception;
        /* [case()] */ CREATE_THREAD_DEBUG_INFO CreateThread;
        /* [case()] */ CREATE_PROCESS_DEBUG_INFO CreateProcessInfo;
        /* [case()] */ EXIT_THREAD_DEBUG_INFO ExitThread;
        /* [case()] */ EXIT_PROCESS_DEBUG_INFO ExitProcess;
        /* [case()] */ LOAD_DLL_DEBUG_INFO LoadDll;
        /* [case()] */ UNLOAD_DLL_DEBUG_INFO UnloadDll;
        /* [case()] */ OUTPUT_DEBUG_STRING_INFO DebugString;
        /* [case()] */ RIP_INFO RipInfo;
        }	u;
    }	DEBUG_EVENT;

typedef struct _DEBUG_EVENT __RPC_FAR *LPDEBUG_EVENT;

BOOL rpcWaitForDebugEvent( 
    /* [full] */ LPDEBUG_EVENT lpDebugEvent,
    DWORD dwMilliseconds);

BOOL rpcWriteProcessMemory( 
    HANDLE hProcess,
    LPVOID lpBaseAddress,
    /* [size_is][in] */ BYTE __RPC_FAR lpBuffer[  ],
    /* [in] */ DWORD nSize,
    /* [full] */ LPDWORD lpNumberOfBytesWritten);

BOOL rpcDebugActiveProcess( 
    DWORD dwProcessId);

BOOL rpcContinueDebugEvent( 
    DWORD dwProcessId,
    DWORD dwThreadId,
    DWORD dwContinueStatus);

BOOL rpcGetThreadContext( 
    HANDLE hThread,
    /* [full] */ LPCONTEXT lpContext);

BOOL rpcGetThreadSelectorEntry( 
    HANDLE hThread,
    DWORD dwSelector,
    /* [full] */ LPLDT_ENTRY lpSelectorEntry);

BOOL rpcReadProcessMemory( 
    HANDLE hProcess,
    const LPVOID lpBaseAddress,
    /* [size_is][in] */ BYTE __RPC_FAR lpBuffer[  ],
    /* [in] */ DWORD nSize,
    /* [full] */ LPDWORD lpNumberOfBytesRead);

BOOL rpcSetThreadContext( 
    HANDLE hThread,
    /* [full][in] */ const CONTEXT __RPC_FAR *lpContext);

BOOL rpcCreateProcessA( 
    LPCSTR lpApplicationName,
    LPSTR lpCommandLine,
    /* [full][in] */ LPSECURITY_ATTRIBUTES lpProcessAttributes,
    /* [full][in] */ LPSECURITY_ATTRIBUTES lpThreadAttributes,
    BOOL bInheritHandles,
    DWORD dwCreationFlags,
    DWORD dwEnvSize,
    /* [size_is] */ BYTE __RPC_FAR lpEnvironment[  ],
    LPCSTR lpCurrentDirectory,
    /* [full] */ LPSTARTUPINFOA lpStartupInfo,
    /* [full] */ LPPROCESS_INFORMATION lpProcessInformation,
    /* [full] */ DWORD __RPC_FAR *lpdwHandled);

BOOL rpcCloseHandle( 
    HANDLE hObject,
    /* [full] */ DWORD __RPC_FAR *dwHandled);

HANDLE rpcOpenProcess( 
    DWORD dwDesiredAccess,
    BOOL bInheritHandle,
    DWORD dwProcessId,
    /* [full] */ DWORD __RPC_FAR *dwHandled);



extern RPC_IF_HANDLE RemoteDebuggerServer_v1_0_c_ifspec;
extern RPC_IF_HANDLE RemoteDebuggerServer_v1_0_s_ifspec;
#endif /* __RemoteDebuggerServer_INTERFACE_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
