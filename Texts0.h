/* voc  1.0  [2013/09/23] xtspkaPS */

#ifndef Texts0__h
#define Texts0__h

#include "SYSTEM.h"
#include "Files0.h"

typedef
	struct Texts0_BufDesc {
		LONGINT len;
		char _prvt0[8];
	} Texts0_BufDesc;

typedef
	Texts0_BufDesc *Texts0_Buffer;

typedef
	struct Texts0_ElemMsg {
		char _prvt0[1];
	} Texts0_ElemMsg;

typedef
	struct Texts0_ElemDesc *Texts0_Elem;

typedef
	struct Texts0_CopyMsg { /* Texts0_ElemMsg */
		Texts0_Elem e;
	} Texts0_CopyMsg;

typedef
	struct Texts0_RunDesc {
		LONGINT _prvt0;
		char _prvt1[27];
	} Texts0_RunDesc;

typedef
	void (*Texts0_Handler)(Texts0_Elem, Texts0_ElemMsg*, LONGINT *);

typedef
	struct Texts0_ElemDesc {
		char _prvt0[40];
		LONGINT W, H;
		Texts0_Handler handle;
		char _prvt1[8];
	} Texts0_ElemDesc;

typedef
	struct Texts0_FileMsg { /* Texts0_ElemMsg */
		INTEGER id;
		LONGINT pos;
		Files0_Rider r;
	} Texts0_FileMsg;

typedef
	struct Texts0_FontDesc {
		char _prvt0[32];
	} Texts0_FontDesc;

typedef
	Texts0_FontDesc *Texts0_FontsFont;

typedef
	struct Texts0_IdentifyMsg { /* Texts0_ElemMsg */
		CHAR mod[32], proc[32];
	} Texts0_IdentifyMsg;

typedef
	struct Texts0_Reader {
		BOOLEAN eot;
		Texts0_FontsFont fnt;
		SHORTINT col, voff;
		Texts0_Elem elem;
		char _prvt0[64];
	} Texts0_Reader;

typedef
	struct Texts0_Scanner { /* Texts0_Reader */
		BOOLEAN eot;
		Texts0_FontsFont fnt;
		SHORTINT col, voff;
		Texts0_Elem elem;
		char _prvt0[64];
		CHAR nextCh;
		INTEGER line, class;
		LONGINT i;
		REAL x;
		LONGREAL y;
		CHAR c;
		SHORTINT len;
		CHAR s[64];
	} Texts0_Scanner;

typedef
	struct Texts0_TextDesc *Texts0_Text;

typedef
	struct Texts0_TextDesc {
		LONGINT len;
		char _prvt0[24];
	} Texts0_TextDesc;

typedef
	struct Texts0_Writer {
		Texts0_Buffer buf;
		Texts0_FontsFont fnt;
		SHORTINT col, voff;
		char _prvt0[54];
	} Texts0_Writer;


import Texts0_Elem Texts0_new;

import LONGINT *Texts0_FontDesc__typ;
import LONGINT *Texts0_RunDesc__typ;
import LONGINT *Texts0_ElemMsg__typ;
import LONGINT *Texts0_ElemDesc__typ;
import LONGINT *Texts0_FileMsg__typ;
import LONGINT *Texts0_CopyMsg__typ;
import LONGINT *Texts0_IdentifyMsg__typ;
import LONGINT *Texts0_BufDesc__typ;
import LONGINT *Texts0_TextDesc__typ;
import LONGINT *Texts0_Reader__typ;
import LONGINT *Texts0_Scanner__typ;
import LONGINT *Texts0_Writer__typ;

import void Texts0_Append (Texts0_Text T, Texts0_Buffer B);
import void Texts0_ChangeLooks (Texts0_Text T, LONGINT beg, LONGINT end, SET sel, Texts0_FontsFont fnt, SHORTINT col, SHORTINT voff);
import void Texts0_Close (Texts0_Text T, CHAR *name, LONGINT name__len);
import void Texts0_Copy (Texts0_Buffer SB, Texts0_Buffer DB);
import void Texts0_CopyElem (Texts0_Elem SE, Texts0_Elem DE);
import void Texts0_Delete (Texts0_Text T, LONGINT beg, LONGINT end);
import Texts0_Text Texts0_ElemBase (Texts0_Elem E);
import LONGINT Texts0_ElemPos (Texts0_Elem E);
import void Texts0_Insert (Texts0_Text T, LONGINT pos, Texts0_Buffer B);
import void Texts0_Load (Files0_Rider *r, LONGINT *r__typ, Texts0_Text T);
import void Texts0_Open (Texts0_Text T, CHAR *name, LONGINT name__len);
import void Texts0_OpenBuf (Texts0_Buffer B);
import void Texts0_OpenReader (Texts0_Reader *R, LONGINT *R__typ, Texts0_Text T, LONGINT pos);
import void Texts0_OpenScanner (Texts0_Scanner *S, LONGINT *S__typ, Texts0_Text T, LONGINT pos);
import void Texts0_OpenWriter (Texts0_Writer *W, LONGINT *W__typ);
import LONGINT Texts0_Pos (Texts0_Reader *R, LONGINT *R__typ);
import void Texts0_Read (Texts0_Reader *R, LONGINT *R__typ, CHAR *ch);
import void Texts0_ReadElem (Texts0_Reader *R, LONGINT *R__typ);
import void Texts0_ReadPrevElem (Texts0_Reader *R, LONGINT *R__typ);
import void Texts0_Recall (Texts0_Buffer *B);
import void Texts0_Save (Texts0_Text T, LONGINT beg, LONGINT end, Texts0_Buffer B);
import void Texts0_Scan (Texts0_Scanner *S, LONGINT *S__typ);
import void Texts0_SetColor (Texts0_Writer *W, LONGINT *W__typ, SHORTINT col);
import void Texts0_SetFont (Texts0_Writer *W, LONGINT *W__typ, Texts0_FontsFont fnt);
import void Texts0_SetOffset (Texts0_Writer *W, LONGINT *W__typ, SHORTINT voff);
import void Texts0_Store (Files0_Rider *r, LONGINT *r__typ, Texts0_Text T);
import void Texts0_Write (Texts0_Writer *W, LONGINT *W__typ, CHAR ch);
import void Texts0_WriteDate (Texts0_Writer *W, LONGINT *W__typ, LONGINT t, LONGINT d);
import void Texts0_WriteElem (Texts0_Writer *W, LONGINT *W__typ, Texts0_Elem e);
import void Texts0_WriteHex (Texts0_Writer *W, LONGINT *W__typ, LONGINT x);
import void Texts0_WriteInt (Texts0_Writer *W, LONGINT *W__typ, LONGINT x, LONGINT n);
import void Texts0_WriteLn (Texts0_Writer *W, LONGINT *W__typ);
import void Texts0_WriteLongReal (Texts0_Writer *W, LONGINT *W__typ, LONGREAL x, INTEGER n);
import void Texts0_WriteLongRealHex (Texts0_Writer *W, LONGINT *W__typ, LONGREAL x);
import void Texts0_WriteReal (Texts0_Writer *W, LONGINT *W__typ, REAL x, INTEGER n);
import void Texts0_WriteRealFix (Texts0_Writer *W, LONGINT *W__typ, REAL x, INTEGER n, INTEGER k);
import void Texts0_WriteRealHex (Texts0_Writer *W, LONGINT *W__typ, REAL x);
import void Texts0_WriteString (Texts0_Writer *W, LONGINT *W__typ, CHAR *s, LONGINT s__len);
import void *Texts0__init(void);


#endif
