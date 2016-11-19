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

#ifndef __RI_COLOR_H__
#define __RI_COLOR_H__

#include "openri.h"

typedef enum {
    RI_COLOR_MODE_UNKNOWN   = 0,
    RI_COLOR_MODE_RGB888    = 1,
    RI_COLOR_MODE_GRAY8     = 2,
    RI_COLOR_MODE_RGB565    = 3,
    RI_COLOR_MODE_ARGB8888  = 4,
    RI_COLOR_MODE_ARGB4444  = 5,
    // RI_COLOR_MODE_BLOB,  
    // RI_COLOR_MODE_YCbCr888,
    // RI_COLOR_MODE_ARGB8888,  
    // RI_COLOR_MODE_RGB565,
    // RI_COLOR_MODE_ARGB1555,
    // RI_COLOR_MODE_ARGB4444,
    // RI_COLOR_MODE_ARGB5676,
    // RI_COLOR_MODE_ARGB8565,
    // RI_COLOR_MODE_YUY2,            // 16-bit 4:2:2.
    // RI_COLOR_MODE_IMC2,            // 12-bit 4:2:0.
    // RI_COLOR_MODE_IMC4,            // 12-bit 4:2:0.
    // RI_COLOR_MODE_YV12,            // 12-bit 4:2:0.
    // RI_COLOR_MODE_iYUV,            // 12-bit 4:2:0.
    // RI_COLOR_MODE_NV12,            // 12-bit 4:2:0.
    // RI_COLOR_MODE_IMC1,            // 16-bit 4:2:0.
    // RI_COLOR_MODE_IMC3,            // 16-bit 4:2:0.
    // RI_COLOR_MODE_UYVY,            // 16-bit 4:2:2.
    // RI_COLOR_MODE_AYUV,            // 32-bit 4:4:4.
    // RI_COLOR_MODE_YUV,
    RI_COLOR_MODE_COUNT
} RI_COLOR_MODE_t;

typedef struct {
    RI_COLOR_MODE_t  mode;

    ri_uint8         red8;
    ri_uint8         green8;
    ri_uint8         blue8;
    ri_uint8         alpha8;

    ri_uint8         gray8;

    ri_uint8         y8;
    ri_uint8         cb8;
    ri_uint8         cr8;

    ri_uint16        red16;
    ri_uint16        green16;
    ri_uint16        blue16;

    ri_uint16        gray16;
} RiColor_t;  

#ifdef __cplusplus
extern "C"
{
#endif

    RiColor_t *RiColor_New();

    int RiColor_Free(RiColor_t *color);

    int RiColor_SetRGB888(RiColor_t *color, int red8, int green8, int blue8);

    int RiColor_SetGRAY8(RiColor_t *color, int gray8);

    RI_COLOR_MODE_t RiColor_GetMode(RiColor_t *color);

    int RiColor_GetRed8(RiColor_t *color);

    int RiColor_GetGreen8(RiColor_t *color);

    int RiColor_GetBlue8(RiColor_t *color);

    int RiColor_GetGray8(RiColor_t *color);

#ifdef __cplusplus
}
#endif

#endif /* __RI_COLOR_H__ */
