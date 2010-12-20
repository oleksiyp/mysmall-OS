#include <stdio.h>
#include <string.h>
#include "types.h"
#include "unreal.h"
#include "dll.h"
#include "pefmt.h"
#include "prot32.h"


DWORD kernelLA = 0x200000; // second MB

int main(void)
{
	FILE *fp = fopen("a:\\kernel.dll", "rb");
	if (fp == 0)
	{
		printf("Failed to open 'kernel.dll'\n");
		return 0;
	}

	printf("Switching to unreal mode...");
	switchUnreal();
	printf("OK\n");

	char buf[4096];
	printf("Loading kernel");
	DWORD la = kernelLA;
	DWORD read = 0;
	while(1)
	{
		int l = fread(buf, 1, 4096, fp);
		if (l <= 0) break; 		
		highMemCopy(to_la(_DS, (WORD)buf), la, l);
		read += l;
		la += l;
		printf(".");
	}

	if (read > 0)
	{
		printf("OK\n");
		printf("%d bytes read\n", read);
		printf("Switching to protected mode\n");
		DWORD entryPoint = getDllEntryPoint(kernelLA);
		DWORD imageBase = getDllImageBase(kernelLA);
		printf("image base = 0x%08lX\n", imageBase);
		printf("image entry point = 0x%08lX\n", entryPoint);
//		getProcAddress(kernelLA, "");
		switchProtected(kernelLA+entryPoint);
	} else {
		printf("failed\n");
		printf("%d bytes read\n", read);
	}

	fclose(fp);
	return 0;
}