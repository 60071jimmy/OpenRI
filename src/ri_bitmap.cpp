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

    static int riBitmapIsInit = 0;

    int RiBitmap_InitLib() {
        if (riBitmapIsInit == 1) return RI_OK_INIT_ALREADY;

        riBitmapIsInit = 1;

        return RI_OK;
    }

    int RiBitmap_Load(RiImage_t *image, ri_byte *bitmapBuffer, int bitmapBufferLength) {
        RiBitmapHeader_t *bmfh;
        RiBitmapInfoHeader_t *bmih;
        RI_COLOR_MODE_t colorMode;
        int row_align;
        int i;
        int j;
        int image_shift;
        int buf_shift;
        int dataSize;
        ri_byte *data;

        if (riBitmapIsInit == 0) return RI_ERROR_NOT_INIT;
        if (image == NULL) return RI_ERROR_PARAMETER_0;
        
        if (bitmapBuffer == NULL) return RI_ERROR_PARAMETER_1;
        if (bitmapBufferLength <= 0) return RI_ERROR_PARAMETER_2;

        bmfh = (RiBitmapHeader_t *)bitmapBuffer;
        bmih = (RiBitmapInfoHeader_t *)(bitmapBuffer + sizeof(RiBitmapHeader_t));

        colorMode = RI_COLOR_MODE_UNKNOWN; 

        if (bmih->biBitCount == 24) {
            colorMode = RI_COLOR_MODE_RGB888;
        } else if (bmih->biBitCount == 8) {
            colorMode = RI_COLOR_MODE_GRAY8;
        } else {
            return RI_ERROR_COLOR_MODE;
        }

        RiImage_Init(image, bmih->biWidth, bmih->biHeight, colorMode);

        data = bitmapBuffer + bmfh->bfOffBits;

        if (colorMode == RI_COLOR_MODE_RGB888) {
            row_align = (bmih->biWidth * 3) % 4;
            row_align = 4 - row_align;
            if (row_align == 4) row_align = 0;

            dataSize = image->dataSize;
            for (j = 0; j < image->height; j++) {
                for (i = 0; i < image->width; i++) {
                    image_shift = (i + j * image->width) * 3;
                    buf_shift = 3 * i + (bmih->biHeight - 1 - j) * (bmih->biWidth * 3 + row_align);
                    if ((buf_shift + 2) < dataSize) {
                        image->data[image_shift  ]   = data[buf_shift + 2];
                        image->data[image_shift+1]   = data[buf_shift + 1];
                        image->data[image_shift+2]   = data[buf_shift  ];
                    }
                }
            }
        } else if (colorMode == RI_COLOR_MODE_GRAY8) {
            row_align = bmih->biWidth % 4;
            row_align = 4 - row_align;
            if (row_align == 4) row_align = 0;

            dataSize = image->dataSize;
            for (j = 0; j < image->height; j++) {
                for (i = 0; i < image->width; i++) {
                    image_shift = i + j * image->width;
                    //buf_shift = image_shift;
                    buf_shift = i + (bmih->biHeight - 1 - j) * (bmih->biWidth + row_align);
                    if (buf_shift < dataSize) {
                        image->data[image_shift]   = data[buf_shift];
                    }
                }
            }
        } else {
            return RI_ERROR_COLOR_MODE;
        }

        return RI_OK;
    }

    int RiBitmap_LoadFile(RiImage_t *image, ri_utf8 *path) {
        //RiFile_t *gtFile;

        //if (riBitmapIsInit == 0) return RI_ERROR_NOT_INIT;
        //if (image == NULL) return RI_ERROR_PARAMETER_0;
        //if (image->magic != RI_MAGIC_IMAGE) return RI_ERROR_PARAMETER_0;
        //if (path == NULL) return RI_ERROR_PARAMETER_1;

        //gtFile = RiFile_New();
        //if (gtFile == NULL) {
        //	return RI_ERROR_NEW_OBJECT;
        //}

        //int ret = RiFile_Open(gtFile, path, RI_FILE_O_RDONLY);
        //if (ret <= 0) {
        //	return ret;
        //}

        //ri_int64 fileSize = RiFile_GetSize(gtFile);
        //if (fileSize < 0) {
        //	return fileSize;
        //}

        //ri_byte *fileData = ri_calloc(1, fileSize);
        //if (fileData == NULL) {
        //	return RI_ERROR_NO_MEMORY;
        //}

        //ret = RiFile_Read(gtFile, fileData, fileSize);
        //if (ret <= 0) {
        //	return ret;
        //}

        //ret = RiBitmap_Load(image, fileData, fileSize);
        //if (ret <= 0) {
        //	return ret;
        //}

        //RiFile_Close(gtFile);

        return RI_OK;
    }

    int RiBitmap_Save(RiImage_t *image, ri_byte **bitmapBuffer) {
        ri_byte *buf;
        ri_byte *data;
        int i;
        int j;
        int image_shift;
        int buf_shift;
        int row_align;
        RiBitmapHeader_t *bmfh;
        RiBitmapInfoHeader_t *bmih;
        int buf_len = 0;

        if (riBitmapIsInit == 0) return RI_ERROR_NOT_INIT;
        if (image == NULL) return RI_ERROR_PARAMETER_0;
        
        if (bitmapBuffer == NULL) return RI_ERROR_PARAMETER_1;

        if (image->colorMode == RI_COLOR_MODE_RGB888) {
            row_align = (image->width * 3) % 4;
            row_align = 4 - row_align;
            if (row_align == 4) row_align = 0;

            buf_len = sizeof(RiBitmapHeader_t) + sizeof(RiBitmapInfoHeader_t) + (image->width * 3 + row_align) * image->height;

            buf = (ri_byte *)ri_calloc(1, buf_len);

            bmfh = (RiBitmapHeader_t *)buf;
            bmih = (RiBitmapInfoHeader_t *)(buf + sizeof(RiBitmapHeader_t));

            // File.
            bmfh->bfType = 0x4D42;
            bmfh->bfSize = buf_len;
            bmfh->bfReserved1 = 0;
            bmfh->bfReserved2 = 0;
            bmfh->bfOffBits = sizeof(RiBitmapHeader_t) + sizeof(RiBitmapInfoHeader_t);

            // Info.
            bmih->biSize = sizeof(RiBitmapInfoHeader_t);
            bmih->biWidth = image->width;
            bmih->biHeight = image->height;
            bmih->biPlanes = 1;
            bmih->biBitCount = 24;
            bmih->biCompression = 0;
            bmih->biSizeImage = buf_len - bmfh->bfOffBits;
            bmih->biXPelsPerMeter = 2835;
            bmih->biYPelsPerMeter = 2835;
            bmih->biClrUsed = 0;
            bmih->biClrImportant = 0;

            // Data.
            data = buf+bmfh->bfOffBits;
            for (j = 0; j < image->height; j++) {
                for (i = 0; i < image->width; i++) {
                    image_shift = (i + j * image->width) * 3;
                    buf_shift = 3 * i + (bmih->biHeight - 1 - j) * (bmih->biWidth * 3 + row_align);
                    data[buf_shift+2] = image->data[image_shift  ];
                    data[buf_shift+1] = image->data[image_shift+1];
                    data[buf_shift  ] = image->data[image_shift+2];
                }
            }

            *bitmapBuffer = buf;
        } else if (image->colorMode == RI_COLOR_MODE_GRAY8) {
            ri_byte *palette;
            int palette_shift;

            row_align = (image->width) % 4;
            row_align = 4 - row_align;
            if (row_align == 4) row_align = 0;

            buf_len = sizeof(RiBitmapHeader_t) + sizeof(RiBitmapInfoHeader_t) + 1024 + (image->width + row_align) * image->height;

            buf = (ri_byte *)ri_calloc(1, buf_len);

            bmfh = (RiBitmapHeader_t *)buf;
            bmih = (RiBitmapInfoHeader_t *)(buf + sizeof(RiBitmapHeader_t));

            // File.
            bmfh->bfType = 0x4D42;
            bmfh->bfSize = buf_len;
            bmfh->bfReserved1 = 0;
            bmfh->bfReserved2 = 0;
            bmfh->bfOffBits = sizeof(RiBitmapHeader_t) + sizeof(RiBitmapInfoHeader_t);

            // Info.
            bmih->biSize = sizeof(RiBitmapInfoHeader_t);
            bmih->biWidth = image->width;
            bmih->biHeight = image->height;
            bmih->biPlanes = 1;
            bmih->biBitCount = 8;
            bmih->biCompression = 0;
            bmih->biSizeImage = buf_len - bmfh->bfOffBits;
            bmih->biXPelsPerMeter = 2835;
            bmih->biYPelsPerMeter = 2835;
            bmih->biClrUsed = 0;
            bmih->biClrImportant = 0;

            // Palette 256 x 4
            palette = buf + bmfh->bfOffBits;
            for (i = 0; i < 256; i ++) {
                palette_shift = i * 4;
                palette[palette_shift] = i;
                palette[palette_shift + 1] = i;
                palette[palette_shift + 2] = i;
                palette[palette_shift + 3] = 0;
            }

            // Data.
            data = buf + bmfh->bfOffBits + 1024;
            for (j = 0; j < image->height; j++) {
                for (i = 0; i < image->width; i++) {
                    image_shift = i + j * image->width;
                    //buf_shift = image_shift;
                    buf_shift = i + (bmih->biHeight - 1 - j) * (bmih->biWidth + row_align);
                    data[buf_shift] = image->data[image_shift];
                }
            }

            *bitmapBuffer = buf;
            //RI_LOGI("here, buf_len = %d", buf_len);
        } else {
            return RI_ERROR_COLOR_MODE;
        }

        return buf_len;
    }

    int RiBitmap_SaveFile(RiImage_t *image, ri_utf8 *path) {
        //if (riBitmapIsInit == 0) return RI_ERROR_NOT_INIT;
        //if (image == NULL) return RI_ERROR_PARAMETER_0;
        //if (image->magic != RI_MAGIC_IMAGE) return RI_ERROR_PARAMETER_0;
        //if (path == NULL) return RI_ERROR_PARAMETER_1;

        //RiFile_t *gtFile = RiFile_New();
        //if (gtFile == NULL) {
        //	return RI_ERROR_NEW_OBJECT;
        //}

        //int ret = RiFile_Open(gtFile, path, RI_FILE_O_WRONLY | RI_FILE_O_CREAT | RI_FILE_O_TRUNC);
        //if (ret <= 0) {
        //	return ret;
        //}

        //ri_byte *fileData;
        //int fileSize = RiBitmap_Save(image, &fileData);
        //if (fileSize <= 0) {
        //	return fileSize;
        //}

        //ret = RiFile_Write(gtFile, fileData, fileSize);
        //if (ret <= 0) {
        //	return ret;
        //}

        //ret = RiFile_Sync(gtFile);
        //if (ret <= 0) {
        //	return ret;
        //}

        //RiFile_Close(gtFile);

        return RI_OK;
    }

#ifdef __cplusplus
}
#endif
