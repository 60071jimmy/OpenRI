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

#ifndef __RI_DBG_H__
#define __RI_DBG_H__


#include "openri.h"


#if defined(RI_DEBUG)
#define dbg(...) RiDbg_Dbg(__VA_ARGS__);
#else
#define dbg(...) RiDbg_Dbg(__VA_ARGS__);
#endif


#ifdef __cplusplus
extern "C" 
{
#endif

	RI_API int RiDbg_Enable();

	RI_API int RiDbg_Disable();

	RI_API int RiDbg_Dbg(char *format, ...);

#ifdef __cplusplus

}
#endif


#endif /* __RI_DBG_H__ */

