/* voc  1.0  [2013/09/23] tspkaPS */

#ifndef Files0__h
#define Files0__h

#include "SYSTEM.h"

typedef
	struct Files0_Handle *Files0_File;

typedef
	struct Files0_Handle {
		char _prvt0[232];
		LONGINT fd;
		char _prvt1[56];
	} Files0_Handle;

typedef
	struct Files0_Rider {
		LONGINT res;
		BOOLEAN eof;
		char _prvt0[31];
	} Files0_Rider;



import LONGINT *Files0_Handle__typ;
import LONGINT *Files0_Rider__typ;

import Files0_File Files0_Base (Files0_Rider *r, LONGINT *r__typ);
import void Files0_ChangeDirectory (CHAR *path, LONGINT path__len, INTEGER *res);
import void Files0_Close (Files0_File f);
import void Files0_Delete (CHAR *name, LONGINT name__len, INTEGER *res);
import void Files0_GetDate (Files0_File f, LONGINT *t, LONGINT *d);
import LONGINT Files0_Length (Files0_File f);
import Files0_File Files0_New (CHAR *name, LONGINT name__len);
import Files0_File Files0_Old (CHAR *name, LONGINT name__len);
import LONGINT Files0_Pos (Files0_Rider *r, LONGINT *r__typ);
import void Files0_Purge (Files0_File f);
import void Files0_Read (Files0_Rider *r, LONGINT *r__typ, SYSTEM_BYTE *x);
import void Files0_ReadBool (Files0_Rider *R, LONGINT *R__typ, BOOLEAN *x);
import void Files0_ReadBytes (Files0_Rider *r, LONGINT *r__typ, SYSTEM_BYTE *x, LONGINT x__len, LONGINT n);
import void Files0_ReadInt (Files0_Rider *R, LONGINT *R__typ, INTEGER *x);
import void Files0_ReadLInt (Files0_Rider *R, LONGINT *R__typ, LONGINT *x);
import void Files0_ReadLReal (Files0_Rider *R, LONGINT *R__typ, LONGREAL *x);
import void Files0_ReadNum (Files0_Rider *R, LONGINT *R__typ, LONGINT *x);
import void Files0_ReadReal (Files0_Rider *R, LONGINT *R__typ, REAL *x);
import void Files0_ReadSet (Files0_Rider *R, LONGINT *R__typ, SET *x);
import void Files0_ReadString (Files0_Rider *R, LONGINT *R__typ, CHAR *x, LONGINT x__len);
import void Files0_Register (Files0_File f);
import void Files0_Rename (CHAR *old, LONGINT old__len, CHAR *new, LONGINT new__len, INTEGER *res);
import void Files0_Set (Files0_Rider *r, LONGINT *r__typ, Files0_File f, LONGINT pos);
import void Files0_Write (Files0_Rider *r, LONGINT *r__typ, SYSTEM_BYTE x);
import void Files0_WriteBool (Files0_Rider *R, LONGINT *R__typ, BOOLEAN x);
import void Files0_WriteBytes (Files0_Rider *r, LONGINT *r__typ, SYSTEM_BYTE *x, LONGINT x__len, LONGINT n);
import void Files0_WriteInt (Files0_Rider *R, LONGINT *R__typ, INTEGER x);
import void Files0_WriteLInt (Files0_Rider *R, LONGINT *R__typ, LONGINT x);
import void Files0_WriteLReal (Files0_Rider *R, LONGINT *R__typ, LONGREAL x);
import void Files0_WriteNum (Files0_Rider *R, LONGINT *R__typ, LONGINT x);
import void Files0_WriteReal (Files0_Rider *R, LONGINT *R__typ, REAL x);
import void Files0_WriteSet (Files0_Rider *R, LONGINT *R__typ, SET x);
import void Files0_WriteString (Files0_Rider *R, LONGINT *R__typ, CHAR *x, LONGINT x__len);
import void *Files0__init(void);


#endif
