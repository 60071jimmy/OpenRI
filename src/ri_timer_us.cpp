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

#ifdef __cplusplus
extern "C" 
{
#endif

    RiTimerUs_t *RiTimerUs_New() {
        RiTimerUs_t *timerUs;

        timerUs = (RiTimerUs_t *)ri_calloc(1, sizeof(RiTimerUs_t));
        if (timerUs == NULL) {
            return NULL;
        }

        return timerUs;
    }

    int RiTimerUs_Free(RiTimerUs_t *timerUs) {
        if (timerUs == NULL) return RI_ERROR_NULL_POINTER;

        ri_free(timerUs);

        return RI_OK;
    }

    ri_int64 RiTimerUs_GetTimeStamp() {
        struct timeval tv;
        // gettimeofday(&tv,NULL);
        return (ri_int64)(tv.tv_sec * (ri_uint64)1000000 + tv.tv_usec);
    }

    int RiTimerUs_Start(RiTimerUs_t *timerUs) {
        if (timerUs == NULL) return RI_ERROR_NULL_POINTER;

        timerUs->start = RiTimerUs_GetTimeStamp();

        return RI_OK;
    }

    int RiTimerUs_Stop(RiTimerUs_t *timerUs) {
        if (timerUs == NULL) return RI_ERROR_NULL_POINTER;

        timerUs->end = RiTimerUs_GetTimeStamp();

        return RI_OK;
    }

    ri_int64 RiTimerUs_GetUs(RiTimerUs_t *timerUs) {
        if (timerUs == NULL) return RI_ERROR_NULL_POINTER;

        return timerUs->end - timerUs->start;
    }

#ifdef __cplusplus
}
#endif
