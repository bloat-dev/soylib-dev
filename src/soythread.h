#ifndef SOY_THREAD_H
#define SOY_THREAD_H

#include "soycore.h"

#define SOY_MAX_THREADS 512

typedef struct tag_soyThreadWin32 {
  DWORD threadID;
  HANDLE threadHandle;
} soyThreadWin32;

typedef struct tag_soyThread {
  unsigned int ID;
  soyThreadWin32 winThread;
} soyThread;

typedef DWORD (*pfWin32ThreadFunc) (LPVOID args);

typedef flag (*pfThreadFunc) (void* args);

#define THREADFUNC pfThreadFunc

flag soy_thread_win32_create(soyThread* st, pfThreadFunc func, void** args) {
  pfWin32ThreadFunc tFunc = (pfWin32ThreadFunc)func;
  LPVOID tArgs = (LPVOID)args;
  st->winThread.threadHandle = CreateThread(NULL, 0, tFunc, tArgs, 0, &st->winThread.threadID);
  if(st->winThread.threadHandle == NULL) {
    return ERROR;
  }
  return TRUE;
}

flag soy_thread_win32_free(soyThread* st) {
  flag ret = UNDEF;
  if(st != NULL) {
    if(CloseHandle(st->winThread.threadHandle) == 0) {
      ret = ERROR;
    }
    st->winThread.threadHandle = NULL;
    ret = TRUE;
  } else {
    ret = ERROR;
  }
  return ret;
}

flag soy_thread_create(soyThread* st, pfThreadFunc func, void** args) {
  flag ret = UNDEF;
  if(st == NULL) { return ERROR; }
  ret = soy_thread_win32_create(st, func, args);
  if(ret == ERROR) {
    SLOG1("Error creating win32 thread %p\n", (void*)st);
  }
  return ret;
}

flag soy_thread_free(soyThread* st) {
  flag ret = UNDEF;
  if(st == NULL) { return ERROR; }
  WaitForSingleObject(st->winThread.threadHandle, INFINITE);
  ret = soy_thread_win32_free(st);
  if(ret == ERROR) {
    SLOG1("Error freeing thread %p\n", (void*)st);
  }
  return ret;
}

#endif
