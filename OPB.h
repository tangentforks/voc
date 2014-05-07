/* voc  1.0  [2013/09/23] xtspkaPS */

#ifndef OPB__h
#define OPB__h

#include "SYSTEM.h"
#include "OPS.h"
#include "OPT.h"


import void (*OPB_typSize)(OPT_Struct);


import void OPB_Assign (OPT_Node *x, OPT_Node y);
import void OPB_Call (OPT_Node *x, OPT_Node apar, OPT_Object fp);
import void OPB_CheckParameters (OPT_Object fp, OPT_Object ap, BOOLEAN checkNames);
import void OPB_Construct (SHORTINT class, OPT_Node *x, OPT_Node y);
import void OPB_DeRef (OPT_Node *x);
import OPT_Node OPB_EmptySet (void);
import void OPB_Enter (OPT_Node *procdec, OPT_Node stat, OPT_Object proc);
import void OPB_Field (OPT_Node *x, OPT_Object y);
import void OPB_In (OPT_Node *x, OPT_Node y);
import void OPB_Index (OPT_Node *x, OPT_Node y);
import void OPB_Inittd (OPT_Node *inittd, OPT_Node *last, OPT_Struct typ);
import void OPB_Link (OPT_Node *x, OPT_Node *last, OPT_Node y);
import void OPB_MOp (SHORTINT op, OPT_Node *x);
import OPT_Node OPB_NewBoolConst (BOOLEAN boolval);
import OPT_Node OPB_NewIntConst (LONGINT intval);
import OPT_Node OPB_NewLeaf (OPT_Object obj);
import OPT_Node OPB_NewRealConst (LONGREAL realval, OPT_Struct typ);
import OPT_Node OPB_NewString (OPS_String str, LONGINT len);
import OPT_Node OPB_Nil (void);
import void OPB_Op (SHORTINT op, OPT_Node *x, OPT_Node y);
import void OPB_OptIf (OPT_Node *x);
import void OPB_Param (OPT_Node ap, OPT_Object fp);
import void OPB_PrepCall (OPT_Node *x, OPT_Object *fpar);
import void OPB_Return (OPT_Node *x, OPT_Object proc);
import void OPB_SetElem (OPT_Node *x);
import void OPB_SetRange (OPT_Node *x, OPT_Node y);
import void OPB_StFct (OPT_Node *par0, SHORTINT fctno, INTEGER parno);
import void OPB_StPar0 (OPT_Node *par0, INTEGER fctno);
import void OPB_StPar1 (OPT_Node *par0, OPT_Node x, SHORTINT fctno);
import void OPB_StParN (OPT_Node *par0, OPT_Node x, INTEGER fctno, INTEGER n);
import void OPB_StaticLink (SHORTINT dlev);
import void OPB_TypTest (OPT_Node *x, OPT_Object obj, BOOLEAN guard);
import void *OPB__init(void);


#endif
