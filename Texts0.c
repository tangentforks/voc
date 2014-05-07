/* voc  1.0  [2013/09/23] xtspkaPS */
#include "SYSTEM.h"
#include "Files0.h"
#include "Modules.h"
#include "Reals.h"

typedef
	struct Texts0_RunDesc *Texts0_Run;

typedef
	struct Texts0_FontDesc *Texts0_FontsFont;

typedef
	struct Texts0_RunDesc {
		Texts0_Run prev, next;
		LONGINT len;
		Texts0_FontsFont fnt;
		SHORTINT col, voff;
		BOOLEAN ascii;
	} Texts0_RunDesc;

typedef
	struct Texts0_ElemDesc *Texts0_Elem;

typedef
	struct Texts0_ElemMsg {
		char _prvt0[1];
	} Texts0_ElemMsg;

typedef
	void (*Texts0_Handler)(Texts0_Elem, Texts0_ElemMsg*, LONGINT *);

typedef
	struct Texts0_TextDesc *Texts0_Text;

typedef
	struct Texts0_ElemDesc {
		Texts0_Run prev, next;
		LONGINT len;
		Texts0_FontsFont fnt;
		SHORTINT col, voff;
		BOOLEAN ascii;
		LONGINT W, H;
		Texts0_Handler handle;
		Texts0_Text base;
	} Texts0_ElemDesc;

struct Texts0__1 { /* Texts0_ElemDesc */
	Texts0_Run prev, next;
	LONGINT len;
	Texts0_FontsFont fnt;
	SHORTINT col, voff;
	BOOLEAN ascii;
	LONGINT W, H;
	Texts0_Handler handle;
	Texts0_Text base;
	Files0_File file;
	LONGINT org, span;
	CHAR mod[32], proc[32];
};

typedef
	struct Texts0__1 *Texts0_Alien;

typedef
	struct Texts0_BufDesc {
		LONGINT len;
		Texts0_Run head;
	} Texts0_BufDesc;

typedef
	Texts0_BufDesc *Texts0_Buffer;

typedef
	struct Texts0_CopyMsg { /* Texts0_ElemMsg */
		Texts0_Elem e;
	} Texts0_CopyMsg;

typedef
	struct Texts0_FileMsg { /* Texts0_ElemMsg */
		INTEGER id;
		LONGINT pos;
		Files0_Rider r;
	} Texts0_FileMsg;

typedef
	struct Texts0_FontDesc {
		CHAR name[32];
	} Texts0_FontDesc;

typedef
	struct Texts0_IdentifyMsg { /* Texts0_ElemMsg */
		CHAR mod[32], proc[32];
	} Texts0_IdentifyMsg;

typedef
	struct Texts0_PieceDesc *Texts0_Piece;

typedef
	struct Texts0_PieceDesc {
		Texts0_Run prev, next;
		LONGINT len;
		Texts0_FontsFont fnt;
		SHORTINT col, voff;
		BOOLEAN ascii;
		Files0_File file;
		LONGINT org;
	} Texts0_PieceDesc;

typedef
	struct Texts0_Reader {
		BOOLEAN eot;
		Texts0_FontsFont fnt;
		SHORTINT col, voff;
		Texts0_Elem elem;
		Files0_Rider rider;
		Texts0_Run run;
		LONGINT org, off;
	} Texts0_Reader;

typedef
	struct Texts0_Scanner { /* Texts0_Reader */
		BOOLEAN eot;
		Texts0_FontsFont fnt;
		SHORTINT col, voff;
		Texts0_Elem elem;
		Files0_Rider rider;
		Texts0_Run run;
		LONGINT org, off;
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
	struct Texts0_TextDesc {
		LONGINT len;
		Texts0_Run head, cache;
		LONGINT corg;
	} Texts0_TextDesc;

typedef
	struct Texts0_Writer {
		Texts0_Buffer buf;
		Texts0_FontsFont fnt;
		SHORTINT col, voff;
		Files0_Rider rider;
		Files0_File file;
	} Texts0_Writer;


export Texts0_Elem Texts0_new;
static Texts0_Buffer Texts0_del;
static Texts0_FontsFont Texts0_FontsDefault;

export LONGINT *Texts0_FontDesc__typ;
export LONGINT *Texts0_RunDesc__typ;
export LONGINT *Texts0_PieceDesc__typ;
export LONGINT *Texts0_ElemMsg__typ;
export LONGINT *Texts0_ElemDesc__typ;
export LONGINT *Texts0_FileMsg__typ;
export LONGINT *Texts0_CopyMsg__typ;
export LONGINT *Texts0_IdentifyMsg__typ;
export LONGINT *Texts0_BufDesc__typ;
export LONGINT *Texts0_TextDesc__typ;
export LONGINT *Texts0_Reader__typ;
export LONGINT *Texts0_Scanner__typ;
export LONGINT *Texts0_Writer__typ;
export LONGINT *Texts0__1__typ;

export void Texts0_Append (Texts0_Text T, Texts0_Buffer B);
export void Texts0_ChangeLooks (Texts0_Text T, LONGINT beg, LONGINT end, SET sel, Texts0_FontsFont fnt, SHORTINT col, SHORTINT voff);
static Texts0_Elem Texts0_CloneElem (Texts0_Elem e);
static Texts0_Piece Texts0_ClonePiece (Texts0_Piece p);
export void Texts0_Close (Texts0_Text T, CHAR *name, LONGINT name__len);
export void Texts0_Copy (Texts0_Buffer SB, Texts0_Buffer DB);
export void Texts0_CopyElem (Texts0_Elem SE, Texts0_Elem DE);
export void Texts0_Delete (Texts0_Text T, LONGINT beg, LONGINT end);
export Texts0_Text Texts0_ElemBase (Texts0_Elem E);
export LONGINT Texts0_ElemPos (Texts0_Elem E);
static void Texts0_Find (Texts0_Text T, LONGINT *pos, Texts0_Run *u, LONGINT *org, LONGINT *off);
static Texts0_FontsFont Texts0_FontsThis (CHAR *name, LONGINT name__len);
static void Texts0_HandleAlien (Texts0_Elem E, Texts0_ElemMsg *msg, LONGINT *msg__typ);
export void Texts0_Insert (Texts0_Text T, LONGINT pos, Texts0_Buffer B);
export void Texts0_Load (Files0_Rider *r, LONGINT *r__typ, Texts0_Text T);
static void Texts0_Load0 (Files0_Rider *r, LONGINT *r__typ, Texts0_Text T);
static void Texts0_Merge (Texts0_Text T, Texts0_Run u, Texts0_Run *v);
export void Texts0_Open (Texts0_Text T, CHAR *name, LONGINT name__len);
export void Texts0_OpenBuf (Texts0_Buffer B);
export void Texts0_OpenReader (Texts0_Reader *R, LONGINT *R__typ, Texts0_Text T, LONGINT pos);
export void Texts0_OpenScanner (Texts0_Scanner *S, LONGINT *S__typ, Texts0_Text T, LONGINT pos);
export void Texts0_OpenWriter (Texts0_Writer *W, LONGINT *W__typ);
export LONGINT Texts0_Pos (Texts0_Reader *R, LONGINT *R__typ);
export void Texts0_Read (Texts0_Reader *R, LONGINT *R__typ, CHAR *ch);
export void Texts0_ReadElem (Texts0_Reader *R, LONGINT *R__typ);
export void Texts0_ReadPrevElem (Texts0_Reader *R, LONGINT *R__typ);
export void Texts0_Recall (Texts0_Buffer *B);
export void Texts0_Save (Texts0_Text T, LONGINT beg, LONGINT end, Texts0_Buffer B);
export void Texts0_Scan (Texts0_Scanner *S, LONGINT *S__typ);
export void Texts0_SetColor (Texts0_Writer *W, LONGINT *W__typ, SHORTINT col);
export void Texts0_SetFont (Texts0_Writer *W, LONGINT *W__typ, Texts0_FontsFont fnt);
export void Texts0_SetOffset (Texts0_Writer *W, LONGINT *W__typ, SHORTINT voff);
static void Texts0_Splice (Texts0_Run un, Texts0_Run v, Texts0_Run w, Texts0_Text base);
static void Texts0_Split (LONGINT off, Texts0_Run *u, Texts0_Run *un);
export void Texts0_Store (Files0_Rider *r, LONGINT *r__typ, Texts0_Text T);
export void Texts0_Write (Texts0_Writer *W, LONGINT *W__typ, CHAR ch);
export void Texts0_WriteDate (Texts0_Writer *W, LONGINT *W__typ, LONGINT t, LONGINT d);
export void Texts0_WriteElem (Texts0_Writer *W, LONGINT *W__typ, Texts0_Elem e);
export void Texts0_WriteHex (Texts0_Writer *W, LONGINT *W__typ, LONGINT x);
export void Texts0_WriteInt (Texts0_Writer *W, LONGINT *W__typ, LONGINT x, LONGINT n);
export void Texts0_WriteLn (Texts0_Writer *W, LONGINT *W__typ);
export void Texts0_WriteLongReal (Texts0_Writer *W, LONGINT *W__typ, LONGREAL x, INTEGER n);
export void Texts0_WriteLongRealHex (Texts0_Writer *W, LONGINT *W__typ, LONGREAL x);
export void Texts0_WriteReal (Texts0_Writer *W, LONGINT *W__typ, REAL x, INTEGER n);
export void Texts0_WriteRealFix (Texts0_Writer *W, LONGINT *W__typ, REAL x, INTEGER n, INTEGER k);
export void Texts0_WriteRealHex (Texts0_Writer *W, LONGINT *W__typ, REAL x);
export void Texts0_WriteString (Texts0_Writer *W, LONGINT *W__typ, CHAR *s, LONGINT s__len);


static Texts0_FontsFont Texts0_FontsThis (CHAR *name, LONGINT name__len)
{
	Texts0_FontsFont F = NIL;
	__NEW(F, Texts0_FontDesc);
	__COPY(name, F->name, 32);
	return F;
}

static void Texts0_Find (Texts0_Text T, LONGINT *pos, Texts0_Run *u, LONGINT *org, LONGINT *off)
{
	Texts0_Run v = NIL;
	LONGINT m;
	if (*pos >= T->len) {
		*pos = T->len;
		*u = T->head;
		*org = T->len;
		*off = 0;
		T->cache = T->head;
		T->corg = 0;
	} else {
		v = T->cache->next;
		m = *pos - T->corg;
		if (*pos >= T->corg) {
			while (m >= v->len) {
				m -= v->len;
				v = v->next;
			}
		} else {
			while (m < 0) {
				v = v->prev;
				m += v->len;
			}
		}
		*u = v;
		*org = *pos - m;
		*off = m;
		T->cache = v->prev;
		T->corg = *org;
	}
}

static void Texts0_Split (LONGINT off, Texts0_Run *u, Texts0_Run *un)
{
	Texts0_Piece p = NIL, U = NIL;
	if (off == 0) {
		*un = *u;
		*u = (*un)->prev;
	} else if (off >= (*u)->len) {
		*un = (*u)->next;
	} else {
		__NEW(p, Texts0_PieceDesc);
		*un = (Texts0_Run)p;
		U = __GUARDP(*u, Texts0_PieceDesc, 1);
		__GUARDEQP(p, Texts0_PieceDesc) = *U;
		p->org += off;
		p->len -= off;
		U->len -= p->len;
		p->ascii = (*u)->ascii;
		p->prev = (Texts0_Run)U;
		p->next = U->next;
		p->next->prev = (Texts0_Run)p;
		U->next = (Texts0_Run)p;
	}
}

static void Texts0_Merge (Texts0_Text T, Texts0_Run u, Texts0_Run *v)
{
	Texts0_Piece p = NIL, q = NIL;
	if ((((((((((__ISP(u, Texts0_PieceDesc, 1) && __ISP(*v, Texts0_PieceDesc, 1))) && __STRCMP(u->fnt->name, (*v)->fnt->name) == 0)) && u->col == (*v)->col)) && u->voff == (*v)->voff)) && __GUARDP(u, Texts0_PieceDesc, 1)->ascii == __GUARDP(*v, Texts0_PieceDesc, 1)->ascii)) {
		p = __GUARDP(u, Texts0_PieceDesc, 1);
		q = __GUARDP(*v, Texts0_PieceDesc, 1);
		if ((p->file == q->file && p->org + p->len == q->org)) {
			if (T->cache == u) {
				T->corg += q->len;
			} else if (T->cache == *v) {
				T->cache = T->head;
				T->corg = 0;
			}
			p->len += q->len;
			*v = (*v)->next;
		}
	}
}

static void Texts0_Splice (Texts0_Run un, Texts0_Run v, Texts0_Run w, Texts0_Text base)
{
	Texts0_Run u = NIL;
	if (v != w->next) {
		u = un->prev;
		u->next = v;
		v->prev = u;
		un->prev = w;
		w->next = un;
		do {
			if (__ISP(v, Texts0_ElemDesc, 1)) {
				__GUARDP(v, Texts0_ElemDesc, 1)->base = base;
			}
			v = v->next;
		} while (!(v == un));
	}
}

static Texts0_Piece Texts0_ClonePiece (Texts0_Piece p)
{
	Texts0_Piece q = NIL;
	__NEW(q, Texts0_PieceDesc);
	__GUARDEQP(q, Texts0_PieceDesc) = *p;
	return q;
}

static Texts0_Elem Texts0_CloneElem (Texts0_Elem e)
{
	Texts0_CopyMsg msg;
	msg.e = NIL;
	(*e->handle)(e, (void*)&msg, Texts0_CopyMsg__typ);
	return msg.e;
}

void Texts0_CopyElem (Texts0_Elem SE, Texts0_Elem DE)
{
	DE->len = SE->len;
	DE->fnt = SE->fnt;
	DE->col = SE->col;
	DE->voff = SE->voff;
	DE->W = SE->W;
	DE->H = SE->H;
	DE->handle = SE->handle;
}

Texts0_Text Texts0_ElemBase (Texts0_Elem E)
{
	return E->base;
}

LONGINT Texts0_ElemPos (Texts0_Elem E)
{
	Texts0_Run u = NIL;
	LONGINT pos;
	u = E->base->head->next;
	pos = 0;
	while (u != (void *) E) {
		pos = pos + u->len;
		u = u->next;
	}
	return pos;
}

static void Texts0_HandleAlien (Texts0_Elem E, Texts0_ElemMsg *msg, LONGINT *msg__typ)
{
	Texts0_Alien e = NIL;
	Files0_Rider r;
	LONGINT i;
	CHAR ch;
	if (__ISP(E, Texts0__1, 2)) {
		if (__IS(msg__typ, Texts0_CopyMsg, 1)) {
			if (__IS(msg__typ, Texts0_CopyMsg, 1)) {
				Texts0_CopyMsg *msg__ = (void*)msg;
				__NEW(e, Texts0__1);
				Texts0_CopyElem((void*)((Texts0_Alien)E), (void*)e);
				e->file = ((Texts0_Alien)E)->file;
				e->org = ((Texts0_Alien)E)->org;
				e->span = ((Texts0_Alien)E)->span;
				__MOVE(((Texts0_Alien)E)->mod, e->mod, 32);
				__MOVE(((Texts0_Alien)E)->proc, e->proc, 32);
				(*msg__).e = (Texts0_Elem)e;
			} else __WITHCHK;
		} else if (__IS(msg__typ, Texts0_IdentifyMsg, 1)) {
			if (__IS(msg__typ, Texts0_IdentifyMsg, 1)) {
				Texts0_IdentifyMsg *msg__ = (void*)msg;
				__COPY(((Texts0_Alien)E)->mod, (*msg__).mod, 32);
				__COPY(((Texts0_Alien)E)->proc, (*msg__).proc, 32);
				(*msg__).mod[31] = 0x01;
			} else __WITHCHK;
		} else if (__IS(msg__typ, Texts0_FileMsg, 1)) {
			if (__IS(msg__typ, Texts0_FileMsg, 1)) {
				Texts0_FileMsg *msg__ = (void*)msg;
				if ((*msg__).id == 1) {
					Files0_Set(&r, Files0_Rider__typ, ((Texts0_Alien)E)->file, ((Texts0_Alien)E)->org);
					i = ((Texts0_Alien)E)->span;
					while (i > 0) {
						Files0_Read(&r, Files0_Rider__typ, (void*)&ch);
						Files0_Write(&(*msg__).r, Files0_Rider__typ, ch);
						i -= 1;
					}
				}
			} else __WITHCHK;
		}
	} else __WITHCHK;
}

void Texts0_OpenBuf (Texts0_Buffer B)
{
	Texts0_Run u = NIL;
	__NEW(u, Texts0_RunDesc);
	u->next = u;
	u->prev = u;
	B->head = u;
	B->len = 0;
}

void Texts0_Copy (Texts0_Buffer SB, Texts0_Buffer DB)
{
	Texts0_Run u = NIL, v = NIL, vn = NIL;
	u = SB->head->next;
	v = DB->head->prev;
	while (u != SB->head) {
		if (__ISP(u, Texts0_PieceDesc, 1)) {
			vn = (Texts0_Run)Texts0_ClonePiece(__GUARDP(u, Texts0_PieceDesc, 1));
		} else {
			vn = (Texts0_Run)Texts0_CloneElem(__GUARDP(u, Texts0_ElemDesc, 1));
		}
		v->next = vn;
		vn->prev = v;
		v = vn;
		u = u->next;
	}
	v->next = DB->head;
	DB->head->prev = v;
	DB->len += SB->len;
}

void Texts0_Recall (Texts0_Buffer *B)
{
	*B = Texts0_del;
	Texts0_del = NIL;
}

void Texts0_Save (Texts0_Text T, LONGINT beg, LONGINT end, Texts0_Buffer B)
{
	Texts0_Run u = NIL, v = NIL, w = NIL, wn = NIL;
	LONGINT uo, ud, vo, vd;
	Texts0_Find(T, &beg, &u, &uo, &ud);
	Texts0_Find(T, &end, &v, &vo, &vd);
	w = B->head->prev;
	while (u != v) {
		if (__ISP(u, Texts0_PieceDesc, 1)) {
			wn = (Texts0_Run)Texts0_ClonePiece(__GUARDP(u, Texts0_PieceDesc, 1));
			wn->len -= ud;
			__GUARDP(wn, Texts0_PieceDesc, 1)->org += ud;
		} else {
			wn = (Texts0_Run)Texts0_CloneElem(__GUARDP(u, Texts0_ElemDesc, 1));
		}
		w->next = wn;
		wn->prev = w;
		w = wn;
		u = u->next;
		ud = 0;
	}
	if (vd > 0) {
		wn = (Texts0_Run)Texts0_ClonePiece(__GUARDP(v, Texts0_PieceDesc, 1));
		wn->len = vd - ud;
		__GUARDP(wn, Texts0_PieceDesc, 1)->org += ud;
		w->next = wn;
		wn->prev = w;
		w = wn;
	}
	w->next = B->head;
	B->head->prev = w;
	B->len += end - beg;
}

void Texts0_Insert (Texts0_Text T, LONGINT pos, Texts0_Buffer B)
{
	Texts0_Run u = NIL, un = NIL, v = NIL;
	Texts0_Piece p = NIL, q = NIL;
	LONGINT uo, ud, len;
	Texts0_Find(T, &pos, &u, &uo, &ud);
	Texts0_Split(ud, &u, &un);
	len = B->len;
	v = B->head->next;
	Texts0_Merge(T, u, &v);
	Texts0_Splice(un, v, B->head->prev, T);
	T->len += len;
	B->head->next = B->head;
	B->head->prev = B->head;
	B->len = 0;
}

void Texts0_Append (Texts0_Text T, Texts0_Buffer B)
{
	Texts0_Run v = NIL;
	LONGINT pos, len;
	pos = T->len;
	len = B->len;
	v = B->head->next;
	Texts0_Merge(T, T->head->prev, &v);
	Texts0_Splice(T->head, v, B->head->prev, T);
	T->len += len;
	B->head->next = B->head;
	B->head->prev = B->head;
	B->len = 0;
}

void Texts0_Delete (Texts0_Text T, LONGINT beg, LONGINT end)
{
	Texts0_Run c = NIL, u = NIL, un = NIL, v = NIL, vn = NIL;
	LONGINT co, uo, ud, vo, vd;
	Texts0_Find(T, &beg, &u, &uo, &ud);
	Texts0_Split(ud, &u, &un);
	c = T->cache;
	co = T->corg;
	Texts0_Find(T, &end, &v, &vo, &vd);
	Texts0_Split(vd, &v, &vn);
	T->cache = c;
	T->corg = co;
	__NEW(Texts0_del, Texts0_BufDesc);
	Texts0_OpenBuf(Texts0_del);
	Texts0_del->len = end - beg;
	Texts0_Splice(Texts0_del->head, un, v, NIL);
	Texts0_Merge(T, u, &vn);
	u->next = vn;
	vn->prev = u;
	T->len -= end - beg;
}

void Texts0_ChangeLooks (Texts0_Text T, LONGINT beg, LONGINT end, SET sel, Texts0_FontsFont fnt, SHORTINT col, SHORTINT voff)
{
	Texts0_Run c = NIL, u = NIL, un = NIL, v = NIL, vn = NIL;
	LONGINT co, uo, ud, vo, vd;
	Texts0_Find(T, &beg, &u, &uo, &ud);
	Texts0_Split(ud, &u, &un);
	c = T->cache;
	co = T->corg;
	Texts0_Find(T, &end, &v, &vo, &vd);
	Texts0_Split(vd, &v, &vn);
	T->cache = c;
	T->corg = co;
	while (un != vn) {
		if ((__IN(0, sel) && fnt != NIL)) {
			un->fnt = fnt;
		}
		if (__IN(1, sel)) {
			un->col = col;
		}
		if (__IN(2, sel)) {
			un->voff = voff;
		}
		Texts0_Merge(T, u, &un);
		if (u->next == un) {
			u = un;
			un = un->next;
		} else {
			u->next = un;
			un->prev = u;
		}
	}
	Texts0_Merge(T, u, &un);
	u->next = un;
	un->prev = u;
}

void Texts0_OpenReader (Texts0_Reader *R, LONGINT *R__typ, Texts0_Text T, LONGINT pos)
{
	Texts0_Run u = NIL;
	if (pos >= T->len) {
		pos = T->len;
	}
	Texts0_Find(T, &pos, &u, &(*R).org, &(*R).off);
	(*R).run = u;
	(*R).eot = 0;
	if (__ISP(u, Texts0_PieceDesc, 1)) {
		Files0_Set(&(*R).rider, Files0_Rider__typ, __GUARDP(u, Texts0_PieceDesc, 1)->file, __GUARDP(u, Texts0_PieceDesc, 1)->org + (*R).off);
	}
}

void Texts0_Read (Texts0_Reader *R, LONGINT *R__typ, CHAR *ch)
{
	Texts0_Run u = NIL;
	u = (*R).run;
	(*R).fnt = u->fnt;
	(*R).col = u->col;
	(*R).voff = u->voff;
	(*R).off += 1;
	if (__ISP(u, Texts0_PieceDesc, 1)) {
		Files0_Read(&(*R).rider, Files0_Rider__typ, (void*)&*ch);
		(*R).elem = NIL;
		if ((*ch == 0x0a && __GUARDP(u, Texts0_PieceDesc, 1)->ascii)) {
			*ch = 0x0d;
		}
	} else if (__ISP(u, Texts0_ElemDesc, 1)) {
		*ch = 0x1c;
		(*R).elem = __GUARDP(u, Texts0_ElemDesc, 1);
	} else {
		*ch = 0x00;
		(*R).elem = NIL;
		(*R).eot = 1;
	}
	if ((*R).off == u->len) {
		(*R).org += u->len;
		u = u->next;
		if (__ISP(u, Texts0_PieceDesc, 1)) {
			if (__ISP(u, Texts0_PieceDesc, 1)) {
				Files0_Set(&(*R).rider, Files0_Rider__typ, ((Texts0_Piece)u)->file, ((Texts0_Piece)u)->org);
			} else __WITHCHK;
		}
		(*R).run = u;
		(*R).off = 0;
	}
}

void Texts0_ReadElem (Texts0_Reader *R, LONGINT *R__typ)
{
	Texts0_Run u = NIL, un = NIL;
	u = (*R).run;
	while (__ISP(u, Texts0_PieceDesc, 1)) {
		(*R).org += u->len;
		u = u->next;
	}
	if (__ISP(u, Texts0_ElemDesc, 1)) {
		un = u->next;
		(*R).run = un;
		(*R).org += 1;
		(*R).off = 0;
		(*R).fnt = u->fnt;
		(*R).col = u->col;
		(*R).voff = u->voff;
		(*R).elem = __GUARDP(u, Texts0_ElemDesc, 1);
		if (__ISP(un, Texts0_PieceDesc, 1)) {
			if (__ISP(un, Texts0_PieceDesc, 1)) {
				Files0_Set(&(*R).rider, Files0_Rider__typ, ((Texts0_Piece)un)->file, ((Texts0_Piece)un)->org);
			} else __WITHCHK;
		}
	} else {
		(*R).eot = 1;
		(*R).elem = NIL;
	}
}

void Texts0_ReadPrevElem (Texts0_Reader *R, LONGINT *R__typ)
{
	Texts0_Run u = NIL;
	u = (*R).run->prev;
	while (__ISP(u, Texts0_PieceDesc, 1)) {
		(*R).org -= u->len;
		u = u->prev;
	}
	if (__ISP(u, Texts0_ElemDesc, 1)) {
		(*R).run = u;
		(*R).org -= 1;
		(*R).off = 0;
		(*R).fnt = u->fnt;
		(*R).col = u->col;
		(*R).voff = u->voff;
		(*R).elem = __GUARDP(u, Texts0_ElemDesc, 1);
	} else {
		(*R).eot = 1;
		(*R).elem = NIL;
	}
}

LONGINT Texts0_Pos (Texts0_Reader *R, LONGINT *R__typ)
{
	return (*R).org + (*R).off;
}

void Texts0_OpenScanner (Texts0_Scanner *S, LONGINT *S__typ, Texts0_Text T, LONGINT pos)
{
	Texts0_OpenReader((void*)&*S, S__typ, T, pos);
	(*S).line = 0;
	(*S).nextCh = ' ';
}

static struct Scan__31 {
	Texts0_Scanner *S;
	LONGINT *S__typ;
	CHAR *ch;
	BOOLEAN *negE;
	INTEGER *e;
	struct Scan__31 *lnk;
} *Scan__31_s;

static void ReadScaleFactor__32 (void);

static void ReadScaleFactor__32 (void)
{
	Texts0_Read((void*)&*Scan__31_s->S, Scan__31_s->S__typ, &*Scan__31_s->ch);
	if (*Scan__31_s->ch == '-') {
		*Scan__31_s->negE = 1;
		Texts0_Read((void*)&*Scan__31_s->S, Scan__31_s->S__typ, &*Scan__31_s->ch);
	} else {
		*Scan__31_s->negE = 0;
		if (*Scan__31_s->ch == '+') {
			Texts0_Read((void*)&*Scan__31_s->S, Scan__31_s->S__typ, &*Scan__31_s->ch);
		}
	}
	while (('0' <= *Scan__31_s->ch && *Scan__31_s->ch <= '9')) {
		*Scan__31_s->e = (*Scan__31_s->e * 10 + (int)*Scan__31_s->ch) - 48;
		Texts0_Read((void*)&*Scan__31_s->S, Scan__31_s->S__typ, &*Scan__31_s->ch);
	}
}

void Texts0_Scan (Texts0_Scanner *S, LONGINT *S__typ)
{
	CHAR ch, term;
	BOOLEAN neg, negE, hex;
	SHORTINT i, j, h;
	INTEGER e;
	LONGINT k;
	REAL x, f;
	LONGREAL y, g;
	CHAR d[32];
	struct Scan__31 _s;
	_s.S = S; _s.S__typ = S__typ;
	_s.ch = &ch;
	_s.negE = &negE;
	_s.e = &e;
	_s.lnk = Scan__31_s;
	Scan__31_s = &_s;
	ch = (*S).nextCh;
	i = 0;
	for (;;) {
		if (ch == 0x0d) {
			(*S).line += 1;
		} else if ((ch != ' ' && ch != 0x09)) {
			break;
		}
		Texts0_Read((void*)&*S, S__typ, &ch);
	}
	if ((('A' <= __CAP(ch) && __CAP(ch) <= 'Z') || ch == '/') || ch == '.') {
		do {
			(*S).s[__X(i, 64)] = ch;
			i += 1;
			Texts0_Read((void*)&*S, S__typ, &ch);
		} while (!((((__CAP(ch) > 'Z' && ch != '_') || ('A' > __CAP(ch) && ch > '9')) || ((('0' > ch && ch != '.')) && ch != '/')) || i == 63));
		(*S).s[__X(i, 64)] = 0x00;
		(*S).len = i;
		(*S).class = 1;
	} else if (ch == '\"') {
		Texts0_Read((void*)&*S, S__typ, &ch);
		while ((((ch != '\"' && ch >= ' ')) && i != 63)) {
			(*S).s[__X(i, 64)] = ch;
			i += 1;
			Texts0_Read((void*)&*S, S__typ, &ch);
		}
		(*S).s[__X(i, 64)] = 0x00;
		(*S).len = i + 1;
		Texts0_Read((void*)&*S, S__typ, &ch);
		(*S).class = 2;
	} else {
		if (ch == '-') {
			neg = 1;
			Texts0_Read((void*)&*S, S__typ, &ch);
		} else {
			neg = 0;
		}
		if (('0' <= ch && ch <= '9')) {
			hex = 0;
			j = 0;
			for (;;) {
				d[__X(i, 32)] = ch;
				i += 1;
				Texts0_Read((void*)&*S, S__typ, &ch);
				if (ch < '0') {
					break;
				}
				if ('9' < ch) {
					if (('A' <= ch && ch <= 'F')) {
						hex = 1;
						ch = (CHAR)((int)ch - 7);
					} else if (('a' <= ch && ch <= 'f')) {
						hex = 1;
						ch = (CHAR)((int)ch - 39);
					} else {
						break;
					}
				}
			}
			if (ch == 'H') {
				Texts0_Read((void*)&*S, S__typ, &ch);
				(*S).class = 3;
				if (i - j > 8) {
					j = i - 8;
				}
				k = (int)d[__X(j, 32)] - 48;
				j += 1;
				if ((i - j == 7 && k >= 8)) {
					k -= 16;
				}
				while (j < i) {
					k = __ASHL(k, 4) + (LONGINT)((int)d[__X(j, 32)] - 48);
					j += 1;
				}
				if (neg) {
					(*S).i = -k;
				} else {
					(*S).i = k;
				}
			} else if (ch == '.') {
				Texts0_Read((void*)&*S, S__typ, &ch);
				h = i;
				while (('0' <= ch && ch <= '9')) {
					d[__X(i, 32)] = ch;
					i += 1;
					Texts0_Read((void*)&*S, S__typ, &ch);
				}
				if (ch == 'D') {
					e = 0;
					y = (LONGREAL)0;
					g = (LONGREAL)1;
					do {
						y = y * (LONGREAL)10 + ((int)d[__X(j, 32)] - 48);
						j += 1;
					} while (!(j == h));
					while (j < i) {
						g = g / (LONGREAL)(LONGREAL)10;
						y = ((int)d[__X(j, 32)] - 48) * g + y;
						j += 1;
					}
					ReadScaleFactor__32();
					if (negE) {
						if (e <= 308) {
							y = y / (LONGREAL)Reals_TenL(e);
						} else {
							y = (LONGREAL)0;
						}
					} else if (e > 0) {
						if (e <= 308) {
							y = Reals_TenL(e) * y;
						} else {
							__HALT(40);
						}
					}
					if (neg) {
						y = -y;
					}
					(*S).class = 5;
					(*S).y = y;
				} else {
					e = 0;
					x = (REAL)0;
					f = (REAL)1;
					do {
						x = x * (REAL)10 + ((int)d[__X(j, 32)] - 48);
						j += 1;
					} while (!(j == h));
					while (j < i) {
						f = f / (REAL)(REAL)10;
						x = ((int)d[__X(j, 32)] - 48) * f + x;
						j += 1;
					}
					if (ch == 'E') {
						ReadScaleFactor__32();
					}
					if (negE) {
						if (e <= 38) {
							x = x / (REAL)Reals_Ten(e);
						} else {
							x = (REAL)0;
						}
					} else if (e > 0) {
						if (e <= 38) {
							x = Reals_Ten(e) * x;
						} else {
							__HALT(40);
						}
					}
					if (neg) {
						x = -x;
					}
					(*S).class = 4;
					(*S).x = x;
				}
				if (hex) {
					(*S).class = 0;
				}
			} else {
				(*S).class = 3;
				k = 0;
				do {
					k = k * 10 + (LONGINT)((int)d[__X(j, 32)] - 48);
					j += 1;
				} while (!(j == i));
				if (neg) {
					(*S).i = -k;
				} else {
					(*S).i = k;
				}
				if (hex) {
					(*S).class = 0;
				} else {
					(*S).class = 3;
				}
			}
		} else {
			(*S).class = 6;
			if (neg) {
				(*S).c = '-';
			} else {
				(*S).c = ch;
				Texts0_Read((void*)&*S, S__typ, &ch);
			}
		}
	}
	(*S).nextCh = ch;
	Scan__31_s = _s.lnk;
}

void Texts0_OpenWriter (Texts0_Writer *W, LONGINT *W__typ)
{
	__NEW((*W).buf, Texts0_BufDesc);
	Texts0_OpenBuf((*W).buf);
	(*W).fnt = Texts0_FontsDefault;
	(*W).col = 15;
	(*W).voff = 0;
	(*W).file = Files0_New((CHAR*)"", (LONGINT)1);
	Files0_Set(&(*W).rider, Files0_Rider__typ, (*W).file, 0);
}

void Texts0_SetFont (Texts0_Writer *W, LONGINT *W__typ, Texts0_FontsFont fnt)
{
	(*W).fnt = fnt;
}

void Texts0_SetColor (Texts0_Writer *W, LONGINT *W__typ, SHORTINT col)
{
	(*W).col = col;
}

void Texts0_SetOffset (Texts0_Writer *W, LONGINT *W__typ, SHORTINT voff)
{
	(*W).voff = voff;
}

void Texts0_Write (Texts0_Writer *W, LONGINT *W__typ, CHAR ch)
{
	Texts0_Run u = NIL, un = NIL;
	Texts0_Piece p = NIL;
	Files0_Write(&(*W).rider, Files0_Rider__typ, ch);
	(*W).buf->len += 1;
	un = (*W).buf->head;
	u = un->prev;
	if ((((((((((__ISP(u, Texts0_PieceDesc, 1) && __GUARDP(u, Texts0_PieceDesc, 1)->file == (*W).file)) && __STRCMP(u->fnt->name, (*W).fnt->name) == 0)) && u->col == (*W).col)) && u->voff == (*W).voff)) && !__GUARDP(u, Texts0_PieceDesc, 1)->ascii)) {
		u->len += 1;
	} else {
		__NEW(p, Texts0_PieceDesc);
		u->next = (Texts0_Run)p;
		p->prev = u;
		p->next = un;
		un->prev = (Texts0_Run)p;
		p->len = 1;
		p->fnt = (*W).fnt;
		p->col = (*W).col;
		p->voff = (*W).voff;
		p->file = (*W).file;
		p->org = Files0_Length((*W).file) - 1;
		p->ascii = 0;
	}
}

void Texts0_WriteElem (Texts0_Writer *W, LONGINT *W__typ, Texts0_Elem e)
{
	Texts0_Run u = NIL, un = NIL;
	if (e->base != NIL) {
		__HALT(99);
	}
	(*W).buf->len += 1;
	e->len = 1;
	e->fnt = (*W).fnt;
	e->col = (*W).col;
	e->voff = (*W).voff;
	un = (*W).buf->head;
	u = un->prev;
	u->next = (Texts0_Run)e;
	e->prev = u;
	e->next = un;
	un->prev = (Texts0_Run)e;
}

void Texts0_WriteLn (Texts0_Writer *W, LONGINT *W__typ)
{
	Texts0_Write(&*W, W__typ, 0x0d);
}

void Texts0_WriteString (Texts0_Writer *W, LONGINT *W__typ, CHAR *s, LONGINT s__len)
{
	INTEGER i;
	__DUP(s, s__len, CHAR);
	i = 0;
	while (s[__X(i, s__len)] >= ' ') {
		Texts0_Write(&*W, W__typ, s[__X(i, s__len)]);
		i += 1;
	}
	__DEL(s);
}

void Texts0_WriteInt (Texts0_Writer *W, LONGINT *W__typ, LONGINT x, LONGINT n)
{
	INTEGER i;
	LONGINT x0;
	CHAR a[11];
	i = 0;
	if (x < 0) {
		if (x == (-9223372036854775807-1)) {
			Texts0_WriteString(&*W, W__typ, (CHAR*)" -2147483648", (LONGINT)13);
			return;
		} else {
			n -= 1;
			x0 = -x;
		}
	} else {
		x0 = x;
	}
	do {
		a[__X(i, 11)] = (CHAR)(__MOD(x0, 10) + 48);
		x0 = __DIV(x0, 10);
		i += 1;
	} while (!(x0 == 0));
	while (n > (LONGINT)i) {
		Texts0_Write(&*W, W__typ, ' ');
		n -= 1;
	}
	if (x < 0) {
		Texts0_Write(&*W, W__typ, '-');
	}
	do {
		i -= 1;
		Texts0_Write(&*W, W__typ, a[__X(i, 11)]);
	} while (!(i == 0));
}

void Texts0_WriteHex (Texts0_Writer *W, LONGINT *W__typ, LONGINT x)
{
	INTEGER i;
	LONGINT y;
	CHAR a[10];
	i = 0;
	Texts0_Write(&*W, W__typ, ' ');
	do {
		y = __MASK(x, -16);
		if (y < 10) {
			a[__X(i, 10)] = (CHAR)(y + 48);
		} else {
			a[__X(i, 10)] = (CHAR)(y + 55);
		}
		x = __ASHR(x, 4);
		i += 1;
	} while (!(i == 8));
	do {
		i -= 1;
		Texts0_Write(&*W, W__typ, a[__X(i, 10)]);
	} while (!(i == 0));
}

void Texts0_WriteReal (Texts0_Writer *W, LONGINT *W__typ, REAL x, INTEGER n)
{
	INTEGER e;
	REAL x0;
	CHAR d[9];
	e = Reals_Expo(x);
	if (e == 0) {
		Texts0_WriteString(&*W, W__typ, (CHAR*)"  0", (LONGINT)4);
		do {
			Texts0_Write(&*W, W__typ, ' ');
			n -= 1;
		} while (!(n <= 3));
	} else if (e == 255) {
		Texts0_WriteString(&*W, W__typ, (CHAR*)" NaN", (LONGINT)5);
		while (n > 4) {
			Texts0_Write(&*W, W__typ, ' ');
			n -= 1;
		}
	} else {
		if (n <= 9) {
			n = 3;
		} else {
			n -= 6;
		}
		do {
			Texts0_Write(&*W, W__typ, ' ');
			n -= 1;
		} while (!(n <= 8));
		if (x < (REAL)0) {
			Texts0_Write(&*W, W__typ, '-');
			x = -x;
		} else {
			Texts0_Write(&*W, W__typ, ' ');
		}
		e = __ASHR((e - 127) * 77, 8);
		if (e >= 0) {
			x = x / (REAL)Reals_Ten(e);
		} else {
			x = Reals_Ten(-e) * x;
		}
		if (x >= (REAL)10) {
			x =   1.0000000e-001 * x;
			e += 1;
		}
		x0 = Reals_Ten(n - 1);
		x = x0 * x +   5.0000000e-001;
		if (x >= (REAL)10 * x0) {
			x = x *   1.0000000e-001;
			e += 1;
		}
		Reals_Convert(x, n, (void*)d, 9);
		n -= 1;
		Texts0_Write(&*W, W__typ, d[__X(n, 9)]);
		Texts0_Write(&*W, W__typ, '.');
		do {
			n -= 1;
			Texts0_Write(&*W, W__typ, d[__X(n, 9)]);
		} while (!(n == 0));
		Texts0_Write(&*W, W__typ, 'E');
		if (e < 0) {
			Texts0_Write(&*W, W__typ, '-');
			e = -e;
		} else {
			Texts0_Write(&*W, W__typ, '+');
		}
		Texts0_Write(&*W, W__typ, (CHAR)(__DIV(e, 10) + 48));
		Texts0_Write(&*W, W__typ, (CHAR)((int)__MOD(e, 10) + 48));
	}
}

static struct WriteRealFix__53 {
	Texts0_Writer *W;
	LONGINT *W__typ;
	INTEGER *i;
	CHAR (*d)[9];
	struct WriteRealFix__53 *lnk;
} *WriteRealFix__53_s;

static void dig__54 (INTEGER n);
static void seq__56 (CHAR ch, INTEGER n);

static void seq__56 (CHAR ch, INTEGER n)
{
	while (n > 0) {
		Texts0_Write(&*WriteRealFix__53_s->W, WriteRealFix__53_s->W__typ, ch);
		n -= 1;
	}
}

static void dig__54 (INTEGER n)
{
	while (n > 0) {
		*WriteRealFix__53_s->i -= 1;
		Texts0_Write(&*WriteRealFix__53_s->W, WriteRealFix__53_s->W__typ, (*WriteRealFix__53_s->d)[__X(*WriteRealFix__53_s->i, 9)]);
		n -= 1;
	}
}

void Texts0_WriteRealFix (Texts0_Writer *W, LONGINT *W__typ, REAL x, INTEGER n, INTEGER k)
{
	INTEGER e, i;
	CHAR sign;
	REAL x0;
	CHAR d[9];
	struct WriteRealFix__53 _s;
	_s.W = W; _s.W__typ = W__typ;
	_s.i = &i;
	_s.d = (void*)d;
	_s.lnk = WriteRealFix__53_s;
	WriteRealFix__53_s = &_s;
	e = Reals_Expo(x);
	if (k < 0) {
		k = 0;
	}
	if (e == 0) {
		seq__56(' ', (n - k) - 2);
		Texts0_Write(&*W, W__typ, '0');
		seq__56(' ', k + 1);
	} else if (e == 255) {
		Texts0_WriteString(&*W, W__typ, (CHAR*)" NaN", (LONGINT)5);
		seq__56(' ', n - 4);
	} else {
		e = __ASHR((e - 127) * 77, 8);
		if (x < (REAL)0) {
			sign = '-';
			x = -x;
		} else {
			sign = ' ';
		}
		if (e >= 0) {
			x = x / (REAL)Reals_Ten(e);
		} else {
			x = Reals_Ten(-e) * x;
		}
		if (x >= (REAL)10) {
			x =   1.0000000e-001 * x;
			e += 1;
		}
		if (k + e >= 8) {
			k = 8 - e;
		} else if (k + e < 0) {
			k = -e;
			x = (REAL)0;
		}
		x0 = Reals_Ten(k + e);
		x = x0 * x +   5.0000000e-001;
		if (x >= (REAL)10 * x0) {
			e += 1;
		}
		e += 1;
		i = k + e;
		Reals_Convert(x, i, (void*)d, 9);
		if (e > 0) {
			seq__56(' ', ((n - e) - k) - 2);
			Texts0_Write(&*W, W__typ, sign);
			dig__54(e);
			Texts0_Write(&*W, W__typ, '.');
			dig__54(k);
		} else {
			seq__56(' ', (n - k) - 3);
			Texts0_Write(&*W, W__typ, sign);
			Texts0_Write(&*W, W__typ, '0');
			Texts0_Write(&*W, W__typ, '.');
			seq__56('0', -e);
			dig__54(k + e);
		}
	}
	WriteRealFix__53_s = _s.lnk;
}

void Texts0_WriteRealHex (Texts0_Writer *W, LONGINT *W__typ, REAL x)
{
	INTEGER i;
	CHAR d[8];
	Reals_ConvertH(x, (void*)d, 8);
	i = 0;
	do {
		Texts0_Write(&*W, W__typ, d[__X(i, 8)]);
		i += 1;
	} while (!(i == 8));
}

void Texts0_WriteLongReal (Texts0_Writer *W, LONGINT *W__typ, LONGREAL x, INTEGER n)
{
	INTEGER e;
	LONGREAL x0;
	CHAR d[16];
	e = Reals_ExpoL(x);
	if (e == 0) {
		Texts0_WriteString(&*W, W__typ, (CHAR*)"  0", (LONGINT)4);
		do {
			Texts0_Write(&*W, W__typ, ' ');
			n -= 1;
		} while (!(n <= 3));
	} else if (e == 2047) {
		Texts0_WriteString(&*W, W__typ, (CHAR*)" NaN", (LONGINT)5);
		while (n > 4) {
			Texts0_Write(&*W, W__typ, ' ');
			n -= 1;
		}
	} else {
		if (n <= 10) {
			n = 3;
		} else {
			n -= 7;
		}
		do {
			Texts0_Write(&*W, W__typ, ' ');
			n -= 1;
		} while (!(n <= 16));
		if (x < (LONGREAL)0) {
			Texts0_Write(&*W, W__typ, '-');
			x = -x;
		} else {
			Texts0_Write(&*W, W__typ, ' ');
		}
		e = (int)__ASHR((LONGINT)(e - 1023) * 77, 8);
		if (e >= 0) {
			x = x / (LONGREAL)Reals_TenL(e);
		} else {
			x = Reals_TenL(-e) * x;
		}
		if (x >= (LONGREAL)10) {
			x =   1.00000000000000e-001 * x;
			e += 1;
		}
		x0 = Reals_TenL(n - 1);
		x = x0 * x +   5.00000000000000e-001;
		if (x >= (LONGREAL)10 * x0) {
			x =   1.00000000000000e-001 * x;
			e += 1;
		}
		Reals_ConvertL(x, n, (void*)d, 16);
		n -= 1;
		Texts0_Write(&*W, W__typ, d[__X(n, 16)]);
		Texts0_Write(&*W, W__typ, '.');
		do {
			n -= 1;
			Texts0_Write(&*W, W__typ, d[__X(n, 16)]);
		} while (!(n == 0));
		Texts0_Write(&*W, W__typ, 'D');
		if (e < 0) {
			Texts0_Write(&*W, W__typ, '-');
			e = -e;
		} else {
			Texts0_Write(&*W, W__typ, '+');
		}
		Texts0_Write(&*W, W__typ, (CHAR)(__DIV(e, 100) + 48));
		e = (int)__MOD(e, 100);
		Texts0_Write(&*W, W__typ, (CHAR)(__DIV(e, 10) + 48));
		Texts0_Write(&*W, W__typ, (CHAR)((int)__MOD(e, 10) + 48));
	}
}

void Texts0_WriteLongRealHex (Texts0_Writer *W, LONGINT *W__typ, LONGREAL x)
{
	INTEGER i;
	CHAR d[16];
	Reals_ConvertHL(x, (void*)d, 16);
	i = 0;
	do {
		Texts0_Write(&*W, W__typ, d[__X(i, 16)]);
		i += 1;
	} while (!(i == 16));
}

static struct WriteDate__43 {
	Texts0_Writer *W;
	LONGINT *W__typ;
	struct WriteDate__43 *lnk;
} *WriteDate__43_s;

static void WritePair__44 (CHAR ch, LONGINT x);

static void WritePair__44 (CHAR ch, LONGINT x)
{
	Texts0_Write(&*WriteDate__43_s->W, WriteDate__43_s->W__typ, ch);
	Texts0_Write(&*WriteDate__43_s->W, WriteDate__43_s->W__typ, (CHAR)(__DIV(x, 10) + 48));
	Texts0_Write(&*WriteDate__43_s->W, WriteDate__43_s->W__typ, (CHAR)(__MOD(x, 10) + 48));
}

void Texts0_WriteDate (Texts0_Writer *W, LONGINT *W__typ, LONGINT t, LONGINT d)
{
	struct WriteDate__43 _s;
	_s.W = W; _s.W__typ = W__typ;
	_s.lnk = WriteDate__43_s;
	WriteDate__43_s = &_s;
	WritePair__44(' ', __MASK(d, -32));
	WritePair__44('.', __MASK(__ASHR(d, 5), -16));
	WritePair__44('.', __MASK(__ASHR(d, 9), -128));
	WritePair__44(' ', __MASK(__ASHR(t, 12), -32));
	WritePair__44(':', __MASK(__ASHR(t, 6), -64));
	WritePair__44(':', __MASK(t, -64));
	WriteDate__43_s = _s.lnk;
}

static struct Load0__16 {
	Texts0_Text *T;
	SHORTINT *ecnt;
	Files0_File *f;
	Texts0_FileMsg *msg;
	CHAR (*mods)[64][32], (*procs)[64][32];
	struct Load0__16 *lnk;
} *Load0__16_s;

static void LoadElem__17 (Files0_Rider *r, LONGINT *r__typ, LONGINT pos, LONGINT span, Texts0_Elem *e);

static void LoadElem__17 (Files0_Rider *r, LONGINT *r__typ, LONGINT pos, LONGINT span, Texts0_Elem *e)
{
	Modules_Module M = NIL;
	Modules_Command Cmd;
	Texts0_Alien a = NIL;
	LONGINT org, ew, eh;
	SHORTINT eno;
	Texts0_new = NIL;
	Files0_ReadLInt(&*r, r__typ, &ew);
	Files0_ReadLInt(&*r, r__typ, &eh);
	Files0_Read(&*r, r__typ, (void*)&eno);
	if (eno > *Load0__16_s->ecnt) {
		*Load0__16_s->ecnt = eno;
		Files0_ReadString(&*r, r__typ, (void*)(*Load0__16_s->mods)[__X(eno, 64)], 32);
		Files0_ReadString(&*r, r__typ, (void*)(*Load0__16_s->procs)[__X(eno, 64)], 32);
	}
	org = Files0_Pos(&*r, r__typ);
	M = Modules_ThisMod((*Load0__16_s->mods)[__X(eno, 64)], 32);
	if (M != NIL) {
		Cmd = Modules_ThisCommand(M, (*Load0__16_s->procs)[__X(eno, 64)], 32);
		if (Cmd != NIL) {
			(*Cmd)();
		}
	}
	*e = Texts0_new;
	if (*e != NIL) {
		(*e)->W = ew;
		(*e)->H = eh;
		(*e)->base = *Load0__16_s->T;
		(*Load0__16_s->msg).pos = pos;
		(*(*e)->handle)(*e, (void*)&*Load0__16_s->msg, Texts0_FileMsg__typ);
		if (Files0_Pos(&*r, r__typ) != org + span) {
			*e = NIL;
		}
	}
	if (*e == NIL) {
		Files0_Set(&*r, r__typ, *Load0__16_s->f, org + span);
		__NEW(a, Texts0__1);
		a->W = ew;
		a->H = eh;
		a->handle = Texts0_HandleAlien;
		a->base = *Load0__16_s->T;
		a->file = *Load0__16_s->f;
		a->org = org;
		a->span = span;
		__COPY((*Load0__16_s->mods)[__X(eno, 64)], a->mod, 32);
		__COPY((*Load0__16_s->procs)[__X(eno, 64)], a->proc, 32);
		*e = (Texts0_Elem)a;
	}
}

static void Texts0_Load0 (Files0_Rider *r, LONGINT *r__typ, Texts0_Text T)
{
	Texts0_Run u = NIL, un = NIL;
	Texts0_Piece p = NIL;
	Texts0_Elem e = NIL;
	LONGINT org, pos, hlen, plen;
	SHORTINT ecnt, fno, fcnt, col, voff;
	Files0_File f = NIL;
	Texts0_FileMsg msg;
	CHAR mods[64][32], procs[64][32];
	CHAR name[32];
	Texts0_FontsFont fnts[32];
	struct Load0__16 _s;
	_s.T = &T;
	_s.ecnt = &ecnt;
	_s.f = &f;
	_s.msg = &msg;
	_s.mods = (void*)mods;
	_s.procs = (void*)procs;
	_s.lnk = Load0__16_s;
	Load0__16_s = &_s;
	pos = Files0_Pos(&*r, r__typ);
	f = Files0_Base(&*r, r__typ);
	__NEW(u, Texts0_RunDesc);
	u->len = 9223372036854775807;
	u->fnt = NIL;
	u->col = 15;
	T->head = u;
	ecnt = 0;
	fcnt = 0;
	msg.id = 0;
	msg.r = *r;
	Files0_ReadLInt(&msg.r, Files0_Rider__typ, &hlen);
	org = (pos - 2) + hlen;
	pos = org;
	Files0_Read(&msg.r, Files0_Rider__typ, (void*)&fno);
	while (fno != 0) {
		if (fno > fcnt) {
			fcnt = fno;
			Files0_ReadString(&msg.r, Files0_Rider__typ, (void*)name, 32);
			fnts[__X(fno, 32)] = Texts0_FontsThis((void*)name, 32);
		}
		Files0_Read(&msg.r, Files0_Rider__typ, (void*)&col);
		Files0_Read(&msg.r, Files0_Rider__typ, (void*)&voff);
		Files0_ReadLInt(&msg.r, Files0_Rider__typ, &plen);
		if (plen > 0) {
			__NEW(p, Texts0_PieceDesc);
			p->file = f;
			p->org = pos;
			p->ascii = 0;
			un = (Texts0_Run)p;
			un->len = plen;
		} else {
			LoadElem__17(&msg.r, Files0_Rider__typ, pos - org, -plen, &e);
			un = (Texts0_Run)e;
			un->len = 1;
		}
		un->fnt = fnts[__X(fno, 32)];
		un->col = col;
		un->voff = voff;
		pos += un->len;
		u->next = un;
		un->prev = u;
		u = un;
		Files0_Read(&msg.r, Files0_Rider__typ, (void*)&fno);
	}
	u->next = T->head;
	T->head->prev = u;
	T->cache = T->head;
	T->corg = 0;
	Files0_ReadLInt(&msg.r, Files0_Rider__typ, &T->len);
	Files0_Set(&*r, r__typ, f, Files0_Pos(&msg.r, Files0_Rider__typ) + T->len);
	Load0__16_s = _s.lnk;
}

void Texts0_Load (Files0_Rider *r, LONGINT *r__typ, Texts0_Text T)
{
	INTEGER tag;
	Files0_ReadInt(&*r, r__typ, &tag);
	if (tag != -4095) {
		Files0_Set(&*r, r__typ, Files0_Base(&*r, r__typ), Files0_Pos(&*r, r__typ) - 2);
	}
	Texts0_Load0(&*r, r__typ, T);
}

void Texts0_Open (Texts0_Text T, CHAR *name, LONGINT name__len)
{
	Files0_File f = NIL;
	Files0_Rider r;
	Texts0_Run u = NIL;
	Texts0_Piece p = NIL;
	CHAR tag, version;
	LONGINT hlen;
	__DUP(name, name__len, CHAR);
	f = Files0_Old(name, name__len);
	if (f == NIL) {
		f = Files0_New((CHAR*)"", (LONGINT)1);
	}
	Files0_Set(&r, Files0_Rider__typ, f, 0);
	Files0_Read(&r, Files0_Rider__typ, (void*)&tag);
	Files0_Read(&r, Files0_Rider__typ, (void*)&version);
	if (tag == 0xf0 || (tag == 0x01 && version == 0xf0)) {
		Texts0_Load0(&r, Files0_Rider__typ, T);
	} else {
		__NEW(u, Texts0_RunDesc);
		u->len = 9223372036854775807;
		u->fnt = NIL;
		u->col = 15;
		__NEW(p, Texts0_PieceDesc);
		if ((tag == 0xf7 && version == 0x07)) {
			Files0_Set(&r, Files0_Rider__typ, f, 28);
			Files0_ReadLInt(&r, Files0_Rider__typ, &hlen);
			Files0_Set(&r, Files0_Rider__typ, f, 22 + hlen);
			Files0_ReadLInt(&r, Files0_Rider__typ, &T->len);
			p->org = 26 + hlen;
		} else {
			T->len = Files0_Length(f);
			p->org = 0;
		}
		if (T->len > 0) {
			p->len = T->len;
			p->fnt = Texts0_FontsDefault;
			p->col = 15;
			p->voff = 0;
			p->file = f;
			p->ascii = 1;
			u->next = (Texts0_Run)p;
			u->prev = (Texts0_Run)p;
			p->next = u;
			p->prev = u;
		} else {
			u->next = u;
			u->prev = u;
		}
		T->head = u;
		T->cache = T->head;
		T->corg = 0;
	}
	__DEL(name);
}

static struct Store__39 {
	SHORTINT *ecnt;
	Texts0_FileMsg *msg;
	Texts0_IdentifyMsg *iden;
	CHAR (*mods)[64][32], (*procs)[64][32];
	struct Store__39 *lnk;
} *Store__39_s;

static void StoreElem__40 (Files0_Rider *r, LONGINT *r__typ, LONGINT pos, Texts0_Elem e);

static void StoreElem__40 (Files0_Rider *r, LONGINT *r__typ, LONGINT pos, Texts0_Elem e)
{
	Files0_Rider r1;
	LONGINT org, span;
	SHORTINT eno;
	__COPY((*Store__39_s->iden).mod, (*Store__39_s->mods)[__X(*Store__39_s->ecnt, 64)], 32);
	__COPY((*Store__39_s->iden).proc, (*Store__39_s->procs)[__X(*Store__39_s->ecnt, 64)], 32);
	eno = 1;
	while (__STRCMP((*Store__39_s->mods)[__X(eno, 64)], (*Store__39_s->iden).mod) != 0 || __STRCMP((*Store__39_s->procs)[__X(eno, 64)], (*Store__39_s->iden).proc) != 0) {
		eno += 1;
	}
	Files0_Set(&r1, Files0_Rider__typ, Files0_Base(&*r, r__typ), Files0_Pos(&*r, r__typ));
	Files0_WriteLInt(&*r, r__typ, 0);
	Files0_WriteLInt(&*r, r__typ, 0);
	Files0_WriteLInt(&*r, r__typ, 0);
	Files0_Write(&*r, r__typ, eno);
	if (eno == *Store__39_s->ecnt) {
		*Store__39_s->ecnt += 1;
		Files0_WriteString(&*r, r__typ, (*Store__39_s->iden).mod, 32);
		Files0_WriteString(&*r, r__typ, (*Store__39_s->iden).proc, 32);
	}
	(*Store__39_s->msg).pos = pos;
	org = Files0_Pos(&*r, r__typ);
	(*e->handle)(e, (void*)&*Store__39_s->msg, Texts0_FileMsg__typ);
	span = Files0_Pos(&*r, r__typ) - org;
	Files0_WriteLInt(&r1, Files0_Rider__typ, -span);
	Files0_WriteLInt(&r1, Files0_Rider__typ, e->W);
	Files0_WriteLInt(&r1, Files0_Rider__typ, e->H);
}

void Texts0_Store (Files0_Rider *r, LONGINT *r__typ, Texts0_Text T)
{
	Files0_Rider r1;
	Texts0_Run u = NIL, un = NIL;
	Texts0_Elem e = NIL;
	LONGINT org, pos, delta, hlen, rlen;
	SHORTINT ecnt, fno, fcnt;
	CHAR ch;
	Texts0_FileMsg msg;
	Texts0_IdentifyMsg iden;
	CHAR mods[64][32], procs[64][32];
	Texts0_FontsFont fnts[32];
	CHAR block[1024];
	struct Store__39 _s;
	_s.ecnt = &ecnt;
	_s.msg = &msg;
	_s.iden = &iden;
	_s.mods = (void*)mods;
	_s.procs = (void*)procs;
	_s.lnk = Store__39_s;
	Store__39_s = &_s;
	org = Files0_Pos(&*r, r__typ);
	msg.id = 1;
	msg.r = *r;
	Files0_WriteLInt(&msg.r, Files0_Rider__typ, 0);
	u = T->head->next;
	pos = 0;
	delta = 0;
	fcnt = 1;
	ecnt = 1;
	while (u != T->head) {
		if (__ISP(u, Texts0_ElemDesc, 1)) {
			iden.mod[0] = 0x00;
			(*__GUARDP(u, Texts0_ElemDesc, 1)->handle)(__GUARDP(u, Texts0_ElemDesc, 1), (void*)&iden, Texts0_IdentifyMsg__typ);
		} else {
			iden.mod[0] = 0x01;
		}
		if (iden.mod[0] != 0x00) {
			fnts[__X(fcnt, 32)] = u->fnt;
			fno = 1;
			while (__STRCMP(fnts[__X(fno, 32)]->name, u->fnt->name) != 0) {
				fno += 1;
			}
			Files0_Write(&msg.r, Files0_Rider__typ, fno);
			if (fno == fcnt) {
				fcnt += 1;
				Files0_WriteString(&msg.r, Files0_Rider__typ, u->fnt->name, 32);
			}
			Files0_Write(&msg.r, Files0_Rider__typ, u->col);
			Files0_Write(&msg.r, Files0_Rider__typ, u->voff);
		}
		if (__ISP(u, Texts0_PieceDesc, 1)) {
			rlen = u->len;
			un = u->next;
			while ((((((__ISP(un, Texts0_PieceDesc, 1) && un->fnt == u->fnt)) && un->col == u->col)) && un->voff == u->voff)) {
				rlen += un->len;
				un = un->next;
			}
			Files0_WriteLInt(&msg.r, Files0_Rider__typ, rlen);
			pos += rlen;
			u = un;
		} else if (iden.mod[0] != 0x00) {
			StoreElem__40(&msg.r, Files0_Rider__typ, pos, __GUARDP(u, Texts0_ElemDesc, 1));
			pos += 1;
			u = u->next;
		} else {
			delta += 1;
			u = u->next;
		}
	}
	Files0_Write(&msg.r, Files0_Rider__typ, 0);
	Files0_WriteLInt(&msg.r, Files0_Rider__typ, T->len - delta);
	hlen = (Files0_Pos(&msg.r, Files0_Rider__typ) - org) + 2;
	Files0_Set(&r1, Files0_Rider__typ, Files0_Base(&msg.r, Files0_Rider__typ), org);
	Files0_WriteLInt(&r1, Files0_Rider__typ, hlen);
	u = T->head->next;
	while (u != T->head) {
		if (__ISP(u, Texts0_PieceDesc, 1)) {
			if (__ISP(u, Texts0_PieceDesc, 1)) {
				if (((Texts0_Piece)u)->ascii) {
					Files0_Set(&r1, Files0_Rider__typ, ((Texts0_Piece)u)->file, ((Texts0_Piece)u)->org);
					delta = ((Texts0_Piece)u)->len;
					while (delta > 0) {
						Files0_Read(&r1, Files0_Rider__typ, (void*)&ch);
						delta -= 1;
						if (ch == 0x0a) {
							Files0_Write(&msg.r, Files0_Rider__typ, 0x0d);
						} else {
							Files0_Write(&msg.r, Files0_Rider__typ, ch);
						}
					}
				} else {
					Files0_Set(&r1, Files0_Rider__typ, ((Texts0_Piece)u)->file, ((Texts0_Piece)u)->org);
					delta = ((Texts0_Piece)u)->len;
					while (delta > 1024) {
						Files0_ReadBytes(&r1, Files0_Rider__typ, (void*)block, 1024, 1024);
						Files0_WriteBytes(&msg.r, Files0_Rider__typ, (void*)block, 1024, 1024);
						delta -= 1024;
					}
					Files0_ReadBytes(&r1, Files0_Rider__typ, (void*)block, 1024, delta);
					Files0_WriteBytes(&msg.r, Files0_Rider__typ, (void*)block, 1024, delta);
				}
			} else __WITHCHK;
		} else {
			iden.mod[0] = 0x00;
			(*__GUARDP(u, Texts0_ElemDesc, 1)->handle)(__GUARDP(u, Texts0_ElemDesc, 1), (void*)&iden, Texts0_IdentifyMsg__typ);
			if (iden.mod[0] != 0x00) {
				Files0_Write(&msg.r, Files0_Rider__typ, 0x1c);
			}
		}
		u = u->next;
	}
	__GUARDEQR(r, r__typ, Files0_Rider) = msg.r;
	Store__39_s = _s.lnk;
}

void Texts0_Close (Texts0_Text T, CHAR *name, LONGINT name__len)
{
	Files0_File f = NIL;
	Files0_Rider r;
	INTEGER i, res;
	CHAR bak[64];
	__DUP(name, name__len, CHAR);
	f = Files0_New(name, name__len);
	Files0_Set(&r, Files0_Rider__typ, f, 0);
	Files0_Write(&r, Files0_Rider__typ, 0xf0);
	Files0_Write(&r, Files0_Rider__typ, 0x01);
	Texts0_Store(&r, Files0_Rider__typ, T);
	i = 0;
	while (name[__X(i, name__len)] != 0x00) {
		i += 1;
	}
	__COPY(name, bak, 64);
	bak[__X(i, 64)] = '.';
	bak[__X(i + 1, 64)] = 'B';
	bak[__X(i + 2, 64)] = 'a';
	bak[__X(i + 3, 64)] = 'k';
	bak[__X(i + 4, 64)] = 0x00;
	Files0_Rename(name, name__len, bak, 64, &res);
	Files0_Register(f);
	__DEL(name);
}

static void EnumPtrs(void (*P)(void*))
{
	P(Texts0_new);
	P(Texts0_del);
	P(Texts0_FontsDefault);
}

__TDESC(Texts0_FontDesc, 1, 0) = {__TDFLDS("FontDesc", 32), {-8}};
__TDESC(Texts0_RunDesc, 1, 3) = {__TDFLDS("RunDesc", 40), {0, 8, 24, -32}};
__TDESC(Texts0_PieceDesc, 1, 4) = {__TDFLDS("PieceDesc", 56), {0, 8, 24, 40, -40}};
__TDESC(Texts0_ElemMsg, 1, 0) = {__TDFLDS("ElemMsg", 1), {-8}};
__TDESC(Texts0_ElemDesc, 1, 4) = {__TDFLDS("ElemDesc", 72), {0, 8, 24, 64, -40}};
__TDESC(Texts0_FileMsg, 1, 1) = {__TDFLDS("FileMsg", 56), {32, -16}};
__TDESC(Texts0_CopyMsg, 1, 1) = {__TDFLDS("CopyMsg", 8), {0, -16}};
__TDESC(Texts0_IdentifyMsg, 1, 0) = {__TDFLDS("IdentifyMsg", 64), {-8}};
__TDESC(Texts0_BufDesc, 1, 1) = {__TDFLDS("BufDesc", 16), {8, -16}};
__TDESC(Texts0_TextDesc, 1, 2) = {__TDFLDS("TextDesc", 32), {8, 16, -24}};
__TDESC(Texts0_Reader, 1, 4) = {__TDFLDS("Reader", 96), {8, 24, 48, 72, -40}};
__TDESC(Texts0_Scanner, 1, 4) = {__TDFLDS("Scanner", 208), {8, 24, 48, 72, -40}};
__TDESC(Texts0_Writer, 1, 4) = {__TDFLDS("Writer", 72), {0, 8, 40, 64, -40}};
__TDESC(Texts0__1, 1, 5) = {__TDFLDS("", 160), {0, 8, 24, 64, 72, -48}};

export void *Texts0__init(void)
{
	__DEFMOD;
	__IMPORT(Files0);
	__IMPORT(Modules);
	__IMPORT(Reals);
	__REGMOD("Texts0", EnumPtrs);
	__INITYP(Texts0_FontDesc, Texts0_FontDesc, 0);
	__INITYP(Texts0_RunDesc, Texts0_RunDesc, 0);
	__INITYP(Texts0_PieceDesc, Texts0_RunDesc, 1);
	__INITYP(Texts0_ElemMsg, Texts0_ElemMsg, 0);
	__INITYP(Texts0_ElemDesc, Texts0_RunDesc, 1);
	__INITYP(Texts0_FileMsg, Texts0_ElemMsg, 1);
	__INITYP(Texts0_CopyMsg, Texts0_ElemMsg, 1);
	__INITYP(Texts0_IdentifyMsg, Texts0_ElemMsg, 1);
	__INITYP(Texts0_BufDesc, Texts0_BufDesc, 0);
	__INITYP(Texts0_TextDesc, Texts0_TextDesc, 0);
	__INITYP(Texts0_Reader, Texts0_Reader, 0);
	__INITYP(Texts0_Scanner, Texts0_Reader, 1);
	__INITYP(Texts0_Writer, Texts0_Writer, 0);
	__INITYP(Texts0__1, Texts0_ElemDesc, 2);
/* BEGIN */
	Texts0_del = NIL;
	__NEW(Texts0_FontsDefault, Texts0_FontDesc);
	__MOVE("Syntax10.Scn.Fnt", Texts0_FontsDefault->name, 17);
	__ENDMOD;
}
