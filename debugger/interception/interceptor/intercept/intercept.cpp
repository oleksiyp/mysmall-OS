// intercept.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "intercept.h"

FILE *log = fopen("log", "w");

IMAGE_OPTIONAL_HEADER getDllOptHeader(PVOID base)
{
	IMAGE_DOS_HEADER *pheader = (IMAGE_DOS_HEADER *)base;
	IMAGE_NT_HEADERS *pntheader = (IMAGE_NT_HEADERS *)((char *)base+ pheader->e_lfanew);
	return pntheader->OptionalHeader;
}

int strnlen(char *name, int maxlen)
{
	int i;
	for (i = 0; i < maxlen; i++)
		if (name[i] == 0)
			break;
	return i;
}

void toCanonical(char *name, char *buf)
{
	int len = strnlen(name, 50);
	strncpy(buf, name, 50);
	buf[len] = 0;
	char *p = strrchr(buf, '.');
	if (!p || stricmp(p, ".dll") != 0)
	{
		strcat(buf, ".dll");
	}
	strlwr(buf);
}


void PatchFunctions(LPVOID handle, PATCH *patchs, int count)
{
	LPVOID base = handle;
	IMAGE_OPTIONAL_HEADER oh = getDllOptHeader(base);
	if(oh.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size==0)
		return;

	DWORD importVA = oh.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;
	IMAGE_IMPORT_DESCRIPTOR *pid = (IMAGE_IMPORT_DESCRIPTOR*)((char *)base + importVA);

	char moduleName[100];
	while(pid->Name)
	{
		char *name = (char*) base + pid->Name;
		toCanonical(name, moduleName);

		DWORD *ptrs = (DWORD *)((char*)base + pid->Characteristics);
		for(int k = 0; ptrs[k]; k++)
		{
			if ((ptrs[k] & 0x80000000) == 0x80000000)
				continue;
			IMAGE_IMPORT_BY_NAME *import = (IMAGE_IMPORT_BY_NAME *)(ptrs[k] + (char*)base);
			char *funcName = (char*)import->Name;
			LPVOID *pptr = (LPVOID*)(pid->FirstThunk+k*4+(char*)base);
			for (int i = 0;i < count; i++)
			{
				if (strcmp(patchs[i].procName, funcName) == 0)
				{
					if (stricmp(moduleName, patchs[i].module) == 0)
						break;
				}
			}
			if (i != count)
			{
				try
				{
					if (*pptr != patchs[i].newProc)
					{
						if (patchs[i].oldProc)
						{
							fprintf(log, "Patching %s!%s\n", moduleName, funcName);
							fflush(log);
							*patchs[i].oldProc = *pptr;
						}

						DWORD dw;
						VirtualProtect(pptr, 0x1000, 4, &dw);
						
						*pptr = patchs[i].newProc;
					}
				} catch(...)
				{
					fprintf(log, "Error patching 0x%08X - %s!%s\n", pptr, moduleName, funcName);
					fflush(log);
				}					
			}
		}
		pid++;
	}
}

HMODULE
(WINAPI
*oldLoadLibraryA)(
    LPCSTR lpLibFileName
    );

void PatchDLL(LPVOID handle);

HMODULE
WINAPI
myLoadLibraryA(
    LPCSTR lpLibFileName
    )
{
	HMODULE ret = 0;
	if (lpLibFileName != 0)
		ret = (*oldLoadLibraryA)(lpLibFileName);
	fprintf(log, "Load library '%s' = 0x%08X\n", lpLibFileName, ret);
	fflush(log);
	if (ret)
		PatchDLL(ret);
	return ret;
}

FARPROC
(WINAPI
*oldGetProcAddress)(
    HMODULE hModule,
    LPCSTR lpProcName
    );

LPVOID crackedGetProcAddress(char *module, const char *name);

FARPROC
WINAPI
myGetProcAddress(
    HMODULE hModule,
    LPCSTR lpProcName)
{
	char buf[MAX_PATH];
	GetModuleFileName(hModule, buf, sizeof(buf));
	char *s = strrchr(buf, '\\');
	if (s) s++; else s = buf;

	if (((DWORD)(lpProcName) >> 16) == 0) // by ordinal
		return (*oldGetProcAddress)(hModule, lpProcName);

	LPVOID ptr = crackedGetProcAddress(s, lpProcName);
	if (ptr)
		return (FARPROC)ptr;
	ptr = (*oldGetProcAddress)(hModule, lpProcName);
	fprintf(log, "Get proc address %s(0x%08X)!%s = 0x%08X\n", s, hModule, lpProcName, ptr);
	return (FARPROC)ptr;
}



PATCH reload_patches[] =
{
	{"kernel32.dll", "LoadLibraryA", (LPVOID)myLoadLibraryA, (LPVOID *)&oldLoadLibraryA},
	{"kernel32.dll", "GetProcAddress", (LPVOID)myGetProcAddress, (LPVOID *)&oldGetProcAddress}
};
extern PATCH debug_patches[];
extern int debug_patches_sz;

void PatchDLL(LPVOID handle)
{
	PatchFunctions(handle, debug_patches, debug_patches_sz);
	PatchFunctions(handle, reload_patches, sizeof(reload_patches)/sizeof(reload_patches[0]));
}

BOOL crackedGetProcAddressPatch(char *module, const char *funcName, LPVOID *ptr, PATCH *patchs, int count)
{
	char moduleName[100], buf2[100];
	toCanonical(module, moduleName);
	for (int i = 0;i < count; i++)
	{
		if (strcmp(patchs[i].procName, funcName) == 0)
		{
			toCanonical(patchs[i].module, buf2);
			if (stricmp(moduleName, buf2) == 0)
				break;
		}
	}
	if (i != count)
	{
		*ptr = patchs[i].newProc;
		return TRUE;
	}
	return FALSE;
}

LPVOID crackedGetProcAddress(char *module, const char *name)
{
	LPVOID ptr;
	if (crackedGetProcAddressPatch(module, name, &ptr, debug_patches, debug_patches_sz))
		return ptr;
	if (crackedGetProcAddressPatch(module, name, &ptr, reload_patches, sizeof(reload_patches)/sizeof(reload_patches[0])))
		return ptr;
	return 0;
}

set<HMODULE> modulesVisited;

void RecurseAllModules(HMODULE base)
{
	modulesVisited.insert(base);
	
	try
	{
		PatchDLL(base);
	} catch(...)
	{
		fprintf(log, "Cought an exception\n");
		fflush(log);
	}

	IMAGE_OPTIONAL_HEADER oh = getDllOptHeader(base);
	if(oh.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size==0)
	{
		fprintf(log, "No import table\n");
		fflush(log);
		return;
	}

	DWORD importVA = oh.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;
	IMAGE_IMPORT_DESCRIPTOR *pid = (IMAGE_IMPORT_DESCRIPTOR*)((char *)base + importVA);

	while(pid->Name)
	{
		char *name = (char*) base + pid->Name;
		HMODULE module = GetModuleHandle(name);
		if (module)
		{
			try
			{
				if (modulesVisited.find(module) == modulesVisited.end())
				{
					fprintf(log ,"Recursing down '%s'\n", name);
					fflush(log);
					RecurseAllModules(module);
				}
			} catch(...) {}
		}
		pid++;
	}
}

void initRemoteDebugging(void);

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			{
				fprintf(log, "DLL_PROCESS_ATTACH\n");
				fflush(log);
				RecurseAllModules(GetModuleHandle(0));
				initRemoteDebugging();
			}
			break;
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
			break;
		case DLL_PROCESS_DETACH:
			fprintf(log, "------\n");
			fclose(log);
			break;
    }
    return TRUE;
}


