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

#ifndef __RI_FIFO_H__
#define __RI_FIFO_H__

#include "openri.h"

#ifdef __cplusplus
extern "C" 
{
#endif

typedef struct {
  int            iterStart;
  int            iterEnd;
  int            elementSize;
  int            dataLength;
  int            fifoLength;  
  ri_byte          *data;
} RiFifo_t;

RI_API RiFifo_t *RiFifo_t_New(int elementSize, int fifoLength);
RI_API int  RiFifo_t_Init(RiFifo_t *fifo, int elementSize, int fifoLength);
RI_API int  RiFifo_t_Enqueue(RiFifo_t *fifo, ri_ptr element);
RI_API int  RiFifo_t_Dequeue(RiFifo_t *fifo, ri_ptr element);
RI_API int  RiFifo_t_Empty(RiFifo_t *fifo);
RI_API int    RiFifo_t_GetFifoLength(RiFifo_t *fifo);
RI_API int    RiFifo_t_GetLength(RiFifo_t *fifo);
RI_API int    RiFifo_t_GetElementSize(RiFifo_t *fifo);
RI_API int  RiFifo_t_Free(RiFifo_t *fifo);

#ifdef __cplusplus
}
#endif

#endif /* __RI_FIFO_H__ */
