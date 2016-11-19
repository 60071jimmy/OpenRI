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

#ifndef __RI_COM_H__
#define __RI_COM_H__


#include "openri.h"


#ifdef __cplusplus
extern "C" 
{
#endif

	RI_API int RiCom_Open(char *name, int baudRate, char parity, int databits, int stopBits);
	RI_API int RiCom_Write(char *buf, int bufLen);
	RI_API int RiCom_Read(char *buf, int bufSize);
	RI_API int RiCom_Close();

#ifdef __cplusplus
}
#endif

#endif /* __RI_COM_H__ */
