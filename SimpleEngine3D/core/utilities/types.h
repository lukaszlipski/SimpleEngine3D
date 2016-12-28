#pragma once

#define MIN_INT8   128 * -1
#define MAX_INT8   127
#define MIN_INT16  32,768 * -1
#define MAX_INT16  32,767
#define MIN_INT32  2,147,483,648 * -1
#define MAX_INT32  2,147,483,647
#define MIN_INT64  9,223,372,036,854,775,808 * -1
#define MAX_INT64  9,223,372,036,854,775,807

#define MIN_UINT8  0x00
#define MAX_UINT8  0xFF
#define MIN_UINT16 0x0000
#define MAX_UINT16 0xFFFF
#define MIN_UINT32 0x00000000
#define MAX_UINT32 0xFFFFFFFF
#define MIN_UINT64 0x0000000000000000
#define MAX_UINT64 0xFFFFFFFFFFFFFFFF

#define MIN_FLOAT  1.175494351e-38F
#define MAX_FLOAT  3.402823466e+38F
#define MIN_DOUBLE 2.2250738585072014e-308
#define MAX_DOUBLE 1.7976931348623158e+308

typedef signed char int8;
typedef short int16;
typedef int int32;
typedef long long int64;

typedef unsigned char byte;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;
