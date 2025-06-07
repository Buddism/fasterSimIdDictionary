#include <Windows.h>

#define RBH_DEBUGPRINT true
#include "RedoBlHooks.hpp"
#include "torque.hpp"

typedef unsigned int U32;
typedef signed int S32;
typedef float F32;

const U32 gIdDictionary_hashTableSize = 1<<19; // 1 << 19


#define gId_patchInt(offset, target, text) \
	target = rbh_ScanFunctionHex((char*)text); \
	if (!target) { \
		rbh_BlPrintf("fastSimIDPatch || Cannot find "#target"!"); \
		return false; \
	} \
	if(RBH_DEBUGPRINT) rbh_BlPrintf("fastSimIDPatch || Found "#target" at %08X", (int)target); \
	rbh_PatchInt(target + offset, gIdDictionary_hashTableSize - 1);\

bool init()
{
	//investigate if this needs updating:
	//mightve been able to get away with using rbh_PatchAllMatches in most of these cases
	BlInit;
	if (!tsf_InitInternal())
		return false;

	//tsf_Eval("EnableWinConsole(true);");

	ADDR BlScanHex(initRoot_gIdDictionary_alloc, "B9 00 40 00 00 E8 ? ? ? ? 8B D0");
	rbh_PatchInt(initRoot_gIdDictionary_alloc + 1, gIdDictionary_hashTableSize * 4);

	ADDR BlScanHex(initRoot_gIdDictionary_memset, "B9 00 10 00 00 33 C0");
	rbh_PatchInt(initRoot_gIdDictionary_memset + 1, gIdDictionary_hashTableSize);
	

	ADDR gId_patchInt(1, sub_44D290_loc_44D2D0, "25 FF 0F 00 00 8B 04 81");
	ADDR gId_patchInt(1, sub_44D290_loc_44D2FE, "25 FF 0F 00 00 8D 0C 81");
	ADDR gId_patchInt(1, sub_461DA0_63, "25 FF 0F 00 00 8B 34 86 85 F6 74 56");
	ADDR gId_patchInt(1, sub_482270_loc_482296, "25 FF 0F 00 00 89 0D");
	ADDR gId_patchInt(1, sub_595BF0_28, "25 FF 0F 00 00 8B 34 86 85 F6 74 12");

	ADDR gId_patchInt(2, sub_413D80_10, "81 E1 FF 0F 00 00 8B 04 88 85 C0 74 0C 39 50 20 74 09 8B 40 10 85 C0 75 F4 33 C0 6A 00 68 ? ? ? ? 68 ? ? ? ? 6A 00 50 E8 ? ? ? ? 83 C4 14 89 46 40");
	ADDR gId_patchInt(2, sub_413D80_70, "81 E1 FF 0F 00 00 8B 04 88 85 C0 74 0C 39 50 20 74 09 8B 40 10 85 C0 75 F4 33 C0 6A 00 68 ? ? ? ? 68 ? ? ? ? 6A 00 50 E8 ? ? ? ? 83 C4 14 89 46 48");
	ADDR gId_patchInt(2, Codeblock__Exec_42FD20_1981, "81 E2 FF 0F 00 00 8B 04 91 89 46 10");
	ADDR gId_patchInt(2, Codeblock__Exec_42FD20_loc_431B07, "81 E2 FF 0F 00 00 C1 E2 02");
	ADDR gId_patchInt(2, sub_44ADD0_73, "81 E1 FF 0F 00 00 8B 04 88 85 C0 74 10 39 50 20");
	ADDR gId_patchInt(2, sub_44ADD0_A1, "81 E2 FF 0F 00 00 83 C4 04 8B 0C 91 85 C9 74 13");
	ADDR gId_patchInt(2, sub_44C2E0_4, "81 E1 FF 0F 00 00 8D 0C 88");
	ADDR gId_patchInt(2, Sim__findObject_44C740_45, "81 E2 FF 0F 00 00 8B 04 91 85 C0");
	ADDR gId_patchInt(2, Sim__findObject_44C740_79, "81 E2 FF 0F 00 00 83 C4 04 8B 0C 91 85 C9 74 DB");
	ADDR gId_patchInt(2, sub_44C860, "81 E2 FF 0F 00 00 8B 04 90 85 C0 74 0C 39 48 20");
	ADDR gId_patchInt(2, sub_464D10_D8, "81 E1 FF 0F 00 00 8B 04 88 85 C0 74 14");
	ADDR gId_patchInt(2, sub_464D10_10A, "81 E2 FF 0F 00 00 83 C4 04 8B 0C 91 85 C9 74 0C");
	ADDR gId_patchInt(2, sub_465CB0_ED, "81 E1 FF 0F 00 00 8B 0C 88");
	ADDR gId_patchInt(2, sub_466F60_E, "81 E2 FF 0F 00 00 8B 04 90 85 C0 74 0C 39 70 20 74 09 8B 40 10 85 C0 75 F4 33 C0 8D 54 24 07");
	ADDR gId_patchInt(2, sub_477B60_loc_477BBA, "81 E2 FF 0F 00 00 8B 0C 91 85 C9 74 0D");
	ADDR gId_patchInt(2, sub_4785B0_390, "81 E1 FF 0F 00 00 8B 04 88 85 C0 74 0C 39 50 20 74 09 8B 40 10 85 C0 75 F4 33 C0 6A 00 68 ? ? ? ? 68 ? ? ? ? 6A 00 50 E8 ? ? ? ? 83 C4 14 89 86 A8 00 00 00");
	ADDR gId_patchInt(2, sub_4785B0_400, "81 E1 FF 0F 00 00 8B 04 88 85 C0 74 0C 39 50 20 74 09 8B 40 10 85 C0 75 F4 33 C0 6A 00 68 ?? ?? ?? ?? 68 ?? ?? ?? ?? 6A 00 50 E8 ?? ?? ?? ?? 83 C4 14 89 47 F0");
	ADDR gId_patchInt(2, sub_4785B0_46D, "81 E1 FF 0F 00 00 8B 04 88 85 C0 74 0C 39 50 20 74 09 8B 40 10 85 C0 75 F4 33 C0 6A 00 68 ? ? ? ? 68 ? ? ? ? 6A 00 50 E8 ? ? ? ? 83 C4 14 89 46 EC");
	ADDR gId_patchInt(2, sub_489220_6E, "81 E1 FF 0F 00 00 8B 04 88 85 C0 74 0C 39 50 20 74 09 8B 40 10 85 C0 75 F4 33 C0 6A 00 68 ? ? ? ? 68 ? ? ? ? 6A 00 50 E8 ? ? ? ? 83 C4 14 85 C0 74 0C");
	ADDR gId_patchInt(2, sub_492B90_C8, "81 E1 FF 0F 00 00 8B 04 88 85 C0 74 12 8D 9B 00 00 00 00 39 50 20 74 09 8B 40 10 85 C0 75 F4 33 C0 6A 00 68 ? ? ? ? 68 ? ? ? ? 6A 00 50 E8 ? ? ? ? 83 C4 14 85 C0");
	ADDR gId_patchInt(2, sub_492F30_AC, "81 E1 FF 0F 00 00 8B 04 88 85 C0 74 0E 8B FF 39 50 20 74 09 8B 40 10 85 C0 75 F4 33 C0 6A 00 68 ? ? ? ? 68 ? ? ? ? 6A 00 50 E8 ? ? ? ? 8B F0");
	ADDR gId_patchInt(2, sub_493470_7C, "81 E1 FF 0F 00 00 8B 04 88 85 C0 74 0E 8B FF 39 50 20 74 09 8B 40 10 85 C0 75 F4 33 C0 6A 00 68 ? ? ? ? 68 ? ? ? ? 6A 00 50 E8 ? ? ? ? 83 C4 14 85 C0");
	ADDR gId_patchInt(2, sub_4935E0_loc_493752, "81 E2 FF 0F 00 00 8B 0C 91 85 C9 74 0C 39 59 20");
	ADDR gId_patchInt(2, sub_4A16C0_33, "81 E1 FF 0F 00 00 8B 04 88 85 C0 74 0C 39 50 20 74 09 8B 40 10 85 C0 75 F4 33 C0 6A 00 68 ? ? ? ? 68 ? ? ? ? 6A 00 50 E8 ? ? ? ? 83 C4 14 85 C0 74 08");
	ADDR gId_patchInt(2, sub_4A1A70_25, "81 E1 FF 0F 00 00 8B 04 88 85 C0 74 13 8D A4 24 00 00 00 00 39 50 20 74 09 8B 40 10 85 C0 75 F4 33 C0 6A 00 68 ? ? ? ? 68 ? ? ? ? 6A 00 50 E8 ? ? ? ? 83 C4 14");
	ADDR gId_patchInt(2, sub_4A1A70_94, "81 E1 FF 0F 00 00 8B 04 88 85 C0 74 0C 39 50 20 74 09 8B 40 10 85 C0 75 F4 33 C0 6A 00 68 ? ? ? ? 68 ? ? ? ? 6A 00 50 E8 ? ? ? ? 83 C4 14 89 43 64");
	ADDR gId_patchInt(2, sub_4A5F70_23B, "81 E1 FF 0F 00 00 8B 04 88 85 C0 74 0F 8D 49 00 39 50 20 74 09 8B 40 10 85 C0 75 F4 33 C0 6A 00 68 ? ? ? ? 68 ? ? ? ? 6A 00 50 E8 ? ? ? ? 8B C8");
	ADDR gId_patchInt(2, sub_4A64A0_loc_4A64D7, "81 E2 FF 0F 00 00 8B 0C 91 85 C9 74 10");
	ADDR gId_patchInt(2, sub_4A7C50_2B, "81 E1 FF 0F 00 00 8B 04 88 85 C0 74 0F 8D 49 00 39 50 20 74 09 8B 40 10 85 C0 75 F4 33 C0 6A 00 68 ? ? ? ? 68 ? ? ? ? 6A 00 50 E8 ? ? ? ? 83 C4 14 89 44 24 10");
	ADDR gId_patchInt(2, sub_4B0D70_4D, "81 E1 FF 0F 00 00 8B 04 88 85 C0 74 0C 39 50 20 74 09 8B 40 10 85 C0 75 F4 33 C0 6A 00 68 ? ? ? ? 68 ? ? ? ? 6A 00 50 E8 ? ? ? ? 83 C4 14 89 46 F4");
	ADDR gId_patchInt(2, sub_4B0D70_122, "81 E1 FF 0F 00 00 8B 04 88 85 C0 74 0C 39 50 20 74 09 8B 40 10 85 C0 75 F4 33 C0 6A 00 68 ? ? ? ? 68 ? ? ? ? 6A 00 50 E8 ? ? ? ? 83 C4 14 89 83 00 01 00 00");
	ADDR gId_patchInt(2, sub_4B6DD0_91, "81 E2 FF 0F 00 00 8B 0C 91 85 C9 74 0C 39 41 20 74 09 8B 49 10 85 C9 75 F4 33 C9 6A 00 68 ? ? ? ? 68 ? ? ? ? 6A 00 51 E8 ? ? ? ? 8B D0");
	ADDR gId_patchInt(2, sub_4B87B0_loc_4B87F0, "81 E2 FF 0F 00 00 8B 04 90 85 C0 74 0C 39 70 20 74 09 8B 40 10 85 C0 75 F4 33 C0 6A 00");
	ADDR gId_patchInt(2, sub_4B87B0_D7, "81 E1 FF 0F 00 00 8B 04 88 85 C0 74 13 8D A4 24 00 00 00 00 39 50 20 74 09 8B 40 10 85 C0 75 F4 33 C0 6A 00 68 ? ? ? ? 68 ? ? ? ? 6A 00 50 E8 ? ? ? ? 8B 0F");
	ADDR gId_patchInt(2, sub_4BB7C0_E, "81 E2 FF 0F 00 00 57");
	ADDR gId_patchInt(2, sub_4BBAA0_9C, "81 E1 FF 0F 00 00 8B 04 88 85 C0 74 0C 39 50 20 74 09 8B 40 10 85 C0 75 F4 33 C0 6A 00 68 ? ? ? ? 68 ? ? ? ? 6A 00 50 E8 ? ? ? ? 8B F0");
	ADDR gId_patchInt(2, sub_4BBAA0_loc_4BBC3C, "81 E6 FF 0F 00 00 8B 04 B2");
	ADDR gId_patchInt(2, sub_4BBD60_2C, "81 E1 FF 0F 00 00 8B 04 88 85 C0 74 0C 39 50 20 74 09 8B 40 10 85 C0 75 F4 33 C0 6A 00 68 ? ? ? ? 68 ? ? ? ? 6A 00 50 E8 ? ? ? ? 83 C4 14 89 46 10");
	ADDR gId_patchInt(2, sub_4BBF70_36, "81 E1 FF 0F 00 00 8B 04 88 85 C0 74 12 8D 9B 00 00 00 00 39 50 20 74 09 8B 40 10 85 C0 75 F4 33 C0 6A 00 68 ? ? ? ? 68 ? ? ? ? 6A 00 50 E8 ? ? ? ? 89 47 10");
	ADDR gId_patchInt(2, sub_4C2A70_loc_4C2A85, "81 E2 FF 0F 00 00 8B 0C 91 85 C9 74 12");
	ADDR gId_patchInt(2, sub_4D2940_56, "81 E1 FF 0F 00 00 8B 04 88 85 C0 74 12 8D 9B 00 00 00 00 39 50 20 74 09 8B 40 10 85 C0 75 F4 33 C0 6A 00 68 ? ? ? ? 68 ? ? ? ? 6A 00 50 E8 ? ? ? ? 83 C4 14 89 07");
	ADDR gId_patchInt(2, sub_4D2940_64A, "81 E1 FF 0F 00 00 8B 04 88 85 C0 74 0E 8B FF 39 50 20 74 09 8B 40 10 85 C0 75 F4 33 C0 6A 00 68 ? ? ? ? 68 ? ? ? ? 6A 00 50 E8 ? ? ? ? 83 C4 14 89 86 A4 0B 00 00");
	ADDR gId_patchInt(2, sub_4D2940_6BA, "81 E1 FF 0F 00 00 8B 04 88 85 C0 74 0E 8B FF 39 50 20 74 09 8B 40 10 85 C0 75 F4 33 C0 6A 00 68 ? ? ? ? 68 ? ? ? ? 6A 00 50 E8 ? ? ? ? 83 C4 14 89 86 B4 0B 00 00");
	ADDR gId_patchInt(2, sub_4D2940_72C, "81 E1 FF 0F 00 00 8B 04 88 85 C0 74 0C 39 50 20 74 09 8B 40 10 85 C0 75 F4 33 C0 6A 00 68 ? ? ? ? 68 ? ? ? ? 6A 00 50 E8 ? ? ? ? 83 C4 14 89 47 F4");
	ADDR gId_patchInt(2, sub_4D2940_79A, "81 E1 FF 0F 00 00 8B 04 88 85 C0 74 0E 8B FF 39 50 20 74 09 8B 40 10 85 C0 75 F4 33 C0 6A 00 68 ? ? ? ? 68 ? ? ? ? 6A 00 50 E8 ? ? ? ? 83 C4 14 89 86 84 0B 00 00");
	ADDR gId_patchInt(2, sub_4D2940_80E, "81 E1 FF 0F 00 00 8B 04 88 85 C0 74 0C 39 50 20 74 09 8B 40 10 85 C0 75 F4 33 C0 6A 00 68 ? ? ? ? 68 ? ? ? ? 6A 00 50 E8 ? ? ? ? 83 C4 14 89 86 8C 0B 00 00");
	ADDR gId_patchInt(2, sub_4D2940_880, "81 E1 FF 0F 00 00 8B 04 88 85 C0 74 0C 39 50 20 74 09 8B 40 10 85 C0 75 F4 33 C0 6A 00 68 ? ? ? ? 68 ? ? ? ? 6A 00 50 E8 ? ? ? ? 83 C4 14 89 86 BC 0B 00 00");
	ADDR gId_patchInt(2, sub_4F7900_24D, "81 E1 FF 0F 00 00 8B 04 88 85 C0 74 0C 39 50 20 74 09 8B 40 10 85 C0 75 F4 33 C0 6A 00 68 ? ? ? ? 68 ? ? ? ? 6A 00 50 E8 ? ? ? ? 83 C4 14 89 45 EC");
	ADDR gId_patchInt(2, sub_4FC740_66, "81 E1 FF 0F 00 00 8B 04 88 85 C0 74 12 8D 9B 00 00 00 00 39 50 20 74 09 8B 40 10 85 C0 75 F4 33 C0 6A 00 68 ? ? ? ? 68 ? ? ? ? 6A 00 50 E8 ? ? ? ? 83 C4 14 89 83 F8 0C 00 00");
	ADDR gId_patchInt(2, sub_4FC740_B9, "81 E1 FF 0F 00 00 8B 04 88 85 C0 74 0F 8D 49 00 39 50 20 74 09 8B 40 10 85 C0 75 F4 33 C0 6A 00 68 ? ? ? ? 68 ? ? ? ? 6A 00 50 E8 ? ? ? ? 83 C4 14 89 06");
	ADDR gId_patchInt(2, sub_4FC740_138, "81 E1 FF 0F 00 00 8B 04 88 85 C0 74 10 8D 64 24 00");
	ADDR gId_patchInt(2, sub_507690_AC, "81 E1 FF 0F 00 00 8B 04 88 85 C0 74 0C 39 50 20 74 09 8B 40 10 85 C0 75 F4 33 C0 6A 00 68 ? ? ? ? 68 ? ? ? ? 6A 00 50 E8 ? ? ? ? 83 C4 14 89 06");
	ADDR gId_patchInt(2, sub_507690_106, "81 E1 FF 0F 00 00 8B 04 88 85 C0 74 12 8D 9B 00 00 00 00 39 50 20 74 09 8B 40 10 85 C0 75 F4 33 C0 6A 00 68 ? ? ? ? 68 ? ? ? ? 6A 00 50 E8 ? ? ? ? 83 C4 14 89 06 83 C6 04 83 EF 01 75 B1 8B 75 F0");
	ADDR gId_patchInt(2, sub_50A9F0_36, "81 E1 FF 0F 00 00 8B 04 88 85 C0 74 12 8D 9B 00 00 00 00 39 50 20 74 09 8B 40 10 85 C0 75 F4 33 C0 6A 00 68 ? ? ? ? 68 ? ? ? ? 6A 00 50 E8 ? ? ? ? 83 C4 14 89 06 83 C6 04 83 EF 01 75 B1 83 BD F0 02 00 00 00");
	ADDR gId_patchInt(2, sub_50A9F0_CD, "81 E1 FF 0F 00 00 8B 04 88 85 C0 74 0C 39 50 20 74 09 8B 40 10 85 C0 75 F4 33 C0 6A 00 68 ? ? ? ? 68 ? ? ? ? 6A 00 50 E8 ? ? ? ? 83 C4 14 89 46 DC");
	ADDR gId_patchInt(2, sub_50A9F0_13C, "81 E1 FF 0F 00 00 8B 04 88 85 C0 74 0C 39 50 20 74 09 8B 40 10 85 C0 75 F4 33 C0 6A 00 68 ? ? ? ? 68 ? ? ? ? 6A 00 50 E8 ? ? ? ? 83 C4 14 89 46 F8");
	ADDR gId_patchInt(2, sub_50B240_443, "81 E1 FF 0F 00 00 8B 04 88 85 C0 74 0C 39 50 20 74 09 8B 40 10 85 C0 75 F4 33 C0 6A 00 68 ? ? ? ? 68 ? ? ? ? 6A 00 50 E8 ? ? ? ? 83 C4 14 89 07");
	ADDR gId_patchInt(2, sub_511AE0_A7, "81 E1 FF 0F 00 00 8B 04 88 85 C0 74 11");
	ADDR gId_patchInt(2, sub_511AE0_FF, "81 E1 FF 0F 00 00 8B 04 88 85 C0 74 0C 39 50 20 74 09 8B 40 10 85 C0 75 F4 33 C0 6A 00 68 ? ? ? ? 68 ? ? ? ? 6A 00 50 E8 ? ? ? ? 83 C4 14 89 86 64 03 00 00");
	ADDR gId_patchInt(2, sub_516DA0_D0, "81 E1 FF 0F 00 00 8D 58 03");
	ADDR gId_patchInt(2, sub_516DA0_10F, "81 E1 FF 0F 00 00 8B 04 88 85 C0 74 0C 39 58 20");
	ADDR gId_patchInt(2, sub_592AD0_4C0, "81 E1 FF 0F 00 00 03 15");
	ADDR gId_patchInt(2, sub_59D0C0_loc_59D18E, "81 E2 FF 0F 00 00 8B 0C 91 85 C9 74 0C 39 41 20 74 09 8B 49 10 85 C9 75 F4 33 C9 6A 00 68 ? ? ? ? 68 ? ? ? ? 6A 00 51 E8 ? ? ? ? 83 C4 14");
	ADDR gId_patchInt(2, sub_59D0C0_loc_59D234, "81 E2 FF 0F 00 00 8B 0C 91 85 C9 74 13");


	ADDR gId_patchInt(54, sub_4716E0_2D, "83 EC 08 56 8B F1 E8 ? ? ? ? 84 C0 75 05 5E 83 C4 08 C3 53");
	ADDR gId_patchInt(162, sub_4716E0_99, "83 EC 08 56 8B F1 E8 ? ? ? ? 84 C0 75 05 5E 83 C4 08 C3 53");

	ADDR BlScanHex(sub1_4744C0, "E8 ? ? ? ? 84 C0 75 15 FF B6 0C 02 00 00");
	ADDR BlScanHex(sub2_4E8410, "E8 ? ? ? ? 84 C0 75 15 FF B6 E8 00 00 00");
	ADDR BlScanHex(sub3_474510, "E8 ? ? ? ? 84 C0 75 12 FF 73 60");
	ADDR BlScanHex(sub4_47BA50, "E8 ? ? ? ? 8B 43 54");
	ADDR BlScanHex(sub5_47BAA0, "E8 ? ? ? ? 84 C0 74 71");
	ADDR BlScanHex(sub6_4A5500, "E8 ? ? ? ? 84 C0 74 19 FF 75 F0");
	
	//relative calls
	//enjoy magical numbers (maybe there is a less dumb way of doing this)
	rbh_PatchInt((sub1_4744C0 + 5 + (*(ADDR*)(sub1_4744C0 + 1)) + 10), gIdDictionary_hashTableSize - 1);
	rbh_PatchInt((sub2_4E8410 + 5 + (*(ADDR*)(sub2_4E8410 + 1)) + 10), gIdDictionary_hashTableSize - 1);
	rbh_PatchInt((sub3_474510 + 5 + (*(ADDR*)(sub3_474510 + 1)) + 10), gIdDictionary_hashTableSize - 1);
	rbh_PatchInt((sub4_47BA50 + 5 + (*(ADDR*)(sub4_47BA50 + 1)) + 10), gIdDictionary_hashTableSize - 1);
	rbh_PatchInt((sub5_47BAA0 + 5 + (*(ADDR*)(sub5_47BAA0 + 1)) + 10), gIdDictionary_hashTableSize - 1);
	rbh_PatchInt((sub6_4A5500 + 5 + (*(ADDR*)(sub6_4A5500 + 1)) + 10), gIdDictionary_hashTableSize - 1);

	ADDR BlScanHex(Codeblock__Exec_42FD20_loc_431B88, "8B 89 FC 3F 00 00");
	ADDR BlScanHex(CodeBlock__exec_42FD20_1DA3, "8B 80 FC 3F 00 00 85 C0 74 0D");
	ADDR BlScanHex(sub_547740_loc_54776B, "8B 80 FC 3F 00 00 85 C0 74 13");
	rbh_PatchInt(Codeblock__Exec_42FD20_loc_431B88 + 2, (gIdDictionary_hashTableSize - 1) * 4);
	rbh_PatchInt(CodeBlock__exec_42FD20_1DA3 + 2, (gIdDictionary_hashTableSize - 1) * 4);
	rbh_PatchInt(sub_547740_loc_54776B + 2, (gIdDictionary_hashTableSize - 1) * 4);

	return true;
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		return init();
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

//extern "C" void __declspec(dllexport) __cdecl fasterSimIdDictionary() {}

