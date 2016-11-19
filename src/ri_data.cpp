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


#include "openri.h"
//#include "ri_data.h"

#include <stdlib.h>

#ifdef __cplusplus
extern "C" 
{
#endif


    /**
    * @brief 
    *
    * @param void.
    *
    * @return int
    *
    * @retval
    *
    * @history 2007-09-12 Initial.                    Mingta Li  
    */
    /*int ri_data_InitLL(RI_INIT *init)
    {
    if(RI_INIT_Magic(init) != RI_OK) return RI_ERR_MAGIC;

    // Init before RiSys. Must not put any init which is related to system here.

    return RI_OK;
    }*/


    RI_API int ri_reverse_endian (ri_byte *data, size_t size)
    {  
        size_t i;
        size_t to;
        ri_byte temp;
        if(size == 0) return RI_OK;
        if(data == NULL) return RI_ERROR_NULL_POINTER;

        to = size / 2;

        for(i = 0; i < to; i ++)
        {
            temp = data[i];
            data[i] = data[size - 1 - i];   
            data[size - 1 - i] = temp;  
        }

        return RI_OK;
    }


    RI_API ri_uint32 ri_cpu_to_le32(ri_uint32 value)
    {
        ri_uint32 temp;

        temp = value;

        /*if(RI_SYS_GetEndian() == RI_ENDIAN_BIG)
        {
        ri_reverse_endian ((ri_byte*)&temp, sizeof(ri_uint32));
        }*/

        value = temp;

        return value;
    }

    RI_API ri_uint32 ri_le32_to_cpu(ri_uint32 value)
    {
        ri_uint32 temp;

        temp = value;

        /*if(RI_SYS_GetEndian() == RI_ENDIAN_BIG)
        {
        ri_reverse_endian ((ri_byte*)&temp, sizeof(ri_uint32));
        }*/

        value = temp;

        return value;
    }

    RI_API ri_uint32 ri_cpu_to_be32(ri_uint32 value)
    {
        ri_uint32 temp;

        temp = value;

        /*if(RI_SYS_GetEndian() == RI_ENDIAN_LITTLE)
        {
        ri_reverse_endian ((ri_byte*)&temp, sizeof(ri_uint32));
        }*/

        value = temp;

        return value;
    }

    RI_API ri_uint32 ri_be32_to_cpu(ri_uint32 value)
    {
        ri_uint32 temp;

        temp = value;

        /*if(RI_SYS_GetEndian() == RI_ENDIAN_LITTLE)
        {
        ri_reverse_endian ((ri_byte*)&temp, sizeof(ri_uint32));
        }*/

        value = temp;

        return value;
    }

    RI_API ri_uint16 ri_cpu_to_le16(ri_uint16 value)
    {
        ri_uint16 temp;

        temp = value;

        /*if(RI_SYS_GetEndian() == RI_ENDIAN_BIG)
        {
        ri_reverse_endian ((ri_byte*)&temp, sizeof(ri_uint16));
        }*/

        value = temp;

        return value;
    }

    RI_API ri_uint16 ri_le16_to_cpu(ri_uint16 value)
    {
        ri_uint16 temp;

        temp = value;

        /*if(RI_SYS_GetEndian() == RI_ENDIAN_BIG)
        {
        ri_reverse_endian ((ri_byte*)&temp, sizeof(ri_uint16));
        }*/

        value = temp;

        return value;
    }

    RI_API ri_uint16 ri_cpu_to_be16(ri_uint16 value)
    {
        ri_uint16 temp;

        temp = value;

        /*if(RI_SYS_GetEndian() == RI_ENDIAN_LITTLE)
        {
        ri_reverse_endian ((ri_byte*)&temp, sizeof(ri_uint16));
        }*/

        value = temp;

        return value;
    }

    RI_API ri_uint16 ri_be16_to_cpu(ri_uint16 value)
    {
        ri_uint16 temp;

        temp = value;

        /*if(RI_SYS_GetEndian() == RI_ENDIAN_LITTLE)
        {
        ri_reverse_endian ((ri_byte*)&temp, sizeof(ri_uint16));
        }*/

        value = temp;

        return value;
    }

    RI_API ri_uint64 ri_cpu_to_le64(ri_uint64 value)
    {
        ri_uint64 temp;

        temp = value;

        /*if(RI_SYS_GetEndian() == RI_ENDIAN_BIG)
        {
        ri_reverse_endian ((ri_byte*)&temp, sizeof(ri_uint64));
        }*/

        value = temp;

        return value;
    }

    RI_API ri_uint64 ri_le64_to_cpu(ri_uint64 value)
    {
        ri_uint64 temp;

        temp = value;

        /*if(RI_SYS_GetEndian() == RI_ENDIAN_BIG)
        {
        ri_reverse_endian ((ri_byte*)&temp, sizeof(ri_uint64));
        }*/

        value = temp;

        return value;
    }

    RI_API ri_uint64 ri_cpu_to_be64(ri_uint64 value)
    {
        ri_uint64 temp;

        temp = value;

        /*if(RI_SYS_GetEndian() == RI_ENDIAN_LITTLE)
        {
        ri_reverse_endian ((ri_byte*)&temp, sizeof(ri_uint64));
        }*/

        value = temp;

        return value;
    }

    RI_API ri_uint64 ri_be64_to_cpu(ri_uint64 value)
    {
        ri_uint64 temp;

        temp = value;

        /*if(RI_SYS_GetEndian() == RI_ENDIAN_LITTLE)
        {
        ri_reverse_endian ((ri_byte*)&temp, sizeof(ri_uint64));
        }*/

        value = temp;

        return value;
    }


    // Safe data convert functions.

#if !defined(RI_32BIT)
    //#error Safe data convert functions are only for 32 bit processors now!
#endif


    RI_API ri_uint   ri_int_to_uint(int  from)
    {
        ri_uint to;

        //  if(from > RI_UINT_MAX)
        //    to = RI_UINT_MAX;
        if(from < RI_UINT_MIN)
            to = RI_UINT_MIN;
        else
            to = (ri_uint)from;

        return to;  
    }

    RI_API ri_int8   ri_int_to_int8(int  from)
    {
        ri_int8 to;

        if(from > RI_INT8_MAX)
            to = RI_INT8_MAX;
        else if(from < RI_INT8_MIN)
            to = RI_INT8_MIN;
        else
            to = (ri_int8)from;

        return to;  
    }

    RI_API ri_uint8  ri_int_to_uint8(int from)
    {
        ri_uint8 to;

        if(from > RI_UINT8_MAX)
            to = RI_UINT8_MAX;
        else if(from < RI_UINT8_MIN)
            to = RI_UINT8_MIN;
        else
            to = (ri_uint8)from;

        return to;    
    }

    RI_API ri_int16   ri_int_to_int16(int from)
    {
        ri_int16 to;

        if(from > RI_INT16_MAX)
            to = RI_INT16_MAX;
        else if(from < RI_INT16_MIN)
            to = RI_INT16_MIN;
        else
            to = (ri_int16)from;

        return to;    
    }

    RI_API ri_uint16  ri_int_to_uint16(int from)
    {
        ri_uint16 to;

        if(from > RI_UINT16_MAX)
            to = RI_UINT16_MAX;
        else if(from < RI_UINT16_MIN)
            to = RI_UINT16_MIN;
        else
            to = (ri_uint16)from;

        return to;
    }

    RI_API ri_int32  ri_int_to_int32(int from)
    {
        ri_int32 to;

        if(from > RI_INT32_MAX)
            to = RI_INT32_MAX;
        else if(from < RI_INT32_MIN)
            to = RI_INT32_MIN;
        else
            to = (ri_int32)from;

        return to;
    }

    RI_API ri_uint32 ri_int_to_uint32(int from)
    {
        ri_uint32 to;

        //  if(from > RI_UINT32_MAX)
        //    to = RI_UINT32_MAX;
        if(from < RI_UINT32_MIN)
            to = RI_UINT32_MIN;
        else
            to = (ri_uint32)from;

        return to;
    }

    RI_API ri_int64   ri_int_to_int64(int from)
    {
        ri_int64 to;

        //  if((ri_int64)from > RI_INT64_MAX)
        //    to = RI_INT64_MAX;
        //  else if((ri_int64)from < RI_INT64_MIN)
        //    to = RI_INT64_MIN;
        //  else
        to = (ri_int64)from;

        return to;
    }

    RI_API ri_uint64  ri_int_to_uint64(int from)
    {
        ri_uint64 to;

        //  if(from > RI_UINT64_MAX)
        //    to = RI_UINT64_MAX;
        if(from < RI_UINT64_MIN)
            to = RI_UINT64_MIN;
        else
            to = (ri_uint64)from;

        return to;
    }

    RI_API long  ri_int_to_long(int from)
    {
        long to;

        if(from > RI_LONG_MAX)
            to = RI_LONG_MAX;
        else if(from < RI_LONG_MIN)
            to = RI_LONG_MIN;
        else
            to = (ri_long)from;

        return to;
    }

    RI_API ri_ulong  ri_int_to_ulong(int from)
    {
        ri_ulong to;

        //  if(from > RI_ULONG_MAX)
        //    to = RI_ULONG_MAX;
        if(from < RI_ULONG_MIN)
            to = RI_ULONG_MIN;
        else
            to = (ri_ulong)from;

        return to;
    }

    RI_API ri_longlong  ri_int_to_longlong(int from)
    {
        ri_longlong to;

        to = (ri_longlong)from;

        return to;
    }

    RI_API ri_ulonglong  ri_int_to_ulonglong(int from)
    {
        ri_ulonglong to;

        //  if(from > RI_ULONGLONG_MAX)
        //    to = RI_ULONGLONG_MAX;
        if(from < RI_ULONGLONG_MIN)
            to = RI_ULONGLONG_MIN;
        else
            to = (ri_ulonglong)from;

        return to;
    }

    RI_API size_t   ri_int_to_size(int from)
    {
        size_t to;

        //  if(from > RI_SIZE_MAX)
        //    to = RI_SIZE_MAX;
        if(from < RI_SIZE_MIN)
            to = RI_SIZE_MIN;
        else
            to = (ri_size)from;

        return to;
    }

    RI_API ri_ssize  ri_int_to_ssize(int from)
    {
        ri_ssize to;

        if(from > RI_SSIZE_MAX)
            to = RI_SSIZE_MAX;
        else if(from < RI_SSIZE_MIN)
            to = RI_SSIZE_MIN;
        else
            to = (ri_ssize)from;

        return to;
    }

    RI_API float  ri_int_to_float(int from)
    {
        float to;

        if(from > RI_FLOAT_MAX)
            to = RI_FLOAT_MAX;
        else if(from < RI_FLOAT_MIN)
            to = RI_FLOAT_MIN;
        else
            to = (ri_float)from;

        return to;
    }

    RI_API ri_float32  ri_int_to_float32(int from)
    {
        ri_float32 to;

        if(from > RI_FLOAT32_MAX)
            to = RI_FLOAT32_MAX;
        else if(from < RI_FLOAT32_MIN)
            to = RI_FLOAT32_MIN;
        else
            to = (ri_float32)from;

        return to;
    }

    RI_API ri_float64  ri_int_to_float64(int from)
    {
        ri_float64 to;

        if(from > RI_FLOAT64_MAX)
            to = RI_FLOAT64_MAX;
        else if(from < RI_FLOAT64_MIN)
            to = RI_FLOAT64_MIN;
        else
            to = (ri_float64)from;

        return to;
    }

    RI_API double  ri_int_to_double(int from)
    {
        double to;

        if(from > RI_DOUBLE_MAX)
            to = RI_DOUBLE_MAX;
        else if(from < RI_DOUBLE_MIN)
            to = RI_DOUBLE_MIN;
        else
            to = (ri_double)from;

        return to;
    }





    RI_API int   ri_uint_to_int(ri_uint  from)
    {
        int to;

        if(from > RI_INT_MAX)
            to = (ri_int)RI_INT_MAX;
        else
            to = (ri_int)from;

        return to;  
    }

    RI_API ri_int8   ri_uint_to_int8(ri_uint  from)
    {
        ri_int8 to;

        if(from > RI_INT8_MAX)
            to = RI_INT8_MAX;
        else
            to = (ri_int8)from;

        return to;  
    }

    RI_API ri_uint8  ri_uint_to_uint8(ri_uint from)
    {
        ri_uint8 to;

        if(from > RI_UINT8_MAX)
            to = RI_UINT8_MAX;
        else if(from < RI_UINT8_MIN)
            to = RI_UINT8_MIN;
        else
            to = (ri_uint8)from;

        return to;    
    }

    RI_API ri_int16   ri_uint_to_int16(ri_uint from)
    {
        ri_int16 to;

        if(from > RI_INT16_MAX)
            to = RI_INT16_MAX;
        else
            to = (ri_int16)from;

        return to;    
    }

    RI_API ri_uint16  ri_uint_to_uint16(ri_uint from)
    {
        ri_uint16 to;

        if(from > RI_UINT16_MAX)
            to = RI_UINT16_MAX;
        else if(from < RI_UINT16_MIN)
            to = RI_UINT16_MIN;
        else
            to = (ri_uint16)from;

        return to;
    }

    RI_API ri_int32  ri_uint_to_int32(ri_uint from)
    {
        ri_int32 to;

        if(from > RI_INT32_MAX)
            to = RI_INT32_MAX;
        else
            to = (ri_int32)from;

        return to;
    }

    RI_API ri_uint32 ri_uint_to_uint32(ri_uint from)
    {
        ri_uint32 to;

        if(from > RI_UINT32_MAX)
            to = RI_UINT32_MAX;
        else if(from < RI_UINT32_MIN)
            to = RI_UINT32_MIN;
        else
            to = (ri_uint32)from;

        return to;
    }

    RI_API ri_int64   ri_uint_to_int64(ri_uint from)
    {
        ri_int64 to;


        to = (ri_int64)from;

        return to;
    }

    RI_API ri_uint64  ri_uint_to_uint64(ri_uint from)
    {
        ri_uint64 to;

        to = (ri_uint64)from;

        return to;
    }

    RI_API long  ri_uint_to_long(ri_uint from)
    {
        long to;

        if(from > RI_LONG_MAX)
            to = RI_LONG_MAX;
        else
            to = (ri_long)from;

        return to;
    }

    RI_API ri_ulong  ri_uint_to_ulong(ri_uint from)
    {
        ri_ulong to;

        if(from > RI_ULONG_MAX)
            to = RI_ULONG_MAX;
        else if(from < RI_ULONG_MIN)
            to = RI_ULONG_MIN;
        else
            to = (ri_ulong)from;

        return to;
    }

    RI_API ri_longlong  ri_uint_to_longlong(ri_uint from)
    {
        ri_longlong to;

        to = (ri_longlong)from;

        return to;
    }

    RI_API ri_ulonglong  ri_uint_to_ulonglong(ri_uint from)
    {
        ri_ulonglong to;

        to = (ri_ulonglong)from;

        return to;
    }

    RI_API size_t   ri_uint_to_size(ri_uint from)
    {
        size_t to;

        if(from > RI_SIZE_MAX)
            to = RI_SIZE_MAX;
        else if(from < RI_SIZE_MIN)
            to = RI_SIZE_MIN;
        else
            to = (ri_size)from;

        return to;
    }

    RI_API ri_ssize  ri_uint_to_ssize(ri_uint from)
    {
        ri_ssize to;

        if(from > RI_SSIZE_MAX)
            to = RI_SSIZE_MAX;
        else
            to = (ri_ssize)from;

        return to;
    }

    RI_API float  ri_uint_to_float(ri_uint from)
    {
        float to;

        if(from > RI_FLOAT_MAX)
            to = RI_FLOAT_MAX;
        else if(from < RI_FLOAT_MIN)
            to = RI_FLOAT_MIN;
        else
            to = (ri_float)from;

        return to;
    }

    RI_API ri_float32  ri_uint_to_float32(ri_uint from)
    {
        ri_float32 to;

        if(from > RI_FLOAT32_MAX)
            to = RI_FLOAT32_MAX;
        else if(from < RI_FLOAT32_MIN)
            to = RI_FLOAT32_MIN;
        else
            to = (ri_float32)from;

        return to;
    }

    RI_API ri_float64  ri_uint_to_float64(ri_uint from)
    {
        ri_float64 to;

        if(from > RI_FLOAT64_MAX)
            to = RI_FLOAT64_MAX;
        else if(from < RI_FLOAT64_MIN)
            to = RI_FLOAT64_MIN;
        else
            to = (ri_float64)from;

        return to;
    }

    RI_API double  ri_uint_to_double(ri_uint from)
    {
        double to;

        if(from > RI_DOUBLE_MAX)
            to = RI_DOUBLE_MAX;
        else if(from < RI_DOUBLE_MIN)
            to = RI_DOUBLE_MIN;
        else
            to = (ri_double)from;

        return to;
    }





    RI_API int   ri_int8_to_int(ri_int8  from)
    {
        int to;

        //  if(from > RI_INT_MAX)
        //    to = RI_INT_MAX;
        //  else if(from < RI_INT_MIN)
        //    to = RI_INT_MIN;
        //  else
        to = (ri_int)from;

        return to;  
    }

    RI_API ri_uint   ri_int8_to_uint(ri_int8  from)
    {
        ri_uint to;

        //  if(from > RI_UINT_MAX)
        //    to = RI_UINT_MAX;
        if(from < RI_UINT_MIN)
            to = RI_UINT_MIN;
        else
            to = (ri_uint)from;

        return to;  
    }

    RI_API ri_uint8  ri_int8_to_uint8(ri_int8 from)
    {
        ri_uint8 to;

        //  if(from > RI_UINT8_MAX)
        //    to = RI_UINT8_MAX;
        if(from < RI_UINT8_MIN)
            to = RI_UINT8_MIN;
        else
            to = (ri_uint8)from;

        return to;    
    }

    RI_API ri_int16   ri_int8_to_int16(ri_int8 from)
    {
        ri_int16 to;

        //  if(from > RI_INT16_MAX)
        //    to = RI_INT16_MAX;
        //  else if(from < RI_INT16_MIN)
        //    to = RI_INT16_MIN;
        //  else
        to = (ri_int16)from;

        return to;    
    }

    RI_API ri_uint16  ri_int8_to_uint16(ri_int8 from)
    {
        ri_uint16 to;

        //  if(from > RI_UINT16_MAX)
        //    to = RI_UINT16_MAX;
        if(from < RI_UINT16_MIN)
            to = RI_UINT16_MIN;
        else
            to = (ri_uint16)from;

        return to;
    }

    RI_API ri_int32  ri_int8_to_int32(ri_int8 from)
    {
        ri_int32 to;

        //  if(from > RI_INT32_MAX)
        //    to = RI_INT32_MAX;
        //  else if(from < RI_INT32_MIN)
        //    to = RI_INT32_MIN;
        //  else
        to = (ri_int32)from;

        return to;
    }

    RI_API ri_uint32 ri_int8_to_uint32(ri_int8 from)
    {
        ri_uint32 to;

        //  if(from > RI_UINT32_MAX)
        //    to = RI_UINT32_MAX;
        if(from < RI_UINT32_MIN)
            to = RI_UINT32_MIN;
        else
            to = (ri_uint32)from;

        return to;
    }

    RI_API ri_int64   ri_int8_to_int64(ri_int8 from)
    {
        ri_int64 to;

        //  if(from > RI_INT64_MAX)
        //    to = RI_INT64_MAX;
        //  else if(from < RI_INT64_MIN)
        //    to = RI_INT64_MIN;
        //  else
        to = (ri_int64)from;

        return to;
    }

    RI_API ri_uint64  ri_int8_to_uint64(ri_int8 from)
    {
        ri_uint64 to;

        //  if(from > RI_UINT64_MAX)
        //    to = RI_UINT64_MAX;
        if(from < RI_UINT64_MIN)
            to = RI_UINT64_MIN;
        else
            to = (ri_uint64)from;

        return to;
    }

    RI_API long  ri_int8_to_long(ri_int8 from)
    {
        long to;

        to = (ri_long)from;

        return to;
    }

    RI_API ri_ulong  ri_int8_to_ulong(ri_int8 from)
    {
        ri_ulong to;

        //  if(from > RI_ULONG_MAX)
        //    to = RI_ULONG_MAX;
        if(from < RI_ULONG_MIN)
            to = RI_ULONG_MIN;
        else
            to = (ri_ulong)from;

        return to;
    }

    RI_API ri_longlong  ri_int8_to_longlong(ri_int8 from)
    {
        ri_longlong to;

        to = (ri_longlong)from;

        return to;
    }

    RI_API ri_ulonglong  ri_int8_to_ulonglong(ri_int8 from)
    {
        ri_ulonglong to;

        //  if(from > RI_ULONGLONG_MAX)
        //    to = RI_ULONGLONG_MAX;
        if(from < RI_ULONGLONG_MIN)
            to = RI_ULONGLONG_MIN;
        else
            to = (ri_ulonglong)from;

        return to;
    }

    RI_API size_t   ri_int8_to_size(ri_int8 from)
    {
        size_t to;

        //  if(from > RI_SIZE_MAX)
        //    to = RI_SIZE_MAX;
        if(from < RI_SIZE_MIN)
            to = RI_SIZE_MIN;
        else
            to = (ri_size)from;

        return to;
    }

    RI_API ri_ssize  ri_int8_to_ssize(ri_int8 from)
    {
        ri_ssize to;

        //  if(from > RI_SSIZE_MAX)
        //    to = RI_SSIZE_MAX;
        //  else if(from < RI_SSIZE_MIN)
        //    to = RI_SSIZE_MIN;
        //  else
        to = (ri_ssize)from;

        return to;
    }

    RI_API float  ri_int8_to_float(ri_int8 from)
    {
        float to;

        if(from > RI_FLOAT_MAX)
            to = RI_FLOAT_MAX;
        else if(from < RI_FLOAT_MIN)
            to = RI_FLOAT_MIN;
        else
            to = (ri_float)from;

        return to;
    }

    RI_API ri_float32  ri_int8_to_float32(ri_int8 from)
    {
        ri_float32 to;

        if(from > RI_FLOAT32_MAX)
            to = RI_FLOAT32_MAX;
        else if(from < RI_FLOAT32_MIN)
            to = RI_FLOAT32_MIN;
        else
            to = (ri_float32)from;

        return to;
    }

    RI_API ri_float64  ri_int8_to_float64(ri_int8 from)
    {
        ri_float64 to;

        if(from > RI_FLOAT64_MAX)
            to = RI_FLOAT64_MAX;
        else if(from < RI_FLOAT64_MIN)
            to = RI_FLOAT64_MIN;
        else
            to = (ri_float64)from;

        return to;
    }

    RI_API double  ri_int8_to_double(ri_int8 from)
    {
        double to;

        if(from > RI_DOUBLE_MAX)
            to = RI_DOUBLE_MAX;
        else if(from < RI_DOUBLE_MIN)
            to = RI_DOUBLE_MIN;
        else
            to = (ri_double)from;

        return to;
    }







    RI_API int   ri_uint8_to_int(ri_uint8  from)
    {
        int to;

        to = (ri_int)from;

        return to;  
    }
    RI_API ri_uint   ri_uint8_to_uint(ri_uint8  from)
    {
        ri_uint to;

        to = (ri_uint)from;

        return to;  
    }
    RI_API ri_int8  ri_uint8_to_int8(ri_uint8 from)
    {
        ri_int8 to;

        to = (ri_int8)from;

        return to;    
    }

    RI_API ri_int16   ri_uint8_to_int16(ri_uint8 from)
    {
        ri_int16 to;

        to = (ri_int16)from;

        return to;    
    }

    RI_API ri_uint16  ri_uint8_to_uint16(ri_uint8 from)
    {
        ri_uint16 to;

        //  if(from > RI_UINT16_MAX)
        //    to = RI_UINT16_MAX;
        //  else if(from < RI_UINT16_MIN)
        //    to = RI_UINT16_MIN;
        //  else
        to = (ri_uint16)from;

        return to;
    }

    RI_API ri_int32  ri_uint8_to_int32(ri_uint8 from)
    {
        ri_int32 to;

        to = (ri_int32)from;

        return to;
    }

    RI_API ri_uint32 ri_uint8_to_uint32(ri_uint8 from)
    {
        ri_uint32 to;

        //  if(from > RI_UINT32_MAX)
        //    to = RI_UINT32_MAX;
        //  else if(from < RI_UINT32_MIN)
        //    to = RI_UINT32_MIN;
        //  else
        to = (ri_uint32)from;

        return to;
    }

    RI_API ri_int64   ri_uint8_to_int64(ri_uint8 from)
    {
        ri_int64 to;

        to = (ri_int64)from;

        return to;
    }

    RI_API ri_uint64  ri_uint8_to_uint64(ri_uint8 from)
    {
        ri_uint64 to;

        //  if(from > RI_UINT64_MAX)
        //    to = RI_UINT64_MAX;
        //  else if(from < RI_UINT64_MIN)
        //    to = RI_UINT64_MIN;
        //  else
        to = (ri_uint64)from;

        return to;
    }

    RI_API long  ri_uint8_to_long(ri_uint8 from)
    {
        long to;

        to = (ri_long)from;

        return to;
    }

    RI_API ri_ulong  ri_uint8_to_ulong(ri_uint8 from)
    {
        ri_ulong to;

        to = (ri_ulong)from;

        return to;
    }

    RI_API ri_longlong  ri_uint8_to_longlong(ri_uint8 from)
    {
        ri_longlong to;

        to = (ri_longlong)from;

        return to;
    }

    RI_API ri_ulonglong  ri_uint8_to_ulonglong(ri_uint8 from)
    {
        ri_ulonglong to;

        to = (ri_ulonglong)from;

        return to;
    }

    RI_API size_t   ri_uint8_to_size(ri_uint8 from)
    {
        size_t to;

        //  if(from > RI_SIZE_MAX)
        //    to = RI_SIZE_MAX;
        //  else if(from < RI_SIZE_MIN)
        //    to = RI_SIZE_MIN;
        //  else
        to = (ri_size)from;

        return to;
    }

    RI_API ri_ssize  ri_uint8_to_ssize(ri_uint8 from)
    {
        ri_ssize to;

        to = (ri_ssize)from;

        return to;
    }

    RI_API float  ri_uint8_to_float(ri_uint8 from)
    {
        float to;

        if(from > RI_FLOAT_MAX)
            to = RI_FLOAT_MAX;
        else if(from < RI_FLOAT_MIN)
            to = RI_FLOAT_MIN;
        else
            to = (ri_float)from;

        return to;
    }

    RI_API ri_float32  ri_uint8_to_float32(ri_uint8 from)
    {
        ri_float32 to;

        if(from > RI_FLOAT32_MAX)
            to = RI_FLOAT32_MAX;
        else if(from < RI_FLOAT32_MIN)
            to = RI_FLOAT32_MIN;
        else
            to = (ri_float32)from;

        return to;
    }

    RI_API ri_float64  ri_uint8_to_float64(ri_uint8 from)
    {
        ri_float64 to;

        if(from > RI_FLOAT64_MAX)
            to = RI_FLOAT64_MAX;
        else if(from < RI_FLOAT64_MIN)
            to = RI_FLOAT64_MIN;
        else
            to = (ri_float64)from;

        return to;
    }

    RI_API double  ri_uint8_to_double(ri_uint8 from)
    {
        double to;

        if(from > RI_DOUBLE_MAX)
            to = RI_DOUBLE_MAX;
        else if(from < RI_DOUBLE_MIN)
            to = RI_DOUBLE_MIN;
        else
            to = (ri_double)from;

        return to;
    }


    RI_API int   ri_int16_to_int(ri_int16  from)
    {
        int to;

        //  if(from > RI_INT_MAX)
        //    to = RI_INT_MAX;
        //  else if(from < RI_INT_MIN)
        //    to = RI_INT_MIN;
        //  else
        to = (ri_int)from;

        return to;  
    }
    RI_API ri_uint   ri_int16_to_uint(ri_int16  from)
    {
        ri_uint to;

        //  if(from > RI_UINT_MAX)
        //    to = RI_UINT_MAX;
        if(from < RI_UINT_MIN)
            to = RI_UINT_MIN;
        else
            to = (ri_uint)from;

        return to;  
    }

    RI_API ri_int8  ri_int16_to_int8(ri_int16 from)
    {
        ri_int8 to;

        //  if(from > RI_INT8_MAX)
        //    to = RI_INT8_MAX;
        //  else if(from < RI_INT8_MIN)
        //    to = RI_INT8_MIN;
        //  else
        to = (ri_int8)from;

        return to;    
    }

    RI_API ri_uint8   ri_int16_to_uint8(ri_int16 from)
    {
        ri_uint8 to;

        if(from > RI_UINT8_MAX)
            to = RI_UINT8_MAX;
        else if(from < RI_UINT8_MIN)
            to = RI_UINT8_MIN;
        else
            to = (ri_uint8)from;

        return to;    
    }

    RI_API ri_uint16  ri_int16_to_uint16(ri_int16 from)
    {
        ri_uint16 to;

        //  if(from > RI_UINT16_MAX)
        //    to = RI_UINT16_MAX;
        if(from < RI_UINT16_MIN)
            to = RI_UINT16_MIN;
        else
            to = (ri_uint16)from;

        return to;
    }

    RI_API ri_int32  ri_int16_to_int32(ri_int16 from)
    {
        ri_int32 to;

        //  if(from > RI_INT32_MAX)
        //    to = RI_INT32_MAX;
        //  else if(from < RI_INT32_MIN)
        //    to = RI_INT32_MIN;
        //  else
        to = (ri_int32)from;

        return to;
    }

    RI_API ri_uint32 ri_int16_to_uint32(ri_int16 from)
    {
        ri_uint32 to;

        //  if(from > RI_UINT32_MAX)
        //    to = RI_UINT32_MAX;
        if(from < RI_UINT32_MIN)
            to = RI_UINT32_MIN;
        else
            to = (ri_uint32)from;

        return to;
    }

    RI_API ri_int64   ri_int16_to_int64(ri_int16 from)
    {
        ri_int64 to;

        //  if(from > RI_INT64_MAX)
        //    to = RI_INT64_MAX;
        //  else if(from < RI_INT64_MIN)
        //    to = RI_INT64_MIN;
        //  else
        to = (ri_int64)from;

        return to;
    }

    RI_API ri_uint64  ri_int16_to_uint64(ri_int16 from)
    {
        ri_uint64 to;

        //  if(from > RI_UINT64_MAX)
        //    to = RI_UINT64_MAX;
        if(from < RI_UINT64_MIN)
            to = RI_UINT64_MIN;
        else
            to = (ri_uint64)from;

        return to;
    }

    RI_API long  ri_int16_to_long(ri_int16 from)
    {
        long to;

        to = (ri_long)from;

        return to;
    }

    RI_API ri_ulong  ri_int16_to_ulong(ri_int16 from)
    {
        ri_ulong to;

        //  if(from > RI_ULONG_MAX)
        //    to = RI_ULONG_MAX;
        if(from < RI_ULONG_MIN)
            to = RI_ULONG_MIN;
        else
            to = (ri_ulong)from;

        return to;
    }

    RI_API ri_longlong  ri_int16_to_longlong(ri_int16 from)
    {
        ri_longlong to;

        to = (ri_longlong)from;

        return to;
    }

    RI_API ri_ulonglong  ri_int16_to_ulonglong(ri_int16 from)
    {
        ri_ulonglong to;

        //  if(from > RI_ULONGLONG_MAX)
        //    to = RI_ULONGLONG_MAX;
        if(from < RI_ULONGLONG_MIN)
            to = RI_ULONGLONG_MIN;
        else
            to = (ri_ulonglong)from;

        return to;
    }

    RI_API size_t   ri_int16_to_size(ri_int16 from)
    {
        size_t to;

        //  if(from > RI_SIZE_MAX)
        //    to = RI_SIZE_MAX;
        if(from < RI_SIZE_MIN)
            to = RI_SIZE_MIN;
        else
            to = (ri_size)from;

        return to;
    }

    RI_API ri_ssize  ri_int16_to_ssize(ri_int16 from)
    {
        ri_ssize to;

        //  if(from > RI_SSIZE_MAX)
        //    to = RI_SSIZE_MAX;
        if(from < RI_SSIZE_MIN)
            to = RI_SSIZE_MIN;
        else
            to = (ri_ssize)from;

        return to;
    }

    RI_API float  ri_int16_to_float(ri_int16 from)
    {
        float to;

        if(from > RI_FLOAT_MAX)
            to = RI_FLOAT_MAX;
        else if(from < RI_FLOAT_MIN)
            to = RI_FLOAT_MIN;
        else
            to = (ri_float)from;

        return to;
    }

    RI_API ri_float32  ri_int16_to_float32(ri_int16 from)
    {
        ri_float32 to;

        if(from > RI_FLOAT32_MAX)
            to = RI_FLOAT32_MAX;
        else if(from < RI_FLOAT32_MIN)
            to = RI_FLOAT32_MIN;
        else
            to = (ri_float32)from;

        return to;
    }

    RI_API ri_float64  ri_int16_to_float64(ri_int16 from)
    {
        ri_float64 to;

        if(from > RI_FLOAT64_MAX)
            to = RI_FLOAT64_MAX;
        else if(from < RI_FLOAT64_MIN)
            to = RI_FLOAT64_MIN;
        else
            to = (ri_float64)from;

        return to;
    }

    RI_API double  ri_int16_to_double(ri_int16 from)
    {
        double to;

        if(from > RI_DOUBLE_MAX)
            to = RI_DOUBLE_MAX;
        else if(from < RI_DOUBLE_MIN)
            to = RI_DOUBLE_MIN;
        else
            to = (ri_double)from;

        return to;
    }








    RI_API int   ri_uint16_to_int(ri_uint16  from)
    {
        int to;

        to = (ri_int)from;

        return to;  
    }
    RI_API ri_uint   ri_uint16_to_uint(ri_uint16  from)
    {
        ri_uint to;

        to = (ri_uint)from;

        return to;  
    }

    RI_API ri_int8  ri_uint16_to_int8(ri_uint16 from)
    {
        ri_int8 to;

        if(from > RI_INT8_MAX)
            to = RI_INT8_MAX;
        //  else if(from < RI_INT8_MIN)
        //    to = RI_INT8_MIN;
        else
            to = (ri_int8)from;

        return to;    
    }

    RI_API ri_uint8   ri_uint16_to_uint8(ri_uint16 from)
    {
        ri_uint8 to;

        if(from > RI_UINT8_MAX)
            to = RI_UINT8_MAX;
        //  else if(from < RI_UINT8_MIN)
        //    to = RI_UINT8_MIN;
        else
            to = (ri_uint8)from;

        return to;    
    }

    RI_API ri_int16  ri_uint16_to_int16(ri_uint16 from)
    {
        ri_int16 to;

        if(from > RI_INT16_MAX)
            to = RI_INT16_MAX;
        else
            to = (ri_int16)from;

        return to;
    }

    RI_API ri_int32  ri_uint16_to_int32(ri_uint16 from)
    {
        ri_int32 to;

        //  if(from > RI_INT32_MAX)
        //    to = RI_INT32_MAX;
        //  else if(from < RI_INT32_MIN)
        //    to = RI_INT32_MIN;
        //  else
        to = (ri_int32)from;

        return to;
    }

    RI_API ri_uint32 ri_uint16_to_uint32(ri_uint16 from)
    {
        ri_uint32 to;

        //  if(from > RI_UINT32_MAX)
        //    to = RI_UINT32_MAX;
        //  else if(from < RI_UINT32_MIN)
        //    to = RI_UINT32_MIN;
        //  else
        to = (ri_uint32)from;

        return to;
    }

    RI_API ri_int64   ri_uint16_to_int64(ri_uint16 from)
    {
        ri_int64 to;

        //  if(from > RI_INT64_MAX)
        //    to = RI_INT64_MAX;
        //  else if(from < RI_INT64_MIN)
        //    to = RI_INT64_MIN;
        //  else
        to = (ri_int64)from;

        return to;
    }

    RI_API ri_uint64  ri_uint16_to_uint64(ri_uint16 from)
    {
        ri_uint64 to;

        //  if(from > RI_UINT64_MAX)
        //    to = RI_UINT64_MAX;
        //  else if(from < RI_UINT64_MIN)
        //    to = RI_UINT64_MIN;
        //  else
        to = (ri_uint64)from;

        return to;
    }

    RI_API long  ri_uint16_to_long(ri_uint16 from)
    {
        long to;

        to = (ri_long)from;

        return to;
    }

    RI_API ri_ulong  ri_uint16_to_ulong(ri_uint16 from)
    {
        ri_ulong to;

        to = (ri_ulong)from;

        return to;
    }

    RI_API ri_longlong  ri_uint16_to_longlong(ri_uint16 from)
    {
        ri_longlong to;

        to = (ri_longlong)from;

        return to;
    }

    RI_API ri_ulonglong  ri_uint16_to_ulonglong(ri_uint16 from)
    {
        ri_ulonglong to;

        to = (ri_ulonglong)from;

        return to;
    }

    RI_API size_t   ri_uint16_to_size(ri_uint16 from)
    {
        size_t to;

        //  if(from > RI_SIZE_MAX)
        //    to = RI_SIZE_MAX;
        //  else if(from < RI_SIZE_MIN)
        //    to = RI_SIZE_MIN;
        //  else
        to = (ri_size)from;

        return to;
    }

    RI_API ri_ssize  ri_uint16_to_ssize(ri_uint16 from)
    {
        ri_ssize to;

        //  if(from > RI_SSIZE_MAX)
        //    to = RI_SSIZE_MAX;
        //  else if(from < RI_SSIZE_MIN)
        //    to = RI_SSIZE_MIN;
        //  else
        to = (ri_ssize)from;

        return to;
    }

    RI_API float  ri_uint16_to_float(ri_uint16 from)
    {
        float to;

        if(from > RI_FLOAT_MAX)
            to = RI_FLOAT_MAX;
        else if(from < RI_FLOAT_MIN)
            to = RI_FLOAT_MIN;
        else
            to = (ri_float)from;

        return to;
    }

    RI_API ri_float32  ri_uint16_to_float32(ri_uint16 from)
    {
        ri_float32 to;

        if(from > RI_FLOAT32_MAX)
            to = RI_FLOAT32_MAX;
        else if(from < RI_FLOAT32_MIN)
            to = RI_FLOAT32_MIN;
        else
            to = (ri_float32)from;

        return to;
    }

    RI_API ri_float64  ri_uint16_to_float64(ri_uint16 from)
    {
        ri_float64 to;

        if(from > RI_FLOAT64_MAX)
            to = RI_FLOAT64_MAX;
        else if(from < RI_FLOAT64_MIN)
            to = RI_FLOAT64_MIN;
        else
            to = (ri_float64)from;

        return to;
    }

    RI_API double  ri_uint16_to_double(ri_uint16 from)
    {
        double to;

        if(from > RI_DOUBLE_MAX)
            to = RI_DOUBLE_MAX;
        else if(from < RI_DOUBLE_MIN)
            to = RI_DOUBLE_MIN;
        else
            to = (ri_double)from;

        return to;
    }






    RI_API int   ri_int32_to_int(ri_int32  from)
    {
        int to;

        if(from > RI_INT_MAX)
            to = (ri_int)RI_INT_MAX;
        else if(from < RI_INT_MIN)
            to = (ri_int)RI_INT_MIN;
        else
            to = (ri_int)from;

        return to;  
    }

    RI_API ri_uint   ri_int32_to_uint(ri_int32  from)
    {
        ri_uint to;

        //  if(from > RI_UINT_MAX)
        //    to = RI_UINT_MAX;
        if(from < RI_UINT_MIN)
            to = RI_UINT_MIN;
        else
            to = (ri_uint)from;

        return to;  
    }

    RI_API ri_int8  ri_int32_to_int8(ri_int32 from)
    {
        ri_int8 to;

        if(from > RI_INT8_MAX)
            to = RI_INT8_MAX;
        else if(from < RI_INT8_MIN)
            to = RI_INT8_MIN;
        else
            to = (ri_int8)from;

        return to;    
    }

    RI_API ri_uint8   ri_int32_to_uint8(ri_int32 from)
    {
        ri_uint8 to;

        if(from > RI_UINT8_MAX)
            to = RI_UINT8_MAX;
        else if(from < RI_UINT8_MIN)
            to = RI_UINT8_MIN;
        else
            to = (ri_uint8)from;

        return to;    
    }

    RI_API ri_int16  ri_int32_to_int16(ri_int32 from)
    {
        ri_int16 to;

        if(from > RI_INT16_MAX)
            to = RI_INT16_MAX;
        else if(from < RI_INT16_MIN)
            to = RI_INT16_MIN;
        else
            to = (ri_int16)from;

        return to;
    }

    RI_API ri_uint16  ri_int32_to_uint16(ri_int32 from)
    {
        ri_uint16 to;

        if(from > RI_UINT16_MAX)
            to = RI_UINT16_MAX;
        else if(from < RI_UINT16_MIN)
            to = RI_UINT16_MIN;
        else
            to = (ri_uint16)from;

        return to;
    }

    RI_API ri_uint32 ri_int32_to_uint32(ri_int32 from)
    {
        ri_uint32 to;

        //  if(from > RI_UINT32_MAX)
        //    to = RI_UINT32_MAX;
        if(from < RI_UINT32_MIN)
            to = RI_UINT32_MIN;
        else
            to = (ri_uint32)from;

        return to;
    }

    RI_API ri_int64   ri_int32_to_int64(ri_int32 from)
    {
        ri_int64 to;

        //  if(from > RI_INT64_MAX)
        //    to = RI_INT64_MAX;
        //  else if(from < RI_INT64_MIN)
        //    to = RI_INT64_MIN;
        //  else
        to = (ri_int64)from;

        return to;
    }

    RI_API ri_uint64  ri_int32_to_uint64(ri_int32 from)
    {
        ri_uint64 to;

        //  if(from > RI_UINT64_MAX)
        //    to = RI_UINT64_MAX;
        if(from < RI_UINT64_MIN)
            to = RI_UINT64_MIN;
        else
            to = (ri_uint64)from;

        return to;
    }

    RI_API long  ri_int32_to_long(ri_int32 from)
    {
        long to;

        if(from > RI_LONG_MAX)
            to = RI_LONG_MAX;
        else if(from < RI_LONG_MIN)
            to = RI_LONG_MIN;
        else
            to = (ri_long)from;

        return to;
    }

    RI_API ri_ulong  ri_int32_to_ulong(ri_int32 from)
    {
        ri_ulong to;

        //  if(from > RI_ULONG_MAX)
        //    to = RI_ULONG_MAX;
        if(from < RI_ULONG_MIN)
            to = RI_ULONG_MIN;
        else
            to = (ri_ulong)from;

        return to;
    }

    RI_API ri_longlong  ri_int32_to_longlong(ri_int32 from)
    {
        ri_longlong to;

        to = (ri_longlong)from;

        return to;
    }

    RI_API ri_ulonglong  ri_int32_to_ulonglong(ri_int32 from)
    {
        ri_ulonglong to;

        //  if(from > RI_ULONGLONG_MAX)
        //    to = RI_ULONGLONG_MAX;
        if(from < RI_ULONGLONG_MIN)
            to = RI_ULONGLONG_MIN;
        else
            to = (ri_ulonglong)from;

        return to;
    }

    RI_API size_t   ri_int32_to_size(ri_int32 from)
    {
        size_t to;

        //  if(from > RI_SIZE_MAX)
        //    to = RI_SIZE_MAX;
        if(from < RI_SIZE_MIN)
            to = RI_SIZE_MIN;
        else
            to = (ri_size)from;

        return to;
    }

    RI_API ri_ssize  ri_int32_to_ssize(ri_int32 from)
    {
        ri_ssize to;

        if(from > RI_SSIZE_MAX)
            to = RI_SSIZE_MAX;
        else if(from < RI_SSIZE_MIN)
            to = RI_SSIZE_MIN;
        else
            to = (ri_ssize)from;

        return to;
    }

    RI_API float  ri_int32_to_float(ri_int32 from)
    {
        float to;

        if(from > RI_FLOAT_MAX)
            to = RI_FLOAT_MAX;
        else if(from < RI_FLOAT_MIN)
            to = RI_FLOAT_MIN;
        else
            to = (ri_float)from;

        return to;
    }

    RI_API ri_float32  ri_int32_to_float32(ri_int32 from)
    {
        ri_float32 to;

        if(from > RI_FLOAT32_MAX)
            to = RI_FLOAT32_MAX;
        else if(from < RI_FLOAT32_MIN)
            to = RI_FLOAT32_MIN;
        else
            to = (ri_float32)from;

        return to;
    }

    RI_API ri_float64  ri_int32_to_float64(ri_int32 from)
    {
        ri_float64 to;

        if(from > RI_FLOAT64_MAX)
            to = RI_FLOAT64_MAX;
        else if(from < RI_FLOAT64_MIN)
            to = RI_FLOAT64_MIN;
        else
            to = (ri_float64)from;

        return to;
    }

    RI_API double  ri_int32_to_double(ri_int32 from)
    {
        double to;

        if(from > RI_DOUBLE_MAX)
            to = RI_DOUBLE_MAX;
        else if(from < RI_DOUBLE_MIN)
            to = RI_DOUBLE_MIN;
        else
            to = (ri_double)from;

        return to;
    }






    RI_API int   ri_uint32_to_int(ri_uint32  from)
    {
        int to;

        if(from > RI_INT_MAX)
            to = (ri_int)RI_INT_MAX;
        else
            to = (ri_int)from;

        return to;  
    }

    RI_API ri_uint   ri_uint32_to_uint(ri_uint32  from)
    {
        ri_uint to;

        if(from > RI_UINT_MAX)
            to = (ri_int)RI_UINT_MAX;
        else if(from < RI_UINT_MIN)
            to = (ri_int)RI_UINT_MIN;
        else
            to = (ri_uint)from;

        return to;  
    }

    RI_API ri_int8  ri_uint32_to_int8(ri_uint32 from)
    {
        ri_int8 to;

        if(from > RI_INT8_MAX)
            to = RI_INT8_MAX;
        else
            to = (ri_int8)from;

        return to;    
    }

    RI_API ri_uint8   ri_uint32_to_uint8(ri_uint32 from)
    {
        ri_uint8 to;

        if(from > RI_UINT8_MAX)
            to = RI_UINT8_MAX;
        else if(from < RI_UINT8_MIN)
            to = RI_UINT8_MIN;
        else
            to = (ri_uint8)from;

        return to;    
    }

    RI_API ri_int16  ri_uint32_to_int16(ri_uint32 from)
    {
        ri_int16 to;

        if(from > RI_INT16_MAX)
            to = RI_INT16_MAX;
        else
            to = (ri_int16)from;

        return to;
    }

    RI_API ri_uint16  ri_uint32_to_uint16(ri_uint32 from)
    {
        ri_uint16 to;

        if(from > RI_UINT16_MAX)
            to = RI_UINT16_MAX;
        else if(from < RI_UINT16_MIN)
            to = RI_UINT16_MIN;
        else
            to = (ri_uint16)from;

        return to;
    }

    RI_API ri_int32 ri_uint32_to_int32(ri_uint32 from)
    {
        ri_int32 to;

        if(from > RI_INT32_MAX)
            to = RI_INT32_MAX;
        else
            to = (ri_int32)from;

        return to;
    }

    RI_API ri_int64   ri_uint32_to_int64(ri_uint32 from)
    {
        ri_int64 to;

        to = (ri_int64)from;

        return to;
    }

    RI_API ri_uint64  ri_uint32_to_uint64(ri_uint32 from)
    {
        ri_uint64 to;

        //  if(from > RI_UINT64_MAX)
        //    to = RI_UINT64_MAX;
        if(from < RI_UINT64_MIN)
            to = RI_UINT64_MIN;
        else
            to = (ri_uint64)from;

        return to;
    }

    RI_API long  ri_uint32_to_long(ri_uint32 from)
    {
        long to;

        if(from > RI_LONG_MAX)
            to = RI_LONG_MAX;
        else
            to = (ri_long)from;

        return to;
    }

    RI_API ri_ulong  ri_uint32_to_ulong(ri_uint32 from)
    {
        ri_ulong to;

        if(from > RI_ULONG_MAX)
            to = RI_ULONG_MAX;
        else if(from < RI_ULONG_MIN)
            to = RI_ULONG_MIN;
        else
            to = (ri_ulong)from;

        return to;
    }

    RI_API ri_longlong  ri_uint32_to_longlong(ri_uint32 from)
    {
        ri_longlong to;

        to = (ri_longlong)from;

        return to;
    }

    RI_API ri_ulonglong  ri_uint32_to_ulonglong(ri_uint32 from)
    {
        ri_ulonglong to;

        to = (ri_ulonglong)from;

        return to;
    }

    RI_API size_t   ri_uint32_to_size(ri_uint32 from)
    {
        size_t to;

        if(from > RI_SIZE_MAX)
            to = RI_SIZE_MAX;
        else if(from < RI_SIZE_MIN)
            to = RI_SIZE_MIN;
        else
            to = (ri_size)from;

        return to;
    }

    RI_API ri_ssize  ri_uint32_to_ssize(ri_uint32 from)
    {
        ri_ssize to;

        if(from > RI_SSIZE_MAX)
            to = RI_SSIZE_MAX;
        else
            to = (ri_ssize)from;

        return to;
    }

    RI_API float  ri_uint32_to_float(ri_uint32 from)
    {
        float to;

        if(from > RI_FLOAT_MAX)
            to = RI_FLOAT_MAX;
        else if(from < RI_FLOAT_MIN)
            to = RI_FLOAT_MIN;
        else
            to = (ri_float)from;

        return to;
    }

    RI_API ri_float32  ri_uint32_to_float32(ri_uint32 from)
    {
        ri_float32 to;

        if(from > RI_FLOAT32_MAX)
            to = RI_FLOAT32_MAX;
        else if(from < RI_FLOAT32_MIN)
            to = RI_FLOAT32_MIN;
        else
            to = (ri_float32)from;

        return to;
    }

    RI_API ri_float64  ri_uint32_to_float64(ri_uint32 from)
    {
        ri_float64 to;

        if(from > RI_FLOAT64_MAX)
            to = RI_FLOAT64_MAX;
        else if(from < RI_FLOAT64_MIN)
            to = RI_FLOAT64_MIN;
        else
            to = (ri_float64)from;

        return to;
    }

    RI_API double  ri_uint32_to_double(ri_uint32 from)
    {
        double to;

        if(from > RI_DOUBLE_MAX)
            to = RI_DOUBLE_MAX;
        else if(from < RI_DOUBLE_MIN)
            to = RI_DOUBLE_MIN;
        else
            to = (ri_double)from;

        return to;
    }




    RI_API int   ri_int64_to_int(ri_int64  from)
    {
        int to;

        if(from > RI_INT_MAX)
            to = (ri_int)RI_INT_MAX;
        else if(from < RI_INT_MIN)
            to = (ri_int)RI_INT_MIN;
        else
            to = (ri_int)from;

        return to;  
    }

    RI_API ri_int8  ri_int64_to_int8(ri_int64 from)
    {
        ri_int8 to;

        if(from > RI_INT8_MAX)
            to = RI_INT8_MAX;
        else if(from < RI_INT8_MIN)
            to = RI_INT8_MIN;
        else
            to = (ri_int8)from;

        return to;    
    }

    RI_API ri_uint   ri_int64_to_uint(ri_int64  from)
    {
        ri_uint to;

        if(from > RI_UINT_MAX)
            to = (ri_int)RI_UINT_MAX;
        else if(from < RI_UINT_MIN)
            to = (ri_int)RI_UINT_MIN;
        else
            to = (ri_uint)from;

        return to;  
    }

    RI_API ri_uint8   ri_int64_to_uint8(ri_int64 from)
    {
        ri_uint8 to;

        if(from > RI_UINT8_MAX)
            to = RI_UINT8_MAX;
        else if(from < RI_UINT8_MIN)
            to = RI_UINT8_MIN;
        else
            to = (ri_uint8)from;

        return to;    
    }

    RI_API ri_int16  ri_int64_to_int16(ri_int64 from)
    {
        ri_int16 to;

        if(from > RI_INT16_MAX)
            to = RI_INT16_MAX;
        else if(from < RI_INT16_MIN)
            to = RI_INT16_MIN;
        else
            to = (ri_int16)from;

        return to;
    }

    RI_API ri_uint16  ri_int64_to_uint16(ri_int64 from)
    {
        ri_uint16 to;

        if(from > RI_UINT16_MAX)
            to = RI_UINT16_MAX;
        else if(from < RI_UINT16_MIN)
            to = RI_UINT16_MIN;
        else
            to = (ri_uint16)from;

        return to;
    }

    RI_API ri_int32 ri_int64_to_int32(ri_int64 from)
    {
        ri_int32 to;

        if(from > RI_INT32_MAX)
            to = RI_INT32_MAX;
        else if(from < RI_INT32_MIN)
            to = RI_INT32_MIN;
        else
            to = (ri_int32)from;

        return to;
    }

    RI_API ri_uint32   ri_int64_to_uint32(ri_int64 from)
    {
        ri_uint32 to;

        if(from > RI_UINT32_MAX)
            to = RI_UINT32_MAX;
        else if(from < RI_UINT32_MIN)
            to = RI_UINT32_MIN;
        else
            to = (ri_uint32)from;

        return to;
    }

    RI_API ri_uint64  ri_int64_to_uint64(ri_int64 from)
    {
        ri_uint64 to;

        //  if(from > RI_UINT64_MAX)
        //    to = RI_UINT64_MAX;
        if(from < RI_UINT64_MIN)
            to = RI_UINT64_MIN;
        else
            to = (ri_uint64)from;

        return to;
    }

    RI_API long  ri_int64_to_long(ri_int64 from)
    {
        long to;

        if(from > RI_LONG_MAX)
            to = RI_LONG_MAX;
        else if(from < RI_LONG_MIN)
            to = RI_LONG_MIN;
        else
            to = (ri_long)from;

        return to;
    }

    RI_API ri_ulong  ri_int64_to_ulong(ri_int64 from)
    {
        ri_ulong to;

        if(from > RI_ULONG_MAX)
            to = RI_ULONG_MAX;
        else if(from < RI_ULONG_MIN)
            to = RI_ULONG_MIN;
        else
            to = (ri_ulong)from;

        return to;
    }

    RI_API ri_longlong  ri_int64_to_longlong(ri_int64 from)
    {
        ri_longlong to;

        if(from > RI_LONGLONG_MAX)
            to = RI_LONGLONG_MAX;
        else if(from < RI_LONGLONG_MIN)
            to = RI_LONGLONG_MIN;
        else
            to = (ri_longlong)from;

        return to;
    }

    RI_API ri_ulonglong  ri_int64_to_ulonglong(ri_int64 from)
    {
        ri_ulonglong to;

        //  if(from > RI_ULONGLONG_MAX)
        //    to = RI_ULONGLONG_MAX;
        if(from < RI_ULONGLONG_MIN)
            to = RI_ULONGLONG_MIN;
        else
            to = (ri_ulonglong)from;

        return to;
    }

    RI_API size_t   ri_int64_to_size(ri_int64 from)
    {
        size_t to;

        if(from > RI_SIZE_MAX)
            to = RI_SIZE_MAX;
        else if(from < RI_SIZE_MIN)
            to = RI_SIZE_MIN;
        else
            to = (ri_size)from;

        return to;
    }

    RI_API ri_ssize  ri_int64_to_ssize(ri_int64 from)
    {
        ri_ssize to;

        if(from > RI_SSIZE_MAX)
            to = RI_SSIZE_MAX;
        else if(from < RI_SSIZE_MIN)
            to = RI_SSIZE_MIN;
        else
            to = (ri_ssize)from;

        return to;
    }

    RI_API float  ri_int64_to_float(ri_int64 from)
    {
        float to;

        if(from > RI_FLOAT_MAX)
            to = RI_FLOAT_MAX;
        else if(from < RI_FLOAT_MIN)
            to = RI_FLOAT_MIN;
        else
            to = (ri_float)from;

        return to;
    }

    RI_API ri_float32  ri_int64_to_float32(ri_int64 from)
    {
        ri_float32 to;

        if(from > RI_FLOAT32_MAX)
            to = RI_FLOAT32_MAX;
        else if(from < RI_FLOAT32_MIN)
            to = RI_FLOAT32_MIN;
        else
            to = (ri_float32)from;

        return to;
    }

    RI_API ri_float64  ri_int64_to_float64(ri_int64 from)
    {
        ri_float64 to;

        if(from > RI_FLOAT64_MAX)
            to = RI_FLOAT64_MAX;
        else if(from < RI_FLOAT64_MIN)
            to = RI_FLOAT64_MIN;
        else
            to = (ri_float64)from;

        return to;
    }

    RI_API double  ri_int64_to_double(ri_int64 from)
    {
        double to;

        if(from > RI_DOUBLE_MAX)
            to = RI_DOUBLE_MAX;
        else if(from < RI_DOUBLE_MIN)
            to = RI_DOUBLE_MIN;
        else
            to = (ri_double)from;

        return to;
    }




    RI_API int   ri_uint64_to_int(ri_uint64  from)
    {
        int to;

        if(from > RI_INT_MAX)
            to = (ri_int)RI_INT_MAX;
        else
            to = (ri_int)from;

        return to;  
    }
    RI_API ri_uint   ri_uint64_to_uint(ri_uint64  from)
    {
        ri_uint to;

        if(from > RI_UINT_MAX)
            to = (ri_int)RI_UINT_MAX;
        else if(from < RI_UINT_MIN)
            to = (ri_int)RI_UINT_MIN;
        else
            to = (ri_uint)from;

        return to;  
    }

    RI_API ri_int8  ri_uint64_to_int8(ri_uint64 from)
    {
        ri_int8 to;

        if(from > RI_INT8_MAX)
            to = RI_INT8_MAX;
        else
            to = (ri_int8)from;

        return to;    
    }

    RI_API ri_uint8   ri_uint64_to_uint8(ri_uint64 from)
    {
        ri_uint8 to;

        if(from > RI_UINT8_MAX)
            to = RI_UINT8_MAX;
        else if(from < RI_UINT8_MIN)
            to = RI_UINT8_MIN;
        else
            to = (ri_uint8)from;

        return to;    
    }



    RI_API ri_int16  ri_uint64_to_int16(ri_uint64 from)
    {
        ri_int16 to;

        if(from > RI_INT16_MAX)
            to = RI_INT16_MAX;
        else
            to = (ri_int16)from;

        return to;
    }

    RI_API ri_uint16  ri_uint64_to_uint16(ri_uint64 from)
    {
        ri_uint16 to;

        if(from > RI_UINT16_MAX)
            to = RI_UINT16_MAX;
        else if(from < RI_UINT16_MIN)
            to = RI_UINT16_MIN;
        else
            to = (ri_uint16)from;

        return to;
    }

    RI_API ri_int32 ri_uint64_to_int32(ri_uint64 from)
    {
        ri_int32 to;

        if(from > RI_INT32_MAX)
            to = RI_INT32_MAX;
        else
            to = (ri_int32)from;

        return to;
    }

    RI_API ri_uint32   ri_uint64_to_uint32(ri_uint64 from)
    {
        ri_uint32 to;

        if(from > RI_UINT32_MAX)
            to = RI_UINT32_MAX;
        else if(from < RI_UINT32_MIN)
            to = RI_UINT32_MIN;
        else
            to = (ri_uint32)from;

        return to;
    }

    RI_API ri_int64  ri_uint64_to_int64(ri_uint64 from)
    {
        ri_int64 to;

        if(from > RI_INT64_MAX)
            to = RI_INT64_MAX;
        else
            to = (ri_int64)from;

        return to;
    }

    RI_API long  ri_uint64_to_long(ri_uint64 from)
    {
        long to;

        if(from > RI_LONG_MAX)
            to = RI_LONG_MAX;
        else
            to = (ri_long)from;

        return to;
    }

    RI_API ri_ulong  ri_uint64_to_ulong(ri_uint64 from)
    {
        ri_ulong to;

        if(from > RI_ULONG_MAX)
            to = RI_ULONG_MAX;
        else if(from < RI_ULONG_MIN)
            to = RI_ULONG_MIN;
        else
            to = (ri_ulong)from;

        return to;
    }

    RI_API ri_longlong  ri_uint64_to_longlong(ri_uint64 from)
    {
        ri_longlong to;

        if(from > RI_LONGLONG_MAX)
            to = RI_LONGLONG_MAX;
        else
            to = (ri_longlong)from;

        return to;
    }

    RI_API ri_ulonglong  ri_uint64_to_ulonglong(ri_uint64 from)
    {
        ri_ulonglong to;

        if(from > RI_ULONGLONG_MAX)
            to = RI_ULONGLONG_MAX;
        else if(from < RI_ULONGLONG_MIN)
            to = RI_ULONGLONG_MIN;
        else
            to = (ri_ulonglong)from;

        return to;
    }

    RI_API size_t   ri_uint64_to_size(ri_uint64 from)
    {
        size_t to;

        if(from > RI_SIZE_MAX)
            to = RI_SIZE_MAX;
        else if(from < RI_SIZE_MIN)
            to = RI_SIZE_MIN;
        else
            to = (ri_size)from;

        return to;
    }

    RI_API ri_ssize  ri_uint64_to_ssize(ri_uint64 from)
    {
        ri_ssize to;

        if(from > RI_SSIZE_MAX)
            to = RI_SSIZE_MAX;
        else
            to = (ri_ssize)from;

        return to;
    }

    RI_API float  ri_uint64_to_float(ri_uint64 from)
    {
        float to;

        if(from > RI_FLOAT_MAX)
            to = RI_FLOAT_MAX;
        else if(from < RI_FLOAT_MIN)
            to = RI_FLOAT_MIN;
        else
            to = (ri_float)from;

        return to;
    }

    RI_API ri_float32  ri_uint64_to_float32(ri_uint64 from)
    {
        ri_float32 to;

        if(from > RI_FLOAT32_MAX)
            to = RI_FLOAT32_MAX;
        else if(from < RI_FLOAT32_MIN)
            to = RI_FLOAT32_MIN;
        else
            to = (ri_float32)from;

        return to;
    }

    RI_API ri_float64  ri_uint64_to_float64(ri_uint64 from)
    {
        ri_float64 to;

        if(from > RI_FLOAT64_MAX)
            to = RI_FLOAT64_MAX;
        else if(from < RI_FLOAT64_MIN)
            to = RI_FLOAT64_MIN;
        else
            to = (ri_float64)from;

        return to;
    }

    RI_API double  ri_uint64_to_double(ri_uint64 from)
    {
        double to;

        if(from > RI_DOUBLE_MAX)
            to = RI_DOUBLE_MAX;
        else if(from < RI_DOUBLE_MIN)
            to = RI_DOUBLE_MIN;
        else
            to = (ri_double)from;

        return to;
    }






    RI_API int   ri_long_to_int(long  from)
    {
        int to;

        if(from > RI_INT_MAX)
            to = (ri_int)RI_INT_MAX;
        else if(from < RI_INT_MIN)
            to = (ri_int)RI_INT_MIN;
        else
            to = (ri_int)from;

        return to;  
    }

    RI_API ri_uint   ri_long_to_uint(long  from)
    {
        ri_uint to;

        //  if(from > RI_UINT_MAX)
        //    to = RI_UINT_MAX;
        if(from < RI_UINT_MIN)
            to = RI_UINT_MIN;
        else
            to = (ri_uint)from;

        return to;  
    }

    RI_API ri_int8  ri_long_to_int8(long from)
    {
        ri_int8 to;

        if(from > RI_INT8_MAX)
            to = RI_INT8_MAX;
        else if(from < RI_INT8_MIN)
            to = RI_INT8_MIN;
        else
            to = (ri_int8)from;

        return to;    
    }

    RI_API ri_uint8   ri_long_to_uint8(long from)
    {
        ri_uint8 to;

        if(from > RI_UINT8_MAX)
            to = RI_UINT8_MAX;
        else if(from < RI_UINT8_MIN)
            to = RI_UINT8_MIN;
        else
            to = (ri_uint8)from;

        return to;    
    }

    RI_API ri_int16  ri_long_to_int16(long from)
    {
        ri_int16 to;

        if(from > RI_INT16_MAX)
            to = RI_INT16_MAX;
        else if(from < RI_INT16_MIN)
            to = RI_INT16_MIN;
        else
            to = (ri_int16)from;

        return to;
    }

    RI_API ri_uint16  ri_long_to_uint16(long from)
    {
        ri_uint16 to;

        if(from > RI_UINT16_MAX)
            to = RI_UINT16_MAX;
        else if(from < RI_UINT16_MIN)
            to = RI_UINT16_MIN;
        else
            to = (ri_uint16)from;

        return to;
    }

    RI_API ri_int32 ri_long_to_int32(long from)
    {
        ri_int32 to;

        if(from > RI_INT32_MAX)
            to = RI_INT32_MAX;
        else if(from < RI_INT32_MIN)
            to = RI_INT32_MIN;
        else
            to = (ri_int32)from;

        return to;
    }

    RI_API ri_uint32   ri_long_to_uint32(long from)
    {
        ri_uint32 to;

        //  if(from > RI_UINT32_MAX)
        //    to = RI_UINT32_MAX;
        if(from < RI_UINT32_MIN)
            to = RI_UINT32_MIN;
        else
            to = (ri_uint32)from;

        return to;
    }

    RI_API ri_int64  ri_long_to_int64(long from)
    {
        ri_int64 to;

        to = (ri_int64)from;

        return to;
    }

    RI_API ri_uint64  ri_long_to_uint64(long from)
    {
        ri_uint64 to;

        //  if(from > RI_UINT64_MAX)
        //    to = RI_UINT64_MAX;
        if(from < RI_UINT64_MIN)
            to = RI_UINT64_MIN;
        else
            to = (ri_uint64)from;

        return to;
    }

    RI_API ri_ulong  ri_long_to_ulong(long from)
    {
        ri_ulong to;

        //  if(from > RI_ULONG_MAX)
        //    to = RI_ULONG_MAX;
        if(from < RI_ULONG_MIN)
            to = RI_ULONG_MIN;
        else
            to = (ri_ulong)from;

        return to;
    }

    RI_API ri_longlong  ri_long_to_longlong(long from)
    {
        ri_longlong to;

        to = (ri_longlong)from;

        return to;
    }

    RI_API ri_ulonglong  ri_long_to_ulonglong(long from)
    {
        ri_ulonglong to;

        //  if(from > RI_ULONGLONG_MAX)
        //    to = RI_ULONGLONG_MAX;
        if(from < RI_ULONGLONG_MIN)
            to = RI_ULONGLONG_MIN;
        else
            to = (ri_ulonglong)from;

        return to;
    }

    RI_API size_t   ri_long_to_size(long from)
    {
        size_t to;

        //  if(from > RI_SIZE_MAX)
        //    to = RI_SIZE_MAX;
        if(from < RI_SIZE_MIN)
            to = RI_SIZE_MIN;
        else
            to = (ri_size)from;

        return to;
    }

    RI_API ri_ssize  ri_long_to_ssize(long from)
    {
        ri_ssize to;

        if(from > RI_SSIZE_MAX)
            to = RI_SSIZE_MAX;
        else if(from < RI_SSIZE_MIN)
            to = RI_SSIZE_MIN;
        else
            to = (ri_ssize)from;

        return to;
    }

    RI_API float  ri_long_to_float(long from)
    {
        float to;

        if(from > RI_FLOAT_MAX)
            to = RI_FLOAT_MAX;
        else if(from < RI_FLOAT_MIN)
            to = RI_FLOAT_MIN;
        else
            to = (ri_float)from;

        return to;
    }

    RI_API ri_float32  ri_long_to_float32(long from)
    {
        ri_float32 to;

        if(from > RI_FLOAT32_MAX)
            to = RI_FLOAT32_MAX;
        else if(from < RI_FLOAT32_MIN)
            to = RI_FLOAT32_MIN;
        else
            to = (ri_float32)from;

        return to;
    }

    RI_API ri_float64  ri_long_to_float64(long from)
    {
        ri_float64 to;

        if(from > RI_FLOAT64_MAX)
            to = RI_FLOAT64_MAX;
        else if(from < RI_FLOAT64_MIN)
            to = RI_FLOAT64_MIN;
        else
            to = (ri_float64)from;

        return to;
    }

    RI_API double  ri_long_to_double(long from)
    {
        double to;

        if(from > RI_DOUBLE_MAX)
            to = RI_DOUBLE_MAX;
        else if(from < RI_DOUBLE_MIN)
            to = RI_DOUBLE_MIN;
        else
            to = (ri_double)from;

        return to;
    }






    RI_API int   ri_ulong_to_int(ri_ulong  from)
    {
        int to;

        if(from > RI_INT_MAX)
            to = (ri_int)RI_INT_MAX;
        else
            to = (ri_int)from;

        return to;  
    }

    RI_API ri_uint   ri_ulong_to_uint(ri_ulong  from)
    {
        ri_uint to;

        if(from > RI_UINT_MAX)
            to = (ri_int)RI_UINT_MAX;
        else if(from < RI_UINT_MIN)
            to = (ri_int)RI_UINT_MIN;
        else
            to = (ri_uint)from;

        return to;  
    }

    RI_API ri_int8  ri_ulong_to_int8(ri_ulong from)
    {
        ri_int8 to;

        if(from > RI_INT8_MAX)
            to = RI_INT8_MAX;
        else
            to = (ri_int8)from;

        return to;    
    }

    RI_API ri_uint8   ri_ulong_to_uint8(ri_ulong from)
    {
        ri_uint8 to;

        if(from > RI_UINT8_MAX)
            to = RI_UINT8_MAX;
        else if(from < RI_UINT8_MIN)
            to = RI_UINT8_MIN;
        else
            to = (ri_uint8)from;

        return to;    
    }

    RI_API ri_int16  ri_ulong_to_int16(ri_ulong from)
    {
        ri_int16 to;

        if(from > RI_INT16_MAX)
            to = RI_INT16_MAX;
        else
            to = (ri_int16)from;

        return to;
    }

    RI_API ri_uint16  ri_ulong_to_uint16(ri_ulong from)
    {
        ri_uint16 to;

        if(from > RI_UINT16_MAX)
            to = RI_UINT16_MAX;
        else if(from < RI_UINT16_MIN)
            to = RI_UINT16_MIN;
        else
            to = (ri_uint16)from;

        return to;
    }

    RI_API ri_int32 ri_ulong_to_int32(ri_ulong from)
    {
        ri_int32 to;

        if(from > RI_INT32_MAX)
            to = RI_INT32_MAX;
        else
            to = (ri_int32)from;

        return to;
    }

    RI_API ri_uint32   ri_ulong_to_uint32(ri_ulong from)
    {
        ri_uint32 to;

        if(from > RI_UINT32_MAX)
            to = RI_UINT32_MAX;
        else if(from < RI_UINT32_MIN)
            to = RI_UINT32_MIN;
        else
            to = (ri_uint32)from;

        return to;
    }

    RI_API ri_int64  ri_ulong_to_int64(ri_ulong from)
    {
        ri_int64 to;

        to = (ri_int64)from;

        return to;
    }

    RI_API ri_uint64  ri_ulong_to_uint64(ri_ulong from)
    {
        ri_uint64 to;

        to = (ri_uint64)from;

        return to;
    }

    RI_API long  ri_ulong_to_long(ri_ulong from)
    {
        long to;

        if(from > RI_LONG_MAX)
            to = RI_LONG_MAX;
        else
            to = (ri_long)from;

        return to;
    }

    RI_API ri_longlong  ri_ulong_to_longlong(ri_ulong from)
    {
        ri_longlong to;

        to = (ri_longlong)from;

        return to;
    }

    RI_API ri_ulonglong  ri_ulong_to_ulonglong(ri_ulong from)
    {
        ri_ulonglong to;

        to = (ri_ulonglong)from;

        return to;
    }

    RI_API size_t   ri_ulong_to_size(ri_ulong from)
    {
        size_t to;

        if(from > RI_SIZE_MAX)
            to = RI_SIZE_MAX;
        else if(from < RI_SIZE_MIN)
            to = RI_SIZE_MIN;
        else
            to = (ri_size)from;

        return to;
    }

    RI_API ri_ssize  ri_ulong_to_ssize(ri_ulong from)
    {
        ri_ssize to;

        if(from > RI_SSIZE_MAX)
            to = RI_SSIZE_MAX;
        else
            to = (ri_ssize)from;

        return to;
    }

    RI_API float  ri_ulong_to_float(ri_ulong from)
    {
        float to;

        if(from > RI_FLOAT_MAX)
            to = RI_FLOAT_MAX;
        else if(from < RI_FLOAT_MIN)
            to = RI_FLOAT_MIN;
        else
            to = (ri_float)from;

        return to;
    }

    RI_API ri_float32  ri_ulong_to_float32(ri_ulong from)
    {
        ri_float32 to;

        if(from > RI_FLOAT32_MAX)
            to = RI_FLOAT32_MAX;
        else if(from < RI_FLOAT32_MIN)
            to = RI_FLOAT32_MIN;
        else
            to = (ri_float32)from;

        return to;
    }

    RI_API ri_float64  ri_ulong_to_float64(ri_ulong from)
    {
        ri_float64 to;

        if(from > RI_FLOAT64_MAX)
            to = RI_FLOAT64_MAX;
        else if(from < RI_FLOAT64_MIN)
            to = RI_FLOAT64_MIN;
        else
            to = (ri_float64)from;

        return to;
    }

    RI_API double  ri_ulong_to_double(ri_ulong from)
    {
        double to;

        if(from > RI_DOUBLE_MAX)
            to = RI_DOUBLE_MAX;
        else if(from < RI_DOUBLE_MIN)
            to = RI_DOUBLE_MIN;
        else
            to = (ri_double)from;

        return to;
    }






    RI_API int   ri_longlong_to_int(ri_longlong  from)
    {
        int to;

        if(from > RI_INT_MAX)
            to = (ri_int)RI_INT_MAX;
        else if(from < RI_INT_MIN)
            to =(ri_int) RI_INT_MIN;
        else
            to = (ri_int)from;

        return to;  
    }

    RI_API ri_uint   ri_longlong_to_uint(ri_longlong  from)
    {
        ri_uint to;

        if(from > RI_UINT_MAX)
            to = (ri_int)RI_UINT_MAX;
        else if(from < RI_UINT_MIN)
            to = RI_UINT_MIN;
        else
            to = (ri_uint)from;

        return to;  
    }

    RI_API ri_int8  ri_longlong_to_int8(ri_longlong from)
    {
        ri_int8 to;

        if(from > RI_INT8_MAX)
            to = RI_INT8_MAX;
        else if(from < RI_INT8_MIN)
            to = RI_INT8_MIN;
        else
            to = (ri_int8)from;

        return to;    
    }

    RI_API ri_uint8   ri_longlong_to_uint8(ri_longlong from)
    {
        ri_uint8 to;

        if(from > RI_UINT8_MAX)
            to = RI_UINT8_MAX;
        else if(from < RI_UINT8_MIN)
            to = RI_UINT8_MIN;
        else
            to = (ri_uint8)from;

        return to;    
    }

    RI_API ri_int16  ri_longlong_to_int16(ri_longlong from)
    {
        ri_int16 to;

        if(from > RI_INT16_MAX)
            to = RI_INT16_MAX;
        else if(from < RI_INT16_MIN)
            to = RI_INT16_MIN;
        else
            to = (ri_int16)from;

        return to;
    }

    RI_API ri_uint16  ri_longlong_to_uint16(ri_longlong from)
    {
        ri_uint16 to;

        if(from > RI_UINT16_MAX)
            to = RI_UINT16_MAX;
        else if(from < RI_UINT16_MIN)
            to = RI_UINT16_MIN;
        else
            to = (ri_uint16)from;

        return to;
    }

    RI_API ri_int32 ri_longlong_to_int32(ri_longlong from)
    {
        ri_int32 to;

        if(from > RI_INT32_MAX)
            to = RI_INT32_MAX;
        else if(from < RI_INT32_MIN)
            to = RI_INT32_MIN;
        else
            to = (ri_int32)from;

        return to;
    }

    RI_API ri_uint32   ri_longlong_to_uint32(ri_longlong from)
    {
        ri_uint32 to;

        if(from > RI_UINT32_MAX)
            to = RI_UINT32_MAX;
        else if(from < RI_UINT32_MIN)
            to = RI_UINT32_MIN;
        else
            to = (ri_uint32)from;

        return to;
    }

    RI_API ri_int64  ri_longlong_to_int64(ri_longlong from)
    {
        ri_int64 to;

        if(from > RI_INT64_MAX)
            to = RI_INT64_MAX;
        else if(from < RI_INT64_MIN)
            to = RI_INT64_MIN;
        else
            to = (ri_int64)from;

        return to;
    }

    RI_API ri_uint64  ri_longlong_to_uint64(ri_longlong from)
    {
        ri_uint64 to;

        //  if(from > RI_UINT64_MAX)
        //    to = RI_UINT64_MAX;
        if(from < RI_UINT64_MIN)
            to = RI_UINT64_MIN;
        else
            to = (ri_uint64)from;

        return to;
    }

    RI_API long  ri_longlong_to_long(ri_longlong from)
    {
        long to;

        if(from > RI_LONG_MAX)
            to = RI_LONG_MAX;
        else if(from < RI_LONG_MIN)
            to = RI_LONG_MIN;
        else
            to = (ri_long)from;

        return to;
    }

    RI_API ri_ulong  ri_longlong_to_ulong(ri_longlong from)
    {
        ri_ulong to;

        if(from > RI_ULONG_MAX)
            to = RI_ULONG_MAX;
        else if(from < RI_ULONG_MIN)
            to = RI_ULONG_MIN;
        else
            to = (ri_ulong)from;

        return to;
    }

    RI_API ri_ulonglong  ri_longlong_to_ulonglong(ri_longlong from)
    {
        ri_ulonglong to;

        //  if(from > RI_ULONGLONG_MAX)
        //    to = RI_ULONGLONG_MAX;
        if(from < RI_ULONGLONG_MIN)
            to = RI_ULONGLONG_MIN;
        else
            to = (ri_ulonglong)from;

        return to;
    }

    RI_API size_t   ri_longlong_to_size(ri_longlong from)
    {
        size_t to;

        if(from > RI_SIZE_MAX)
            to = RI_SIZE_MAX;
        else if(from < RI_SIZE_MIN)
            to = RI_SIZE_MIN;
        else
            to = (ri_size)from;

        return to;
    }

    RI_API ri_ssize  ri_longlong_to_ssize(ri_longlong from)
    {
        ri_ssize to;

        if(from > RI_SSIZE_MAX)
            to = RI_SSIZE_MAX;
        else if(from < RI_SSIZE_MIN)
            to = RI_SSIZE_MIN;
        else
            to = (ri_ssize)from;

        return to;
    }

    RI_API float  ri_longlong_to_float(ri_longlong from)
    {
        float to;

        if(from > RI_FLOAT_MAX)
            to = RI_FLOAT_MAX;
        else if(from < RI_FLOAT_MIN)
            to = RI_FLOAT_MIN;
        else
            to = (ri_float)from;

        return to;
    }

    RI_API ri_float32  ri_longlong_to_float32(ri_longlong from)
    {
        ri_float32 to;

        if(from > RI_FLOAT32_MAX)
            to = RI_FLOAT32_MAX;
        else if(from < RI_FLOAT32_MIN)
            to = RI_FLOAT32_MIN;
        else
            to = (ri_float32)from;

        return to;
    }

    RI_API ri_float64  ri_longlong_to_float64(ri_longlong from)
    {
        ri_float64 to;

        if(from > RI_FLOAT64_MAX)
            to = RI_FLOAT64_MAX;
        else if(from < RI_FLOAT64_MIN)
            to = RI_FLOAT64_MIN;
        else
            to = (ri_float64)from;

        return to;
    }

    RI_API double  ri_longlong_to_double(ri_longlong from)
    {
        double to;

        if(from > RI_DOUBLE_MAX)
            to = RI_DOUBLE_MAX;
        else if(from < RI_DOUBLE_MIN)
            to = RI_DOUBLE_MIN;
        else
            to = (ri_double)from;

        return to;
    }






    RI_API int   ri_ulonglong_to_int(ri_ulonglong  from)
    {
        int to;

        if(from > RI_INT_MAX)
            to = (ri_int)RI_INT_MAX;
        else
            to = (ri_int)from;

        return to;  
    }

    RI_API ri_uint   ri_ulonglong_to_uint(ri_ulonglong  from)
    {
        ri_uint to;

        if(from > RI_UINT_MAX)
            to = (ri_int)RI_UINT_MAX;
        else if(from < RI_UINT_MIN)
            to = (ri_int)RI_UINT_MIN;
        else
            to = (ri_uint)from;

        return to;  
    }

    RI_API ri_int8  ri_ulonglong_to_int8(ri_ulonglong from)
    {
        ri_int8 to;

        if(from > RI_INT8_MAX)
            to = RI_INT8_MAX;
        else
            to = (ri_int8)from;

        return to;    
    }

    RI_API ri_uint8   ri_ulonglong_to_uint8(ri_ulonglong from)
    {
        ri_uint8 to;

        if(from > RI_UINT8_MAX)
            to = RI_UINT8_MAX;
        else if(from < RI_UINT8_MIN)
            to = RI_UINT8_MIN;
        else
            to = (ri_uint8)from;

        return to;    
    }

    RI_API ri_int16  ri_ulonglong_to_int16(ri_ulonglong from)
    {
        ri_int16 to;

        if(from > RI_INT16_MAX)
            to = RI_INT16_MAX;
        else
            to = (ri_int16)from;

        return to;
    }

    RI_API ri_uint16  ri_ulonglong_to_uint16(ri_ulonglong from)
    {
        ri_uint16 to;

        if(from > RI_UINT16_MAX)
            to = RI_UINT16_MAX;
        else if(from < RI_UINT16_MIN)
            to = RI_UINT16_MIN;
        else
            to = (ri_uint16)from;

        return to;
    }

    RI_API ri_int32 ri_ulonglong_to_int32(ri_ulonglong from)
    {
        ri_int32 to;

        if(from > RI_INT32_MAX)
            to = RI_INT32_MAX;
        else
            to = (ri_int32)from;

        return to;
    }

    RI_API ri_uint32   ri_ulonglong_to_uint32(ri_ulonglong from)
    {
        ri_uint32 to;

        if(from > RI_UINT32_MAX)
            to = RI_UINT32_MAX;
        else if(from < RI_UINT32_MIN)
            to = RI_UINT32_MIN;
        else
            to = (ri_uint32)from;

        return to;
    }

    RI_API ri_int64  ri_ulonglong_to_int64(ri_ulonglong from)
    {
        ri_int64 to;

        if(from > RI_INT64_MAX)
            to = RI_INT64_MAX;
        else
            to = (ri_int64)from;

        return to;
    }

    RI_API ri_uint64  ri_ulonglong_to_uint64(ri_ulonglong from)
    {
        ri_uint64 to;

        if(from > RI_UINT64_MAX)
            to = RI_UINT64_MAX;
        else if(from < RI_UINT64_MIN)
            to = RI_UINT64_MIN;
        else
            to = (ri_uint64)from;

        return to;
    }

    RI_API long  ri_ulonglong_to_long(ri_ulonglong from)
    {
        long to;

        if(from > RI_LONG_MAX)
            to = RI_LONG_MAX;
        else
            to = (ri_long)from;

        return to;
    }

    RI_API ri_ulong  ri_ulonglong_to_ulong(ri_ulonglong from)
    {
        ri_ulong to;

        if(from > RI_ULONG_MAX)
            to = RI_ULONG_MAX;
        else if(from < RI_ULONG_MIN)
            to = RI_ULONG_MIN;
        else
            to = (ri_ulong)from;

        return to;
    }

    RI_API ri_longlong  ri_ulonglong_to_longlong(ri_ulonglong from)
    {
        ri_longlong to;

        if(from > RI_LONGLONG_MAX)
            to = RI_LONGLONG_MAX;
        else
            to = (ri_longlong)from;

        return to;
    }

    RI_API size_t   ri_ulonglong_to_size(ri_ulonglong from)
    {
        size_t to;

        if(from > RI_SIZE_MAX)
            to = RI_SIZE_MAX;
        else if(from < RI_SIZE_MIN)
            to = RI_SIZE_MIN;
        else
            to = (ri_size)from;

        return to;
    }

    RI_API ri_ssize  ri_ulonglong_to_ssize(ri_ulonglong from)
    {
        ri_ssize to;

        if(from > RI_SSIZE_MAX)
            to = RI_SSIZE_MAX;
        else
            to = (ri_ssize)from;

        return to;
    }

    RI_API float  ri_ulonglong_to_float(ri_ulonglong from)
    {
        float to;

        if(from > RI_FLOAT_MAX)
            to = RI_FLOAT_MAX;
        else if(from < RI_FLOAT_MIN)
            to = RI_FLOAT_MIN;
        else
            to = (ri_float)from;

        return to;
    }

    RI_API ri_float32  ri_ulonglong_to_float32(ri_ulonglong from)
    {
        ri_float32 to;

        if(from > RI_FLOAT32_MAX)
            to = RI_FLOAT32_MAX;
        else if(from < RI_FLOAT32_MIN)
            to = RI_FLOAT32_MIN;
        else
            to = (ri_float32)from;

        return to;
    }

    RI_API ri_float64  ri_ulonglong_to_float64(ri_ulonglong from)
    {
        ri_float64 to;

        if(from > RI_FLOAT64_MAX)
            to = RI_FLOAT64_MAX;
        else if(from < RI_FLOAT64_MIN)
            to = RI_FLOAT64_MIN;
        else
            to = (ri_float64)from;

        return to;
    }

    RI_API double  ri_ulonglong_to_double(ri_ulonglong from)
    {
        double to;

        if(from > RI_DOUBLE_MAX)
            to = RI_DOUBLE_MAX;
        else if(from < RI_DOUBLE_MIN)
            to = RI_DOUBLE_MIN;
        else
            to = (ri_double)from;

        return to;
    }





    RI_API int   ri_size_to_int(size_t  from)
    {
        int to;

        if(from > RI_INT_MAX)
            to = (ri_int)RI_INT_MAX;
        else
            to = (ri_int)from;

        return to;  
    }

    RI_API ri_uint   ri_size_to_uint(size_t  from)
    {
        ri_uint to;

        if(from > RI_UINT_MAX)
            to = (ri_int)RI_UINT_MAX;
        else if(from < RI_UINT_MIN)
            to = (ri_int)RI_UINT_MIN;
        else
            to = (ri_uint)from;

        return to;  
    }

    RI_API ri_int8  ri_size_to_int8(size_t from)
    {
        ri_int8 to;

        if(from > RI_INT8_MAX)
            to = RI_INT8_MAX;
        else
            to = (ri_int8)from;

        return to;    
    }

    RI_API ri_uint8   ri_size_to_uint8(size_t from)
    {
        ri_uint8 to;

        if(from > RI_UINT8_MAX)
            to = RI_UINT8_MAX;
        else if(from < RI_UINT8_MIN)
            to = RI_UINT8_MIN;
        else
            to = (ri_uint8)from;

        return to;    
    }

    RI_API ri_int16  ri_size_to_int16(size_t from)
    {
        ri_int16 to;

        if(from > RI_INT16_MAX)
            to = RI_INT16_MAX;
        else
            to = (ri_int16)from;

        return to;
    }

    RI_API ri_uint16  ri_size_to_uint16(size_t from)
    {
        ri_uint16 to;

        if(from > RI_UINT16_MAX)
            to = RI_UINT16_MAX;
        else if(from < RI_UINT16_MIN)
            to = RI_UINT16_MIN;
        else
            to = (ri_uint16)from;

        return to;
    }

    RI_API ri_int32 ri_size_to_int32(size_t from)
    {
        ri_int32 to;

        if(from > RI_INT32_MAX)
            to = RI_INT32_MAX;
        else
            to = (ri_int32)from;

        return to;
    }

    RI_API ri_uint32   ri_size_to_uint32(size_t from)
    {
        ri_uint32 to;

        if(from > RI_UINT32_MAX)
            to = RI_UINT32_MAX;
        else if(from < RI_UINT32_MIN)
            to = RI_UINT32_MIN;
        else
            to = (ri_uint32)from;

        return to;
    }

    RI_API ri_int64  ri_size_to_int64(size_t from)
    {
        ri_int64 to;

        to = (ri_int64)from;

        return to;
    }

    RI_API ri_uint64 ri_size_to_uint64(size_t from)
    {
        ri_uint64 to;

        //  if(from > RI_UINT64_MAX)
        //    to = RI_UINT64_MAX;
        //  else if(from < RI_UINT64_MIN)
        //    to = RI_UINT64_MIN;
        //  else
        to = (ri_uint64)from;

        return to;
    }

    RI_API long  ri_size_to_long(size_t from)
    {
        long to;

        if(from > RI_LONG_MAX)
            to = RI_LONG_MAX;
        else
            to = (ri_long)from;

        return to;
    }

    RI_API ri_ulong  ri_size_to_ulong(size_t from)
    {
        ri_ulong to;

        if(from > RI_ULONG_MAX)
            to = RI_ULONG_MAX;
        else if(from < RI_ULONG_MIN)
            to = RI_ULONG_MIN;
        else
            to = (ri_ulong)from;

        return to;
    }

    RI_API ri_longlong  ri_size_to_longlong(size_t from)
    {
        ri_longlong to;

        to = (ri_longlong)from;

        return to;
    }

    RI_API ri_ulonglong  ri_size_to_ulonglong(size_t from)
    {
        ri_ulonglong to;

        to = (ri_ulonglong)from;

        return to;
    }

    RI_API ri_ssize  ri_size_to_ssize(size_t from)
    {
        ri_ssize to;

        if(from > RI_SSIZE_MAX)
            to = RI_SSIZE_MAX;
        else
            to = (ri_ssize)from;

        return to;
    }

    RI_API float  ri_size_to_float(size_t from)
    {
        float to;

        if(from > RI_FLOAT_MAX)
            to = RI_FLOAT_MAX;
        else if(from < RI_FLOAT_MIN)
            to = RI_FLOAT_MIN;
        else
            to = (ri_float)from;

        return to;
    }

    RI_API ri_float32  ri_size_to_float32(size_t from)
    {
        ri_float32 to;

        if(from > RI_FLOAT32_MAX)
            to = RI_FLOAT32_MAX;
        else if(from < RI_FLOAT32_MIN)
            to = RI_FLOAT32_MIN;
        else
            to = (ri_float32)from;

        return to;
    }

    RI_API ri_float64  ri_size_to_float64(size_t from)
    {
        ri_float64 to;

        if(from > RI_FLOAT64_MAX)
            to = RI_FLOAT64_MAX;
        else if(from < RI_FLOAT64_MIN)
            to = RI_FLOAT64_MIN;
        else
            to = (ri_float64)from;

        return to;
    }

    RI_API double  ri_size_to_double(size_t from)
    {
        double to;

        if(from > RI_DOUBLE_MAX)
            to = RI_DOUBLE_MAX;
        else if(from < RI_DOUBLE_MIN)
            to = RI_DOUBLE_MIN;
        else
            to = (ri_double)from;

        return to;
    }





    RI_API int   ri_ssize_to_int(ri_ssize  from)
    {
        int to;

        if(from > RI_INT_MAX)
            to = (ri_int)RI_INT_MAX;
        else if(from < RI_INT_MIN)
            to = (ri_int)RI_INT_MIN;
        else
            to = (ri_int)from;

        return to;  
    }

    RI_API ri_uint   ri_ssize_to_uint(ri_ssize  from)
    {
        ri_uint to;

        //  if(from > RI_UINT_MAX)
        //    to = RI_UINT_MAX;
        if(from < RI_UINT_MIN)
            to = RI_UINT_MIN;
        else
            to = (ri_uint)from;

        return to;  
    }

    RI_API ri_int8  ri_ssize_to_int8(ri_ssize from)
    {
        ri_int8 to;

        if(from > RI_INT8_MAX)
            to = RI_INT8_MAX;
        else if(from < RI_INT8_MIN)
            to = RI_INT8_MIN;
        else
            to = (ri_int8)from;

        return to;    
    }

    RI_API ri_uint8   ri_ssize_to_uint8(ri_ssize from)
    {
        ri_uint8 to;

        if(from > RI_UINT8_MAX)
            to = RI_UINT8_MAX;
        else if(from < RI_UINT8_MIN)
            to = RI_UINT8_MIN;
        else
            to = (ri_uint8)from;

        return to;    
    }

    RI_API ri_int16  ri_ssize_to_int16(ri_ssize from)
    {
        ri_int16 to;

        if(from > RI_INT16_MAX)
            to = RI_INT16_MAX;
        else if(from < RI_INT16_MIN)
            to = RI_INT16_MIN;
        else
            to = (ri_int16)from;

        return to;
    }

    RI_API ri_uint16  ri_ssize_to_uint16(ri_ssize from)
    {
        ri_uint16 to;

        if(from > RI_UINT16_MAX)
            to = RI_UINT16_MAX;
        else if(from < RI_UINT16_MIN)
            to = RI_UINT16_MIN;
        else
            to = (ri_uint16)from;

        return to;
    }

    RI_API ri_int32  ri_ssize_to_int32(ri_ssize from)
    {
        ri_int32 to;

        if(from > RI_INT32_MAX)
            to = RI_INT32_MAX;
        else if(from < RI_INT32_MIN)
            to = RI_INT32_MIN;
        else
            to = (ri_int32)from;

        return to;
    }

    RI_API ri_uint32   ri_ssize_to_uint32(ri_ssize from)
    {
        ri_uint32 to;

        //  if(from > RI_UINT32_MAX)
        //    to = RI_UINT32_MAX;
        if(from < RI_UINT32_MIN)
            to = RI_UINT32_MIN;
        else
            to = (ri_uint32)from;

        return to;
    }

    RI_API ri_int64  ri_ssize_to_int64(ri_ssize from)
    {
        ri_int64 to;

        //  if(from > RI_INT64_MAX)
        //    to = RI_INT64_MAX;
        //  else if(from < RI_INT64_MIN)
        //    to = RI_INT64_MIN;
        //  else
        to = (ri_int64)from;

        return to;
    }

    RI_API ri_uint64   ri_ssize_to_uint64(ri_ssize from)
    {
        ri_uint64 to;

        //  if(from > RI_UINT64_MAX)
        //    to = RI_UINT64_MAX;
        if(from < RI_UINT64_MIN)
            to = RI_UINT64_MIN;
        else
            to = (ri_uint64)from;

        return to;
    }

    RI_API long  ri_ssize_to_long(ri_ssize from)
    {
        long to;

        if(from > RI_LONG_MAX)
            to = RI_LONG_MAX;
        else if(from < RI_LONG_MIN)
            to = RI_LONG_MIN;
        else
            to = (ri_long)from;

        return to;
    }

    RI_API ri_ulong  ri_ssize_to_ulong(ri_ssize from)
    {
        ri_ulong to;

        //  if(from > RI_ULONG_MAX)
        //    to = RI_ULONG_MAX;
        if(from < RI_ULONG_MIN)
            to = RI_ULONG_MIN;
        else
            to = (ri_ulong)from;

        return to;
    }

    RI_API ri_longlong  ri_ssize_to_longlong(ri_ssize from)
    {
        ri_longlong to;

        to = (ri_longlong)from;

        return to;
    }

    RI_API ri_ulonglong  ri_ssize_to_ulonglong(ri_ssize from)
    {
        ri_ulonglong to;

        //  if(from > RI_ULONGLONG_MAX)
        //    to = RI_ULONGLONG_MAX;
        if(from < RI_ULONGLONG_MIN)
            to = RI_ULONGLONG_MIN;
        else
            to = (ri_ulonglong)from;

        return to;
    }

    RI_API size_t  ri_ssize_to_size(ri_ssize from)
    {
        size_t to;

        //  if(from > RI_SIZE_MAX)
        //    to = RI_SIZE_MAX;
        if(from < RI_SIZE_MIN)
            to = RI_SIZE_MIN;
        else
            to = (ri_size)from;

        return to;
    }

    RI_API float  ri_ssize_to_float(ri_ssize from)
    {
        float to;

        if(from > RI_FLOAT_MAX)
            to = RI_FLOAT_MAX;
        else if(from < RI_FLOAT_MIN)
            to = RI_FLOAT_MIN;
        else
            to = (ri_float)from;

        return to;
    }

    RI_API ri_float32  ri_ssize_to_float32(ri_ssize from)
    {
        ri_float32 to;

        if(from > RI_FLOAT32_MAX)
            to = RI_FLOAT32_MAX;
        else if(from < RI_FLOAT32_MIN)
            to = RI_FLOAT32_MIN;
        else
            to = (ri_float32)from;

        return to;
    }

    RI_API ri_float64  ri_ssize_to_float64(ri_ssize from)
    {
        ri_float64 to;

        if(from > RI_FLOAT64_MAX)
            to = RI_FLOAT64_MAX;
        else if(from < RI_FLOAT64_MIN)
            to = RI_FLOAT64_MIN;
        else
            to = (ri_float64)from;

        return to;
    }

    RI_API double  ri_ssize_to_double(ri_ssize from)
    {
        double to;

        if(from > RI_DOUBLE_MAX)
            to = RI_DOUBLE_MAX;
        else if(from < RI_DOUBLE_MIN)
            to = RI_DOUBLE_MIN;
        else
            to = (ri_double)from;

        return to;
    }






    RI_API int   ri_float_to_int(float  from)
    {
        int to;

        if(from > RI_INT_MAX)
            to = (ri_int)RI_INT_MAX;
        else if(from < RI_INT_MIN)
            to = (ri_int)RI_INT_MIN;
        else
            to = (ri_int)from;

        return to;  
    }

    RI_API ri_uint   ri_float_to_uint(float  from)
    {
        ri_uint to;

        if(from > RI_UINT_MAX)
            to = (ri_int)RI_UINT_MAX;
        else if(from < RI_UINT_MIN)
            to = RI_UINT_MIN;
        else
            to = (ri_uint)from;

        return to;  
    }
    RI_API ri_int8  ri_float_to_int8(float from)
    {
        ri_int8 to;

        if(from > RI_INT8_MAX)
            to = RI_INT8_MAX;
        else if(from < RI_INT8_MIN)
            to = RI_INT8_MIN;
        else
            to = (ri_int8)from;

        return to;    
    }

    RI_API ri_uint8   ri_float_to_uint8(float from)
    {
        ri_uint8 to;

        if(from > RI_UINT8_MAX)
            to = RI_UINT8_MAX;
        else if(from < RI_UINT8_MIN)
            to = RI_UINT8_MIN;
        else
            to = (ri_uint8)from;

        return to;    
    }

    RI_API ri_int16  ri_float_to_int16(float from)
    {
        ri_int16 to;

        if(from > RI_INT16_MAX)
            to = RI_INT16_MAX;
        else if(from < RI_INT16_MIN)
            to = RI_INT16_MIN;
        else
            to = (ri_int16)from;

        return to;
    }

    RI_API ri_uint16  ri_float_to_uint16(float from)
    {
        ri_uint16 to;

        if(from > RI_UINT16_MAX)
            to = RI_UINT16_MAX;
        else if(from < RI_UINT16_MIN)
            to = RI_UINT16_MIN;
        else
            to = (ri_uint16)from;

        return to;
    }

    RI_API ri_int32  ri_float_to_int32(float from)
    {
        ri_int32 to;

        if(from > RI_INT32_MAX)
            to = RI_INT32_MAX;
        else if(from < RI_INT32_MIN)
            to = RI_INT32_MIN;
        else
            to = (ri_int32)from;

        return to;
    }

    RI_API ri_uint32   ri_float_to_uint32(float from)
    {
        ri_uint32 to;

        if(from > RI_UINT32_MAX)
            to = RI_UINT32_MAX;
        else if(from < RI_UINT32_MIN)
            to = RI_UINT32_MIN;
        else
            to = (ri_uint32)from;

        return to;
    }

    RI_API ri_int64  ri_float_to_int64(float from)
    {
        ri_int64 to;

        if(from > RI_INT64_MAX)
            to = RI_INT64_MAX;
        else if(from < RI_INT64_MIN)
            to = RI_INT64_MIN;
        else
            to = (ri_int64)from;

        return to;
    }

    RI_API ri_uint64   ri_float_to_uint64(float from)
    {
        ri_uint64 to;

        if(from > RI_UINT64_MAX)
            to = RI_UINT64_MAX;
        else if(from < RI_UINT64_MIN)
            to = RI_UINT64_MIN;
        else
            to = (ri_uint64)from;

        return to;
    }

    RI_API long  ri_float_to_long(float from)
    {
        long to;

        if(from > RI_LONG_MAX)
            to = RI_LONG_MAX;
        else if(from < RI_LONG_MIN)
            to = RI_LONG_MIN;
        else
            to = (ri_long)from;

        return to;
    }

    RI_API ri_ulong  ri_float_to_ulong(float from)
    {
        ri_ulong to;

        if(from > RI_ULONG_MAX)
            to = RI_ULONG_MAX;
        else if(from < RI_ULONG_MIN)
            to = RI_ULONG_MIN;
        else
            to = (ri_ulong)from;

        return to;
    }

    RI_API ri_longlong  ri_float_to_longlong(float from)
    {
        ri_longlong to;

        if(from > RI_LONGLONG_MAX)
            to = RI_LONGLONG_MAX;
        else if(from < RI_LONGLONG_MIN)
            to = RI_LONGLONG_MIN;
        else
            to = (ri_longlong)from;

        return to;
    }

    RI_API ri_ulonglong  ri_float_to_ulonglong(float from)
    {
        ri_ulonglong to;

        if(from > RI_ULONGLONG_MAX)
            to = RI_ULONGLONG_MAX;
        else if(from < RI_ULONGLONG_MIN)
            to = RI_ULONGLONG_MIN;
        else
            to = (ri_ulonglong)from;

        return to;
    }

    RI_API size_t  ri_float_to_size(float from)
    {
        size_t to;

        if(from > RI_SIZE_MAX)
            to = RI_SIZE_MAX;
        else if(from < RI_SIZE_MIN)
            to = RI_SIZE_MIN;
        else
            to = (ri_size)from;

        return to;
    }

    RI_API ri_ssize  ri_float_to_ssize(float from)
    {
        ri_ssize to;

        if(from > RI_SSIZE_MAX)
            to = RI_SSIZE_MAX;
        else if(from < RI_SSIZE_MIN)
            to = RI_SSIZE_MIN;
        else
            to = (ri_ssize)from;

        return to;
    }

    RI_API ri_float32  ri_float_to_float32(float from)
    {
        ri_float32 to;

        if(from > RI_FLOAT32_MAX)
            to = RI_FLOAT32_MAX;
        else if(from < RI_FLOAT32_MIN)
            to = RI_FLOAT32_MIN;
        else
            to = (ri_float32)from;

        return to;
    }

    RI_API ri_float64  ri_float_to_float64(float from)
    {
        ri_float64 to;

        if(from > RI_FLOAT64_MAX)
            to = RI_FLOAT64_MAX;
        else if(from < RI_FLOAT64_MIN)
            to = RI_FLOAT64_MIN;
        else
            to = (ri_float64)from;

        return to;
    }

    RI_API double  ri_float_to_double(float from)
    {
        double to;

        if(from > RI_DOUBLE_MAX)
            to = RI_DOUBLE_MAX;
        else if(from < RI_DOUBLE_MIN)
            to = RI_DOUBLE_MIN;
        else
            to = (ri_double)from;

        return to;
    }





    RI_API int   ri_float32_to_int(ri_float32  from)
    {
        int to;

        if(from > RI_INT_MAX)
            to = (ri_int)RI_INT_MAX;
        else if(from < RI_INT_MIN)
            to = (ri_int)RI_INT_MIN;
        else
            to = (ri_int)from;

        return to;  
    }

    RI_API ri_uint   ri_float32_to_uint(ri_float32  from)
    {
        ri_uint to;

        if(from > RI_UINT_MAX)
            to = (ri_int)RI_UINT_MAX;
        else if(from < RI_UINT_MIN)
            to = RI_UINT_MIN;
        else
            to = (ri_uint)from;

        return to;  
    }

    RI_API ri_int8  ri_float32_to_int8(ri_float32 from)
    {
        ri_int8 to;

        if(from > RI_INT8_MAX)
            to = RI_INT8_MAX;
        else if(from < RI_INT8_MIN)
            to = RI_INT8_MIN;
        else
            to = (ri_int8)from;

        return to;    
    }

    RI_API ri_uint8   ri_float32_to_uint8(ri_float32 from)
    {
        ri_uint8 to;

        if(from > RI_UINT8_MAX)
            to = RI_UINT8_MAX;
        else if(from < RI_UINT8_MIN)
            to = RI_UINT8_MIN;
        else
            to = (ri_uint8)from;

        return to;    
    }

    RI_API ri_int16  ri_float32_to_int16(ri_float32 from)
    {
        ri_int16 to;

        if(from > RI_INT16_MAX)
            to = RI_INT16_MAX;
        else if(from < RI_INT16_MIN)
            to = RI_INT16_MIN;
        else
            to = (ri_int16)from;

        return to;
    }

    RI_API ri_uint16  ri_float32_to_uint16(ri_float32 from)
    {
        ri_uint16 to;

        if(from > RI_UINT16_MAX)
            to = RI_UINT16_MAX;
        else if(from < RI_UINT16_MIN)
            to = RI_UINT16_MIN;
        else
            to = (ri_uint16)from;

        return to;
    }

    RI_API ri_int32  ri_float32_to_int32(ri_float32 from)
    {
        ri_int32 to;

        if(from > RI_INT32_MAX)
            to = RI_INT32_MAX;
        else if(from < RI_INT32_MIN)
            to = RI_INT32_MIN;
        else
            to = (ri_int32)from;

        return to;
    }

    RI_API ri_uint32   ri_float32_to_uint32(ri_float32 from)
    {
        ri_uint32 to;

        if(from > RI_UINT32_MAX)
            to = RI_UINT32_MAX;
        else if(from < RI_UINT32_MIN)
            to = RI_UINT32_MIN;
        else
            to = (ri_uint32)from;

        return to;
    }

    RI_API ri_int64  ri_float32_to_int64(ri_float32 from)
    {
        ri_int64 to;

        if(from > RI_INT64_MAX)
            to = RI_INT64_MAX;
        else if(from < RI_INT64_MIN)
            to = RI_INT64_MIN;
        else
            to = (ri_int64)from;

        return to;
    }

    RI_API ri_uint64   ri_float32_to_uint64(ri_float32 from)
    {
        ri_uint64 to;

        if(from > RI_UINT64_MAX)
            to = RI_UINT64_MAX;
        else if(from < RI_UINT64_MIN)
            to = RI_UINT64_MIN;
        else
            to = (ri_uint64)from;

        return to;
    }

    RI_API long  ri_float32_to_long(ri_float32 from)
    {
        long to;

        if(from > RI_LONG_MAX)
            to = RI_LONG_MAX;
        else if(from < RI_LONG_MIN)
            to = RI_LONG_MIN;
        else
            to = (ri_long)from;

        return to;
    }

    RI_API ri_ulong  ri_float32_to_ulong(ri_float32 from)
    {
        ri_ulong to;

        if(from > RI_ULONG_MAX)
            to = RI_ULONG_MAX;
        else if(from < RI_ULONG_MIN)
            to = RI_ULONG_MIN;
        else
            to = (ri_ulong)from;

        return to;
    }

    RI_API ri_longlong  ri_float32_to_longlong(ri_float32 from)
    {
        ri_longlong to;

        if(from > RI_LONGLONG_MAX)
            to = RI_LONGLONG_MAX;
        else if(from < RI_LONGLONG_MIN)
            to = RI_LONGLONG_MIN;
        else
            to = (ri_longlong)from;

        return to;
    }

    RI_API ri_ulonglong  ri_float32_to_ulonglong(ri_float32 from)
    {
        ri_ulonglong to;

        if(from > RI_ULONGLONG_MAX)
            to = RI_ULONGLONG_MAX;
        else if(from < RI_ULONGLONG_MIN)
            to = RI_ULONGLONG_MIN;
        else
            to = (ri_ulonglong)from;

        return to;
    }

    RI_API size_t  ri_float32_to_size(ri_float32 from)
    {
        size_t to;

        if(from > RI_SIZE_MAX)
            to = RI_SIZE_MAX;
        else if(from < RI_SIZE_MIN)
            to = RI_SIZE_MIN;
        else
            to = (ri_size)from;

        return to;
    }

    RI_API ri_ssize  ri_float32_to_ssize(ri_float32 from)
    {
        ri_ssize to;

        if(from > RI_SSIZE_MAX)
            to = RI_SSIZE_MAX;
        else if(from < RI_SSIZE_MIN)
            to = RI_SSIZE_MIN;
        else
            to = (ri_ssize)from;

        return to;
    }

    RI_API float  ri_float32_to_float(ri_float32 from)
    {
        float to;

        if(from > RI_FLOAT_MAX)
            to = RI_FLOAT_MAX;
        else if(from < RI_FLOAT_MIN)
            to = RI_FLOAT_MIN;
        else
            to = (ri_float)from;

        return to;
    }

    RI_API ri_float64  ri_float32_to_float64(ri_float32 from)
    {
        ri_float64 to;

        if(from > RI_FLOAT64_MAX)
            to = RI_FLOAT64_MAX;
        else if(from < RI_FLOAT64_MIN)
            to = RI_FLOAT64_MIN;
        else
            to = (ri_float64)from;

        return to;
    }

    RI_API double  ri_float32_to_double(ri_float32 from)
    {
        double to;

        if(from > RI_DOUBLE_MAX)
            to = RI_DOUBLE_MAX;
        else if(from < RI_DOUBLE_MIN)
            to = RI_DOUBLE_MIN;
        else
            to = (ri_double)from;

        return to;
    }

    RI_API int   ri_float64_to_int(ri_float64  from)
    {
        int to;

        if(from > RI_INT_MAX)
            to = (ri_int)RI_INT_MAX;
        else if(from < RI_INT_MIN)
            to = (ri_int)RI_INT_MIN;
        else
            to = (ri_int)from;

        return to;  
    }

    RI_API ri_uint   ri_float64_to_uint(ri_float64  from)
    {
        ri_uint to;

        if(from > RI_UINT_MAX)
            to = (ri_int)RI_UINT_MAX;
        else if(from < RI_UINT_MIN)
            to = RI_UINT_MIN;
        else
            to = (ri_uint)from;

        return to;  
    }

    RI_API ri_int8  ri_float64_to_int8(ri_float64 from)
    {
        ri_int8 to;

        if(from > RI_INT8_MAX)
            to = RI_INT8_MAX;
        else if(from < RI_INT8_MIN)
            to = RI_INT8_MIN;
        else
            to = (ri_int8)from;

        return to;    
    }

    RI_API ri_uint8   ri_float64_to_uint8(ri_float64 from)
    {
        ri_uint8 to;

        if(from > RI_UINT8_MAX)
            to = RI_UINT8_MAX;
        else if(from < RI_UINT8_MIN)
            to = RI_UINT8_MIN;
        else
            to = (ri_uint8)from;

        return to;    
    }

    RI_API ri_int16  ri_float64_to_int16(ri_float64 from)
    {
        ri_int16 to;

        if(from > RI_INT16_MAX)
            to = RI_INT16_MAX;
        else if(from < RI_INT16_MIN)
            to = RI_INT16_MIN;
        else
            to = (ri_int16)from;

        return to;
    }

    RI_API ri_uint16  ri_float64_to_uint16(ri_float64 from)
    {
        ri_uint16 to;

        if(from > RI_UINT16_MAX)
            to = RI_UINT16_MAX;
        else if(from < RI_UINT16_MIN)
            to = RI_UINT16_MIN;
        else
            to = (ri_uint16)from;

        return to;
    }

    RI_API ri_int32  ri_float64_to_int32(ri_float64 from)
    {
        ri_int32 to;

        if(from > RI_INT32_MAX)
            to = RI_INT32_MAX;
        else if(from < RI_INT32_MIN)
            to = RI_INT32_MIN;
        else
            to = (ri_int32)from;

        return to;
    }

    RI_API ri_uint32   ri_float64_to_uint32(ri_float64 from)
    {
        ri_uint32 to;

        if(from > RI_UINT32_MAX)
            to = RI_UINT32_MAX;
        else if(from < RI_UINT32_MIN)
            to = RI_UINT32_MIN;
        else
            to = (ri_uint32)from;

        return to;
    }

    RI_API ri_int64  ri_float64_to_int64(ri_float64 from)
    {
        ri_int64 to;

        if(from > RI_INT64_MAX)
            to = RI_INT64_MAX;
        else if(from < RI_INT64_MIN)
            to = RI_INT64_MIN;
        else
            to = (ri_int64)from;

        return to;
    }

    RI_API ri_uint64   ri_float64_to_uint64(ri_float64 from)
    {
        ri_uint64 to;

        if(from > RI_UINT64_MAX)
            to = RI_UINT64_MAX;
        else if(from < RI_UINT64_MIN)
            to = RI_UINT64_MIN;
        else
            to = (ri_uint64)from;

        return to;
    }

    RI_API long  ri_float64_to_long(ri_float64 from)
    {
        long to;

        if(from > RI_LONG_MAX)
            to = RI_LONG_MAX;
        else if(from < RI_LONG_MIN)
            to = RI_LONG_MIN;
        else
            to = (ri_long)from;

        return to;
    }

    RI_API ri_ulong  ri_float64_to_ulong(ri_float64 from)
    {
        ri_ulong to;

        if(from > RI_ULONG_MAX)
            to = RI_ULONG_MAX;
        else if(from < RI_ULONG_MIN)
            to = RI_ULONG_MIN;
        else
            to = (ri_ulong)from;

        return to;
    }

    RI_API ri_longlong  ri_float64_to_longlong(ri_float64 from)
    {
        ri_longlong to;

        if(from > RI_LONGLONG_MAX)
            to = RI_LONGLONG_MAX;
        else if(from < RI_LONGLONG_MIN)
            to = RI_LONGLONG_MIN;
        else
            to = (ri_longlong)from;

        return to;
    }

    RI_API ri_ulonglong  ri_float64_to_ulonglong(ri_float64 from)
    {
        ri_ulonglong to;

        if(from > RI_ULONGLONG_MAX)
            to = RI_ULONGLONG_MAX;
        else if(from < RI_ULONGLONG_MIN)
            to = RI_ULONGLONG_MIN;
        else
            to = (ri_ulonglong)from;

        return to;
    }

    RI_API size_t  ri_float64_to_size(ri_float64 from)
    {
        size_t to;

        if(from > RI_SIZE_MAX)
            to = RI_SIZE_MAX;
        else if(from < RI_SIZE_MIN)
            to = RI_SIZE_MIN;
        else
            to = (ri_size)from;

        return to;
    }

    RI_API ri_ssize  ri_float64_to_ssize(ri_float64 from)
    {
        ri_ssize to;

        if(from > RI_SSIZE_MAX)
            to = RI_SSIZE_MAX;
        else if(from < RI_SSIZE_MIN)
            to = RI_SSIZE_MIN;
        else
            to = (ri_ssize)from;

        return to;
    }

    RI_API float  ri_float64_to_float(ri_float64 from)
    {
        float to;

        if(from > RI_FLOAT_MAX)
            to = RI_FLOAT_MAX;
        else if(from < RI_FLOAT_MIN)
            to = RI_FLOAT_MIN;
        else
            to = (ri_float)from;

        return to;
    }

    RI_API ri_float32  ri_float64_to_float32(ri_float64 from)
    {
        ri_float32 to;

        if(from > RI_FLOAT32_MAX)
            to = RI_FLOAT32_MAX;
        else if(from < RI_FLOAT32_MIN)
            to = RI_FLOAT32_MIN;
        else
            to = (ri_float32)from;

        return to;
    }

    RI_API double  ri_float64_to_double(ri_float64 from)
    {
        double to;

        if(from > RI_DOUBLE_MAX)
            to = RI_DOUBLE_MAX;
        else if(from < RI_DOUBLE_MIN)
            to = RI_DOUBLE_MIN;
        else
            to = (ri_double)from;

        return to;
    }


    RI_API int   ri_double_to_int(double  from)
    {
        int to;

        if(from > RI_INT_MAX)
            to = (ri_int)RI_INT_MAX;
        else if(from < RI_INT_MIN)
            to = (ri_int)RI_INT_MIN;
        else
            to = (ri_int)from;

        return to;  
    }

    RI_API ri_uint   ri_double_to_uint(double  from)
    {
        ri_uint to;

        if(from > RI_UINT_MAX)
            to = (ri_int)RI_UINT_MAX;
        else if(from < RI_UINT_MIN)
            to = RI_UINT_MIN;
        else
            to = (ri_uint)from;

        return to;  
    }

    RI_API ri_int8  ri_double_to_int8(double from)
    {
        ri_int8 to;

        if(from > RI_INT8_MAX)
            to = RI_INT8_MAX;
        else if(from < RI_INT8_MIN)
            to = RI_INT8_MIN;
        else
            to = (ri_int8)from;

        return to;    
    }

    RI_API ri_uint8   ri_double_to_uint8(double from)
    {
        ri_uint8 to;

        if(from > RI_UINT8_MAX)
            to = RI_UINT8_MAX;
        else if(from < RI_UINT8_MIN)
            to = RI_UINT8_MIN;
        else
            to = (ri_uint8)from;

        return to;    
    }

    RI_API ri_int16  ri_double_to_int16(double from)
    {
        ri_int16 to;

        if(from > RI_INT16_MAX)
            to = RI_INT16_MAX;
        else if(from < RI_INT16_MIN)
            to = RI_INT16_MIN;
        else
            to = (ri_int16)from;

        return to;
    }

    RI_API ri_uint16  ri_double_to_uint16(double from)
    {
        ri_uint16 to;

        if(from > RI_UINT16_MAX)
            to = RI_UINT16_MAX;
        else if(from < RI_UINT16_MIN)
            to = RI_UINT16_MIN;
        else
            to = (ri_uint16)from;

        return to;
    }

    RI_API ri_int32  ri_double_to_int32(double from)
    {
        ri_int32 to;

        if(from > RI_INT32_MAX)
            to = RI_INT32_MAX;
        else if(from < RI_INT32_MIN)
            to = RI_INT32_MIN;
        else
            to = (ri_int32)from;

        return to;
    }

    RI_API ri_uint32   ri_double_to_uint32(double from)
    {
        ri_uint32 to;

        if(from > RI_UINT32_MAX)
            to = RI_UINT32_MAX;
        else if(from < RI_UINT32_MIN)
            to = RI_UINT32_MIN;
        else
            to = (ri_uint32)from;

        return to;
    }

    RI_API ri_int64  ri_double_to_int64(double from)
    {
        ri_int64 to;

        if(from > RI_INT64_MAX)
            to = RI_INT64_MAX;
        else if(from < RI_INT64_MIN)
            to = RI_INT64_MIN;
        else
            to = (ri_int64)from;

        return to;
    }

    RI_API ri_uint64   ri_double_to_uint64(double from)
    {
        ri_uint64 to;

        if(from > RI_UINT64_MAX)
            to = RI_UINT64_MAX;
        else if(from < RI_UINT64_MIN)
            to = RI_UINT64_MIN;
        else
            to = (ri_uint64)from;

        return to;
    }

    RI_API long  ri_double_to_long(double from)
    {
        long to;

        if(from > RI_LONG_MAX)
            to = RI_LONG_MAX;
        else if(from < RI_LONG_MIN)
            to = RI_LONG_MIN;
        else
            to = (ri_long)from;

        return to;
    }

    RI_API ri_ulong  ri_double_to_ulong(double from)
    {
        ri_ulong to;

        if(from > RI_ULONG_MAX)
            to = RI_ULONG_MAX;
        else if(from < RI_ULONG_MIN)
            to = RI_ULONG_MIN;
        else
            to = (ri_ulong)from;

        return to;
    }

    RI_API ri_longlong  ri_double_to_longlong(double from)
    {
        ri_longlong to;

        if(from > RI_LONGLONG_MAX)
            to = RI_LONGLONG_MAX;
        else if(from < RI_LONGLONG_MIN)
            to = RI_LONGLONG_MIN;
        else
            to = (ri_longlong)from;

        return to;
    }

    RI_API ri_ulonglong  ri_double_to_ulonglong(double from)
    {
        ri_ulonglong to;

        if(from > RI_ULONGLONG_MAX)
            to = RI_ULONGLONG_MAX;
        else if(from < RI_ULONGLONG_MIN)
            to = RI_ULONGLONG_MIN;
        else
            to = (ri_ulonglong)from;

        return to;
    }

    RI_API size_t  ri_double_to_size(double from)
    {
        size_t to;

        if(from > RI_SIZE_MAX)
            to = RI_SIZE_MAX;
        else if(from < RI_SIZE_MIN)
            to = RI_SIZE_MIN;
        else
            to = (ri_size)from;

        return to;
    }

    RI_API ri_ssize  ri_double_to_ssize(double from)
    {
        ri_ssize to;

        if(from > RI_SSIZE_MAX)
            to = RI_SSIZE_MAX;
        else if(from < RI_SSIZE_MIN)
            to = RI_SSIZE_MIN;
        else
            to = (ri_ssize)from;

        return to;
    }

    RI_API float  ri_double_to_float(double from)
    {
        float to;

        if(from > RI_FLOAT_MAX)
            to = RI_FLOAT_MAX;
        else if(from < RI_FLOAT_MIN)
            to = RI_FLOAT_MIN;
        else
            to = (ri_float)from;

        return to;
    }

    RI_API ri_float32  ri_double_to_float32(double from)
    {
        ri_float32 to;

        if(from > RI_FLOAT32_MAX)
            to = RI_FLOAT32_MAX;
        else if(from < RI_FLOAT32_MIN)
            to = RI_FLOAT32_MIN;
        else
            to = (ri_float32)from;

        return to;
    }

    RI_API ri_float64  ri_double_to_float64(double from)
    {
        ri_float64 to;

        if(from > RI_FLOAT64_MAX)
            to = RI_FLOAT64_MAX;
        else if(from < RI_FLOAT64_MIN)
            to = RI_FLOAT64_MIN;
        else
            to = (ri_float64)from;

        return to;
    }

    RI_API int ri_ptr_sub_ptr(unsigned int *ptr_a, unsigned int *ptr_b)
    {
		unsigned int uint_a =  *ptr_a;
		unsigned int uint_b =  *ptr_b;

        return uint_a - uint_b;
    }

    //RI_API RI_COMPARE_t ri_memcmp(const ri_byte *a, const ri_byte *b, size_t size)
    //{
    //  RI_COMPARE_t compare;
    //  size_t i;
    //  
    //  if(a == NULL && b == NULL)  return RI_COMPARE_UNKNOWN;
    //  if(size == 0)  return RI_COMPARE_UNKNOWN;
    //  if(a == NULL)  return RI_LESS;  
    //  if(b == NULL)  return RI_GREAT;
    //  
    //
    //  compare = RI_EQUAL; 
    //
    //  for(i = 0; i< size; i++)
    //  {
    //    if(a[i] < b[i])
    //    {
    //      compare = RI_LESS;
    //      i = size;
    //    }
    //    else if(a[i] > b[i])
    //    {
    //      compare = RI_GREAT;
    //      i = size;
    //    }
    //  }  
    //
    //  return compare;                        
    //}

#ifdef __cplusplus
}
#endif

