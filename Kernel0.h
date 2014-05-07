/* voc  1.0  [2013/09/23] xtspkaPS */

#ifndef Kernel0__h
#define Kernel0__h

#include "SYSTEM.h"
#include "Unix.h"

typedef
	void (*Kernel0_KeyCmd)(void);

typedef
	void (*Kernel0_ObjFinalizer)(SYSTEM_PTR);


import Unix_JmpBuf Kernel0_trapEnv;
import LONGINT Kernel0_nofiles;
import Unix_FdSet Kernel0_readSet, Kernel0_readySet;
import Kernel0_KeyCmd Kernel0_FKey[16];
import BOOLEAN Kernel0_littleEndian;
import LONGINT Kernel0_TimeUnit;
import CHAR Kernel0_LIB[256], Kernel0_CWD[256];
import CHAR Kernel0_OBERON[1024];
import CHAR Kernel0_MODULES[1024];
import CHAR Kernel0_prefix[256], Kernel0_fullprefix[256];


import void Kernel0_GetClock (LONGINT *t, LONGINT *d);
import void Kernel0_InstallTermHandler (void (*p)(void));
import LONGINT Kernel0_LargestAvailable (void);
import void Kernel0_Select (LONGINT delay);
import void Kernel0_SetClock (LONGINT t, LONGINT d);
import LONGINT Kernel0_Time (void);
import void *Kernel0__init(void);

#define Kernel0_Exit(n)	exit(n)
#define Kernel0_GC(markStack)	SYSTEM_GC(markStack)
#define Kernel0_Lock()	SYSTEM_lock++
#define Kernel0_RegisterObject(obj, finalize)	SYSTEM_REGFIN(obj, finalize)
#define Kernel0_SetHalt(p)	SYSTEM_Halt = p
#define Kernel0_Unlock()	SYSTEM_lock--; if (SYSTEM_interrupted && SYSTEM_lock == 0) __HALT(-9)
#define Kernel0_allocated()	SYSTEM_allocated
#define Kernel0_free(adr)	(void)free(adr)
#define Kernel0_heapsize()	SYSTEM_heapsize
#define Kernel0_malloc(size)	(LONGINT)malloc(size)
#define Kernel0_siglongjmp(env, env__typ, val)	siglongjmp(env, val)
#define Kernel0_sigsetjmp(env, env__typ, savemask)	__sigsetjmp(env, savemask)

#endif
