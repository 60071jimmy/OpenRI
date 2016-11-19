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

    static int riBufferIsInit = 0;

    int RiBuffer_InitLib() {
        if (riBufferIsInit == 1) {
            return RI_OK_INIT_ALREADY;
        }
        riBufferIsInit = 1;

        return RI_OK;
    }

    RiBuffer_t *RiBuffer_New(int size, int align) {
        RiBuffer_t *buffer;
        int ret;

        if (riBufferIsInit == 0) return NULL;
        if (size < 0) return NULL;
        if (align < 0) return NULL;

        buffer = (RiBuffer_t *)ri_calloc(1, sizeof(RiBuffer_t));
        if (buffer == NULL) {
            return NULL;
        }

        buffer->align = align;

        ret = RiBuffer_SetSize(buffer, size);
        if (ret <= 0) {
            ri_free(buffer);
            return NULL;
        }

        

        return buffer;
    }

    int RiBuffer_Free(RiBuffer_t *buffer) {
        if (buffer == NULL) return RI_ERROR_NULL_POINTER;


        ri_free(buffer->buf);

        ri_free(buffer);

        return RI_OK;
    }

    int RiBuffer_SetSize(RiBuffer_t *buffer, int size) {
        int rest;
        ri_byte *bufTemp;

        if (buffer == NULL) return RI_ERROR_PARAMETER_0;
        
        if (size <= 0) return RI_ERROR_PARAMETER_1;

        if (buffer->size == size) {
            return RI_OK;
        }

        rest = size % buffer->align;
        size += rest;

        bufTemp = NULL;

        bufTemp = (ri_byte *) ri_malloc(size);
        if (bufTemp == NULL) {
            return RI_ERROR_NO_MEMORY;
        }

        if (buffer->size > 0) {
            if (buffer->size >= size) {
                ri_memcpy(bufTemp, buffer->buf, size);
                buffer->length = size;
            } else {
                ri_memcpy(bufTemp, buffer->buf, buffer->size);
            }
        }

        if (buffer->buf != NULL) {
            ri_free(buffer->buf);
        }

        buffer->size = size;
        buffer->buf = bufTemp;

        return RI_OK;
    }

    int RiBuffer_Append(RiBuffer_t *buffer, ri_byte *buf, int length) {
        int ret;
        int length_new;

        if (buffer == NULL) return RI_ERROR_PARAMETER_0;
        
        if (buf == NULL) return RI_ERROR_PARAMETER_1;
        if (length < 0) return RI_ERROR_PARAMETER_2;

        length_new = buffer->length + length;
        if (length_new > buffer->size) {
            ret = RiBuffer_SetSize(buffer, length_new);
            if (ret <= 0) {
                return ret;
            }
        }

        ri_memcpy(buffer->buf + buffer->length, buf, length);
        buffer->length += length;

        return RI_OK;
    }

    int RiBuffer_GetLength(RiBuffer_t *buffer) {
        if (buffer == NULL) return RI_ERROR_NULL_POINTER;
        

        return buffer->length;
    }

    int RiBuffer_GetSize(RiBuffer_t *buffer) {
        if (buffer == NULL) return RI_ERROR_NULL_POINTER;
        

        return buffer->size;
    }

    int RiBuffer_Get(RiBuffer_t *buffer, ri_byte *buf, int length) {
        if (buffer == NULL) return RI_ERROR_PARAMETER_0;
        
        if (buf == NULL) return RI_ERROR_PARAMETER_1;
        if (length <= 0) return RI_ERROR_PARAMETER_2;

        if (length > buffer->length) {
            length = buffer->length;
        }

        ri_memcpy(buf, buffer->buf, length);

        buffer->length -= length;

        if (buffer->length > 0) {
            ri_memmove(buffer->buf, buffer->buf + length, buffer->length);
        }

        return length;
    }

    int RiBuffer_Empty(RiBuffer_t *buffer) {
        if (buffer == NULL) return RI_ERROR_NULL_POINTER;
        

        buffer->length = 0;

        return RI_OK;
    }

    int RiBuffer_SetLength(RiBuffer_t *buffer, int length) {
        if (buffer == NULL) return RI_ERROR_PARAMETER_0;
        
        if (length < 0) return RI_ERROR_PARAMETER_1;
        if (buffer->length < length) return RI_ERROR_PARAMETER_1;

        buffer->length = length;

        return RI_OK;
    }

    int RiBuffer_Search(RiBuffer_t *buffer, ri_byte *buf, int length) {
        int i;
        int ret;

        if (buffer == NULL) return RI_ERROR_PARAMETER_0;
        
        if (buf == NULL) return RI_ERROR_PARAMETER_1;
        if (length <= 0) return RI_ERROR_PARAMETER_2;
        if (length > buffer->length) return RI_ERROR_PARAMETER_2;

        for (i = 0; i < buffer->length; i ++) {
            ret = ri_memcmp(buffer->buf + i, buf, length);
            if (ret == 0) {
                return i;
            }
        }

        return RI_ERROR_NOT_FOUND;
    }

    int RiBuffer_Print(RiBuffer_t *buffer) {
        char *str;

        if (buffer == NULL) return RI_ERROR_PARAMETER_0;
        
        if (buffer->length == 0) {
            return RI_OK;
        }

        str = (char *)ri_malloc(buffer->length + 1);
        if (str == NULL) {
            return RI_ERROR_NO_MEMORY;
        }

        ri_memcpy(str, buffer->buf, buffer->length);
        str[buffer->length] = '\0';

#if defined(RI_LINUX)
        RI_LOGI("%s", str);
#endif
        dbg("%s", str);

        ri_free(str);
        return RI_OK;
    }

    int RiBuffer_PrintHex(RiBuffer_t *buffer) {
        int i;
        char *str;

        if (buffer == NULL) return RI_ERROR_PARAMETER_0;
        
        if (buffer->length == 0) return RI_OK;

        str = (char *)ri_malloc(buffer->length * 2 + 1);
        if (str == NULL) {
            return RI_ERROR_NO_MEMORY;
        }

        for(i = 0; i < buffer->length; i++) {
            sprintf(&str[i*2], "%02X", (unsigned int)buffer->buf[i]);
        }
        str[buffer->length * 2 + 1] = '\0';

#if defined(RI_LINUX)
        RI_LOGI("%s", str);
#endif
        dbg("%s", str);

        ri_free(str);
        return RI_OK;
    }

    int RiBuffer_Set(RiBuffer_t *buffer, int value) {
        if (buffer == NULL) return RI_ERROR_PARAMETER_0;
        

        ri_memset(buffer->buf, value, buffer->size);

        return RI_OK;
    }

#ifdef __cplusplus
}
#endif
