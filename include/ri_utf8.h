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

#ifndef __RI_UTF8_H__
#define __RI_UTF8_H__

#include "openri.h"

#define RI_WSTR_LENGTH (RI_STR_SIZE/2)
#define RI_CHAR_SIZE 5  // 4 bytes for UTF-8. 1 byte for ending.

#ifdef __cplusplus
extern "C" 
{
#endif

    RI_API ri_utf8 *RiUtf8_NextChar(const ri_utf8 *str);

    RI_API int RiUtf8_GetLength(const ri_utf8 *str);

    RI_API int RiUtf8_GetSize(const ri_utf8 *str); // The size and len is only matched in ASCII code.

    RI_API int RiUtf8_ToWchar(wchar_t *wstr, ri_int wstr_length, const ri_utf8 *str);

    RI_API int RiUtf8_FromWchar(ri_utf8 *str, ri_int str_size, const wchar_t *wstr);

    RI_API int RiUtf8_ToLowerCase(ri_utf8 *str);

    RI_API int RiUtf8_ToUpperCase(ri_utf8 *str);

    RI_API int RiUtf8_GetIndexShift(const ri_utf8 *str, ri_int index);

    RI_API int RiUtf8_GetIndex(const ri_utf8 *str, const ri_utf8 *str_find);

    RI_API int RiUtf8_GetLastIndex(const ri_utf8 *str, const ri_utf8 *str_find);

    RI_API int RiUtf8_SubString(ri_utf8 *str_to, ri_int str_to_size, const ri_utf8 *str_from, ri_int from, ri_int to);

    RI_API int RiUtf8_GetChar(const ri_utf8 *str, ri_int index, ri_utf8 *char_buf, ri_int char_buf_size);

    RI_API ri_utf8 *RiUtf8_GetCharAddress(const ri_utf8 *str, ri_int index);

#ifdef __cplusplus
}
#endif

#endif /* __RI_UTF8_H__ */
