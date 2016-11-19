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

static HANDLE ricomHandle = INVALID_HANDLE_VALUE;

#ifdef __cplusplus
extern "C" 
{
#endif

    RI_API int RiCom_Open(char *name, int baudRate, char parity, int databits, int stopBits) {
#if defined(RI_WINDOWS)
        WCHAR wideCharName[RI_PAGE_SIZE];

        int len = MultiByteToWideChar(CP_ACP, 0, name, -1, NULL, 0);

        if (len <= 0) {
            return -1;
        }

        if (len >= RI_PAGE_SIZE) {
            return -2;
        }

        len = MultiByteToWideChar(CP_ACP, 0, name, -1, (LPWSTR)wideCharName, len * sizeof(WCHAR));

        if (len <= 0) {
            return -3;
        }

        ricomHandle = CreateFile(wideCharName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

        if (ricomHandle == INVALID_HANDLE_VALUE) { 
            dbg ("CreateFile failed with error %d.\n", GetLastError());
            CloseHandle(ricomHandle);
            return -4;
        }

        DCB dcb ={0};
        FillMemory(&dcb, sizeof(dcb), 0);
        dcb.DCBlength = sizeof(dcb);

        if (!GetCommState(ricomHandle, &dcb)) {
            dbg ("GetCommState failed with error %d.\n", GetLastError());
            CloseHandle(ricomHandle);
            return -5;
        }

        char BuildDCB[256] = {0};
        sprintf_s(BuildDCB, 256, "baud=%d parity=%c data=%d stop=%d", baudRate, parity, databits, stopBits);
        dbg("%s",BuildDCB);

        WCHAR wideBuildDCB[RI_PAGE_SIZE];
        len = MultiByteToWideChar(CP_ACP, 0, BuildDCB, -1, NULL, 0);

        if (len <= 0) {
            return -6;
        }

        if (len >= RI_PAGE_SIZE) {
            return -6;  // TODO: Error code.
        }

        if (wideBuildDCB == NULL) {
            return -7;
        }

        len = MultiByteToWideChar(CP_ACP, 0, BuildDCB, -1, (LPWSTR)wideBuildDCB, len * sizeof(WCHAR));

        if (len <= 0) {
            return -8;
        }

        if (!BuildCommDCB(wideBuildDCB, &dcb)) {
            dbg ("BuildCommDCB failed with error %d.\n", GetLastError());
            CloseHandle(ricomHandle);
            return -9;
        }

        if (!SetCommState(ricomHandle, &dcb)) {
            dbg ("SetCommState failed with error %d.\n", GetLastError());
            CloseHandle(ricomHandle);
            return -10;
        }

        return 1;
#endif
    }

    RI_API int RiCom_Write(char *buf, int bufLen) {
#if defined(RI_WINDOWS)
        DWORD bytesWritten;
        WriteFile(ricomHandle, buf, bufLen, &bytesWritten, NULL);

        if (bytesWritten < 0 ) {
            return -1;
        }

        return 1;
#endif
    }


    RI_API int RiCom_Read(char *buf, int bufSize) {
#if defined(RI_WINDOWS)	
        DWORD bytesRead;
        ReadFile(ricomHandle, buf, bufSize, &bytesRead, NULL);

        if (bytesRead <= 0 ) {
            return -1;	
        }

        return 1;
#endif
    }

    RI_API int RiCom_Close() {
#if defined(RI_WINDOWS)
        CloseHandle(ricomHandle);
        ricomHandle = INVALID_HANDLE_VALUE;

        return 1;
#endif
    }


#ifdef __cplusplus

}
#endif

