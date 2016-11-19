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

#ifndef __RI_CONFIG_H__
#define __RI_CONFIG_H__

#ifdef __cplusplus
extern "C" 
{
#endif

//#define RI_DEBUG 1

//#define RI_LINUX 1
//#define RI_ANDROID 1
//#define RI_IOS 1
#define RI_WINDOWS 1

//#define RI_32BIT 1
#define RI_64BIT 1

#define RI_X86 1
//#define RI_ARM 1
//#define RI_SH4 1

//#define RI_GCC 1
#define RI_VC 1

#define RI_PAGE_SIZE 4096

//#define RI_MEDIA_PLAYER 1
//#define RI_MEDIA_PLAYER_FFMPEG_PACKET_LOST_COUNTER 1
//#define RI_MEDIA_PLAYER_DEFAULT_TCP 1

//#define RI_CUDA 1

//#define RI_OCL 1

#define RI_EXPORT_API 1

#ifdef __cplusplus
}
#endif

#endif /* __RI_CONFIG_H__ */
