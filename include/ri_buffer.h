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

#ifndef __RI_BUFFER_H__
#define __RI_BUFFER_H__

#include "openri.h"

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct {
        ri_byte *buf;
        int size;
        int length;
        int align;
    } RiBuffer_t;

    RiBuffer_t *RiBuffer_New(int size, int align);

    int RiBuffer_Free(RiBuffer_t *buffer);

    int RiBuffer_SetSize(RiBuffer_t *buffer, int size);

    int RiBuffer_Append(RiBuffer_t *buffer, ri_byte *buf, int length);

    int RiBuffer_GetLength(RiBuffer_t *buffer);

    int RiBuffer_GetSize(RiBuffer_t *buffer);

    int RiBuffer_Get(RiBuffer_t *buffer, ri_byte *buf, int length);

    int RiBuffer_Empty(RiBuffer_t *buffer);

    int RiBuffer_SetLength(RiBuffer_t *buffer, int length);

    int RiBuffer_Search(RiBuffer_t *buffer, ri_byte *buf, int length);

    int RiBuffer_Print(RiBuffer_t *buffer);

    int RiBuffer_PrintHex(RiBuffer_t *buffer);

    int RiBuffer_Set(RiBuffer_t *buffer, int value);

#ifdef __cplusplus
}
#endif

#endif /* __RI_BUFFER_H__ */
