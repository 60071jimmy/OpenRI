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

#ifndef __RI_STRING_H__
#define __RI_STRING_H__

#include "openri.h"

#ifdef  __cplusplus
extern "C" {
#endif

    RI_API void *ri_memset(void *ptr, int value, int num);

    RI_API void *ri_memcpy(void *destination, const void *source, size_t num);

    RI_API void *ri_memmove(void *destination, const void *source, int num);

    RI_API int   ri_memcmp(const void *ptr1, const void *ptr2, int num);

#ifdef  __cplusplus
}
#endif

#endif  /* __RI_STRING_H__ */
