#include "Common.hpp"

LPWORD MMF2Func GetDebugTree(RD *rd)
{
	DM("GetDebugTree(p", "rd", rd);
	return NULL;
}

void MMF2Func GetDebugItem(LPTSTR Buffer, RD *rd, int ID)
{
	DB_BUFFERSIZE;
	DM("GetDebugItem(ppi", "Buffer", Buffer, "rd", rd, "ID", ID);
}

void MMF2Func EditDebugItem(RD *rd, int ID)
{
	DM("EditDebugItem(pi", "rd", rd, "ID", ID);
}
