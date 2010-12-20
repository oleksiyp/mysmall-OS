/* this ALWAYS GENERATED file contains the RPC server stubs */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Jan 20 17:09:59 2005
 */
/* Compiler settings for RemoteDebuggerServer.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )

#include <string.h>
#include "RemoteDebuggerServer.h"

#define TYPE_FORMAT_STRING_SIZE   467                               
#define PROC_FORMAT_STRING_SIZE   119                               

typedef struct _MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } MIDL_TYPE_FORMAT_STRING;

typedef struct _MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } MIDL_PROC_FORMAT_STRING;

extern const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString;
extern const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString;

/* Standard interface: RemoteDebuggerServer, ver. 1.0,
   GUID={0xafa74268,0x5823,0x47d5,{0xad,0xc7,0xa6,0xe8,0x73,0xf7,0x48,0x18}} */


extern RPC_DISPATCH_TABLE RemoteDebuggerServer_v1_0_DispatchTable;

static const RPC_SERVER_INTERFACE RemoteDebuggerServer___RpcServerInterface =
    {
    sizeof(RPC_SERVER_INTERFACE),
    {{0xafa74268,0x5823,0x47d5,{0xad,0xc7,0xa6,0xe8,0x73,0xf7,0x48,0x18}},{1,0}},
    {{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}},
    &RemoteDebuggerServer_v1_0_DispatchTable,
    0,
    0,
    0,
    0,
    0
    };
RPC_IF_HANDLE RemoteDebuggerServer_v1_0_s_ifspec = (RPC_IF_HANDLE)& RemoteDebuggerServer___RpcServerInterface;

extern const MIDL_STUB_DESC RemoteDebuggerServer_StubDesc;

void __RPC_STUB
RemoteDebuggerServer_rpcWaitForDebugEvent(
    PRPC_MESSAGE _pRpcMessage )
{
    BOOL _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    DWORD dwMilliseconds;
    LPDEBUG_EVENT lpDebugEvent;
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &RemoteDebuggerServer_StubDesc);
    
    ( LPDEBUG_EVENT  )lpDebugEvent = 0;
    RpcTryFinally
        {
        RpcTryExcept
            {
            _StubMsg.FullPtrXlatTables = NdrFullPointerXlatInit(0,XLAT_SERVER);
            
            if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[0] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&lpDebugEvent,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            dwMilliseconds = *(( DWORD __RPC_FAR * )_StubMsg.Buffer)++;
            
            if(_StubMsg.Buffer > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            }
        RpcExcept( RPC_BAD_STUB_DATA_EXCEPTION_FILTER )
            {
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
            }
        RpcEndExcept
        
        _RetVal = rpcWaitForDebugEvent(lpDebugEvent,dwMilliseconds);
        
        _StubMsg.BufferLength = 4U;
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        *(( BOOL __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)lpDebugEvent,
                        &__MIDL_TypeFormatString.Format[2] );
        
        NdrFullPointerXlatFree(_StubMsg.FullPtrXlatTables);
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
RemoteDebuggerServer_rpcWriteProcessMemory(
    PRPC_MESSAGE _pRpcMessage )
{
    BOOL _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    HANDLE hProcess;
    LPVOID lpBaseAddress;
    BYTE ( __RPC_FAR *lpBuffer )[  ];
    LPDWORD lpNumberOfBytesWritten;
    DWORD nSize;
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &RemoteDebuggerServer_StubDesc);
    
    lpBuffer = 0;
    ( LPDWORD  )lpNumberOfBytesWritten = 0;
    RpcTryFinally
        {
        RpcTryExcept
            {
            _StubMsg.FullPtrXlatTables = NdrFullPointerXlatInit(0,XLAT_SERVER);
            
            if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[8] );
            
            hProcess = *(( HANDLE __RPC_FAR * )_StubMsg.Buffer)++;
            
            lpBaseAddress = *(( LPVOID __RPC_FAR * )_StubMsg.Buffer)++;
            
            NdrConformantArrayUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                          (unsigned char __RPC_FAR * __RPC_FAR *)&lpBuffer,
                                          (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[264],
                                          (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            nSize = *(( DWORD __RPC_FAR * )_StubMsg.Buffer)++;
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&lpNumberOfBytesWritten,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[274],
                                  (unsigned char)0 );
            
            if(_StubMsg.Buffer > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            }
        RpcExcept( RPC_BAD_STUB_DATA_EXCEPTION_FILTER )
            {
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
            }
        RpcEndExcept
        
        _RetVal = rpcWriteProcessMemory(
                                hProcess,
                                lpBaseAddress,
                                *lpBuffer,
                                nSize,
                                lpNumberOfBytesWritten);
        
        _StubMsg.BufferLength = 4U;
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        *(( BOOL __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)lpNumberOfBytesWritten,
                        &__MIDL_TypeFormatString.Format[274] );
        
        NdrFullPointerXlatFree(_StubMsg.FullPtrXlatTables);
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
RemoteDebuggerServer_rpcDebugActiveProcess(
    PRPC_MESSAGE _pRpcMessage )
{
    BOOL _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    DWORD dwProcessId;
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &RemoteDebuggerServer_StubDesc);
    
    RpcTryFinally
        {
        RpcTryExcept
            {
            if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[24] );
            
            dwProcessId = *(( DWORD __RPC_FAR * )_StubMsg.Buffer)++;
            
            if(_StubMsg.Buffer > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            }
        RpcExcept( RPC_BAD_STUB_DATA_EXCEPTION_FILTER )
            {
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
            }
        RpcEndExcept
        
        _RetVal = rpcDebugActiveProcess(dwProcessId);
        
        _StubMsg.BufferLength = 4U;
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        *(( BOOL __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
RemoteDebuggerServer_rpcContinueDebugEvent(
    PRPC_MESSAGE _pRpcMessage )
{
    BOOL _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    DWORD dwContinueStatus;
    DWORD dwProcessId;
    DWORD dwThreadId;
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &RemoteDebuggerServer_StubDesc);
    
    RpcTryFinally
        {
        RpcTryExcept
            {
            if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[28] );
            
            dwProcessId = *(( DWORD __RPC_FAR * )_StubMsg.Buffer)++;
            
            dwThreadId = *(( DWORD __RPC_FAR * )_StubMsg.Buffer)++;
            
            dwContinueStatus = *(( DWORD __RPC_FAR * )_StubMsg.Buffer)++;
            
            if(_StubMsg.Buffer > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            }
        RpcExcept( RPC_BAD_STUB_DATA_EXCEPTION_FILTER )
            {
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
            }
        RpcEndExcept
        
        _RetVal = rpcContinueDebugEvent(
                                dwProcessId,
                                dwThreadId,
                                dwContinueStatus);
        
        _StubMsg.BufferLength = 4U;
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        *(( BOOL __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
RemoteDebuggerServer_rpcGetThreadContext(
    PRPC_MESSAGE _pRpcMessage )
{
    BOOL _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    HANDLE hThread;
    LPCONTEXT lpContext;
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &RemoteDebuggerServer_StubDesc);
    
    ( LPCONTEXT  )lpContext = 0;
    RpcTryFinally
        {
        RpcTryExcept
            {
            _StubMsg.FullPtrXlatTables = NdrFullPointerXlatInit(0,XLAT_SERVER);
            
            if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[36] );
            
            hThread = *(( HANDLE __RPC_FAR * )_StubMsg.Buffer)++;
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&lpContext,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[278],
                                  (unsigned char)0 );
            
            if(_StubMsg.Buffer > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            }
        RpcExcept( RPC_BAD_STUB_DATA_EXCEPTION_FILTER )
            {
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
            }
        RpcEndExcept
        
        _RetVal = rpcGetThreadContext(hThread,lpContext);
        
        _StubMsg.BufferLength = 4U;
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        *(( BOOL __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)lpContext,
                        &__MIDL_TypeFormatString.Format[278] );
        
        NdrFullPointerXlatFree(_StubMsg.FullPtrXlatTables);
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
RemoteDebuggerServer_rpcGetThreadSelectorEntry(
    PRPC_MESSAGE _pRpcMessage )
{
    BOOL _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    DWORD dwSelector;
    HANDLE hThread;
    LPLDT_ENTRY lpSelectorEntry;
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &RemoteDebuggerServer_StubDesc);
    
    ( LPLDT_ENTRY  )lpSelectorEntry = 0;
    RpcTryFinally
        {
        RpcTryExcept
            {
            _StubMsg.FullPtrXlatTables = NdrFullPointerXlatInit(0,XLAT_SERVER);
            
            if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[44] );
            
            hThread = *(( HANDLE __RPC_FAR * )_StubMsg.Buffer)++;
            
            dwSelector = *(( DWORD __RPC_FAR * )_StubMsg.Buffer)++;
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&lpSelectorEntry,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[348],
                                  (unsigned char)0 );
            
            if(_StubMsg.Buffer > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            }
        RpcExcept( RPC_BAD_STUB_DATA_EXCEPTION_FILTER )
            {
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
            }
        RpcEndExcept
        
        _RetVal = rpcGetThreadSelectorEntry(
                                    hThread,
                                    dwSelector,
                                    lpSelectorEntry);
        
        _StubMsg.BufferLength = 4U;
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        *(( BOOL __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)lpSelectorEntry,
                        &__MIDL_TypeFormatString.Format[348] );
        
        NdrFullPointerXlatFree(_StubMsg.FullPtrXlatTables);
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
RemoteDebuggerServer_rpcReadProcessMemory(
    PRPC_MESSAGE _pRpcMessage )
{
    BOOL _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    HANDLE hProcess;
    LPVOID lpBaseAddress;
    BYTE ( __RPC_FAR *lpBuffer )[  ];
    LPDWORD lpNumberOfBytesRead;
    DWORD nSize;
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &RemoteDebuggerServer_StubDesc);
    
    lpBuffer = 0;
    ( LPDWORD  )lpNumberOfBytesRead = 0;
    RpcTryFinally
        {
        RpcTryExcept
            {
            _StubMsg.FullPtrXlatTables = NdrFullPointerXlatInit(0,XLAT_SERVER);
            
            if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[8] );
            
            hProcess = *(( HANDLE __RPC_FAR * )_StubMsg.Buffer)++;
            
            lpBaseAddress = *(( LPVOID __RPC_FAR * )_StubMsg.Buffer)++;
            
            NdrConformantArrayUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                          (unsigned char __RPC_FAR * __RPC_FAR *)&lpBuffer,
                                          (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[264],
                                          (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            nSize = *(( DWORD __RPC_FAR * )_StubMsg.Buffer)++;
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&lpNumberOfBytesRead,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[274],
                                  (unsigned char)0 );
            
            if(_StubMsg.Buffer > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            }
        RpcExcept( RPC_BAD_STUB_DATA_EXCEPTION_FILTER )
            {
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
            }
        RpcEndExcept
        
        _RetVal = rpcReadProcessMemory(
                               hProcess,
                               lpBaseAddress,
                               *lpBuffer,
                               nSize,
                               lpNumberOfBytesRead);
        
        _StubMsg.BufferLength = 4U;
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        *(( BOOL __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)lpNumberOfBytesRead,
                        &__MIDL_TypeFormatString.Format[274] );
        
        NdrFullPointerXlatFree(_StubMsg.FullPtrXlatTables);
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
RemoteDebuggerServer_rpcSetThreadContext(
    PRPC_MESSAGE _pRpcMessage )
{
    BOOL _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    HANDLE hThread;
    const CONTEXT __RPC_FAR *lpContext;
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &RemoteDebuggerServer_StubDesc);
    
    ( CONTEXT __RPC_FAR * )lpContext = 0;
    RpcTryFinally
        {
        RpcTryExcept
            {
            _StubMsg.FullPtrXlatTables = NdrFullPointerXlatInit(0,XLAT_SERVER);
            
            if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[36] );
            
            hThread = *(( HANDLE __RPC_FAR * )_StubMsg.Buffer)++;
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&lpContext,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[278],
                                  (unsigned char)0 );
            
            if(_StubMsg.Buffer > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            }
        RpcExcept( RPC_BAD_STUB_DATA_EXCEPTION_FILTER )
            {
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
            }
        RpcEndExcept
        
        _RetVal = rpcSetThreadContext(hThread,lpContext);
        
        _StubMsg.BufferLength = 4U;
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        *(( BOOL __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)lpContext,
                        &__MIDL_TypeFormatString.Format[278] );
        
        NdrFullPointerXlatFree(_StubMsg.FullPtrXlatTables);
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
RemoteDebuggerServer_rpcCreateProcessA(
    PRPC_MESSAGE _pRpcMessage )
{
    BOOL _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    BOOL bInheritHandles;
    DWORD dwCreationFlags;
    DWORD dwEnvSize;
    LPCSTR lpApplicationName;
    LPSTR lpCommandLine;
    LPCSTR lpCurrentDirectory;
    BYTE ( __RPC_FAR *lpEnvironment )[  ];
    LPSECURITY_ATTRIBUTES lpProcessAttributes;
    LPPROCESS_INFORMATION lpProcessInformation;
    LPSTARTUPINFOA lpStartupInfo;
    LPSECURITY_ATTRIBUTES lpThreadAttributes;
    DWORD __RPC_FAR *lpdwHandled;
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &RemoteDebuggerServer_StubDesc);
    
    ( LPCSTR  )lpApplicationName = 0;
    ( LPSTR  )lpCommandLine = 0;
    ( LPSECURITY_ATTRIBUTES  )lpProcessAttributes = 0;
    ( LPSECURITY_ATTRIBUTES  )lpThreadAttributes = 0;
    lpEnvironment = 0;
    ( LPCSTR  )lpCurrentDirectory = 0;
    ( LPSTARTUPINFOA  )lpStartupInfo = 0;
    ( LPPROCESS_INFORMATION  )lpProcessInformation = 0;
    ( DWORD __RPC_FAR * )lpdwHandled = 0;
    RpcTryFinally
        {
        RpcTryExcept
            {
            _StubMsg.FullPtrXlatTables = NdrFullPointerXlatInit(0,XLAT_SERVER);
            
            if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[54] );
            
            NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char __RPC_FAR * __RPC_FAR *)&lpApplicationName,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[364],
                                           (unsigned char)0 );
            
            NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char __RPC_FAR * __RPC_FAR *)&lpCommandLine,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[364],
                                           (unsigned char)0 );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&lpProcessAttributes,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[366],
                                  (unsigned char)0 );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&lpThreadAttributes,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[366],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            bInheritHandles = *(( BOOL __RPC_FAR * )_StubMsg.Buffer)++;
            
            dwCreationFlags = *(( DWORD __RPC_FAR * )_StubMsg.Buffer)++;
            
            dwEnvSize = *(( DWORD __RPC_FAR * )_StubMsg.Buffer)++;
            
            NdrConformantArrayUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                          (unsigned char __RPC_FAR * __RPC_FAR *)&lpEnvironment,
                                          (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[370],
                                          (unsigned char)0 );
            
            NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char __RPC_FAR * __RPC_FAR *)&lpCurrentDirectory,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[364],
                                           (unsigned char)0 );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&lpStartupInfo,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[380],
                                  (unsigned char)0 );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&lpProcessInformation,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[452],
                                  (unsigned char)0 );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&lpdwHandled,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[274],
                                  (unsigned char)0 );
            
            if(_StubMsg.Buffer > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            }
        RpcExcept( RPC_BAD_STUB_DATA_EXCEPTION_FILTER )
            {
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
            }
        RpcEndExcept
        
        _RetVal = rpcCreateProcessA(
                            lpApplicationName,
                            lpCommandLine,
                            lpProcessAttributes,
                            lpThreadAttributes,
                            bInheritHandles,
                            dwCreationFlags,
                            dwEnvSize,
                            *lpEnvironment,
                            lpCurrentDirectory,
                            lpStartupInfo,
                            lpProcessInformation,
                            lpdwHandled);
        
        _StubMsg.BufferLength = 4U;
        _StubMsg.BufferLength += 16;
        
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        *(( BOOL __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)lpProcessAttributes,
                        &__MIDL_TypeFormatString.Format[366] );
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)lpThreadAttributes,
                        &__MIDL_TypeFormatString.Format[366] );
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)lpStartupInfo,
                        &__MIDL_TypeFormatString.Format[380] );
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)lpProcessInformation,
                        &__MIDL_TypeFormatString.Format[452] );
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)lpdwHandled,
                        &__MIDL_TypeFormatString.Format[274] );
        
        NdrFullPointerXlatFree(_StubMsg.FullPtrXlatTables);
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
RemoteDebuggerServer_rpcCloseHandle(
    PRPC_MESSAGE _pRpcMessage )
{
    BOOL _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    DWORD __RPC_FAR *dwHandled;
    HANDLE hObject;
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &RemoteDebuggerServer_StubDesc);
    
    ( DWORD __RPC_FAR * )dwHandled = 0;
    RpcTryFinally
        {
        RpcTryExcept
            {
            _StubMsg.FullPtrXlatTables = NdrFullPointerXlatInit(0,XLAT_SERVER);
            
            if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[98] );
            
            hObject = *(( HANDLE __RPC_FAR * )_StubMsg.Buffer)++;
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&dwHandled,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[274],
                                  (unsigned char)0 );
            
            if(_StubMsg.Buffer > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            }
        RpcExcept( RPC_BAD_STUB_DATA_EXCEPTION_FILTER )
            {
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
            }
        RpcEndExcept
        
        _RetVal = rpcCloseHandle(hObject,dwHandled);
        
        _StubMsg.BufferLength = 4U;
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        *(( BOOL __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)dwHandled,
                        &__MIDL_TypeFormatString.Format[274] );
        
        NdrFullPointerXlatFree(_StubMsg.FullPtrXlatTables);
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
RemoteDebuggerServer_rpcOpenProcess(
    PRPC_MESSAGE _pRpcMessage )
{
    HANDLE _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    BOOL bInheritHandle;
    DWORD dwDesiredAccess;
    DWORD __RPC_FAR *dwHandled;
    DWORD dwProcessId;
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &RemoteDebuggerServer_StubDesc);
    
    ( DWORD __RPC_FAR * )dwHandled = 0;
    RpcTryFinally
        {
        RpcTryExcept
            {
            _StubMsg.FullPtrXlatTables = NdrFullPointerXlatInit(0,XLAT_SERVER);
            
            if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[106] );
            
            dwDesiredAccess = *(( DWORD __RPC_FAR * )_StubMsg.Buffer)++;
            
            bInheritHandle = *(( BOOL __RPC_FAR * )_StubMsg.Buffer)++;
            
            dwProcessId = *(( DWORD __RPC_FAR * )_StubMsg.Buffer)++;
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&dwHandled,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[274],
                                  (unsigned char)0 );
            
            if(_StubMsg.Buffer > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            }
        RpcExcept( RPC_BAD_STUB_DATA_EXCEPTION_FILTER )
            {
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
            }
        RpcEndExcept
        
        _RetVal = rpcOpenProcess(
                         dwDesiredAccess,
                         bInheritHandle,
                         dwProcessId,
                         dwHandled);
        
        _StubMsg.BufferLength = 4U;
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        *(( HANDLE __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)dwHandled,
                        &__MIDL_TypeFormatString.Format[274] );
        
        NdrFullPointerXlatFree(_StubMsg.FullPtrXlatTables);
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


static const MIDL_STUB_DESC RemoteDebuggerServer_StubDesc = 
    {
    (void __RPC_FAR *)& RemoteDebuggerServer___RpcServerInterface,
    MIDL_user_allocate,
    MIDL_user_free,
    0,
    0,
    0,
    0,
    0,
    __MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x10001, /* Ndr library version */
    0,
    0x50100a4, /* MIDL Version 5.1.164 */
    0,
    0,
    0,  /* notify & notify_flag routine table */
    1,  /* Flags */
    0,  /* Reserved3 */
    0,  /* Reserved4 */
    0   /* Reserved5 */
    };

static RPC_DISPATCH_FUNCTION RemoteDebuggerServer_table[] =
    {
    RemoteDebuggerServer_rpcWaitForDebugEvent,
    RemoteDebuggerServer_rpcWriteProcessMemory,
    RemoteDebuggerServer_rpcDebugActiveProcess,
    RemoteDebuggerServer_rpcContinueDebugEvent,
    RemoteDebuggerServer_rpcGetThreadContext,
    RemoteDebuggerServer_rpcGetThreadSelectorEntry,
    RemoteDebuggerServer_rpcReadProcessMemory,
    RemoteDebuggerServer_rpcSetThreadContext,
    RemoteDebuggerServer_rpcCreateProcessA,
    RemoteDebuggerServer_rpcCloseHandle,
    RemoteDebuggerServer_rpcOpenProcess,
    0
    };
RPC_DISPATCH_TABLE RemoteDebuggerServer_v1_0_DispatchTable = 
    {
    11,
    RemoteDebuggerServer_table
    };

#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString =
    {
        0,
        {
			
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/*  2 */	NdrFcShort( 0x2 ),	/* Type Offset=2 */
/*  4 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/*  6 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/*  8 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 10 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 12 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 14 */	NdrFcShort( 0x108 ),	/* Type Offset=264 */
/* 16 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 18 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 20 */	NdrFcShort( 0x112 ),	/* Type Offset=274 */
/* 22 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 24 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 26 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 28 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 30 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 32 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 34 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 36 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 38 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 40 */	NdrFcShort( 0x116 ),	/* Type Offset=278 */
/* 42 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 44 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 46 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 48 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 50 */	NdrFcShort( 0x15c ),	/* Type Offset=348 */
/* 52 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 54 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 56 */	NdrFcShort( 0x16a ),	/* Type Offset=362 */
/* 58 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 60 */	NdrFcShort( 0x16a ),	/* Type Offset=362 */
/* 62 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 64 */	NdrFcShort( 0x16e ),	/* Type Offset=366 */
/* 66 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 68 */	NdrFcShort( 0x16e ),	/* Type Offset=366 */
/* 70 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 72 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 74 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 76 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 78 */	NdrFcShort( 0x172 ),	/* Type Offset=370 */
/* 80 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 82 */	NdrFcShort( 0x16a ),	/* Type Offset=362 */
/* 84 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 86 */	NdrFcShort( 0x17c ),	/* Type Offset=380 */
/* 88 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 90 */	NdrFcShort( 0x1c4 ),	/* Type Offset=452 */
/* 92 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 94 */	NdrFcShort( 0x112 ),	/* Type Offset=274 */
/* 96 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 98 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 100 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 102 */	NdrFcShort( 0x112 ),	/* Type Offset=274 */
/* 104 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 106 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 108 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 110 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 112 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 114 */	NdrFcShort( 0x112 ),	/* Type Offset=274 */
/* 116 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */

			0x0
        }
    };

static const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x14, 0x0,	/* FC_FP */
/*  4 */	NdrFcShort( 0xf4 ),	/* Offset= 244 (248) */
/*  6 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/*  8 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 10 */	NdrFcShort( 0xfff4 ),	/* -12 */
/* 12 */	NdrFcShort( 0x2 ),	/* Offset= 2 (14) */
/* 14 */	NdrFcShort( 0x54 ),	/* 84 */
/* 16 */	NdrFcShort( 0x9 ),	/* 9 */
/* 18 */	NdrFcLong( 0x1 ),	/* 1 */
/* 22 */	NdrFcShort( 0x68 ),	/* Offset= 104 (126) */
/* 24 */	NdrFcLong( 0x2 ),	/* 2 */
/* 28 */	NdrFcShort( 0x8c ),	/* Offset= 140 (168) */
/* 30 */	NdrFcLong( 0x3 ),	/* 3 */
/* 34 */	NdrFcShort( 0x8e ),	/* Offset= 142 (176) */
/* 36 */	NdrFcLong( 0x4 ),	/* 4 */
/* 40 */	NdrFcShort( 0x9c ),	/* Offset= 156 (196) */
/* 42 */	NdrFcLong( 0x5 ),	/* 5 */
/* 46 */	NdrFcShort( 0x96 ),	/* Offset= 150 (196) */
/* 48 */	NdrFcLong( 0x6 ),	/* 6 */
/* 52 */	NdrFcShort( 0x96 ),	/* Offset= 150 (202) */
/* 54 */	NdrFcLong( 0x7 ),	/* 7 */
/* 58 */	NdrFcShort( 0x8a ),	/* Offset= 138 (196) */
/* 60 */	NdrFcLong( 0x8 ),	/* 8 */
/* 64 */	NdrFcShort( 0x9a ),	/* Offset= 154 (218) */
/* 66 */	NdrFcLong( 0x9 ),	/* 9 */
/* 70 */	NdrFcShort( 0xaa ),	/* Offset= 170 (240) */
/* 72 */	NdrFcShort( 0xffffffff ),	/* Offset= -1 (71) */
/* 74 */	
			0x1d,		/* FC_SMFARRAY */
			0x3,		/* 3 */
/* 76 */	NdrFcShort( 0x3c ),	/* 60 */
/* 78 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 80 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 82 */	NdrFcShort( 0x50 ),	/* 80 */
/* 84 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 86 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 88 */	NdrFcShort( 0x8 ),	/* 8 */
/* 90 */	NdrFcShort( 0x8 ),	/* 8 */
/* 92 */	0x14, 0x0,	/* FC_FP */
/* 94 */	NdrFcShort( 0xfffffff2 ),	/* Offset= -14 (80) */
/* 96 */	
			0x47,		/* FC_FIXED_REPEAT */
			0x5c,		/* FC_PAD */
/* 98 */	NdrFcShort( 0xf ),	/* 15 */
/* 100 */	NdrFcShort( 0x4 ),	/* 4 */
/* 102 */	NdrFcShort( 0x14 ),	/* 20 */
/* 104 */	NdrFcShort( 0x1 ),	/* 1 */
/* 106 */	NdrFcShort( 0x14 ),	/* 20 */
/* 108 */	NdrFcShort( 0x14 ),	/* 20 */
/* 110 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 112 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 114 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 116 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 118 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 120 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 122 */	NdrFcShort( 0xffffffd0 ),	/* Offset= -48 (74) */
/* 124 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 126 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 128 */	NdrFcShort( 0x54 ),	/* 84 */
/* 130 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 132 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 134 */	NdrFcShort( 0x8 ),	/* 8 */
/* 136 */	NdrFcShort( 0x8 ),	/* 8 */
/* 138 */	0x14, 0x0,	/* FC_FP */
/* 140 */	NdrFcShort( 0xffffffc4 ),	/* Offset= -60 (80) */
/* 142 */	
			0x47,		/* FC_FIXED_REPEAT */
			0x5c,		/* FC_PAD */
/* 144 */	NdrFcShort( 0xf ),	/* 15 */
/* 146 */	NdrFcShort( 0x4 ),	/* 4 */
/* 148 */	NdrFcShort( 0x10 ),	/* 16 */
/* 150 */	NdrFcShort( 0x1 ),	/* 1 */
/* 152 */	NdrFcShort( 0x10 ),	/* 16 */
/* 154 */	NdrFcShort( 0x10 ),	/* 16 */
/* 156 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 158 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 160 */	
			0x5b,		/* FC_END */

			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 162 */	0x0,		/* 0 */
			NdrFcShort( 0xffffffad ),	/* Offset= -83 (80) */
			0x8,		/* FC_LONG */
/* 166 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 168 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 170 */	NdrFcShort( 0xc ),	/* 12 */
/* 172 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 174 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 176 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 178 */	NdrFcShort( 0x28 ),	/* 40 */
/* 180 */	NdrFcShort( 0x0 ),	/* 0 */
/* 182 */	NdrFcShort( 0x0 ),	/* Offset= 0 (182) */
/* 184 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 186 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 188 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 190 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 192 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 194 */	0x3e,		/* FC_STRUCTPAD2 */
			0x5b,		/* FC_END */
/* 196 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 198 */	NdrFcShort( 0x4 ),	/* 4 */
/* 200 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 202 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 204 */	NdrFcShort( 0x18 ),	/* 24 */
/* 206 */	NdrFcShort( 0x0 ),	/* 0 */
/* 208 */	NdrFcShort( 0x0 ),	/* Offset= 0 (208) */
/* 210 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 212 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 214 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 216 */	0x3e,		/* FC_STRUCTPAD2 */
			0x5b,		/* FC_END */
/* 218 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 220 */	NdrFcShort( 0x8 ),	/* 8 */
/* 222 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 224 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 226 */	NdrFcShort( 0x0 ),	/* 0 */
/* 228 */	NdrFcShort( 0x0 ),	/* 0 */
/* 230 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 232 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 234 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 236 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 238 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 240 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 242 */	NdrFcShort( 0x8 ),	/* 8 */
/* 244 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 246 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 248 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 250 */	NdrFcShort( 0x60 ),	/* 96 */
/* 252 */	NdrFcShort( 0x0 ),	/* 0 */
/* 254 */	NdrFcShort( 0x0 ),	/* Offset= 0 (254) */
/* 256 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 258 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 260 */	0x0,		/* 0 */
			NdrFcShort( 0xffffff01 ),	/* Offset= -255 (6) */
			0x5b,		/* FC_END */
/* 264 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 266 */	NdrFcShort( 0x1 ),	/* 1 */
/* 268 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
#ifndef _ALPHA_
/* 270 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 272 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/* 274 */	
			0x14, 0x8,	/* FC_FP [simple_pointer] */
/* 276 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 278 */	
			0x14, 0x0,	/* FC_FP */
/* 280 */	NdrFcShort( 0x20 ),	/* Offset= 32 (312) */
/* 282 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 284 */	NdrFcShort( 0x50 ),	/* 80 */
/* 286 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/* 288 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 290 */	NdrFcShort( 0x70 ),	/* 112 */
/* 292 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 294 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 296 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 298 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 300 */	0x0,		/* 0 */
			NdrFcShort( 0xffffffed ),	/* Offset= -19 (282) */
			0x8,		/* FC_LONG */
/* 304 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 306 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 308 */	NdrFcShort( 0x200 ),	/* 512 */
/* 310 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/* 312 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 314 */	NdrFcShort( 0x2cc ),	/* 716 */
/* 316 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 318 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 320 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 322 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 324 */	0x0,		/* 0 */
			NdrFcShort( 0xffffffdb ),	/* Offset= -37 (288) */
			0x8,		/* FC_LONG */
/* 328 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 330 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 332 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 334 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 336 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 338 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 340 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 342 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 344 */	0x0,		/* 0 */
			NdrFcShort( 0xffffffd9 ),	/* Offset= -39 (306) */
			0x5b,		/* FC_END */
/* 348 */	
			0x14, 0x0,	/* FC_FP */
/* 350 */	NdrFcShort( 0x2 ),	/* Offset= 2 (352) */
/* 352 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 354 */	NdrFcShort( 0x8 ),	/* 8 */
/* 356 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 358 */	0x38,		/* FC_ALIGNM4 */
			0x8,		/* FC_LONG */
/* 360 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 362 */	
			0x11, 0x8,	/* FC_RP [simple_pointer] */
/* 364 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 366 */	
			0x14, 0x0,	/* FC_FP */
/* 368 */	NdrFcShort( 0xffffff38 ),	/* Offset= -200 (168) */
/* 370 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 372 */	NdrFcShort( 0x1 ),	/* 1 */
/* 374 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
#ifndef _ALPHA_
/* 376 */	NdrFcShort( 0x18 ),	/* x86, MIPS, PPC Stack size/offset = 24 */
#else
			NdrFcShort( 0x30 ),	/* Alpha Stack size/offset = 48 */
#endif
/* 378 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/* 380 */	
			0x14, 0x0,	/* FC_FP */
/* 382 */	NdrFcShort( 0x2 ),	/* Offset= 2 (384) */
/* 384 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 386 */	NdrFcShort( 0x44 ),	/* 68 */
/* 388 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 390 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 392 */	NdrFcShort( 0x4 ),	/* 4 */
/* 394 */	NdrFcShort( 0x4 ),	/* 4 */
/* 396 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 398 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 400 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 402 */	NdrFcShort( 0x8 ),	/* 8 */
/* 404 */	NdrFcShort( 0x8 ),	/* 8 */
/* 406 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 408 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 410 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 412 */	NdrFcShort( 0xc ),	/* 12 */
/* 414 */	NdrFcShort( 0xc ),	/* 12 */
/* 416 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 418 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 420 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 422 */	NdrFcShort( 0x34 ),	/* 52 */
/* 424 */	NdrFcShort( 0x34 ),	/* 52 */
/* 426 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 428 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/* 430 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 432 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 434 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 436 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 438 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 440 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 442 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 444 */	0x6,		/* FC_SHORT */
			0x38,		/* FC_ALIGNM4 */
/* 446 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 448 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 450 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 452 */	
			0x14, 0x0,	/* FC_FP */
/* 454 */	NdrFcShort( 0x2 ),	/* Offset= 2 (456) */
/* 456 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 458 */	NdrFcShort( 0x10 ),	/* 16 */
/* 460 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 462 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 464 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */

			0x0
        }
    };
