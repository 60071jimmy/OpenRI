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

#include <malloc.h>

#include "openri.h"


#ifdef __cplusplus
extern "C" 
{
#endif

    static volatile int riMemMallocGood  = 0;
    static volatile int riMemMallocBad   = 0;
    static volatile int riMemMallocZero  = 0;

    static volatile int riMemCallocGood  = 0;
    static volatile int riMemCallocBad   = 0;
    static volatile int riMemCallocZero  = 0;

    static volatile int riMemReallocGood = 0;
    static volatile int riMemReallocBad  = 0;
    static volatile int riMemReallocZero = 0;

    static volatile int riMemFreeGood = 0;
    static volatile int riMemFreeNull = 0;

    RI_API void *ri_malloc(int size) {
        void *ptr;

        if (size < 0) {
            riMemMallocBad ++;
            return NULL;
        }

        if (size == 0) {
            riMemMallocZero ++;
            return NULL;
        }

        ptr = malloc(size);
        if (ptr == NULL) {
            riMemMallocBad ++;
            return NULL;
        }

        riMemMallocGood ++;

        return ptr;
    }

    RI_API void *ri_calloc(int num, int size) {
        void *ptr;

        if (num < 0) {
            riMemCallocBad ++;
            return NULL;
        }

        if (size < 0) {
            riMemCallocBad ++;
            return NULL;
        }

        if (num == 0) {
            riMemCallocZero ++;
            return NULL;
        }

        if (size == 0) {
            riMemCallocZero ++;
            return NULL;
        }

        ptr = calloc(num, size);
        if (ptr == NULL) {
            riMemCallocBad ++;
            return NULL;
        }

        riMemCallocGood ++;

        return ptr;
    }

    RI_API void *ri_realloc(void *ptr, int size) {
        void *ptrNew;

        if (size < 0) {
            riMemReallocBad ++;
            if (ptr != NULL) {
                free(ptr);	
            }
            return NULL;
        }

        if (size == 0) {
            riMemReallocZero ++;
            if (ptr != NULL) {
                free(ptr);	
            }
            return NULL;
        }

        ptrNew = realloc(ptr, size);
        if (ptrNew == NULL) {
            riMemReallocBad ++;
            return NULL;
        }

        riMemReallocGood ++;

        return ptrNew;
    }


    RI_API void ri_free(void *ptr) {
        if (ptr == NULL) {
            riMemFreeNull ++;
            return;
        }

        free (ptr);

        riMemFreeGood ++;

        return;
    }

	RI_API void *ri_aligned_malloc(size_t size, size_t alignment) {
		return _aligned_malloc(size, alignment);
	}

	void ri_aligned_free(void *memblock) {
		_aligned_free (memblock);
		return;
	}

    RI_API int RiMem_PrintInfo() {
#if !defined(RI_WINDOWS)
        RI_LOGI("Malloc Count", riMemMallocGood + riMemMallocBad + riMemMallocZero);
        RI_LOGI("Malloc Good", riMemMallocGood);
        RI_LOGI("Malloc Bad", riMemMallocBad);
        RI_LOGI("Malloc Zero", riMemMallocZero);

        RI_LOGI("Calloc Count", riMemCallocGood + riMemCallocBad + riMemCallocZero);
        RI_LOGI("Calloc Good", riMemCallocGood);
        RI_LOGI("Calloc Bad", riMemCallocBad);
        RI_LOGI("Calloc Zero", riMemCallocZero);

        RI_LOGI("Realloc Count", riMemReallocGood + riMemReallocBad + riMemReallocZero);
        RI_LOGI("Realloc Good", riMemReallocGood);
        RI_LOGI("Realloc Bad", riMemReallocBad);
        RI_LOGI("Realloc Zero", riMemReallocZero);

        RI_LOGI("Free Count", riMemFreeGood + riMemFreeNull);
        RI_LOGI("Free Good", riMemFreeGood);
        RI_LOGI("Free NULL", riMemFreeNull);
#endif
        return RI_OK;
    }

#ifdef __cplusplus
}
#endif
