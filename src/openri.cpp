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


static int openriIsInited = 0;


#ifdef __cplusplus
extern "C" 
{
#endif

RI_API int OpenRI_InitLib() {
	if (openriIsInited != 0) {
		return 3;
	}
	openriIsInited = 2;

	// Check whether CPU supporting AVX instruction set or not.
	bool isAVX = false;
	int cpuInfo[4] = { 0,0,0,0 };
	__cpuid(cpuInfo, 0);
	if (cpuInfo[0] != 0) {
		__cpuid(cpuInfo, 1);
		if (cpuInfo[2] & (1 << 28)) {
			isAVX = true;
		}
	}
	if (isAVX == false) {
		return -2; // Do not support AVX instruction set.
	}

	// Put init code here.
	int ret;
	ret = riThread_InitLib();
	if (ret <= 0) {
		return ret;
	}
#if defined(RI_UR)
	ret = riSocket_InitLib();
	if (ret <= 0) {
		return ret;
	}

	ret = riHttpd_InitLib();
	if (ret <= 0) {
		return ret;
	}

#endif
	openriIsInited = 1;
	return 1;
}


#ifdef __cplusplus

}
#endif


