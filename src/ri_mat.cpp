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

#include <ri_mat.h>

#ifdef __cplusplus
extern "C" 
{
#endif

    static int riMatrixIsInit = 0;

    int RiMat_InitLib() {
        if (riMatrixIsInit == 1) {
            return RI_OK_INIT_ALREADY;
        }
        riMatrixIsInit = 1;

        return RI_OK;
    }

    RiMat_t *RiMat_New() {
        RiMat_t *matrix;

        if (riMatrixIsInit == 0) return NULL;

        matrix = (RiMat_t *)ri_calloc(1, sizeof(RiMat_t));
        if (matrix == NULL) {
            return NULL;
        }


        return matrix;
    }

    int RiMat_Free(RiMat_t *matrix) {
        if (matrix == NULL) return RI_ERROR_NULL_POINTER;


        if (matrix->m > 0) {
            int i;
            int n = matrix->n;
            for (i = 0; i < n; i++) {
                ri_free(matrix->value[i]);
            }
            ri_free(matrix->value);
        }

        ri_free(matrix->value);

        ri_free(matrix);

        return RI_OK;
    }

    int RiMat_Init(RiMat_t *matrix, int n, int m) {
        int i;

        if (matrix == NULL) return RI_ERROR_PARAMETER_0;
        if (n <= 0) return RI_ERROR_PARAMETER_1;
        if (m <= 0) return RI_ERROR_PARAMETER_2;

        if (matrix->value != NULL) {
            for (i = 0; i < n; i++) {
                ri_free(matrix->value[i]);
            }
            ri_free(matrix->value);
        }

        matrix->value = (double **)ri_calloc(n, sizeof(double *));
        if (matrix->value == NULL) {
            return RI_ERROR_NO_MEMORY;
        }

        for (i = 0; i < n; i++) {
            matrix->value[i] = (double *)ri_calloc(m, sizeof(double));
            if (matrix->value == NULL) {
                for (i = i; i >= 0; i--) {
                    ri_free(matrix->value[i]);
                }
                ri_free(matrix->value);

                return RI_ERROR_NO_MEMORY;
            }
        }

        matrix->n = n;
        matrix->m = m;

        return RI_OK;
    }

    int RiMat_Set(RiMat_t *matrix, int n, int m, double value) {
        if (matrix == NULL) return RI_ERROR_PARAMETER_0;
        if (n < 0) return RI_ERROR_PARAMETER_1;
        if (n >= matrix->n) return RI_ERROR_PARAMETER_1;
        if (m < 0) return RI_ERROR_PARAMETER_2;
        if (m >= matrix->m) return RI_ERROR_PARAMETER_2;

        matrix->value[n][m] = value;

        return RI_OK;
    }

    int RiMat_Get(RiMat_t *matrix, int n, int m, double *value) {
        if (matrix == NULL) return RI_ERROR_PARAMETER_0;
        if (n < 0) return RI_ERROR_PARAMETER_1;
        if (n >= matrix->n) return RI_ERROR_PARAMETER_1;
        if (m < 0) return RI_ERROR_PARAMETER_2;
        if (m >= matrix->m) return RI_ERROR_PARAMETER_2;
        if (value == NULL) return RI_ERROR_PARAMETER_3;

        *value = matrix->value[n][m];

        return RI_OK;
    }

    int RiMat_Add(RiMat_t *matrix_a, RiMat_t *matrix_b, RiMat_t *matrix_ab) {
        int n;
        int m;
        int i;
        int j;

        if (matrix_a == NULL) return RI_ERROR_PARAMETER_0;
        if (matrix_b == NULL) return RI_ERROR_PARAMETER_1;
        if (matrix_ab == NULL) return RI_ERROR_PARAMETER_2;
        if (matrix_a->n < 0)  return RI_ERROR_PARAMETER_0;
        if (matrix_a->m < 0)  return RI_ERROR_PARAMETER_0;
        if (matrix_b->n < 0)  return RI_ERROR_PARAMETER_1;
        if (matrix_b->m < 0)  return RI_ERROR_PARAMETER_1;

        if (matrix_a->n != matrix_b->n) return RI_ERROR_PARAMETER_1;
        if (matrix_a->m != matrix_b->m) return RI_ERROR_PARAMETER_1;

        n = matrix_a->n;
        m = matrix_a->m;

        RiMat_Init(matrix_ab, n, m);

        for (j = 0; j < m; j++) {
            for (i = 0; i < n; i++) {
                matrix_ab->value[i][j] = matrix_a->value[i][j] + matrix_b->value[i][j];
            }
        }
        return RI_OK;
    }

    int RiMat_Mul(RiMat_t *matrix_a, RiMat_t *matrix_b, RiMat_t *matrix_ab) {
        int n;
        int m;
        int i;
        int j;
        int k;

        if (matrix_a == NULL) return RI_ERROR_PARAMETER_0;
        if (matrix_b == NULL) return RI_ERROR_PARAMETER_1;
        if (matrix_ab == NULL) return RI_ERROR_PARAMETER_2;
        if (matrix_a->n < 0)  return RI_ERROR_PARAMETER_0;
        if (matrix_a->m < 0)  return RI_ERROR_PARAMETER_0;
        if (matrix_b->n < 0)  return RI_ERROR_PARAMETER_1;
        if (matrix_b->m < 0)  return RI_ERROR_PARAMETER_1;
        if (matrix_a->m != matrix_b->n) return RI_ERROR_PARAMETER_1;

        n = matrix_a->n;
        m = matrix_b->m;

        RiMat_Init(matrix_ab, n, m);

        for (i = 0; i < n; i++) {
            for (k = 0; k < matrix_a->m; k++) {
                for (j=0; j<matrix_b->m; j++) {
                    matrix_ab->value[i][j] += matrix_a->value[i][k] * matrix_b->value[k][j];
                }
            }
        }

        return RI_OK;
    }

#ifdef __cplusplus
}
#endif
