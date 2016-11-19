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

#ifndef __RI_IMAGE_H__
#define __RI_IMAGE_H__

#include "openri.h"

typedef struct {
    RI_COLOR_MODE_t   colorMode;
    ri_int            width;
    ri_int            height;
    ri_byte          *data;
    ri_int            dataSize;
} RiImage_t;

#ifdef __cplusplus
extern "C"
{
#endif

    RiImage_t *RiImage_New();

    int RiImage_Free(RiImage_t *image);

    int RiImage_Init(RiImage_t *image, int width, int height, int colorMode);

    int RiImage_GetColorMode(RiImage_t *image);

    int RiImage_SetColorMode(RiImage_t *image, int colorMode);

    int RiImage_Fill(RiImage_t *image, RiColor_t *color);

    int RiImage_GetPixelColor(RiImage_t *image, int x, int y, RiColor_t *color);

    int RiImage_DrawPixel(RiImage_t *image, int x, int y, RiColor_t *color);

    int RiImage_SetThreshold(RiImage_t *image, int threshold);

    int RiImage_SetBrightness(RiImage_t *image, int brightness);

    int RiImage_GetCorrelation(RiImage_t *imageRoi, RiImage_t *imagePattern, RiImage_t *imageCorrelation);

    int RiImage_Load(RiImage_t *image, ri_byte *buffer, int bufferLength, int colorMode, int width, int height);

    int RiImage_Save(RiImage_t *image, ri_byte *buffer, int bufferLength, int colorMode, int width, int height);

#ifdef __cplusplus
}
#endif

#endif /* __RI_IMAGE_H__ */
