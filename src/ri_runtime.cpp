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


#if defined(RI_ANDROID)
#include <cpu-features.h>
#endif // RI_CONFIG_ANDROID

#ifdef __cplusplus
extern "C" 
{
#endif

    static int riRuntimeIsInit = 0;

    int RiRuntime_InitLib() {
        if (riRuntimeIsInit == 1) {
            return RI_OK_INIT_ALREADY;
        }
        riRuntimeIsInit = 1;

        return RI_OK;
    }

    int RIRuntime_GetCpuCount() {
#if defined(RI_ANDROID)
        return android_getCpuCount();
#elif defined(RI_IOS)
        return RI_ERROR_NOT_SUPPORT;
#elif defined(RI_LINUX)
        return RI_ERROR_NOT_SUPPORT;
#elif defined(RI_WINDOWS)
        return RI_ERROR_NOT_SUPPORT;
#else
        //	#error OS is not defined!
#endif
    }

#ifdef __cplusplus
}
#endif
