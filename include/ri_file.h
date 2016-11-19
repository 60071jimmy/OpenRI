/*
Copyright (c) LEADERG INC. All rights reserved.
Released under LEADERG LICENSE NUMBER 1.
*/

#ifndef __RI_FILE_H__
#define __RI_FILE_H__

#include "openri.h"

#if defined(RI_VC)
#define RI_FILE_O_RDONLY       _O_RDONLY
#define RI_FILE_O_WRONLY       _O_WRONLY
#define RI_FILE_O_RDWR         _O_RDWR
#define RI_FILE_O_CREAT        _O_CREAT
#define RI_FILE_O_EXCL         _O_EXCL
//  #define RI_FILE_O_NOCTTY       _O_NOCTTY
#define RI_FILE_O_TRUNC        _O_TRUNC  
#define RI_FILE_O_APPEND       _O_APPEND
//  #define RI_FILE_O_NONBLOCK     _O_NONBLOCK
//  #define RI_FILE_O_NDELAY     _O_NDELAY
//  #define RI_FILE_O_SYNC       _O_SYNC
//  #define RI_FILE_O_NOFOLLOW       _O_NOFOLLOW

#define RI_FILE_O_BINARY       _O_BINARY
#define RI_FILE_O_TEXT         _O_TEXT
#define RI_FILE_O_NOINHERIT    _O_NOINHERIT
#define RI_FILE_O_RANDOM       _O_RANDOM    
#define RI_FILE_O_SEQUENTIAL   _O_SEQUENTIAL
#define RI_FILE_O_SHORT_LIVED  _O_SHORT_LIVED
#define RI_FILE_O_U16TEXT      _O_U16TEXT
#define RI_FILE_O_U8TEXT       _O_U8TEXT
#define RI_FILE_O_WTEXT        _O_WTEXT

#define RI_FILE_S_IREAD        _S_IREAD
#define RI_FILE_S_IWRITE       _S_IWRITE
#else  
#define RI_FILE_O_RDONLY       O_RDONLY
#define RI_FILE_O_WRONLY       O_WRONLY
#define RI_FILE_O_RDWR         O_RDWR
#define RI_FILE_O_CREAT        O_CREAT
#define RI_FILE_O_EXCL         O_EXCL
#define RI_FILE_O_NOCTTY       O_NOCTTY
#define RI_FILE_O_TRUNC        O_TRUNC  
#define RI_FILE_O_APPEND       O_APPEND
#define RI_FILE_O_NONBLOCK     O_NONBLOCK
#define RI_FILE_O_NDELAY       O_NDELAY
#define RI_FILE_O_SYNC         O_SYNC
#define RI_FILE_O_NOFOLLOW     O_NOFOLLOW

//  #define RI_FILE_O_BINARY       O_BINARY
//  #define RI_FILE_O_TEXT         O_TEXT
//  #define RI_FILE_O_NOINHERIT    O_NOINHERIT
//  #define RI_FILE_O_RANDOM       O_RANDOM    
//  #define RI_FILE_O_SEQUENTIAL   O_SEQUENTIAL
//  #define RI_FILE_O_SHORT_LIVED  O_SHORT_LIVED
//  #define RI_FILE_O_U16TEXT      O_U16TEXT
//  #define RI_FILE_O_U8TEXT       O_U8TEXT
//  #define RI_FILE_O_WTEXT        O_WTEXT

//  #define RI_FILE_S_IREAD        S_IREAD
//  #define RI_FILE_S_IWRITE       S_IWRITE

#define RI_FILE_S_IRWXU        S_IRWXU
#define RI_FILE_S_IRUSR        S_IRUSR
#define RI_FILE_S_IWUSR        S_IWUSR
#define RI_FILE_S_IXUSR        S_IXUSR
#define RI_FILE_S_IRWXG        S_IRWXG
#define RI_FILE_S_IRGRP        S_IRGRP
#define RI_FILE_S_IWGRP        S_IWGRP
#define RI_FILE_S_IXGRP        S_IXGRP
#define RI_FILE_S_IRWXO        S_IRWXO
#define RI_FILE_S_IROTH        S_IROTH
#define RI_FILE_S_IWOTH        S_IWOTH
#define RI_FILE_S_IXOTH        S_IXOTH
#endif

#define RI_FILE_SEEK_SET   SEEK_SET
#define RI_FILE_SEEK_CUR   SEEK_CUR
#define RI_FILE_SEEK_END   SEEK_END

typedef struct {
#if defined (RI_VC)
    HANDLE sys_file;
#else
    int sys_file;
#endif

    void       *lock;
} RiFile_t;  

#ifdef __cplusplus
extern "C"
{
#endif

    int RiFile_InitLib();

    RiFile_t *RiFile_New();

    int RiFile_Free(RiFile_t *riFile);

    int RiFile_Lock(RiFile_t *riFile);

    int RiFile_Unlock(RiFile_t *riFile);

    int RiFile_Open(RiFile_t *riFile, ri_utf8 *path , int flags);

    int RiFile_Close(RiFile_t *riFile);

    ri_int64 RiFile_Write(RiFile_t *riFile, const void *buffer, ri_int64 count);

    ri_int64 RiFile_Read(RiFile_t *riFile, void *buffer, ri_int64 count);

    ri_int64 RiFile_Seek(RiFile_t *riFile, ri_int64 offset, int origin);

    int RiFile_Sync(RiFile_t *riFile);

    ri_int64 RiFile_GetSize(RiFile_t *riFile);

    int RiFile_Chmod(ri_utf8 *path, int mode);

#ifdef __cplusplus
}
#endif

#endif /* __RI_FILE_H__ */
