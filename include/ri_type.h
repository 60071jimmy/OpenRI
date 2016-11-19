/*
Copyright 2016 Open Robot Club

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef __RI_TYPE_H__
#define __RI_TYPE_H__

#include <limits>

/* signed */
#define ri_char                 char
#define ri_int8                 signed char
#define ri_short                short
#define ri_int16                short
#define ri_int                  int
#define ri_int32                int
#define ri_long                 long
#define ri_longlong             long long

#if defined(RI_WINDOWS)
#define ri_int64                __int64
#else
#define ri_int64                long long
#endif

#define ri_float                float
#define ri_float32              float
#define ri_float64              double
#define ri_double               double
#define ri_bool                 int

/* unsigned */
#define ri_byte                 unsigned char 
#define ri_uchar                unsigned char
#define ri_uint8                unsigned char
#define ri_ushort               unsigned short
#define ri_uint16               unsigned short
#define ri_uint                 unsigned int
#define ri_uint32               unsigned int
#define ri_ulong                unsigned long
#define ri_ulonglong            unsigned long long
#define ri_uint64               unsigned long long
#define ri_constptr             const void*
typedef void*                   ri_ptr;
typedef size_t                  ri_size;
typedef unsigned char           ri_pixel8;
#define ri_wchar                wchar_t

#if defined(RI_32BIT)
#define ri_word                 unsigned short
#define ri_dword                unsigned int
#endif

#if defined(RI_WINDOWS) //(RI_CONFIG_VC)
typedef SSIZE_T ri_ssize;
#else
typedef key_t ri_key_t;
typedef ssize_t ri_ssize;
#endif

#define RI_STR_SIZE RI_PAGE_SIZE // 1 memory page for faster performance.

/* Define min and max constants for the fixed size numerical types. */
#define RI_CHAR_MAX       127
#define RI_CHAR_MIN	      (-128)

#define RI_INT8_MAX       127
#define RI_INT8_MIN	      (-128)

#define RI_UINT8_MAX	    255
#define RI_UINT8_MIN	    0

#define RI_INT16_MAX	    32767
#define RI_INT16_MIN	    (-32768)

#define RI_UINT16_MAX     65535
#define RI_UINT16_MIN     0

#define RI_INT32_MAX	    2147483647L
#define RI_INT32_MIN	    (-RI_INT32_MAX-1)

#define RI_UINT32_MAX     0xffffffffL
#define RI_UINT32_MIN     0

#if defined(RI_32BIT)
#define RI_INT_MAX	    2147483647L
#define RI_INT_MIN	    (-RI_INT_MAX-1)
#define RI_UINT_MAX	    0xffffffffL
#define RI_SIZE_MAX     0xffffffffL
#define RI_SSIZE_MAX    2147483647L
#elif defined(RI_64BIT)
#define RI_INT_MAX	    9223372036854775807LL
#define RI_INT_MIN	    (-LLONG_MAX-1)// RI_LONG_LONG_MAX
#define RI_UINT_MAX	  (2ULL * LLONG_MAX + 1) //LONG_LONG_MAX
#define RI_SIZE_MAX	    (2ULL * LLONG_MAX + 1) //RI_LONG_LONG_MAX
#define RI_SSIZE_MAX	  9223372036854775807LL
#endif

#define RI_UINT_MIN	    0
#define RI_SIZE_MIN 0
#define RI_SSIZE_MIN 0

#define RI_LONG_MAX       2147483647L
#define RI_LONG_MIN       (-RI_LONG_MAX-1)

#define RI_ULONG_MAX      0xffffffffUL
#define RI_ULONG_MIN      0

#define RI_INT64_MAX	9223372036854775807LL
#define RI_INT64_MIN	(-RI_INT64_MAX-1)

#define RI_UINT64_MAX	(2ULL * RI_INT64_MAX + 1)
#define RI_UINT64_MIN	0

#define RI_LONGLONG_MAX	9223372036854775807LL
#define RI_LONGLONG_MIN	(-RI_LONGLONG_MAX-1)

#define RI_ULONGLONG_MAX	(2ULL * RI_LONGLONG_MAX + 1)
#define RI_ULONGLONG_MIN	0

#define RI_FLOAT_MAX                    3.402823466e+38F
#define RI_FLOAT_MIN                   -3.402823466e+38F
#define RI_FLOAT_POSITIVE_MAX           3.402823466e+38F
#define RI_FLOAT_POSITIVE_MIN           1.175494351e-38F
#define RI_FLOAT_NEGTIVE_MAX           -1.175494351e-38F
#define RI_FLOAT_NEGTIVE_MIN           -3.402823466e+38F

#define RI_FLOAT32_MAX                  3.402823466e+38F
#define RI_FLOAT32_MIN                 -3.402823466e+38F
#define RI_FLOAT32_POSITIVE_MAX         3.402823466e+38F
#define RI_FLOAT32_POSITIVE_MIN         1.175494351e-38F
#define RI_FLOAT32_NEGTIVE_MAX         -1.175494351e-38F
#define RI_FLOAT32_NEGTIVE_MIN         -3.402823466e+38F

#define RI_FLOAT64_MAX                  1.7976931348623158e+308
#define RI_FLOAT64_MIN                 -1.7976931348623158e+308
#define RI_FLOAT64_POSITIVE_MAX         1.7976931348623158e+308
#define RI_FLOAT64_POSITIVE_MIN         2.2250738585072014e-308
#define RI_FLOAT64_NEGTIVE_MAX         -2.2250738585072014e-308 
#define RI_FLOAT64_NEGTIVE_MIN         -1.7976931348623158e+308

#define RI_DOUBLE_MAX                   1.7976931348623158e+308
#define RI_DOUBLE_MIN                  -1.7976931348623158e+308
#define RI_DOUBLE_POSITIVE_MAX          1.7976931348623158e+308
#define RI_DOUBLE_POSITIVE_MIN          2.2250738585072014e-308
#define RI_DOUBLE_NEGTIVE_MAX          -2.2250738585072014e-308 
#define RI_DOUBLE_NEGTIVE_MIN          -1.7976931348623158e+308

#define RI_TB 1099511627776LL
#define RI_GB 1073741824L
#define RI_MB 1048576L
#define RI_KB 1024

#ifndef	TRUE
#define	TRUE	 (1)  // !FALSE
#endif

#ifndef	FALSE
#define	FALSE	(0)
#endif

/* Char coding */
#define ri_ascii                unsigned char
#define ri_big5                 unsigned char
#define ri_gb2312               unsigned char
#define ri_utf8                 unsigned char
#define ri_utf16                unsigned short

/* New line */
#if defined(RI_WINDOWS)
#define RI_NL "\r\n"
#elif defined(RI_MAC)
#define RI_NL "\r"
#else
#define RI_NL "\n"
#endif

/* Axis */
typedef enum {
    RI_X = 0, RI_Y = 1, RI_Z = 2, RI_U = 3,
} RI_AXIS_t;

/* Boolean */
typedef enum {
    RI_UNKNOWN = -1, RI_FALSE = 0, RI_TRUE = 1,
} RI_BOOLEAN_t;

typedef enum {
    RI_OFF = 0, RI_ON = 1,
} RI_ON_OFF_t;

typedef enum {
    RI_NO = 0, RI_YES = 1,
} RI_YES_NO_t;

typedef enum {
    RI_COMPARE_UNKNOWN = -2, RI_LESS = -1, RI_EQUAL = 0, RI_GREAT = 1,
} RI_COMPARE_t;

typedef enum {
    RI_CW = 0,              // 0: Clockwise.
    RI_CCW,                 // 1: Counter clockwise.
} RI_CLOCK_DIRECTION_t;                // Circle direction.

typedef int (*RiCompare_f)(ri_constptr a, ri_constptr b);
typedef int (*RiCompareDataFunction)(ri_constptr a, ri_constptr b, ri_ptr user_data);

typedef struct {
    int x;
    int y;
} RiPoint_t;

typedef struct {
    int x;
    int y;
    int z;
} RiPoint3D_t;

typedef struct {
    int x;
    int y;
    int z;
    int u;
} RiPoint4D_t;

/* Callback function */
typedef int (*RiCallback_t)(int data);
typedef int (*RiCallbackData_t)(ri_ptr data, int dataSize);

/* Bit defination. */
#define RI_BIT_0                      0x1U
#define RI_BIT_1                      0x2U
#define RI_BIT_2                      0x4U
#define RI_BIT_3                      0x8U
#define RI_BIT_4                     0x10U
#define RI_BIT_5                     0x20U
#define RI_BIT_6                     0x40U
#define RI_BIT_7                     0x80U
#define RI_BIT_8                    0x100U
#define RI_BIT_9                    0x200U
#define RI_BIT_10                   0x400U
#define RI_BIT_11                   0x800U
#define RI_BIT_12                  0x1000U
#define RI_BIT_13                  0x2000U
#define RI_BIT_14                  0x4000U
#define RI_BIT_15                  0x8000U
#define RI_BIT_16                 0x10000U
#define RI_BIT_17                 0x20000U
#define RI_BIT_18                 0x40000U
#define RI_BIT_19                 0x80000U
#define RI_BIT_20                0x100000U
#define RI_BIT_21                0x200000U
#define RI_BIT_22                0x400000U
#define RI_BIT_23                0x800000U
#define RI_BIT_24               0x1000000U
#define RI_BIT_25               0x2000000U
#define RI_BIT_26               0x4000000U
#define RI_BIT_27               0x8000000U
#define RI_BIT_28              0x10000000U
#define RI_BIT_29              0x20000000U
#define RI_BIT_30              0x40000000U
#define RI_BIT_31              0x80000000U
#define RI_BIT_32             0x100000000UL
#define RI_BIT_33             0x200000000UL
#define RI_BIT_34             0x400000000UL
#define RI_BIT_35             0x800000000UL
#define RI_BIT_36            0x1000000000UL
#define RI_BIT_37            0x2000000000UL
#define RI_BIT_38            0x4000000000UL
#define RI_BIT_39            0x8000000000UL
#define RI_BIT_40           0x10000000000UL
#define RI_BIT_41           0x20000000000UL
#define RI_BIT_42           0x40000000000UL
#define RI_BIT_43           0x80000000000UL
#define RI_BIT_44          0x100000000000UL
#define RI_BIT_45          0x200000000000UL
#define RI_BIT_46          0x400000000000UL
#define RI_BIT_47          0x800000000000UL
#define RI_BIT_48         0x1000000000000UL
#define RI_BIT_49         0x2000000000000UL
#define RI_BIT_50         0x4000000000000UL
#define RI_BIT_51         0x8000000000000UL
#define RI_BIT_52        0x10000000000000UL
#define RI_BIT_53        0x20000000000000UL
#define RI_BIT_54        0x40000000000000UL
#define RI_BIT_55        0x80000000000000UL
#define RI_BIT_56       0x100000000000000UL
#define RI_BIT_57       0x200000000000000UL
#define RI_BIT_58       0x400000000000000UL
#define RI_BIT_59       0x800000000000000UL
#define RI_BIT_60      0x1000000000000000UL
#define RI_BIT_61      0x2000000000000000UL
#define RI_BIT_62      0x4000000000000000UL
#define RI_BIT_63      0x8000000000000000UL


#define RI_UNUSED(name) ((void)(name))

/* Remark for function call */
#define RI_IN
#define RI_OUT
#define RI_IN_OUT

#endif /* __RI_TYPE_H__ */
