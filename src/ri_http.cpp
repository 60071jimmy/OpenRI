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

static int riHttpIsInit = 0;

int RiHttp_InitLib() {
	if (riHttpIsInit == 1) {
		return RI_OK_INIT_ALREADY;
	}
	riHttpIsInit = 1;

	return RI_OK;
}

RiHttp_t *RiHttp_New() {
	RiHttp_t *http;

	if (riHttpIsInit == 0) return NULL;
	
	http = (RiHttp_t *)ri_calloc(1, sizeof(RiHttp_t));
	if (http == NULL) {
		return NULL;
	}
	
	

	return http;
}

int RiHttp_Free(RiHttp_t *http) {
	if (http == NULL) return RI_ERROR_NULL_POINTER;
    
    ri_free(http);
    
    return RI_OK;
}

int RiHttp_Get(RiHttp_t *http, ri_utf8 *url) {
	if (http == NULL) return RI_ERROR_PARAMETER_0;
	
	if (url == NULL) return RI_ERROR_PARAMETER_1;

	return RI_OK;
}

#ifdef __cplusplus
}
#endif
