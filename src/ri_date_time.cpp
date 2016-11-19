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

/**
* @name ri_date_time.c
*
* @brief Date time library.
*
* @reference  
*
* @author Mingta Li 
*
* @version 2.1.0
* 
* @history 2009-07-02     Re-organize.                 Mingta Li 
* @history 2006-07-20     Initial version.             Mingta Li  
*
*/

#include "openri.h"


#ifdef __cplusplus
extern "C" 
{
#endif

    RI_API int RiDateTime_Init(RiDateTime_t *date_time)
    {
        if(date_time == NULL) return RI_ERROR_NULL_POINTER;

        ri_memset(date_time, 0, sizeof(RiDateTime_t));

        return RI_OK;
    }

    RI_API RiDateTime_t *RiDateTime_New(void)
    {
        RiDateTime_t *date_time;

        date_time = (RiDateTime_t *)ri_calloc(1, sizeof(RiDateTime_t));
        if(date_time == NULL)
        {
            return NULL;
        }

        return date_time;
    }
}


