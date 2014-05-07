/* voc  1.0  [2013/09/23] xtspkamPS */
#include "SYSTEM.h"
#include "Kernel0.h"
#include "OPB.h"
#include "OPC.h"
#include "OPM.h"
#include "OPP.h"
#include "OPT.h"
#include "OPV.h"
#include "Strings.h"
#include "Unix.h"
#include "extTools.h"
#include "vt100.h"


static CHAR voc_mname[256];


export void voc_Module (BOOLEAN *done);
export void voc_Translate (void);
static void voc_Trap (LONGINT sig, LONGINT code, Unix_SigCtxPtr scp);

#define voc_fin()	SYSTEM_FINALL()
#define voc_halt()	SYSTEM_halt
#define voc_signal(sig, func)	signal(sig, func)

static void voc_Trap (LONGINT sig, LONGINT code, Unix_SigCtxPtr scp)
{
	voc_fin();
	if (sig == 3) {
		Unix_Exit(0);
	} else {
		if ((sig == 4 && voc_halt() == -15)) {
			OPM_LogWStr((CHAR*)" --- voc: internal error", (LONGINT)25);
			OPM_LogWLn();
		}
		Unix_Exit(2);
	}
}

void voc_Module (BOOLEAN *done)
{
	BOOLEAN ext, new;
	OPT_Node p = NIL;
	OPP_Module(&p, OPM_opt);
	if (OPM_noerr) {
		OPV_Init();
		OPV_AdrAndSize(OPT_topScope);
		OPT_Export(&ext, &new);
		if (OPM_noerr) {
			OPM_OpenFiles((void*)OPT_SelfName, 32);
			OPC_Init();
			OPV_Module(p);
			if (OPM_noerr) {
				if (((OPM_mainProg || OPM_mainLinkStat) && __STRCMP(OPM_modName, "SYSTEM") != 0)) {
					OPM_DeleteNewSym();
					if (!OPM_notColorOutput) {
						vt100_SetAttr((CHAR*)"32m", (LONGINT)4);
					}
					OPM_LogWStr((CHAR*)"  main program", (LONGINT)15);
					if (!OPM_notColorOutput) {
						vt100_SetAttr((CHAR*)"0m", (LONGINT)3);
					}
				} else {
					if (new) {
						if (!OPM_notColorOutput) {
							vt100_SetAttr((CHAR*)"32m", (LONGINT)4);
						}
						OPM_LogWStr((CHAR*)"  new symbol file", (LONGINT)18);
						if (!OPM_notColorOutput) {
							vt100_SetAttr((CHAR*)"0m", (LONGINT)3);
						}
						OPM_RegisterNewSym();
					} else if (ext) {
						OPM_LogWStr((CHAR*)"  extended symbol file", (LONGINT)23);
						OPM_RegisterNewSym();
					}
				}
			} else {
				OPM_DeleteNewSym();
			}
		}
	}
	OPM_CloseFiles();
	OPT_Close();
	OPM_LogWLn();
	*done = OPM_noerr;
}

void voc_Translate (void)
{
	BOOLEAN done;
	CHAR modulesobj[2048];
	modulesobj[0] = 0x00;
	OPM_OpenPar();
	OPT_bytetyp->size = OPM_ByteSize;
	OPT_sysptrtyp->size = OPM_PointerSize;
	OPT_chartyp->size = OPM_CharSize;
	OPT_settyp->size = OPM_SetSize;
	OPT_realtyp->size = OPM_RealSize;
	OPT_inttyp->size = OPM_IntSize;
	OPT_linttyp->size = OPM_LIntSize;
	OPT_lrltyp->size = OPM_LRealSize;
	OPT_sinttyp->size = OPM_SIntSize;
	OPT_booltyp->size = OPM_BoolSize;
	for (;;) {
		OPM_Init(&done, (void*)voc_mname, 256);
		if (!done) {
			break;
		}
		OPM_InitOptions();
		Kernel0_GC(0);
		voc_Module(&done);
		if (!done) {
			Unix_Exit(1);
		}
		if (done) {
			if (!OPM_dontAsm) {
				extTools_Assemble(OPM_modName, 32);
				if (!(OPM_mainProg || OPM_mainLinkStat)) {
					Strings_Append((CHAR*)" ", (LONGINT)2, (void*)modulesobj, 2048);
					Strings_Append(OPM_modName, 32, (void*)modulesobj, 2048);
					Strings_Append((CHAR*)".o ", (LONGINT)4, (void*)modulesobj, 2048);
				}
				if ((!OPM_dontLink && (OPM_mainProg || OPM_mainLinkStat))) {
					extTools_LinkMain((void*)OPM_modName, 32, OPM_mainLinkStat, modulesobj, 2048);
				}
			}
		}
	}
}


export main(int argc, char **argv)
{
	__INIT(argc, argv);
	__IMPORT(Kernel0);
	__IMPORT(OPB);
	__IMPORT(OPC);
	__IMPORT(OPM);
	__IMPORT(OPP);
	__IMPORT(OPT);
	__IMPORT(OPV);
	__IMPORT(Strings);
	__IMPORT(Unix);
	__IMPORT(extTools);
	__IMPORT(vt100);
	__REGMAIN("voc", 0);
	__REGCMD("Translate", voc_Translate);
/* BEGIN */
	voc_signal(2, voc_Trap);
	voc_signal(3, voc_Trap);
	voc_signal(4, voc_Trap);
	OPB_typSize = OPV_TypSize;
	OPT_typSize = OPV_TypSize;
	voc_Translate();
	__FINI;
}
