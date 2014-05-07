/* voc  1.0  [2013/09/23] tspkaPS */

#ifndef OPS__h
#define OPS__h

#include "SYSTEM.h"

typedef
	CHAR OPS_Name[32];

typedef
	CHAR OPS_String[256];


import OPS_Name OPS_name;
import OPS_String OPS_str;
import INTEGER OPS_numtyp;
import LONGINT OPS_intval;
import REAL OPS_realval;
import LONGREAL OPS_lrlval;


import void OPS_Get (SHORTINT *sym);
import void OPS_Init (void);
import void *OPS__init(void);


#endif
