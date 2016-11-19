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

#ifndef __RI_MEM_H__
#define __RI_MEM_H__

#include "openri.h"

#ifdef  __cplusplus
extern "C" {
#endif

    // Memory barrier for share memory multi-processors.
#if defined(RI_GCC)
#include <unistd.h>

#if defined(RI_X86)
	#define ri_mb()    asm volatile("mfence":::"memory")
#elif defined(RI_ARM)
	#define ri_mb()    asm volatile ("dmb" ::: "memory")
#elif defined(RI_SH4)
	#define ri_mb()    asm volatile("": : :"memory")
#elif defined(RI_IXP435)
	#define ri_mb()    asm volatile("": : :"memory")
#else
	#error CPU is not defined!
#endif

//#elif defined(RI_VC)
#elif defined(RI_VC)
	#define ri_mb() __asm {mfence}
#else
	#error Compiler is not defined!
#endif

    RI_API int RiMem_PrintInfo();

    RI_API void *ri_malloc(int size);

    RI_API void *ri_calloc(int num, int size);

    RI_API void *ri_realloc(void *ptr, int size);

    RI_API void ri_free(void *ptr);

	RI_API void *ri_aligned_malloc(size_t size, size_t alignment);

	RI_API void ri_aligned_free(void *memblock);

#ifdef  __cplusplus
}
#endif

#endif  /* __RI_MEM_H__ */
