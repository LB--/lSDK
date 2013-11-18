#include "Common.hpp"
#include <sstream>

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

		 DevTab_DevMode,

		 JsonTab_Json,

		 General_Start
	};
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
	static PropData dev_props[] =
	{
		PropData_CheckBox(Prop::DevTab_DevMode, (UINT_PTR)"Enable Developer Mode",
			(UINT_PTR)"Allows widget developers access to the A/C/Es required for programming a widget."),
		PropData_End()
	};
	static PropData json_props[] =
	{
		PropData_EditMultiLine(Prop::JsonTab_Json, (UINT_PTR)"Widget Definition", (UINT_PTR)"The JSON string defining this widget."),
		PropData_End()
	};
}

BOOL MMF2Func GetProperties(mv *mV, SerializedED *SED, BOOL MasterItem)
{
	DM("GetProperties(ppi", "mV", mV, "SED", SED, "MasterItem", MasterItem);
	ED ed (SED);
	if(MasterItem)
	{
		mvInsertProps(mV, SED, Prop::about_props,   PROPID_TAB_ABOUT,   FALSE);
		mvInsertProps(mV, SED, Prop::dev_props,     PROPID_TAB_CUSTOM1, TRUE);
		if(ed.devmode)
		mvInsertProps(mV, SED, Prop::json_props,    PROPID_TAB_CUSTOM1, TRUE);
//		mvInsertProps(mV, SED, Prop::general_props, PROPID_TAB_GENERAL, TRUE);
	}
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
		case Prop::About_Name:     return new CPropDataValue(info["Name"]);
		case Prop::About_ID:       return new CPropDataValue(info["ID"]);
		case Prop::About_Version:  return new CPropDataValue(info["Version"]);
		case Prop::About_Author:   return new CPropDataValue(info["Author"]);

		case Prop::JsonTab_Json:   return new CPropDataValue(EnsureWinNL(ed.Json()).c_str());
	}
	return NULL;
}
BOOL MMF2Func GetPropCheck(mv *mV, SerializedED *SED, unsigned int PropID)
{
	DM("GetPropCheck(ppi", "mV", mV, "SED", SED, "PropID", PropID);
	ED ed (SED);
	switch(PropID)
	{
		case Prop::DevTab_DevMode: return ed.devmode;
	}
	return FALSE;
}
void MMF2Func SetPropValue(mv *mV, SerializedED *SED, unsigned int PropID, CPropValue *Value)
{
	DM("SetPropValue(ppii", "mV", mV, "SED", SED, "PropID", PropID, "Value", Value);
	ED ed (SED);
	switch(PropID)
	{
		case Prop::JsonTab_Json:
		{
			LPSTR json = (LPSTR)((CPropDataValue *)Value)->m_pData;
			std::istringstream def (json);
			json_verifier jv (def);
			if(jv.json)
			{
				ed.Json(json);
			}
			else
			{
				MessageBoxA
				(
					mV->mvHEditWin,
					(std::string("Error in definition:\r\n")+jv.error).c_str(),
					"Widget+",
					MB_OK|MB_ICONERROR
				);
			}
			mvRefreshProp(mV, SED, Prop::JsonTab_Json, TRUE);
		} break;
	}
	ed.Serialize(mV, SED);
}
void MMF2Func SetPropCheck(mv *mV, SerializedED *SED, unsigned int PropID, BOOL Checked)
{
	DM("SetPropCheck(ppii", "mV", mV, "SED", SED, "PropID", PropID, "Checked", Checked);
	ED ed (SED);
	switch(PropID)
	{
		case Prop::DevTab_DevMode:
		{
			ed.devmode = (Checked? true : false);
			if(ed.devmode)
			{
				mvInsertProps(mV, SED, Prop::json_props, PROPID_TAB_CUSTOM2, TRUE);
			}
			else
			{
				mvRemoveProps(mV, SED, Prop::json_props);
			}
		} break;
	}
	ed.Serialize(mV, SED);
}
BOOL MMF2Func EditProp(mv *mV, SerializedED *SED, unsigned int PropID)
{
	DM("EditProp(ppi", "mV", mV, "SED", SED, "PropID", PropID);
	return TRUE;
}
