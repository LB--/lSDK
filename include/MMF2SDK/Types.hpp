#ifndef MMF2SDK_Types_HeaderPlusPlus
#define MMF2SDK_Types_HeaderPlusPlus

#if !defined(_MSC_VER) || _MSC_VER >= 1700

	#include <cstdint>

	typedef std::uint8_t  ubyte;
	typedef std::uint8_t  uchar;
	typedef std::uint32_t uint;
	typedef std::uint16_t ushort;
	typedef std::uint32_t ulong;

	typedef std::int8_t  *npchar;
	typedef std::int32_t *npint;
	typedef std::int16_t *npshort;
	typedef std::int32_t *nplong;

#else

	typedef unsigned char  ubyte;
	typedef unsigned char  uchar;
	typedef unsigned int   uint;
	typedef unsigned short ushort;
	typedef unsigned long  ulong;

	typedef char  *npchar;
	typedef int   *npint;
	typedef short *npshort;
	typedef long  *nplong;

#endif

typedef void   *npvoid;
typedef ubyte  *npubyte;
typedef uchar  *npuchar;
typedef uint   *npuint;
typedef ushort *npushort;
typedef ulong  *npulong;

typedef npchar  fpchar;
typedef npint   fpint;
typedef npshort fpshort;
typedef nplong  fplong;

typedef npvoid   fpvoid;
typedef npubyte  fpubyte;
typedef npuchar  fpuchar;
typedef npuint   fpuint;
typedef npushort fpushort;
typedef npulong  fpulong;

#endif
