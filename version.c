/* voc  1.0  [2013/09/23] xtspkaPS */
#include "SYSTEM.h"
#include "Strings.h"
#include "architecture.h"
#include "prf.h"


export CHAR version_arch[256], version_version[256], version_date[256], version_versionLong[256], version_prefix0[256], version_prefix[256];
export INTEGER version_defaultTarget;





export void *version__init(void)
{
	__DEFMOD;
	__IMPORT(Strings);
	__IMPORT(architecture);
	__IMPORT(prf);
	__REGMOD("version", 0);
/* BEGIN */
	__MOVE("x86_64", version_arch, 7);
	__MOVE(" [2013/09/23]", version_date, 14);
	__MOVE("1.0", version_version, 4);
	version_versionLong[0] = 0x00;
	__COPY(version_version, version_versionLong, 256);
	Strings_Append((CHAR*)" ", (LONGINT)2, (void*)version_versionLong, 256);
	Strings_Append(version_date, 256, (void*)version_versionLong, 256);
	version_prefix[0] = 0x00;
	__COPY("/opt", version_prefix0, 256);
	__COPY(version_prefix0, version_prefix, 256);
	Strings_Append((CHAR*)"/voc-", (LONGINT)6, (void*)version_prefix, 256);
	Strings_Append(version_version, 256, (void*)version_prefix, 256);
	if (__STRCMP(version_arch, "x86_64") == 0) {
		version_defaultTarget = 1;
	} else if (__STRCMP(version_arch, "x86") == 0) {
		version_defaultTarget = 0;
	} else if (__STRCMP(version_arch, "armv6j") == 0) {
		version_defaultTarget = 2;
	} else if (__STRCMP(version_arch, "armv6j_hardfp") == 0) {
		version_defaultTarget = 3;
	} else if (__STRCMP(version_arch, "armv7a_hardfp") == 0) {
		version_defaultTarget = 4;
	} else if (__STRCMP(version_arch, "powerpc") == 0) {
		version_defaultTarget = 5;
	} else {
		version_defaultTarget = 1;
	}
	__ENDMOD;
}
