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

/**
* @name ri_data.c
*
* @brief Value library.
*
* @reference  
*
* @author Mingta Li 
*
* @version 2.1.0
* 
* @history 2009-07-02     Re-organize.                 Mingta Li 
* @history 2006-07-20     Initial version.             Mingta Li  
*
*/

#include "openri.h"


#ifdef __cplusplus
extern "C" 
{
#endif

    int ri_value_SetType(RI_VALUE_t *value, RI_VALUE_TYPE_t type);


    RI_API int RI_VALUE_Init(RI_VALUE_t *value)
    {
        if(value == NULL) return RI_ERROR_NULL_POINTER;

        ri_memset(value, 0, sizeof(RI_VALUE_t));

        value->type = RI_VALUE_UNKNOWN;

        return RI_OK;
    }

    RI_API RI_VALUE_t *RI_VALUE_New(void)
    {
        RI_VALUE_t *value;

        value = (RI_VALUE_t *)ri_calloc(1, sizeof(RiArray_t));
        if(value == NULL)
        {
            return NULL;
        }

        value->type = RI_VALUE_UNKNOWN;

        return value;
    }

    RI_API int RI_VALUE_Free(RI_VALUE_t *value)
    {
        ri_free(value);

        return RI_OK;
    }

    RI_API int ri_value_Empty(RI_VALUE_t *value)
    {
        if(value->dataSize > 0)
        {    
            ri_free(value->data);
            value->data = NULL;
            value->dataSize = 0;
        }
        value->type = RI_VALUE_UNKNOWN;

        return RI_OK;
    }

    RI_API int RI_VALUE_SetInt(RI_VALUE_t *value, int int_value)
    {
        ri_value_Empty(value);

        value->type = RI_VALUE_INT;
        ri_memcpy(value->dataTemp, &int_value, sizeof(ri_int));

        return RI_OK;  
    }

    RI_API int RI_VALUE_SetInt32(RI_VALUE_t *value, ri_int32 int32)
    {
        ri_value_Empty(value);

        value->type = RI_VALUE_INT32;
        ri_memcpy(value->dataTemp, &int32, sizeof(ri_int32));

        return RI_OK;  
    }

    RI_API int RI_VALUE_SetUInt32(RI_VALUE_t *value, ri_uint32 uint32)
    {
        ri_value_Empty(value);

        value->type = RI_VALUE_UINT32;
        ri_memcpy(value->dataTemp, &uint32, sizeof(ri_uint32));

        return RI_OK;  
    }

    RI_API int RI_VALUE_SetInt8(RI_VALUE_t *value, ri_int8 int8)
    {
        ri_value_Empty(value);

        value->type = RI_VALUE_INT8;
        ri_memcpy(value->dataTemp, &int8, sizeof(ri_int8));

        return RI_OK;  
    }

    RI_API int RI_VALUE_SetUInt8(RI_VALUE_t *value, ri_uint8 uint8)
    {
        ri_value_Empty(value);

        value->type = RI_VALUE_UINT8;
        ri_memcpy(value->dataTemp, &uint8, sizeof(ri_uint8));

        return RI_OK;  
    }

    RI_API int RI_VALUE_SetInt16(RI_VALUE_t *value, ri_int16 int16)
    {
        ri_value_Empty(value);

        value->type = RI_VALUE_INT16;
        ri_memcpy(value->dataTemp, &int16, sizeof(ri_int16));

        return RI_OK;  
    }

    RI_API int RI_VALUE_SetUInt16(RI_VALUE_t *value, ri_uint16 uint16)
    {
        ri_value_Empty(value);

        value->type = RI_VALUE_UINT16;
        ri_memcpy(value->dataTemp, &uint16, sizeof(ri_uint16));

        return RI_OK;  
    }

    RI_API int RI_VALUE_SetInt64(RI_VALUE_t *value, ri_int64 int64)
    {
        ri_value_Empty(value);

        value->type = RI_VALUE_INT64;
        ri_memcpy(value->dataTemp, &int64, sizeof(ri_int64));

        return RI_OK;  
    }

    RI_API int RI_VALUE_SetUInt64(RI_VALUE_t *value, ri_uint64 uint64)
    {
        ri_value_Empty(value);

        value->type = RI_VALUE_UINT64;
        ri_memcpy(value->dataTemp, &uint64, sizeof(ri_uint64));

        return RI_OK;  
    }

    RI_API int RI_VALUE_SetFloat(RI_VALUE_t *value, float float_value)
    {
        ri_value_Empty(value);

        value->type = RI_VALUE_FLOAT;
        ri_memcpy(value->dataTemp, &float_value, sizeof(ri_float));

        return RI_OK;  
    }

    RI_API int RI_VALUE_SetFloat32(RI_VALUE_t *value, ri_float32 float32)
    {
        ri_value_Empty(value);

        value->type = RI_VALUE_FLOAT32;
        ri_memcpy(value->dataTemp, &float32, sizeof(ri_float32));

        return RI_OK;  
    }

    RI_API int RI_VALUE_SetFloat64(RI_VALUE_t *value, ri_float64 float64)
    {
        ri_value_Empty(value);

        value->type = RI_VALUE_FLOAT64;
        ri_memcpy(value->dataTemp, &float64, sizeof(ri_float64));

        return RI_OK;  
    }

    RI_API int RI_VALUE_SetDate(RI_VALUE_t *value, int year, int month, int day)
    {
        RiDateTime_t date_time;

        if(month < 1 || month >    12)  return RI_ERROR_PARAMETER_WRONG;
        if(day   < 1 || day   >    31)  return RI_ERROR_PARAMETER_WRONG;  

        ri_value_Empty(value);

        RiDateTime_Init(&date_time);  
        date_time.year = year;
        date_time.month = month;
        date_time.day = day;

        value->data = (ri_byte *)ri_malloc(sizeof(RiDateTime_t));
        if(value->data == NULL)
        {
            return RI_ERROR; 
        }
        value->dataSize = sizeof(RiDateTime_t);
        ri_memcpy(value->data, &date_time, (int)value->dataSize);
        value->type = RI_VALUE_DATE;

        return RI_OK;   
    }

    RI_API int RI_VALUE_SetTime(RI_VALUE_t *value, int hour, int min, int sec, int ms)
    {
        RiDateTime_t date_time;

        if(hour  < 0 || hour  >=   24)  return RI_ERROR_PARAMETER_WRONG;
        if(min   < 0 || min   >=   60)  return RI_ERROR_PARAMETER_WRONG;
        if(sec   < 0 || sec   >=   60)  return RI_ERROR_PARAMETER_WRONG;
        if(ms    < 0 || ms    >= 1000)  return RI_ERROR_PARAMETER_WRONG;

        ri_value_Empty(value);

        RiDateTime_Init(&date_time);  
        date_time.hour = hour;
        date_time.min = min;
        date_time.sec = sec;
        date_time.ms = ms;

        value->data = (ri_byte *)ri_malloc(sizeof(RiDateTime_t));
        if(value->data == NULL)
        {
            return RI_ERROR; 
        }
        value->dataSize = sizeof(RiDateTime_t);
        ri_memcpy(value->data, &date_time, (int)value->dataSize);
        value->type = RI_VALUE_TIME;

        return RI_OK;   
    }
    RI_API int RI_VALUE_SetDateTime(RI_VALUE_t *value,
        ri_int64 year,
        int   month,
        int   day,
        int   hour,
        int   min,
        int   sec,
        int   ms)
    {
        RiDateTime_t date_time;

        if(month < 1 || month >    12)  return RI_ERROR_PARAMETER_WRONG;
        if(day   < 1 || day   >    31)  return RI_ERROR_PARAMETER_WRONG;
        if(hour  < 0 || hour  >=   24)  return RI_ERROR_PARAMETER_WRONG;
        if(min   < 0 || min   >=   60)  return RI_ERROR_PARAMETER_WRONG;
        if(sec   < 0 || sec   >=   60)  return RI_ERROR_PARAMETER_WRONG;
        if(ms    < 0 || ms    >= 1000)  return RI_ERROR_PARAMETER_WRONG;

        ri_value_Empty(value);

        RiDateTime_Init(&date_time);  
        date_time.year = year;
        date_time.month = month;
        date_time.day = day;
        date_time.hour = hour;
        date_time.min = min;
        date_time.sec = sec;
        date_time.ms = ms;

        value->data = (ri_byte *)ri_malloc(sizeof(RiDateTime_t));
        if(value->data == NULL)
        {
            return RI_ERROR; 
        }
        value->dataSize = sizeof(RiDateTime_t);
        ri_memcpy(value->data, &date_time, (int)value->dataSize);
        value->type = RI_VALUE_DATE_TIME;

        return RI_OK;  
    }

    RI_API int RI_VALUE_SetBinary(RI_VALUE_t *value, ri_byte *binary, size_t size)
    {
        ri_value_Empty(value);

        value->data = (ri_byte *)ri_malloc((int)size);
        if(value->data == NULL)
        {
            return RI_ERROR; 
        }
        value->dataSize = size;
        ri_memcpy(value->data, binary, (int)value->dataSize);
        value->type = RI_VALUE_BINARY;

        return RI_OK; 
    }

    RI_API int RI_VALUE_SetString(RI_VALUE_t *value, ri_utf8 *str)
    {
        //size_t size;

        ri_value_Empty(value);

        /*size = ri_strsize(str);

        value->data = (ri_byte *)ri_calloc(1, size) + 1;  // Extra 1 for string end.
        if(value->data == NULL)
        {
        RiLock_Unlock(&value->lock);
        RiLock_Unlock(&lock);
        return RI_ERROR; 
        }
        value->dataSize = size;
        ri_memcpy(value->data, str, (int)value->dataSize);
        value->type = RI_VALUE_STRING;


        RiLock_Unlock(&value->lock);
        */
        return RI_OK; 
    }                                         

    RI_API int RI_VALUE_Empty(RI_VALUE_t *value)
    {
        int ret;

        ret = ri_value_Empty(value);

        return ret;   
    }

    RI_API RI_VALUE_TYPE_t RI_VALUE_GetType(RI_VALUE_t *value)
    {
        RI_VALUE_TYPE_t type;

        type = value->type;

        return type;
    }

    int ri_value_SetType(RI_VALUE_t *value, RI_VALUE_TYPE_t type)
    {
        int ret;

        if(type == RI_VALUE_UNKNOWN)
        {
            ret = ri_value_Empty(value);
            return ret;
        }

        if(value->type == RI_VALUE_UNKNOWN)
        {
            value->type = type;
            return RI_OK;
        }

        ret = RI_OK;


        if(value->type == RI_VALUE_INT && type == RI_VALUE_UINT)
        {
            int   from;
            ri_uint  to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int));
            to = ri_int_to_uint(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint));
            value->type = RI_VALUE_UINT;
        }
        else if(value->type == RI_VALUE_INT && type == RI_VALUE_INT8)
        {
            int   from;
            ri_int8 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int));
            to = ri_int_to_int8(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int8));
            value->type = RI_VALUE_INT8;
        } 
        else if(value->type == RI_VALUE_INT && type == RI_VALUE_UINT8)
        {
            int   from;
            ri_uint8 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int));
            to = ri_int_to_uint8(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint8));
            value->type = RI_VALUE_UINT8;
        }
        else if(value->type == RI_VALUE_INT && type == RI_VALUE_INT16)
        {
            int from;
            ri_int16 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int));
            to = ri_int_to_int16(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int16));
            value->type = RI_VALUE_INT16;
        }
        else if(value->type == RI_VALUE_INT && type == RI_VALUE_UINT16)
        {
            int from;
            ri_uint16 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int));
            to = ri_int_to_uint16(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint16));
            value->type = RI_VALUE_UINT16;
        }
        else if(value->type == RI_VALUE_INT && type == RI_VALUE_INT32)
        {
            int from;
            ri_int32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int));
            to = ri_int_to_int32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int32));
            value->type = RI_VALUE_INT32;
        }
        else if(value->type == RI_VALUE_INT && type == RI_VALUE_UINT32)
        {
            int from;
            ri_uint32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int));
            to = ri_int_to_uint32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint32));
            value->type = RI_VALUE_UINT32;
        }
        else if(value->type == RI_VALUE_INT && type == RI_VALUE_INT64)
        {
            int from;
            ri_int64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int));
            to = ri_int_to_int64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int64));
            value->type = RI_VALUE_INT64;
        }
        else if(value->type == RI_VALUE_INT && type == RI_VALUE_UINT64)
        {
            int from;
            ri_uint64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int));
            to = ri_int_to_uint64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint64));
            value->type = RI_VALUE_UINT64;
        }
        else if(value->type == RI_VALUE_INT && type == RI_VALUE_LONG)
        {
            int from;
            long to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int));
            to = ri_int_to_long(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_long));
            value->type = RI_VALUE_LONG;
        }
        else if(value->type == RI_VALUE_INT && type == RI_VALUE_ULONG)
        {
            int from;
            ri_ulong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int));
            to = ri_int_to_ulong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ulong));
            value->type = RI_VALUE_ULONG;
        }
        else if(value->type == RI_VALUE_INT && type == RI_VALUE_LONGLONG)
        {
            int from;
            ri_longlong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int));
            to = ri_int_to_longlong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_longlong));
            value->type = RI_VALUE_LONGLONG;
        }
        else if(value->type == RI_VALUE_INT && type == RI_VALUE_ULONGLONG)
        {
            int from;
            ri_ulonglong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int));
            to = ri_int_to_ulonglong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ulonglong));
            value->type = RI_VALUE_ULONGLONG;
        }       
        else if(value->type == RI_VALUE_INT && type == RI_VALUE_SIZE)
        {
            int from;
            size_t to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int));
            to = ri_int_to_size(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_size));
            value->type = RI_VALUE_SIZE;
        }
        else if(value->type == RI_VALUE_INT && type == RI_VALUE_SSIZE)
        {
            int from;
            ri_ssize to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int));
            to = ri_int_to_ssize(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ssize));
            value->type = RI_VALUE_SSIZE;
        }
        else if(value->type == RI_VALUE_INT && type == RI_VALUE_FLOAT)
        {
            int from;
            float to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int));
            to = ri_int_to_float(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float));
            value->type = RI_VALUE_FLOAT;
        }
        else if(value->type == RI_VALUE_INT && type == RI_VALUE_FLOAT32)
        {
            int from;
            ri_float32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int));
            to = ri_int_to_float32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float32));
            value->type = RI_VALUE_FLOAT32;
        }
        else if(value->type == RI_VALUE_INT && type == RI_VALUE_FLOAT64)
        {
            int from;
            ri_float64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int));
            to = ri_int_to_float64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float64));
            value->type = RI_VALUE_FLOAT64;
        }
        else if(value->type == RI_VALUE_INT && type == RI_VALUE_DOUBLE)
        {
            int from;
            double to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int));
            to = ri_int_to_double(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_double));
            value->type = RI_VALUE_DOUBLE;
        }




        else if(value->type == RI_VALUE_UINT && type == RI_VALUE_INT)
        {
            ri_uint   from;
            int  to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint));
            to = ri_uint_to_int(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int));
            value->type = RI_VALUE_INT;
        }
        else if(value->type == RI_VALUE_UINT && type == RI_VALUE_INT8)
        {
            ri_uint   from;
            ri_int8 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint));
            to = ri_uint_to_int8(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int8));
            value->type = RI_VALUE_INT8;
        }
        else if(value->type == RI_VALUE_UINT && type == RI_VALUE_UINT8)
        {
            ri_uint   from;
            ri_uint8 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint));
            to = ri_uint_to_uint8(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint8));
            value->type = RI_VALUE_UINT8;
        }

        else if(value->type == RI_VALUE_UINT && type == RI_VALUE_INT16)
        {
            ri_uint from;
            ri_int16 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint));
            to = ri_uint_to_int16(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int16));
            value->type = RI_VALUE_INT16;
        }
        else if(value->type == RI_VALUE_UINT && type == RI_VALUE_UINT16)
        {
            ri_uint from;
            ri_uint16 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint));
            to = ri_uint_to_uint16(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint16));
            value->type = RI_VALUE_UINT16;
        }
        else if(value->type == RI_VALUE_UINT && type == RI_VALUE_INT32)
        {
            ri_uint from;
            ri_int32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint));
            to = ri_uint_to_int32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int32));
            value->type = RI_VALUE_INT32;
        }
        else if(value->type == RI_VALUE_UINT && type == RI_VALUE_UINT32)
        {
            ri_uint from;
            ri_uint32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint));
            to = ri_uint_to_uint32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint32));
            value->type = RI_VALUE_UINT32;
        }
        else if(value->type == RI_VALUE_UINT && type == RI_VALUE_INT64)
        {
            ri_uint from;
            ri_int64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint));
            to = ri_uint_to_int64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int64));
            value->type = RI_VALUE_INT64;
        }
        else if(value->type == RI_VALUE_UINT && type == RI_VALUE_UINT64)
        {
            ri_uint from;
            ri_uint64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint));
            to = ri_uint_to_uint64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint64));
            value->type = RI_VALUE_UINT64;
        }
        else if(value->type == RI_VALUE_UINT && type == RI_VALUE_LONG)
        {
            ri_uint from;
            long to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint));
            to = ri_uint_to_long(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_long));
            value->type = RI_VALUE_LONG;
        }
        else if(value->type == RI_VALUE_UINT && type == RI_VALUE_ULONG)
        {
            ri_uint from;
            ri_ulong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint));
            to = ri_uint_to_ulong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ulong));
            value->type = RI_VALUE_ULONG;
        }
        else if(value->type == RI_VALUE_UINT && type == RI_VALUE_LONGLONG)
        {
            ri_uint from;
            ri_longlong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint));
            to = ri_uint_to_longlong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_longlong));
            value->type = RI_VALUE_LONGLONG;
        }
        else if(value->type == RI_VALUE_UINT && type == RI_VALUE_ULONGLONG)
        {
            ri_uint from;
            ri_ulonglong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint));
            to = ri_uint_to_ulonglong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ulonglong));
            value->type = RI_VALUE_ULONGLONG;
        }           
        else if(value->type == RI_VALUE_UINT && type == RI_VALUE_SIZE)
        {
            ri_uint from;
            size_t to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint));
            to = ri_uint_to_size(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_size));
            value->type = RI_VALUE_SIZE;
        }
        else if(value->type == RI_VALUE_UINT && type == RI_VALUE_SSIZE)
        {
            ri_uint from;
            ri_ssize to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint));
            to = ri_uint_to_ssize(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ssize));
            value->type = RI_VALUE_SSIZE;
        }
        else if(value->type == RI_VALUE_UINT && type == RI_VALUE_FLOAT)
        {
            ri_uint from;
            float to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint));
            to = ri_uint_to_float(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float));
            value->type = RI_VALUE_FLOAT;
        }
        else if(value->type == RI_VALUE_UINT && type == RI_VALUE_FLOAT32)
        {
            ri_uint from;
            ri_float32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint));
            to = ri_uint_to_float32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float32));
            value->type = RI_VALUE_FLOAT32;
        }
        else if(value->type == RI_VALUE_UINT && type == RI_VALUE_FLOAT64)
        {
            ri_uint from;
            ri_float64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint));
            to = ri_uint_to_float64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float64));
            value->type = RI_VALUE_FLOAT64;
        }
        else if(value->type == RI_VALUE_UINT && type == RI_VALUE_DOUBLE)
        {
            ri_uint from;
            double to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint));
            to = ri_uint_to_double(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_double));
            value->type = RI_VALUE_DOUBLE;
        }


        else if(value->type == RI_VALUE_INT8 && type == RI_VALUE_INT)
        {
            ri_int8   from;
            int  to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int8));
            to = ri_int8_to_int(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int));
            value->type = RI_VALUE_INT;
        }
        else if(value->type == RI_VALUE_INT8 && type == RI_VALUE_UINT)
        {
            ri_int8   from;
            ri_uint  to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int8));
            to = ri_int8_to_uint(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint));
            value->type = RI_VALUE_UINT;
        }  
        else if(value->type == RI_VALUE_INT8 && type == RI_VALUE_UINT8)
        {
            ri_int8   from;
            ri_uint8 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int8));
            to = ri_int8_to_uint8(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint8));
            value->type = RI_VALUE_UINT8;
        }
        else if(value->type == RI_VALUE_INT8 && type == RI_VALUE_INT16)
        {
            ri_int8 from;
            ri_int16 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int8));
            to = ri_int8_to_int16(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int16));
            value->type = RI_VALUE_INT16;
        }
        else if(value->type == RI_VALUE_INT8 && type == RI_VALUE_UINT16)
        {
            ri_int8 from;
            ri_uint16 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int8));
            to = ri_int8_to_uint16(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint16));
            value->type = RI_VALUE_UINT16;
        }
        else if(value->type == RI_VALUE_INT8 && type == RI_VALUE_INT32)
        {
            ri_int8 from;
            ri_int32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int8));
            to = ri_int8_to_int32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int32));
            value->type = RI_VALUE_INT32;
        }
        else if(value->type == RI_VALUE_INT8 && type == RI_VALUE_UINT32)
        {
            ri_int8 from;
            ri_uint32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int8));
            to = ri_int8_to_uint32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint32));
            value->type = RI_VALUE_UINT32;
        }
        else if(value->type == RI_VALUE_INT8 && type == RI_VALUE_INT64)
        {
            ri_int8 from;
            ri_int64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int8));
            to = ri_int8_to_int64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int64));
            value->type = RI_VALUE_INT64;
        }
        else if(value->type == RI_VALUE_INT8 && type == RI_VALUE_UINT64)
        {
            ri_int8 from;
            ri_uint64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int8));
            to = ri_int8_to_uint64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint64));
            value->type = RI_VALUE_UINT64;
        }
        else if(value->type == RI_VALUE_INT8 && type == RI_VALUE_SIZE)
        {
            ri_int8 from;
            size_t to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int8));
            to = ri_int8_to_size(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_size));
            value->type = RI_VALUE_SIZE;
        }
        else if(value->type == RI_VALUE_INT8 && type == RI_VALUE_LONG)
        {
            ri_int8 from;
            long to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int8));
            to = ri_int8_to_long(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_long));
            value->type = RI_VALUE_LONG;
        }
        else if(value->type == RI_VALUE_INT8 && type == RI_VALUE_ULONG)
        {
            ri_int8 from;
            ri_ulong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int8));
            to = ri_int8_to_ulong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ulong));
            value->type = RI_VALUE_ULONG;
        }
        else if(value->type == RI_VALUE_INT8 && type == RI_VALUE_LONGLONG)
        {
            ri_int8 from;
            ri_longlong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int8));
            to = ri_int8_to_longlong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_longlong));
            value->type = RI_VALUE_LONGLONG;
        }
        else if(value->type == RI_VALUE_INT8 && type == RI_VALUE_ULONGLONG)
        {
            ri_int8 from;
            ri_ulonglong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int8));
            to = ri_int8_to_ulonglong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ulonglong));
            value->type = RI_VALUE_ULONGLONG;
        }  
        else if(value->type == RI_VALUE_INT8 && type == RI_VALUE_SSIZE)
        {
            ri_int8 from;
            ri_ssize to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int8));
            to = ri_int8_to_ssize(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ssize));
            value->type = RI_VALUE_SSIZE;
        }
        else if(value->type == RI_VALUE_INT8 && type == RI_VALUE_FLOAT)
        {
            ri_int8 from;
            float to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int8));
            to = ri_int8_to_float(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float));
            value->type = RI_VALUE_FLOAT;
        }
        else if(value->type == RI_VALUE_INT8 && type == RI_VALUE_FLOAT32)
        {
            ri_int8 from;
            ri_float32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int8));
            to = ri_int8_to_float32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float32));
            value->type = RI_VALUE_FLOAT32;
        }
        else if(value->type == RI_VALUE_INT8 && type == RI_VALUE_FLOAT64)
        {
            ri_int8 from;
            ri_float64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int8));
            to = ri_int8_to_float64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float64));
            value->type = RI_VALUE_FLOAT64;
        }
        else if(value->type == RI_VALUE_INT8 && type == RI_VALUE_DOUBLE)
        {
            ri_int8 from;
            double to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int8));
            to = ri_int8_to_double(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_double));
            value->type = RI_VALUE_DOUBLE;
        }







        else if(value->type == RI_VALUE_UINT8 && type == RI_VALUE_INT)
        {
            ri_uint8   from;
            int  to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint8));
            to = ri_uint8_to_int(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int));
            value->type = RI_VALUE_INT;
        }
        else if(value->type == RI_VALUE_UINT8 && type == RI_VALUE_UINT)
        {
            ri_uint8   from;
            ri_uint  to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint8));
            to = ri_uint8_to_uint(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint));
            value->type = RI_VALUE_UINT;
        }
        else if(value->type == RI_VALUE_UINT8 && type == RI_VALUE_INT8)
        {
            ri_uint8   from;
            ri_int8 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint8));
            to = ri_uint8_to_int8(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int8));
            value->type = RI_VALUE_INT8;
        }
        else if(value->type == RI_VALUE_UINT8 && type == RI_VALUE_INT16)
        {
            ri_uint8 from;
            ri_int16 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint8));
            to = ri_uint8_to_int16(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int16));
            value->type = RI_VALUE_INT16;
        }
        else if(value->type == RI_VALUE_UINT8 && type == RI_VALUE_UINT16)
        {
            ri_uint8 from;
            ri_uint16 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint8));
            to = ri_uint8_to_uint16(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint16));
            value->type = RI_VALUE_UINT16;
        }
        else if(value->type == RI_VALUE_UINT8 && type == RI_VALUE_INT32)
        {
            ri_uint8 from;
            ri_int32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint8));
            to = ri_uint8_to_int32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int32));
            value->type = RI_VALUE_INT32;
        }
        else if(value->type == RI_VALUE_UINT8 && type == RI_VALUE_UINT32)
        {
            ri_uint8 from;
            ri_uint32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint8));
            to = ri_uint8_to_uint32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint32));
            value->type = RI_VALUE_UINT32;
        }
        else if(value->type == RI_VALUE_UINT8 && type == RI_VALUE_INT64)
        {
            ri_uint8 from;
            ri_int64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint8));
            to = ri_uint8_to_int64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int64));
            value->type = RI_VALUE_INT64;
        }
        else if(value->type == RI_VALUE_UINT8 && type == RI_VALUE_UINT64)
        {
            ri_uint8 from;
            ri_uint64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint8));
            to = ri_uint8_to_uint64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint64));
            value->type = RI_VALUE_UINT64;
        }
        else if(value->type == RI_VALUE_UINT8 && type == RI_VALUE_LONG)
        {
            ri_uint8 from;
            long to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint8));
            to = ri_uint8_to_long(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_long));
            value->type = RI_VALUE_LONG;
        }
        else if(value->type == RI_VALUE_UINT8 && type == RI_VALUE_ULONG)
        {
            ri_uint8 from;
            ri_ulong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint8));
            to = ri_int_to_ulong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ulong));
            value->type = RI_VALUE_ULONG;
        }
        else if(value->type == RI_VALUE_UINT8 && type == RI_VALUE_LONGLONG)
        {
            ri_uint8 from;
            ri_longlong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint8));
            to = ri_uint8_to_longlong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_longlong));
            value->type = RI_VALUE_LONGLONG;
        }
        else if(value->type == RI_VALUE_UINT8 && type == RI_VALUE_ULONGLONG)
        {
            ri_uint8 from;
            ri_ulonglong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint8));
            to = ri_uint8_to_ulonglong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ulonglong));
            value->type = RI_VALUE_ULONGLONG;
        }      
        else if(value->type == RI_VALUE_UINT8 && type == RI_VALUE_SIZE)
        {
            ri_uint8 from;
            size_t to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint8));
            to = ri_uint8_to_size(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_size));
            value->type = RI_VALUE_SIZE;
        }
        else if(value->type == RI_VALUE_UINT8 && type == RI_VALUE_SSIZE)
        {
            ri_uint8 from;
            ri_ssize to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint8));
            to = ri_uint8_to_ssize(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ssize));
            value->type = RI_VALUE_SSIZE;
        }
        else if(value->type == RI_VALUE_UINT8 && type == RI_VALUE_FLOAT)
        {
            ri_uint8 from;
            float to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint8));
            to = ri_uint8_to_float(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float));
            value->type = RI_VALUE_FLOAT;
        }
        else if(value->type == RI_VALUE_UINT8 && type == RI_VALUE_FLOAT32)
        {
            ri_uint8 from;
            ri_float32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint8));
            to = ri_uint8_to_float32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float32));
            value->type = RI_VALUE_FLOAT32;
        }
        else if(value->type == RI_VALUE_UINT8 && type == RI_VALUE_FLOAT64)
        {
            ri_uint8 from;
            ri_float64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint8));
            to = ri_uint8_to_float64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float64));
            value->type = RI_VALUE_FLOAT64;
        }
        else if(value->type == RI_VALUE_UINT8 && type == RI_VALUE_DOUBLE)
        {
            ri_uint8 from;
            double to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint8));
            to = ri_uint8_to_double(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_double));
            value->type = RI_VALUE_DOUBLE;
        }








        else if(value->type == RI_VALUE_INT16 && type == RI_VALUE_INT)
        {
            ri_int16   from;
            int  to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int16));
            to = ri_int16_to_int(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int));
            value->type = RI_VALUE_INT;
        }
        else if(value->type == RI_VALUE_INT16 && type == RI_VALUE_UINT)
        {
            ri_int16   from;
            ri_uint  to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int16));
            to = ri_int16_to_uint(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint));
            value->type = RI_VALUE_INT;
        }
        else if(value->type == RI_VALUE_INT16 && type == RI_VALUE_INT8)
        {
            ri_int16   from;
            ri_int8 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int16));
            to = ri_int16_to_int8(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int8));
            value->type = RI_VALUE_INT8;
        }
        else if(value->type == RI_VALUE_INT16 && type == RI_VALUE_UINT8)
        {
            ri_int16 from;
            ri_uint8 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int16));
            to = ri_int16_to_uint8(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint8));
            value->type = RI_VALUE_UINT8;
        }
        else if(value->type == RI_VALUE_INT16 && type == RI_VALUE_UINT16)
        {
            ri_int16 from;
            ri_uint16 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int16));
            to = ri_int16_to_uint16(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint16));
            value->type = RI_VALUE_UINT16;
        }
        else if(value->type == RI_VALUE_INT16 && type == RI_VALUE_INT32)
        {
            ri_int16 from;
            ri_int32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int16));
            to = ri_int16_to_int32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int32));
            value->type = RI_VALUE_INT32;
        }
        else if(value->type == RI_VALUE_INT16 && type == RI_VALUE_UINT32)
        {
            ri_int16 from;
            ri_uint32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int16));
            to = ri_int16_to_uint32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint32));
            value->type = RI_VALUE_UINT32;
        }
        else if(value->type == RI_VALUE_INT16 && type == RI_VALUE_INT64)
        {
            ri_int16 from;
            ri_int64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int16));
            to = ri_int16_to_int64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int64));
            value->type = RI_VALUE_INT64;
        }
        else if(value->type == RI_VALUE_INT16 && type == RI_VALUE_UINT64)
        {
            ri_int16 from;
            ri_uint64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int16));
            to = ri_int16_to_uint64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint64));
            value->type = RI_VALUE_UINT64;
        }
        else if(value->type == RI_VALUE_INT16 && type == RI_VALUE_LONG)
        {
            ri_int16 from;
            long to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int16));
            to = ri_int16_to_long(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_long));
            value->type = RI_VALUE_LONG;
        }
        else if(value->type == RI_VALUE_INT16 && type == RI_VALUE_ULONG)
        {
            ri_int16 from;
            ri_ulong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int16));
            to = ri_int16_to_ulong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ulong));
            value->type = RI_VALUE_ULONG;
        }
        else if(value->type == RI_VALUE_INT16 && type == RI_VALUE_LONGLONG)
        {
            ri_int16 from;
            ri_longlong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int16));
            to = ri_int16_to_longlong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_longlong));
            value->type = RI_VALUE_LONGLONG;
        }
        else if(value->type == RI_VALUE_INT16 && type == RI_VALUE_ULONGLONG)
        {
            ri_int16 from;
            ri_ulonglong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int16));
            to = ri_int16_to_ulonglong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ulonglong));
            value->type = RI_VALUE_ULONGLONG;
        }  
        else if(value->type == RI_VALUE_INT16 && type == RI_VALUE_SIZE)
        {
            ri_int16 from;
            size_t to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int16));
            to = ri_int16_to_size(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_size));
            value->type = RI_VALUE_SIZE;
        }
        else if(value->type == RI_VALUE_INT16 && type == RI_VALUE_SSIZE)
        {
            ri_int16 from;
            ri_ssize to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int16));
            to = ri_int16_to_ssize(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ssize));
            value->type = RI_VALUE_SSIZE;
        }
        else if(value->type == RI_VALUE_INT16 && type == RI_VALUE_FLOAT)
        {
            ri_int16 from;
            float to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int16));
            to = ri_int16_to_float(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float));
            value->type = RI_VALUE_FLOAT;
        }
        else if(value->type == RI_VALUE_INT16 && type == RI_VALUE_FLOAT32)
        {
            ri_int16 from;
            ri_float32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int16));
            to = ri_int16_to_float32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float32));
            value->type = RI_VALUE_FLOAT32;
        }
        else if(value->type == RI_VALUE_INT16 && type == RI_VALUE_FLOAT64)
        {
            ri_int16 from;
            ri_float64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int16));
            to = ri_int16_to_float64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float64));
            value->type = RI_VALUE_FLOAT64;
        }
        else if(value->type == RI_VALUE_INT16 && type == RI_VALUE_DOUBLE)
        {
            ri_int16 from;
            double to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int16));
            to = ri_int16_to_double(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_double));
            value->type = RI_VALUE_DOUBLE;
        }








        else if(value->type == RI_VALUE_UINT16 && type == RI_VALUE_INT)
        {
            ri_uint16   from;
            int  to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint16));
            to = ri_uint16_to_int(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int));
            value->type = RI_VALUE_INT;
        }
        else if(value->type == RI_VALUE_UINT16 && type == RI_VALUE_UINT)
        {
            ri_uint16   from;
            ri_uint  to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint16));
            to = ri_uint16_to_uint(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint));
            value->type = RI_VALUE_UINT;
        }
        else if(value->type == RI_VALUE_UINT16 && type == RI_VALUE_INT8)
        {
            ri_uint16   from;
            ri_int8 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint16));
            to = ri_uint16_to_int8(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int8));
            value->type = RI_VALUE_INT8;
        }
        else if(value->type == RI_VALUE_UINT16 && type == RI_VALUE_UINT8)
        {
            ri_uint16 from;
            ri_uint8 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint16));
            to = ri_uint16_to_uint8(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint8));
            value->type = RI_VALUE_UINT8;
        }
        else if(value->type == RI_VALUE_UINT16 && type == RI_VALUE_INT16)
        {
            ri_uint16 from;
            ri_int16 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint16));
            to = ri_uint16_to_int16(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int16));
            value->type = RI_VALUE_INT16;
        }
        else if(value->type == RI_VALUE_UINT16 && type == RI_VALUE_INT32)
        {
            ri_uint16 from;
            ri_int32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint16));
            to = ri_uint16_to_int32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int32));
            value->type = RI_VALUE_INT32;
        }
        else if(value->type == RI_VALUE_UINT16 && type == RI_VALUE_UINT32)
        {
            ri_uint16 from;
            ri_uint32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint16));
            to = ri_uint16_to_uint32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint32));
            value->type = RI_VALUE_UINT32;
        }
        else if(value->type == RI_VALUE_UINT16 && type == RI_VALUE_INT64)
        {
            ri_uint16 from;
            ri_int64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint16));
            to = ri_uint16_to_int64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int64));
            value->type = RI_VALUE_INT64;
        }
        else if(value->type == RI_VALUE_UINT16 && type == RI_VALUE_UINT64)
        {
            ri_uint16 from;
            ri_uint64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint16));
            to = ri_uint16_to_uint64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint64));
            value->type = RI_VALUE_UINT64;
        }
        else if(value->type == RI_VALUE_UINT16 && type == RI_VALUE_LONG)
        {
            ri_uint16 from;
            long to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint16));
            to = ri_uint16_to_long(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_long));
            value->type = RI_VALUE_LONG;
        }
        else if(value->type == RI_VALUE_UINT16 && type == RI_VALUE_ULONG)
        {
            ri_uint16 from;
            ri_ulong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint16));
            to = ri_uint16_to_ulong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ulong));
            value->type = RI_VALUE_ULONG;
        }
        else if(value->type == RI_VALUE_UINT16 && type == RI_VALUE_LONGLONG)
        {
            ri_uint16 from;
            ri_longlong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint16));
            to = ri_uint16_to_longlong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_longlong));
            value->type = RI_VALUE_LONGLONG;
        }
        else if(value->type == RI_VALUE_UINT16 && type == RI_VALUE_ULONGLONG)
        {
            ri_uint16 from;
            ri_ulonglong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint16));
            to = ri_uint16_to_ulonglong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ulonglong));
            value->type = RI_VALUE_ULONGLONG;
        } 
        else if(value->type == RI_VALUE_UINT16 && type == RI_VALUE_SIZE)
        {
            ri_uint16 from;
            size_t to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint16));
            to = ri_uint16_to_size(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_size));
            value->type = RI_VALUE_SIZE;
        }
        else if(value->type == RI_VALUE_UINT16 && type == RI_VALUE_SSIZE)
        {
            ri_uint16 from;
            ri_ssize to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint16));
            to = ri_uint16_to_ssize(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ssize));
            value->type = RI_VALUE_SSIZE;
        }
        else if(value->type == RI_VALUE_UINT16 && type == RI_VALUE_FLOAT)
        {
            ri_uint16 from;
            float to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint16));
            to = ri_uint16_to_float(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float));
            value->type = RI_VALUE_FLOAT;
        }
        else if(value->type == RI_VALUE_UINT16 && type == RI_VALUE_FLOAT32)
        {
            ri_uint16 from;
            ri_float32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint16));
            to = ri_uint16_to_float32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float32));
            value->type = RI_VALUE_FLOAT32;
        }
        else if(value->type == RI_VALUE_UINT16 && type == RI_VALUE_FLOAT64)
        {
            ri_uint16 from;
            ri_float64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint16));
            to = ri_uint16_to_float64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float64));
            value->type = RI_VALUE_FLOAT64;
        }
        else if(value->type == RI_VALUE_UINT16 && type == RI_VALUE_DOUBLE)
        {
            ri_uint16 from;
            double to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint16));
            to = ri_uint16_to_double(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_double));
            value->type = RI_VALUE_DOUBLE;
        }









        else if(value->type == RI_VALUE_INT32 && type == RI_VALUE_INT)
        {
            ri_int32   from;
            int  to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int32));
            to = ri_int32_to_int(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int));
            value->type = RI_VALUE_INT;
        }
        else if(value->type == RI_VALUE_INT32 && type == RI_VALUE_UINT)
        {
            ri_int32   from;
            ri_uint  to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int32));
            to = ri_int32_to_uint(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint));
            value->type = RI_VALUE_UINT;
        }
        else if(value->type == RI_VALUE_INT32 && type == RI_VALUE_INT8)
        {
            ri_int32   from;
            ri_int8 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int32));
            to = ri_int32_to_int8(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int8));
            value->type = RI_VALUE_INT8;
        }
        else if(value->type == RI_VALUE_INT32 && type == RI_VALUE_UINT8)
        {
            ri_int32 from;
            ri_uint8 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int32));
            to = ri_int32_to_uint8(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint8));
            value->type = RI_VALUE_UINT8;
        }
        else if(value->type == RI_VALUE_INT32 && type == RI_VALUE_INT16)
        {
            ri_int32 from;
            ri_int16 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int32));
            to = ri_int32_to_int16(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int16));
            value->type = RI_VALUE_INT16;
        }
        else if(value->type == RI_VALUE_INT32 && type == RI_VALUE_UINT16)
        {
            ri_int32 from;
            ri_uint16 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int32));
            to = ri_int32_to_uint16(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint16));
            value->type = RI_VALUE_UINT16;
        }
        else if(value->type == RI_VALUE_INT32 && type == RI_VALUE_UINT32)
        {
            ri_int32 from;
            ri_uint32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int32));
            to = ri_int32_to_uint32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint32));
            value->type = RI_VALUE_UINT32;
        }
        else if(value->type == RI_VALUE_INT32 && type == RI_VALUE_INT64)
        {
            ri_int32 from;
            ri_int64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int32));
            to = ri_int32_to_int64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int64));
            value->type = RI_VALUE_INT64;
        }
        //else 
        if(value->type == RI_VALUE_INT32 && type == RI_VALUE_UINT64)
        {
            ri_int32 from;
            ri_uint64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int32));
            to = ri_int32_to_uint64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint64));
            value->type = RI_VALUE_UINT64;
        }
        else if(value->type == RI_VALUE_INT32 && type == RI_VALUE_LONG)
        {
            ri_int32 from;
            long to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int32));
            to = ri_int32_to_long(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_long));
            value->type = RI_VALUE_LONG;
        }
        else if(value->type == RI_VALUE_INT32 && type == RI_VALUE_ULONG)
        {
            ri_int32 from;
            ri_ulong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int32));
            to = ri_int32_to_ulong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ulong));
            value->type = RI_VALUE_ULONG;
        }
        else if(value->type == RI_VALUE_INT32 && type == RI_VALUE_LONGLONG)
        {
            ri_int32 from;
            ri_longlong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int32));
            to = ri_int32_to_longlong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_longlong));
            value->type = RI_VALUE_LONGLONG;
        }
        else if(value->type == RI_VALUE_INT32 && type == RI_VALUE_ULONGLONG)
        {
            ri_int32 from;
            ri_ulonglong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int32));
            to = ri_int32_to_ulonglong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ulonglong));
            value->type = RI_VALUE_ULONGLONG;
        }       
        else if(value->type == RI_VALUE_INT32 && type == RI_VALUE_SIZE)
        {
            ri_int32 from;
            size_t to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int32));
            to = ri_int32_to_size(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_size));
            value->type = RI_VALUE_SIZE;
        }
        else if(value->type == RI_VALUE_INT32 && type == RI_VALUE_SSIZE)
        {
            ri_int32 from;
            ri_ssize to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int32));
            to = ri_int32_to_ssize(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ssize));
            value->type = RI_VALUE_SSIZE;
        }
        else if(value->type == RI_VALUE_INT32 && type == RI_VALUE_FLOAT)
        {
            ri_int32 from;
            float to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int32));
            to = ri_int32_to_float(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float));
            value->type = RI_VALUE_FLOAT;
        }
        else if(value->type == RI_VALUE_INT32 && type == RI_VALUE_FLOAT32)
        {
            ri_int32 from;
            ri_float32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int32));
            to = ri_int32_to_float32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float32));
            value->type = RI_VALUE_FLOAT32;
        }
        else if(value->type == RI_VALUE_INT32 && type == RI_VALUE_FLOAT64)
        {
            ri_int32 from;
            ri_float64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int32));
            to = ri_int32_to_float64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float64));
            value->type = RI_VALUE_FLOAT64;
        }
        else if(value->type == RI_VALUE_INT32 && type == RI_VALUE_DOUBLE)
        {
            ri_int32 from;
            double to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int32));
            to = ri_int32_to_double(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_double));
            value->type = RI_VALUE_DOUBLE;
        }

        //else 
        if(value->type == RI_VALUE_UINT32 && type == RI_VALUE_INT)
        {
            ri_uint32   from;
            int  to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint32));
            to = ri_uint32_to_int(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int));
            value->type = RI_VALUE_INT;
        }
        else if(value->type == RI_VALUE_UINT32 && type == RI_VALUE_UINT)
        {
            ri_uint32   from;
            ri_uint  to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int32));
            to = ri_int32_to_uint(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint));
            value->type = RI_VALUE_UINT;
        }
        else if(value->type == RI_VALUE_UINT32 && type == RI_VALUE_INT8)
        {
            ri_uint32   from;
            ri_int8 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint32));
            to = ri_uint32_to_int8(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int8));
            value->type = RI_VALUE_INT8;
        }
        else if(value->type == RI_VALUE_UINT32 && type == RI_VALUE_UINT8)
        {
            ri_uint32 from;
            ri_uint8 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint32));
            to = ri_uint32_to_uint8(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint8));
            value->type = RI_VALUE_UINT8;
        }
        else if(value->type == RI_VALUE_UINT32 && type == RI_VALUE_INT16)
        {
            ri_uint32 from;
            ri_int16 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint32));
            to = ri_uint32_to_int16(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int16));
            value->type = RI_VALUE_INT16;
        }
        else if(value->type == RI_VALUE_UINT32 && type == RI_VALUE_UINT16)
        {
            ri_uint32 from;
            ri_uint16 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint32));
            to = ri_uint32_to_uint16(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint16));
            value->type = RI_VALUE_UINT16;
        }
        else if(value->type == RI_VALUE_UINT32 && type == RI_VALUE_INT32)
        {
            ri_uint32 from;
            ri_int32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint32));
            to = ri_uint32_to_int32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int32));
            value->type = RI_VALUE_INT32;
        }
        else if(value->type == RI_VALUE_UINT32 && type == RI_VALUE_INT64)
        {
            ri_uint32 from;
            ri_int64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint32));
            to = ri_uint32_to_int64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int64));
            value->type = RI_VALUE_INT64;
        }
        else if(value->type == RI_VALUE_UINT32 && type == RI_VALUE_UINT64)
        {
            ri_uint32 from;
            ri_uint64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint32));
            to = ri_uint32_to_uint64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint64));
            value->type = RI_VALUE_UINT64;
        }
        else if(value->type == RI_VALUE_UINT32 && type == RI_VALUE_LONG)
        {
            ri_uint32 from;
            long to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint32));
            to = ri_uint32_to_long(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_long));
            value->type = RI_VALUE_LONG;
        }
        else if(value->type == RI_VALUE_UINT32 && type == RI_VALUE_ULONG)
        {
            ri_uint32 from;
            ri_ulong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint32));
            to = ri_uint32_to_ulong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ulong));
            value->type = RI_VALUE_ULONG;
        }
        else if(value->type == RI_VALUE_UINT32 && type == RI_VALUE_LONGLONG)
        {
            ri_uint32 from;
            ri_longlong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint32));
            to = ri_uint32_to_longlong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_longlong));
            value->type = RI_VALUE_LONGLONG;
        }
        else if(value->type == RI_VALUE_UINT32 && type == RI_VALUE_ULONGLONG)
        {
            ri_uint32 from;
            ri_ulonglong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint32));
            to = ri_uint32_to_ulonglong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ulonglong));
            value->type = RI_VALUE_ULONGLONG;
        }         
        else if(value->type == RI_VALUE_UINT32 && type == RI_VALUE_SIZE)
        {
            ri_uint32 from;
            size_t to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint32));
            to = ri_uint32_to_size(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_size));
            value->type = RI_VALUE_SIZE;
        }
        else if(value->type == RI_VALUE_UINT32 && type == RI_VALUE_SSIZE)
        {
            ri_uint32 from;
            ri_ssize to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint32));
            to = ri_uint32_to_ssize(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ssize));
            value->type = RI_VALUE_SSIZE;
        }
        else if(value->type == RI_VALUE_UINT32 && type == RI_VALUE_FLOAT)
        {
            ri_uint32 from;
            float to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint32));
            to = ri_uint32_to_float(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float));
            value->type = RI_VALUE_FLOAT;
        }
        else if(value->type == RI_VALUE_UINT32 && type == RI_VALUE_FLOAT32)
        {
            ri_uint32 from;
            ri_float32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint32));
            to = ri_uint32_to_float32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float32));
            value->type = RI_VALUE_FLOAT32;
        }
        else if(value->type == RI_VALUE_UINT32 && type == RI_VALUE_FLOAT64)
        {
            ri_uint32 from;
            ri_float64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint32));
            to = ri_uint32_to_float64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float64));
            value->type = RI_VALUE_FLOAT64;
        }
        else if(value->type == RI_VALUE_UINT32 && type == RI_VALUE_DOUBLE)
        {
            ri_uint32 from;
            double to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint32));
            to = ri_uint32_to_double(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_double));
            value->type = RI_VALUE_DOUBLE;
        }









        //else 
        if(value->type == RI_VALUE_INT64 && type == RI_VALUE_INT)
        {
            ri_int64   from;
            int  to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int64));
            to = ri_int64_to_int(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int));
            value->type = RI_VALUE_INT;
        }
        else if(value->type == RI_VALUE_INT64 && type == RI_VALUE_UINT)
        {
            ri_int64   from;
            ri_uint  to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int64));
            to = ri_int64_to_uint(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint));
            value->type = RI_VALUE_UINT;
        }
        else if(value->type == RI_VALUE_INT64 && type == RI_VALUE_INT8)
        {
            ri_int64   from;
            ri_int8 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int64));
            to = ri_int64_to_int8(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int8));
            value->type = RI_VALUE_INT8;
        }
        else if(value->type == RI_VALUE_INT64 && type == RI_VALUE_UINT8)
        {
            ri_int64 from;
            ri_uint8 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int64));
            to = ri_int64_to_uint8(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint8));
            value->type = RI_VALUE_UINT8;
        }
        else if(value->type == RI_VALUE_INT64 && type == RI_VALUE_INT16)
        {
            ri_int64 from;
            ri_int16 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int64));
            to = ri_int64_to_int16(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int16));
            value->type = RI_VALUE_INT16;
        }
        else if(value->type == RI_VALUE_INT64 && type == RI_VALUE_UINT16)
        {
            ri_int64 from;
            ri_uint16 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int64));
            to = ri_int64_to_uint16(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint16));
            value->type = RI_VALUE_UINT16;
        }
        else if(value->type == RI_VALUE_INT64 && type == RI_VALUE_INT32)
        {
            ri_int64 from;
            ri_int32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int64));
            to = ri_int64_to_int32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int32));
            value->type = RI_VALUE_INT32;
        }
        else if(value->type == RI_VALUE_INT64 && type == RI_VALUE_UINT32)
        {
            ri_int64 from;
            ri_uint32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int64));
            to = ri_int64_to_uint32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint32));
            value->type = RI_VALUE_UINT32;
        }
        else if(value->type == RI_VALUE_INT64 && type == RI_VALUE_UINT64)
        {
            ri_int64 from;
            ri_uint64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int64));
            to = ri_int64_to_uint64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint64));
            value->type = RI_VALUE_UINT64;
        }
        else if(value->type == RI_VALUE_INT64 && type == RI_VALUE_LONG)
        {
            ri_int64 from;
            long to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int64));
            to = ri_int64_to_long(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_long));
            value->type = RI_VALUE_LONG;
        }
        else if(value->type == RI_VALUE_INT64 && type == RI_VALUE_ULONG)
        {
            ri_int64 from;
            ri_ulong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int64));
            to = ri_int64_to_ulong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ulong));
            value->type = RI_VALUE_ULONG;
        }
        else if(value->type == RI_VALUE_INT64 && type == RI_VALUE_LONGLONG)
        {
            ri_int64 from;
            ri_longlong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int64));
            to = ri_int64_to_longlong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_longlong));
            value->type = RI_VALUE_LONGLONG;
        }
        else if(value->type == RI_VALUE_INT64 && type == RI_VALUE_ULONGLONG)
        {
            ri_int64 from;
            ri_ulonglong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int64));
            to = ri_int64_to_ulonglong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ulonglong));
            value->type = RI_VALUE_ULONGLONG;
        }          
        else if(value->type == RI_VALUE_INT64 && type == RI_VALUE_SIZE)
        {
            ri_int64 from;
            size_t to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int64));
            to = ri_int64_to_size(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_size));
            value->type = RI_VALUE_SIZE;
        }
        else if(value->type == RI_VALUE_INT64 && type == RI_VALUE_SSIZE)
        {
            ri_int64 from;
            ri_ssize to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int64));
            to = ri_int64_to_ssize(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ssize));
            value->type = RI_VALUE_SSIZE;
        }
        else if(value->type == RI_VALUE_INT64 && type == RI_VALUE_FLOAT)
        {
            ri_int64 from;
            float to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int64));
            to = ri_int64_to_float(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float));
            value->type = RI_VALUE_FLOAT;
        }
        else if(value->type == RI_VALUE_INT64 && type == RI_VALUE_FLOAT32)
        {
            ri_int64 from;
            ri_float32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int64));
            to = ri_int64_to_float32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float32));
            value->type = RI_VALUE_FLOAT32;
        }
        else if(value->type == RI_VALUE_INT64 && type == RI_VALUE_FLOAT64)
        {
            ri_int64 from;
            ri_float64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int64));
            to = ri_int64_to_float64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float64));
            value->type = RI_VALUE_FLOAT64;
        }
        else if(value->type == RI_VALUE_INT64 && type == RI_VALUE_DOUBLE)
        {
            ri_int64 from;
            double to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_int64));
            to = ri_int64_to_double(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_double));
            value->type = RI_VALUE_DOUBLE;
        }









        //else 
        if(value->type == RI_VALUE_UINT64 && type == RI_VALUE_INT)
        {
            ri_uint64   from;
            int  to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint64));
            to = ri_uint64_to_int(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int));
            value->type = RI_VALUE_INT;
        }
        else if(value->type == RI_VALUE_UINT64 && type == RI_VALUE_UINT)
        {
            ri_uint64   from;
            ri_uint  to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint64));
            to = ri_uint64_to_uint(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint));
            value->type = RI_VALUE_UINT;
        }
        else if(value->type == RI_VALUE_UINT64 && type == RI_VALUE_INT8)
        {
            ri_uint64   from;
            ri_int8 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint64));
            to = ri_uint64_to_int8(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int8));
            value->type = RI_VALUE_INT8;
        }
        else if(value->type == RI_VALUE_UINT64 && type == RI_VALUE_UINT8)
        {
            ri_uint64 from;
            ri_uint8 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint64));
            to = ri_uint64_to_uint8(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint8));
            value->type = RI_VALUE_UINT8;
        }
        else if(value->type == RI_VALUE_UINT64 && type == RI_VALUE_INT16)
        {
            ri_uint64 from;
            ri_int16 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint64));
            to = ri_uint64_to_int16(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int16));
            value->type = RI_VALUE_INT16;
        }
        else if(value->type == RI_VALUE_UINT64 && type == RI_VALUE_UINT16)
        {
            ri_uint64 from;
            ri_uint16 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint64));
            to = ri_uint64_to_uint16(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint16));
            value->type = RI_VALUE_UINT16;
        }
        else if(value->type == RI_VALUE_UINT64 && type == RI_VALUE_INT32)
        {
            ri_uint64 from;
            ri_int32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint64));
            to = ri_uint64_to_int32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int32));
            value->type = RI_VALUE_INT32;
        }
        else if(value->type == RI_VALUE_UINT64 && type == RI_VALUE_UINT32)
        {
            ri_uint64 from;
            ri_uint32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint64));
            to = ri_uint64_to_uint32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint32));
            value->type = RI_VALUE_UINT32;
        }
        else if(value->type == RI_VALUE_UINT64 && type == RI_VALUE_INT64)
        {
            ri_uint64 from;
            ri_int64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint64));
            to = ri_uint64_to_int64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int64));
            value->type = RI_VALUE_INT64;
        }
        else if(value->type == RI_VALUE_UINT64 && type == RI_VALUE_LONG)
        {
            ri_uint64 from;
            long to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint64));
            to = ri_uint64_to_long(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_long));
            value->type = RI_VALUE_LONG;
        }
        else if(value->type == RI_VALUE_UINT64 && type == RI_VALUE_ULONG)
        {
            ri_uint64 from;
            ri_ulong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint64));
            to = ri_uint64_to_ulong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ulong));
            value->type = RI_VALUE_ULONG;
        }
        else if(value->type == RI_VALUE_UINT64 && type == RI_VALUE_LONGLONG)
        {
            ri_uint64 from;
            ri_longlong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint64));
            to = ri_uint64_to_longlong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_longlong));
            value->type = RI_VALUE_LONGLONG;
        }
        else if(value->type == RI_VALUE_UINT64 && type == RI_VALUE_ULONGLONG)
        {
            ri_uint64 from;
            ri_ulonglong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint64));
            to = ri_uint64_to_ulonglong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ulonglong));
            value->type = RI_VALUE_ULONGLONG;
        }             
        else if(value->type == RI_VALUE_UINT64 && type == RI_VALUE_SIZE)
        {
            ri_uint64 from;
            size_t to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint64));
            to = ri_uint64_to_size(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_size));
            value->type = RI_VALUE_SIZE;
        }
        else if(value->type == RI_VALUE_UINT64 && type == RI_VALUE_SSIZE)
        {
            ri_uint64 from;
            ri_ssize to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint64));
            to = ri_uint64_to_ssize(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ssize));
            value->type = RI_VALUE_SSIZE;
        }
        else if(value->type == RI_VALUE_UINT64 && type == RI_VALUE_FLOAT)
        {
            ri_uint64 from;
            float to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint64));
            to = ri_uint64_to_float(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float));
            value->type = RI_VALUE_FLOAT;
        }
        else if(value->type == RI_VALUE_UINT64 && type == RI_VALUE_FLOAT32)
        {
            ri_uint64 from;
            ri_float32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint64));
            to = ri_uint64_to_float32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float32));
            value->type = RI_VALUE_FLOAT32;
        }
        else if(value->type == RI_VALUE_UINT64 && type == RI_VALUE_FLOAT64)
        {
            ri_uint64 from;
            ri_float64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint64));
            to = ri_uint64_to_float64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float64));
            value->type = RI_VALUE_FLOAT64;
        }
        else if(value->type == RI_VALUE_UINT64 && type == RI_VALUE_DOUBLE)
        {
            ri_uint64 from;
            double to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_uint64));
            to = ri_uint64_to_double(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_double));
            value->type = RI_VALUE_DOUBLE;
        }




        //else 
        if(value->type == RI_VALUE_LONG && type == RI_VALUE_INT)
        {
            long   from;
            int  to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_long));
            to = ri_long_to_int(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int));
            value->type = RI_VALUE_INT;
        }
        else if(value->type == RI_VALUE_LONG && type == RI_VALUE_UINT)
        {
            long   from;
            ri_uint  to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_long));
            to = ri_long_to_uint(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint));
            value->type = RI_VALUE_UINT;
        }
        else if(value->type == RI_VALUE_LONG && type == RI_VALUE_INT8)
        {
            long   from;
            ri_int8 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_long));
            to = ri_long_to_int8(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int8));
            value->type = RI_VALUE_INT8;
        }
        else if(value->type == RI_VALUE_LONG && type == RI_VALUE_UINT8)
        {
            long from;
            ri_uint8 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_long));
            to = ri_long_to_uint8(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint8));
            value->type = RI_VALUE_UINT8;
        }
        else if(value->type == RI_VALUE_LONG && type == RI_VALUE_INT16)
        {
            long from;
            ri_int16 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_long));
            to = ri_long_to_int16(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int16));
            value->type = RI_VALUE_INT16;
        }
        else if(value->type == RI_VALUE_LONG && type == RI_VALUE_UINT16)
        {
            long from;
            ri_uint16 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_long));
            to = ri_long_to_uint16(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint16));
            value->type = RI_VALUE_UINT16;
        }
        else if(value->type == RI_VALUE_LONG && type == RI_VALUE_INT32)
        {
            long from;
            ri_int32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_long));
            to = ri_long_to_int32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int32));
            value->type = RI_VALUE_INT32;
        }
        else if(value->type == RI_VALUE_LONG && type == RI_VALUE_UINT32)
        {
            long from;
            ri_uint32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_long));
            to = ri_long_to_uint32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint32));
            value->type = RI_VALUE_UINT32;
        }
        else if(value->type == RI_VALUE_LONG && type == RI_VALUE_INT64)
        {
            long from;
            ri_int64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_long));
            to = ri_long_to_int64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int64));
            value->type = RI_VALUE_INT64;
        }
        else if(value->type == RI_VALUE_LONG && type == RI_VALUE_UINT64)
        {
            long from;
            ri_uint64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_long));
            to = ri_long_to_uint64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint64));
            value->type = RI_VALUE_UINT64;
        }
        else if(value->type == RI_VALUE_LONG && type == RI_VALUE_ULONG)
        {
            long from;
            ri_ulong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_long));
            to = ri_long_to_ulong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ulong));
            value->type = RI_VALUE_ULONG;
        }
        else if(value->type == RI_VALUE_LONG && type == RI_VALUE_LONGLONG)
        {
            long from;
            ri_longlong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_long));
            to = ri_long_to_longlong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_longlong));
            value->type = RI_VALUE_LONGLONG;
        }
        else if(value->type == RI_VALUE_LONG && type == RI_VALUE_ULONGLONG)
        {
            long from;
            ri_ulonglong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_long));
            to = ri_long_to_ulonglong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ulonglong));
            value->type = RI_VALUE_ULONGLONG;
        }             
        else if(value->type == RI_VALUE_LONG && type == RI_VALUE_SIZE)
        {
            long from;
            size_t to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_long));
            to = ri_long_to_size(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_size));
            value->type = RI_VALUE_SIZE;
        }
        else if(value->type == RI_VALUE_LONG && type == RI_VALUE_SSIZE)
        {
            long from;
            ri_ssize to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_long));
            to = ri_long_to_ssize(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ssize));
            value->type = RI_VALUE_SSIZE;
        }
        else if(value->type == RI_VALUE_LONG && type == RI_VALUE_FLOAT)
        {
            long from;
            float to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_long));
            to = ri_long_to_float(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float));
            value->type = RI_VALUE_FLOAT;
        }
        else if(value->type == RI_VALUE_LONG && type == RI_VALUE_FLOAT32)
        {
            long from;
            ri_float32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_long));
            to = ri_long_to_float32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float32));
            value->type = RI_VALUE_FLOAT32;
        }
        else if(value->type == RI_VALUE_LONG && type == RI_VALUE_FLOAT64)
        {
            long from;
            ri_float64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_long));
            to = ri_long_to_float64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float64));
            value->type = RI_VALUE_FLOAT64;
        }
        else if(value->type == RI_VALUE_LONG && type == RI_VALUE_DOUBLE)
        {
            long from;
            double to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_long));
            to = ri_long_to_double(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_double));
            value->type = RI_VALUE_DOUBLE;
        }







        //else 
        if(value->type == RI_VALUE_ULONG && type == RI_VALUE_INT)
        {
            ri_ulong   from;
            int  to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ulong));
            to = ri_ulong_to_int(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int));
            value->type = RI_VALUE_INT;
        }
        else if(value->type == RI_VALUE_ULONG && type == RI_VALUE_UINT)
        {
            ri_ulong   from;
            ri_uint  to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ulong));
            to = ri_ulong_to_uint(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint));
            value->type = RI_VALUE_UINT;
        }
        else if(value->type == RI_VALUE_ULONG && type == RI_VALUE_INT8)
        {
            ri_ulong   from;
            ri_int8 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ulong));
            to = ri_ulong_to_int8(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int8));
            value->type = RI_VALUE_INT8;
        }
        else if(value->type == RI_VALUE_ULONG && type == RI_VALUE_UINT8)
        {
            ri_ulong from;
            ri_uint8 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ulong));
            to = ri_ulong_to_uint8(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint8));
            value->type = RI_VALUE_UINT8;
        }
        else if(value->type == RI_VALUE_ULONG && type == RI_VALUE_INT16)
        {
            ri_ulong from;
            ri_int16 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ulong));
            to = ri_ulong_to_int16(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int16));
            value->type = RI_VALUE_INT16;
        }
        else if(value->type == RI_VALUE_ULONG && type == RI_VALUE_UINT16)
        {
            ri_ulong from;
            ri_uint16 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ulong));
            to = ri_ulong_to_uint16(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint16));
            value->type = RI_VALUE_UINT16;
        }
        else if(value->type == RI_VALUE_ULONG && type == RI_VALUE_INT32)
        {
            ri_ulong from;
            ri_int32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ulong));
            to = ri_ulong_to_int32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int32));
            value->type = RI_VALUE_INT32;
        }
        else if(value->type == RI_VALUE_ULONG && type == RI_VALUE_UINT32)
        {
            ri_ulong from;
            ri_uint32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ulong));
            to = ri_ulong_to_uint32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint32));
            value->type = RI_VALUE_UINT32;
        }
        else if(value->type == RI_VALUE_ULONG && type == RI_VALUE_INT64)
        {
            ri_ulong from;
            ri_int64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ulong));
            to = ri_ulong_to_int64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int64));
            value->type = RI_VALUE_INT64;
        }
        else if(value->type == RI_VALUE_ULONG && type == RI_VALUE_UINT64)
        {
            ri_ulong from;
            ri_uint64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ulong));
            to = ri_ulong_to_uint64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint64));
            value->type = RI_VALUE_UINT64;
        }
        else if(value->type == RI_VALUE_ULONG && type == RI_VALUE_LONG)
        {
            ri_ulong from;
            long to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ulong));
            to = ri_ulong_to_long(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_long));
            value->type = RI_VALUE_LONG;
        }
        else if(value->type == RI_VALUE_ULONG && type == RI_VALUE_LONGLONG)
        {
            ri_ulong from;
            ri_longlong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ulong));
            to = ri_ulong_to_longlong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_longlong));
            value->type = RI_VALUE_LONGLONG;
        }
        else if(value->type == RI_VALUE_ULONG && type == RI_VALUE_ULONGLONG)
        {
            ri_ulong from;
            ri_ulonglong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ulong));
            to = ri_ulong_to_ulonglong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ulonglong));
            value->type = RI_VALUE_ULONGLONG;
        }             
        else if(value->type == RI_VALUE_ULONG && type == RI_VALUE_SIZE)
        {
            ri_ulong from;
            size_t to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ulong));
            to = ri_ulong_to_size(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_size));
            value->type = RI_VALUE_SIZE;
        }
        else if(value->type == RI_VALUE_ULONG && type == RI_VALUE_SSIZE)
        {
            ri_ulong from;
            ri_ssize to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ulong));
            to = ri_ulong_to_ssize(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ssize));
            value->type = RI_VALUE_SSIZE;
        }
        else if(value->type == RI_VALUE_ULONG && type == RI_VALUE_FLOAT)
        {
            ri_ulong from;
            float to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ulong));
            to = ri_ulong_to_float(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float));
            value->type = RI_VALUE_FLOAT;
        }
        else if(value->type == RI_VALUE_ULONG && type == RI_VALUE_FLOAT32)
        {
            ri_ulong from;
            ri_float32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ulong));
            to = ri_ulong_to_float32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float32));
            value->type = RI_VALUE_FLOAT32;
        }
        else if(value->type == RI_VALUE_ULONG && type == RI_VALUE_FLOAT64)
        {
            ri_ulong from;
            ri_float64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ulong));
            to = ri_ulong_to_float64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float64));
            value->type = RI_VALUE_FLOAT64;
        }
        else if(value->type == RI_VALUE_ULONG && type == RI_VALUE_DOUBLE)
        {
            ri_ulong from;
            double to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ulong));
            to = ri_ulong_to_double(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_double));
            value->type = RI_VALUE_DOUBLE;
        }




        else if(value->type == RI_VALUE_LONGLONG && type == RI_VALUE_INT)
        {
            ri_longlong   from;
            int  to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_longlong));
            to = ri_longlong_to_int(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int));
            value->type = RI_VALUE_INT;
        }
        else if(value->type == RI_VALUE_LONGLONG && type == RI_VALUE_UINT)
        {
            ri_longlong   from;
            ri_uint  to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_longlong));
            to = ri_longlong_to_uint(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint));
            value->type = RI_VALUE_UINT;
        }
        else if(value->type == RI_VALUE_LONGLONG && type == RI_VALUE_INT8)
        {
            ri_longlong   from;
            ri_int8 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_longlong));
            to = ri_longlong_to_int8(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int8));
            value->type = RI_VALUE_INT8;
        }
        else if(value->type == RI_VALUE_LONGLONG && type == RI_VALUE_UINT8)
        {
            ri_longlong from;
            ri_uint8 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_longlong));
            to = ri_longlong_to_uint8(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint8));
            value->type = RI_VALUE_UINT8;
        }
        else if(value->type == RI_VALUE_LONGLONG && type == RI_VALUE_INT16)
        {
            ri_longlong from;
            ri_int16 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_longlong));
            to = ri_longlong_to_int16(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int16));
            value->type = RI_VALUE_INT16;
        }
        else if(value->type == RI_VALUE_LONGLONG && type == RI_VALUE_UINT16)
        {
            ri_longlong from;
            ri_uint16 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_longlong));
            to = ri_longlong_to_uint16(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint16));
            value->type = RI_VALUE_UINT16;
        }
        else if(value->type == RI_VALUE_LONGLONG && type == RI_VALUE_INT32)
        {
            ri_longlong from;
            ri_int32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_longlong));
            to = ri_longlong_to_int32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int32));
            value->type = RI_VALUE_INT32;
        }
        else if(value->type == RI_VALUE_LONGLONG && type == RI_VALUE_UINT32)
        {
            ri_longlong from;
            ri_uint32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_longlong));
            to = ri_longlong_to_uint32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint32));
            value->type = RI_VALUE_UINT32;
        }
        else if(value->type == RI_VALUE_LONGLONG && type == RI_VALUE_INT64)
        {
            ri_longlong from;
            ri_int64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_longlong));
            to = ri_longlong_to_int64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int64));
            value->type = RI_VALUE_INT64;
        }
        else if(value->type == RI_VALUE_LONGLONG && type == RI_VALUE_UINT64)
        {
            ri_longlong from;
            ri_uint64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_longlong));
            to = ri_longlong_to_uint64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint64));
            value->type = RI_VALUE_UINT64;
        }    
        else if(value->type == RI_VALUE_LONGLONG && type == RI_VALUE_LONG)
        {
            ri_longlong from;
            long to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_longlong));
            to = ri_longlong_to_long(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_long));
            value->type = RI_VALUE_LONG;
        }
        else if(value->type == RI_VALUE_LONGLONG && type == RI_VALUE_ULONG)
        {
            ri_longlong from;
            ri_ulong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_longlong));
            to = ri_longlong_to_ulong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ulong));
            value->type = RI_VALUE_ULONG;
        }
        else if(value->type == RI_VALUE_LONGLONG && type == RI_VALUE_ULONGLONG)
        {
            ri_longlong from;
            ri_ulonglong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_longlong));
            to = ri_longlong_to_ulonglong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ulonglong));
            value->type = RI_VALUE_ULONGLONG;
        }           
        else if(value->type == RI_VALUE_LONGLONG && type == RI_VALUE_SIZE)
        {
            ri_longlong from;
            size_t to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_longlong));
            to = ri_longlong_to_size(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_size));
            value->type = RI_VALUE_SIZE;
        }
        else if(value->type == RI_VALUE_LONGLONG && type == RI_VALUE_SSIZE)
        {
            ri_longlong from;
            ri_ssize to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_longlong));
            to = ri_longlong_to_ssize(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ssize));
            value->type = RI_VALUE_SSIZE;
        }
        else if(value->type == RI_VALUE_LONGLONG && type == RI_VALUE_FLOAT)
        {
            ri_longlong from;
            float to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_longlong));
            to = ri_longlong_to_float(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float));
            value->type = RI_VALUE_FLOAT;
        }
        else if(value->type == RI_VALUE_LONGLONG && type == RI_VALUE_FLOAT32)
        {
            ri_longlong from;
            ri_float32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_longlong));
            to = ri_longlong_to_float32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float32));
            value->type = RI_VALUE_FLOAT32;
        }
        else if(value->type == RI_VALUE_LONGLONG && type == RI_VALUE_FLOAT64)
        {
            ri_longlong from;
            ri_float64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_longlong));
            to = ri_longlong_to_float64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float64));
            value->type = RI_VALUE_FLOAT64;
        }
        else if(value->type == RI_VALUE_LONGLONG && type == RI_VALUE_DOUBLE)
        {
            ri_longlong from;
            double to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_longlong));
            to = ri_longlong_to_double(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_double));
            value->type = RI_VALUE_DOUBLE;
        }



        else if(value->type == RI_VALUE_ULONGLONG && type == RI_VALUE_INT)
        {
            ri_ulonglong   from;
            int  to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ulonglong));
            to = ri_ulonglong_to_int(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int));
            value->type = RI_VALUE_INT;
        }
        else if(value->type == RI_VALUE_ULONGLONG && type == RI_VALUE_UINT)
        {
            ri_ulonglong   from;
            ri_uint  to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ulonglong));
            to = ri_ulonglong_to_uint(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint));
            value->type = RI_VALUE_UINT;
        }
        else if(value->type == RI_VALUE_ULONGLONG && type == RI_VALUE_INT8)
        {
            ri_ulonglong   from;
            ri_int8 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ulonglong));
            to = ri_ulonglong_to_int8(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int8));
            value->type = RI_VALUE_INT8;
        }
        else if(value->type == RI_VALUE_ULONGLONG && type == RI_VALUE_UINT8)
        {
            ri_ulonglong from;
            ri_uint8 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ulonglong));
            to = ri_ulonglong_to_uint8(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint8));
            value->type = RI_VALUE_UINT8;
        }
        else if(value->type == RI_VALUE_ULONGLONG && type == RI_VALUE_INT16)
        {
            ri_ulonglong from;
            ri_int16 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ulonglong));
            to = ri_ulonglong_to_int16(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int16));
            value->type = RI_VALUE_INT16;
        }
        else if(value->type == RI_VALUE_ULONGLONG && type == RI_VALUE_UINT16)
        {
            ri_ulonglong from;
            ri_uint16 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ulonglong));
            to = ri_ulonglong_to_uint16(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint16));
            value->type = RI_VALUE_UINT16;
        }
        else if(value->type == RI_VALUE_ULONGLONG && type == RI_VALUE_INT32)
        {
            ri_ulonglong from;
            ri_int32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ulonglong));
            to = ri_ulonglong_to_int32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int32));
            value->type = RI_VALUE_INT32;
        }
        else if(value->type == RI_VALUE_ULONGLONG && type == RI_VALUE_UINT32)
        {
            ri_ulonglong from;
            ri_uint32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ulonglong));
            to = ri_ulonglong_to_uint32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint32));
            value->type = RI_VALUE_UINT32;
        }
        else if(value->type == RI_VALUE_ULONGLONG && type == RI_VALUE_INT64)
        {
            ri_ulonglong from;
            ri_int64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ulonglong));
            to = ri_ulonglong_to_int64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int64));
            value->type = RI_VALUE_INT64;
        }
        else if(value->type == RI_VALUE_ULONGLONG && type == RI_VALUE_UINT64)
        {
            ri_ulonglong from;
            ri_uint64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ulonglong));
            to = ri_ulonglong_to_uint64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint64));
            value->type = RI_VALUE_UINT64;
        }    
        else if(value->type == RI_VALUE_ULONGLONG && type == RI_VALUE_LONG)
        {
            ri_ulonglong from;
            long to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ulonglong));
            to = ri_ulonglong_to_long(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_long));
            value->type = RI_VALUE_LONG;
        }
        else if(value->type == RI_VALUE_ULONGLONG && type == RI_VALUE_ULONG)
        {
            ri_ulonglong from;
            ri_ulong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ulonglong));
            to = ri_ulonglong_to_ulong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ulong));
            value->type = RI_VALUE_ULONG;
        }
        else if(value->type == RI_VALUE_ULONGLONG && type == RI_VALUE_ULONGLONG)
        {
            ri_ulonglong from;
            ri_longlong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ulonglong));
            to = ri_ulonglong_to_longlong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ulonglong));
            value->type = RI_VALUE_ULONGLONG;
        }           
        else if(value->type == RI_VALUE_ULONGLONG && type == RI_VALUE_SIZE)
        {
            ri_ulonglong from;
            size_t to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ulonglong));
            to = ri_ulonglong_to_size(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_size));
            value->type = RI_VALUE_SIZE;
        }
        else if(value->type == RI_VALUE_ULONGLONG && type == RI_VALUE_SSIZE)
        {
            ri_ulonglong from;
            ri_ssize to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ulonglong));
            to = ri_ulonglong_to_ssize(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ssize));
            value->type = RI_VALUE_SSIZE;
        }
        else if(value->type == RI_VALUE_ULONGLONG && type == RI_VALUE_FLOAT)
        {
            ri_ulonglong from;
            float to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ulonglong));
            to = ri_ulonglong_to_float(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float));
            value->type = RI_VALUE_FLOAT;
        }
        else if(value->type == RI_VALUE_ULONGLONG && type == RI_VALUE_FLOAT32)
        {
            ri_ulonglong from;
            ri_float32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ulonglong));
            to = ri_ulonglong_to_float32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float32));
            value->type = RI_VALUE_FLOAT32;
        }
        else if(value->type == RI_VALUE_ULONGLONG && type == RI_VALUE_FLOAT64)
        {
            ri_ulonglong from;
            ri_float64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ulonglong));
            to = ri_ulonglong_to_float64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float64));
            value->type = RI_VALUE_FLOAT64;
        }
        else if(value->type == RI_VALUE_ULONGLONG && type == RI_VALUE_DOUBLE)
        {
            ri_ulonglong from;
            double to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ulonglong));
            to = ri_ulonglong_to_double(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_double));
            value->type = RI_VALUE_DOUBLE;
        }


        else if(value->type == RI_VALUE_SIZE && type == RI_VALUE_INT)
        {
            size_t   from;
            int  to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_size));
            to = ri_size_to_int(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int));
            value->type = RI_VALUE_INT;
        }
        else if(value->type == RI_VALUE_SIZE && type == RI_VALUE_UINT)
        {
            size_t   from;
            ri_uint  to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_size));
            to = ri_size_to_uint(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint));
            value->type = RI_VALUE_UINT;
        }
        else if(value->type == RI_VALUE_SIZE && type == RI_VALUE_INT8)
        {
            size_t   from;
            ri_int8 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_size));
            to = ri_size_to_int8(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int8));
            value->type = RI_VALUE_INT8;
        }
        else if(value->type == RI_VALUE_SIZE && type == RI_VALUE_UINT8)
        {
            size_t from;
            ri_uint8 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_size));
            to = ri_size_to_uint8(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint8));
            value->type = RI_VALUE_UINT8;
        }
        else if(value->type == RI_VALUE_SIZE && type == RI_VALUE_INT16)
        {
            size_t from;
            ri_int16 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_size));
            to = ri_size_to_int16(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int16));
            value->type = RI_VALUE_INT16;
        }
        else if(value->type == RI_VALUE_SIZE && type == RI_VALUE_UINT16)
        {
            size_t from;
            ri_uint16 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_size));
            to = ri_size_to_uint16(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint16));
            value->type = RI_VALUE_UINT16;
        }
        else if(value->type == RI_VALUE_SIZE && type == RI_VALUE_INT32)
        {
            size_t from;
            ri_int32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_size));
            to = ri_size_to_int32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int32));
            value->type = RI_VALUE_INT32;
        }
        else if(value->type == RI_VALUE_SIZE && type == RI_VALUE_UINT32)
        {
            size_t from;
            ri_uint32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_size));
            to = ri_size_to_uint32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint32));
            value->type = RI_VALUE_UINT32;
        }
        else if(value->type == RI_VALUE_SIZE && type == RI_VALUE_INT64)
        {
            size_t from;
            ri_int64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_size));
            to = ri_size_to_int64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int64));
            value->type = RI_VALUE_INT64;
        }
        else if(value->type == RI_VALUE_SIZE && type == RI_VALUE_UINT64)
        {
            size_t from;
            ri_uint64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_size));
            to = ri_size_to_uint64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint64));
            value->type = RI_VALUE_UINT64;
        }
        else if(value->type == RI_VALUE_SIZE && type == RI_VALUE_LONG)
        {
            size_t from;
            long to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_size));
            to = ri_size_to_long(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_long));
            value->type = RI_VALUE_LONG;
        }
        else if(value->type == RI_VALUE_SIZE && type == RI_VALUE_ULONG)
        {
            size_t from;
            ri_ulong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_size));
            to = ri_size_to_ulong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ulong));
            value->type = RI_VALUE_ULONG;
        }
        else if(value->type == RI_VALUE_SIZE && type == RI_VALUE_LONGLONG)
        {
            size_t from;
            ri_longlong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_size));
            to = ri_size_to_longlong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_longlong));
            value->type = RI_VALUE_LONGLONG;
        }
        else if(value->type == RI_VALUE_SIZE && type == RI_VALUE_ULONGLONG)
        {
            size_t from;
            ri_ulonglong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_size));
            to = ri_size_to_ulonglong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ulonglong));
            value->type = RI_VALUE_ULONGLONG;
        }          
        else if(value->type == RI_VALUE_SIZE && type == RI_VALUE_SSIZE)
        {
            size_t from;
            ri_ssize to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_size));
            to = ri_size_to_ssize(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ssize));
            value->type = RI_VALUE_SSIZE;
        }
        else if(value->type == RI_VALUE_SIZE && type == RI_VALUE_FLOAT)
        {
            size_t from;
            float to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_size));
            to = ri_size_to_float(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float));
            value->type = RI_VALUE_FLOAT;
        }
        else if(value->type == RI_VALUE_SIZE && type == RI_VALUE_FLOAT32)
        {
            size_t from;
            ri_float32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_size));
            to = ri_size_to_float32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float32));
            value->type = RI_VALUE_FLOAT32;
        }
        else if(value->type == RI_VALUE_SIZE && type == RI_VALUE_FLOAT64)
        {
            size_t from;
            ri_float64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_size));
            to = ri_size_to_float64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float64));
            value->type = RI_VALUE_FLOAT64;
        }
        else if(value->type == RI_VALUE_SIZE && type == RI_VALUE_DOUBLE)
        {
            size_t from;
            double to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_size));
            to = ri_size_to_double(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_double));
            value->type = RI_VALUE_DOUBLE;
        }







        else if(value->type == RI_VALUE_SSIZE && type == RI_VALUE_INT)
        {
            ri_ssize   from;
            int  to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ssize));
            to = ri_ssize_to_int(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int));
            value->type = RI_VALUE_INT;
        }
        else if(value->type == RI_VALUE_SSIZE && type == RI_VALUE_UINT)
        {
            ri_ssize   from;
            ri_uint  to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ssize));
            to = ri_ssize_to_uint(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint));
            value->type = RI_VALUE_UINT;
        }
        else if(value->type == RI_VALUE_SSIZE && type == RI_VALUE_INT8)
        {
            ri_ssize   from;
            ri_int8 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ssize));
            to = ri_ssize_to_int8(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int8));
            value->type = RI_VALUE_INT8;
        }
        else if(value->type == RI_VALUE_SSIZE && type == RI_VALUE_UINT8)
        {
            ri_ssize from;
            ri_uint8 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ssize));
            to = ri_ssize_to_uint8(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint8));
            value->type = RI_VALUE_UINT8;
        }
        else if(value->type == RI_VALUE_SSIZE && type == RI_VALUE_INT16)
        {
            ri_ssize from;
            ri_int16 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ssize));
            to = ri_ssize_to_int16(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int16));
            value->type = RI_VALUE_INT16;
        }
        else if(value->type == RI_VALUE_SSIZE && type == RI_VALUE_UINT16)
        {
            ri_ssize from;
            ri_uint16 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ssize));
            to = ri_ssize_to_uint16(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint16));
            value->type = RI_VALUE_UINT16;
        }
        else if(value->type == RI_VALUE_SSIZE && type == RI_VALUE_INT32)
        {
            ri_ssize from;
            ri_int32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ssize));
            to = ri_ssize_to_int32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int32));
            value->type = RI_VALUE_INT32;
        }
        else if(value->type == RI_VALUE_SSIZE && type == RI_VALUE_UINT32)
        {
            ri_ssize from;
            ri_uint32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ssize));
            to = ri_size_to_uint32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint32));
            value->type = RI_VALUE_UINT32;
        }
        else if(value->type == RI_VALUE_SSIZE && type == RI_VALUE_INT64)
        {
            ri_ssize from;
            ri_int64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ssize));
            to = ri_ssize_to_int64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int64));
            value->type = RI_VALUE_INT64;
        }
        else if(value->type == RI_VALUE_SSIZE && type == RI_VALUE_UINT64)
        {
            ri_ssize from;
            ri_uint64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ssize));
            to = ri_ssize_to_uint64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint64));
            value->type = RI_VALUE_UINT64;
        }
        else if(value->type == RI_VALUE_SSIZE && type == RI_VALUE_LONG)
        {
            ri_ssize from;
            long to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ssize));
            to = ri_ssize_to_long(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_long));
            value->type = RI_VALUE_LONG;
        }
        else if(value->type == RI_VALUE_SSIZE && type == RI_VALUE_ULONG)
        {
            ri_ssize from;
            ri_ulong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ssize));
            to = ri_ssize_to_ulong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ulong));
            value->type = RI_VALUE_ULONG;
        }
        else if(value->type == RI_VALUE_SSIZE && type == RI_VALUE_LONGLONG)
        {
            ri_ssize from;
            ri_longlong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ssize));
            to = ri_ssize_to_longlong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_longlong));
            value->type = RI_VALUE_LONGLONG;
        }
        else if(value->type == RI_VALUE_SSIZE && type == RI_VALUE_ULONGLONG)
        {
            ri_ssize from;
            ri_ulonglong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ssize));
            to = ri_ssize_to_ulonglong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ulonglong));
            value->type = RI_VALUE_ULONGLONG;
        } 
        else if(value->type == RI_VALUE_SSIZE && type == RI_VALUE_SIZE)
        {
            ri_ssize from;
            size_t to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ssize));
            to = ri_ssize_to_size(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_size));
            value->type = RI_VALUE_SIZE;
        }
        else if(value->type == RI_VALUE_SSIZE && type == RI_VALUE_FLOAT)
        {
            ri_ssize from;
            float to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ssize));
            to = ri_ssize_to_float(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float));
            value->type = RI_VALUE_FLOAT;
        }
        else if(value->type == RI_VALUE_SSIZE && type == RI_VALUE_FLOAT32)
        {
            ri_ssize from;
            ri_float32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ssize));
            to = ri_ssize_to_float32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float32));
            value->type = RI_VALUE_FLOAT32;
        }
        else if(value->type == RI_VALUE_SSIZE && type == RI_VALUE_FLOAT64)
        {
            ri_ssize from;
            ri_float64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ssize));
            to = ri_ssize_to_float64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float64));
            value->type = RI_VALUE_FLOAT64;
        }
        else if(value->type == RI_VALUE_SSIZE && type == RI_VALUE_DOUBLE)
        {
            ri_ssize from;
            double to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_ssize));
            to = ri_ssize_to_double(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_double));
            value->type = RI_VALUE_DOUBLE;
        }







        else if(value->type == RI_VALUE_FLOAT && type == RI_VALUE_INT)
        {
            float   from;
            int  to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float));
            to = ri_float_to_int(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int));
            value->type = RI_VALUE_INT;
        }
        else if(value->type == RI_VALUE_FLOAT && type == RI_VALUE_UINT)
        {
            float   from;
            ri_uint  to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float));
            to = ri_float_to_uint(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint));
            value->type = RI_VALUE_UINT;
        }
        else if(value->type == RI_VALUE_FLOAT && type == RI_VALUE_INT8)
        {
            float   from;
            ri_int8 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float));
            to = ri_float_to_int8(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int8));
            value->type = RI_VALUE_INT8;
        }
        else if(value->type == RI_VALUE_FLOAT && type == RI_VALUE_UINT8)
        {
            float from;
            ri_uint8 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float));
            to = ri_float_to_uint8(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint8));
            value->type = RI_VALUE_UINT8;
        }
        else if(value->type == RI_VALUE_FLOAT && type == RI_VALUE_INT16)
        {
            float from;
            ri_int16 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float));
            to = ri_float_to_int16(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int16));
            value->type = RI_VALUE_INT16;
        }
        else if(value->type == RI_VALUE_FLOAT && type == RI_VALUE_UINT16)
        {
            float from;
            ri_uint16 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float));
            to = ri_float_to_uint16(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint16));
            value->type = RI_VALUE_UINT16;
        }
        else if(value->type == RI_VALUE_FLOAT && type == RI_VALUE_INT32)
        {
            float from;
            ri_int32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float));
            to = ri_float_to_int32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int32));
            value->type = RI_VALUE_INT32;
        }
        else if(value->type == RI_VALUE_FLOAT && type == RI_VALUE_UINT32)
        {
            float from;
            ri_uint32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float));
            to = ri_float_to_uint32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint32));
            value->type = RI_VALUE_UINT32;
        }
        else if(value->type == RI_VALUE_FLOAT && type == RI_VALUE_INT64)
        {
            float from;
            ri_int64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float));
            to = ri_float_to_int64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int64));
            value->type = RI_VALUE_INT64;
        }
        else if(value->type == RI_VALUE_FLOAT && type == RI_VALUE_UINT64)
        {
            float from;
            ri_uint64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float));
            to = ri_float_to_uint64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint64));
            value->type = RI_VALUE_UINT64;
        }
        else if(value->type == RI_VALUE_FLOAT && type == RI_VALUE_LONG)
        {
            float from;
            long to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float));
            to = ri_float_to_long(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_long));
            value->type = RI_VALUE_LONG;
        }
        else if(value->type == RI_VALUE_FLOAT && type == RI_VALUE_ULONG)
        {
            float from;
            ri_ulong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float));
            to = ri_float_to_ulong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ulong));
            value->type = RI_VALUE_ULONG;
        }
        else if(value->type == RI_VALUE_FLOAT && type == RI_VALUE_LONGLONG)
        {
            float from;
            ri_longlong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float));
            to = ri_float_to_longlong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_longlong));
            value->type = RI_VALUE_LONGLONG;
        }
        else if(value->type == RI_VALUE_FLOAT && type == RI_VALUE_ULONGLONG)
        {
            float from;
            ri_ulonglong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float));
            to = ri_float_to_ulonglong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ulonglong));
            value->type = RI_VALUE_ULONGLONG;
        } 
        else if(value->type == RI_VALUE_FLOAT && type == RI_VALUE_SIZE)
        {
            float from;
            size_t to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float));
            to = ri_float_to_size(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_size));
            value->type = RI_VALUE_SIZE;
        }
        else if(value->type == RI_VALUE_FLOAT && type == RI_VALUE_SSIZE)
        {
            float from;
            ri_ssize to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float));
            to = ri_float_to_ssize(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ssize));
            value->type = RI_VALUE_SSIZE;
        }
        else if(value->type == RI_VALUE_FLOAT && type == RI_VALUE_FLOAT32)
        {
            float from;
            ri_float32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float));
            to = ri_float_to_float32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float32));
            value->type = RI_VALUE_FLOAT32;
        }
        else if(value->type == RI_VALUE_FLOAT && type == RI_VALUE_FLOAT64)
        {
            float from;
            ri_float64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float));
            to = ri_float_to_float64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float64));
            value->type = RI_VALUE_FLOAT64;
        }
        else if(value->type == RI_VALUE_FLOAT && type == RI_VALUE_DOUBLE)
        {
            float from;
            double to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float));
            to = ri_float_to_double(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_double));
            value->type = RI_VALUE_DOUBLE;
        }








        //else 
        if(value->type == RI_VALUE_FLOAT32 && type == RI_VALUE_INT)
        {
            ri_float32   from;
            int  to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float32));
            to = ri_float32_to_int(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int));
            value->type = RI_VALUE_INT;
        }
        else if(value->type == RI_VALUE_FLOAT32 && type == RI_VALUE_UINT)
        {
            ri_float32   from;
            ri_uint  to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float32));
            to = ri_float32_to_uint(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint));
            value->type = RI_VALUE_UINT;
        }
        else if(value->type == RI_VALUE_FLOAT32 && type == RI_VALUE_INT8)
        {
            ri_float32   from;
            ri_int8 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float32));
            to = ri_float32_to_int8(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int8));
            value->type = RI_VALUE_INT8;
        }
        else if(value->type == RI_VALUE_FLOAT32 && type == RI_VALUE_UINT8)
        {
            ri_float32 from;
            ri_uint8 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float32));
            to = ri_float32_to_uint8(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint8));
            value->type = RI_VALUE_UINT8;
        }
        else if(value->type == RI_VALUE_FLOAT32 && type == RI_VALUE_INT16)
        {
            ri_float32 from;
            ri_int16 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float32));
            to = ri_float32_to_int16(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int16));
            value->type = RI_VALUE_INT16;
        }
        else if(value->type == RI_VALUE_FLOAT32 && type == RI_VALUE_UINT16)
        {
            ri_float32 from;
            ri_uint16 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float32));
            to = ri_float32_to_uint16(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint16));
            value->type = RI_VALUE_UINT16;
        }
        else if(value->type == RI_VALUE_FLOAT32 && type == RI_VALUE_INT32)
        {
            ri_float32 from;
            ri_int32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float));
            to = ri_float_to_int32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int32));
            value->type = RI_VALUE_INT32;
        }
        else if(value->type == RI_VALUE_FLOAT32 && type == RI_VALUE_UINT32)
        {
            ri_float32 from;
            ri_uint32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float32));
            to = ri_float32_to_uint32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint32));
            value->type = RI_VALUE_UINT32;
        }
        else if(value->type == RI_VALUE_FLOAT32 && type == RI_VALUE_INT64)
        {
            ri_float32 from;
            ri_int64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float32));
            to = ri_float32_to_int64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int64));
            value->type = RI_VALUE_INT64;
        }
        else if(value->type == RI_VALUE_FLOAT32 && type == RI_VALUE_UINT64)
        {
            ri_float32 from;
            ri_uint64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float32));
            to = ri_float32_to_uint64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint64));
            value->type = RI_VALUE_UINT64;
        }
        else if(value->type == RI_VALUE_FLOAT32 && type == RI_VALUE_LONG)
        {
            ri_float32 from;
            long to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float32));
            to = ri_float32_to_long(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_long));
            value->type = RI_VALUE_LONG;
        }
        else if(value->type == RI_VALUE_FLOAT32 && type == RI_VALUE_ULONG)
        {
            ri_float32 from;
            ri_ulong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float32));
            to = ri_float32_to_ulong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ulong));
            value->type = RI_VALUE_ULONG;
        }
        else if(value->type == RI_VALUE_FLOAT32 && type == RI_VALUE_LONGLONG)
        {
            ri_float32 from;
            ri_longlong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float32));
            to = ri_float32_to_longlong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_longlong));
            value->type = RI_VALUE_LONGLONG;
        }
        else if(value->type == RI_VALUE_FLOAT32 && type == RI_VALUE_ULONGLONG)
        {
            ri_float32 from;
            ri_ulonglong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float32));
            to = ri_float32_to_ulonglong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ulonglong));
            value->type = RI_VALUE_ULONGLONG;
        } 
        else if(value->type == RI_VALUE_FLOAT32 && type == RI_VALUE_SIZE)
        {
            ri_float32 from;
            size_t to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float32));
            to = ri_float32_to_size(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_size));
            value->type = RI_VALUE_SIZE;
        }
        else if(value->type == RI_VALUE_FLOAT32 && type == RI_VALUE_SSIZE)
        {
            ri_float32 from;
            ri_ssize to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float32));
            to = ri_float32_to_ssize(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ssize));
            value->type = RI_VALUE_SSIZE;
        }
        else if(value->type == RI_VALUE_FLOAT32 && type == RI_VALUE_FLOAT)
        {
            ri_float32 from;
            float to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float32));
            to = ri_float32_to_float(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float));
            value->type = RI_VALUE_FLOAT;
        }
        else if(value->type == RI_VALUE_FLOAT32 && type == RI_VALUE_FLOAT64)
        {
            ri_float32 from;
            ri_float64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float32));
            to = ri_float32_to_float64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float64));
            value->type = RI_VALUE_FLOAT64;
        }
        else if(value->type == RI_VALUE_FLOAT32 && type == RI_VALUE_DOUBLE)
        {
            ri_float32 from;
            double to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float32));
            to = ri_float32_to_double(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_double));
            value->type = RI_VALUE_DOUBLE;
        }






        //else 
        if(value->type == RI_VALUE_FLOAT64 && type == RI_VALUE_INT)
        {
            ri_float64   from;
            int  to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float64));
            to = ri_float64_to_int(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int));
            value->type = RI_VALUE_INT;
        }
        else if(value->type == RI_VALUE_FLOAT64 && type == RI_VALUE_UINT)
        {
            ri_float64   from;
            ri_uint  to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float64));
            to = ri_float64_to_uint(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint));
            value->type = RI_VALUE_UINT;
        }
        else if(value->type == RI_VALUE_FLOAT64 && type == RI_VALUE_INT8)
        {
            ri_float64   from;
            ri_int8 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float64));
            to = ri_float64_to_int8(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int8));
            value->type = RI_VALUE_INT8;
        }
        else if(value->type == RI_VALUE_FLOAT64 && type == RI_VALUE_UINT8)
        {
            ri_float64 from;
            ri_uint8 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float64));
            to = ri_float64_to_uint8(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint8));
            value->type = RI_VALUE_UINT8;
        }
        else if(value->type == RI_VALUE_FLOAT64 && type == RI_VALUE_INT16)
        {
            ri_float64 from;
            ri_int16 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float64));
            to = ri_float64_to_int16(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int16));
            value->type = RI_VALUE_INT16;
        }
        else if(value->type == RI_VALUE_FLOAT64 && type == RI_VALUE_UINT16)
        {
            ri_float64 from;
            ri_uint16 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float64));
            to = ri_float64_to_uint16(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint16));
            value->type = RI_VALUE_UINT16;
        }
        else if(value->type == RI_VALUE_FLOAT64 && type == RI_VALUE_INT32)
        {
            ri_float64 from;
            ri_int32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float64));
            to = ri_float64_to_int32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int32));
            value->type = RI_VALUE_INT32;
        }
        else if(value->type == RI_VALUE_FLOAT64 && type == RI_VALUE_UINT32)
        {
            ri_float64 from;
            ri_uint32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float64));
            to = ri_float64_to_uint32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint32));
            value->type = RI_VALUE_UINT32;
        }
        else if(value->type == RI_VALUE_FLOAT64 && type == RI_VALUE_INT64)
        {
            ri_float64 from;
            ri_int64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float64));
            to = ri_float64_to_int64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int64));
            value->type = RI_VALUE_INT64;
        }
        else if(value->type == RI_VALUE_FLOAT64 && type == RI_VALUE_UINT64)
        {
            ri_float64 from;
            ri_uint64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float64));
            to = ri_float64_to_uint64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint64));
            value->type = RI_VALUE_UINT64;
        }
        else if(value->type == RI_VALUE_FLOAT64 && type == RI_VALUE_LONG)
        {
            ri_float64 from;
            long to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float64));
            to = ri_float64_to_long(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_long));
            value->type = RI_VALUE_LONG;
        }
        else if(value->type == RI_VALUE_FLOAT64 && type == RI_VALUE_ULONG)
        {
            ri_float64 from;
            ri_ulong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float64));
            to = ri_float64_to_ulong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ulong));
            value->type = RI_VALUE_ULONG;
        }
        else if(value->type == RI_VALUE_FLOAT64 && type == RI_VALUE_LONGLONG)
        {
            ri_float64 from;
            ri_longlong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float64));
            to = ri_float64_to_longlong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_longlong));
            value->type = RI_VALUE_LONGLONG;
        }
        else if(value->type == RI_VALUE_FLOAT64 && type == RI_VALUE_ULONGLONG)
        {
            ri_float64 from;
            ri_ulonglong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float64));
            to = ri_float64_to_ulonglong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ulonglong));
            value->type = RI_VALUE_ULONGLONG;
        } 
        else if(value->type == RI_VALUE_FLOAT64 && type == RI_VALUE_SIZE)
        {
            ri_float64 from;
            size_t to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float64));
            to = ri_float64_to_size(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_size));
            value->type = RI_VALUE_SIZE;
        }
        else if(value->type == RI_VALUE_FLOAT64 && type == RI_VALUE_SSIZE)
        {
            ri_float64 from;
            ri_ssize to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float64));
            to = ri_float64_to_ssize(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ssize));
            value->type = RI_VALUE_SSIZE;
        }
        else if(value->type == RI_VALUE_FLOAT64 && type == RI_VALUE_FLOAT)
        {
            ri_float64 from;
            float to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float64));
            to = ri_float64_to_float(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float));
            value->type = RI_VALUE_FLOAT;
        }
        else if(value->type == RI_VALUE_FLOAT64 && type == RI_VALUE_FLOAT32)
        {
            ri_float64 from;
            ri_float32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float64));
            to = ri_float64_to_float32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float32));
            value->type = RI_VALUE_FLOAT32;
        }
        else if(value->type == RI_VALUE_FLOAT64&& type == RI_VALUE_DOUBLE)
        {
            ri_float64 from;
            double to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_float64));
            to = ri_float64_to_double(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_double));
            value->type = RI_VALUE_DOUBLE;
        }








        if(value->type == RI_VALUE_DOUBLE && type == RI_VALUE_INT)
        {
            double   from;
            int  to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_double));
            to = ri_double_to_int(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int));
            value->type = RI_VALUE_INT;
        }
        else if(value->type == RI_VALUE_DOUBLE && type == RI_VALUE_UINT)
        {
            double   from;
            ri_uint  to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_double));
            to = ri_double_to_uint(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint));
            value->type = RI_VALUE_UINT;
        }
        else if(value->type == RI_VALUE_DOUBLE && type == RI_VALUE_INT8)
        {
            double   from;
            ri_int8 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_double));
            to = ri_double_to_int8(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int8));
            value->type = RI_VALUE_INT8;
        }
        else if(value->type == RI_VALUE_DOUBLE && type == RI_VALUE_UINT8)
        {
            double from;
            ri_uint8 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_double));
            to = ri_double_to_uint8(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint8));
            value->type = RI_VALUE_UINT8;
        }
        else if(value->type == RI_VALUE_DOUBLE && type == RI_VALUE_INT16)
        {
            double from;
            ri_int16 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_double));
            to = ri_double_to_int16(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int16));
            value->type = RI_VALUE_INT16;
        }
        else if(value->type == RI_VALUE_DOUBLE && type == RI_VALUE_UINT16)
        {
            double from;
            ri_uint16 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_double));
            to = ri_double_to_uint16(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint16));
            value->type = RI_VALUE_UINT16;
        }
        else if(value->type == RI_VALUE_DOUBLE && type == RI_VALUE_INT32)
        {
            double from;
            ri_int32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_double));
            to = ri_double_to_int32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int32));
            value->type = RI_VALUE_INT32;
        }
        else if(value->type == RI_VALUE_DOUBLE && type == RI_VALUE_UINT32)
        {
            double from;
            ri_uint32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_double));
            to = ri_double_to_uint32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint32));
            value->type = RI_VALUE_UINT32;
        }
        else if(value->type == RI_VALUE_DOUBLE && type == RI_VALUE_INT64)
        {
            double from;
            ri_int64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_double));
            to = ri_double_to_int64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_int64));
            value->type = RI_VALUE_INT64;
        }
        else if(value->type == RI_VALUE_DOUBLE && type == RI_VALUE_UINT64)
        {
            double from;
            ri_uint64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_double));
            to = ri_double_to_uint64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_uint64));
            value->type = RI_VALUE_UINT64;
        }
        else if(value->type == RI_VALUE_DOUBLE && type == RI_VALUE_LONG)
        {
            double from;
            long to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_double));
            to = ri_double_to_long(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_long));
            value->type = RI_VALUE_LONG;
        }
        else if(value->type == RI_VALUE_DOUBLE && type == RI_VALUE_ULONG)
        {
            double from;
            ri_ulong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_double));
            to = ri_double_to_ulong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ulong));
            value->type = RI_VALUE_ULONG;
        }
        else if(value->type == RI_VALUE_DOUBLE && type == RI_VALUE_LONGLONG)
        {
            double from;
            ri_longlong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_double));
            to = ri_double_to_longlong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_longlong));
            value->type = RI_VALUE_LONGLONG;
        }
        else if(value->type == RI_VALUE_DOUBLE && type == RI_VALUE_ULONGLONG)
        {
            double from;
            ri_ulonglong to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_double));
            to = ri_double_to_ulonglong(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ulonglong));
            value->type = RI_VALUE_ULONGLONG;
        } 
        else if(value->type == RI_VALUE_DOUBLE && type == RI_VALUE_SIZE)
        {
            double from;
            size_t to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_double));
            to = ri_double_to_size(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_size));
            value->type = RI_VALUE_SIZE;
        }
        else if(value->type == RI_VALUE_DOUBLE && type == RI_VALUE_SSIZE)
        {
            double from;
            ri_ssize to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_double));
            to = ri_double_to_ssize(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_ssize));
            value->type = RI_VALUE_SSIZE;
        }
        else if(value->type == RI_VALUE_DOUBLE && type == RI_VALUE_FLOAT)
        {
            double from;
            float to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_double));
            to = ri_double_to_float(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float));
            value->type = RI_VALUE_FLOAT;
        }
        else if(value->type == RI_VALUE_DOUBLE && type == RI_VALUE_FLOAT32)
        {
            double from;
            ri_float32 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_double));
            to = ri_double_to_float32(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float32));
            value->type = RI_VALUE_FLOAT32;
        }
        else if(value->type == RI_VALUE_DOUBLE && type == RI_VALUE_FLOAT64)
        {
            double from;
            ri_float64 to;

            ri_memcpy(&from, value->dataTemp, sizeof(ri_double));
            to = ri_double_to_float64(from);
            ri_memcpy(value->dataTemp, &to, sizeof(ri_float64));
            value->type = RI_VALUE_FLOAT64;
        }

        return ret;
    }

    RI_API int RI_VALUE_SetType(RI_VALUE_t *value, RI_VALUE_TYPE_t type)
    {
        int ret;

        ret = ri_value_SetType(value, type);

        return ret;;
    }

    RI_API ri_int32 RI_VALUE_GetInt32(RI_VALUE_t *value)
    {
        ri_int32 int32;

        if(value->type != RI_VALUE_INT32)
        {
            return 0; 
        }

        ri_memcpy(&int32, value->dataTemp, sizeof(ri_int32));

        return int32;
    }

    RI_API int RI_VALUE_GetInt(RI_VALUE_t *value)
    {
        int int_value;

        if(value->type != RI_VALUE_INT)
        {
            return 0; 
        }

        ri_memcpy(&int_value, value->dataTemp, sizeof(ri_int));

        return int_value;
    }

    RI_API ri_uint32 RI_VALUE_GetUInt32(RI_VALUE_t *value)
    {
        ri_uint32 uint32;

        if(value->type != RI_VALUE_UINT32)
        {
            return 0; 
        }

        ri_memcpy(&uint32, value->dataTemp, sizeof(ri_uint32));

        return uint32;
    }

    RI_API ri_int8 RI_VALUE_GetInt8(RI_VALUE_t *value)
    {
        ri_int8 int8;

        if(value->type != RI_VALUE_INT8)
        {
            return 0; 
        }

        ri_memcpy(&int8, value->dataTemp, sizeof(ri_int8));

        return int8;
    }

    RI_API ri_uint8 RI_VALUE_GetUInt8(RI_VALUE_t *value)
    {
        ri_uint8 uint8;

        if(value->type != RI_VALUE_UINT8)
        {
            return 0; 
        }

        ri_memcpy(&uint8, value->dataTemp, sizeof(ri_uint8));

        return uint8;
    }

    RI_API ri_int16 RI_VALUE_GetInt16(RI_VALUE_t *value)
    {
        ri_int16 int16;

        if(value->type != RI_VALUE_INT16)
        {
            return 0; 
        }

        ri_memcpy(&int16, value->dataTemp, sizeof(ri_int16));

        return int16;
    }

    RI_API ri_uint16 RI_VALUE_GetUInt16(RI_VALUE_t *value)
    {
        ri_int16 uint16;

        if(value->type != RI_VALUE_UINT16)
        {
            return 0; 
        }

        ri_memcpy(&uint16, value->dataTemp, sizeof(ri_uint16));

        return uint16;
    }

    RI_API ri_int64 RI_VALUE_GetInt64(RI_VALUE_t *value)
    {
        ri_int64 int64;

        if(value->type != RI_VALUE_INT64)
        {
            return 0; 
        }

        ri_memcpy(&int64, value->dataTemp, sizeof(ri_int64));

        return int64;
    }

    RI_API ri_uint64 RI_VALUE_GetUInt64(RI_VALUE_t *value)
    {
        ri_uint64 uint64;

        if(value->type != RI_VALUE_UINT64)
        {
            return 0; 
        }

        ri_memcpy(&uint64, value->dataTemp, sizeof(ri_uint64));

        return uint64;
    }

    RI_API float RI_VALUE_GetFloat(RI_VALUE_t *value)
    {
        float float_value;

        if(value->type != RI_VALUE_FLOAT32)
        {
            return 0; 
        }

        ri_memcpy(&float_value, value->dataTemp, sizeof(ri_float));

        return float_value;
    }

    RI_API ri_float32 RI_VALUE_GetFloat32(RI_VALUE_t *value)
    {
        ri_float32 float32;

        if(value->type != RI_VALUE_FLOAT32)
        {
            return 0; 
        }

        ri_memcpy(&float32, value->dataTemp, sizeof(ri_float32));

        return float32;
    }

    RI_API ri_float64 RI_VALUE_GetFloat64(RI_VALUE_t *value)
    {
        ri_float64 float64;

        if(value->type != RI_VALUE_FLOAT64)
        {
            return 0; 
        }

        ri_memcpy(&float64, value->dataTemp, sizeof(ri_float64));

        return float64;
    }

    RI_API size_t RI_VALUE_GetBinary(RI_VALUE_t *value, ri_byte *binary, size_t binary_size)
    {
        size_t size;

        if(value->type != RI_VALUE_BINARY)
        {
            return 0; 
        }

        if(value->dataSize > binary_size)
        {
            return 0; 
        }

        ri_memcpy(binary, value->dataTemp, (int)value->dataSize);
        size = value->dataSize;

        return size;
    }

    RI_API size_t RI_VALUE_GetBinarySize(RI_VALUE_t *value)
    {
        size_t size;

        if(value->type != RI_VALUE_BINARY)
        {
            return 0; 
        }

        size = value->dataSize;

        return size;
    }

    RI_API size_t RI_VALUE_GetString(RI_VALUE_t *value, ri_utf8 *str, size_t str_size)
    {
        //size_t size;

        if(value->type != RI_VALUE_STRING)
        {
            return 0; 
        }

        /*size = ri_strsize((const ri_utf8 *)value->data);

        if(size > str_size)
        {
        RiLock_Unlock(&value->lock);
        RiLock_Unlock(&lock);
        return 0; 
        }

        ri_memcpy(str, value->data, (int)size);*/

        return RI_OK;;
    }

    RI_API size_t RI_VALUE_GetStringSize(RI_VALUE_t *value)
    {
        //size_t size;;

        if(value->type != RI_VALUE_STRING)
        {
            return 0; 
        }

        //size = ri_strsize((const ri_utf8 *)value->data);

        //return size;
        return RI_OK;
    }

    RI_API ri_int64 RI_VALUE_GetYear(RI_VALUE_t *value)
    {
        RiDateTime_t date_time;

        if(value->type != RI_VALUE_DATE_TIME &&
            value->type != RI_VALUE_DATE &&
            value->type != RI_VALUE_TIME)
        {
            return 0; 
        }

        ri_memcpy(&date_time, value->data, sizeof(RiDateTime_t));  

        return date_time.year;
    }

    RI_API int RI_VALUE_GetMonth(RI_VALUE_t *value)
    {
        RiDateTime_t date_time;

        if(value->type != RI_VALUE_DATE_TIME &&
            value->type != RI_VALUE_DATE &&
            value->type != RI_VALUE_TIME)
        {
            return 0; 
        }

        ri_memcpy(&date_time, value->data, sizeof(RiDateTime_t));  

        return date_time.month;
    }

    RI_API int RI_VALUE_GetDay(RI_VALUE_t *value)
    {
        RiDateTime_t date_time;

        if(value->type != RI_VALUE_DATE_TIME &&
            value->type != RI_VALUE_DATE &&
            value->type != RI_VALUE_TIME)
        {
            return 0; 
        }

        ri_memcpy(&date_time, value->data, sizeof(RiDateTime_t));  

        return date_time.day;
    }

    RI_API int RI_VALUE_GetHour(RI_VALUE_t *value)
    {
        RiDateTime_t date_time;

        if(value->type != RI_VALUE_DATE_TIME &&
            value->type != RI_VALUE_DATE &&
            value->type != RI_VALUE_TIME)
        {
            return 0; 
        }

        ri_memcpy(&date_time, value->data, sizeof(RiDateTime_t));  

        return date_time.hour;
    }

    RI_API int RI_VALUE_GetMin(RI_VALUE_t *value)
    {
        RiDateTime_t date_time;

        if(value->type != RI_VALUE_DATE_TIME &&
            value->type != RI_VALUE_DATE &&
            value->type != RI_VALUE_TIME)
        {
            return 0; 
        }

        ri_memcpy(&date_time, value->data, sizeof(RiDateTime_t));  

        return date_time.min;
    }


    RI_API int RI_VALUE_GetSec(RI_VALUE_t *value)
    {
        RiDateTime_t date_time;

        if(value->type != RI_VALUE_DATE_TIME &&
            value->type != RI_VALUE_DATE &&
            value->type != RI_VALUE_TIME)
        {
            return 0; 
        }

        ri_memcpy(&date_time, value->data, sizeof(RiDateTime_t));

        return date_time.sec;
    }

    RI_API int RI_VALUE_GetMs(RI_VALUE_t *value)
    {
        RiDateTime_t date_time;

        if(value->type != RI_VALUE_DATE_TIME &&
            value->type != RI_VALUE_DATE &&
            value->type != RI_VALUE_TIME)
        {
            return 0; 
        }

        ri_memcpy(&date_time, value->data, sizeof(RiDateTime_t));  

        return date_time.ms;
    }


#ifdef __cplusplus
}
#endif

