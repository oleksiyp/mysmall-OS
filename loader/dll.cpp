#include <stdio.h>
#include "pefmt.h"
#include "unreal.h"

IMAGE_OPTIONAL_HEADER getDllOptHeader(DWORD base)
{
	IMAGE_DOS_HEADER header;
	IMAGE_NT_HEADERS ntheader;
	highMemCopy(base, to_la(_SS, (WORD)&header), sizeof(header));
	highMemCopy(base+header.e_lfanew, to_la(_SS, (WORD)&ntheader), sizeof(ntheader));	
	return ntheader.OptionalHeader;
}

DWORD getDllEntryPoint(DWORD base)
{
	return getDllOptHeader(base).AddressOfEntryPoint;
}

DWORD getDllImageBase(DWORD base)
{
	return getDllOptHeader(base).ImageBase;
}
/*
DWORD getProcAddress(DWORD base, char *name)
{
	IMAGE_OPTIONAL_HEADER oh = getDllOptHeader(base);
	if(oh.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size==0)
		return 0;
	
	IMAGE_EXPORT_DIRECTORY ed;
	DWORD dirLa = oh.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
	DWORD dw = *(DWORD *)((char *)(&oh)+ 96);
	highMemCopy(base + dirLa, to_la(_SS, (WORD)&ed), sizeof(ed));
	DWORD pnamesLa = base + ed.AddressOfNames;
	asm int 3;
	for (int i = 0;i < ed.NumberOfNames; i++)
	{
		DWORD nameLa;
		highMemCopy(pnamesLa, to_la(_SS, (WORD)&nameLa), 4);
		char buf[1024];
		nameLa += base;
		highMemCopy(nameLa, to_la(_SS, (WORD)buf), 1024);
		printf("%s\n", buf);
		pnamesLa += 4;
	}
	return 0;
}
*/