#ifndef _INTERCEPT_H_
#define _INTERCEPT_H_

typedef struct
{
	char *module;
	char *procName;
	void *newProc;
	void **oldProc;
} PATCH;


#endif