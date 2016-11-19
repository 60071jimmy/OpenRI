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

#ifndef __RI_THREAD_H__
#define __RI_THREAD_H__

#include "openri.h"

#if defined(RI_WINDOWS)
#include <windows.h>
#else
#include <unistd.h>
#include <pthread.h>
#endif

#define RI_THREAD_NAME_SIZE 32
#define RI_THREAD_ID_ERROR (-1)

#if defined(RI_WINDOWS)
#define RiThread_SleepMs(ms) Sleep(ms)
#define RiThread_SleepUs(us) Sleep(us/1000)
#define RiThread_Yield()     Sleep(0)
#else
#define RiThread_SleepMs(ms) usleep(ms*1000)
#define RiThread_SleepUs(us) usleep(us)
#define RiThread_Yield()     usleep(0)
#endif


#ifdef __cplusplus
extern "C"
{
#endif

    int riThread_InitLib();

    typedef void *(*RiThreadRoutine_t) (void *);

    typedef struct {
        //int	id;
        int	priority;
        int	isJoinable;
        //int	is_in_use;
        //int	is_closed;
#if defined(RI_WINDOWS)
        HANDLE       thread;
        DWORD        thread_id;
#else
        pthread_t    thread;
#endif
        ri_utf8      name[RI_THREAD_NAME_SIZE];

        RiThreadRoutine_t routine;

        void        *arg;

    } RiThread_t;

    RI_API RiThread_t *RiThread_New();

    RI_API int RiThread_Free(RiThread_t *thread);

    RI_API int RiThread_Start(RiThread_t *thread);

    // int RiThread_Cancel(RiThread_t *thread);

    RI_API int RiThread_GetPriorityMax(void);

    RI_API int RiThread_GetPriorityMin(void);

    RI_API int RiThread_GetPriorityNone(void);

    RI_API int RiThread_GetPriorityLow(void);

    RI_API int RiThread_GetPriorityNormal(void);

    RI_API int RiThread_GetPriorityHigh(void);

    RI_API int RiThread_GetPriorityUrgent(void);

    RI_API int RiThread_SetPriority(RiThread_t *thread, int priority);

    RI_API int RiThread_SetIsJoinable(RiThread_t *thread, int isJoinable);

    RI_API int RiThread_SetRoutine(RiThread_t *thread, RiThreadRoutine_t routine);

    RI_API int RiThread_SetArg(RiThread_t *thread, void *arg);

#ifdef __cplusplus
}
#endif

#endif /* __RI_THREAD_H__ */
