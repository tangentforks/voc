/* voc  1.0  [2013/09/23] xtspkaPS */
#include "SYSTEM.h"
#include "OPM.h"
#include "OPS.h"

typedef
	struct OPT_ConstDesc *OPT_Const;

typedef
	OPS_String *OPT_ConstExt;

typedef
	struct OPT_ConstDesc {
		OPT_ConstExt ext;
		LONGINT intval, intval2;
		SET setval;
		LONGREAL realval;
	} OPT_ConstDesc;

typedef
	struct OPT_ExpCtxt {
		LONGINT reffp;
		INTEGER ref;
		SHORTINT nofm;
		SHORTINT locmno[64];
	} OPT_ExpCtxt;

typedef
	struct OPT_StrDesc *OPT_Struct;

typedef
	struct OPT_ObjDesc *OPT_Object;

typedef
	struct OPT_ImpCtxt {
		LONGINT nextTag, reffp;
		INTEGER nofr, minr, nofm;
		BOOLEAN self;
		OPT_Struct ref[255];
		OPT_Object old[255];
		LONGINT pvfp[255];
		SHORTINT glbmno[64];
	} OPT_ImpCtxt;

typedef
	struct OPT_NodeDesc *OPT_Node;

typedef
	struct OPT_NodeDesc {
		OPT_Node left, right, link;
		SHORTINT class, subcl;
		BOOLEAN readonly;
		OPT_Struct typ;
		OPT_Object obj;
		OPT_Const conval;
	} OPT_NodeDesc;

typedef
	struct OPT_ObjDesc {
		OPT_Object left, right, link, scope;
		OPS_Name name;
		BOOLEAN leaf;
		SHORTINT mode, mnolev, vis, history;
		BOOLEAN used, fpdone;
		LONGINT fprint;
		OPT_Struct typ;
		OPT_Const conval;
		LONGINT adr, linkadr;
		INTEGER x;
	} OPT_ObjDesc;

typedef
	struct OPT_StrDesc {
		SHORTINT form, comp, mno, extlev;
		INTEGER ref, sysflag;
		LONGINT n, size, align, txtpos;
		BOOLEAN allocated, pbused, pvused, fpdone, idfpdone;
		LONGINT idfp, pbfp, pvfp;
		OPT_Struct BaseTyp;
		OPT_Object link, strobj;
	} OPT_StrDesc;


export void (*OPT_typSize)(OPT_Struct);
export OPT_Object OPT_topScope;
export OPT_Struct OPT_undftyp, OPT_bytetyp, OPT_booltyp, OPT_chartyp, OPT_sinttyp, OPT_inttyp, OPT_linttyp, OPT_realtyp, OPT_lrltyp, OPT_settyp, OPT_stringtyp, OPT_niltyp, OPT_notyp, OPT_sysptrtyp;
export SHORTINT OPT_nofGmod;
export OPT_Object OPT_GlbMod[64];
export OPS_Name OPT_SelfName;
export BOOLEAN OPT_SYSimported;
static OPT_Object OPT_universe, OPT_syslink;
static OPT_ImpCtxt OPT_impCtxt;
static OPT_ExpCtxt OPT_expCtxt;
static LONGINT OPT_nofhdfld;
static BOOLEAN OPT_newsf, OPT_findpc, OPT_extsf, OPT_sfpresent, OPT_symExtended, OPT_symNew;

export LONGINT *OPT_ConstDesc__typ;
export LONGINT *OPT_ObjDesc__typ;
export LONGINT *OPT_StrDesc__typ;
export LONGINT *OPT_NodeDesc__typ;
export LONGINT *OPT_ImpCtxt__typ;
export LONGINT *OPT_ExpCtxt__typ;

export void OPT_Close (void);
export void OPT_CloseScope (void);
static void OPT_EnterBoolConst (OPS_Name name, LONGINT value);
static void OPT_EnterProc (OPS_Name name, INTEGER num);
static void OPT_EnterTyp (OPS_Name name, SHORTINT form, INTEGER size, OPT_Struct *res);
export void OPT_Export (BOOLEAN *ext, BOOLEAN *new);
export void OPT_FPrintErr (OPT_Object obj, INTEGER errno);
static void OPT_FPrintName (LONGINT *fp, CHAR *name, LONGINT name__len);
export void OPT_FPrintObj (OPT_Object obj);
static void OPT_FPrintSign (LONGINT *fp, OPT_Struct result, OPT_Object par);
export void OPT_FPrintStr (OPT_Struct typ);
export void OPT_Find (OPT_Object *res);
export void OPT_FindField (OPS_Name name, OPT_Struct typ, OPT_Object *res);
export void OPT_FindImport (OPT_Object mod, OPT_Object *res);
export void OPT_IdFPrint (OPT_Struct typ);
export void OPT_Import (OPS_Name aliasName, OPS_Name name, BOOLEAN *done);
static void OPT_InConstant (LONGINT f, OPT_Const conval);
static OPT_Object OPT_InFld (void);
static void OPT_InMod (SHORTINT *mno);
static void OPT_InName (CHAR *name, LONGINT name__len);
static OPT_Object OPT_InObj (SHORTINT mno);
static void OPT_InSign (SHORTINT mno, OPT_Struct *res, OPT_Object *par);
static void OPT_InStruct (OPT_Struct *typ);
static OPT_Object OPT_InTProc (SHORTINT mno);
export void OPT_Init (OPS_Name name, SET opt);
static void OPT_InitStruct (OPT_Struct *typ, SHORTINT form);
export void OPT_Insert (OPS_Name name, OPT_Object *obj);
export void OPT_InsertImport (OPT_Object obj, OPT_Object *root, OPT_Object *old);
export OPT_Const OPT_NewConst (void);
export OPT_ConstExt OPT_NewExt (void);
export OPT_Node OPT_NewNode (SHORTINT class);
export OPT_Object OPT_NewObj (void);
export OPT_Struct OPT_NewStr (SHORTINT form, SHORTINT comp);
export void OPT_OpenScope (SHORTINT level, OPT_Object owner);
static void OPT_OutConstant (OPT_Object obj);
static void OPT_OutFlds (OPT_Object fld, LONGINT adr, BOOLEAN visible);
static void OPT_OutHdFld (OPT_Struct typ, OPT_Object fld, LONGINT adr);
static void OPT_OutMod (INTEGER mno);
static void OPT_OutName (CHAR *name, LONGINT name__len);
static void OPT_OutObj (OPT_Object obj);
static void OPT_OutSign (OPT_Struct result, OPT_Object par);
static void OPT_OutStr (OPT_Struct typ);
static void OPT_OutTProcs (OPT_Struct typ, OPT_Object obj);
static void OPT_err (INTEGER n);


static void OPT_err (INTEGER n)
{
	OPM_err(n);
}

OPT_Const OPT_NewConst (void)
{
	OPT_Const const_ = NIL;
	__NEW(const_, OPT_ConstDesc);
	return const_;
}

OPT_Object OPT_NewObj (void)
{
	OPT_Object obj = NIL;
	__NEW(obj, OPT_ObjDesc);
	return obj;
}

OPT_Struct OPT_NewStr (SHORTINT form, SHORTINT comp)
{
	OPT_Struct typ = NIL;
	__NEW(typ, OPT_StrDesc);
	typ->form = form;
	typ->comp = comp;
	typ->ref = 255;
	if (form != 0) {
		typ->txtpos = OPM_errpos;
	}
	typ->size = -1;
	typ->BaseTyp = OPT_undftyp;
	return typ;
}

OPT_Node OPT_NewNode (SHORTINT class)
{
	OPT_Node node = NIL;
	__NEW(node, OPT_NodeDesc);
	node->class = class;
	return node;
}

OPT_ConstExt OPT_NewExt (void)
{
	OPT_ConstExt ext = NIL;
	ext = __NEWARR(NIL, 1, 1, 1, 0, 256);
	return ext;
}

void OPT_OpenScope (SHORTINT level, OPT_Object owner)
{
	OPT_Object head = NIL;
	head = OPT_NewObj();
	head->mode = 12;
	head->mnolev = level;
	head->link = owner;
	if (owner != NIL) {
		owner->scope = head;
	}
	head->left = OPT_topScope;
	head->right = NIL;
	head->scope = NIL;
	OPT_topScope = head;
}

void OPT_CloseScope (void)
{
	OPT_topScope = OPT_topScope->left;
}

void OPT_Init (OPS_Name name, SET opt)
{
	OPT_topScope = OPT_universe;
	OPT_OpenScope(0, NIL);
	OPT_SYSimported = 0;
	__MOVE(name, OPT_SelfName, 32);
	__MOVE(name, OPT_topScope->name, 32);
	OPT_GlbMod[0] = OPT_topScope;
	OPT_nofGmod = 1;
	OPT_newsf = __IN(4, opt);
	OPT_findpc = __IN(8, opt);
	OPT_extsf = OPT_newsf || __IN(9, opt);
	OPT_sfpresent = 1;
}

void OPT_Close (void)
{
	INTEGER i;
	OPT_CloseScope();
	i = 0;
	while (i < 64) {
		OPT_GlbMod[__X(i, 64)] = NIL;
		i += 1;
	}
	i = 16;
	while (i < 255) {
		OPT_impCtxt.ref[__X(i, 255)] = NIL;
		OPT_impCtxt.old[__X(i, 255)] = NIL;
		i += 1;
	}
}

void OPT_FindImport (OPT_Object mod, OPT_Object *res)
{
	OPT_Object obj = NIL;
	obj = mod->scope;
	for (;;) {
		if (obj == NIL) {
			break;
		}
		if (__STRCMP(OPS_name, obj->name) < 0) {
			obj = obj->left;
		} else if (__STRCMP(OPS_name, obj->name) > 0) {
			obj = obj->right;
		} else {
			if ((obj->mode == 5 && obj->vis == 0)) {
				obj = NIL;
			} else {
				obj->used = 1;
			}
			break;
		}
	}
	*res = obj;
}

void OPT_Find (OPT_Object *res)
{
	OPT_Object obj = NIL, head = NIL;
	head = OPT_topScope;
	for (;;) {
		obj = head->right;
		for (;;) {
			if (obj == NIL) {
				break;
			}
			if (__STRCMP(OPS_name, obj->name) < 0) {
				obj = obj->left;
			} else if (__STRCMP(OPS_name, obj->name) > 0) {
				obj = obj->right;
			} else {
				break;
			}
		}
		if (obj != NIL) {
			break;
		}
		head = head->left;
		if (head == NIL) {
			break;
		}
	}
	*res = obj;
}

void OPT_FindField (OPS_Name name, OPT_Struct typ, OPT_Object *res)
{
	OPT_Object obj = NIL;
	while (typ != NIL) {
		obj = typ->link;
		while (obj != NIL) {
			if (__STRCMP(name, obj->name) < 0) {
				obj = obj->left;
			} else if (__STRCMP(name, obj->name) > 0) {
				obj = obj->right;
			} else {
				*res = obj;
				return;
			}
		}
		typ = typ->BaseTyp;
	}
	*res = NIL;
}

void OPT_Insert (OPS_Name name, OPT_Object *obj)
{
	OPT_Object ob0 = NIL, ob1 = NIL;
	BOOLEAN left;
	SHORTINT mnolev;
	ob0 = OPT_topScope;
	ob1 = ob0->right;
	left = 0;
	for (;;) {
		if (ob1 != NIL) {
			if (__STRCMP(name, ob1->name) < 0) {
				ob0 = ob1;
				ob1 = ob0->left;
				left = 1;
			} else if (__STRCMP(name, ob1->name) > 0) {
				ob0 = ob1;
				ob1 = ob0->right;
				left = 0;
			} else {
				OPT_err(1);
				ob0 = ob1;
				ob1 = ob0->right;
			}
		} else {
			ob1 = OPT_NewObj();
			ob1->leaf = 1;
			if (left) {
				ob0->left = ob1;
			} else {
				ob0->right = ob1;
			}
			ob1->left = NIL;
			ob1->right = NIL;
			__COPY(name, ob1->name, 32);
			mnolev = OPT_topScope->mnolev;
			ob1->mnolev = mnolev;
			break;
		}
	}
	*obj = ob1;
}

static void OPT_FPrintName (LONGINT *fp, CHAR *name, LONGINT name__len)
{
	INTEGER i;
	CHAR ch;
	i = 0;
	do {
		ch = name[__X(i, name__len)];
		OPM_FPrint(&*fp, (int)ch);
		i += 1;
	} while (!(ch == 0x00));
}

static void OPT_FPrintSign (LONGINT *fp, OPT_Struct result, OPT_Object par)
{
	OPT_IdFPrint(result);
	OPM_FPrint(&*fp, result->idfp);
	while (par != NIL) {
		OPM_FPrint(&*fp, par->mode);
		OPT_IdFPrint(par->typ);
		OPM_FPrint(&*fp, par->typ->idfp);
		par = par->link;
	}
}

void OPT_IdFPrint (OPT_Struct typ)
{
	OPT_Struct btyp = NIL;
	OPT_Object strobj = NIL;
	LONGINT idfp;
	INTEGER f, c;
	if (!typ->idfpdone) {
		typ->idfpdone = 1;
		idfp = 0;
		f = typ->form;
		c = typ->comp;
		OPM_FPrint(&idfp, f);
		OPM_FPrint(&idfp, c);
		btyp = typ->BaseTyp;
		strobj = typ->strobj;
		if ((strobj != NIL && strobj->name[0] != 0x00)) {
			OPT_FPrintName(&idfp, (void*)OPT_GlbMod[__X(typ->mno, 64)]->name, 32);
			OPT_FPrintName(&idfp, (void*)strobj->name, 32);
		}
		if ((f == 13 || (c == 4 && btyp != NIL)) || c == 3) {
			OPT_IdFPrint(btyp);
			OPM_FPrint(&idfp, btyp->idfp);
		} else if (c == 2) {
			OPT_IdFPrint(btyp);
			OPM_FPrint(&idfp, btyp->idfp);
			OPM_FPrint(&idfp, typ->n);
		} else if (f == 14) {
			OPT_FPrintSign(&idfp, btyp, typ->link);
		}
		typ->idfp = idfp;
	}
}

static struct FPrintStr__11 {
	LONGINT *pbfp, *pvfp;
	struct FPrintStr__11 *lnk;
} *FPrintStr__11_s;

static void FPrintFlds__12 (OPT_Object fld, LONGINT adr, BOOLEAN visible);
static void FPrintHdFld__14 (OPT_Struct typ, OPT_Object fld, LONGINT adr);
static void FPrintTProcs__16 (OPT_Object obj);

static void FPrintHdFld__14 (OPT_Struct typ, OPT_Object fld, LONGINT adr)
{
	LONGINT i, j, n;
	OPT_Struct btyp = NIL;
	if (typ->comp == 4) {
		FPrintFlds__12(typ->link, adr, 0);
	} else if (typ->comp == 2) {
		btyp = typ->BaseTyp;
		n = typ->n;
		while (btyp->comp == 2) {
			n = btyp->n * n;
			btyp = btyp->BaseTyp;
		}
		if (btyp->form == 13 || btyp->comp == 4) {
			j = OPT_nofhdfld;
			FPrintHdFld__14(btyp, fld, adr);
			if (j != OPT_nofhdfld) {
				i = 1;
				while ((i < n && OPT_nofhdfld <= 2048)) {
					adr += btyp->size;
					FPrintHdFld__14(btyp, fld, adr);
					i += 1;
				}
			}
		}
	} else if (typ->form == 13 || __STRCMP(fld->name, "@ptr") == 0) {
		OPM_FPrint(&*FPrintStr__11_s->pvfp, 13);
		OPM_FPrint(&*FPrintStr__11_s->pvfp, adr);
		OPT_nofhdfld += 1;
	}
}

static void FPrintFlds__12 (OPT_Object fld, LONGINT adr, BOOLEAN visible)
{
	while ((fld != NIL && fld->mode == 4)) {
		if ((fld->vis != 0 && visible)) {
			OPM_FPrint(&*FPrintStr__11_s->pbfp, fld->vis);
			OPT_FPrintName(&*FPrintStr__11_s->pbfp, (void*)fld->name, 32);
			OPM_FPrint(&*FPrintStr__11_s->pbfp, fld->adr);
			OPT_FPrintStr(fld->typ);
			OPM_FPrint(&*FPrintStr__11_s->pbfp, fld->typ->pbfp);
			OPM_FPrint(&*FPrintStr__11_s->pvfp, fld->typ->pvfp);
		} else {
			FPrintHdFld__14(fld->typ, fld, fld->adr + adr);
		}
		fld = fld->link;
	}
}

static void FPrintTProcs__16 (OPT_Object obj)
{
	if (obj != NIL) {
		FPrintTProcs__16(obj->left);
		if (obj->mode == 13) {
			if (obj->vis != 0) {
				OPM_FPrint(&*FPrintStr__11_s->pbfp, 13);
				OPM_FPrint(&*FPrintStr__11_s->pbfp, __ASHR(obj->adr, 16));
				OPT_FPrintSign(&*FPrintStr__11_s->pbfp, obj->typ, obj->link);
				OPT_FPrintName(&*FPrintStr__11_s->pbfp, (void*)obj->name, 32);
			}
		}
		FPrintTProcs__16(obj->right);
	}
}

void OPT_FPrintStr (OPT_Struct typ)
{
	INTEGER f, c;
	OPT_Struct btyp = NIL;
	OPT_Object strobj = NIL, bstrobj = NIL;
	LONGINT pbfp, pvfp;
	struct FPrintStr__11 _s;
	_s.pbfp = &pbfp;
	_s.pvfp = &pvfp;
	_s.lnk = FPrintStr__11_s;
	FPrintStr__11_s = &_s;
	if (!typ->fpdone) {
		OPT_IdFPrint(typ);
		pbfp = typ->idfp;
		if (typ->sysflag != 0) {
			OPM_FPrint(&pbfp, typ->sysflag);
		}
		pvfp = pbfp;
		typ->pbfp = pbfp;
		typ->pvfp = pvfp;
		typ->fpdone = 1;
		f = typ->form;
		c = typ->comp;
		btyp = typ->BaseTyp;
		if (f == 13) {
			strobj = typ->strobj;
			bstrobj = btyp->strobj;
			if (((strobj == NIL || strobj->name[0] == 0x00) || bstrobj == NIL) || bstrobj->name[0] == 0x00) {
				OPT_FPrintStr(btyp);
				OPM_FPrint(&pbfp, btyp->pbfp);
				pvfp = pbfp;
			}
		} else if (f == 14) {
		} else if (__IN(c, 0x0c)) {
			OPT_FPrintStr(btyp);
			OPM_FPrint(&pbfp, btyp->pvfp);
			pvfp = pbfp;
		} else {
			if (btyp != NIL) {
				OPT_FPrintStr(btyp);
				OPM_FPrint(&pbfp, btyp->pbfp);
				OPM_FPrint(&pvfp, btyp->pvfp);
			}
			OPM_FPrint(&pvfp, typ->size);
			OPM_FPrint(&pvfp, typ->align);
			OPM_FPrint(&pvfp, typ->n);
			OPT_nofhdfld = 0;
			FPrintFlds__12(typ->link, 0, 1);
			if (OPT_nofhdfld > 2048) {
				OPM_Mark(225, typ->txtpos);
			}
			FPrintTProcs__16(typ->link);
			OPM_FPrint(&pvfp, pbfp);
			strobj = typ->strobj;
			if (strobj == NIL || strobj->name[0] == 0x00) {
				pbfp = pvfp;
			}
		}
		typ->pbfp = pbfp;
		typ->pvfp = pvfp;
	}
	FPrintStr__11_s = _s.lnk;
}

void OPT_FPrintObj (OPT_Object obj)
{
	LONGINT fprint;
	INTEGER f, m;
	REAL rval;
	OPT_ConstExt ext = NIL;
	if (!obj->fpdone) {
		fprint = 0;
		obj->fpdone = 1;
		OPM_FPrint(&fprint, obj->mode);
		if (obj->mode == 3) {
			f = obj->typ->form;
			OPM_FPrint(&fprint, f);
			switch (f) {
				case 2: case 3: case 4: case 5: case 6: 
					OPM_FPrint(&fprint, obj->conval->intval);
					break;
				case 9: 
					OPM_FPrintSet(&fprint, obj->conval->setval);
					break;
				case 7: 
					rval = obj->conval->realval;
					OPM_FPrintReal(&fprint, rval);
					break;
				case 8: 
					OPM_FPrintLReal(&fprint, obj->conval->realval);
					break;
				case 10: 
					OPT_FPrintName(&fprint, (void*)*obj->conval->ext, 256);
					break;
				case 11: 
					break;
				default: 
					OPT_err(127);
					break;
			}
		} else if (obj->mode == 1) {
			OPM_FPrint(&fprint, obj->vis);
			OPT_FPrintStr(obj->typ);
			OPM_FPrint(&fprint, obj->typ->pbfp);
		} else if (__IN(obj->mode, 0x0480)) {
			OPT_FPrintSign(&fprint, obj->typ, obj->link);
		} else if (obj->mode == 9) {
			OPT_FPrintSign(&fprint, obj->typ, obj->link);
			ext = obj->conval->ext;
			m = (int)(*ext)[0];
			f = 1;
			OPM_FPrint(&fprint, m);
			while (f <= m) {
				OPM_FPrint(&fprint, (int)(*ext)[__X(f, 256)]);
				f += 1;
			}
		} else if (obj->mode == 5) {
			OPT_FPrintStr(obj->typ);
			OPM_FPrint(&fprint, obj->typ->pbfp);
		}
		obj->fprint = fprint;
	}
}

void OPT_FPrintErr (OPT_Object obj, INTEGER errno)
{
	INTEGER i, j;
	CHAR ch;
	if (obj->mnolev != 0) {
		__COPY(OPT_GlbMod[__X(-obj->mnolev, 64)]->name, OPM_objname, 64);
		i = 0;
		while (OPM_objname[__X(i, 64)] != 0x00) {
			i += 1;
		}
		OPM_objname[__X(i, 64)] = '.';
		j = 0;
		i += 1;
		do {
			ch = obj->name[__X(j, 32)];
			OPM_objname[__X(i, 64)] = ch;
			j += 1;
			i += 1;
		} while (!(ch == 0x00));
	} else {
		__COPY(obj->name, OPM_objname, 64);
	}
	if (errno == 249) {
		if (OPM_noerr) {
			OPT_err(errno);
		}
	} else if (errno == 253) {
		if ((((!OPT_symNew && !OPT_symExtended)) && !OPT_extsf)) {
			OPT_err(errno);
		}
		OPT_symExtended = 1;
	} else {
		if ((!OPT_symNew && !OPT_newsf)) {
			OPT_err(errno);
		}
		OPT_symNew = 1;
	}
}

void OPT_InsertImport (OPT_Object obj, OPT_Object *root, OPT_Object *old)
{
	OPT_Object ob0 = NIL, ob1 = NIL;
	BOOLEAN left;
	if (*root == NIL) {
		*root = obj;
		*old = NIL;
	} else {
		ob0 = *root;
		ob1 = ob0->right;
		left = 0;
		if (__STRCMP(obj->name, ob0->name) < 0) {
			ob1 = ob0->left;
			left = 1;
		} else if (__STRCMP(obj->name, ob0->name) > 0) {
			ob1 = ob0->right;
			left = 0;
		} else {
			*old = ob0;
			return;
		}
		for (;;) {
			if (ob1 != NIL) {
				if (__STRCMP(obj->name, ob1->name) < 0) {
					ob0 = ob1;
					ob1 = ob1->left;
					left = 1;
				} else if (__STRCMP(obj->name, ob1->name) > 0) {
					ob0 = ob1;
					ob1 = ob1->right;
					left = 0;
				} else {
					*old = ob1;
					break;
				}
			} else {
				ob1 = obj;
				if (left) {
					ob0->left = ob1;
				} else {
					ob0->right = ob1;
				}
				ob1->left = NIL;
				ob1->right = NIL;
				*old = NIL;
				break;
			}
		}
	}
}

static void OPT_InName (CHAR *name, LONGINT name__len)
{
	INTEGER i;
	CHAR ch;
	i = 0;
	do {
		OPM_SymRCh(&ch);
		name[__X(i, name__len)] = ch;
		i += 1;
	} while (!(ch == 0x00));
}

static void OPT_InMod (SHORTINT *mno)
{
	OPT_Object head = NIL;
	OPS_Name name;
	LONGINT mn;
	SHORTINT i;
	mn = OPM_SymRInt();
	if (mn == 0) {
		*mno = OPT_impCtxt.glbmno[0];
	} else {
		if (mn == 16) {
			OPT_InName((void*)name, 32);
			if ((__STRCMP(name, OPT_SelfName) == 0 && !OPT_impCtxt.self)) {
				OPT_err(154);
			}
			i = 0;
			while ((i < OPT_nofGmod && __STRCMP(name, OPT_GlbMod[__X(i, 64)]->name) != 0)) {
				i += 1;
			}
			if (i < OPT_nofGmod) {
				*mno = i;
			} else {
				head = OPT_NewObj();
				head->mode = 12;
				__COPY(name, head->name, 32);
				*mno = OPT_nofGmod;
				head->mnolev = -*mno;
				if (OPT_nofGmod < 64) {
					OPT_GlbMod[__X(*mno, 64)] = head;
					OPT_nofGmod += 1;
				} else {
					OPT_err(227);
				}
			}
			OPT_impCtxt.glbmno[__X(OPT_impCtxt.nofm, 64)] = *mno;
			OPT_impCtxt.nofm += 1;
		} else {
			*mno = OPT_impCtxt.glbmno[__X(-mn, 64)];
		}
	}
}

static void OPT_InConstant (LONGINT f, OPT_Const conval)
{
	CHAR ch;
	INTEGER i;
	OPT_ConstExt ext = NIL;
	REAL rval;
	switch (f) {
		case 1: case 3: case 2: 
			OPM_SymRCh(&ch);
			conval->intval = (int)ch;
			break;
		case 4: case 5: case 6: 
			conval->intval = OPM_SymRInt();
			break;
		case 9: 
			OPM_SymRSet(&conval->setval);
			break;
		case 7: 
			OPM_SymRReal(&rval);
			conval->realval = rval;
			conval->intval = -1;
			break;
		case 8: 
			OPM_SymRLReal(&conval->realval);
			conval->intval = -1;
			break;
		case 10: 
			ext = OPT_NewExt();
			conval->ext = ext;
			i = 0;
			do {
				OPM_SymRCh(&ch);
				(*ext)[__X(i, 256)] = ch;
				i += 1;
			} while (!(ch == 0x00));
			conval->intval2 = i;
			conval->intval = -1;
			break;
		case 11: 
			conval->intval = 0;
			break;
		default: __CASECHK;
	}
}

static void OPT_InSign (SHORTINT mno, OPT_Struct *res, OPT_Object *par)
{
	OPT_Object last = NIL, new = NIL;
	LONGINT tag;
	OPT_InStruct(&*res);
	tag = OPM_SymRInt();
	last = NIL;
	while (tag != 18) {
		new = OPT_NewObj();
		new->mnolev = -mno;
		if (last == NIL) {
			*par = new;
		} else {
			last->link = new;
		}
		if (tag == 23) {
			new->mode = 1;
		} else {
			new->mode = 2;
		}
		OPT_InStruct(&new->typ);
		new->adr = OPM_SymRInt();
		OPT_InName((void*)new->name, 32);
		last = new;
		tag = OPM_SymRInt();
	}
}

static OPT_Object OPT_InFld (void)
{
	LONGINT tag;
	OPT_Object obj = NIL;
	tag = OPT_impCtxt.nextTag;
	obj = OPT_NewObj();
	if (tag <= 26) {
		obj->mode = 4;
		if (tag == 26) {
			obj->vis = 2;
		} else {
			obj->vis = 1;
		}
		OPT_InStruct(&obj->typ);
		OPT_InName((void*)obj->name, 32);
		obj->adr = OPM_SymRInt();
	} else {
		obj->mode = 4;
		if (tag == 27) {
			__MOVE("@ptr", obj->name, 5);
		} else {
			__MOVE("@proc", obj->name, 6);
		}
		obj->typ = OPT_undftyp;
		obj->vis = 0;
		obj->adr = OPM_SymRInt();
	}
	return obj;
}

static OPT_Object OPT_InTProc (SHORTINT mno)
{
	LONGINT tag;
	OPT_Object obj = NIL;
	tag = OPT_impCtxt.nextTag;
	obj = OPT_NewObj();
	obj->mnolev = -mno;
	if (tag == 29) {
		obj->mode = 13;
		obj->conval = OPT_NewConst();
		obj->conval->intval = -1;
		OPT_InSign(mno, &obj->typ, &obj->link);
		obj->vis = 1;
		OPT_InName((void*)obj->name, 32);
		obj->adr = __ASHL(OPM_SymRInt(), 16);
	} else {
		obj->mode = 13;
		__MOVE("@tproc", obj->name, 7);
		obj->link = OPT_NewObj();
		obj->typ = OPT_undftyp;
		obj->vis = 0;
		obj->adr = __ASHL(OPM_SymRInt(), 16);
	}
	return obj;
}

static void OPT_InStruct (OPT_Struct *typ)
{
	SHORTINT mno;
	INTEGER ref;
	LONGINT tag;
	OPS_Name name;
	OPT_Struct t = NIL;
	OPT_Object obj = NIL, last = NIL, fld = NIL, old = NIL, dummy = NIL;
	tag = OPM_SymRInt();
	if (tag != 34) {
		*typ = OPT_impCtxt.ref[__X(-tag, 255)];
	} else {
		ref = OPT_impCtxt.nofr;
		OPT_impCtxt.nofr += 1;
		if (ref < OPT_impCtxt.minr) {
			OPT_impCtxt.minr = ref;
		}
		OPT_InMod(&mno);
		OPT_InName((void*)name, 32);
		obj = OPT_NewObj();
		if (name[0] == 0x00) {
			if (OPT_impCtxt.self) {
				old = NIL;
			} else {
				__MOVE("@", obj->name, 2);
				OPT_InsertImport(obj, &OPT_GlbMod[__X(mno, 64)]->right, &old);
				obj->name[0] = 0x00;
			}
			*typ = OPT_NewStr(0, 1);
		} else {
			__MOVE(name, obj->name, 32);
			OPT_InsertImport(obj, &OPT_GlbMod[__X(mno, 64)]->right, &old);
			if (old != NIL) {
				OPT_FPrintObj(old);
				OPT_impCtxt.pvfp[__X(ref, 255)] = old->typ->pvfp;
				if (OPT_impCtxt.self) {
					*typ = OPT_NewStr(0, 1);
				} else {
					*typ = old->typ;
					(*typ)->link = NIL;
					(*typ)->sysflag = 0;
					(*typ)->fpdone = 0;
					(*typ)->idfpdone = 0;
				}
			} else {
				*typ = OPT_NewStr(0, 1);
			}
		}
		OPT_impCtxt.ref[__X(ref, 255)] = *typ;
		OPT_impCtxt.old[__X(ref, 255)] = old;
		(*typ)->ref = ref + 255;
		(*typ)->mno = mno;
		(*typ)->allocated = 1;
		(*typ)->strobj = obj;
		obj->mode = 5;
		obj->typ = *typ;
		obj->mnolev = -mno;
		obj->vis = 0;
		tag = OPM_SymRInt();
		if (tag == 35) {
			(*typ)->sysflag = (int)OPM_SymRInt();
			tag = OPM_SymRInt();
		}
		switch (tag) {
			case 36: 
				(*typ)->form = 13;
				(*typ)->size = OPM_PointerSize;
				(*typ)->n = 0;
				OPT_InStruct(&(*typ)->BaseTyp);
				break;
			case 37: 
				(*typ)->form = 15;
				(*typ)->comp = 2;
				OPT_InStruct(&(*typ)->BaseTyp);
				(*typ)->n = OPM_SymRInt();
				(*OPT_typSize)(*typ);
				break;
			case 38: 
				(*typ)->form = 15;
				(*typ)->comp = 3;
				OPT_InStruct(&(*typ)->BaseTyp);
				if ((*typ)->BaseTyp->comp == 3) {
					(*typ)->n = (*typ)->BaseTyp->n + 1;
				} else {
					(*typ)->n = 0;
				}
				(*OPT_typSize)(*typ);
				break;
			case 39: 
				(*typ)->form = 15;
				(*typ)->comp = 4;
				OPT_InStruct(&(*typ)->BaseTyp);
				if ((*typ)->BaseTyp == OPT_notyp) {
					(*typ)->BaseTyp = NIL;
				}
				(*typ)->extlev = 0;
				t = (*typ)->BaseTyp;
				while (t != NIL) {
					(*typ)->extlev += 1;
					t = t->BaseTyp;
				}
				(*typ)->size = OPM_SymRInt();
				(*typ)->align = OPM_SymRInt();
				(*typ)->n = OPM_SymRInt();
				OPT_impCtxt.nextTag = OPM_SymRInt();
				last = NIL;
				while ((OPT_impCtxt.nextTag >= 25 && OPT_impCtxt.nextTag <= 28)) {
					fld = OPT_InFld();
					fld->mnolev = -mno;
					if (last != NIL) {
						last->link = fld;
					}
					last = fld;
					OPT_InsertImport(fld, &(*typ)->link, &dummy);
					OPT_impCtxt.nextTag = OPM_SymRInt();
				}
				while (OPT_impCtxt.nextTag != 18) {
					fld = OPT_InTProc(mno);
					OPT_InsertImport(fld, &(*typ)->link, &dummy);
					OPT_impCtxt.nextTag = OPM_SymRInt();
				}
				break;
			case 40: 
				(*typ)->form = 14;
				(*typ)->size = OPM_ProcSize;
				OPT_InSign(mno, &(*typ)->BaseTyp, &(*typ)->link);
				break;
			default: __CASECHK;
		}
		if (ref == OPT_impCtxt.minr) {
			while (ref < OPT_impCtxt.nofr) {
				t = OPT_impCtxt.ref[__X(ref, 255)];
				OPT_FPrintStr(t);
				obj = t->strobj;
				if (obj->name[0] != 0x00) {
					OPT_FPrintObj(obj);
				}
				old = OPT_impCtxt.old[__X(ref, 255)];
				if (old != NIL) {
					t->strobj = old;
					if (OPT_impCtxt.self) {
						if (old->mnolev < 0) {
							if (old->history != 5) {
								if (old->fprint != obj->fprint) {
									old->history = 2;
								} else if (OPT_impCtxt.pvfp[__X(ref, 255)] != t->pvfp) {
									old->history = 3;
								}
							}
						} else if (old->fprint != obj->fprint) {
							old->history = 2;
						} else if (OPT_impCtxt.pvfp[__X(ref, 255)] != t->pvfp) {
							old->history = 3;
						} else if (old->vis == 0) {
							old->history = 1;
						} else {
							old->history = 0;
						}
					} else {
						if (OPT_impCtxt.pvfp[__X(ref, 255)] != t->pvfp) {
							old->history = 5;
						}
						if (old->fprint != obj->fprint) {
							OPT_FPrintErr(old, 249);
						}
					}
				} else if (OPT_impCtxt.self) {
					obj->history = 4;
				} else {
					obj->history = 1;
				}
				ref += 1;
			}
			OPT_impCtxt.minr = 255;
		}
	}
}

static OPT_Object OPT_InObj (SHORTINT mno)
{
	INTEGER i, s;
	CHAR ch;
	OPT_Object obj = NIL, old = NIL;
	OPT_Struct typ = NIL;
	LONGINT tag;
	OPT_ConstExt ext = NIL;
	tag = OPT_impCtxt.nextTag;
	if (tag == 19) {
		OPT_InStruct(&typ);
		obj = typ->strobj;
		if (!OPT_impCtxt.self) {
			obj->vis = 1;
		}
	} else {
		obj = OPT_NewObj();
		obj->mnolev = -mno;
		obj->vis = 1;
		if (tag <= 13) {
			obj->mode = 3;
			obj->typ = OPT_impCtxt.ref[__X(tag, 255)];
			obj->conval = OPT_NewConst();
			OPT_InConstant(tag, obj->conval);
		} else if (tag >= 31) {
			obj->conval = OPT_NewConst();
			obj->conval->intval = -1;
			OPT_InSign(mno, &obj->typ, &obj->link);
			switch (tag) {
				case 31: 
					obj->mode = 7;
					break;
				case 32: 
					obj->mode = 10;
					break;
				case 33: 
					obj->mode = 9;
					ext = OPT_NewExt();
					obj->conval->ext = ext;
					s = (int)OPM_SymRInt();
					(*ext)[0] = (CHAR)s;
					i = 1;
					while (i <= s) {
						OPM_SymRCh(&(*ext)[__X(i, 256)]);
						i += 1;
					}
					break;
				default: __CASECHK;
			}
		} else if (tag == 20) {
			obj->mode = 5;
			OPT_InStruct(&obj->typ);
		} else {
			obj->mode = 1;
			if (tag == 22) {
				obj->vis = 2;
			}
			OPT_InStruct(&obj->typ);
		}
		OPT_InName((void*)obj->name, 32);
	}
	OPT_FPrintObj(obj);
	if ((obj->mode == 1 && (obj->typ->strobj == NIL || obj->typ->strobj->name[0] == 0x00))) {
		OPM_FPrint(&OPT_impCtxt.reffp, obj->typ->ref - 255);
	}
	if (tag != 19) {
		OPT_InsertImport(obj, &OPT_GlbMod[__X(mno, 64)]->right, &old);
		if (OPT_impCtxt.self) {
			if (old != NIL) {
				if (old->vis == 0) {
					old->history = 4;
				} else {
					OPT_FPrintObj(old);
					if (obj->fprint != old->fprint) {
						old->history = 2;
					} else if (obj->typ->pvfp != old->typ->pvfp) {
						old->history = 3;
					} else {
						old->history = 1;
					}
				}
			} else {
				obj->history = 4;
			}
		}
	} else {
		if (OPT_impCtxt.self) {
			if (obj->vis == 0) {
				obj->history = 4;
			} else if (obj->history == 0) {
				obj->history = 1;
			}
		}
	}
	return obj;
}

void OPT_Import (OPS_Name aliasName, OPS_Name name, BOOLEAN *done)
{
	OPT_Object obj = NIL;
	SHORTINT mno;
	OPS_Name aliasName__copy;
	__DUPARR(aliasName, OPS_Name);
	if (__STRCMP(name, "SYSTEM") == 0) {
		OPT_SYSimported = 1;
		OPT_Insert(aliasName, &obj);
		obj->mode = 11;
		obj->mnolev = 0;
		obj->scope = OPT_syslink;
		obj->typ = OPT_notyp;
	} else {
		OPT_impCtxt.nofr = 16;
		OPT_impCtxt.minr = 255;
		OPT_impCtxt.nofm = 0;
		OPT_impCtxt.self = __STRCMP(aliasName, "@self") == 0;
		OPT_impCtxt.reffp = 0;
		OPM_OldSym((void*)name, 32, &*done);
		if (*done) {
			OPT_InMod(&mno);
			OPT_impCtxt.nextTag = OPM_SymRInt();
			while (!OPM_eofSF()) {
				obj = OPT_InObj(mno);
				OPT_impCtxt.nextTag = OPM_SymRInt();
			}
			OPT_Insert(aliasName, &obj);
			obj->mode = 11;
			obj->scope = OPT_GlbMod[__X(mno, 64)]->right;
			OPT_GlbMod[__X(mno, 64)]->link = obj;
			obj->mnolev = -mno;
			obj->typ = OPT_notyp;
			OPM_CloseOldSym();
		} else if (OPT_impCtxt.self) {
			OPT_newsf = 1;
			OPT_extsf = 1;
			OPT_sfpresent = 0;
		} else {
			OPT_err(152);
		}
	}
}

static void OPT_OutName (CHAR *name, LONGINT name__len)
{
	INTEGER i;
	CHAR ch;
	i = 0;
	do {
		ch = name[__X(i, name__len)];
		OPM_SymWCh(ch);
		i += 1;
	} while (!(ch == 0x00));
}

static void OPT_OutMod (INTEGER mno)
{
	if (OPT_expCtxt.locmno[__X(mno, 64)] < 0) {
		OPM_SymWInt(16);
		OPT_expCtxt.locmno[__X(mno, 64)] = OPT_expCtxt.nofm;
		OPT_expCtxt.nofm += 1;
		OPT_OutName((void*)OPT_GlbMod[__X(mno, 64)]->name, 32);
	} else {
		OPM_SymWInt(-OPT_expCtxt.locmno[__X(mno, 64)]);
	}
}

static void OPT_OutHdFld (OPT_Struct typ, OPT_Object fld, LONGINT adr)
{
	LONGINT i, j, n;
	OPT_Struct btyp = NIL;
	if (typ->comp == 4) {
		OPT_OutFlds(typ->link, adr, 0);
	} else if (typ->comp == 2) {
		btyp = typ->BaseTyp;
		n = typ->n;
		while (btyp->comp == 2) {
			n = btyp->n * n;
			btyp = btyp->BaseTyp;
		}
		if (btyp->form == 13 || btyp->comp == 4) {
			j = OPT_nofhdfld;
			OPT_OutHdFld(btyp, fld, adr);
			if (j != OPT_nofhdfld) {
				i = 1;
				while ((i < n && OPT_nofhdfld <= 2048)) {
					adr += btyp->size;
					OPT_OutHdFld(btyp, fld, adr);
					i += 1;
				}
			}
		}
	} else if (typ->form == 13 || __STRCMP(fld->name, "@ptr") == 0) {
		OPM_SymWInt(27);
		OPM_SymWInt(adr);
		OPT_nofhdfld += 1;
	}
}

static void OPT_OutFlds (OPT_Object fld, LONGINT adr, BOOLEAN visible)
{
	while ((fld != NIL && fld->mode == 4)) {
		if ((fld->vis != 0 && visible)) {
			if (fld->vis == 2) {
				OPM_SymWInt(26);
			} else {
				OPM_SymWInt(25);
			}
			OPT_OutStr(fld->typ);
			OPT_OutName((void*)fld->name, 32);
			OPM_SymWInt(fld->adr);
		} else {
			OPT_OutHdFld(fld->typ, fld, fld->adr + adr);
		}
		fld = fld->link;
	}
}

static void OPT_OutSign (OPT_Struct result, OPT_Object par)
{
	OPT_OutStr(result);
	while (par != NIL) {
		if (par->mode == 1) {
			OPM_SymWInt(23);
		} else {
			OPM_SymWInt(24);
		}
		OPT_OutStr(par->typ);
		OPM_SymWInt(par->adr);
		OPT_OutName((void*)par->name, 32);
		par = par->link;
	}
	OPM_SymWInt(18);
}

static void OPT_OutTProcs (OPT_Struct typ, OPT_Object obj)
{
	if (obj != NIL) {
		OPT_OutTProcs(typ, obj->left);
		if (obj->mode == 13) {
			if ((((typ->BaseTyp != NIL && __ASHR(obj->adr, 16) < typ->BaseTyp->n)) && obj->vis == 0)) {
				OPM_Mark(109, typ->txtpos);
			}
			if (obj->vis != 0) {
				if (obj->vis != 0) {
					OPM_SymWInt(29);
					OPT_OutSign(obj->typ, obj->link);
					OPT_OutName((void*)obj->name, 32);
					OPM_SymWInt(__ASHR(obj->adr, 16));
				} else {
					OPM_SymWInt(30);
					OPM_SymWInt(__ASHR(obj->adr, 16));
				}
			}
		}
		OPT_OutTProcs(typ, obj->right);
	}
}

static void OPT_OutStr (OPT_Struct typ)
{
	OPT_Object strobj = NIL;
	if (typ->ref < OPT_expCtxt.ref) {
		OPM_SymWInt(-typ->ref);
	} else {
		OPM_SymWInt(34);
		typ->ref = OPT_expCtxt.ref;
		OPT_expCtxt.ref += 1;
		if (OPT_expCtxt.ref >= 255) {
			OPT_err(228);
		}
		OPT_OutMod(typ->mno);
		strobj = typ->strobj;
		if ((strobj != NIL && strobj->name[0] != 0x00)) {
			OPT_OutName((void*)strobj->name, 32);
			switch (strobj->history) {
				case 2: 
					OPT_FPrintErr(strobj, 252);
					break;
				case 3: 
					OPT_FPrintErr(strobj, 251);
					break;
				case 5: 
					OPT_FPrintErr(strobj, 249);
					break;
				default: 
					break;
			}
		} else {
			OPM_SymWCh(0x00);
		}
		if (typ->sysflag != 0) {
			OPM_SymWInt(35);
			OPM_SymWInt(typ->sysflag);
		}
		switch (typ->form) {
			case 13: 
				OPM_SymWInt(36);
				OPT_OutStr(typ->BaseTyp);
				break;
			case 14: 
				OPM_SymWInt(40);
				OPT_OutSign(typ->BaseTyp, typ->link);
				break;
			case 15: 
				switch (typ->comp) {
					case 2: 
						OPM_SymWInt(37);
						OPT_OutStr(typ->BaseTyp);
						OPM_SymWInt(typ->n);
						break;
					case 3: 
						OPM_SymWInt(38);
						OPT_OutStr(typ->BaseTyp);
						break;
					case 4: 
						OPM_SymWInt(39);
						if (typ->BaseTyp == NIL) {
							OPT_OutStr(OPT_notyp);
						} else {
							OPT_OutStr(typ->BaseTyp);
						}
						OPM_SymWInt(typ->size);
						OPM_SymWInt(typ->align);
						OPM_SymWInt(typ->n);
						OPT_nofhdfld = 0;
						OPT_OutFlds(typ->link, 0, 1);
						if (OPT_nofhdfld > 2048) {
							OPM_Mark(223, typ->txtpos);
						}
						OPT_OutTProcs(typ, typ->link);
						OPM_SymWInt(18);
						break;
					default: __CASECHK;
				}
				break;
			default: __CASECHK;
		}
	}
}

static void OPT_OutConstant (OPT_Object obj)
{
	INTEGER f;
	REAL rval;
	f = obj->typ->form;
	OPM_SymWInt(f);
	switch (f) {
		case 2: case 3: 
			OPM_SymWCh((CHAR)obj->conval->intval);
			break;
		case 4: case 5: case 6: 
			OPM_SymWInt(obj->conval->intval);
			break;
		case 9: 
			OPM_SymWSet(obj->conval->setval);
			break;
		case 7: 
			rval = obj->conval->realval;
			OPM_SymWReal(rval);
			break;
		case 8: 
			OPM_SymWLReal(obj->conval->realval);
			break;
		case 10: 
			OPT_OutName((void*)*obj->conval->ext, 256);
			break;
		case 11: 
			break;
		default: 
			OPT_err(127);
			break;
	}
}

static void OPT_OutObj (OPT_Object obj)
{
	INTEGER i, j;
	OPT_ConstExt ext = NIL;
	if (obj != NIL) {
		OPT_OutObj(obj->left);
		if (__IN(obj->mode, 0x06ea)) {
			if (obj->history == 4) {
				OPT_FPrintErr(obj, 250);
			} else if (obj->vis != 0) {
				switch (obj->history) {
					case 0: 
						OPT_FPrintErr(obj, 253);
						break;
					case 1: 
						break;
					case 2: 
						OPT_FPrintErr(obj, 252);
						break;
					case 3: 
						OPT_FPrintErr(obj, 251);
						break;
					default: __CASECHK;
				}
				switch (obj->mode) {
					case 3: 
						OPT_OutConstant(obj);
						OPT_OutName((void*)obj->name, 32);
						break;
					case 5: 
						if (obj->typ->strobj == obj) {
							OPM_SymWInt(19);
							OPT_OutStr(obj->typ);
						} else {
							OPM_SymWInt(20);
							OPT_OutStr(obj->typ);
							OPT_OutName((void*)obj->name, 32);
						}
						break;
					case 1: 
						if (obj->vis == 2) {
							OPM_SymWInt(22);
						} else {
							OPM_SymWInt(21);
						}
						OPT_OutStr(obj->typ);
						OPT_OutName((void*)obj->name, 32);
						if (obj->typ->strobj == NIL || obj->typ->strobj->name[0] == 0x00) {
							OPM_FPrint(&OPT_expCtxt.reffp, obj->typ->ref);
						}
						break;
					case 7: 
						OPM_SymWInt(31);
						OPT_OutSign(obj->typ, obj->link);
						OPT_OutName((void*)obj->name, 32);
						break;
					case 10: 
						OPM_SymWInt(32);
						OPT_OutSign(obj->typ, obj->link);
						OPT_OutName((void*)obj->name, 32);
						break;
					case 9: 
						OPM_SymWInt(33);
						OPT_OutSign(obj->typ, obj->link);
						ext = obj->conval->ext;
						j = (int)(*ext)[0];
						i = 1;
						OPM_SymWInt(j);
						while (i <= j) {
							OPM_SymWCh((*ext)[__X(i, 256)]);
							i += 1;
						}
						OPT_OutName((void*)obj->name, 32);
						break;
					default: __CASECHK;
				}
			}
		}
		OPT_OutObj(obj->right);
	}
}

void OPT_Export (BOOLEAN *ext, BOOLEAN *new)
{
	INTEGER i;
	SHORTINT nofmod;
	BOOLEAN done;
	OPT_symExtended = 0;
	OPT_symNew = 0;
	nofmod = OPT_nofGmod;
	OPT_Import((CHAR*)"@self", OPT_SelfName, &done);
	OPT_nofGmod = nofmod;
	if (OPM_noerr) {
		OPM_NewSym((void*)OPT_SelfName, 32);
		if (OPM_noerr) {
			OPM_SymWInt(16);
			OPT_OutName((void*)OPT_SelfName, 32);
			OPT_expCtxt.reffp = 0;
			OPT_expCtxt.ref = 16;
			OPT_expCtxt.nofm = 1;
			OPT_expCtxt.locmno[0] = 0;
			i = 1;
			while (i < 64) {
				OPT_expCtxt.locmno[__X(i, 64)] = -1;
				i += 1;
			}
			OPT_OutObj(OPT_topScope->right);
			*ext = (OPT_sfpresent && OPT_symExtended);
			*new = !OPT_sfpresent || OPT_symNew;
			if ((((OPM_noerr && OPT_sfpresent)) && OPT_impCtxt.reffp != OPT_expCtxt.reffp)) {
				*new = 1;
				if (!OPT_extsf) {
					OPT_err(155);
				}
			}
			OPT_newsf = 0;
			OPT_symNew = 0;
			if (!OPM_noerr || OPT_findpc) {
				OPM_DeleteNewSym();
			}
		}
	}
}

static void OPT_InitStruct (OPT_Struct *typ, SHORTINT form)
{
	*typ = OPT_NewStr(form, 1);
	(*typ)->ref = form;
	(*typ)->size = OPM_ByteSize;
	(*typ)->allocated = 1;
	(*typ)->strobj = OPT_NewObj();
	(*typ)->pbfp = form;
	(*typ)->pvfp = form;
	(*typ)->fpdone = 1;
	(*typ)->idfp = form;
	(*typ)->idfpdone = 1;
}

static void OPT_EnterBoolConst (OPS_Name name, LONGINT value)
{
	OPT_Object obj = NIL;
	OPS_Name name__copy;
	__DUPARR(name, OPS_Name);
	OPT_Insert(name, &obj);
	obj->conval = OPT_NewConst();
	obj->mode = 3;
	obj->typ = OPT_booltyp;
	obj->conval->intval = value;
}

static void OPT_EnterTyp (OPS_Name name, SHORTINT form, INTEGER size, OPT_Struct *res)
{
	OPT_Object obj = NIL;
	OPT_Struct typ = NIL;
	OPS_Name name__copy;
	__DUPARR(name, OPS_Name);
	OPT_Insert(name, &obj);
	typ = OPT_NewStr(form, 1);
	obj->mode = 5;
	obj->typ = typ;
	obj->vis = 1;
	typ->strobj = obj;
	typ->size = size;
	typ->ref = form;
	typ->allocated = 1;
	typ->pbfp = form;
	typ->pvfp = form;
	typ->fpdone = 1;
	typ->idfp = form;
	typ->idfpdone = 1;
	*res = typ;
}

static void OPT_EnterProc (OPS_Name name, INTEGER num)
{
	OPT_Object obj = NIL;
	OPS_Name name__copy;
	__DUPARR(name, OPS_Name);
	OPT_Insert(name, &obj);
	obj->mode = 8;
	obj->typ = OPT_notyp;
	obj->adr = num;
}

static void EnumPtrs(void (*P)(void*))
{
	P(OPT_topScope);
	P(OPT_undftyp);
	P(OPT_bytetyp);
	P(OPT_booltyp);
	P(OPT_chartyp);
	P(OPT_sinttyp);
	P(OPT_inttyp);
	P(OPT_linttyp);
	P(OPT_realtyp);
	P(OPT_lrltyp);
	P(OPT_settyp);
	P(OPT_stringtyp);
	P(OPT_niltyp);
	P(OPT_notyp);
	P(OPT_sysptrtyp);
	__ENUMP(OPT_GlbMod, 64, P);
	P(OPT_universe);
	P(OPT_syslink);
	__ENUMR(&OPT_impCtxt, OPT_ImpCtxt__typ, 6216, 1, P);
}

__TDESC(OPT_ConstDesc, 1, 1) = {__TDFLDS("ConstDesc", 40), {0, -16}};
__TDESC(OPT_ObjDesc, 1, 6) = {__TDFLDS("ObjDesc", 120), {0, 8, 16, 24, 80, 88, -56}};
__TDESC(OPT_StrDesc, 1, 3) = {__TDFLDS("StrDesc", 104), {80, 88, 96, -32}};
__TDESC(OPT_NodeDesc, 1, 6) = {__TDFLDS("NodeDesc", 56), {0, 8, 16, 32, 40, 48, -56}};
__TDESC(OPT_ImpCtxt, 1, 510) = {__TDFLDS("ImpCtxt", 6216), {32, 40, 48, 56, 64, 72, 80, 88, 96, 104, 112, 120, 128, 136, 144, 152, 
	160, 168, 176, 184, 192, 200, 208, 216, 224, 232, 240, 248, 256, 264, 272, 280, 
	288, 296, 304, 312, 320, 328, 336, 344, 352, 360, 368, 376, 384, 392, 400, 408, 
	416, 424, 432, 440, 448, 456, 464, 472, 480, 488, 496, 504, 512, 520, 528, 536, 
	544, 552, 560, 568, 576, 584, 592, 600, 608, 616, 624, 632, 640, 648, 656, 664, 
	672, 680, 688, 696, 704, 712, 720, 728, 736, 744, 752, 760, 768, 776, 784, 792, 
	800, 808, 816, 824, 832, 840, 848, 856, 864, 872, 880, 888, 896, 904, 912, 920, 
	928, 936, 944, 952, 960, 968, 976, 984, 992, 1000, 1008, 1016, 1024, 1032, 1040, 1048, 
	1056, 1064, 1072, 1080, 1088, 1096, 1104, 1112, 1120, 1128, 1136, 1144, 1152, 1160, 1168, 1176, 
	1184, 1192, 1200, 1208, 1216, 1224, 1232, 1240, 1248, 1256, 1264, 1272, 1280, 1288, 1296, 1304, 
	1312, 1320, 1328, 1336, 1344, 1352, 1360, 1368, 1376, 1384, 1392, 1400, 1408, 1416, 1424, 1432, 
	1440, 1448, 1456, 1464, 1472, 1480, 1488, 1496, 1504, 1512, 1520, 1528, 1536, 1544, 1552, 1560, 
	1568, 1576, 1584, 1592, 1600, 1608, 1616, 1624, 1632, 1640, 1648, 1656, 1664, 1672, 1680, 1688, 
	1696, 1704, 1712, 1720, 1728, 1736, 1744, 1752, 1760, 1768, 1776, 1784, 1792, 1800, 1808, 1816, 
	1824, 1832, 1840, 1848, 1856, 1864, 1872, 1880, 1888, 1896, 1904, 1912, 1920, 1928, 1936, 1944, 
	1952, 1960, 1968, 1976, 1984, 1992, 2000, 2008, 2016, 2024, 2032, 2040, 2048, 2056, 2064, 2072, 
	2080, 2088, 2096, 2104, 2112, 2120, 2128, 2136, 2144, 2152, 2160, 2168, 2176, 2184, 2192, 2200, 
	2208, 2216, 2224, 2232, 2240, 2248, 2256, 2264, 2272, 2280, 2288, 2296, 2304, 2312, 2320, 2328, 
	2336, 2344, 2352, 2360, 2368, 2376, 2384, 2392, 2400, 2408, 2416, 2424, 2432, 2440, 2448, 2456, 
	2464, 2472, 2480, 2488, 2496, 2504, 2512, 2520, 2528, 2536, 2544, 2552, 2560, 2568, 2576, 2584, 
	2592, 2600, 2608, 2616, 2624, 2632, 2640, 2648, 2656, 2664, 2672, 2680, 2688, 2696, 2704, 2712, 
	2720, 2728, 2736, 2744, 2752, 2760, 2768, 2776, 2784, 2792, 2800, 2808, 2816, 2824, 2832, 2840, 
	2848, 2856, 2864, 2872, 2880, 2888, 2896, 2904, 2912, 2920, 2928, 2936, 2944, 2952, 2960, 2968, 
	2976, 2984, 2992, 3000, 3008, 3016, 3024, 3032, 3040, 3048, 3056, 3064, 3072, 3080, 3088, 3096, 
	3104, 3112, 3120, 3128, 3136, 3144, 3152, 3160, 3168, 3176, 3184, 3192, 3200, 3208, 3216, 3224, 
	3232, 3240, 3248, 3256, 3264, 3272, 3280, 3288, 3296, 3304, 3312, 3320, 3328, 3336, 3344, 3352, 
	3360, 3368, 3376, 3384, 3392, 3400, 3408, 3416, 3424, 3432, 3440, 3448, 3456, 3464, 3472, 3480, 
	3488, 3496, 3504, 3512, 3520, 3528, 3536, 3544, 3552, 3560, 3568, 3576, 3584, 3592, 3600, 3608, 
	3616, 3624, 3632, 3640, 3648, 3656, 3664, 3672, 3680, 3688, 3696, 3704, 3712, 3720, 3728, 3736, 
	3744, 3752, 3760, 3768, 3776, 3784, 3792, 3800, 3808, 3816, 3824, 3832, 3840, 3848, 3856, 3864, 
	3872, 3880, 3888, 3896, 3904, 3912, 3920, 3928, 3936, 3944, 3952, 3960, 3968, 3976, 3984, 3992, 
	4000, 4008, 4016, 4024, 4032, 4040, 4048, 4056, 4064, 4072, 4080, 4088, 4096, 4104, -4088}};
__TDESC(OPT_ExpCtxt, 1, 0) = {__TDFLDS("ExpCtxt", 80), {-8}};

export void *OPT__init(void)
{
	__DEFMOD;
	__IMPORT(OPM);
	__IMPORT(OPS);
	__REGMOD("OPT", EnumPtrs);
	__REGCMD("Close", OPT_Close);
	__REGCMD("CloseScope", OPT_CloseScope);
	__INITYP(OPT_ConstDesc, OPT_ConstDesc, 0);
	__INITYP(OPT_ObjDesc, OPT_ObjDesc, 0);
	__INITYP(OPT_StrDesc, OPT_StrDesc, 0);
	__INITYP(OPT_NodeDesc, OPT_NodeDesc, 0);
	__INITYP(OPT_ImpCtxt, OPT_ImpCtxt, 0);
	__INITYP(OPT_ExpCtxt, OPT_ExpCtxt, 0);
/* BEGIN */
	OPT_topScope = NIL;
	OPT_OpenScope(0, NIL);
	OPM_errpos = 0;
	OPT_InitStruct(&OPT_undftyp, 0);
	OPT_InitStruct(&OPT_notyp, 12);
	OPT_InitStruct(&OPT_stringtyp, 10);
	OPT_InitStruct(&OPT_niltyp, 11);
	OPT_undftyp->BaseTyp = OPT_undftyp;
	OPT_EnterTyp((CHAR*)"BYTE", 1, OPM_ByteSize, &OPT_bytetyp);
	OPT_EnterTyp((CHAR*)"PTR", 13, OPM_PointerSize, &OPT_sysptrtyp);
	OPT_EnterProc((CHAR*)"ADR", 20);
	OPT_EnterProc((CHAR*)"CC", 21);
	OPT_EnterProc((CHAR*)"LSH", 22);
	OPT_EnterProc((CHAR*)"ROT", 23);
	OPT_EnterProc((CHAR*)"GET", 24);
	OPT_EnterProc((CHAR*)"PUT", 25);
	OPT_EnterProc((CHAR*)"GETREG", 26);
	OPT_EnterProc((CHAR*)"PUTREG", 27);
	OPT_EnterProc((CHAR*)"BIT", 28);
	OPT_EnterProc((CHAR*)"VAL", 29);
	OPT_EnterProc((CHAR*)"NEW", 30);
	OPT_EnterProc((CHAR*)"MOVE", 31);
	OPT_syslink = OPT_topScope->right;
	OPT_universe = OPT_topScope;
	OPT_topScope->right = NIL;
	OPT_EnterTyp((CHAR*)"CHAR", 3, OPM_CharSize, &OPT_chartyp);
	OPT_EnterTyp((CHAR*)"SET", 9, OPM_SetSize, &OPT_settyp);
	OPT_EnterTyp((CHAR*)"REAL", 7, OPM_RealSize, &OPT_realtyp);
	OPT_EnterTyp((CHAR*)"INTEGER", 5, OPM_IntSize, &OPT_inttyp);
	OPT_EnterTyp((CHAR*)"LONGINT", 6, OPM_LIntSize, &OPT_linttyp);
	OPT_EnterTyp((CHAR*)"LONGREAL", 8, OPM_LRealSize, &OPT_lrltyp);
	OPT_EnterTyp((CHAR*)"SHORTINT", 4, OPM_SIntSize, &OPT_sinttyp);
	OPT_EnterTyp((CHAR*)"BOOLEAN", 2, OPM_BoolSize, &OPT_booltyp);
	OPT_EnterBoolConst((CHAR*)"FALSE", 0);
	OPT_EnterBoolConst((CHAR*)"TRUE", 1);
	OPT_EnterProc((CHAR*)"HALT", 0);
	OPT_EnterProc((CHAR*)"NEW", 1);
	OPT_EnterProc((CHAR*)"ABS", 2);
	OPT_EnterProc((CHAR*)"CAP", 3);
	OPT_EnterProc((CHAR*)"ORD", 4);
	OPT_EnterProc((CHAR*)"ENTIER", 5);
	OPT_EnterProc((CHAR*)"ODD", 6);
	OPT_EnterProc((CHAR*)"MIN", 7);
	OPT_EnterProc((CHAR*)"MAX", 8);
	OPT_EnterProc((CHAR*)"CHR", 9);
	OPT_EnterProc((CHAR*)"SHORT", 10);
	OPT_EnterProc((CHAR*)"LONG", 11);
	OPT_EnterProc((CHAR*)"SIZE", 12);
	OPT_EnterProc((CHAR*)"INC", 13);
	OPT_EnterProc((CHAR*)"DEC", 14);
	OPT_EnterProc((CHAR*)"INCL", 15);
	OPT_EnterProc((CHAR*)"EXCL", 16);
	OPT_EnterProc((CHAR*)"LEN", 17);
	OPT_EnterProc((CHAR*)"COPY", 18);
	OPT_EnterProc((CHAR*)"ASH", 19);
	OPT_EnterProc((CHAR*)"ASSERT", 32);
	OPT_impCtxt.ref[0] = OPT_undftyp;
	OPT_impCtxt.ref[1] = OPT_bytetyp;
	OPT_impCtxt.ref[2] = OPT_booltyp;
	OPT_impCtxt.ref[3] = OPT_chartyp;
	OPT_impCtxt.ref[4] = OPT_sinttyp;
	OPT_impCtxt.ref[5] = OPT_inttyp;
	OPT_impCtxt.ref[6] = OPT_linttyp;
	OPT_impCtxt.ref[7] = OPT_realtyp;
	OPT_impCtxt.ref[8] = OPT_lrltyp;
	OPT_impCtxt.ref[9] = OPT_settyp;
	OPT_impCtxt.ref[10] = OPT_stringtyp;
	OPT_impCtxt.ref[11] = OPT_niltyp;
	OPT_impCtxt.ref[12] = OPT_notyp;
	OPT_impCtxt.ref[13] = OPT_sysptrtyp;
	__ENDMOD;
}
