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

#ifndef __RI_BIT_BUFFER_H__
#define __RI_BIT_BUFFER_H__

#include "openri.h"

#ifdef __cplusplus
extern "C" 
{
#endif

    typedef struct {
        RiArray_t         *riArray;
    } RiBitBuffer_t;


    RI_API int       RiBitBuffer_Init(RiBitBuffer_t *buffer);
    RI_API RiBitBuffer_t *RiBitBuffer_New(void);
    RI_API int       RiBitBuffer_SetBuffer(RiBitBuffer_t *buffer, ri_byte *data, size_t dataSize);
    RI_API size_t        RiBitBuffer_GetBitLength(RiBitBuffer_t *buffer);
    RI_API size_t        RiBitBuffer_GetBuffer(RiBitBuffer_t *buffer, ri_byte *data, size_t dataSize);
    RI_API int       RiBitBuffer_Free(RiBitBuffer_t *buffer);
    RI_API ri_byte        RiBitBuffer_GetBit(RiBitBuffer_t *buffer, size_t index);
    RI_API int       RiBitBuffer_InsertBit(RiBitBuffer_t *buffer, size_t index, ri_byte bit);
    RI_API int       RiBitBuffer_SetBit(RiBitBuffer_t *buffer, size_t index, ri_byte bit);


#ifdef __cplusplus
}
#endif

#endif /* __RI_BIT_BUFFER_H__ */


