/* voc  1.0  [2013/09/23] xtspkaPS */
#include "SYSTEM.h"
#include "Args.h"
#include "Console.h"
#include "Files0.h"
#include "Texts0.h"
#include "errors.h"
#include "version.h"
#include "vt100.h"

typedef
	CHAR OPM_FileName[32];


static CHAR OPM_SourceFileName[256];
export INTEGER OPM_ByteSize, OPM_CharSize, OPM_BoolSize, OPM_SIntSize, OPM_IntSize, OPM_LIntSize, OPM_SetSize, OPM_RealSize, OPM_LRealSize, OPM_PointerSize, OPM_ProcSize, OPM_RecSize, OPM_CharAlign, OPM_BoolAlign, OPM_SIntAlign, OPM_IntAlign, OPM_LIntAlign, OPM_SetAlign, OPM_RealAlign, OPM_LRealAlign, OPM_PointerAlign, OPM_ProcAlign, OPM_RecAlign, OPM_ByteOrder, OPM_BitOrder, OPM_MaxSet;
export LONGINT OPM_MinSInt, OPM_MinInt, OPM_MinLInt, OPM_MaxSInt, OPM_MaxInt, OPM_MaxLInt, OPM_MaxIndex;
export LONGREAL OPM_MinReal, OPM_MaxReal, OPM_MinLReal, OPM_MaxLReal;
export BOOLEAN OPM_noerr;
export LONGINT OPM_curpos, OPM_errpos, OPM_breakpc;
export INTEGER OPM_currFile, OPM_level, OPM_pc, OPM_entno;
export CHAR OPM_modName[32];
export CHAR OPM_objname[64];
export SET OPM_opt, OPM_glbopt;
static LONGINT OPM_lasterrpos;
static Texts0_Reader OPM_inR;
static Texts0_Text OPM_Log;
static Texts0_Writer OPM_W;
static Files0_Rider OPM_oldSF, OPM_newSF;
static Files0_Rider OPM_R[3];
static Files0_File OPM_oldSFile, OPM_newSFile, OPM_HFile, OPM_BFile, OPM_HIFile;
static INTEGER OPM_S;
static BOOLEAN OPM_stop, OPM_useLineNo, OPM_useParFile;
export BOOLEAN OPM_dontAsm, OPM_dontLink, OPM_mainProg, OPM_mainLinkStat, OPM_notColorOutput;


static void OPM_Append (Files0_Rider *R, LONGINT *R__typ, Files0_File F);
export void OPM_CloseFiles (void);
export void OPM_CloseOldSym (void);
export void OPM_DeleteNewSym (void);
export void OPM_FPrint (LONGINT *fp, LONGINT val);
export void OPM_FPrintLReal (LONGINT *fp, LONGREAL lr);
export void OPM_FPrintReal (LONGINT *fp, REAL real);
export void OPM_FPrintSet (LONGINT *fp, SET set);
export void OPM_Get (CHAR *ch);
static void OPM_GetProperties (void);
static void OPM_GetProperty (Texts0_Scanner *S, LONGINT *S__typ, CHAR *name, LONGINT name__len, INTEGER *size, INTEGER *align);
export void OPM_Init (BOOLEAN *done, CHAR *mname, LONGINT mname__len);
export void OPM_InitOptions (void);
static void OPM_LogErrMsg (INTEGER n);
export void OPM_LogW (CHAR ch);
export void OPM_LogWLn (void);
export void OPM_LogWNum (LONGINT i, LONGINT len);
export void OPM_LogWStr (CHAR *s, LONGINT s__len);
static void OPM_MakeFileName (CHAR *name, LONGINT name__len, CHAR *FName, LONGINT FName__len, CHAR *ext, LONGINT ext__len);
export void OPM_Mark (INTEGER n, LONGINT pos);
export void OPM_NewSym (CHAR *modName, LONGINT modName__len);
export void OPM_OldSym (CHAR *modName, LONGINT modName__len, BOOLEAN *done);
export void OPM_OpenFiles (CHAR *moduleName, LONGINT moduleName__len);
export void OPM_OpenPar (void);
export void OPM_PromoteIntConstToLInt (void);
export void OPM_RegisterNewSym (void);
static void OPM_ScanOptions (CHAR *s, LONGINT s__len, SET *opt);
static void OPM_ShowLine (LONGINT pos);
static void OPM_ShowLineErr (LONGINT linenum, LONGINT posnum);
export void OPM_SymRCh (CHAR *ch);
export LONGINT OPM_SymRInt (void);
export void OPM_SymRLReal (LONGREAL *lr);
export void OPM_SymRReal (REAL *r);
export void OPM_SymRSet (SET *s);
export void OPM_SymWCh (CHAR ch);
export void OPM_SymWInt (LONGINT i);
export void OPM_SymWLReal (LONGREAL lr);
export void OPM_SymWReal (REAL r);
export void OPM_SymWSet (SET s);
export void OPM_Write (CHAR ch);
export void OPM_WriteHex (LONGINT i);
export void OPM_WriteInt (LONGINT i);
export void OPM_WriteLn (void);
export void OPM_WriteReal (LONGREAL r, CHAR suffx);
export void OPM_WriteString (CHAR *s, LONGINT s__len);
export void OPM_WriteStringVar (CHAR *s, LONGINT s__len);
export BOOLEAN OPM_eofSF (void);
export void OPM_err (INTEGER n);
static LONGINT OPM_power0 (INTEGER i, INTEGER j);


void OPM_LogW (CHAR ch)
{
	Console_Char(ch);
}

void OPM_LogWStr (CHAR *s, LONGINT s__len)
{
	__DUP(s, s__len, CHAR);
	Console_String(s, s__len);
	__DEL(s);
}

void OPM_LogWNum (LONGINT i, LONGINT len)
{
	Console_Int(i, len);
}

void OPM_LogWLn (void)
{
	Console_Ln();
}

static void OPM_ScanOptions (CHAR *s, LONGINT s__len, SET *opt)
{
	INTEGER i;
	i = 1;
	while (s[__X(i, s__len)] != 0x00) {
		switch (s[__X(i, s__len)]) {
			case 'e': 
				*opt = *opt ^ 0x0200;
				break;
			case 's': 
				*opt = *opt ^ 0x10;
				break;
			case 'm': 
				*opt = *opt ^ 0x0400;
				break;
			case 'x': 
				*opt = *opt ^ 0x01;
				break;
			case 'v': 
				*opt = *opt ^ 0x02;
				break;
			case 'r': 
				*opt = *opt ^ 0x04;
				break;
			case 't': 
				*opt = *opt ^ 0x08;
				break;
			case 'a': 
				*opt = *opt ^ 0x80;
				break;
			case 'k': 
				*opt = *opt ^ 0x40;
				break;
			case 'p': 
				*opt = *opt ^ 0x20;
				break;
			case 'i': 
				*opt = *opt ^ 0x0100;
				break;
			case 'l': 
				*opt = *opt ^ 0x0800;
				break;
			case 'P': 
				*opt = *opt ^ 0x1000;
				break;
			case 'S': 
				*opt = *opt ^ 0x2000;
				break;
			case 'c': 
				*opt = *opt ^ 0x4000;
				break;
			case 'M': 
				*opt = *opt ^ 0x8000;
				break;
			case 'f': 
				*opt = *opt ^ 0x010000;
				break;
			default: 
				OPM_LogWStr((CHAR*)"  warning: option ", (LONGINT)19);
				OPM_LogW('-');
				OPM_LogW(s[__X(i, s__len)]);
				OPM_LogWStr((CHAR*)" ignored", (LONGINT)9);
				OPM_LogWLn();
				break;
		}
		i += 1;
	}
}

void OPM_OpenPar (void)
{
	CHAR s[256];
	if (Args_argc == 1) {
		OPM_stop = 1;
		Console_Ln();
		Console_String((CHAR*)"voc - Vishap Oberon-2 compiler ", (LONGINT)32);
		Console_String(version_version, 256);
		Console_String((CHAR*)" ", (LONGINT)2);
		Console_String(version_date, 256);
		Console_String((CHAR*)" for ", (LONGINT)6);
		Console_String(version_arch, 256);
		Console_Ln();
		Console_String((CHAR*)"based on Ofront by Software Templ OEG", (LONGINT)38);
		Console_Ln();
		Console_String((CHAR*)"continued by Norayr Chilingarian and others", (LONGINT)44);
		Console_Ln();
		Console_Ln();
		Console_String((CHAR*)"  command = \"voc\" options {file options}.", (LONGINT)42);
		Console_Ln();
		Console_String((CHAR*)"  options = [\"-\" {option} ].", (LONGINT)29);
		Console_Ln();
		Console_String((CHAR*)"  option  = \"m\" | \"M\" | \"s\" | \"e\" | \"i\" | \"l\" | \"k\" | \"r\" | \"x\" | \"a\" | \"p\" | \"t\" | \"P\" | \"S\" | \"c\" | \"f\" .", (LONGINT)108);
		Console_Ln();
		Console_Ln();
		Console_String((CHAR*)" m      - generate code for main module", (LONGINT)40);
		Console_Ln();
		Console_String((CHAR*)" M      - generate code for main module and link object statically", (LONGINT)67);
		Console_Ln();
		Console_String((CHAR*)" s      - generate new symbol file", (LONGINT)35);
		Console_Ln();
		Console_String((CHAR*)" e      - allow extending the module interface", (LONGINT)47);
		Console_Ln();
		Console_String((CHAR*)" i      - include header and body prefix files (c0)", (LONGINT)52);
		Console_Ln();
		Console_String((CHAR*)" l      - use line numbers", (LONGINT)27);
		Console_Ln();
		Console_String((CHAR*)" r      - check value ranges", (LONGINT)29);
		Console_Ln();
		Console_String((CHAR*)" x      - turn off array indices check", (LONGINT)39);
		Console_Ln();
		Console_String((CHAR*)" a      - don\'t check ASSERTs at runtime, use this option in tested production code", (LONGINT)84);
		Console_Ln();
		Console_String((CHAR*)" p      - turn off automatic pointer initialization", (LONGINT)52);
		Console_Ln();
		Console_String((CHAR*)" t      - don\'t check type guards (use in rare cases such as low-level modules where every cycle counts)", (LONGINT)105);
		Console_Ln();
		Console_String((CHAR*)" P      - use .par file", (LONGINT)24);
		Console_Ln();
		Console_String((CHAR*)" S      - don\'t call external assembler/compiler, only generate the asm/C code", (LONGINT)79);
		Console_Ln();
		Console_String((CHAR*)" c      - don\'t call linker", (LONGINT)28);
		Console_Ln();
		Console_String((CHAR*)" f      - don\'t use color output", (LONGINT)33);
		Console_Ln();
		Console_Ln();
	} else {
		OPM_glbopt = 0xe9;
		OPM_S = 1;
		s[0] = 0x00;
		Args_Get(1, (void*)s, 256);
		OPM_stop = 0;
		while (s[0] == '-') {
			OPM_ScanOptions((void*)s, 256, &OPM_glbopt);
			OPM_S += 1;
			s[0] = 0x00;
			Args_Get(OPM_S, (void*)s, 256);
		}
		if (__IN(11, OPM_opt)) {
			OPM_useLineNo = 1;
			OPM_curpos = 256;
			OPM_errpos = OPM_curpos;
			OPM_lasterrpos = OPM_curpos - 10;
		} else {
			OPM_useLineNo = 0;
		}
		if (__IN(12, OPM_glbopt)) {
			OPM_useParFile = 1;
		} else {
			OPM_useParFile = 0;
		}
		if (__IN(13, OPM_glbopt)) {
			OPM_dontAsm = 1;
		} else {
			OPM_dontAsm = 0;
		}
		if (__IN(14, OPM_glbopt)) {
			OPM_dontLink = 1;
		} else {
			OPM_dontLink = 0;
		}
		if (__IN(10, OPM_glbopt)) {
			OPM_mainProg = 1;
		} else {
			OPM_mainProg = 0;
		}
		if (__IN(15, OPM_glbopt)) {
			OPM_glbopt |= __SETOF(10);
			OPM_mainLinkStat = 1;
		} else {
			OPM_mainLinkStat = 0;
		}
		if (__IN(16, OPM_glbopt)) {
			OPM_notColorOutput = 1;
		} else {
			OPM_notColorOutput = 0;
		}
		OPM_GetProperties();
	}
}

void OPM_InitOptions (void)
{
	CHAR s[256];
	OPM_opt = OPM_glbopt;
	s[0] = 0x00;
	Args_Get(OPM_S, (void*)s, 256);
	while (s[0] == '-') {
		OPM_ScanOptions((void*)s, 256, &OPM_opt);
		OPM_S += 1;
		s[0] = 0x00;
		Args_Get(OPM_S, (void*)s, 256);
	}
	if (__IN(11, OPM_opt)) {
		OPM_useLineNo = 1;
		OPM_curpos = 256;
		OPM_errpos = OPM_curpos;
		OPM_lasterrpos = OPM_curpos - 10;
	} else {
		OPM_useLineNo = 0;
	}
	if (__IN(12, OPM_opt)) {
		OPM_useParFile = 1;
	} else {
		OPM_useParFile = 0;
	}
	if (__IN(13, OPM_opt)) {
		OPM_dontAsm = 1;
	} else {
		OPM_dontAsm = 0;
	}
	if (__IN(14, OPM_opt)) {
		OPM_dontLink = 1;
	} else {
		OPM_dontLink = 0;
	}
	if (__IN(10, OPM_opt)) {
		OPM_mainProg = 1;
	} else {
		OPM_mainProg = 0;
	}
	if (__IN(15, OPM_opt)) {
		OPM_glbopt |= __SETOF(10);
		OPM_mainLinkStat = 1;
	} else {
		OPM_mainLinkStat = 0;
	}
}

void OPM_Init (BOOLEAN *done, CHAR *mname, LONGINT mname__len)
{
	Texts0_Text T = NIL;
	LONGINT beg, end, time;
	CHAR s[256];
	*done = 0;
	OPM_curpos = 0;
	if (OPM_stop || (LONGINT)OPM_S >= Args_argc) {
		return;
	}
	s[0] = 0x00;
	Args_Get(OPM_S, (void*)s, 256);
	__NEW(T, Texts0_TextDesc);
	Texts0_Open(T, s, 256);
	OPM_LogWStr(s, 256);
	__COPY(s, mname, mname__len);
	__COPY(s, OPM_SourceFileName, 256);
	if (T->len == 0) {
		OPM_LogWStr((CHAR*)" not found", (LONGINT)11);
		OPM_LogWLn();
	} else {
		Texts0_OpenReader(&OPM_inR, Texts0_Reader__typ, T, 0);
		OPM_LogWStr((CHAR*)"  translating", (LONGINT)14);
		*done = 1;
	}
	OPM_S += 1;
	OPM_level = 0;
	OPM_noerr = 1;
	OPM_errpos = OPM_curpos;
	OPM_lasterrpos = OPM_curpos - 10;
}

void OPM_Get (CHAR *ch)
{
	Texts0_Read(&OPM_inR, Texts0_Reader__typ, &*ch);
	if (OPM_useLineNo) {
		if (*ch == 0x0d) {
			OPM_curpos = __ASHL(__ASHR(OPM_curpos, 8) + 1, 8);
		} else if (__MASK(OPM_curpos, -256) != 255) {
			OPM_curpos += 1;
		}
	} else {
		OPM_curpos += 1;
	}
	if ((*ch < 0x09 && !OPM_inR.eot)) {
		*ch = ' ';
	}
}

static void OPM_MakeFileName (CHAR *name, LONGINT name__len, CHAR *FName, LONGINT FName__len, CHAR *ext, LONGINT ext__len)
{
	INTEGER i, j;
	CHAR ch;
	__DUP(ext, ext__len, CHAR);
	i = 0;
	for (;;) {
		ch = name[__X(i, name__len)];
		if (ch == 0x00) {
			break;
		}
		FName[__X(i, FName__len)] = ch;
		i += 1;
	}
	j = 0;
	do {
		ch = ext[__X(j, ext__len)];
		FName[__X(i, FName__len)] = ch;
		i += 1;
		j += 1;
	} while (!(ch == 0x00));
	__DEL(ext);
}

static void OPM_LogErrMsg (INTEGER n)
{
	Texts0_Scanner S;
	Texts0_Text T = NIL;
	CHAR ch;
	INTEGER i;
	CHAR buf[1024];
	if (n >= 0) {
		if (!OPM_notColorOutput) {
			vt100_SetAttr((CHAR*)"31m", (LONGINT)4);
		}
		OPM_LogWStr((CHAR*)"  err ", (LONGINT)7);
		if (!OPM_notColorOutput) {
			vt100_SetAttr((CHAR*)"0m", (LONGINT)3);
		}
	} else {
		if (!OPM_notColorOutput) {
			vt100_SetAttr((CHAR*)"35m", (LONGINT)4);
		}
		OPM_LogWStr((CHAR*)"  warning ", (LONGINT)11);
		n = -n;
		if (!OPM_notColorOutput) {
			vt100_SetAttr((CHAR*)"0m", (LONGINT)3);
		}
	}
	OPM_LogWNum(n, 1);
	OPM_LogWStr((CHAR*)"  ", (LONGINT)3);
	OPM_LogWStr(errors_errors[__X(n, 350)], 128);
}

static void OPM_ShowLine (LONGINT pos)
{
	Files0_File f = NIL;
	Files0_Rider r;
	LONGINT newpos, localpos, delta;
	CHAR line[1023];
	INTEGER i;
	CHAR ch;
	localpos = pos;
	f = Files0_Old(OPM_SourceFileName, 256);
	do {
		localpos -= 1;
		if (localpos < 0) {
			localpos = 0;
		}
		Files0_Set(&r, Files0_Rider__typ, f, localpos);
		Files0_Read(&r, Files0_Rider__typ, (void*)&ch);
	} while (!((localpos < 1 || (int)ch >= 32) || (int)ch == 9));
	newpos = localpos;
	do {
		localpos -= 1;
		if (localpos < 0) {
			newpos = 0;
		}
		Files0_Set(&r, Files0_Rider__typ, f, localpos);
		Files0_Read(&r, Files0_Rider__typ, (void*)&ch);
	} while (!(localpos < 1 || ((int)ch < 32 && (int)ch != 9)));
	delta = (newpos - localpos) - 1;
	if (delta < 1) {
		delta = 1;
	}
	do {
		localpos += 1;
		Files0_Set(&r, Files0_Rider__typ, f, localpos);
		Files0_Read(&r, Files0_Rider__typ, (void*)&ch);
	} while (!((int)ch >= 32 || (int)ch == 9));
	i = 0;
	do {
		Files0_Set(&r, Files0_Rider__typ, f, localpos);
		Files0_Read(&r, Files0_Rider__typ, (void*)&ch);
		if ((int)ch == 9) {
			ch = ' ';
		}
		line[__X(i, 1023)] = ch;
		localpos += 1;
		i += 1;
	} while (!((r.eof || i >= 1022) || ((int)ch < 32 && (int)ch != 9)));
	line[__X(i, 1023)] = 0x00;
	Console_Ln();
	Console_Ln();
	Console_String((CHAR*)"  ", (LONGINT)3);
	Console_String(line, 1023);
	i = 0;
	Console_String((CHAR*)"  ", (LONGINT)3);
	do {
		Console_Char(' ');
		i += 1;
	} while (!((LONGINT)i >= delta));
	if (!OPM_notColorOutput) {
		vt100_SetAttr((CHAR*)"32m", (LONGINT)4);
	}
	Console_Char('^');
	if (!OPM_notColorOutput) {
		vt100_SetAttr((CHAR*)"0m", (LONGINT)3);
	}
	Files0_Close(f);
}

static void OPM_ShowLineErr (LONGINT linenum, LONGINT posnum)
{
	Files0_File f = NIL;
	Files0_Rider r;
	CHAR line[1023];
	LONGINT i, j;
	CHAR ch;
	f = Files0_Old(OPM_SourceFileName, 256);
	Files0_Set(&r, Files0_Rider__typ, f, 0);
	do {
		Files0_Read(&r, Files0_Rider__typ, (void*)&ch);
	} while (!((int)ch > 31));
	i = 0;
	j = 0;
	do {
		if ((int)ch > 31 || (int)ch == 9) {
			if ((int)ch == 9) {
				ch = ' ';
			}
			line[__X(i, 1023)] = ch;
			i += 1;
			line[__X(i + 1, 1023)] = 0x00;
		} else {
			j += 1;
			i = 0;
		}
		Files0_Read(&r, Files0_Rider__typ, (void*)&ch);
	} while (!(j >= linenum || i >= 1022));
	Console_Ln();
	Console_String((CHAR*)"  ", (LONGINT)3);
	Console_String(line, 1023);
	Console_Ln();
	i = 0;
	while (i < posnum - 1) {
		Console_Char(' ');
		i += 1;
	}
	Console_String((CHAR*)"  ", (LONGINT)3);
	if (!OPM_notColorOutput) {
		vt100_SetAttr((CHAR*)"32m", (LONGINT)4);
	}
	Console_Char('^');
	Console_Ln();
	if (!OPM_notColorOutput) {
		vt100_SetAttr((CHAR*)"0m", (LONGINT)3);
	}
	Files0_Close(f);
}

void OPM_Mark (INTEGER n, LONGINT pos)
{
	LONGINT linenumber, posnumber;
	if (pos == -1) {
		pos = 0;
	}
	linenumber = __ASHR(pos, 8);
	posnumber = __MASK(pos, -256);
	if (OPM_useLineNo) {
		if (n >= 0) {
			OPM_noerr = 0;
			if (pos < OPM_lasterrpos || OPM_lasterrpos + 9 < pos) {
				OPM_lasterrpos = pos;
				OPM_LogWLn();
				OPM_LogWStr((CHAR*)"  ", (LONGINT)3);
				if (n < 249) {
					OPM_ShowLineErr(linenumber, posnumber);
					OPM_LogWStr((CHAR*)"  line ", (LONGINT)8);
					OPM_LogWNum(linenumber, 1);
					OPM_LogWStr((CHAR*)"  pos ", (LONGINT)7);
					OPM_LogWNum(posnumber, 1);
					OPM_LogErrMsg(n);
				} else if (n == 255) {
					OPM_ShowLineErr(linenumber, posnumber);
					OPM_LogWStr((CHAR*)"  line ", (LONGINT)8);
					OPM_LogWNum(linenumber, 1);
					OPM_LogWStr((CHAR*)"  pos ", (LONGINT)7);
					OPM_LogWNum(posnumber, 1);
					OPM_LogWStr((CHAR*)"  pc ", (LONGINT)6);
					OPM_LogWNum(OPM_breakpc, 1);
				} else if (n == 254) {
					OPM_LogWStr((CHAR*)"pc not found", (LONGINT)13);
				} else {
					OPM_LogWStr(OPM_objname, 64);
					if (n == 253) {
						OPM_LogWStr((CHAR*)" is new, compile with option e", (LONGINT)31);
					} else if (n == 252) {
						OPM_LogWStr((CHAR*)" is redefined, compile with option s", (LONGINT)37);
					} else if (n == 251) {
						OPM_LogWStr((CHAR*)" is redefined (private part only), compile with option s", (LONGINT)57);
					} else if (n == 250) {
						OPM_LogWStr((CHAR*)" is no longer visible, compile with option s", (LONGINT)45);
					} else if (n == 249) {
						OPM_LogWStr((CHAR*)" is not consistently imported, recompile imports", (LONGINT)49);
					}
				}
			}
		} else {
			OPM_ShowLineErr(linenumber, posnumber);
			if (pos >= 0) {
				OPM_LogWLn();
				OPM_LogWStr((CHAR*)"  line ", (LONGINT)8);
				OPM_LogWNum(__ASHR(pos, 8), 1);
				OPM_LogWStr((CHAR*)"  pos ", (LONGINT)7);
				OPM_LogWNum(__MASK(pos, -256), 1);
			}
			OPM_LogErrMsg(n);
			if (pos < 0) {
				OPM_LogWLn();
			}
		}
	} else {
		if (n >= 0) {
			OPM_noerr = 0;
			if (pos < OPM_lasterrpos || OPM_lasterrpos + 9 < pos) {
				OPM_lasterrpos = pos;
				OPM_ShowLine(pos);
				OPM_LogWLn();
				OPM_LogWStr((CHAR*)"  ", (LONGINT)3);
				if (n < 249) {
					OPM_LogWStr((CHAR*)"  pos", (LONGINT)6);
					OPM_LogWNum(pos, 6);
					OPM_LogErrMsg(n);
				} else if (n == 255) {
					OPM_LogWStr((CHAR*)"pos", (LONGINT)4);
					OPM_LogWNum(pos, 6);
					OPM_LogWStr((CHAR*)"  pc ", (LONGINT)6);
					OPM_LogWNum(OPM_breakpc, 1);
				} else if (n == 254) {
					OPM_LogWStr((CHAR*)"pc not found", (LONGINT)13);
				} else {
					OPM_LogWStr(OPM_objname, 64);
					if (n == 253) {
						OPM_LogWStr((CHAR*)" is new, compile with option e", (LONGINT)31);
					} else if (n == 252) {
						OPM_LogWStr((CHAR*)" is redefined, compile with option s", (LONGINT)37);
					} else if (n == 251) {
						OPM_LogWStr((CHAR*)" is redefined (private part only), compile with option s", (LONGINT)57);
					} else if (n == 250) {
						OPM_LogWStr((CHAR*)" is no longer visible, compile with option s", (LONGINT)45);
					} else if (n == 249) {
						OPM_LogWStr((CHAR*)" is not consistently imported, recompile imports", (LONGINT)49);
					}
				}
			}
		} else {
			if (pos >= 0) {
				OPM_ShowLine(pos);
				OPM_LogWLn();
				OPM_LogWStr((CHAR*)"  pos", (LONGINT)6);
				OPM_LogWNum(pos, 6);
			}
			OPM_LogErrMsg(n);
			if (pos < 0) {
				OPM_LogWLn();
			}
		}
	}
}

void OPM_err (INTEGER n)
{
	if ((OPM_useLineNo && __MASK(OPM_errpos, -256) == 255)) {
		OPM_Mark(n, OPM_errpos + 1);
	} else {
		OPM_Mark(n, OPM_errpos);
	}
}

void OPM_FPrint (LONGINT *fp, LONGINT val)
{
	*fp = __ROTL((LONGINT)((SET)*fp ^ (SET)val), 1, LONGINT);
}

void OPM_FPrintSet (LONGINT *fp, SET set)
{
	OPM_FPrint(&*fp, (LONGINT)set);
}

void OPM_FPrintReal (LONGINT *fp, REAL real)
{
	OPM_FPrint(&*fp, __VAL(LONGINT, real));
}

void OPM_FPrintLReal (LONGINT *fp, LONGREAL lr)
{
	LONGINT l, h;
	__GET((LONGINT)&lr, l, LONGINT);
	__GET((LONGINT)&lr + 4, h, LONGINT);
	OPM_FPrint(&*fp, l);
	OPM_FPrint(&*fp, h);
}

static void OPM_GetProperty (Texts0_Scanner *S, LONGINT *S__typ, CHAR *name, LONGINT name__len, INTEGER *size, INTEGER *align)
{
	__DUP(name, name__len, CHAR);
	if (((*S).class == 1 && __STRCMP((*S).s, name) == 0)) {
		Texts0_Scan(&*S, S__typ);
		if ((*S).class == 3) {
			*size = (int)(*S).i;
			Texts0_Scan(&*S, S__typ);
		} else {
			OPM_Mark(-157, -1);
		}
		if ((*S).class == 3) {
			*align = (int)(*S).i;
			Texts0_Scan(&*S, S__typ);
		} else {
			OPM_Mark(-157, -1);
		}
	} else {
		OPM_Mark(-157, -1);
	}
	__DEL(name);
}

static LONGINT OPM_power0 (INTEGER i, INTEGER j)
{
	INTEGER k;
	LONGINT p;
	k = 1;
	p = i;
	do {
		p = p * (LONGINT)i;
		k += 1;
	} while (!(k == j));
	return p;
}

static void OPM_GetProperties (void)
{
	Texts0_Text T = NIL;
	Texts0_Scanner S;
	if (!OPM_useParFile) {
		if (version_defaultTarget == 1) {
			Console_String((CHAR*)" GNU ", (LONGINT)6);
			Console_String(version_arch, 256);
			Console_String((CHAR*)" target", (LONGINT)8);
			Console_Ln();
			OPM_ByteSize = 1;
			OPM_CharSize = 1;
			OPM_BoolSize = 1;
			OPM_SIntSize = 1;
			OPM_IntSize = 4;
			OPM_LIntSize = 8;
			OPM_SetSize = 8;
			OPM_RealSize = 4;
			OPM_LRealSize = 8;
			OPM_ProcSize = 8;
			OPM_PointerSize = 8;
			OPM_RecSize = 1;
			OPM_CharAlign = 1;
			OPM_BoolAlign = 1;
			OPM_SIntAlign = 1;
			OPM_IntAlign = 4;
			OPM_LIntAlign = 8;
			OPM_SetAlign = 8;
			OPM_RealAlign = 4;
			OPM_LRealAlign = 8;
			OPM_ProcAlign = 8;
			OPM_PointerAlign = 8;
			OPM_RecAlign = 1;
		} else if ((version_defaultTarget >= 2 && version_defaultTarget <= 4)) {
			Console_String((CHAR*)" GNU ", (LONGINT)6);
			Console_String(version_arch, 256);
			Console_String((CHAR*)" target", (LONGINT)8);
			Console_Ln();
			OPM_ByteSize = 1;
			OPM_CharSize = 1;
			OPM_BoolSize = 1;
			OPM_SIntSize = 1;
			OPM_IntSize = 2;
			OPM_LIntSize = 4;
			OPM_SetSize = 4;
			OPM_RealSize = 4;
			OPM_LRealSize = 8;
			OPM_ProcSize = 4;
			OPM_PointerSize = 4;
			OPM_RecSize = 1;
			OPM_CharAlign = 1;
			OPM_BoolAlign = 1;
			OPM_SIntAlign = 1;
			OPM_IntAlign = 2;
			OPM_LIntAlign = 4;
			OPM_SetAlign = 4;
			OPM_RealAlign = 4;
			OPM_LRealAlign = 8;
			OPM_ProcAlign = 4;
			OPM_PointerAlign = 4;
			OPM_RecAlign = 1;
		} else if (version_defaultTarget == 5) {
			Console_String((CHAR*)" GNU ", (LONGINT)6);
			Console_String(version_arch, 256);
			Console_String((CHAR*)" target", (LONGINT)8);
			Console_Ln();
			OPM_ByteSize = 1;
			OPM_CharSize = 1;
			OPM_BoolSize = 1;
			OPM_SIntSize = 1;
			OPM_IntSize = 2;
			OPM_LIntSize = 4;
			OPM_SetSize = 4;
			OPM_RealSize = 4;
			OPM_LRealSize = 8;
			OPM_ProcSize = 4;
			OPM_PointerSize = 4;
			OPM_RecSize = 1;
			OPM_CharAlign = 1;
			OPM_BoolAlign = 1;
			OPM_SIntAlign = 1;
			OPM_IntAlign = 2;
			OPM_LIntAlign = 4;
			OPM_SetAlign = 4;
			OPM_RealAlign = 4;
			OPM_LRealAlign = 8;
			OPM_ProcAlign = 4;
			OPM_PointerAlign = 4;
			OPM_RecAlign = 1;
		} else if (version_defaultTarget == 0) {
			Console_String((CHAR*)"GNU ", (LONGINT)5);
			Console_String(version_arch, 256);
			Console_String((CHAR*)" target", (LONGINT)8);
			Console_Ln();
			OPM_ByteSize = 1;
			OPM_CharSize = 1;
			OPM_BoolSize = 1;
			OPM_SIntSize = 1;
			OPM_IntSize = 2;
			OPM_LIntSize = 4;
			OPM_SetSize = 4;
			OPM_RealSize = 4;
			OPM_LRealSize = 8;
			OPM_ProcSize = 4;
			OPM_PointerSize = 4;
			OPM_RecSize = 1;
			OPM_CharAlign = 1;
			OPM_BoolAlign = 1;
			OPM_SIntAlign = 1;
			OPM_IntAlign = 2;
			OPM_LIntAlign = 4;
			OPM_SetAlign = 4;
			OPM_RealAlign = 4;
			OPM_LRealAlign = 4;
			OPM_ProcAlign = 4;
			OPM_PointerAlign = 4;
			OPM_RecAlign = 1;
		} else {
			Console_String((CHAR*)" generic target, like GNU x86 system", (LONGINT)37);
			Console_Ln();
			OPM_ByteSize = 1;
			OPM_CharSize = 1;
			OPM_BoolSize = 1;
			OPM_SIntSize = 1;
			OPM_IntSize = 2;
			OPM_LIntSize = 4;
			OPM_SetSize = 4;
			OPM_RealSize = 4;
			OPM_LRealSize = 8;
			OPM_ProcSize = 4;
			OPM_PointerSize = 4;
			OPM_RecSize = 1;
			OPM_CharAlign = 1;
			OPM_BoolAlign = 1;
			OPM_SIntAlign = 1;
			OPM_IntAlign = 2;
			OPM_LIntAlign = 4;
			OPM_SetAlign = 4;
			OPM_RealAlign = 4;
			OPM_LRealAlign = 4;
			OPM_ProcAlign = 4;
			OPM_PointerAlign = 4;
			OPM_RecAlign = 1;
		}
	}
	if (OPM_useParFile) {
		Console_String((CHAR*)"loading type sizes from voc.par", (LONGINT)32);
		Console_Ln();
		__NEW(T, Texts0_TextDesc);
		Texts0_Open(T, (CHAR*)"voc.par", (LONGINT)8);
		if (T->len != 0) {
			Texts0_OpenScanner(&S, Texts0_Scanner__typ, T, 0);
			Texts0_Scan(&S, Texts0_Scanner__typ);
			OPM_GetProperty(&S, Texts0_Scanner__typ, (CHAR*)"CHAR", (LONGINT)5, &OPM_CharSize, &OPM_CharAlign);
			OPM_GetProperty(&S, Texts0_Scanner__typ, (CHAR*)"BOOLEAN", (LONGINT)8, &OPM_BoolSize, &OPM_BoolAlign);
			OPM_GetProperty(&S, Texts0_Scanner__typ, (CHAR*)"SHORTINT", (LONGINT)9, &OPM_SIntSize, &OPM_SIntAlign);
			OPM_GetProperty(&S, Texts0_Scanner__typ, (CHAR*)"INTEGER", (LONGINT)8, &OPM_IntSize, &OPM_IntAlign);
			OPM_GetProperty(&S, Texts0_Scanner__typ, (CHAR*)"LONGINT", (LONGINT)8, &OPM_LIntSize, &OPM_LIntAlign);
			OPM_GetProperty(&S, Texts0_Scanner__typ, (CHAR*)"SET", (LONGINT)4, &OPM_SetSize, &OPM_SetAlign);
			OPM_GetProperty(&S, Texts0_Scanner__typ, (CHAR*)"REAL", (LONGINT)5, &OPM_RealSize, &OPM_RealAlign);
			OPM_GetProperty(&S, Texts0_Scanner__typ, (CHAR*)"LONGREAL", (LONGINT)9, &OPM_LRealSize, &OPM_LRealAlign);
			OPM_GetProperty(&S, Texts0_Scanner__typ, (CHAR*)"PTR", (LONGINT)4, &OPM_PointerSize, &OPM_PointerAlign);
			OPM_GetProperty(&S, Texts0_Scanner__typ, (CHAR*)"PROC", (LONGINT)5, &OPM_ProcSize, &OPM_ProcAlign);
			OPM_GetProperty(&S, Texts0_Scanner__typ, (CHAR*)"RECORD", (LONGINT)7, &OPM_RecSize, &OPM_RecAlign);
			OPM_GetProperty(&S, Texts0_Scanner__typ, (CHAR*)"ENDIAN", (LONGINT)7, &OPM_ByteOrder, &OPM_BitOrder);
			OPM_ByteSize = OPM_CharSize;
		} else {
			OPM_Mark(-156, -1);
		}
	} else {
		Console_String((CHAR*)"not using voc.par file", (LONGINT)23);
		Console_Ln();
	}
	OPM_MinSInt = OPM_power0(-2, __ASHL(OPM_SIntSize, 3) - 1);
	OPM_MaxSInt = OPM_power0(2, __ASHL(OPM_SIntSize, 3) - 1) - 1;
	OPM_MinInt = OPM_power0(-2, __ASHL(OPM_IntSize, 3) - 1);
	OPM_MaxInt = OPM_power0(2, __ASHL(OPM_IntSize, 3) - 1) - 1;
	OPM_MinLInt = OPM_power0(-2, __ASHL(OPM_LIntSize, 3) - 1);
	OPM_MaxLInt = OPM_power0(2, __ASHL(OPM_LIntSize, 3) - 1) - 1;
	if (OPM_RealSize == 4) {
		OPM_MaxReal =   3.40282346000000e+038;
	} else if (OPM_RealSize == 8) {
		OPM_MaxReal =   1.79769296342094e+308;
	}
	if (OPM_LRealSize == 4) {
		OPM_MaxLReal =   3.40282346000000e+038;
	} else if (OPM_LRealSize == 8) {
		OPM_MaxLReal =   1.79769296342094e+308;
	}
	OPM_MinReal = -OPM_MaxReal;
	OPM_MinLReal = -OPM_MaxLReal;
	OPM_MaxSet = __ASHL(OPM_SetSize, 3) - 1;
	OPM_MaxIndex = OPM_MaxLInt;
}

void OPM_SymRCh (CHAR *ch)
{
	Files0_Read(&OPM_oldSF, Files0_Rider__typ, (void*)&*ch);
}

LONGINT OPM_SymRInt (void)
{
	LONGINT k;
	Files0_ReadNum(&OPM_oldSF, Files0_Rider__typ, &k);
	return k;
}

void OPM_SymRSet (SET *s)
{
	Files0_ReadNum(&OPM_oldSF, Files0_Rider__typ, (LONGINT*)&*s);
}

void OPM_SymRReal (REAL *r)
{
	Files0_ReadReal(&OPM_oldSF, Files0_Rider__typ, &*r);
}

void OPM_SymRLReal (LONGREAL *lr)
{
	Files0_ReadLReal(&OPM_oldSF, Files0_Rider__typ, &*lr);
}

void OPM_CloseOldSym (void)
{
}

void OPM_OldSym (CHAR *modName, LONGINT modName__len, BOOLEAN *done)
{
	CHAR ch;
	OPM_FileName fileName;
	OPM_MakeFileName((void*)modName, modName__len, (void*)fileName, 32, (CHAR*)".sym", (LONGINT)5);
	OPM_oldSFile = Files0_Old(fileName, 32);
	*done = OPM_oldSFile != NIL;
	if (*done) {
		Files0_Set(&OPM_oldSF, Files0_Rider__typ, OPM_oldSFile, 0);
		Files0_Read(&OPM_oldSF, Files0_Rider__typ, (void*)&ch);
		if (ch != 0xf7) {
			OPM_err(-306);
			OPM_CloseOldSym();
			*done = 0;
		}
	}
}

BOOLEAN OPM_eofSF (void)
{
	return OPM_oldSF.eof;
}

void OPM_SymWCh (CHAR ch)
{
	Files0_Write(&OPM_newSF, Files0_Rider__typ, ch);
}

void OPM_SymWInt (LONGINT i)
{
	Files0_WriteNum(&OPM_newSF, Files0_Rider__typ, i);
}

void OPM_SymWSet (SET s)
{
	Files0_WriteNum(&OPM_newSF, Files0_Rider__typ, (LONGINT)s);
}

void OPM_SymWReal (REAL r)
{
	Files0_WriteReal(&OPM_newSF, Files0_Rider__typ, r);
}

void OPM_SymWLReal (LONGREAL lr)
{
	Files0_WriteLReal(&OPM_newSF, Files0_Rider__typ, lr);
}

void OPM_RegisterNewSym (void)
{
	if (__STRCMP(OPM_modName, "SYSTEM") != 0 || __IN(10, OPM_opt)) {
		Files0_Register(OPM_newSFile);
	}
}

void OPM_DeleteNewSym (void)
{
}

void OPM_NewSym (CHAR *modName, LONGINT modName__len)
{
	OPM_FileName fileName;
	OPM_MakeFileName((void*)modName, modName__len, (void*)fileName, 32, (CHAR*)".sym", (LONGINT)5);
	OPM_newSFile = Files0_New(fileName, 32);
	if (OPM_newSFile != NIL) {
		Files0_Set(&OPM_newSF, Files0_Rider__typ, OPM_newSFile, 0);
		Files0_Write(&OPM_newSF, Files0_Rider__typ, 0xf7);
	} else {
		OPM_err(153);
	}
}

void OPM_Write (CHAR ch)
{
	Files0_Write(&OPM_R[__X(OPM_currFile, 3)], Files0_Rider__typ, ch);
}

void OPM_WriteString (CHAR *s, LONGINT s__len)
{
	INTEGER i;
	i = 0;
	while (s[__X(i, s__len)] != 0x00) {
		i += 1;
	}
	Files0_WriteBytes(&OPM_R[__X(OPM_currFile, 3)], Files0_Rider__typ, (void*)s, s__len * 1, i);
}

void OPM_WriteStringVar (CHAR *s, LONGINT s__len)
{
	INTEGER i;
	i = 0;
	while (s[__X(i, s__len)] != 0x00) {
		i += 1;
	}
	Files0_WriteBytes(&OPM_R[__X(OPM_currFile, 3)], Files0_Rider__typ, (void*)s, s__len * 1, i);
}

void OPM_WriteHex (LONGINT i)
{
	CHAR s[3];
	INTEGER digit;
	digit = __ASHR((int)i, 4);
	if (digit < 10) {
		s[0] = (CHAR)(48 + digit);
	} else {
		s[0] = (CHAR)(87 + digit);
	}
	digit = __MASK((int)i, -16);
	if (digit < 10) {
		s[1] = (CHAR)(48 + digit);
	} else {
		s[1] = (CHAR)(87 + digit);
	}
	s[2] = 0x00;
	OPM_WriteString(s, 3);
}

void OPM_WriteInt (LONGINT i)
{
	CHAR s[20];
	LONGINT i1, k;
	if (i == OPM_MinLInt) {
		OPM_Write('(');
		OPM_WriteInt(i + 1);
		OPM_WriteString((CHAR*)"-1)", (LONGINT)4);
	} else {
		i1 = __ABS(i);
		s[0] = (CHAR)(__MOD(i1, 10) + 48);
		i1 = __DIV(i1, 10);
		k = 1;
		while (i1 > 0) {
			s[__X(k, 20)] = (CHAR)(__MOD(i1, 10) + 48);
			i1 = __DIV(i1, 10);
			k += 1;
		}
		if (i < 0) {
			s[__X(k, 20)] = '-';
			k += 1;
		}
		while (k > 0) {
			k -= 1;
			OPM_Write(s[__X(k, 20)]);
		}
	}
}

void OPM_WriteReal (LONGREAL r, CHAR suffx)
{
	Texts0_Writer W;
	Texts0_Text T = NIL;
	Texts0_Reader R;
	CHAR s[32];
	CHAR ch;
	INTEGER i;
	if ((((r < OPM_MaxLInt && r > OPM_MinLInt)) && r == (__ENTIER(r)))) {
		if (suffx == 'f') {
			OPM_WriteString((CHAR*)"(REAL)", (LONGINT)7);
		} else {
			OPM_WriteString((CHAR*)"(LONGREAL)", (LONGINT)11);
		}
		OPM_WriteInt(__ENTIER(r));
	} else {
		Texts0_OpenWriter(&W, Texts0_Writer__typ);
		if (suffx == 'f') {
			Texts0_WriteLongReal(&W, Texts0_Writer__typ, r, 16);
		} else {
			Texts0_WriteLongReal(&W, Texts0_Writer__typ, r, 23);
		}
		__NEW(T, Texts0_TextDesc);
		Texts0_Open(T, (CHAR*)"", (LONGINT)1);
		Texts0_Append(T, W.buf);
		Texts0_OpenReader(&R, Texts0_Reader__typ, T, 0);
		i = 0;
		Texts0_Read(&R, Texts0_Reader__typ, &ch);
		while (ch != 0x00) {
			s[__X(i, 32)] = ch;
			i += 1;
			Texts0_Read(&R, Texts0_Reader__typ, &ch);
		}
		s[__X(i, 32)] = 0x00;
		i = 0;
		ch = s[0];
		while ((ch != 'D' && ch != 0x00)) {
			i += 1;
			ch = s[__X(i, 32)];
		}
		if (ch == 'D') {
			s[__X(i, 32)] = 'e';
		}
		OPM_WriteString(s, 32);
	}
}

void OPM_WriteLn (void)
{
	Files0_Write(&OPM_R[__X(OPM_currFile, 3)], Files0_Rider__typ, 0x0a);
}

static void OPM_Append (Files0_Rider *R, LONGINT *R__typ, Files0_File F)
{
	Files0_Rider R1;
	CHAR buffer[4096];
	if (F != NIL) {
		Files0_Set(&R1, Files0_Rider__typ, F, 0);
		Files0_ReadBytes(&R1, Files0_Rider__typ, (void*)buffer, 4096, 4096);
		while (4096 - R1.res > 0) {
			Files0_WriteBytes(&*R, R__typ, (void*)buffer, 4096, 4096 - R1.res);
			Files0_ReadBytes(&R1, Files0_Rider__typ, (void*)buffer, 4096, 4096);
		}
	}
}

void OPM_OpenFiles (CHAR *moduleName, LONGINT moduleName__len)
{
	CHAR FName[32];
	__COPY(moduleName, OPM_modName, 32);
	OPM_HFile = Files0_New((CHAR*)"", (LONGINT)1);
	if (OPM_HFile != NIL) {
		Files0_Set(&OPM_R[0], Files0_Rider__typ, OPM_HFile, 0);
	} else {
		OPM_err(153);
	}
	OPM_MakeFileName((void*)moduleName, moduleName__len, (void*)FName, 32, (CHAR*)".c", (LONGINT)3);
	OPM_BFile = Files0_New(FName, 32);
	if (OPM_BFile != NIL) {
		Files0_Set(&OPM_R[1], Files0_Rider__typ, OPM_BFile, 0);
	} else {
		OPM_err(153);
	}
	OPM_MakeFileName((void*)moduleName, moduleName__len, (void*)FName, 32, (CHAR*)".h", (LONGINT)3);
	OPM_HIFile = Files0_New(FName, 32);
	if (OPM_HIFile != NIL) {
		Files0_Set(&OPM_R[2], Files0_Rider__typ, OPM_HIFile, 0);
	} else {
		OPM_err(153);
	}
	if (__IN(8, OPM_opt)) {
		OPM_MakeFileName((void*)moduleName, moduleName__len, (void*)FName, 32, (CHAR*)".h0", (LONGINT)4);
		OPM_Append(&OPM_R[2], Files0_Rider__typ, Files0_Old(FName, 32));
		OPM_MakeFileName((void*)moduleName, moduleName__len, (void*)FName, 32, (CHAR*)".c0", (LONGINT)4);
		OPM_Append(&OPM_R[1], Files0_Rider__typ, Files0_Old(FName, 32));
	}
}

void OPM_CloseFiles (void)
{
	CHAR FName[32];
	INTEGER res;
	if (OPM_noerr) {
		OPM_LogWStr((CHAR*)"    ", (LONGINT)5);
		OPM_LogWNum(Files0_Pos(&OPM_R[1], Files0_Rider__typ), 0);
	}
	if (OPM_noerr) {
		if (__STRCMP(OPM_modName, "SYSTEM") == 0) {
			if (!__IN(10, OPM_opt)) {
				Files0_Register(OPM_BFile);
			}
		} else if (!__IN(10, OPM_opt)) {
			OPM_Append(&OPM_R[2], Files0_Rider__typ, OPM_HFile);
			Files0_Register(OPM_HIFile);
			Files0_Register(OPM_BFile);
		} else {
			OPM_MakeFileName((void*)OPM_modName, 32, (void*)FName, 32, (CHAR*)".h", (LONGINT)3);
			Files0_Delete(FName, 32, &res);
			OPM_MakeFileName((void*)OPM_modName, 32, (void*)FName, 32, (CHAR*)".sym", (LONGINT)5);
			Files0_Delete(FName, 32, &res);
			Files0_Register(OPM_BFile);
		}
	}
	OPM_HFile = NIL;
	OPM_BFile = NIL;
	OPM_HIFile = NIL;
	OPM_newSFile = NIL;
	OPM_oldSFile = NIL;
	Files0_Set(&OPM_R[0], Files0_Rider__typ, NIL, 0);
	Files0_Set(&OPM_R[1], Files0_Rider__typ, NIL, 0);
	Files0_Set(&OPM_R[2], Files0_Rider__typ, NIL, 0);
	Files0_Set(&OPM_newSF, Files0_Rider__typ, NIL, 0);
	Files0_Set(&OPM_oldSF, Files0_Rider__typ, NIL, 0);
}

void OPM_PromoteIntConstToLInt (void)
{
	if (!__IN(6, OPM_opt)) {
		OPM_Write('L');
	}
}

static void EnumPtrs(void (*P)(void*))
{
	__ENUMR(&OPM_inR, Texts0_Reader__typ, 96, 1, P);
	P(OPM_Log);
	__ENUMR(&OPM_W, Texts0_Writer__typ, 72, 1, P);
	__ENUMR(&OPM_oldSF, Files0_Rider__typ, 40, 1, P);
	__ENUMR(&OPM_newSF, Files0_Rider__typ, 40, 1, P);
	__ENUMR(OPM_R, Files0_Rider__typ, 40, 3, P);
	P(OPM_oldSFile);
	P(OPM_newSFile);
	P(OPM_HFile);
	P(OPM_BFile);
	P(OPM_HIFile);
}


export void *OPM__init(void)
{
	__DEFMOD;
	__IMPORT(Args);
	__IMPORT(Console);
	__IMPORT(Files0);
	__IMPORT(Texts0);
	__IMPORT(errors);
	__IMPORT(version);
	__IMPORT(vt100);
	__REGMOD("OPM", EnumPtrs);
	__REGCMD("CloseFiles", OPM_CloseFiles);
	__REGCMD("CloseOldSym", OPM_CloseOldSym);
	__REGCMD("DeleteNewSym", OPM_DeleteNewSym);
	__REGCMD("InitOptions", OPM_InitOptions);
	__REGCMD("LogWLn", OPM_LogWLn);
	__REGCMD("OpenPar", OPM_OpenPar);
	__REGCMD("PromoteIntConstToLInt", OPM_PromoteIntConstToLInt);
	__REGCMD("RegisterNewSym", OPM_RegisterNewSym);
	__REGCMD("WriteLn", OPM_WriteLn);
/* BEGIN */
	Texts0_OpenWriter(&OPM_W, Texts0_Writer__typ);
	__ENDMOD;
}
