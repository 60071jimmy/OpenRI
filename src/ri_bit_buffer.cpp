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
* @name ri_bit_buffer.c
*
* @brief Bit buffer library.
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


//#include <gt_ll.h>
#include "openri.h"

#ifdef __cplusplus
extern "C" 
{
#endif

    RI_API int RiBitBuffer_Init(RiBitBuffer_t *buffer)
    {
        if(buffer == NULL)  return RI_ERROR_NULL_POINTER;

        ri_memset(buffer, 0, sizeof(RiBitBuffer_t));

        buffer->riArray = RiArray_New((unsigned char*)"ri_byte", sizeof(ri_byte), 0);

        return RI_OK;
    }

    RI_API RiBitBuffer_t *RiBitBuffer_New(void)
    {
        RiBitBuffer_t *buffer;

        buffer = (RiBitBuffer_t *)ri_calloc(1, sizeof(RiBitBuffer_t));

        if(buffer == NULL)
        {
            return NULL;
        }

        buffer->riArray = RiArray_New((unsigned char*)"ri_byte", sizeof(ri_byte), 0);

        return buffer;
    }

    RI_API int RiBitBuffer_SetBuffer(RiBitBuffer_t *buffer, ri_byte *data, size_t dataSize)
    {
        size_t i;
        ri_utf8 j;
        ri_byte bit;

        if(data == NULL && dataSize != 0)  return RI_ERROR_NULL_POINTER;

        //  ri_dbg("1" RI_NL);

        RiArray_SetLength(buffer->riArray, (int)(dataSize * 8));

        //  ri_dbg("2" RI_NL);

        if(dataSize == 0)
        {
            return RI_OK;
        }

        //  ri_dbg("3" RI_NL);

        for(i = 0; i < dataSize; i ++)
        {
            for(j = 0; j < 8; j ++)
            {
                bit = data[i] & (1 << (7-j));
                if(bit > 0) bit = 1;
                //      ri_dbg("RiArray_Set(%d, %d)=%d" RI_NL, i, j, bit);
                RiArray_Set(buffer->riArray, (int)i * 8 + j, &bit);    
            }
        }

        //  ri_dbg("4" RI_NL);

        return RI_OK;
    }

    RI_API size_t RiBitBuffer_GetBitLength(RiBitBuffer_t *buffer)
    {
        size_t bit_len;

        bit_len = RiArray_GetLength(buffer->riArray);

        return bit_len;
    }

    RI_API size_t RiBitBuffer_GetBuffer(RiBitBuffer_t *buffer, ri_byte *data, size_t dataSize)
    {
        size_t i;
        ri_utf8 j;
        ri_byte bit;
        size_t bit_len;
        size_t byte_len;
        size_t mod;
        int ret;

        if(data == NULL)  return 0;
        if(dataSize == 0)  return 0;

        bit_len = RiArray_GetLength(buffer->riArray);

        byte_len = bit_len / 8;
        mod = bit_len % 8;

        if(mod > 0)
            byte_len ++;

        if(bit_len == 0 || byte_len > dataSize)
        {
            memset(data, 0, dataSize);
            return 0;
        }

        memset(data, 0, dataSize);

        //  ri_dbg("byte_len=%d, bit_len=%d" RI_NL, byte_len, bit_len);

        for(i = 0; i < byte_len; i ++)
        {
            for(j = 0; j < 8; j ++)
            {
                bit = 0;
                ret = RiArray_Copy(buffer->riArray,(int) i * 8 + j, &bit);
                //      ri_dbg("(%d, %d) ret=%d, bit=%d" RI_NL, i, j, ret, bit);
                data[i] |= bit << (7-j);
            }
        }

        return byte_len;
    }

    RI_API int RiBitBuffer_Free(RiBitBuffer_t *buffer)
    {

        RiArray_Free(buffer->riArray);

        ri_free(buffer);
        return RI_OK;
    }

    RI_API ri_byte RiBitBuffer_GetBit(RiBitBuffer_t *buffer, size_t index)
    {
        ri_byte   bit;
        size_t bit_len;

        bit_len = RiArray_GetLength(buffer->riArray);

        if(bit_len == 0 || bit_len <= index)
        {
            return 0;
        }

        bit = 0;
        RiArray_Copy(buffer->riArray, (int)index, &bit);

        return bit;
    }

    RI_API int RiBitBuffer_InsertBit(RiBitBuffer_t *buffer, size_t index, ri_byte bit)
    {
        int ret;

        if(bit > 0) bit = 1;

        ret = RiArray_Insert(buffer->riArray, (int)index, &bit);

        return ret;  
    }

    RI_API int RiBitBuffer_SetBit(RiBitBuffer_t *buffer, size_t index, ri_byte bit)
    {
        int ret;

        if(bit > 0) bit = 1;

        ret = RiArray_Set(buffer->riArray, (int)index, &bit);

        return ret;  
    }


#ifdef __cplusplus
}
#endif

