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

#ifndef __RI_LOCK_H__
#define __RI_LOCK_H__

#include "openri.h"

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct {
        void *mutex;
    } RiLock_t;

    RI_API RiLock_t *RiLock_New();

    RI_API int RiLock_Free(RiLock_t *lock);

    inline RI_API int RiLock_Lock(RiLock_t *lock);

    inline RI_API int RiLock_Unlock(RiLock_t *lock);

#ifdef __cplusplus
}
#endif

#endif /* __RI_LOCK_H__ */
