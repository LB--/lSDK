#ifndef EdittimeData_HeaderPlusPlus
#define EdittimeData_HeaderPlusPlus

struct SerializedED
{
	extHeader h;
	char d[1];
};

struct EditData
{
	std::string json_str;
	json_value *json;

private:
	void initJson()
	{
		json_settings options = {0};
		char error[json_error_max];
		json = json_parse_ex(&options, json_str.c_str(), json_str.length(), error);
	}
public:

	EditData(std::string str) : json_str(str)
	{
		initJson();
	}
	EditData(EditData const &o) : json_str(o.json_str)
	{
		initJson();
	}
	EditData &operator=(EditData const &o)
	{
		json_str = o.json_str;
		json_value_free(json), json = 0;
		initJson();
	}
	~EditData()
	{
		json_value_free(json), json = 0;
	}

#ifndef RUN_ONLY
	bool Serialize(mv *mV, SerializedED *&SED) const
	{
		std::size_t size = json_str.size()+1;
		SerializedED *t = (SerializedED *)mvReAllocEditData(mV, SED, sizeof(SerializedED)+size);
		if(t)
		{
			SED = t;
		}
		else return false;
		char *p = (char *)(&SED->d);
		memcpy(p, json_str.c_str(), json_str.size()+1); p += json_str.size()+1;
		return true;
	}
#endif
	EditData(SerializedED *SED) : json_str(SED->d)
	{
		initJson();
	}
};
typedef EditData ED;

#endif
