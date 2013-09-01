#include "Common.hpp"

BOOL MMF2Func GetProperties(mv *mV, SerializedED *SED, BOOL MasterItem)
{
	DM("GetProperties(ppi", "mV", mV, "SED", SED, "MasterItem", MasterItem);
	return TRUE;
}
LPARAM MMF2Func GetPropCreateParam(mv *mV, SerializedED *SED, unsigned int PropID)
{
	DM("GetPropCreateParam(ppi", "mV", mV, "SED", SED, "PropID", PropID);
	return NULL;
}
void MMF2Func ReleasePropCreateParam(mv *mV, SerializedED *SED, unsigned int PropID, LPARAM lParam)
{
	DM("ReleasePropCreateParam(ppii", "mV", mV, "SED", SED, "PropID", PropID, "lParam", lParam);
}
void MMF2Func ReleaseProperties(mv *mV, SerializedED *SED, BOOL MasterItem)
{
	DM("ReleaseProperties(ppi", "mV", mV, "SED", SED, "MasterItem", MasterItem);
}

BOOL MMF2Func IsPropEnabled(mv *mV, SerializedED *SED, unsigned int PropID)
{
	DM("IsPropEnabled(ppi", "mV", mV, "SED", SED, "PropID", PropID);
	return TRUE;
}

LPVOID MMF2Func GetPropValue(mv *mV, SerializedED *SED, unsigned int PropID)
{
	DM("GetPropValue(ppi", "mV", mV, "SED", SED, "PropID", PropID);
	return NULL;
}
BOOL MMF2Func GetPropCheck(mv *mV, SerializedED *SED, unsigned int PropID)
{
	DM("GetPropCheck(ppi", "mV", mV, "SED", SED, "PropID", PropID);
	return FALSE;
}
void MMF2Func SetPropValue(mv *mV, SerializedED *SED, unsigned int PropID, LPVOID lParam)
{
	DM("SetPropValue(ppii", "mV", mV, "SED", SED, "PropID", PropID, "lParam", lParam);
}
void MMF2Func SetPropCheck(mv *mV, SerializedED *SED, unsigned int PropID, BOOL Checked)
{
	DM("SetPropCheck(ppii", "mV", mV, "SED", SED, "PropID", PropID, "Checked", Checked);
}
BOOL MMF2Func EditProp(mv *mV, SerializedED *SED, unsigned int PropID)
{
	DM("EditProp(ppi", "mV", mV, "SED", SED, "PropID", PropID);
	return TRUE;
}
