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

#ifndef __RI_BITMAP_H__
#define __RI_BITMAP_H__

#include "openri.h"

#define RI_BITMAP_HEADER         "BM"
#define RI_BITMAP_HEADER_LENGTH  2   
  
#ifdef RI_VC
  #pragma pack(push)
  #pragma pack(1)
#else
  #pragma pack(1)
#endif

typedef struct tagRiBitmapHeader { 
	ri_uint16 bfType;
	ri_uint32 bfSize;
	ri_uint16 bfReserved1;
	ri_uint16 bfReserved2;
	ri_uint32 bfOffBits;
} RiBitmapHeader_t;  

#ifdef RI_VC
  #pragma pack(pop)
#else
  #pragma pack()
#endif
   
typedef struct tagRiBitmapInfoHeader { 
	ri_uint32 biSize;
	ri_int32  biWidth;
	ri_int32  biHeight;
	ri_uint16 biPlanes;
	ri_uint16 biBitCount;
	ri_uint32 biCompression;
	ri_uint32 biSizeImage;
	ri_int32  biXPelsPerMeter;
	ri_int32  biYPelsPerMeter;
	ri_uint32 biClrUsed;
	ri_uint32 biClrImportant;
} RiBitmapInfoHeader_t;
    
typedef struct tagRiRgbQuad {
	ri_byte rgbBlue;
	ri_byte rgbGreen;
	ri_byte rgbRed;
	ri_byte rgbReserved;
} RiRgbQuad_t;  
   
typedef struct tagRiBitmapInfo {
	RiBitmapInfoHeader_t bmiHeader;
	RiRgbQuad_t bmiColors[1];
} RiBitmapInfo_t;


#ifdef __cplusplus
extern "C"
{
#endif


int RiBitmap_Load(RiImage_t *image, ri_byte *bitmapBuffer, int bitmapBufferLength);

int RiBitmap_LoadFile(RiImage_t *image, ri_utf8 *path);

int RiBitmap_Save(RiImage_t *image, ri_byte **bitmapBuffer);

int RiBitmap_SaveFile(RiImage_t *image, ri_utf8 *path);

#ifdef __cplusplus
}
#endif

#endif /* __RI_BITMAP_H__ */
