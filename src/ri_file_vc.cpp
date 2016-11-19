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

#include "ri_file.h"

#ifdef __cplusplus
extern "C" 
{
#endif

    static int riFileIsInit = 0;

    int RiFile_InitLib() {
        if (riFileIsInit == 1) {
            return RI_OK_INIT_ALREADY;
        }
        riFileIsInit = 1;

        return RI_OK;
    }

    RiFile_t *RiFile_New() {
        RiFile_t *riFile;

        if (riFileIsInit == 0) return NULL;

        riFile = (RiFile_t *)ri_calloc(1, sizeof(RiFile_t));
        if (riFile == NULL) {
            return NULL;
        }

        riFile->sys_file = INVALID_HANDLE_VALUE;

        return riFile;
    }

    int RiFile_Free(RiFile_t *riFile) {
        if (riFile == NULL) return RI_ERROR_NULL_POINTER;


        ri_free(riFile);

        return RI_OK;
    }

    int RiFile_Lock(RiFile_t *riFile) {
        if (riFile == NULL) return RI_ERROR_NULL_POINTER;

        if (riFile->lock == NULL) {
            riFile->lock  = RiLock_New();
            if (riFile->lock == NULL) {
                return RI_ERROR_NEW_LOCK;
            }
        }

        return RiLock_Lock((RiLock_t *)riFile->lock);
    }

    int RiFile_Unlock(RiFile_t *riFile) {
        if (riFile== NULL) return RI_ERROR_NULL_POINTER;

        return RiLock_Unlock((RiLock_t *)riFile->lock);
    }

    int RiFile_Open(RiFile_t *riFile, ri_utf8 *path , int flags) {
        if (riFile == NULL) return RI_ERROR_PARAMETER_0;
        if (path == NULL) return RI_ERROR_PARAMETER_1;

#if defined(RI_LINUX)
        riFile->sys_file = open((const char *)path, flags);
        if (riFile->sys_file < 0) {
            return RI_ERROR_OPEN_FILE;
        }
#endif
        return RI_OK;
    }

    int RiFile_Close(RiFile_t *riFile) {
        if (riFile == NULL) return RI_ERROR_PARAMETER_0;

        if (riFile->sys_file < 0) {
            return RI_OK_DONE_ALREADY;
        }

#if defined(RI_LINUX)
        int ret = close(riFile->sys_file);

        if (ret != 0) {
            return RI_ERROR;
        }
#endif
        return RI_OK;
    }

    ri_int64 RiFile_Read(RiFile_t *riFile, void *buffer, ri_int64 count) {
        if (riFile == NULL) return RI_ERROR_PARAMETER_0;
        if (buffer == NULL) return RI_ERROR_PARAMETER_1;
        if (count <= 0) return RI_ERROR_PARAMETER_2;

        if (riFile->sys_file < 0) {
            return RI_ERROR_OPEN_FILE;
        }
#if defined(RI_LINUX)
        return read(riFile->sys_file, buffer, count);
#endif

        return 0;

    }

    ri_int64 RiFile_Write(RiFile_t *riFile, const void *buffer, ri_int64 count) {
        if (riFile == NULL) return RI_ERROR_PARAMETER_0;
        if (buffer == NULL) return RI_ERROR_PARAMETER_1;
        if (count <= 0) return RI_ERROR_PARAMETER_2;

        if (riFile->sys_file < 0) {
            return RI_ERROR_OPEN_FILE;
        }
#if defined(RI_LINUX)
        return write(riFile->sys_file, buffer, count);
#endif
        return 0;

    }

    ri_int64 RiFile_Seek(RiFile_t *riFile, ri_int64 offset, int origin) {
        if (riFile == NULL) return RI_ERROR_PARAMETER_0;

        if (riFile->sys_file < 0) {
            return RI_ERROR_OPEN_FILE;
        }
#if defined(RI_LINUX)
        return lseek(riFile->sys_file, offset, origin);  // lseek = lseek64 in SH4 tool chain.
#endif
        return 0;

    }

    int RiFile_Sync(RiFile_t *riFile) {
        if (riFile == NULL) return RI_ERROR_PARAMETER_0;

        if (riFile->sys_file < 0) {
            return RI_ERROR_OPEN_FILE;
        }
#if defined(RI_LINUX)
        int ret = fsync(riFile->sys_file);

        if (ret != 0) {
            return RI_ERROR;	
        }

#endif

        return RI_OK;
    }

    ri_int64 RiFile_GetSize(RiFile_t *riFile) {
        if (riFile == NULL) return RI_ERROR_PARAMETER_0;

        if (riFile->sys_file < 0) {
            return RI_ERROR_OPEN_FILE;
        }
#if defined(RI_LINUX)
        ri_int64 currentPosition = lseek(riFile->sys_file, 0, SEEK_CUR);

        ri_int64 fileSize = lseek(riFile->sys_file, 0, SEEK_END);

        ri_int64 newPosition = lseek(riFile->sys_file, currentPosition, SEEK_SET);

        if (currentPosition != newPosition) {
            return RI_ERROR;
        }

        return fileSize;
#endif
        return 0;
    }

    int RiFile_Chmod(ri_utf8 *path, int mode) {
        if (path == NULL) return RI_ERROR_PARAMETER_0;
#if defined(RI_LINUX)
        int ret = chmod((const char *)path, mode);
        if (ret != 0) {
            return RI_ERROR;
        }
#endif
        return RI_OK;
    }

#ifdef __cplusplus
}
#endif
