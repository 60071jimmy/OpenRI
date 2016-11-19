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

static int riThreadIsInit = 0;

static int riThreadPriorityUrgent = 0;
static int riThreadPriorityHigh   = 0;
static int riThreadPriorityNormal = 0;
static int riThreadPriorityLow    = 0;
static int riThreadPriorityNone   = 0;

int riThread_InitLib() {
	if (riThreadIsInit == 1) {
		return RI_OK_INIT_ALREADY;
	}
	riThreadIsInit = 1;

#if defined(RI_WINDOWS)
	//if(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED) != S_OK) {
	HRESULT h = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	// The return value of CoInitializeEx() means:
	//    S_OK: The COM library was initialized successfully on this thread.
	//    S_FALSE: The COM library is already initialized on this thread.
	//    other values: Fail to initialize the COM library.

	if (h != S_OK && h != S_FALSE) {
		return RI_ERROR;
	}

  riThreadPriorityUrgent = THREAD_PRIORITY_TIME_CRITICAL;
  riThreadPriorityNone   = THREAD_PRIORITY_IDLE;
  riThreadPriorityNormal = (riThreadPriorityUrgent + riThreadPriorityNone)/2;
  riThreadPriorityHigh   = (riThreadPriorityUrgent + riThreadPriorityNone)*3/4;
  riThreadPriorityLow    = (riThreadPriorityUrgent + riThreadPriorityNone)*1/4;
#else
  riThreadPriorityUrgent = sched_get_priority_max(SCHED_RR);
  riThreadPriorityNone   = sched_get_priority_min(SCHED_RR);
  riThreadPriorityNormal = (riThreadPriorityUrgent + riThreadPriorityNone)/2;
  riThreadPriorityHigh   = (riThreadPriorityUrgent + riThreadPriorityNone)*3/4;
  riThreadPriorityLow    = (riThreadPriorityUrgent + riThreadPriorityNone)*1/4;
#endif

	return RI_OK;
}

RI_API RiThread_t *RiThread_New() {
	RiThread_t *thread;

	if (riThreadIsInit == 0) return NULL;

	thread = (RiThread_t *)ri_calloc(1, sizeof(RiThread_t));
	if (thread == NULL) {
		return NULL;
	}

	thread->priority = riThreadPriorityNormal;

#if defined(RI_WINDOWS)

#else

#endif


	return thread;
}

RI_API int RiThread_Free(RiThread_t *thread) {
	if (thread == NULL) return RI_ERROR_NULL_POINTER;

	ri_free(thread);

	return RI_OK;
}

RI_API int RiThread_Start(RiThread_t *thread) {
	if (thread == NULL) return RI_ERROR_NULL_POINTER;

	if (thread->priority > riThreadPriorityUrgent) {
    return RI_ERROR;
  }

  if (thread->priority < riThreadPriorityNone) {
    return RI_ERROR;
  }

  if (thread->routine == NULL) {
     return RI_ERROR;
  }

#if defined(RI_WINDOWS)

#else
	int ret;
	pthread_attr_t thread_attr;
	struct sched_param thread_param;

	pthread_attr_init(&thread_attr);

	pthread_attr_setscope(&thread_attr, PTHREAD_SCOPE_SYSTEM);  // Schedule in system scope.

	if(thread->isJoinable == RI_YES)
		pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_JOINABLE);
	else
		pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);

	pthread_attr_getschedparam(&thread_attr, &thread_param);

  thread_param.sched_priority = thread->priority;
  pthread_attr_setschedparam (&thread_attr, &thread_param);

  ret = pthread_create(&thread->thread, &thread_attr, thread->routine, thread->arg);
  if (ret != 0) {
  	return RI_ERROR;
  }

  // 20140520: tried to fix memory leak but didn't succeed
  // 20140526: tried using detached thread, didn't make any difference.
  pthread_detach(pthread_self());
  pthread_attr_destroy(&thread_attr);

#endif

	return RI_OK;
}

//RI_API int RiThread_Cancel(RiThread_t *thread) {
//	int ret;
//	if (thread == NULL) return RI_ERROR_NULL_POINTER;
//	if (thread->magic != RI_MAGIC_THREAD) return RI_ERROR_MAGIC;
//
//	ret = pthread_cancel(thread->thread);
//	if (ret != 0) {
//		return RI_ERROR;
//	}
//
//	return RI_OK;
//}

RI_API int RiThread_SetPriority(RiThread_t *thread, int priority) {
	if (thread == NULL) return RI_ERROR_NULL_POINTER;

	thread->priority = priority;
	return RI_OK;
}

RI_API int RiThread_SetIsJoinable(RiThread_t *thread, int isJoinable) {
	if (thread == NULL) return RI_ERROR_NULL_POINTER;

	thread->isJoinable = isJoinable;
	return RI_OK;
}

RI_API int RiThread_SetRoutine(RiThread_t *thread, RiThreadRoutine_t routine) {
	if (thread == NULL) return RI_ERROR_NULL_POINTER;

	thread->routine = routine;
	return RI_OK;
}

RI_API int RiThread_SetArg(RiThread_t *thread, void *arg) {
	if (thread == NULL) return RI_ERROR_NULL_POINTER;

	thread->arg = arg;
	return RI_OK;
}

#ifdef __cplusplus
}
#endif
