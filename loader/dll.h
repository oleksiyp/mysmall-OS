#ifndef _DLL_H_
#define _DLL_H_

DWORD getDllImageBase(DWORD la);
DWORD getDllEntryPoint(DWORD la);
DWORD getProcAddress(DWORD base, char *name);

#endif