The `RunData` structure is one that you must define yourself, but which Fusion ultimately controls and owns.
The entire memory content of the structure may be copied byte-for-byte, so it can't contain any types with constructors/destructors.
You can only have pointers and plain data members in this structure.
The destructor and all constructors and assignment coperators must be explicitly deleted. The first data member must be the `headerObject` structure.

The next data members depend on what flags you specified in `GetRunObjectInfos` in this order:
* If you specified `OEFLAG_MOVEMENTS`, `OEFLAG_ANIMATIONS`, or `OEFLAG_SPRITES`, the next data member must be `rCom rc;`
* If you specified `OEFLAG_MOVEMENTS`, next is `rMvt rm;`
* If you specified `OEFLAG_ANIMATIONS`, next is `rAni ra;`
* If you specified `OEFLAG_SPRITES`, next is `rSpr rs;`
* If you specified `OEFLAG_VALUES`, last is `rVal rv;`

After those, you may define your own plain data members.
You should generally only store a single data member: a pointer to your real C++ runtime class with normal C++ data types as members.

You can use `static_assert(fusion::is_valid_rundata_structure<FUSION_OEFLAGS>());` after the structure definition to be sure that you have correctly adhered to the rules, where `FUSION_OEFLAGS` is the same as what you provided in `GetRunObjectInfos`.
It is recommended that you define `FUSION_OEFLAGS` as a preprocessor definition in your project settings unless it needs to be dynamic.
For a dynamic runtime structure, you will need to have a byte array after the `headerObject` with enough space to hold all possible configurations.

You should avoid storing pointers or references to the `RunData` structure, as some versions of Fusion may relocate it in memory.
Pass it as a parameter when needed, or pass a reference to the `headerObject` structure as that is what most lSDK and Fusion utility functions need to operate on.

## Example definition
```cpp
struct RunData final
{
	headerObject rHo;
	rVal rv;

	Runtime *runtime; //your C++ class

	RunData() = delete;
	RunData(RunData const &) = delete;
	RunData(RunData &&) = delete;
	RunData &operator=(RunData &&) = delete;
	RunData &operator=(RunData const &) = delete;
	~RunData() = delete;
};

static_assert(fusion::is_valid_rundata_structure<FUSION_OEFLAGS>());
```
