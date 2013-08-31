#ifndef _SOUNDCONVERTER_H_
#define _SOUNDCONVERTER_H_

#ifdef WIN32
#include <MMReg.h>
#endif //WIN32

typedef void (*SAMPLECONVERTPROC)(LPVOID pSrc,LPVOID pDst,DWORD nSrcSample,DWORD nSrcFreqSample,DWORD nDstWrite);

extern const SAMPLECONVERTPROC SampleConversionProcArray[];

#define SMP_CONV_8BITMONO_TO_8BITSTEREO        0
#define SMP_CONV_8BITMONO_TO_16BITMONO        1
#define SMP_CONV_8BITMONO_TO_16BITSTEREO    2

#define SMP_CONV_8BITSTEREO_TO_8BITMONO        3
#define SMP_CONV_8BITSTEREO_TO_16BITMONO    4
#define SMP_CONV_8BITSTEREO_TO_16BITSTEREO    5


#define SMP_CONV_16BITMONO_TO_16BITSTEREO    6
#define SMP_CONV_16BITMONO_TO_8BITMONO        7
#define SMP_CONV_16BITMONO_TO_8BITSTEREO    8

#define SMP_CONV_16BITSTEREO_TO_16BITMONO    9
#define SMP_CONV_16BITSTEREO_TO_8BITMONO    10
#define SMP_CONV_16BITSTEREO_TO_8BITSTEREO    11


SAMPLECONVERTPROC GetConversionFunction(LPWAVEFORMATEX pSrcFormat,LPWAVEFORMATEX pDstFormat);

#endif //_SOUNDCONVERTER_H_
