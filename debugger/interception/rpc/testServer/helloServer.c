/* file: hellos.c */
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "testServ.h"
 

void HelloWorld(short data)
{
	printf("Hello, world! Data = 0x%04X\n", data);
}

void Shutdown(void)
{
    RPC_STATUS status;
 
    status = RpcMgmtStopServerListening(NULL);
 
    if (status) 
       exit(status);
 
    status = RpcServerUnregisterIf(NULL, NULL, FALSE);
 
    if (status) 
       exit(status);
}

void main()
{
    RPC_STATUS status;
    unsigned char * pszProtocolSequence = "ncacn_np";
    unsigned char * pszSecurity     = NULL; /*Security not implemented */
    unsigned char * pszEndpoint    = "\\pipe\\hello";
    unsigned int    cMinCalls      = 1;
    unsigned int    cMaxCalls      = 20;
    unsigned int    fDontWait      = FALSE;
 
    status = RpcServerUseProtseqEp(pszProtocolSequence, cMaxCalls,
                                   pszEndpoint, pszSecurity); 
 
    if (status) 
        exit(status);
 
    status = RpcServerRegisterIf(TestServer_v1_0_s_ifspec, NULL, NULL); 
 
    if (status) 
        exit(status);
 
    status = RpcServerListen(cMinCalls, cMaxCalls, fDontWait);
 
    if (status) 
        exit(status);
 
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
