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

#ifndef __RI_RET_H__
#define __RI_RET_H__

#include "openri.h"

#ifdef __cplusplus
extern "C"
{
#endif
    
    typedef enum {
        RI_RET_MAX                    =  4,      // Maximum.

        RI_OK_DONE_ALREADY            =  3,      // Done already.
        RI_OK_INIT_ALREADY            =  2,      // Init already but OK.
        RI_OK                       =  1,      // Success.
        RI_ERROR                    =  0,      // Error.
        RI_ERROR_NO_MATCH             = -1,      // No match parameter.
        RI_ERROR_NOT_DEFINED          = -2,      // Not defined yet.
        RI_ERROR_INVALID_ACC_TYPE     = -3,      // Invalid acceleration type.
        RI_ERROR_OPEN_FILE            = -4,      // Open file fail.
        RI_ERROR_SET_LOCALE           = -5,      // Set locale fail.
        RI_ERROR_AXIS_COUNT           = -6,      // Axis count mismatch.
        RI_ERROR_DEVICE_ID            = -7,      // Device id mismatch.
        RI_ERROR_DEVICE_NAME          = -8,      // Device name mismatch.
        RI_ERROR_DEVICE_TYPE          = -9,      // Device type mismatch.
        RI_ERROR_BUSY                 = -10,     // Busy and in use.
        RI_ERROR_KEY                  = -11,     // Key error.
        RI_ERROR_NO_MEMORY            = -12,     // Not enough memory.
        RI_ERROR_RANGE                = -13,     // Out of range.
        RI_ERROR_MOTION_LOCK          = -14,     // Motion is locked.
        RI_ERROR_WRONG_PARAMETER      = -15,     // Parameter is wrong.
        RI_ERROR_NOT_OPENED           = -16,     // File is not opened.
        RI_ERROR_NOT_INIT             = -17,     // Not init.
        RI_ERROR_NOT_SUPPORT_FUNCTION = -18,     // Not support this function yet.
        RI_ERROR_NOT_SUPPORT_FORMAT   = -19,     // Not support this format yet.
        RI_ERROR_NULL_POINTER         = -20,     // NULL pointer.
        RI_ERROR_NOT_CLOSED           = -21,     // File is not closed.
        RI_ERROR_EMPTY                = -22,     // Empty.
        RI_ERROR_NOT_SUPPORT_DEVICE   = -23,     // Not support this device yet.
        RI_ERROR_BUFFER_OVERRUN       = -24,     // Buffer overrun.
        
        RI_ERROR_VERSION              = -26,     // Version is wrong.
        RI_ERROR_NOT_SUPPORT          = -27,     // Not support.
        RI_ERROR_NOT_SUPPORT_TYPE     = -28,     // Not support type.
        RI_ERROR_ZERO                 = -29,     // Error because of "Zero" value.
        RI_ERROR_TIMEOUT              = -30,     // Timeout.
        RI_ERROR_LICENSE              = -31,     // Timeout.
        RI_ERROR_FULL                 = -32,     // Full.
        RI_ERROR_ALREADY_OPENED       = -33,     // Already opened.
        RI_ERROR_ALIGNMENT            = -34,     // Alignment.
        RI_ERROR_CRC                  = -35,     // CRC.
        RI_ERROR_TYPE                 = -36,     // Type.
        RI_ERROR_NOT_FOUND                = -37,      // NOT FOUND .

        RI_ERROR_COLOR_MODE           = -38,     // Color mode.
        RI_ERROR_NEW_LOCK             = -39,     // New lock.
        RI_ERROR_NEW_OBJECT           = -40,     // New object.
        RI_ERROR_INIT_ALREADY         = -41,     // Init already.

        RI_ERROR_ENOMEM               = -42,

        RI_ERROR_PARAMETER_WRONG      = -43,

        RI_ERROR_PARAMETER_0          = -100,    // Parameter 0 is wrong.
        RI_ERROR_PARAMETER_1          = -101,    // Parameter 1 is wrong.
        RI_ERROR_PARAMETER_2          = -102,    // Parameter 2 is wrong.
        RI_ERROR_PARAMETER_3          = -103,    // Parameter 3 is wrong.
        RI_ERROR_PARAMETER_4          = -104,    // Parameter 4 is wrong.
        RI_ERROR_PARAMETER_5          = -105,    // Parameter 5 is wrong.
        RI_ERROR_PARAMETER_6          = -106,    // Parameter 6 is wrong.
        RI_ERROR_PARAMETER_7          = -107,    // Parameter 7 is wrong.
        RI_ERROR_PARAMETER_8          = -108,    // Parameter 8 is wrong.
        RI_ERROR_PARAMETER_9          = -109,    // Parameter 9 is wrong.
        RI_ERROR_PARAMETER_10         = -110,    // Parameter 10 is wrong.

        RI_RET_MIN                    = -111     // Minimum.
    } GT_RET_t;

#ifdef __cplusplus
}
#endif

#endif /* __RI_RET_H__ */
