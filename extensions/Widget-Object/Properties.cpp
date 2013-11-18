#include "Common.hpp"

namespace Prop
{
	enum PropID
	{
		 zUnused = PROPID_EXTITEM_CUSTOM_FIRST,
		 About_Header,
		 About_Name,
		 About_ID,
		 About_Version,
		 About_Author,
		 About_EndHeader,
	};
}

BOOL MMF2Func GetProperties(mv *mV, SerializedED *SED, BOOL MasterItem)
{
	DM("GetProperties(ppi", "mV", mV, "SED", SED, "MasterItem", MasterItem);
	static PropData about_props[] =
	{
		PropData_Group           (Prop::About_Header,    (UINT_PTR)"Widget+",           (UINT_PTR)"Information about this Widget"),
		PropData_StaticString    (Prop::About_Name,      (UINT_PTR)"Widget Name",       (UINT_PTR)"The Name of this widget"),
		PropData_StaticString_Opt(Prop::About_ID,        (UINT_PTR)"Widget ID",         (UINT_PTR)"The ID of this widget", PROPOPT_BOLD),
		PropData_StaticString    (Prop::About_Version,   (UINT_PTR)"Widget Version",    (UINT_PTR)"The Version of this widget"),
		PropData_StaticString    (Prop::About_Author,    (UINT_PTR)"Widget Author",     (UINT_PTR)"The Author of this widget"),
		PropData_Group           (Prop::About_EndHeader, (UINT_PTR)"Widget+ Extension", (UINT_PTR)"Information about the Widget+ Extension"),
		PropData_End()
	};
	mvInsertProps(mV, SED, about_props, PROPID_TAB_ABOUT, FALSE);
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
	switch(PropID)
	{
	case Prop::About_ID: return FALSE;
	}
	return TRUE;
}

LPVOID MMF2Func GetPropValue(mv *mV, SerializedED *SED, unsigned int PropID)
{
	DM("GetPropValue(ppi", "mV", mV, "SED", SED, "PropID", PropID);
	ED ed (SED);
	json_value &info = *ed.json;
	switch(PropID)
	{
	case Prop::About_Name:    return new CPropDataValue(info["Name"]);
	case Prop::About_ID:      return new CPropDataValue(info["ID"]);
	case Prop::About_Version: return new CPropDataValue(info["Version"]);
	case Prop::About_Author:  return new CPropDataValue(info["Author"]);
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
