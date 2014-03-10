#include "Common.hpp"

HMENU MMF2Func GetConditionMenu(mv *mV, OI *oi, SerializedED *SED)
{	DST();
	DM("GetConditionMenu(ppp", "mV", mV, "oi", oi, "SED", SED);
	return NULL;
}
HMENU MMF2Func GetActionMenu(mv *mV, OI *oi, SerializedED *SED)
{	DST();
	DM("GetActionMenu(ppp", "mV", mV, "oi", oi, "SED", SED);
	return NULL;
}
HMENU MMF2Func GetExpressionMenu(mv *mV, OI *oi, SerializedED *SED)
{	DST();
	DM("GetExpressionMenu(ppp", "mV", mV, "oi", oi, "SED", SED);
	return NULL;
}

void MMF2Func GetConditionTitle(mv *mV, short ID, short ParamID, LPTSTR Buffer, short MaxLen)
{	DST();
	DM("GetConditionTitle(piipi", "mV", mV, "ID", int(ID), "ParamID", int(ParamID), "Buffer", Buffer, "MaxLen", int(MaxLen));
}
void MMF2Func GetActionTitle(mv *mV, short ID, short ParamID, LPTSTR Buffer, short MaxLen)
{	DST();
	DM("GetActionTitle(piipi", "mV", mV, "ID", int(ID), "ParamID", int(ParamID), "Buffer", Buffer, "MaxLen", int(MaxLen));
}
void MMF2Func GetExpressionTitle(mv *mV, short ID, LPTSTR Buffer, short MaxLen)
{	DST();
	DM("GetExpressionTitle(pipi", "mV", mV, "ID", int(ID), "Buffer", Buffer, "MaxLen", int(MaxLen));
}
void MMF2Func GetExpressionParam(mv *mV, short ID, short ParamID, LPTSTR Buffer, short MaxLen)
{	DST();
	DM("GetExpressionParam(piipi", "mV", mV, "ID", int(ID), "ParamID", int(ParamID), "Buffer", Buffer, "MaxLen", int(MaxLen));
}

short MMF2Func GetConditionCodeFromMenu(mv *mV, short MenuID)
{	DST();
	DM("GetConditionCodeFromMenu(pi", "mV", mV, "MenuID", int(MenuID));
	return 0;
}
short MMF2Func GetActionCodeFromMenu(mv *mV, short MenuID)
{	DST();
	DM("GetActionCodeFromMenu(pi", "mV", mV, "MenuID", int(MenuID));
	return 0;
}
short MMF2Func GetExpressionCodeFromMenu(mv *mV, short MenuID)
{	DST();
	DM("GetExpressionCodeFromMenu(pi", "mV", mV, "MenuID", int(MenuID));
	return 0;
}

LPINFOEVENTSV2 MMF2Func GetConditionInfos(mv *mV, short ID)
{	DST();
	DM("GetConditionInfos(pi", "mV", mV, "ID", int(ID));
	return NULL;
}
LPINFOEVENTSV2 MMF2Func GetActionInfos(mv *mV, short ID)
{	DST();
	DM("GetActionInfos(pi", "mV", mV, "ID", int(ID));
	return NULL;
}
LPINFOEVENTSV2 MMF2Func GetExpressionInfos(mv *mV, short ID)
{	DST();
	DM("GetExpressionInfos(pi", "mV", mV, "ID", int(ID));
	return NULL;
}

void MMF2Func GetConditionString(mv *mV, short ID, LPTSTR Buffer, short MaxLen)
{	DST();
	DM("GetConditionString(pipi", "mV", mV, "ID", int(ID), "Buffer", Buffer, "MaxLen", MaxLen);
}
void MMF2Func GetActionString(mv *mV, short ID, LPTSTR Buffer, short MaxLen)
{	DST();
	DM("GetActionString(pipi", "mV", mV, "ID", int(ID), "Buffer", Buffer, "MaxLen", MaxLen);
}
void MMF2Func GetExpressionString(mv *mV, short ID, LPTSTR Buffer, short MaxLen)
{	DST();
	DM("GetExpressionString(pipi", "mV", mV, "ID", int(ID), "Buffer", Buffer, "MaxLen", MaxLen);
}

void MMF2Func InitParameter(mv *mV, short ID, paramExt *Parameter)
{	DST();
	DM("InitParameter(pip", "mV", mV, "ID", int(ID), "Parameter", Parameter);
}
void MMF2Func EditParameter(mv *mV, short ID, paramExt *Parameter)
{	DST();
	DM("EditParameter(pip", "mV", mV, "ID", int(ID), "Parameter", Parameter);
}
void MMF2Func GetParameterString(mv *mV, short ID, paramExt *Parameter, LPTSTR Buffer, short MaxLen)
{	DST();
	DM("GetParameterString(pippi", "mV", mV, "ID", int(ID), "Parameter", Parameter, "Buffer", Buffer, "MaxLen", int(MaxLen));
}
