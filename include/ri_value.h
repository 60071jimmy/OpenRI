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

#ifndef __RI_VALUE_H__
#define __RI_VALUE_H__

#include "openri.h"

#ifdef __cplusplus
extern "C" 
{
#endif


typedef enum
{
  RI_VALUE_UNKNOWN = 0,
  RI_VALUE_INT,      
  RI_VALUE_UINT,
  RI_VALUE_INT8,
  RI_VALUE_UINT8,
  RI_VALUE_INT16,
  RI_VALUE_UINT16,
  RI_VALUE_INT32,
  RI_VALUE_UINT32,
  RI_VALUE_INT64,
  RI_VALUE_UINT64,
  RI_VALUE_LONG,
  RI_VALUE_ULONG,
  RI_VALUE_LONGLONG,
  RI_VALUE_ULONGLONG,
  RI_VALUE_SIZE,
  RI_VALUE_SSIZE,
  RI_VALUE_FLOAT,
  RI_VALUE_FLOAT32,
  RI_VALUE_FLOAT64,
  RI_VALUE_DOUBLE,
  RI_VALUE_STRING,  
  RI_VALUE_BINARY,
  RI_VALUE_DATE,
  RI_VALUE_TIME,
  RI_VALUE_DATE_TIME,
  RI_VALUE_TYPE_COUNT
} RI_VALUE_TYPE_t;

typedef struct {
  RI_VALUE_TYPE_t   type;  
  ri_byte           dataTemp[16];  // 128 bits temp for fixed length type.
  size_t           dataSize;  
  ri_byte          *data;           // for variable length type.
  
} RI_VALUE_t;


RI_API int   RI_VALUE_Init(RI_VALUE_t *value);
RI_API RI_VALUE_t *RI_VALUE_New(void);
RI_API int   RI_VALUE_Free(RI_VALUE_t *value);

RI_API int RI_VALUE_SetInt(RI_VALUE_t *value, int int_value);
RI_API int RI_VALUE_SetInt32(RI_VALUE_t *value, ri_int32 int32);
RI_API int RI_VALUE_SetUInt32(RI_VALUE_t *value, ri_uint32 uint32);
RI_API int RI_VALUE_SetString(RI_VALUE_t *value, ri_utf8 *str);
RI_API int RI_VALUE_SetInt8(RI_VALUE_t *value, ri_int8 int8);
RI_API int RI_VALUE_SetUInt8(RI_VALUE_t *value, ri_uint8 uint8);
RI_API int RI_VALUE_SetInt16(RI_VALUE_t *value, ri_int16 int16);
RI_API int RI_VALUE_SetUInt16(RI_VALUE_t *value, ri_uint16 uint16);
RI_API int RI_VALUE_SetInt64(RI_VALUE_t *value, ri_int64 int64);
RI_API int RI_VALUE_SetUInt64(RI_VALUE_t *value, ri_uint64 uint64);
RI_API int RI_VALUE_SetFloat(RI_VALUE_t *value, float float_value);
RI_API int RI_VALUE_SetFloat32(RI_VALUE_t *value, ri_float32 float32);
RI_API int RI_VALUE_SetFloat64(RI_VALUE_t *value, ri_float64 float64);
RI_API int RI_VALUE_SetBinary(RI_VALUE_t *value, ri_byte *binary, size_t size);
RI_API int RI_VALUE_SetDate(RI_VALUE_t *value, int year, int month, int day);
RI_API int RI_VALUE_SetTime(RI_VALUE_t *value, int hour, int min, int sec, int ms);
RI_API int RI_VALUE_SetDateTime(RI_VALUE_t *value,
                                           ri_int64 year,
                                           int month,
                                           int day,
                                           int hour,
                                           int min,
                                           int sec,
                                           int ms);
RI_API int RI_VALUE_SetZip(RI_VALUE_t *value, ri_byte *binary, size_t size);
RI_API int RI_VALUE_Empty(RI_VALUE_t *value);

RI_API RI_VALUE_TYPE_t RI_VALUE_GetType(RI_VALUE_t *value);
RI_API ri_int32        RI_VALUE_GetInt32(RI_VALUE_t *value);
RI_API ri_uint32       RI_VALUE_GetUInt32(RI_VALUE_t *value);
RI_API size_t         RI_VALUE_GetString(RI_VALUE_t *value, ri_utf8 *str, size_t str_size);
RI_API size_t         RI_VALUE_GetStringSize(RI_VALUE_t *value);
RI_API ri_int8         RI_VALUE_GetInt8(RI_VALUE_t *value);
RI_API ri_uint8        RI_VALUE_GetUInt8(RI_VALUE_t *value);
RI_API ri_int16        RI_VALUE_GetInt16(RI_VALUE_t *value);
RI_API ri_uint16       RI_VALUE_GetUInt16(RI_VALUE_t *value);
RI_API ri_int64        RI_VALUE_GetInt64(RI_VALUE_t *value);
RI_API ri_uint64       RI_VALUE_GetUInt64(RI_VALUE_t *value);
RI_API ri_float32      RI_VALUE_GetFloat32(RI_VALUE_t *value);
RI_API ri_float64      RI_VALUE_GetFloat64(RI_VALUE_t *value);
RI_API size_t         RI_VALUE_GetBinary(RI_VALUE_t *value, ri_byte *binary, size_t binary_size);
RI_API size_t         RI_VALUE_GetBinarySize(RI_VALUE_t *value);
RI_API ri_int64        RI_VALUE_GetYear(RI_VALUE_t *value);
RI_API int          RI_VALUE_GetMonth(RI_VALUE_t *value);
RI_API int          RI_VALUE_GetDay(RI_VALUE_t *value);
RI_API int          RI_VALUE_GetHour(RI_VALUE_t *value);
RI_API int          RI_VALUE_GetMin(RI_VALUE_t *value);
RI_API int          RI_VALUE_GetSec(RI_VALUE_t *value);
RI_API int          RI_VALUE_GetMs(RI_VALUE_t *value);
RI_API int        RI_VALUE_GetZip(RI_VALUE_t *value, ri_byte *zip, size_t zip_size);
RI_API size_t         RI_VALUE_GetZipSize(RI_VALUE_t *value);
RI_API int        RI_VALUE_SetType(RI_VALUE_t *value, RI_VALUE_TYPE_t type);


#ifdef __cplusplus
}
#endif

#endif /* __RI_VALUE_H__ */


