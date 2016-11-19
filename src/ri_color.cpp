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

    static int riColorIsInit = 0;

    int RiColor_InitLib() {
        if (riColorIsInit == 1) {
            return RI_OK_INIT_ALREADY;
        }
        riColorIsInit = 1;

        return RI_OK;
    }

    RiColor_t *RiColor_New() {
        RiColor_t *color;

        if (riColorIsInit == 0) return NULL;

        color = (RiColor_t *)ri_calloc(1, sizeof(RiColor_t));
        if (color == NULL) {
            return NULL;
        }

        

        return color;
    }

    int RiColor_Free(RiColor_t *color) {
        if (color == NULL) return RI_ERROR_NULL_POINTER;


        ri_free(color);

        return RI_OK;
    }

    int RiColor_SetRGB888(RiColor_t *color, int red8, int green8, int blue8) {
        if (color == NULL) return RI_ERROR_PARAMETER_0;
        
        if (red8 < 0) return RI_ERROR_PARAMETER_1;
        if (red8 > 255) return RI_ERROR_PARAMETER_1;
        if (green8 < 0) return RI_ERROR_PARAMETER_2;
        if (green8 > 255) return RI_ERROR_PARAMETER_2;
        if (blue8 < 0) return RI_ERROR_PARAMETER_3;
        if (blue8 > 255) return RI_ERROR_PARAMETER_3;

        color->mode = RI_COLOR_MODE_RGB888;
        color->red8 = red8;
        color->green8 = green8;
        color->blue8 = blue8;

        return RI_OK;
    }

    int RiColor_SetGRAY8(RiColor_t *color, int gray8) {
        if (color == NULL) return RI_ERROR_PARAMETER_0;
        
        if (gray8 < 0) return RI_ERROR_PARAMETER_1;
        if (gray8 > 255) return RI_ERROR_PARAMETER_1;

        color->mode = RI_COLOR_MODE_GRAY8;
        color->gray8 = gray8;

        return RI_OK;
    }

    RI_COLOR_MODE_t RiColor_GetMode(RiColor_t *color) {
        if (color == NULL) return RI_COLOR_MODE_UNKNOWN;

        return color->mode;
    }

    int RiColor_GetRed8(RiColor_t *color) {
        if (color == NULL) return RI_ERROR_NULL_POINTER;
        
        if (color->mode != RI_COLOR_MODE_RGB888) return RI_ERROR_COLOR_MODE;

        return color->red8;
    }

    int RiColor_GetGreen8(RiColor_t *color) {
        if (color == NULL) return RI_ERROR_NULL_POINTER;
        
        if (color->mode != RI_COLOR_MODE_RGB888) return RI_ERROR_COLOR_MODE;

        return color->green8;
    }

    int RiColor_GetBlue8(RiColor_t *color) {
        if (color == NULL) return RI_ERROR_NULL_POINTER;
        
        if (color->mode != RI_COLOR_MODE_RGB888) return RI_ERROR_COLOR_MODE;

        return color->blue8;
    }

    int RiColor_GetGray8(RiColor_t *color) {
        if (color == NULL) return RI_ERROR_NULL_POINTER;
        
        if (color->mode != RI_COLOR_MODE_GRAY8) return RI_ERROR_COLOR_MODE;

        return color->gray8;
    }

#ifdef __cplusplus
}
#endif
