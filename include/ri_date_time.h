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

#ifndef __RI_DATE_TIME_H__
#define __RI_DATE_TIME_H__

#include "openri.h"

#ifdef __cplusplus
extern "C" 
{
#endif

    typedef struct {
        ri_int64          year;
        ri_int8           month;
        ri_int8           day;
        ri_int8           hour;
        ri_int8           min;
        ri_int8           sec;
        ri_int16          ms;   
        ri_int16          us; 
        ri_int16          ns;
        ri_int16          ps;
        ri_int16          fs;
    } RiDateTime_t;


    RI_API int      RiDateTime_Init(RiDateTime_t *date_time);
    RI_API RiDateTime_t *RiDateTime_New(void);


#ifdef __cplusplus
}
#endif

#endif /* __RI_DATE_TIME_H__ */
