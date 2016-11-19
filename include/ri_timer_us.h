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

#ifndef __RI_TIMER_US_H__
#define __RI_TIMER_US_H__

#include "openri.h"

typedef struct {
    ri_int64     start;
    ri_int64     end;
} RiTimerUs_t;

#ifdef __cplusplus
extern "C" 
{
#endif

    RiTimerUs_t *RiTimerUs_New();

    int RiTimerUs_Free(RiTimerUs_t *timerUs);

    ri_int64 RiTimerUs_GetTimeStamp();

    int RiTimerUs_Start(RiTimerUs_t *timerUs);

    int RiTimerUs_Stop(RiTimerUs_t *timerUs);

    ri_int64 RiTimerUs_GetUs(RiTimerUs_t *timerUs);

#ifdef __cplusplus
}
#endif

#endif /* __RI_TIMER_US_H__ */
