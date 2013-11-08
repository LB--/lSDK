#ifndef MMF2SDK_EventInfo_HeaderPlusPlus
#define MMF2SDK_EventInfo_HeaderPlusPlus

//Structure V2: nombre de parametres variable...
struct infosEventsV2
{
	short code;          //Le numero de type + code event
	short flags;         //Les flags a mettre dans l'event
	short nParams;       //Le nombre de parametres
//	short param[X];      //Le type des parametres
//	short paramTitle[X]; //Le titre de chacun des params
};
typedef infosEventsV2 *LPINFOEVENTSV2;

//Event information structure
struct eventInformations2
{
	short         menu;   //Menu identifier
	short         string; //String identifier
	infosEventsV2 infos;  //Sub structure
};
typedef eventInformations2 *LPEVENTINFOS2;

#define EVINFO2_NEXT(p)         ((LPEVENTINFOS2)((LPBYTE)p + sizeof(eventInformations2) + p->infos.nParams * 2 * sizeof(short)))
#define EVINFO2_PARAM(p,n)      (*(LPWORD)((LPBYTE)p + sizeof(eventInformations2) + n * sizeof(short)))
#define EVINFO2_PARAMTITLE(p,n) (*(LPWORD)((LPBYTE)p + sizeof(eventInformations2) + p->infos.nParams * sizeof(short) + n * sizeof(short)))

#endif
