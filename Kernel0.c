/* voc  1.0  [2013/09/23] xtspkaPS */
#include "SYSTEM.h"
#include "Args.h"
#include "Strings.h"
#include "Unix.h"
#include "version.h"

typedef
	void (*Kernel0_KeyCmd)(void);

typedef
	void (*Kernel0_ObjFinalizer)(SYSTEM_PTR);

typedef
	struct Kernel0_TimeDesc *Kernel0_RealTime;

typedef
	struct Kernel0_TimeDesc {
		LONGINT sec, min, hour, mday, mon, year, wday, isdst, zone, gmtoff;
	} Kernel0_TimeDesc;


export Unix_JmpBuf Kernel0_trapEnv;
export LONGINT Kernel0_nofiles;
export Unix_FdSet Kernel0_readSet, Kernel0_readySet;
export Kernel0_KeyCmd Kernel0_FKey[16];
export BOOLEAN Kernel0_littleEndian;
export LONGINT Kernel0_TimeUnit;
export CHAR Kernel0_LIB[256], Kernel0_CWD[256];
export CHAR Kernel0_OBERON[1024];
export CHAR Kernel0_MODULES[1024];
export CHAR Kernel0_prefix[256], Kernel0_fullprefix[256];
static LONGINT Kernel0_timeStart;

export LONGINT *Kernel0_TimeDesc__typ;

static void Kernel0_EndianTest (void);
export void Kernel0_GetClock (LONGINT *t, LONGINT *d);
static void Kernel0_Halt (LONGINT n);
export void Kernel0_InstallTermHandler (void (*p)(void));
export LONGINT Kernel0_LargestAvailable (void);
export void Kernel0_Select (LONGINT delay);
export void Kernel0_SetClock (LONGINT t, LONGINT d);
export LONGINT Kernel0_Time (void);

#define Kernel0_Exit(n)	exit(n)
#define Kernel0_GC(markStack)	SYSTEM_GC(markStack)
#define Kernel0_Lock()	SYSTEM_lock++
#define Kernel0_RegisterObject(obj, finalize)	SYSTEM_REGFIN(obj, finalize)
#define Kernel0_SetHalt(p)	SYSTEM_Halt = p
#define Kernel0_Unlock()	SYSTEM_lock--; if (SYSTEM_interrupted && SYSTEM_lock == 0) __HALT(-9)
#define Kernel0_allocated()	SYSTEM_allocated
#define Kernel0_free(adr)	(void)free(adr)
#define Kernel0_getcwd(cwd, cwd__len)	getcwd(cwd, cwd__len)
#define Kernel0_heapsize()	SYSTEM_heapsize
#include "setjmp.h"
#include "time.h"
#define Kernel0_localtime(clock)	(Kernel0_RealTime)localtime(clock)
#define Kernel0_malloc(size)	(LONGINT)malloc(size)
#define Kernel0_siglongjmp(env, env__typ, val)	siglongjmp(env, val)
#define Kernel0_sigsetjmp(env, env__typ, savemask)	__sigsetjmp(env, savemask)

void Kernel0_GetClock (LONGINT *t, LONGINT *d)
{
	Unix_Timeval tv;
	Unix_Timezone tz;
	Kernel0_RealTime time = NIL;
	LONGINT l;
	l = Unix_Gettimeofday(&tv, Unix_Timeval__typ, &tz, Unix_Timezone__typ);
	time = Kernel0_localtime(&tv.sec);
	*t = (time->sec + __ASHL(time->min, 6)) + __ASHL(time->hour, 12);
	*d = (time->mday + __ASHL(time->mon + 1, 5)) + __ASHL(__MOD(time->year, 100), 9);
}

void Kernel0_SetClock (LONGINT t, LONGINT d)
{
	CHAR err[25];
	__MOVE("not yet implemented", err, 20);
	__HALT(99);
}

LONGINT Kernel0_Time (void)
{
	Unix_Timeval timeval;
	Unix_Timezone timezone;
	LONGINT l;
	l = Unix_Gettimeofday(&timeval, Unix_Timeval__typ, &timezone, Unix_Timezone__typ);
	return __MOD((__DIV(timeval.usec, 1000) + timeval.sec * 1000) - Kernel0_timeStart, 2147483647);
}

void Kernel0_Select (LONGINT delay)
{
	Unix_FdSet rs, ws, xs;
	LONGINT n;
	Unix_Timeval tv;
	__MOVE(Kernel0_readSet, rs, 64);
	n = 0;
	while (n <= 7) {
		ws[__X(n, 8)] = 0x0;
		xs[__X(n, 8)] = 0x0;
		Kernel0_readySet[__X(n, 8)] = 0x0;
		n += 1;
	}
	if (delay < 0) {
		delay = 0;
	}
	tv.sec = __DIV(delay, 1000);
	tv.usec = __MOD(delay, 1000) * 1000;
	n = Unix_Select(256, rs, ws, xs, &tv, Unix_Timeval__typ);
	if (n >= 0) {
		__MOVE(rs, Kernel0_readySet, 64);
	}
}

void Kernel0_InstallTermHandler (void (*p)(void))
{
}

LONGINT Kernel0_LargestAvailable (void)
{
	return 9223372036854775807;
}

static void Kernel0_Halt (LONGINT n)
{
	LONGINT res;
	res = Unix_Kill(Unix_Getpid(), 4);
}

static void Kernel0_EndianTest (void)
{
	LONGINT i;
	INTEGER dmy;
	dmy = 1;
	i = (LONGINT)&dmy;
	__GET(i, Kernel0_littleEndian, BOOLEAN);
}

__TDESC(Kernel0_TimeDesc, 1, 0) = {__TDFLDS("TimeDesc", 80), {-8}};

export void *Kernel0__init(void)
{
	__DEFMOD;
	__IMPORT(Args);
	__IMPORT(Strings);
	__IMPORT(Unix);
	__IMPORT(version);
	__REGMOD("Kernel0", 0);
	__INITYP(Kernel0_TimeDesc, Kernel0_TimeDesc, 0);
/* BEGIN */
	Kernel0_EndianTest();
	Kernel0_SetHalt(Kernel0_Halt);
	Kernel0_CWD[0] = 0x00;
	__MOVE(".", Kernel0_OBERON, 2);
	Kernel0_LIB[0] = 0x00;
	Kernel0_MODULES[0] = 0x00;
	Kernel0_getcwd((void*)Kernel0_CWD, 256);
	Args_GetEnv((CHAR*)"MODULES", (LONGINT)8, (void*)Kernel0_MODULES, 1024);
	Args_GetEnv((CHAR*)"OBERON", (LONGINT)7, (void*)Kernel0_OBERON, 1024);
	Strings_Append((CHAR*)":.:", (LONGINT)4, (void*)Kernel0_OBERON, 1024);
	Strings_Append(Kernel0_MODULES, 1024, (void*)Kernel0_OBERON, 1024);
	Strings_Append((CHAR*)":", (LONGINT)2, (void*)Kernel0_OBERON, 1024);
	Strings_Append(version_prefix, 256, (void*)Kernel0_OBERON, 1024);
	Strings_Append((CHAR*)"/lib/voc/sym:", (LONGINT)14, (void*)Kernel0_OBERON, 1024);
	Args_GetEnv((CHAR*)"OBERON_LIB", (LONGINT)11, (void*)Kernel0_LIB, 256);
	Kernel0_TimeUnit = 1000;
	Kernel0_timeStart = 0;
	Kernel0_timeStart = Kernel0_Time();
	__ENDMOD;
}
