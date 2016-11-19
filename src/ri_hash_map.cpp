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

#include "ri_hash_map.h"

#define RI_HASH_MAP_INIT_SIZE 16777216 // power of 2
#define RI_HASH_MAP_MUTIPLE 10
#define RI_HASH_MAP_INCEASE 2

#ifdef __cplusplus
extern "C"
{
#endif

    static int riHashMapIsInit = 0;

    static int riHashMapSsum = 0;

    int RiHashMap_InitLib() {
        if (riHashMapIsInit == 1) {
            return RI_OK_INIT_ALREADY;
        }
        riHashMapIsInit = 1;

        return RI_OK;
    }

    RiHashMap_t *RiHashMap_New() {
        RiHashMap_t *hashMap;

        if (riHashMapIsInit == 0) return NULL;

        hashMap = (RiHashMap_t *)ri_calloc(1, sizeof(RiHashMap_t));
        if (hashMap == NULL) {
            return NULL;
        }

        hashMap->data = (RiHashMapData_t **)ri_calloc(RI_HASH_MAP_INIT_SIZE  ,sizeof(RiHashMapData_t *));
        if (hashMap->data == NULL) {
            return NULL;
        }

        hashMap->size= RI_HASH_MAP_INIT_SIZE;
        

        return hashMap;
    }

    int RiHashMap_Free(RiHashMap_t *hashMap) {
        RiHashMapData_t *cur, *next;
        int i;

        if (hashMap == NULL) return RI_ERROR_NULL_POINTER;
        

        for (i = 0; i < hashMap->size; i++) {
            cur = hashMap->data[i];
            while (cur != NULL) {
                next = cur->next;
                ri_free(cur->value);
                ri_free(cur->key);
                ri_free(cur);
                cur = next;
            }
        }

        ri_free(hashMap->data);

        ri_free(hashMap);

        return RI_OK;
    }

    unsigned int riHashMap_BKDR(char *str, int len) {
        unsigned int ret = 0;
        unsigned int seed = 131;

        int i;
        for (i = 0; i < len; i++) {
            ret = ret * seed + (*str);
            str++;
        }
        return ret & 0x7FFFFFFF;
    }

    int riHashMap_CompareData(RiHashMapData_t *data, void *key, int keyLength) {
        ri_byte *cmp1 = (ri_byte *)data->key;
        ri_byte *cmp2 = (ri_byte *)key;
        int i;

        if (data->keySize != keyLength)
            return 0;

        for (i = 0; i < keyLength; i++) {
            if (cmp1[i] != cmp2[i]) {
                return 0;
            }
        }

        return 1;
    }

    int RiHashMap_Append(RiHashMap_t *hashMap, void *key, int keyLength, void *value, int valueLength) {
        char *id;
        int bkdr;
        RiHashMapData_t *data;
        int i;
        int pos;

        if (hashMap == NULL) return RI_ERROR_PARAMETER_0;
        
        if (key == NULL) return RI_ERROR_PARAMETER_1;
        if (keyLength <= 0) return RI_ERROR_PARAMETER_2;
        if (value == NULL) return RI_ERROR_PARAMETER_3;
        if (valueLength <= 0) return RI_ERROR_PARAMETER_4;

        id = (char *)key;
        bkdr = riHashMap_BKDR(id, keyLength);

        // same key exists
        data = hashMap->data[bkdr  & (hashMap->size - 1)];
        while (data != NULL) {
            if (data->hash == bkdr  && data->keySize == keyLength && riHashMap_CompareData(data, key, keyLength)) {
                ri_free(data->value);

                data->valueSize = valueLength;
                data->value = ri_malloc(valueLength);
                ri_memcpy(data->value, value, valueLength);
                return RI_OK;
            }
            data = data->next;
        }

        data = (RiHashMapData_t *)ri_malloc(sizeof(RiHashMapData_t));
        data->hash = bkdr;
        data->valueSize = valueLength;
        data->keySize = keyLength;
        data->next = NULL;

        data->key = ri_malloc(keyLength);
        ri_memcpy(data->key, key, keyLength);

        data->value = ri_malloc(valueLength);
        ri_memcpy(data->value, value, valueLength);

        // Increase hash map size.
        if ((hashMap->length + 1) * RI_HASH_MAP_MUTIPLE > hashMap->size) {
            RiHashMapData_t **dataOld = hashMap->data;
            RiHashMapData_t *cur, *next;

            int oldLength = hashMap->size;
            int newLength = hashMap->size * RI_HASH_MAP_INCEASE;

            hashMap->data = (RiHashMapData_t **)ri_calloc(newLength, sizeof(RiHashMapData_t *));

            for (i = 0; i < oldLength; i++) {
                cur = dataOld[i];
                while (cur != NULL) {
                    next = cur->next;

                    cur->next = hashMap->data[cur->hash & (newLength - 1)];
                    hashMap->data[cur->hash & (newLength - 1)] = cur;  // ?
                    cur = next;
                }

                ri_free(dataOld[i]);  // ?
            }

            ri_free(dataOld);

            hashMap->size = newLength;
        }

        pos = bkdr & (hashMap->size - 1);
        data->next = hashMap->data[pos];  // ?
        hashMap->data[pos] = data;
        hashMap->length++;

        return RI_OK;
    }

    int RiHashMap_GetSize(RiHashMap_t *hashMap) {
        if (hashMap == NULL) return RI_ERROR_NULL_POINTER;
        

        return hashMap->size;
    }

    int RiHashMap_GetLength(RiHashMap_t *hashMap) {
        if (hashMap == NULL) return RI_ERROR_NULL_POINTER;
        

        return hashMap->length;
    }

    int RiHashMap_Get(RiHashMap_t *hashMap, void *key, int keyLength, void *value, int valueSize) {
        char *id;
        int bkdr;
        int pos;
        RiHashMapData_t *cur;

        if (hashMap == NULL) return RI_ERROR_PARAMETER_0;
        
        if (key == NULL) return RI_ERROR_PARAMETER_1;
        if (keyLength <= 0) return RI_ERROR_PARAMETER_2;
        if (value == NULL) return RI_ERROR_PARAMETER_3;
        if (valueSize <= 0) return RI_ERROR_PARAMETER_4;

        id = (char *)key;
        bkdr = riHashMap_BKDR(id, keyLength);
        pos = bkdr & (hashMap->size - 1);

        cur = hashMap->data[pos];
        while (cur != NULL) {
            riHashMapSsum ++;
            if (cur->hash == bkdr && cur->keySize == keyLength && riHashMap_CompareData(cur, key, keyLength)) {
                if (valueSize < cur->valueSize) {
                    return RI_ERROR_PARAMETER_4;
                }

                ri_memcpy(value, cur->value, cur->valueSize);
                return cur->valueSize;
            }
            cur = cur->next;
        }

        return RI_ERROR_NO_MATCH;
    }

#ifdef __cplusplus
}
#endif

