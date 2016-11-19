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

#include <xmmintrin.h> // SSE
#include <immintrin.h> // AVX
#include <intrin.h> // for __movsb, __movsd, __movsq
#include <windows.h>

#include "openri.h"

#ifdef __cplusplus
extern "C" 
{
#endif

    RI_API void *ri_memset(void *ptr, int value, int num) {
        if (ptr == NULL) {
            return NULL;
        }

        if (value < 0) {
            return NULL;
        }

        if (num < 0) {
            return NULL;
        }

        return memset(ptr, value, num);
    }
	

	RI_API void *ri_memcpy(void *destination, const void *source, size_t num) {
		return memcpy(destination, source, num);

		// Generating code is too slow.
		int enableAcc = 1;

		if ((((unsigned long long)destination) % 16) != 0) {
			enableAcc = 0;
		} else if ((((unsigned long long)source) % 16) != 0) {
			enableAcc = 0;
		} else if (num % 32 != 0) {
			enableAcc = 0;
		}

		if (enableAcc == 0) {
			return memcpy(destination, source, num);
		}

		unsigned char *dst = (unsigned char *)destination;
		unsigned char *src = (unsigned char *)source;

		// Accelerate by using SSE2
		// dst and src must be 16-byte aligned
		// size must be multiple of 16*2 = 32 bytes
		size_t stride = 2 * sizeof(__m128);
			while (num) {
			__m128 a = _mm_load_ps((float*)(src));
			__m128 b = _mm_load_ps((float*)(src + sizeof(__m128)));
			_mm_stream_ps((float*)(dst), a);
			_mm_stream_ps((float*)(dst + sizeof(__m128)), b);

			num -= stride;
			src += stride;
			dst += stride;
		}

		return destination;
	}


    RI_API void *ri_memmove(void *destination, const void *source, int num) {
        if (destination == NULL) {
            return NULL;
        }

        if (source == NULL) {
            return NULL;
        }

        if (num < 0) {
            return NULL;
        }

        return memmove(destination, source, num);
    }

    RI_API int ri_memcmp(const void *ptr1, const void *ptr2, int num) {
        if (ptr1 == NULL) {
            return RI_ERROR_PARAMETER_0;
        }

        if (ptr2 == NULL) {
            return RI_ERROR_PARAMETER_1;
        }

        if (num < 0) {
            return RI_ERROR_PARAMETER_2;
        }

        return memcmp(ptr1, ptr2, num);
    }

#ifdef __cplusplus
}
#endif
