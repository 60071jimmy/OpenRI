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

#ifndef __RI_LOG_H__
#define __RI_LOG_H__


#include "openri.h"

#if defined(RI_ANDROID)
#include <android/log.h>
#endif


#ifdef __cplusplus
extern "C" 
{
#endif

	RI_API int RiLog_Open(char *fileName);
    RI_API int RiLog_Log(char *str);
    RI_API int RiLog_Close();

#if defined(RI_ANDROID)//RI_ANDROID
    /**
    * ????Log???????TAG
    */
#define RI_LOG_TAG "RiLib"
    //#if !defined(__OPTIMIZE__) && defined(RI_DEBUG)
#if  defined(RI_DEBUG)
    /**
    * ????Log???????TAG
    */
#define RI_LOG_TAG "RiLib"
    /**
    * ??__android_log_print?Log???Log????ANDROID_LOG_INFO
    */
#define RI_LOGI(...) __android_log_print(ANDROID_LOG_INFO, RI_LOG_TAG, __VA_ARGS__);
    /**
    * ??__android_log_print?Log???Log????ANDROID_LOG_ERROR
    */
#define RI_LOGE(...) __android_log_print(ANDROID_LOG_ERROR, RI_LOG_TAG, __VA_ARGS__);
    //#define PDEBUG(fmt, ...) fprintf(stderr, "[%s:%d] %s: " fmt "\n", __FILE__, __LINE__, __func__, ## __VA_ARGS__)
#else
    /**
    * ??DEBUG????????print??
    */
#define RI_LOGI(...) {}
    /**
    * ??DEBUG????????print??
    */
#define RI_LOGE(...) {}
#endif

#elif defined(RI_WINDOWS)//RI_IOS

#if !defined(__OPTIMIZE__) && defined(RI_DEBUG)
    int RiLog_Log_Old(const char * __restrict format, ...);
#define RI_LOGI(fmt, ...) RiLog_Log_Old(fmt, ## __VA_ARGS__);
#define RI_LOGE(fmt, ...) RiLog_Log_Old(fmt, ## __VA_ARGS__);
    //#define RI_LOGE(...) RiLog_Log_Old(__VA_ARGS__);
    //#define PDEBUG(fmt, ...) fprintf(stderr, "[%s:%d] %s: " fmt "\n", __FILE__, __LINE__, __func__, ## __VA_ARGS__)
#else
#define RI_LOGI(...) {}
#define RI_LOGE(...) {}
    //#define PDEBUGG(args...)
#endif

#elif defined(RI_LINUX)

#if !defined(__OPTIMIZE__) && defined(__OPTIMIZE__)
    int RiLog_Log_Old(const char * __restrict format, ...);
#define RI_LOGI(fmt, ...) RiLog_Log_Old(fmt, ## __VA_ARGS__);
#define RI_LOGE(fmt, ...) RiLog_Log_Old(fmt, ## __VA_ARGS__);
    //#define RI_LOGE(...) RiLog_Log_Old(__VA_ARGS__);
    //#define PDEBUG(fmt, ...) fprintf(stderr, "[%s:%d] %s: " fmt "\n", __FILE__, __LINE__, __func__, ## __VA_ARGS__)
#else
#define RI_LOGI(...) {}
#define RI_LOGE(...) {}
    //#define PDEBUGG(args...)
#endif

#else
    //   #error OS is undefined!
#endif


#ifdef __cplusplus
}
#endif

#endif /* __RI_LOG_H__ */
