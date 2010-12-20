#ifndef _IDT_H_
#define _IDT_H_

#include <basic/types.h>

#define TASK_DESCRIPTOR_TYPE 5
#define INERRUPT_DESCRIPTOR_TYPE 14
#define TRAP_DESCRIPTOR_TYPE 15


typedef struct
{
	dword reserved1 : 16;
	dword tssSelector : 16;
	dword reserved2 : 8;
	dword type : 5; // = 5
	dword dpl : 2;
	dword p : 1;
	dword reserved3 : 16;
} TASK_DESCRIPTOR;

typedef struct
{
	dword offset1 : 16;
	dword segmentSelector : 16;
	dword reserved1 : 5;
	dword null : 3;
	dword type : 5; // = 12
	dword dpl : 2;
	dword p : 1;
	dword offset2 : 16;
} INTERRUPT_DESCRIPTOR;

typedef struct
{
	dword offset1 : 16;
	dword segmentSelector : 16;
	dword reserved1 : 5;
	dword null : 3;
	dword type : 5; // = 15
	dword dpl : 2;
	dword p : 1;
	dword offset2 : 16;
} TRAP_DESCRIPTOR;

typedef struct
{
	union
	{
		TASK_DESCRIPTOR task;
		INTERRUPT_DESCRIPTOR interrupt;
		TRAP_DESCRIPTOR trap;
	};
} IDT_DESCRIPTOR;

#endif