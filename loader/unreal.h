#ifndef _UNREAL_H_
#define _UNREAL_H_

extern "C" void highMemCopy(DWORD from, DWORD to, DWORD bytes);
extern "C" void switchUnreal();
extern "C" DWORD to_la(WORD seg, WORD off);

#endif