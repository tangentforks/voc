/* voc  1.0  [2013/09/23] xtspkaPS */
#include "SYSTEM.h"
#include "Args.h"
#include "Console.h"
#include "Strings.h"
#include "Unix.h"
#include "version.h"


static CHAR extTools_incPath0[1023], extTools_incPath1[1023], extTools_ccOpt[1023], extTools_ccString[1023], extTools_CFLAGS[1023], extTools_tmp0[1023], extTools_tmp1[1023];


export void extTools_Assemble (CHAR *m, LONGINT m__len);
export void extTools_LinkMain (CHAR *m, LONGINT m__len, BOOLEAN statically, CHAR *additionalopts, LONGINT additionalopts__len);


void extTools_Assemble (CHAR *m, LONGINT m__len)
{
	CHAR cmd[1023];
	CHAR cc[1023];
	CHAR ext[5];
	__DUP(m, m__len, CHAR);
	__COPY(extTools_ccString, cc, 1023);
	Strings_Append((CHAR*)" -c ", (LONGINT)5, (void*)cc, 1023);
	__COPY(cc, cmd, 1023);
	Strings_Append((CHAR*)" ", (LONGINT)2, (void*)cmd, 1023);
	Strings_Append(extTools_ccOpt, 1023, (void*)cmd, 1023);
	__MOVE(".c", ext, 3);
	Strings_Append(ext, 5, (void*)m, m__len);
	Strings_Append(m, m__len, (void*)cmd, 1023);
	Unix_system(cmd, 1023);
	__DEL(m);
}

void extTools_LinkMain (CHAR *m, LONGINT m__len, BOOLEAN statically, CHAR *additionalopts, LONGINT additionalopts__len)
{
	CHAR lpath[1023];
	CHAR cc[1023];
	CHAR ccopt[1023];
	CHAR cmd[1023];
	CHAR ext[5];
	__DUP(additionalopts, additionalopts__len, CHAR);
	cmd[0] = 0x00;
	cc[0] = 0x00;
	__MOVE(".c", ext, 3);
	__COPY(extTools_ccString, cc, 1023);
	__COPY(cc, cmd, 1023);
	Strings_Append((CHAR*)" ", (LONGINT)2, (void*)cmd, 1023);
	Strings_Append(m, m__len, (void*)cmd, 1023);
	Strings_Append(ext, 5, (void*)cmd, 1023);
	Strings_Append(additionalopts, additionalopts__len, (void*)cmd, 1023);
	if (statically) {
		Strings_Append((CHAR*)" -static ", (LONGINT)10, (void*)cmd, 1023);
	}
	Strings_Append((CHAR*)" -o ", (LONGINT)5, (void*)cmd, 1023);
	Strings_Append(m, m__len, (void*)cmd, 1023);
	Strings_Append((CHAR*)" ", (LONGINT)2, (void*)cmd, 1023);
	Strings_Append((CHAR*)" -lVishapOberon -L. -L", (LONGINT)23, (void*)extTools_ccOpt, 1023);
	Strings_Append(version_prefix, 256, (void*)extTools_ccOpt, 1023);
	Strings_Append((CHAR*)"/lib ", (LONGINT)6, (void*)extTools_ccOpt, 1023);
	Strings_Append(extTools_ccOpt, 1023, (void*)cmd, 1023);
	Console_Ln();
	Console_String(cmd, 1023);
	Console_Ln();
	Unix_system(cmd, 1023);
	__DEL(additionalopts);
}


export void *extTools__init(void)
{
	__DEFMOD;
	__IMPORT(Args);
	__IMPORT(Console);
	__IMPORT(Strings);
	__IMPORT(Unix);
	__IMPORT(version);
	__REGMOD("extTools", 0);
/* BEGIN */
	__MOVE("src/lib/system/linux/", extTools_incPath0, 22);
	Strings_Append((CHAR*)"gcc", (LONGINT)4, (void*)extTools_incPath0, 1023);
	__MOVE("lib/voc/obj ", extTools_incPath1, 13);
	__MOVE(" -fPIC -g ", extTools_ccOpt, 11);
	__COPY("-I ", extTools_tmp1, 1023);
	Strings_Append(version_prefix, 256, (void*)extTools_tmp1, 1023);
	Strings_Append((CHAR*)"/", (LONGINT)2, (void*)extTools_tmp1, 1023);
	Strings_Append(extTools_incPath0, 1023, (void*)extTools_tmp1, 1023);
	Strings_Append((CHAR*)"/", (LONGINT)2, (void*)extTools_tmp1, 1023);
	Strings_Append(version_arch, 256, (void*)extTools_tmp1, 1023);
	Strings_Append((CHAR*)" -I ", (LONGINT)5, (void*)extTools_tmp1, 1023);
	Strings_Append(version_prefix, 256, (void*)extTools_tmp1, 1023);
	Strings_Append((CHAR*)"/", (LONGINT)2, (void*)extTools_tmp1, 1023);
	Strings_Append(extTools_incPath1, 1023, (void*)extTools_tmp1, 1023);
	Strings_Append(extTools_tmp1, 1023, (void*)extTools_ccOpt, 1023);
	Args_GetEnv((CHAR*)"CFLAGS", (LONGINT)7, (void*)extTools_CFLAGS, 1023);
	Strings_Append(extTools_CFLAGS, 1023, (void*)extTools_ccOpt, 1023);
	Strings_Append((CHAR*)" ", (LONGINT)2, (void*)extTools_ccOpt, 1023);
	__MOVE("gcc", extTools_ccString, 4);
	Strings_Append((CHAR*)" ", (LONGINT)2, (void*)extTools_ccString, 1023);
	__ENDMOD;
}
