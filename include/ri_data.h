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

#ifndef __RI_DATA_H__
#define __RI_DATA_H__

#include "openri.h"

#ifdef __cplusplus
extern "C" 
{
#endif

    // Endian convertion.
    RI_API int  ri_reverse_endian(ri_byte *data, size_t size);
    RI_API ri_uint32 ri_cpu_to_le32(ri_uint32 value);
    RI_API ri_uint32 ri_le32_to_cpu(ri_uint32 value);
    RI_API ri_uint32 ri_cpu_to_be32(ri_uint32 value);
    RI_API ri_uint32 ri_be32_to_cpu(ri_uint32 value);
    RI_API ri_uint16 ri_cpu_to_le16(ri_uint16 value);
    RI_API ri_uint16 ri_le16_to_cpu(ri_uint16 value);
    RI_API ri_uint16 ri_cpu_to_be16(ri_uint16 value);
    RI_API ri_uint16 ri_be16_to_cpu(ri_uint16 value);
    RI_API ri_uint64 ri_cpu_to_le64(ri_uint64 value);
    RI_API ri_uint64 ri_le64_to_cpu(ri_uint64 value);
    RI_API ri_uint64 ri_cpu_to_be64(ri_uint64 value);
    RI_API ri_uint64 ri_be64_to_cpu(ri_uint64 value);

    // Safe data convert functions.
    RI_API ri_uint   ri_int_to_uint(int from);
    RI_API ri_int8   ri_int_to_int8(int from);
    RI_API ri_uint8  ri_int_to_uint8(int from);
    RI_API ri_int16   ri_int_to_int16(int from);
    RI_API ri_uint16  ri_int_to_uint16(int from);
    RI_API ri_int32  ri_int_to_int32(int from);
    RI_API ri_uint32 ri_int_to_uint32(int from);
    RI_API ri_int64   ri_int_to_int64(int from);
    RI_API ri_uint64  ri_int_to_uint64(int from);
    RI_API long  ri_int_to_long(int from);
    RI_API ri_ulong  ri_int_to_ulong(int from);
    RI_API ri_longlong  ri_int_to_longlong(int from);
    RI_API ri_ulonglong  ri_int_to_ulonglong(int from);
    RI_API size_t   ri_int_to_size(int from);
    RI_API ri_ssize  ri_int_to_ssize(int from);
    RI_API float  ri_int_to_float(int from);
    RI_API ri_float32  ri_int_to_float32(int from);
    RI_API ri_float64  ri_int_to_float64(int from);
    RI_API double  ri_int_to_double(int from);

    RI_API int   ri_uint_to_int(ri_uint from);
    RI_API ri_int8   ri_uint_to_int8(ri_uint from);
    RI_API ri_uint8  ri_uint_to_uint8(ri_uint from);
    RI_API ri_int16   ri_uint_to_int16(ri_uint from);
    RI_API ri_uint16  ri_uint_to_uint16(ri_uint from);
    RI_API ri_int32  ri_uint_to_int32(ri_uint from);
    RI_API ri_uint32 ri_uint_to_uint32(ri_uint from);
    RI_API ri_int64   ri_uint_to_int64(ri_uint from);
    RI_API ri_uint64  ri_uint_to_uint64(ri_uint from);
    RI_API long  ri_uint_to_long(ri_uint from);
    RI_API ri_ulong  ri_uint_to_ulong(ri_uint from);
    RI_API ri_longlong  ri_uint_to_longlong(ri_uint from);
    RI_API ri_ulonglong  ri_uint_to_ulonglong(ri_uint from);
    RI_API size_t   ri_uint_to_size(ri_uint from);
    RI_API ri_ssize  ri_uint_to_ssize(ri_uint from);
    RI_API float  ri_uint_to_float(ri_uint from);
    RI_API ri_float32  ri_uint_to_float32(ri_uint from);
    RI_API ri_float64  ri_uint_to_float64(ri_uint from);
    RI_API double  ri_uint_to_double(ri_uint from);

    RI_API int   ri_int8_to_int(ri_int8 from);
    RI_API ri_uint   ri_int8_to_uint(ri_int8 from);
    RI_API ri_uint8  ri_int8_to_uint8(ri_int8 from);
    RI_API ri_int16   ri_int8_to_int16(ri_int8 from);
    RI_API ri_uint16  ri_int8_to_uint16(ri_int8 from);
    RI_API ri_int32  ri_int8_to_int32(ri_int8 from);
    RI_API ri_uint32 ri_int8_to_uint32(ri_int8 from);
    RI_API ri_int64   ri_int8_to_int64(ri_int8 from);
    RI_API ri_uint64  ri_int8_to_uint64(ri_int8 from);
    RI_API long  ri_int8_to_long(ri_int8 from);
    RI_API ri_ulong  ri_int8_to_ulong(ri_int8 from);
    RI_API ri_longlong  ri_int8_to_longlong(ri_int8 from);
    RI_API ri_ulonglong  ri_int8_to_ulonglong(ri_int8 from);
    RI_API size_t   ri_int8_to_size(ri_int8 from);
    RI_API ri_ssize  ri_int8_to_ssize(ri_int8 from);
    RI_API float  ri_int8_to_float(ri_int8 from);
    RI_API ri_float32  ri_int8_to_float32(ri_int8 from);
    RI_API ri_float64  ri_int8_to_float64(ri_int8 from);
    RI_API double  ri_int8_to_double(ri_int8 from);

    RI_API int   ri_uint8_to_int(ri_uint8 from);
    RI_API ri_uint   ri_uint8_to_uint(ri_uint8 from);
    RI_API ri_int8  ri_uint8_to_int8(ri_uint8 from);
    RI_API ri_int16   ri_uint8_to_int16(ri_uint8 from);
    RI_API ri_uint16  ri_uint8_to_uint16(ri_uint8 from);
    RI_API ri_int32  ri_uint8_to_int32(ri_uint8 from);
    RI_API ri_uint32 ri_uint8_to_uint32(ri_uint8 from);
    RI_API ri_int64   ri_uint8_to_int64(ri_uint8 from);
    RI_API ri_uint64  ri_uint8_to_uint64(ri_uint8 from);
    RI_API long  ri_uint8_to_long(ri_uint8 from);
    RI_API ri_ulong  ri_uint8_to_ulong(ri_uint8 from);
    RI_API ri_longlong  ri_uint8_to_longlong(ri_uint8 from);
    RI_API ri_ulonglong  ri_uint8_to_ulonglong(ri_uint8 from);
    RI_API size_t   ri_uint8_to_size(ri_uint8 from);
    RI_API ri_ssize  ri_uint8_to_ssize(ri_uint8 from);
    RI_API float  ri_uint8_to_float(ri_uint8 from);
    RI_API ri_float32  ri_uint8_to_float32(ri_uint8 from);
    RI_API ri_float64  ri_uint8_to_float64(ri_uint8 from);
    RI_API double  ri_uint8_to_double(ri_uint8 from);

    RI_API int   ri_int16_to_int(ri_int16 from);
    RI_API ri_uint   ri_int16_to_uint(ri_int16 from);
    RI_API ri_int8  ri_int16_to_int8(ri_int16 from);
    RI_API ri_uint8   ri_int16_to_uint8(ri_int16 from);
    RI_API ri_uint16  ri_int16_to_uint16(ri_int16 from);
    RI_API ri_int32  ri_int16_to_int32(ri_int16 from);
    RI_API ri_uint32 ri_int16_to_uint32(ri_int16 from);
    RI_API ri_int64   ri_int16_to_int64(ri_int16 from);
    RI_API ri_uint64  ri_int16_to_uint64(ri_int16 from);
    RI_API long  ri_int16_to_long(ri_int16 from);
    RI_API ri_ulong  ri_int16_to_ulong(ri_int16 from);
    RI_API ri_longlong  ri_int16_to_longlong(ri_int16 from);
    RI_API ri_ulonglong  ri_int16_to_ulonglong(ri_int16 from);
    RI_API size_t   ri_int16_to_size(ri_int16 from);
    RI_API ri_ssize  ri_int16_to_ssize(ri_int16 from);
    RI_API float  ri_int16_to_float(ri_int16 from);
    RI_API ri_float32  ri_int16_to_float32(ri_int16 from);
    RI_API ri_float64  ri_int16_to_float64(ri_int16 from);
    RI_API double  ri_int16_to_double(ri_int16 from);

    RI_API int   ri_uint16_to_int(ri_uint16 from);
    RI_API ri_uint   ri_uint16_to_uint(ri_uint16 from);
    RI_API ri_int8  ri_uint16_to_int8(ri_uint16 from);
    RI_API ri_uint8   ri_uint16_to_uint8(ri_uint16 from);
    RI_API ri_int16  ri_uint16_to_int16(ri_uint16 from);
    RI_API ri_int32  ri_uint16_to_int32(ri_uint16 from);
    RI_API ri_uint32 ri_uint16_to_uint32(ri_uint16 from);
    RI_API ri_int64   ri_uint16_to_int64(ri_uint16 from);
    RI_API ri_uint64  ri_uint16_to_uint64(ri_uint16 from);
    RI_API long  ri_uint16_to_long(ri_uint16 from);
    RI_API ri_ulong  ri_uint16_to_ulong(ri_uint16 from);
    RI_API ri_longlong  ri_uint16_to_longlong(ri_uint16 from);
    RI_API ri_ulonglong  ri_uint16_to_ulonglong(ri_uint16 from);
    RI_API size_t   ri_uint16_to_size(ri_uint16 from);
    RI_API ri_ssize  ri_uint16_to_ssize(ri_uint16 from);
    RI_API float  ri_uint16_to_float(ri_uint16 from);
    RI_API ri_float32  ri_uint16_to_float32(ri_uint16 from);
    RI_API ri_float64  ri_uint16_to_float64(ri_uint16 from);
    RI_API double  ri_uint16_to_double(ri_uint16 from);

    RI_API int   ri_int32_to_int(ri_int32 from);
    RI_API ri_uint   ri_int32_to_uint(ri_int32 from);
    RI_API ri_int8  ri_int32_to_int8(ri_int32 from);
    RI_API ri_uint8   ri_int32_to_uint8(ri_int32 from);
    RI_API ri_int16  ri_int32_to_int16(ri_int32 from);
    RI_API ri_uint16  ri_int32_to_uint16(ri_int32 from);
    RI_API ri_uint32 ri_int32_to_uint32(ri_int32 from);
    RI_API ri_int64   ri_int32_to_int64(ri_int32 from);
    RI_API ri_uint64  ri_int32_to_uint64(ri_int32 from);
    RI_API long  ri_int32_to_long(ri_int32 from);
    RI_API ri_ulong  ri_int32_to_ulong(ri_int32 from);
    RI_API ri_longlong  ri_int32_to_longlong(ri_int32 from);
    RI_API ri_ulonglong  ri_int32_to_ulonglong(ri_int32 from);
    RI_API size_t   ri_int32_to_size(ri_int32 from);
    RI_API ri_ssize  ri_int32_to_ssize(ri_int32 from);
    RI_API float  ri_int32_to_float(ri_int32 from);
    RI_API ri_float32  ri_int32_to_float32(ri_int32 from);
    RI_API ri_float64  ri_int32_to_float64(ri_int32 from);
    RI_API double  ri_int32_to_double(ri_int32 from);

    RI_API int   ri_uint32_to_int(ri_uint32 from);
    RI_API ri_uint   ri_uint32_to_uint(ri_uint32 from);
    RI_API ri_int8  ri_uint32_to_int8(ri_uint32 from);
    RI_API ri_uint8   ri_uint32_to_uint8(ri_uint32 from);
    RI_API ri_int16  ri_uint32_to_int16(ri_uint32 from);
    RI_API ri_uint16  ri_uint32_to_uint16(ri_uint32 from);
    RI_API ri_int32 ri_uint32_to_int32(ri_uint32 from);
    RI_API ri_int64   ri_uint32_to_int64(ri_uint32 from);
    RI_API ri_uint64  ri_uint32_to_uint64(ri_uint32 from);
    RI_API long  ri_uint32_to_long(ri_uint32 from);
    RI_API ri_ulong  ri_uint32_to_ulong(ri_uint32 from);
    RI_API ri_longlong  ri_uint32_to_longlong(ri_uint32 from);
    RI_API ri_ulonglong  ri_uint32_to_ulonglong(ri_uint32 from);
    RI_API size_t   ri_uint32_to_size(ri_uint32 from);
    RI_API ri_ssize  ri_uint32_to_ssize(ri_uint32 from);
    RI_API float  ri_uint32_to_float(ri_uint32 from);
    RI_API ri_float32  ri_uint32_to_float32(ri_uint32 from);
    RI_API ri_float64  ri_uint32_to_float64(ri_uint32 from);
    RI_API double  ri_uint32_to_double(ri_uint32 from);

    RI_API int   ri_int64_to_int(ri_int64 from);
    RI_API ri_uint   ri_int64_to_uint(ri_int64 from);
    RI_API ri_int8  ri_int64_to_int8(ri_int64 from);
    RI_API ri_uint8   ri_int64_to_uint8(ri_int64 from);
    RI_API ri_int16  ri_int64_to_int16(ri_int64 from);
    RI_API ri_uint16  ri_int64_to_uint16(ri_int64 from);
    RI_API ri_int32 ri_int64_to_int32(ri_int64 from);
    RI_API ri_uint32   ri_int64_to_uint32(ri_int64 from);
    RI_API ri_uint64  ri_int64_to_uint64(ri_int64 from);
    RI_API long  ri_int64_to_long(ri_int64 from);
    RI_API ri_ulong  ri_int64_to_ulong(ri_int64 from);
    RI_API ri_longlong  ri_int64_to_longlong(ri_int64 from);
    RI_API ri_ulonglong  ri_int64_to_ulonglong(ri_int64 from);
    RI_API size_t   ri_int64_to_size(ri_int64 from);
    RI_API ri_ssize  ri_int64_to_ssize(ri_int64 from);
    RI_API float  ri_int64_to_float(ri_int64 from);
    RI_API ri_float32  ri_int64_to_float32(ri_int64 from);
    RI_API ri_float64  ri_int64_to_float64(ri_int64 from);
    RI_API double  ri_int64_to_double(ri_int64 from);

    RI_API int   ri_uint64_to_int(ri_uint64 from);
    RI_API ri_uint   ri_uint64_to_uint(ri_uint64 from);
    RI_API ri_int8  ri_uint64_to_int8(ri_uint64 from);
    RI_API ri_uint8   ri_uint64_to_uint8(ri_uint64 from);
    RI_API ri_int16  ri_uint64_to_int16(ri_uint64 from);
    RI_API ri_uint16  ri_uint64_to_uint16(ri_uint64 from);
    RI_API ri_int32 ri_uint64_to_int32(ri_uint64 from);
    RI_API ri_uint32   ri_uint64_to_uint32(ri_uint64 from);
    RI_API ri_int64  ri_uint64_to_int64(ri_uint64 from);
    RI_API long  ri_uint64_to_long(ri_uint64 from);
    RI_API ri_ulong  ri_uint64_to_ulong(ri_uint64 from);
    RI_API ri_longlong  ri_uint64_to_longlong(ri_uint64 from);
    RI_API ri_ulonglong  ri_uint64_to_ulonglong(ri_uint64 from);
    RI_API size_t   ri_uint64_to_size(ri_uint64 from);
    RI_API ri_ssize  ri_uint64_to_ssize(ri_uint64 from);
    RI_API float  ri_uint64_to_float(ri_uint64 from);
    RI_API ri_float32  ri_uint64_to_float32(ri_uint64 from);
    RI_API ri_float64  ri_uint64_to_float64(ri_uint64 from);
    RI_API double  ri_uint64_to_double(ri_uint64 from);

    RI_API int   ri_long_to_int(long from);
    RI_API ri_uint   ri_long_to_uint(long from);
    RI_API ri_int8  ri_long_to_int8(long from);
    RI_API ri_uint8   ri_long_to_uint8(long from);
    RI_API ri_int16  ri_long_to_int16(long from);
    RI_API ri_uint16  ri_long_to_uint16(long from);
    RI_API ri_int32 ri_long_to_int32(long from);
    RI_API ri_uint32   ri_long_to_uint32(long from);
    RI_API ri_int64  ri_long_to_int64(long from);
    RI_API ri_uint64  ri_long_to_uint64(long from);
    RI_API ri_ulong  ri_long_to_ulong(long from);
    RI_API ri_longlong  ri_long_to_longlong(long from);
    RI_API ri_ulonglong  ri_long_to_ulonglong(long from);
    RI_API size_t   ri_long_to_size(long from);
    RI_API ri_ssize  ri_long_to_ssize(long from);
    RI_API float  ri_long_to_float(long from);
    RI_API ri_float32  ri_long_to_float32(long from);
    RI_API ri_float64  ri_long_to_float64(long from);
    RI_API double  ri_long_to_double(long from);

    RI_API int   ri_ulong_to_int(ri_ulong from);
    RI_API ri_uint   ri_ulong_to_uint(ri_ulong from);
    RI_API ri_int8  ri_ulong_to_int8(ri_ulong from);
    RI_API ri_uint8   ri_ulong_to_uint8(ri_ulong from);
    RI_API ri_int16  ri_ulong_to_int16(ri_ulong from);
    RI_API ri_uint16  ri_ulong_to_uint16(ri_ulong from);
    RI_API ri_int32 ri_ulong_to_int32(ri_ulong from);
    RI_API ri_uint32   ri_ulong_to_uint32(ri_ulong from);
    RI_API ri_int64  ri_ulong_to_int64(ri_ulong from);
    RI_API ri_uint64  ri_ulong_to_uint64(ri_ulong from);
    RI_API long  ri_ulong_to_long(ri_ulong from);
    RI_API ri_longlong  ri_ulong_to_longlong(ri_ulong from);
    RI_API ri_ulonglong  ri_ulong_to_ulonglong(ri_ulong from);
    RI_API size_t   ri_ulong_to_size(ri_ulong from);
    RI_API ri_ssize  ri_ulong_to_ssize(ri_ulong from);
    RI_API float  ri_ulong_to_float(ri_ulong from);
    RI_API ri_float32  ri_ulong_to_float32(ri_ulong from);
    RI_API ri_float64  ri_ulong_to_float64(ri_ulong from);
    RI_API double  ri_ulong_to_double(ri_ulong from);

    RI_API int   ri_longlong_to_int(ri_longlong from);
    RI_API ri_uint   ri_longlong_to_uint(ri_longlong from);
    RI_API ri_int8  ri_longlong_to_int8(ri_longlong from);
    RI_API ri_uint8   ri_longlong_to_uint8(ri_longlong from);
    RI_API ri_int16  ri_longlong_to_int16(ri_longlong from);
    RI_API ri_uint16  ri_longlong_to_uint16(ri_longlong from);
    RI_API ri_int32 ri_longlong_to_int32(ri_longlong from);
    RI_API ri_uint32   ri_longlong_to_uint32(ri_longlong from);
    RI_API ri_int64  ri_longlong_to_int64(ri_longlong from);
    RI_API ri_uint64  ri_longlong_to_uint64(ri_longlong from);
    RI_API long  ri_longlong_to_long(ri_longlong from);
    RI_API ri_ulong  ri_longlong_to_ulong(ri_longlong from);
    RI_API ri_ulonglong  ri_longlong_to_ulonglong(ri_longlong from);
    RI_API size_t   ri_longlong_to_size(ri_longlong from);
    RI_API ri_ssize  ri_longlong_to_ssize(ri_longlong from);
    RI_API float  ri_longlong_to_float(ri_longlong from);
    RI_API ri_float32  ri_longlong_to_float32(ri_longlong from);
    RI_API ri_float64  ri_longlong_to_float64(ri_longlong from);
    RI_API double  ri_longlong_to_double(ri_longlong from);

    RI_API int   ri_ulonglong_to_int(ri_ulonglong from);
    RI_API ri_uint   ri_ulonglong_to_uint(ri_ulonglong from);
    RI_API ri_int8  ri_ulonglong_to_int8(ri_ulonglong from);
    RI_API ri_uint8   ri_ulonglong_to_uint8(ri_ulonglong from);
    RI_API ri_int16  ri_ulonglong_to_int16(ri_ulonglong from);
    RI_API ri_uint16  ri_ulonglong_to_uint16(ri_ulonglong from);
    RI_API ri_int32 ri_ulonglong_to_int32(ri_ulonglong from);
    RI_API ri_uint32   ri_ulonglong_to_uint32(ri_ulonglong from);
    RI_API ri_int64  ri_ulonglong_to_int64(ri_ulonglong from);
    RI_API ri_uint64  ri_ulonglong_to_uint64(ri_ulonglong from);
    RI_API long  ri_ulonglong_to_long(ri_ulonglong from);
    RI_API ri_ulong  ri_ulonglong_to_ulong(ri_ulonglong from);
    RI_API ri_longlong  ri_ulonglong_to_longlong(ri_ulonglong from);
    RI_API size_t   ri_ulonglong_to_size(ri_ulonglong from);
    RI_API ri_ssize  ri_ulonglong_to_ssize(ri_ulonglong from);
    RI_API float  ri_ulonglong_to_float(ri_ulonglong from);
    RI_API ri_float32  ri_ulonglong_to_float32(ri_ulonglong from);
    RI_API ri_float64  ri_ulonglong_to_float64(ri_ulonglong from);
    RI_API double  ri_ulonglong_to_double(ri_ulonglong from);

    RI_API int   ri_size_to_int(size_t from);
    RI_API ri_uint   ri_size_to_uint(size_t from);
    RI_API ri_int8  ri_size_to_int8(size_t from);
    RI_API ri_uint8   ri_size_to_uint8(size_t from);
    RI_API ri_int16  ri_size_to_int16(size_t from);
    RI_API ri_uint16  ri_size_to_uint16(size_t from);
    RI_API ri_int32 ri_size_to_int32(size_t from);
    RI_API ri_uint32   ri_size_to_uint32(size_t from);
    RI_API ri_int64  ri_size_to_int64(size_t from);
    RI_API ri_uint64   ri_size_to_uint64(size_t from);
    RI_API long ri_size_to_long(size_t from);
    RI_API ri_ulong  ri_size_to_ulong(size_t from);
    RI_API ri_longlong  ri_size_to_longlong(size_t from);
    RI_API ri_ulonglong  ri_size_to_ulonglong(size_t from);
    RI_API ri_ssize  ri_size_to_ssize(size_t from);
    RI_API float  ri_size_to_float(size_t from);
    RI_API ri_float32  ri_size_to_float32(size_t from);
    RI_API ri_float64  ri_size_to_float64(size_t from);
    RI_API double  ri_size_to_double(size_t from);

    RI_API int   ri_ssize_to_int(ri_ssize from);
    RI_API ri_uint   ri_ssize_to_uint(ri_ssize from);
    RI_API ri_int8  ri_ssize_to_int8(ri_ssize from);
    RI_API ri_uint8   ri_ssize_to_uint8(ri_ssize from);
    RI_API ri_int16  ri_ssize_to_int16(ri_ssize from);
    RI_API ri_uint16  ri_ssize_to_uint16(ri_ssize from);
    RI_API ri_int32 ri_ssize_to_int32(ri_ssize from);
    RI_API ri_uint32   ri_ssize_to_uint32(ri_ssize from);
    RI_API ri_int64  ri_ssize_to_int64(ri_ssize from);
    RI_API ri_uint64   ri_ssize_to_uint64(ri_ssize from);
    RI_API long  ri_ssize_to_long(ri_ssize from);
    RI_API ri_ulong  ri_ssize_to_ulong(ri_ssize from);
    RI_API ri_longlong  ri_ssize_to_longlong(ri_ssize from);
    RI_API ri_ulonglong  ri_ssize_to_ulonglong(ri_ssize from);
    RI_API size_t  ri_ssize_to_size(ri_ssize from);
    RI_API float  ri_ssize_to_float(ri_ssize from);
    RI_API ri_float32  ri_ssize_to_float32(ri_ssize from);
    RI_API ri_float64  ri_ssize_to_float64(ri_ssize from);
    RI_API double  ri_ssize_to_double(ri_ssize from);

    RI_API int   ri_float_to_int(float from);
    RI_API ri_uint   ri_float_to_uint(float from);
    RI_API ri_int8  ri_float_to_int8(float from);
    RI_API ri_uint8   ri_float_to_uint8(float from);
    RI_API ri_int16  ri_float_to_int16(float from);
    RI_API ri_uint16  ri_float_to_uint16(float from);
    RI_API ri_int32 ri_float_to_int32(float from);
    RI_API ri_uint32   ri_float_to_uint32(float from);
    RI_API ri_int64  ri_float_to_int64(float from);
    RI_API ri_uint64   ri_float_to_uint64(float from);
    RI_API long  ri_float_to_long(float from);
    RI_API ri_ulong  ri_float_to_ulong(float from);
    RI_API ri_longlong  ri_float_to_longlong(float from);
    RI_API ri_ulonglong  ri_float_to_ulonglong(float from);
    RI_API size_t  ri_float_to_size(float from);
    RI_API ri_ssize  ri_float_to_ssize(float from);
    RI_API ri_float32  ri_float_to_float32(float from);
    RI_API ri_float64  ri_float_to_float64(float from);
    RI_API double  ri_float_to_double(float from);

    RI_API int   ri_float32_to_int(ri_float32 from);
    RI_API ri_uint   ri_float32_to_uint(ri_float32 from);
    RI_API ri_int8  ri_float32_to_int8(ri_float32 from);
    RI_API ri_uint8   ri_float32_to_uint8(ri_float32 from);
    RI_API ri_int16  ri_float32_to_int16(ri_float32 from);
    RI_API ri_uint16  ri_float32_to_uint16(ri_float32 from);
    RI_API ri_int32 ri_float32_to_int32(ri_float32 from);
    RI_API ri_uint32   ri_float32_to_uint32(ri_float32 from);
    RI_API ri_int64  ri_float32_to_int64(ri_float32 from);
    RI_API ri_uint64   ri_float32_to_uint64(ri_float32 from);
    RI_API long  ri_float32_to_long(ri_float32 from);
    RI_API ri_ulong  ri_float32_to_ulong(ri_float32 from);
    RI_API ri_longlong  ri_float32_to_longlong(ri_float32 from);
    RI_API ri_ulonglong  ri_float32_to_ulonglong(ri_float32 from);
    RI_API size_t  ri_float32_to_size(ri_float32 from);
    RI_API ri_ssize  ri_float32_to_ssize(ri_float32 from);
    RI_API float  ri_float32_to_float(ri_float32 from);
    RI_API ri_float64  ri_float32_to_float64(ri_float32 from);
    RI_API double  ri_float32_to_double(ri_float32 from);

    RI_API int   ri_float64_to_int(ri_float64 from);
    RI_API ri_uint   ri_float64_to_uint(ri_float64 from);
    RI_API ri_int8  ri_float64_to_int8(ri_float64 from);
    RI_API ri_uint8   ri_float64_to_uint8(ri_float64 from);
    RI_API ri_int16  ri_float64_to_int16(ri_float64 from);
    RI_API ri_uint16  ri_float64_to_uint16(ri_float64 from);
    RI_API ri_int32 ri_float64_to_int32(ri_float64 from);
    RI_API ri_uint32   ri_float64_to_uint32(ri_float64 from);
    RI_API ri_int64  ri_float64_to_int64(ri_float64 from);
    RI_API ri_uint64   ri_float64_to_uint64(ri_float64 from);
    RI_API long  ri_float64_to_long(ri_float64 from);
    RI_API ri_ulong  ri_float64_to_ulong(ri_float64 from);
    RI_API ri_longlong  ri_float64_to_longlong(ri_float64 from);
    RI_API ri_ulonglong  ri_float64_to_ulonglong(ri_float64 from);
    RI_API size_t  ri_float64_to_size(ri_float64 from);
    RI_API ri_ssize  ri_float64_to_ssize(ri_float64 from);
    RI_API float  ri_float64_to_float(ri_float64 from);
    RI_API ri_float32  ri_float64_to_float32(ri_float64 from);
    RI_API double  ri_float64_to_double(ri_float64 from);

    RI_API int   ri_double_to_int(double from);
    RI_API ri_uint   ri_double_to_uint(double from);
    RI_API ri_uint   ri_double_to_uint(double from);
    RI_API ri_int8  ri_double_to_int8(double from);
    RI_API ri_uint8   ri_double_to_uint8(double from);
    RI_API ri_int16  ri_double_to_int16(double from);
    RI_API ri_uint16  ri_double_to_uint16(double from);
    RI_API ri_int32 ri_double_to_int32(double from);
    RI_API ri_uint32   ri_double_to_uint32(double from);
    RI_API ri_int64  ri_double_to_int64(double from);
    RI_API ri_uint64   ri_double_to_uint64(double from);
    RI_API long  ri_double_to_long(double from);
    RI_API ri_ulong  ri_double_to_ulong(double from);
    RI_API ri_longlong  ri_double_to_longlong(double from);
    RI_API ri_ulonglong  ri_double_to_ulonglong(double from);
    RI_API size_t  ri_double_to_size(double from);
    RI_API ri_ssize  ri_double_to_ssize(double from);
    RI_API float  ri_double_to_float(double from);
    RI_API ri_float32  ri_double_to_float32(double from);
    RI_API double  ri_double_to_float64(double from);

    RI_API int ri_ptr_sub_ptr(unsigned int *ptr_a, unsigned int *ptr_b);

#ifdef __cplusplus
}
#endif

#endif /* __RI_DATA_H__ */


