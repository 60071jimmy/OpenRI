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

#include "ri_runtime.h"
#include "openri.h"

#if defined(RI_ANDROID)
#include <android/log.h>
#endif // RI_ANDROID

static HANDLE rilogFile = INVALID_HANDLE_VALUE;


#ifdef __cplusplus
extern "C" 
{
#endif

#if defined(RI_WINDOWS)
    int riLog_EncodeWCharToUtf8 (const WCHAR *wstr, char *str, int strSize) {
        int len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);

        if (len > 0 && strSize > len) {
            len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, (LPSTR)str, strSize, NULL, NULL);}
        else if (len > 0) {
            len = -1; // String size is not enough.
        } else {
            len = -2; // WCHAR length is 0.
        }

        return len;
    }
#endif

    RI_API int RiLog_Open (char *fileName) {
#if defined(RI_WINDOWS)
        DWORD  pos;
        WCHAR *wideCharFileName = NULL;
        int len = MultiByteToWideChar(CP_ACP, 0, fileName, -1, NULL, 0);

        if (len <= 0) {
            return -1;
        }
        // TODO: Check
        //wideCharFileName = (WCHAR *)malloc(len + sizeof(WCHAR));
        wideCharFileName = (WCHAR *)malloc(len * sizeof(WCHAR));
        if (wideCharFileName == NULL) {
            return -2;
        }
        // TODO: Check
        len = MultiByteToWideChar(CP_ACP, 0, fileName, -1, (LPWSTR)wideCharFileName, len);

        if (len <= 0) {
            return -3;
        }

        rilogFile = CreateFileW((LPCWSTR)wideCharFileName, GENERIC_ALL, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);	
        pos = SetFilePointer(rilogFile, 0, NULL, FILE_END);

        free(wideCharFileName);

        return 1;
#
#endif
    }

    RI_API int RiLog_Log (char *str) {
#if defined(RI_WINDOWS)
        DWORD bytesWritten;
        char buf[RI_PAGE_SIZE];
        WCHAR wstr[RI_PAGE_SIZE];

        int len = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);
        if (len <= 0) {
            return -1;
        }

        len = MultiByteToWideChar(CP_ACP, 0,str, -1, (LPWSTR)wstr, 8192);
        if (len <= 0) {
            return -2;
        } else if (len >= RI_PAGE_SIZE) {
            return -3;
        }

        len = riLog_EncodeWCharToUtf8(wstr, buf, RI_PAGE_SIZE);
        if (len <= 0) {
            return -4;
        }

        BOOL writeSuccess = WriteFile(rilogFile, (char*)buf, len, &bytesWritten, NULL);
        if (!writeSuccess) {
            return -5;
        }

        writeSuccess = WriteFile(rilogFile, "\r\n", 2, &bytesWritten, NULL);
        if (!writeSuccess) {
            return -6;
        }

        return 1;
#endif
    }

    RI_API int RiLog_Close () {
#if defined(RI_WINDOWS)
        CloseHandle(rilogFile);
        rilogFile = INVALID_HANDLE_VALUE;

        return 1;
#endif
    }

	/**
    * @brief 基本的Log功能，把debug訊息print出來
    */
    int RiLog_Log_Old(const char * __restrict format, ...) {
//#if !defined(RI_WINDOWS)
#if defined(RI_WINDOWS)//RI_IOS
        va_list args;
        va_start(args,format);
        vfprintf(stdout, format, args);
        printf(format, args) ;
        va_end(args);
        fprintf(stdout, "\n");
        return 1;
#elif defined(RI_ANDROID)
        va_list args;
        va_start(args,format);
        __android_log_print(ANDROID_LOG_INFO, RI_LOG_TAG, format, args);
        va_end(args);
#elif defined(RI_PI)
#if defined(DEBUG)
        va_list args;
        va_start(args,format);
        vfprintf(stdout, format, args);
        va_end(args);
        fprintf(stdout, "\n");
#endif
#else
#error OS is undefined!
        va_list args;
        va_start(args,format);
        vfprintf(stdout, format, args);
        printf(format, args) ;
        va_end(args);
        fprintf(stdout, "\n");
#endif
//#endif
    }

#ifdef __cplusplus

}
#endif

