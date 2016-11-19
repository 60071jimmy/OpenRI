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

#ifndef __OPENRI_H__
#define __OPENRI_H__


#define OPENRI_VERSION "0.1.0"
#define OPENRI_DATETIME (201608151416ul)


//#include "ri_config.h"
// 2016/11/07 You-Ching
// This version does not have "ri_config.h";
// thus, "RI_WINDOWS" & "RI_VC" & "RI_PAGE_SIZE" are not defined.
// So, I define them here to let this code able to be compiled.
// I also marked the above "#include" code.
#define RI_WINDOWS
#define RI_VC
#define RI_PAGE_SIZE 4096

// 2016/11/08 You-Ching
// "ri_" libraries here are used for dll.
#define RI_EXPORT_API



#ifdef RI_EXPORT_API
#define RI_API __declspec(dllexport)
#else
#define RI_API
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <immintrin.h> // AVX Instruction Set

#ifdef RI_WINDOWS
#include <Windows.h>
#include <tchar.h>
#endif


// Core modules.
#include "ri_ret.h"
#include "ri_type.h"
#include "ri_mem.h" 
#include "ri_utf8.h"
#include "ri_string.h"
#include "ri_dbg.h"
#include "ri_log.h"
#include "ri_runtime.h"
#include "ri_semaphore.h"   
#include "ri_lock.h"
#include "ri_array.h"
#include "ri_fifo.h"
#include "ri_buffer.h"
#include "ri_bit_buffer.h"
#include "ri_data.h"
#include "ri_value.h"
#include "ri_thread.h"
#include "ri_timer_us.h"
#include "ri_file.h"
#include "ri_color.h"
#include "ri_image.h"
#include "ri_bitmap.h"
#include "ri_mat.h"
#include "ri_hash.h"
#ifdef RI_UR
#else
  #include "ri_socket.h"
  #include "ri_httpd.h"
#endif
#include "ri_http.h"
#include "ri_date_time.h"
#include "ri_blob.h"


#ifdef __cplusplus
extern "C" 
{
#endif

    RI_API int OpenRI_InitLib();

#ifdef __cplusplus

}
#endif


#endif /* __OPENRI_H__ */ 

