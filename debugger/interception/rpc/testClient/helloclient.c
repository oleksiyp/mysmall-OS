#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "testServ.h" 

void main()
{
	RPC_STATUS status;
	unsigned char * pszUuid             = NULL;
	unsigned char * pszProtocolSequence = "ncacn_np";
	unsigned char * pszNetworkAddress   = NULL;
	unsigned char * pszEndpoint    = "\\pipe\\hello";
	unsigned char * pszOptions          = NULL;
	unsigned char * pszStringBinding    = NULL;
	unsigned long ulCode;
	
	status = RpcStringBindingCompose(pszUuid,
		pszProtocolSequence,
		pszNetworkAddress,
		pszEndpoint,
		pszOptions,
		&pszStringBinding);
	if (status) 
		exit(status);
	
	status = RpcBindingFromStringBinding(pszStringBinding,
		&testServ_IfHandle);
	
	if (status) 
		exit(status);
	
	
	RpcTryExcept  
	{
		HelloWorld(666);
		Shutdown();
	}
	RpcExcept(1) 
	{
		ulCode = RpcExceptionCode();
		printf("Runtime reported exception 0x%lx = %ld\n", ulCode, ulCode);
	}
	RpcEndExcept
		
    status = RpcStringFree(&pszStringBinding); 
	
	if (status) 
		exit(status);
	
	status = RpcBindingFree(&testServ_IfHandle);
	
	if (status) 
		exit(status);
	
	exit(0);
	
}  // end main()


/******************************************************/
/*         MIDL allocate and free                     */
/******************************************************/

void __RPC_FAR * __RPC_USER midl_user_allocate(size_t len)
{
	return(malloc(len));
}

void __RPC_USER midl_user_free(void __RPC_FAR * ptr)
{
	free(ptr);
}