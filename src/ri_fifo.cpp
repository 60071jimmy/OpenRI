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

/**
* @name ri_fifo.c
*
* @brief FIFO (First in, first out) library.
*
* @reference  
*
* @author Mingta Li 
*
* @version 2.1.0
* 
* @history 2009-07-02     Re-organize.                 Mingta Li 
* @history 2006-07-20     Initial version.             Mingta Li  
*
*/


#include "openri.h"

#ifdef __cplusplus
extern "C" 
{
#endif


    RI_API int RiFifo_t_Free(RiFifo_t *fifo)
    {
        //RiSemaphore_Free(fifo->sem);  
        ri_free(fifo->data);  
        ri_free(fifo);

        return RI_OK;
    }


    RI_API RiFifo_t *RiFifo_t_New(int elementSize, int fifoLength)
    {
        RiFifo_t *fifo;

        if(elementSize == 0)  return NULL;
        if(fifoLength  == 0)  return NULL;

        fifo = (RiFifo_t *)ri_calloc(1, sizeof(RiFifo_t));

        if(fifo == NULL)
        {
            dbg("RiFifo_t_New: ri_calloc == NULL !!!" RI_NL);
            return NULL;
        }

        fifo->data = (ri_byte *)ri_calloc(fifoLength, elementSize);

        if(fifo->data == NULL)
        {
            ri_free(fifo);
            dbg("RiFifo_t_New: ri_calloc == NULL !!!" RI_NL);
            return NULL;
        }

        fifo->elementSize = elementSize;
        fifo->fifoLength = fifoLength;  

        /*fifo->sem = RiSemaphore_New(0);
        if(fifo->sem == NULL)
        {
            ri_free(fifo);
            ri_free(fifo->data);
            dbg("RiFifo_t_New: fifo->sem == NULL !!!" RI_NL);
            return NULL;
        }*/

        

        return fifo;
    }


    RI_API int RiFifo_t_Enqueue(RiFifo_t *fifo, ri_ptr element)
    { 
        //int ret;
        if(element == NULL)                        return RI_ERROR_NULL_POINTER;  

        //  dbg("RiFifo_t_Enqueue: ++, dataLength = %d" RI_NL, fifo->dataLength);

        if(fifo->dataLength == fifo->fifoLength)
        {
            dbg("RiFifo_t_Enqueue: fifo->dataLength == fifo->fifoLength !!!" RI_NL);
            return RI_ERROR_FULL;
        }

        ri_memcpy(fifo->data + fifo->elementSize*fifo->iterEnd, element, fifo->elementSize);

        fifo->iterEnd = fifo->iterEnd + 1;
        if(fifo->iterEnd >= fifo->fifoLength)  fifo->iterEnd = 0;

        fifo->dataLength ++;

        //  dbg("RiFifo_t_Enqueue: --, dataLength = %d" RI_NL, fifo->dataLength);

        //ret = RI_SEM_Signal(fifo->sem);

        //return ret;
        return RI_OK;
    }

    RI_API int RiFifo_t_Dequeue(RiFifo_t *fifo, ri_ptr element)
    { 
        //int ret;
        if(element == NULL)                   return RI_ERROR_NULL_POINTER;

        //  dbg("RiFifo_t_Dequeue: 1, dataLength = %d" RI_NL, fifo->dataLength);

        /*ret = RI_SEM_Wait(fifo->sem);
        if(ret != RI_OK)
        {
            dbg("RiFifo_t_Dequeue: RI_SEM_Wait != SUCCESS !!!" RI_NL);
            ri_memset(element, 0, fifo->elementSize);
            return ret; 
        }*/

        //  dbg("RiFifo_t_Dequeue: 2" RI_NL);

        //  dbg("RiFifo_t_Dequeue: 3" RI_NL);

        if(fifo->dataLength == 0)
        {
            ri_memset(element, 0, fifo->elementSize);
            return RI_ERROR_EMPTY;
        }

        //  dbg("RiFifo_t_Dequeue: 4" RI_NL);

        ri_memcpy(element, fifo->data + fifo->elementSize*fifo->iterStart, fifo->elementSize);

        fifo->iterStart = fifo->iterStart + 1;
        if(fifo->iterStart >= fifo->fifoLength)  fifo->iterStart = 0;

        fifo->dataLength --;

        //  dbg("RiFifo_t_Dequeue: 5" RI_NL);

        return RI_OK;  
    }

    RI_API int RiFifo_t_Empty(RiFifo_t *fifo)
    { 
        fifo->dataLength = 0;
        fifo->iterStart = 0;
        fifo->iterEnd = 0;

        // No need to handle semaphore here.
        // RI_SEM_Free(fifo->sem);
        // fifo->sem   = RI_SEM_New(0);

        return RI_OK;   
    }

    RI_API int RiFifo_t_GetFifoLength(RiFifo_t *fifo)
    {
        return fifo->fifoLength;
    }

    RI_API int RiFifo_t_GetLength(RiFifo_t *fifo)
    {
        return fifo->dataLength;
    }

    RI_API int RiFifo_t_GetElementSize(RiFifo_t *fifo)
    {
        return fifo->elementSize;
    }


#ifdef __cplusplus
}
#endif

