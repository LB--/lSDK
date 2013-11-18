#ifndef EdittimeData_HeaderPlusPlus
#define EdittimeData_HeaderPlusPlus

struct SerializedED
{
	extHeader h;
	char d[1];
};

struct EditData
{
	json_value *json;
	bool devmode;

private:
	std::string json_str;
	void initJson()
	{
		json_settings options = {0};
		char error[json_error_max];
		json = json_parse_ex(&options, json_str.c_str(), json_str.length(), error);
	}
public:

	EditData(std::string str) : json_str(str), devmode(false)
	{
		initJson();
	}
	EditData(EditData const &o) : json_str(o.json_str), devmode(o.devmode)
	{
		initJson();
	}
	EditData &operator=(EditData const &o)
	{
		json_str = o.json_str;
		json_value_free(json), json = 0;
		initJson();
		devmode = o.devmode;
		return *this;
	}
	~EditData()
	{
		json_value_free(json), json = 0;
	}

	void Json(std::string str)
	{
		json_str = str;
		json_value_free(json), json = 0;
		initJson();
	}
	std::string const &Json() const
	{
		return json_str;
	}

#ifndef RUN_ONLY
	bool Serialize(mv *mV, SerializedED *&SED) const
	{
		std::size_t size = json_str.size()+1 + sizeof(devmode);
		SerializedED *t = (SerializedED *)mvReAllocEditData(mV, SED, sizeof(SerializedED)+size);
		if(t)
		{
			SED = t;
		}
		else return false;
		char *p = (char *)(&SED->d);
		memcpy(p, json_str.c_str(), json_str.size()+1); p += json_str.size()+1;
		memcpy(p, &devmode, sizeof(devmode));           p += sizeof(devmode);
		return true;
	}
#endif
	EditData(SerializedED *SED) : json_str(SED->d)
	{
		initJson();
		char *p = (char *)(&SED->d);          p += json_str.size() + 1;
		memcpy(&devmode, p, sizeof(devmode)); p += sizeof(devmode);
	}
};
typedef EditData ED;

#endif
