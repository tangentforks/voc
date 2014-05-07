/* voc  1.0  [2013/09/23] xtspkaPS */

#ifndef OPM__h
#define OPM__h

#include "SYSTEM.h"


import INTEGER OPM_ByteSize, OPM_CharSize, OPM_BoolSize, OPM_SIntSize, OPM_IntSize, OPM_LIntSize, OPM_SetSize, OPM_RealSize, OPM_LRealSize, OPM_PointerSize, OPM_ProcSize, OPM_RecSize, OPM_CharAlign, OPM_BoolAlign, OPM_SIntAlign, OPM_IntAlign, OPM_LIntAlign, OPM_SetAlign, OPM_RealAlign, OPM_LRealAlign, OPM_PointerAlign, OPM_ProcAlign, OPM_RecAlign, OPM_ByteOrder, OPM_BitOrder, OPM_MaxSet;
import LONGINT OPM_MinSInt, OPM_MinInt, OPM_MinLInt, OPM_MaxSInt, OPM_MaxInt, OPM_MaxLInt, OPM_MaxIndex;
import LONGREAL OPM_MinReal, OPM_MaxReal, OPM_MinLReal, OPM_MaxLReal;
import BOOLEAN OPM_noerr;
import LONGINT OPM_curpos, OPM_errpos, OPM_breakpc;
import INTEGER OPM_currFile, OPM_level, OPM_pc, OPM_entno;
import CHAR OPM_modName[32];
import CHAR OPM_objname[64];
import SET OPM_opt, OPM_glbopt;
import BOOLEAN OPM_dontAsm, OPM_dontLink, OPM_mainProg, OPM_mainLinkStat, OPM_notColorOutput;


import void OPM_CloseFiles (void);
import void OPM_CloseOldSym (void);
import void OPM_DeleteNewSym (void);
import void OPM_FPrint (LONGINT *fp, LONGINT val);
import void OPM_FPrintLReal (LONGINT *fp, LONGREAL lr);
import void OPM_FPrintReal (LONGINT *fp, REAL real);
import void OPM_FPrintSet (LONGINT *fp, SET set);
import void OPM_Get (CHAR *ch);
import void OPM_Init (BOOLEAN *done, CHAR *mname, LONGINT mname__len);
import void OPM_InitOptions (void);
import void OPM_LogW (CHAR ch);
import void OPM_LogWLn (void);
import void OPM_LogWNum (LONGINT i, LONGINT len);
import void OPM_LogWStr (CHAR *s, LONGINT s__len);
import void OPM_Mark (INTEGER n, LONGINT pos);
import void OPM_NewSym (CHAR *modName, LONGINT modName__len);
import void OPM_OldSym (CHAR *modName, LONGINT modName__len, BOOLEAN *done);
import void OPM_OpenFiles (CHAR *moduleName, LONGINT moduleName__len);
import void OPM_OpenPar (void);
import void OPM_PromoteIntConstToLInt (void);
import void OPM_RegisterNewSym (void);
import void OPM_SymRCh (CHAR *ch);
import LONGINT OPM_SymRInt (void);
import void OPM_SymRLReal (LONGREAL *lr);
import void OPM_SymRReal (REAL *r);
import void OPM_SymRSet (SET *s);
import void OPM_SymWCh (CHAR ch);
import void OPM_SymWInt (LONGINT i);
import void OPM_SymWLReal (LONGREAL lr);
import void OPM_SymWReal (REAL r);
import void OPM_SymWSet (SET s);
import void OPM_Write (CHAR ch);
import void OPM_WriteHex (LONGINT i);
import void OPM_WriteInt (LONGINT i);
import void OPM_WriteLn (void);
import void OPM_WriteReal (LONGREAL r, CHAR suffx);
import void OPM_WriteString (CHAR *s, LONGINT s__len);
import void OPM_WriteStringVar (CHAR *s, LONGINT s__len);
import BOOLEAN OPM_eofSF (void);
import void OPM_err (INTEGER n);
import void *OPM__init(void);


#endif
