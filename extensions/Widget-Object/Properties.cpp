#include "Common.hpp"

namespace Prop
{
	enum PropID
	{
		About_WigitID = PROPID_EXTITEM_CUSTOM_FIRST
	};
	ED *info = 0;
}

BOOL MMF2Func GetProperties(mv *mV, SerializedED *SED, BOOL MasterItem)
{
	DM("GetProperties(ppi", "mV", mV, "SED", SED, "MasterItem", MasterItem);
	if(!Prop::info) Prop::info = new ED(SED);
	static PropData about_props[] =
	{
		PropData_StaticString(Prop::About_WigitID, (UINT_PTR)"Widget ID", (UINT_PTR)"The ID of this widget")
	};
	mvInsertProps(mV, SED, about_props, PROPID_TAB_ABOUT, TRUE);
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
	if(Prop::info) delete Prop::info, Prop::info = 0;
}

BOOL MMF2Func IsPropEnabled(mv *mV, SerializedED *SED, unsigned int PropID)
{
	DM("IsPropEnabled(ppi", "mV", mV, "SED", SED, "PropID", PropID);
	return TRUE;
}

LPVOID MMF2Func GetPropValue(mv *mV, SerializedED *SED, unsigned int PropID)
{
	DM("GetPropValue(ppi", "mV", mV, "SED", SED, "PropID", PropID);
	if(PropID == Prop::About_WigitID)
	{
		if(Prop::info)
		{
			return new CPropDataValue(Prop::info->wid.c_str());
		}
		else
		{
			return new CPropDataValue("");
		}
	}
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
