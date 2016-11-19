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


static int riDbgIsEnabled = 1;


#ifdef __cplusplus
extern "C" 
{
#endif
    RI_API int RiDbg_Enable() {
        riDbgIsEnabled = 1;

        return 1;
    }

    RI_API int RiDbg_Disable() {
        riDbgIsEnabled = 0;

        return 1;
    }


    // Note: To get dbg message to work, you need to enable: C# property->debug-> Enable unmanaged code debugging
    int RiDbg_Dbg(char *format, ...) {
        if (riDbgIsEnabled <= 0) {
            return 1;
        }

		static RiLock_t *lock = RiLock_New();

		RiLock_Lock(lock);

        char str[RI_PAGE_SIZE];
        wchar_t strw[RI_PAGE_SIZE];

        va_list args;
        va_start(args, format);
        vsprintf_s(str, RI_PAGE_SIZE, format, args);

        MultiByteToWideChar(CP_UTF8, 
            0,         
            str, 
            -1,  // Byte length.       
            strw,  
            RI_PAGE_SIZE * sizeof(wchar_t));

        OutputDebugString(strw);
        OutputDebugStringA("\r\n");
        va_end(args);

		RiLock_Unlock(lock);

        return 1;
    }


#ifdef __cplusplus

}
#endif


