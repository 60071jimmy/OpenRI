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

#include "ri_hash.h"

#if defined(RI_LINUX)
#include "sha1.h"
#include "sha256.h"
#include "md5.h"
#endif

#ifdef __cplusplus
extern "C" 
{
#endif

int RiMd5_GetString(char *str, int strSize, void *data, int dataLength) {
	#if defined(RI_LINUX)
    unsigned char res[20];
	MD5_CTX md5;
	int i;

	if (str == NULL) return RI_ERROR_PARAMETER_0;
	if (strSize < 33) return RI_ERROR_PARAMETER_1;
	if (data == NULL) return RI_ERROR_PARAMETER_2;
	if (dataLength <= 0) return RI_ERROR_PARAMETER_3;

	
	MD5Init(&md5);
	MD5Update(&md5, (unsigned char *)data, dataLength);
	MD5Final(res,&md5);

	for (i = 0; i < 16; i++) {
		sprintf(str + (i * 2), "%02x", res[i]);
	}
	
	return 33;
#endif
}

int RiSha1_GetString(char *str, int strSize, void *data, int dataLength) {
    #if defined(RI_LINUX)
	SHA1Context sha;
	int i;

	if (str == NULL) return RI_ERROR_PARAMETER_0;
	if (strSize < 41) return RI_ERROR_PARAMETER_1;
	if (data == NULL) return RI_ERROR_PARAMETER_2;
	if (dataLength <= 0) return RI_ERROR_PARAMETER_3;

	SHA1Reset(&sha);
	SHA1Input(&sha, (const unsigned char *)data, dataLength);
	SHA1Result(&sha);

	for (i = 0; i < 5; i++) {
		sprintf(str + (i * 8), "%08x", sha.Message_Digest[i]);
	}
	
	return 41;
#endif
}

int RiSha256_GetString(char *str, int strSize, void *data, int dataLength) {
    #if defined(RI_LINUX)
	unsigned char res[40];
	SHA256_CTX ctx;
	int i;

	if (str == NULL) return RI_ERROR_PARAMETER_0;
	if (strSize < 65) return RI_ERROR_PARAMETER_1;
	if (data == NULL) return RI_ERROR_PARAMETER_2;
	if (dataLength <= 0) return RI_ERROR_PARAMETER_3;
	
	sha256_init(&ctx);
	sha256_update(&ctx, (unsigned char *)data, dataLength);
	sha256_final(&ctx,res);

	for (i = 0; i < 32; i++) {
		sprintf(str + (i * 2), "%02x", res[i]);
	}

	return 65;
#endif
}

#ifdef __cplusplus
}
#endif
