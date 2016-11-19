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

#ifndef __RI_HASH_MAP_H__
#define __RI_HASH_MAP_H__

#include "openri.h"

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct RiHashMapData_t {
        void *value;
        int   valueSize;

        void *key;
        int   keySize;
        int   hash;

        struct RiHashMapData_t *next;
    } RiHashMapData_t;

    typedef struct {
        RiHashMapData_t ** data;
        int size;
        int length;
        
    } RiHashMap_t;

    RiHashMap_t *RiHashMap_New();

    int RiHashMap_Free(RiHashMap_t *hashMap);

    int RiHashMap_Append(RiHashMap_t *hashMap, void *key, int keyLength, void *value, int valueLength);

    int RiHashMap_GetLength(RiHashMap_t *hashMap);

    int RiHashMap_GetSize(RiHashMap_t *hashMap);

    int RiHashMap_Get(RiHashMap_t *hashMap, RI_IN void *key, int keyLength, void *value, int valueSize);

#ifdef __cplusplus
}
#endif

#endif /* __RI_HASH_MAP_H__ */
