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


    RiImage_t *RiImage_New() {
        RiImage_t *image;

        image = (RiImage_t *)ri_calloc(1, sizeof(RiImage_t));
        if (image == NULL) return NULL;

        return image;
    }

    int RiImage_Free(RiImage_t *image) {
        if (image == NULL) return RI_ERROR_NULL_POINTER;
        


        ri_free(image->data);

        ri_free(image);

        return RI_OK;
    }

    int RiImage_Init(RiImage_t *image, int width, int height, int colorMode) {
        int dataSize;

        if (image == NULL) return RI_ERROR_PARAMETER_0;
        
        if (width <= 0) return RI_ERROR_PARAMETER_1;
        if (height <= 0) return RI_ERROR_PARAMETER_2;
        if (colorMode <= 0) return RI_ERROR_PARAMETER_3;
        if (colorMode >= RI_COLOR_MODE_COUNT) return RI_ERROR_PARAMETER_3;

        ri_free(image->data);
        image->data = NULL;
        image->dataSize = 0;
        image->colorMode = RI_COLOR_MODE_UNKNOWN;
        image->width = 0;
        image->height = 0;

        dataSize = 0;

        if (colorMode == RI_COLOR_MODE_GRAY8) {
            dataSize = width * height;
            image->data = (unsigned char*)ri_calloc(1, dataSize);
        } else if (colorMode == RI_COLOR_MODE_RGB888) {
            dataSize = width * height * 3;
            image->data = (unsigned char*)ri_calloc(1, dataSize);
        } else {
            return RI_ERROR_COLOR_MODE;
        }

        if (image->data == NULL) {
            return RI_ERROR_NO_MEMORY;
        }

        image->dataSize = dataSize;
        image->colorMode = (RI_COLOR_MODE_t)colorMode;
        image->width = width;
        image->height = height;

        return RI_OK;
    }

    int RiImage_GetColorMode(RiImage_t *image) {
        if (image == NULL) return RI_ERROR_NULL_POINTER;

        return image->colorMode;
    }

    int RiImage_SetColorMode(RiImage_t *image, int colorMode) {
        int gray;
        int shiftRgb888;
        int shiftGray8;
        ri_byte gray8;
        int x;
        int y;

        if (image == NULL) return RI_ERROR_PARAMETER_0;
        
        if (colorMode <= 0) return RI_ERROR_PARAMETER_1;
        if (colorMode >= RI_COLOR_MODE_COUNT) return RI_ERROR_PARAMETER_1;

        if (image->colorMode == colorMode) {
            return RI_OK_DONE_ALREADY;
        }

        if (image->colorMode == RI_COLOR_MODE_RGB888 && colorMode == RI_COLOR_MODE_GRAY8) {
            int dataSize = image->width * image->height;
            ri_byte *data = (ri_byte *)ri_calloc(1, dataSize);
            if (data == NULL) {
                return RI_ERROR_NO_MEMORY;
            }

            for (y = 0; y < image->height; y ++) {
                for (x = 0; x < image->width; x ++) {
                    shiftRgb888 = (x + y * image->width) * 3;
                    shiftGray8 = x + y * image->width;

                    gray  = (int)image->data[shiftRgb888];
                    gray += (int)image->data[shiftRgb888 + 1];
                    gray += (int)image->data[shiftRgb888 + 2];
                    gray = gray / 3;

                    data[shiftGray8] = (ri_byte)gray;
                }
            }

            ri_free(image->data);
            image->data = data;
            image->dataSize = dataSize;
            image->colorMode = (RI_COLOR_MODE_t)colorMode;
        } else if (image->colorMode == RI_COLOR_MODE_GRAY8 && colorMode == RI_COLOR_MODE_RGB888) {
            int dataSize = image->width * image->height * 3;
            ri_byte *data = (ri_byte *)ri_calloc(1, dataSize);
            if (data == NULL) {
                return RI_ERROR_NO_MEMORY;
            }

            for (y = 0; y < image->height; y ++) {
                for (x = 0; x < image->width; x ++) {
                    shiftRgb888 = (x + y * image->width) * 3;
                    shiftGray8 = x + y * image->width;

                    gray8 = image->data[shiftGray8];

                    data[shiftRgb888] = gray8;
                    data[shiftRgb888 + 1] = gray8;
                    data[shiftRgb888 + 2] = gray8;
                }
            }

            ri_free(image->data);
            image->data = data;
            image->dataSize = dataSize;
            image->colorMode = (RI_COLOR_MODE_t)colorMode;
        } else {
            return RI_ERROR_COLOR_MODE;
        }

        return RI_OK;
    }

    int RiImage_Fill(RiImage_t *image, RiColor_t *color) {
        if (image == NULL) return RI_ERROR_PARAMETER_0;
        
        if (color == NULL) return RI_ERROR_PARAMETER_1;

        if (image->colorMode != color->mode) {
            return RI_ERROR_COLOR_MODE;
        }

        if (image->colorMode == RI_COLOR_MODE_RGB888) {
            int shiftRgb888;
            int x;
            int y;
            for (y = 0; y < image->height; y ++) {
                for (x = 0; x < image->width; x ++) {
                    shiftRgb888 = (x + y * image->width) * 3;

                    image->data[shiftRgb888] = color->red8;
                    image->data[shiftRgb888 + 1] = color->green8;
                    image->data[shiftRgb888 + 2] = color->blue8;
                }
            }

            //RI_LOGI("RiImage_Fill w = %d, h = %d", image->width, image->height);
        } else if (image->colorMode == RI_COLOR_MODE_GRAY8) {
            ri_memset(image->data, color->gray8, image->dataSize);
        } else {
            return RI_ERROR_COLOR_MODE;
        }

        return RI_OK;
    }

    int RiImage_GetPixelColor(RiImage_t *image, int x, int y, RiColor_t *color) {
        if (image == NULL) return RI_ERROR_PARAMETER_0;
        
        if (x < 0) return RI_ERROR_PARAMETER_1;
        if (x >= image->width) return RI_ERROR_PARAMETER_1;
        if (y < 0) return RI_ERROR_PARAMETER_2;
        if (y >= image->height) return RI_ERROR_PARAMETER_2;

        color->mode = RI_COLOR_MODE_UNKNOWN;

        if (image->colorMode == RI_COLOR_MODE_RGB888) {
            int shiftRgb888 = (x + y * image->width) * 3;
            color->red8    = image->data[shiftRgb888];
            color->green8  = image->data[shiftRgb888 + 1];
            color->blue8   = image->data[shiftRgb888 + 2];
        } else if (image->colorMode == RI_COLOR_MODE_GRAY8) {
            int shiftGray8 = x + y * image->width;
            color->gray8    = image->data[shiftGray8];
        } else {
            return RI_ERROR_COLOR_MODE;
        }

        color->mode = image->colorMode;

        return RI_OK;
    }

    int RiImage_DrawPixel(RiImage_t *image, int x, int y, RiColor_t *color) {
        if (image == NULL) return RI_ERROR_PARAMETER_0;
        
        if (x < 0) return RI_ERROR_PARAMETER_1;
        if (x >= image->width) return RI_ERROR_PARAMETER_1;
        if (y < 0) return RI_ERROR_PARAMETER_2;
        if (y >= image->height) return RI_ERROR_PARAMETER_2;

        if (image->colorMode != color->mode) {
            return RI_ERROR_COLOR_MODE;
        }

        if (image->colorMode == RI_COLOR_MODE_RGB888) {
            int shiftRgb888 = (x + y * image->width) * 3;
            image->data[shiftRgb888] = color->red8;
            image->data[shiftRgb888 + 1] = color->green8;
            image->data[shiftRgb888 + 2] = color->blue8;
        } else if (image->colorMode == RI_COLOR_MODE_GRAY8) {
            int shiftGray8 = x + y * image->width;
            image->data[shiftGray8] = color->gray8;
        } else {
            return RI_ERROR_COLOR_MODE;
        }

        return RI_OK;
    }

    int RiImage_SetThreshold(RiImage_t *image, int threshold) {
        int i;
        int dataSize;

        if (image == NULL) return RI_ERROR_PARAMETER_0;
        
        if (threshold < 0) return RI_ERROR_PARAMETER_1;
        if (threshold > 255) return RI_ERROR_PARAMETER_1;

        if (image->colorMode != RI_COLOR_MODE_GRAY8) {
            return RI_ERROR_COLOR_MODE;
        }

        dataSize = image->dataSize;
        for (i = 0; i < dataSize; i ++) {
            if (image->data[i] >= threshold) {
                image->data[i] = 255;
            } else {
                image->data[i] = 0;
            }
        }

        return RI_OK;
    }

    int RiImage_SetBrightness(RiImage_t *image, int brightness) {
        int i;
        int dataSize;
        int temp;

        if (image == NULL) return RI_ERROR_PARAMETER_0;
        

        if (image->colorMode != RI_COLOR_MODE_GRAY8) {
            return RI_ERROR_COLOR_MODE;
        }

        dataSize = image->dataSize;
        for (i = 0; i < dataSize; i ++) {
            temp = image->data[i] + brightness;

            if (temp > 255) {
                image->data[i] = 255;
            } else if (temp < 0) {
                image->data[i] = 0;
            } else {
                image->data[i] = temp;
            }
        }

        return RI_OK;
    }

    int RiImage_GetCorrelation(RiImage_t *imageRoi, RiImage_t *imagePattern, RiImage_t *imageCorrelation) {
        if (imageRoi == NULL) return RI_ERROR_PARAMETER_0;
        
        if (imagePattern == NULL) return RI_ERROR_PARAMETER_1;
        
        if (imageCorrelation == NULL) return RI_ERROR_PARAMETER_2;
        

        if (imageRoi->colorMode != RI_COLOR_MODE_GRAY8) {
            return RI_ERROR_COLOR_MODE;
        }

        if (imagePattern->colorMode != RI_COLOR_MODE_GRAY8) {
            return RI_ERROR_COLOR_MODE;
        }

        if (imageRoi->width < imagePattern->width) {
            return RI_ERROR_PARAMETER_1;
        }

        if (imageRoi->height < imagePattern->height) {
            return RI_ERROR_PARAMETER_1;
        }

        // TODO

        return RI_OK;
    }

    int RiImage_Load(RiImage_t *image, ri_byte *buffer, int bufferLength, int colorMode, int width, int height) {
        int length;

        if (image == NULL) return RI_ERROR_PARAMETER_0;
        
        if (buffer == NULL) return RI_ERROR_PARAMETER_1;
        if (bufferLength <= 0) return RI_ERROR_PARAMETER_2;
        if (colorMode <= 0) return RI_ERROR_PARAMETER_3;
        if (width <= 0) return RI_ERROR_PARAMETER_4;
        if (height <= 0) return RI_ERROR_PARAMETER_5;

        length = 0;

        if (image->colorMode == RI_COLOR_MODE_RGB888 && colorMode == RI_COLOR_MODE_RGB565) {
            int x;
            int y;
            int imageDataShift;
            int bufferShift;
            unsigned char byte0;
            unsigned char byte1;
            unsigned char r;
            unsigned char g;
            unsigned char b;

            length = width * height * 2;
            if (bufferLength < length) {
                return RI_ERROR_PARAMETER_2;
            }

            for (y = 0; y < height; y ++) {
                for (x = 0; x < width; x ++) {
                    imageDataShift = (x + y * width) * 3;
                    bufferShift = (x + y * width) * 2;

                    byte0 = buffer[bufferShift];
                    byte1 = buffer[bufferShift + 1];

                    r = (byte1 & 0xF8);
                    g = (byte0 & 0xD0) >> 3;
                    g += (byte1 & 0x7) << 5;
                    b = (byte0 & 0x1F) << 3;

                    image->data[imageDataShift] = r;
                    image->data[imageDataShift + 1] = g;
                    image->data[imageDataShift + 2] = b;
                }
            }
            return length;
        }

        if (image->colorMode == RI_COLOR_MODE_RGB888 && colorMode == RI_COLOR_MODE_ARGB8888) {
            int x;
            int y;
            int imageDataShift;
            int bufferShift;

            length = width * height * 4;
            if (bufferLength < length) {
                return RI_ERROR_PARAMETER_2;
            }

            for (y = 0; y < height; y ++) {
                for (x = 0; x < width; x ++) {
                    imageDataShift = (x + y * width) * 3;
                    bufferShift = (x + y * width) * 4;

                    image->data[imageDataShift]     = buffer[bufferShift];
                    image->data[imageDataShift + 1] = buffer[bufferShift + 1];
                    image->data[imageDataShift + 2] = buffer[bufferShift + 2];
                }
            }
            return length;
        }

        return RI_ERROR_NO_MATCH;
    }

    int RiImage_Save(RiImage_t *image, ri_byte *buffer, int bufferLength, int colorMode, int width, int height) {
        int length;

        if (image == NULL) return RI_ERROR_PARAMETER_0;
        
        if (buffer == NULL) return RI_ERROR_PARAMETER_1;
        if (bufferLength <= 0) return RI_ERROR_PARAMETER_2;
        if (colorMode <= 0) return RI_ERROR_PARAMETER_3;
        if (width <= 0) return RI_ERROR_PARAMETER_4;
        if (height <= 0) return RI_ERROR_PARAMETER_5;

        length = 0;

        if (image->colorMode == RI_COLOR_MODE_RGB888 && colorMode == RI_COLOR_MODE_RGB565) {
            int x;
            int y;
            int imageDataShift;
            int bufferShift;
            unsigned char byte0;
            unsigned char byte1;
            unsigned char r;
            unsigned char g;
            unsigned char b;

            length = width * height * 2;

            if (bufferLength < length) {
                return RI_ERROR_PARAMETER_2;
            }

            for (y = 0; y < height; y ++) {
                for (x = 0; x < width; x ++) {
                    imageDataShift = (x + y * width) * 3;
                    bufferShift = (x + y * width) * 2;

                    r = image->data[imageDataShift];
                    g = image->data[imageDataShift + 1];
                    b = image->data[imageDataShift + 2];

                    byte0 = (b & 0xF8) >> 3;
                    byte0 += (g & 0x1C) << 3;

                    byte1 = (g & 0xD0) >> 5;
                    byte1 += r & 0xF8;

                    buffer[bufferShift] = byte0;
                    buffer[bufferShift + 1] = byte1;
                }
            }
            return length;
        }

        if (image->colorMode == RI_COLOR_MODE_RGB888 && colorMode == RI_COLOR_MODE_ARGB8888) {
            int x;
            int y;
            int imageDataShift;
            int bufferShift;

            length = width * height * 4;

            if (bufferLength < length) {
                return RI_ERROR_PARAMETER_2;
            }

            for (y = 0; y < height; y ++) {
                for (x = 0; x < width; x ++) {
                    imageDataShift = (x + y * width) * 3;
                    bufferShift = (x + y * width) * 4;

                    buffer[bufferShift] = image->data[imageDataShift];
                    buffer[bufferShift + 1] = image->data[imageDataShift + 1];
                    buffer[bufferShift + 2] = image->data[imageDataShift + 2];
                    buffer[bufferShift + 3] = 255;
                }
            }
            return length;
        }

        if (image->colorMode == RI_COLOR_MODE_GRAY8 && colorMode == RI_COLOR_MODE_ARGB8888) {
            int x;
            int y;
            int imageDataShift;
            int bufferShift;
            unsigned char temp;

            length = width * height * 4;

            if (bufferLength < length) {
                return RI_ERROR_PARAMETER_2;
            }

            for (y = 0; y < height; y ++) {
                for (x = 0; x < width; x ++) {
                    imageDataShift = x + y * width;
                    bufferShift = (x + y * width) * 4;

                    temp = image->data[imageDataShift];
                    buffer[bufferShift] = temp;
                    buffer[bufferShift + 1] = temp;
                    buffer[bufferShift + 2] = temp;
                    buffer[bufferShift + 3] = 255;
                }
            }
            return length;
        }

        return RI_ERROR_PARAMETER_3;
    }

#ifdef __cplusplus
}
#endif
