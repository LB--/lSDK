#ifndef EdittimeData_HeaderPlusPlus
#define EdittimeData_HeaderPlusPlus

struct SerializedED
{
	extHeader h;
	char d[1];
};

struct EditData
{
	std::string wid;

	EditData(){}
	EditData(EditData const &o) : wid(o.wid) {}
	EditData &operator=(EditData const &o){ wid = o.wid; }

#ifndef RUN_ONLY
	bool Serialize(mv *mV, SerializedED *&SED) const
	{
		std::size_t size = wid.size()+1;
		SerializedED *t = (SerializedED *)mvReAllocEditData(mV, SED, sizeof(SerializedED)+size);
		if(t)
		{
			SED = t;
		}
		else return false;
		char *p = (char *)(&SED->d);
		memcpy(p, wid.c_str(), wid.size()+1); p += wid.size()+1;
		return true;
	}
#endif
	EditData(SerializedED *SED) : wid(SED->d){}
};
typedef EditData ED;

#endif
