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

#ifndef __RI_ARRAY_H__
#define __RI_ARRAY_H__

#include "openri.h"

#ifdef __cplusplus
extern "C" 
{
#endif

    typedef struct {
        ri_utf8           elementType[RI_PAGE_SIZE];
        int            elementSize;
        int            length;
        int            realLength;
        int            reservedLength;
        ri_byte          *data;

        
    } RiArray_t;


    RI_API RiArray_t *RiArray_New(ri_utf8 *elementType, int elementSize, int reservedLength);
    RI_API ri_utf8   *RiArray_GetElementType(RiArray_t *riArray);
    RI_API int     RiArray_GetElementSize(RiArray_t *riArray);
    RI_API int   RiArray_Free(RiArray_t *riArray);
    RI_API ri_ptr     RiArray_Get(RiArray_t *riArray, int index);
    RI_API int   RiArray_Copy(RiArray_t *riArray, int index, ri_ptr element);
    RI_API int   RiArray_Append(RiArray_t *riArray, ri_ptr element);
    RI_API int   RiArray_Insert(RiArray_t *riArray, int index, ri_ptr element);
    RI_API int   RiArray_Remove(RiArray_t *riArray, int index);
    RI_API int   RiArray_SetReservedLength(RiArray_t *riArray, int reservedLength);
    RI_API int     RiArray_GetRealLength(RiArray_t *riArray);
    RI_API int     RiArray_GetLength(RiArray_t *riArray);
    RI_API int   RiArray_Check(RiArray_t *riArray);
    RI_API int   RiArray_SetLength(RiArray_t *riArray, int length);
    RI_API int   RiArray_SetRealLength(RiArray_t *riArray, int realLength);
    RI_API int   RiArray_CheckElementType(RiArray_t *riArray, ri_utf8 *elementType);
    RI_API int   RiArray_Set(RiArray_t *riArray, int index, ri_ptr element);
    RI_API int   RiArray_Sort(RiArray_t  *riArray, RiCompare_f compareFunction);

    RI_API int RiArray_Init(RiArray_t *riArray, ri_utf8 *elementType, int elementSize, int reservedLength);
    RI_API int RiArray_GetReservedLength(RiArray_t *riArray);

#ifdef __cplusplus
}
#endif

#endif /* __RI_ARRAY_H__ */
