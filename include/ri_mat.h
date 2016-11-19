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

#ifndef __RI_MAT_H__
#define __RI_MAT_H__

#include "openri.h"

#ifdef __cplusplus
extern "C" 
{
#endif

    typedef struct {
        int n;
        int m;
        double      **value;
    } RiMat_t;

    RiMat_t *RiMat_New();

    int RiMat_Free(RiMat_t *matrix);

    int RiMat_Init(RiMat_t *matrix, int n, int m);

    int RiMat_Set(RiMat_t *matrix, int n, int m, double value);

    int RiMat_Get(RiMat_t *matrix, int x, int y, double *value);

    int RiMat_Add(RiMat_t *matrix_a, RiMat_t *matrix_b, RiMat_t *matrix_ab);

    int RiMat_Mul(RiMat_t *matrix_a, RiMat_t *matrix_b, RiMat_t *matrix_ab);

#ifdef __cplusplus
}
#endif

#endif /* __RI_MAT_H__ */
