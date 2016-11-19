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

#if defined(RI_LINUX)
#include "fcntl.h"
#endif

#ifdef __cplusplus
extern "C"
{
#endif

    static int riSemaphoreIsInit = 0;
    static int riSemaphoreCount = 0;

    RI_API int RiSemaphore_InitLib() {
        if (riSemaphoreIsInit == 1) {
            return RI_OK_INIT_ALREADY;
        }
        riSemaphoreIsInit = 1;

        return RI_OK;
    }

    RI_API RiSemaphore_t *RiSemaphore_New(int count) {
        RiSemaphore_t *semaphore;
        if (riSemaphoreIsInit == 0) return NULL;
        if (count < 0) return NULL;

        semaphore = (RiSemaphore_t *)ri_calloc(1, sizeof(RiSemaphore_t));
        if (semaphore == NULL) {
            return NULL;
        }

#if defined(RI_LINUX)
        int ret = sem_init((sem_t *)&semaphore->sem, 0, count);
        if (ret != 0) {
            ri_free(semaphore);
            return NULL;
        }
#endif
        
        return semaphore;
    }

    RI_API int RiSemaphore_Free(RiSemaphore_t *semaphore) {

        if (semaphore == NULL) return RI_ERROR_NULL_POINTER;
        
#if defined(RI_LINUX)
        sem_destroy((sem_t *)&semaphore->sem);
#elif defined(RI_CONFIG_ANDROID)
        sem_destroy((sem_t *) &semaphore->sem);
#elif defined(RI_CONFIG_IOS)
        sem_close((sem_t *)semaphore->sem);

        sprintf(str, "RiSemaphore %d", semaphore->sn);
        sem_unlink(str);
#endif
        ri_free(semaphore);

        return RI_OK;

    }

    RI_API int RiSemaphore_Lock(RiSemaphore_t *semaphore) {

        if (semaphore == NULL) return RI_ERROR_NULL_POINTER;
        
#if defined(RI_LINUX)
        sem_wait((sem_t *)&semaphore->sem);
#endif
        return RI_OK;

    }

    RI_API int RiSemaphore_Unlock(RiSemaphore_t *semaphore) {

        if (semaphore == NULL) return RI_ERROR_NULL_POINTER;
        
#if defined(RI_LINUX)
        sem_post((sem_t *)&semaphore->sem);
#endif
        return RI_OK;

    }

#ifdef __cplusplus
}
#endif
