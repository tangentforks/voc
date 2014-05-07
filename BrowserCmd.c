/* voc  1.0  [2013/09/23] xtspkamPS */
#include "SYSTEM.h"
#include "Args.h"
#include "Console.h"
#include "OPM.h"
#include "OPS.h"
#include "OPT.h"
#include "OPV.h"
#include "Texts0.h"


static Texts0_Writer BrowserCmd_W;
static CHAR BrowserCmd_option;


static void BrowserCmd_Ident (CHAR *name, LONGINT name__len, CHAR *first, LONGINT first__len);
static void BrowserCmd_Indent (INTEGER i);
static void BrowserCmd_Objects (OPT_Object obj, SET mode);
export void BrowserCmd_ShowDef (void);
static void BrowserCmd_WModule (OPS_Name name, Texts0_Text T);
static void BrowserCmd_Wch (CHAR ch);
static void BrowserCmd_Wi (LONGINT i);
static void BrowserCmd_Wln (void);
static void BrowserCmd_Wmthd (OPT_Object obj);
static void BrowserCmd_Ws (CHAR *s, LONGINT s__len);
static void BrowserCmd_Wsign (OPT_Struct result, OPT_Object par);
static void BrowserCmd_Wstruct (OPT_Struct typ);
static void BrowserCmd_Wtype (OPT_Struct typ);


static void BrowserCmd_Ws (CHAR *s, LONGINT s__len)
{
	__DUP(s, s__len, CHAR);
	Texts0_WriteString(&BrowserCmd_W, Texts0_Writer__typ, s, s__len);
	__DEL(s);
}

static void BrowserCmd_Wch (CHAR ch)
{
	Texts0_Write(&BrowserCmd_W, Texts0_Writer__typ, ch);
}

static void BrowserCmd_Wi (LONGINT i)
{
	Texts0_WriteInt(&BrowserCmd_W, Texts0_Writer__typ, i, 0);
}

static void BrowserCmd_Wln (void)
{
	Texts0_WriteLn(&BrowserCmd_W, Texts0_Writer__typ);
}

static void BrowserCmd_Indent (INTEGER i)
{
	while (i > 0) {
		BrowserCmd_Wch(' ');
		BrowserCmd_Wch(' ');
		i -= 1;
	}
}

static void BrowserCmd_Wsign (OPT_Struct result, OPT_Object par)
{
	BOOLEAN paren, res, first;
	first = 1;
	res = (result != NIL && result != OPT_notyp);
	paren = res || par != NIL;
	if (paren) {
		BrowserCmd_Wch('(');
	}
	while (par != NIL) {
		if (!first) {
			BrowserCmd_Ws((CHAR*)"; ", (LONGINT)3);
		} else {
			first = 0;
		}
		if (BrowserCmd_option == 'x') {
			BrowserCmd_Wi(par->adr);
			BrowserCmd_Wch(' ');
		}
		if (par->mode == 2) {
			BrowserCmd_Ws((CHAR*)"VAR ", (LONGINT)5);
		}
		BrowserCmd_Ws(par->name, 32);
		BrowserCmd_Ws((CHAR*)": ", (LONGINT)3);
		BrowserCmd_Wtype(par->typ);
		par = par->link;
	}
	if (paren) {
		BrowserCmd_Wch(')');
	}
	if (res) {
		BrowserCmd_Ws((CHAR*)": ", (LONGINT)3);
		BrowserCmd_Wtype(result);
	}
}

static void BrowserCmd_Objects (OPT_Object obj, SET mode)
{
	LONGINT i;
	INTEGER m;
	SET s;
	OPT_ConstExt ext = NIL;
	if (obj != NIL) {
		BrowserCmd_Objects(obj->left, mode);
		if (__IN(obj->mode, mode)) {
			switch (obj->mode) {
				case 3: 
					BrowserCmd_Indent(2);
					BrowserCmd_Ws(obj->name, 32);
					BrowserCmd_Ws((CHAR*)" = ", (LONGINT)4);
					switch (obj->typ->form) {
						case 2: 
							if (obj->conval->intval == 1) {
								BrowserCmd_Ws((CHAR*)"TRUE", (LONGINT)5);
							} else {
								BrowserCmd_Ws((CHAR*)"FALSE", (LONGINT)6);
							}
							break;
						case 3: 
							if ((obj->conval->intval >= 32 && obj->conval->intval <= 126)) {
								BrowserCmd_Wch('\"');
								BrowserCmd_Wch((CHAR)obj->conval->intval);
								BrowserCmd_Wch('\"');
							} else {
								i = __ASHR(obj->conval->intval, 4);
								if (i > 9) {
									BrowserCmd_Wch((CHAR)(55 + i));
								} else {
									BrowserCmd_Wch((CHAR)(48 + i));
								}
								i = __MASK(obj->conval->intval, -16);
								if (i > 9) {
									BrowserCmd_Wch((CHAR)(55 + i));
								} else {
									BrowserCmd_Wch((CHAR)(48 + i));
								}
								BrowserCmd_Wch('X');
							}
							break;
						case 4: case 5: case 6: 
							BrowserCmd_Wi(obj->conval->intval);
							break;
						case 9: 
							BrowserCmd_Wch('{');
							i = 0;
							s = obj->conval->setval;
							while (i <= 63) {
								if (__IN(i, s)) {
									BrowserCmd_Wi(i);
									s &= ~__SETOF(i);
									if (s != 0x0) {
										BrowserCmd_Ws((CHAR*)", ", (LONGINT)3);
									}
								}
								i += 1;
							}
							BrowserCmd_Wch('}');
							break;
						case 7: 
							Texts0_WriteReal(&BrowserCmd_W, Texts0_Writer__typ, obj->conval->realval, 16);
							break;
						case 8: 
							Texts0_WriteLongReal(&BrowserCmd_W, Texts0_Writer__typ, obj->conval->realval, 23);
							break;
						case 10: 
							BrowserCmd_Ws(*obj->conval->ext, 256);
							break;
						case 11: 
							BrowserCmd_Ws((CHAR*)"NIL", (LONGINT)4);
							break;
						default: __CASECHK;
					}
					BrowserCmd_Wch(';');
					BrowserCmd_Wln();
					break;
				case 5: 
					if (obj->name[0] != 0x00) {
						BrowserCmd_Indent(2);
						if (obj->typ->strobj == obj) {
							BrowserCmd_Wtype(obj->typ);
							BrowserCmd_Ws((CHAR*)" = ", (LONGINT)4);
							BrowserCmd_Wstruct(obj->typ);
						} else {
							BrowserCmd_Ws(obj->name, 32);
							BrowserCmd_Ws((CHAR*)" = ", (LONGINT)4);
							BrowserCmd_Wtype(obj->typ);
						}
						BrowserCmd_Wch(';');
						BrowserCmd_Wln();
					}
					break;
				case 1: 
					BrowserCmd_Indent(2);
					BrowserCmd_Ws(obj->name, 32);
					if (obj->vis == 2) {
						BrowserCmd_Ws((CHAR*)"-: ", (LONGINT)4);
					} else {
						BrowserCmd_Ws((CHAR*)": ", (LONGINT)3);
					}
					BrowserCmd_Wtype(obj->typ);
					BrowserCmd_Wch(';');
					BrowserCmd_Wln();
					break;
				case 7: case 9: case 10: 
					BrowserCmd_Indent(1);
					BrowserCmd_Ws((CHAR*)"PROCEDURE ", (LONGINT)11);
					if (obj->mode == 10) {
						BrowserCmd_Wch('+');
					} else if (obj->mode == 9) {
						BrowserCmd_Wch('-');
					}
					BrowserCmd_Ws(obj->name, 32);
					BrowserCmd_Wsign(obj->typ, obj->link);
					if (obj->mode == 9) {
						ext = obj->conval->ext;
						m = (int)(*ext)[0];
						i = 1;
						BrowserCmd_Ws((CHAR*)"  \"", (LONGINT)4);
						while (i <= (LONGINT)m) {
							BrowserCmd_Wch((*ext)[__X(i, 256)]);
							i += 1;
						}
						BrowserCmd_Wch('\"');
					}
					BrowserCmd_Wch(';');
					BrowserCmd_Wln();
					break;
				default: __CASECHK;
			}
		}
		BrowserCmd_Objects(obj->right, mode);
	}
}

static void BrowserCmd_Wmthd (OPT_Object obj)
{
	if (obj != NIL) {
		BrowserCmd_Wmthd(obj->left);
		if ((obj->mode == 13 && (__STRCMP(obj->name, "@tproc") != 0 || BrowserCmd_option == 'x'))) {
			BrowserCmd_Indent(3);
			BrowserCmd_Ws((CHAR*)"PROCEDURE (", (LONGINT)12);
			if (__STRCMP(obj->name, "@tproc") != 0) {
				if (obj->link->mode == 2) {
					BrowserCmd_Ws((CHAR*)"VAR ", (LONGINT)5);
				}
				BrowserCmd_Ws(obj->link->name, 32);
				BrowserCmd_Ws((CHAR*)": ", (LONGINT)3);
				BrowserCmd_Wtype(obj->link->typ);
			}
			BrowserCmd_Ws((CHAR*)") ", (LONGINT)3);
			BrowserCmd_Ws(obj->name, 32);
			BrowserCmd_Wsign(obj->typ, obj->link->link);
			BrowserCmd_Wch(';');
			if (BrowserCmd_option == 'x') {
				BrowserCmd_Indent(1);
				BrowserCmd_Ws((CHAR*)"(* methno: ", (LONGINT)12);
				BrowserCmd_Wi(__ASHR(obj->adr, 16));
				BrowserCmd_Ws((CHAR*)" *)", (LONGINT)4);
			}
			BrowserCmd_Wln();
		}
		BrowserCmd_Wmthd(obj->right);
	}
}

static struct Wstruct__16 {
	OPT_Struct *typ;
	struct Wstruct__16 *lnk;
} *Wstruct__16_s;

static void SysFlag__17 (void);

static void SysFlag__17 (void)
{
	if ((*Wstruct__16_s->typ)->sysflag != 0) {
		BrowserCmd_Wch('[');
		BrowserCmd_Wi((*Wstruct__16_s->typ)->sysflag);
		BrowserCmd_Ws((CHAR*)"] ", (LONGINT)3);
	}
}

static void BrowserCmd_Wstruct (OPT_Struct typ)
{
	OPT_Object fld = NIL;
	struct Wstruct__16 _s;
	_s.typ = &typ;
	_s.lnk = Wstruct__16_s;
	Wstruct__16_s = &_s;
	switch (typ->form) {
		case 0: 
			BrowserCmd_Ws((CHAR*)"Undef", (LONGINT)6);
			break;
		case 13: 
			BrowserCmd_Ws((CHAR*)"POINTER ", (LONGINT)9);
			SysFlag__17();
			BrowserCmd_Ws((CHAR*)"TO ", (LONGINT)4);
			BrowserCmd_Wtype(typ->BaseTyp);
			break;
		case 14: 
			BrowserCmd_Ws((CHAR*)"PROCEDURE ", (LONGINT)11);
			SysFlag__17();
			BrowserCmd_Wsign(typ->BaseTyp, typ->link);
			break;
		case 15: 
			switch (typ->comp) {
				case 2: 
					BrowserCmd_Ws((CHAR*)"ARRAY ", (LONGINT)7);
					SysFlag__17();
					BrowserCmd_Wi(typ->n);
					BrowserCmd_Ws((CHAR*)" OF ", (LONGINT)5);
					BrowserCmd_Wtype(typ->BaseTyp);
					break;
				case 3: 
					BrowserCmd_Ws((CHAR*)"ARRAY ", (LONGINT)7);
					SysFlag__17();
					BrowserCmd_Ws((CHAR*)"OF ", (LONGINT)4);
					BrowserCmd_Wtype(typ->BaseTyp);
					break;
				case 4: 
					BrowserCmd_Ws((CHAR*)"RECORD ", (LONGINT)8);
					SysFlag__17();
					if (typ->BaseTyp != NIL) {
						BrowserCmd_Wch('(');
						BrowserCmd_Wtype(typ->BaseTyp);
						BrowserCmd_Wch(')');
					}
					BrowserCmd_Wln();
					fld = typ->link;
					while ((fld != NIL && fld->mode == 4)) {
						if (BrowserCmd_option == 'x' || fld->name[0] != '@') {
							BrowserCmd_Indent(3);
							if (BrowserCmd_option == 'x') {
								BrowserCmd_Wi(fld->adr);
								BrowserCmd_Wch(' ');
							}
							BrowserCmd_Ws(fld->name, 32);
							if (fld->vis == 2) {
								BrowserCmd_Wch('-');
							}
							BrowserCmd_Ws((CHAR*)": ", (LONGINT)3);
							BrowserCmd_Wtype(fld->typ);
							BrowserCmd_Wch(';');
							BrowserCmd_Wln();
						}
						fld = fld->link;
					}
					BrowserCmd_Wmthd(typ->link);
					BrowserCmd_Indent(2);
					BrowserCmd_Ws((CHAR*)"END ", (LONGINT)5);
					if (BrowserCmd_option == 'x') {
						BrowserCmd_Indent(1);
						BrowserCmd_Ws((CHAR*)"(* size: ", (LONGINT)10);
						BrowserCmd_Wi(typ->size);
						BrowserCmd_Ws((CHAR*)" align: ", (LONGINT)9);
						BrowserCmd_Wi(typ->align);
						BrowserCmd_Ws((CHAR*)" nofm: ", (LONGINT)8);
						BrowserCmd_Wi(typ->n);
						BrowserCmd_Ws((CHAR*)" *)", (LONGINT)4);
					}
					break;
				default: __CASECHK;
			}
			break;
		default: __CASECHK;
	}
	Wstruct__16_s = _s.lnk;
}

static void BrowserCmd_Wtype (OPT_Struct typ)
{
	OPT_Object obj = NIL;
	obj = typ->strobj;
	if (obj->name[0] != 0x00) {
		if (typ->mno != 0) {
			BrowserCmd_Ws(OPT_GlbMod[__X(typ->mno, 64)]->name, 32);
			BrowserCmd_Wch('.');
		} else if (typ == OPT_bytetyp || typ == OPT_sysptrtyp) {
			BrowserCmd_Ws((CHAR*)"SYSTEM.", (LONGINT)8);
		} else if (obj->vis == 0) {
			BrowserCmd_Wch('#');
		}
		BrowserCmd_Ws(obj->name, 32);
	} else {
		if ((BrowserCmd_option == 'x' && typ->ref > 255)) {
			BrowserCmd_Wch('#');
			BrowserCmd_Wi(typ->ref - 255);
			BrowserCmd_Wch(' ');
		}
		BrowserCmd_Wstruct(typ);
	}
}

static struct WModule__5 {
	Texts0_Text *T;
	LONGINT *beg, *end;
	struct WModule__5 *lnk;
} *WModule__5_s;

static void CheckHeader__6 (void);
static void Header__8 (CHAR *s, LONGINT s__len);

static void Header__8 (CHAR *s, LONGINT s__len)
{
	__DUP(s, s__len, CHAR);
	*WModule__5_s->beg = BrowserCmd_W.buf->len;
	BrowserCmd_Indent(1);
	BrowserCmd_Ws(s, s__len);
	BrowserCmd_Wln();
	*WModule__5_s->end = BrowserCmd_W.buf->len;
	__DEL(s);
}

static void CheckHeader__6 (void)
{
	LONGINT len;
	len = (*WModule__5_s->T)->len;
	if (*WModule__5_s->end == BrowserCmd_W.buf->len) {
		Texts0_Append(*WModule__5_s->T, BrowserCmd_W.buf);
		Texts0_Delete(*WModule__5_s->T, len + *WModule__5_s->beg, len + *WModule__5_s->end);
	} else {
		BrowserCmd_Wln();
	}
}

static void BrowserCmd_WModule (OPS_Name name, Texts0_Text T)
{
	INTEGER i;
	LONGINT beg, end;
	BOOLEAN first, done;
	struct WModule__5 _s;
	OPS_Name name__copy;
	__DUPARR(name, OPS_Name);
	_s.T = &T;
	_s.beg = &beg;
	_s.end = &end;
	_s.lnk = WModule__5_s;
	WModule__5_s = &_s;
	OPT_Import((CHAR*)"@notself", name, &done);
	if (done) {
		BrowserCmd_Ws((CHAR*)"DEFINITION ", (LONGINT)12);
		BrowserCmd_Ws(name, 32);
		BrowserCmd_Wch(';');
		BrowserCmd_Wln();
		BrowserCmd_Wln();
		Header__8((CHAR*)"IMPORT", (LONGINT)7);
		i = 1;
		first = 1;
		while (i < (int)OPT_nofGmod) {
			if (first) {
				first = 0;
				BrowserCmd_Indent(2);
			} else {
				BrowserCmd_Ws((CHAR*)", ", (LONGINT)3);
			}
			BrowserCmd_Ws(OPT_GlbMod[__X(i, 64)]->name, 32);
			i += 1;
		}
		if (!first) {
			BrowserCmd_Wch(';');
			BrowserCmd_Wln();
		}
		CheckHeader__6();
		Header__8((CHAR*)"CONST", (LONGINT)6);
		BrowserCmd_Objects(OPT_GlbMod[0]->right, 0x08);
		CheckHeader__6();
		Header__8((CHAR*)"TYPE", (LONGINT)5);
		BrowserCmd_Objects(OPT_GlbMod[0]->right, 0x20);
		CheckHeader__6();
		Header__8((CHAR*)"VAR", (LONGINT)4);
		BrowserCmd_Objects(OPT_GlbMod[0]->right, 0x02);
		CheckHeader__6();
		BrowserCmd_Objects(OPT_GlbMod[0]->right, 0x0680);
		BrowserCmd_Wln();
		BrowserCmd_Ws((CHAR*)"END ", (LONGINT)5);
		BrowserCmd_Ws(name, 32);
		BrowserCmd_Wch('.');
		BrowserCmd_Wln();
		Texts0_Append(T, BrowserCmd_W.buf);
	} else {
		Texts0_WriteString(&BrowserCmd_W, Texts0_Writer__typ, name, 32);
		Texts0_WriteString(&BrowserCmd_W, Texts0_Writer__typ, (CHAR*)" -- symbol file not found", (LONGINT)26);
		Texts0_WriteLn(&BrowserCmd_W, Texts0_Writer__typ);
		Texts0_Append(T, BrowserCmd_W.buf);
	}
	WModule__5_s = _s.lnk;
}

static void BrowserCmd_Ident (CHAR *name, LONGINT name__len, CHAR *first, LONGINT first__len)
{
	INTEGER i, j;
	CHAR ch;
	i = 0;
	while (name[__X(i, name__len)] != 0x00) {
		i += 1;
	}
	while ((i >= 0 && name[__X(i, name__len)] != '/')) {
		i -= 1;
	}
	i += 1;
	j = 0;
	ch = name[__X(i, name__len)];
	while ((ch != '.' && ch != 0x00)) {
		first[__X(j, first__len)] = ch;
		i += 1;
		j += 1;
		ch = name[__X(i, name__len)];
	}
	first[__X(j, first__len)] = 0x00;
}

void BrowserCmd_ShowDef (void)
{
	Texts0_Text T = NIL, dummyT = NIL;
	OPS_Name S, vname, name;
	Texts0_Reader R;
	CHAR ch;
	CHAR s[1024];
	INTEGER i;
	BrowserCmd_option = 0x00;
	Args_Get(1, (void*)S, 32);
	if (Args_argc > 2) {
		if (S[0] == '-') {
			BrowserCmd_option = S[1];
			Args_Get(2, (void*)S, 32);
		} else {
			Args_Get(2, (void*)vname, 32);
			BrowserCmd_option = vname[1];
		}
	}
	if (Args_argc >= 2) {
		BrowserCmd_Ident((void*)S, 32, (void*)name, 32);
		__NEW(T, Texts0_TextDesc);
		Texts0_Open(T, (CHAR*)"", (LONGINT)1);
		OPT_Init(name, 0x0);
		__MOVE("AvoidErr154", OPT_SelfName, 12);
		BrowserCmd_WModule(name, T);
		OPT_Close();
		Texts0_OpenReader(&R, Texts0_Reader__typ, T, 0);
		Texts0_Read(&R, Texts0_Reader__typ, &ch);
		i = 0;
		while (!R.eot) {
			if (ch == 0x0d) {
				s[__X(i, 1024)] = 0x00;
				i = 0;
				Console_String(s, 1024);
				Console_Ln();
			} else {
				s[__X(i, 1024)] = ch;
				i += 1;
			}
			Texts0_Read(&R, Texts0_Reader__typ, &ch);
		}
		s[__X(i, 1024)] = 0x00;
		Console_String(s, 1024);
	}
}

static void EnumPtrs(void (*P)(void*))
{
	__ENUMR(&BrowserCmd_W, Texts0_Writer__typ, 72, 1, P);
}


export main(int argc, char **argv)
{
	__INIT(argc, argv);
	__IMPORT(Args);
	__IMPORT(Console);
	__IMPORT(OPM);
	__IMPORT(OPS);
	__IMPORT(OPT);
	__IMPORT(OPV);
	__IMPORT(Texts0);
	__REGMAIN("BrowserCmd", EnumPtrs);
	__REGCMD("ShowDef", BrowserCmd_ShowDef);
/* BEGIN */
	OPT_typSize = OPV_TypSize;
	Texts0_OpenWriter(&BrowserCmd_W, Texts0_Writer__typ);
	BrowserCmd_ShowDef();
	__FINI;
}
