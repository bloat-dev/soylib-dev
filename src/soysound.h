#ifndef SOY_SOUND_H
#define SOY_SOUND_H

#include "soycore.h"
#include "soywin.h"
#include "soythread.h"

/* win32 midi playback */

#define MAX_THREADS 1

flag soy_sound_win32_audio_thread_func_midi(void* lpParam);
flag soy_sound_win32_audio_thread_func_wave(void* lpParam);

pfThreadFunc midiFunc = soy_sound_win32_audio_thread_func_midi;
pfThreadFunc waveFunc = soy_sound_win32_audio_thread_func_wave;

typedef enum enum_threadMsg {
  ST_PLAY,
  ST_PAUSE,
  ST_STOP,
  ST_RETURN,
  ST_IDLE
} threadMsg;

typedef enum enum_mciFormat {
  MIDI,
  WAVE
} mciType;

typedef struct tag_playbackDataWin32 {
  LPSTR filename;
  HWND notifyHandle;
  UINT deviceID;
  flag prepped;
  flag finished;
  threadMsg notifyMsg;
} playbackDataWin32;

#define SS_MAX_CHANNELS 64

typedef struct tag_soySound {
  mediaMsg msg;
  soyThread threadData;
  playbackDataWin32 data;
} soySound;

flag soy_sound_win32_create(soySound* sound, HWND winHandle, const char* filename, mciType t) {
  pfThreadFunc audioFunc;
  void* pSndData;
  if(filename == NULL) {
    SLOG("Error with filename input\n");
    return ERROR;
  }
  if(sound == NULL) {
    SLOG("NULL input\n");
    return ERROR;
  }
  audioFunc = waveFunc;
  switch(t) {
    case(MIDI): audioFunc = midiFunc; SLOG("MIDI device selected\n"); break;
    case(WAVE): audioFunc = waveFunc; SLOG("WAVE device selected\n"); break;
  }
  sound->data.prepped = FALSE;
  sound->data.notifyMsg = ST_IDLE;
  sound->data.filename = (LPSTR)filename;
  sound->data.notifyHandle = winHandle;
  sound->data.finished = FALSE;
  pSndData = &(sound->data);
  if(soy_thread_create(&(sound->threadData), audioFunc, pSndData) == ERROR) {
    SLOG("Error creating thread\n");
    return ERROR;
  } else {
    SLOG1("Created thread for %s\n", filename);
  }
  return TRUE;
}

flag soy_sound_win32_play(UINT wDeviceId, HWND notifyWindow) {
  DWORD dwReturn;
  MCI_PLAY_PARMS mciPlayParms;
  char szErrorBuf[512];
  SLOG("Starting MCI playback\n");
  mciPlayParms.dwCallback = (DWORD_PTR)notifyWindow;
  if((dwReturn = mciSendCommand(wDeviceId, MCI_PLAY, MCI_NOTIFY, (DWORD_PTR)(LPVOID)&mciPlayParms))) {
    MessageBeep(MB_ICONEXCLAMATION);
    if(mciGetErrorString(dwReturn, (LPSTR)szErrorBuf, 512)) {
      MessageBox(notifyWindow, szErrorBuf, "MCI Error", MB_ICONEXCLAMATION);
    } else {
      MessageBox(notifyWindow, szErrorBuf, "UNKNOWN Error", MB_ICONEXCLAMATION);
    }
    SLOG1("Playback stopped. Error code: %ld\n", dwReturn);
    return (dwReturn);
  }
  return TRUE;
}

flag soy_sound_win32_pause(UINT wDeviceId, HWND notifyWindow) {
  DWORD dwReturn;
  MCI_GENERIC_PARMS mciPlayParms;
  char szErrorBuf[512];
  mciPlayParms.dwCallback = (DWORD_PTR)notifyWindow;
  SLOG("Pausing MCI playback\n");
  if((dwReturn = mciSendCommand(wDeviceId, MCI_PAUSE, MCI_NOTIFY, (DWORD_PTR)(LPVOID)&mciPlayParms))) {
    MessageBeep(MB_ICONEXCLAMATION);
    if(mciGetErrorString(dwReturn, (LPSTR)szErrorBuf, 512)) {
      MessageBox(notifyWindow, szErrorBuf, "MCI Error", MB_ICONEXCLAMATION);
    } else {
      MessageBox(notifyWindow, szErrorBuf, "UNKNOWN Error", MB_ICONEXCLAMATION);
    }
    SLOG("Playback stopped\n");
    return (dwReturn);
  }
  return TRUE;
}


flag soy_sound_win32_init_wave(playbackDataWin32* data, LPSTR wavFilename) {
  UINT wDeviceId;
  DWORD dwReturn;
  MCI_OPEN_PARMS mciOpenParms;
  char szErrorBuf[512];
  SLOG("Initializing WAVE MCI\n");
  mciOpenParms.lpstrDeviceType = "waveaudio";
  mciOpenParms.lpstrElementName = wavFilename;
  SLOG1("File: %s\n", wavFilename);
  if((dwReturn = mciSendCommand(0,
        MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT,
        (DWORD_PTR)(LPVOID) &mciOpenParms))) {
    if(mciGetErrorString(dwReturn, (LPSTR)szErrorBuf, 512)) {
      MessageBox(GetActiveWindow(), szErrorBuf, "MCI Error", MB_ICONEXCLAMATION);
      MessageBeep(MB_ICONEXCLAMATION);
    } else {
      MessageBox(GetActiveWindow(), szErrorBuf, "UNKNOWN Error", MB_ICONEXCLAMATION);
      MessageBeep(MB_ICONEXCLAMATION);
    }
    SLOG1("Error opening MCI device. Error code: %ld\n", dwReturn);
    return(dwReturn);
  }
  SLOG("MCI Device opened\n");
  wDeviceId = mciOpenParms.wDeviceID;
  data->deviceID = wDeviceId;
  return TRUE;
}

flag soy_sound_win32_init_midi(playbackDataWin32* data, LPSTR midiFilename) {
  flag ret = UNDEF;
  UINT wDeviceId;
  DWORD dwReturn;
  MCI_OPEN_PARMS mciOpenParms;
  MCI_STATUS_PARMS mciStatusParms;
  SLOG("Initializing MIDI MCI\n");
  mciOpenParms.lpstrDeviceType = "sequencer";
  mciOpenParms.lpstrElementName = midiFilename;
  if((dwReturn = mciSendCommand(0,
        MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT,
        (DWORD_PTR)(LPVOID) &mciOpenParms))) {
    SLOG("Error opening MCI device\n");
    return(dwReturn);
  }
  SLOG("MCI Device opened\n");
  wDeviceId = mciOpenParms.wDeviceID;
  mciStatusParms.dwItem = MCI_SEQ_STATUS_PORT;
  if((dwReturn = mciSendCommand(wDeviceId,
        MCI_STATUS, MCI_STATUS_ITEM, (DWORD_PTR)(LPVOID)&mciStatusParms))) {

    SLOG("Output port is not midi mapper\n");
    mciSendCommand(wDeviceId, MCI_CLOSE, 0, 0);
    return(dwReturn);
  }
  SLOG("MCI Output port found\n");
  data->deviceID = wDeviceId;
  ret = TRUE;
  return ret;
}

flag soy_sound_win32_poll_messages(playbackDataWin32* pDataArray) {
  flag doLoop = TRUE;
  threadMsg msgT = (pDataArray->notifyMsg);
  do {
      switch(msgT) {
        case(ST_PLAY): {
                        soy_sound_win32_play(pDataArray->deviceID, pDataArray->notifyHandle);
                        SLOG("Recieved PLAY message\n"); 
                        pDataArray->notifyMsg = ST_IDLE;
                        break; }
        case(ST_PAUSE): {
                        soy_sound_win32_pause(pDataArray->deviceID, pDataArray->notifyHandle);
                        SLOG("Recieved PAUSE message\n"); 
                        pDataArray->notifyMsg = ST_IDLE;
                        break; }
        case(ST_STOP):  {
                        SLOG("Recieved STOP message\n");
                        pDataArray->notifyMsg = ST_IDLE;
                        break; }
        case(ST_RETURN): {
                        doLoop = FALSE;
                        SLOG("Recieved RETURN message\n"); 
                        pDataArray->notifyMsg = ST_IDLE;
                        break; }
        default: {

                break; }
      }
      msgT = pDataArray->notifyMsg;
  } while(doLoop);
  return TRUE;
}

flag soy_sound_win32_audio_thread_func_midi(void* lpParam) {
  playbackDataWin32* pDataArray;
  pDataArray = (playbackDataWin32*)lpParam;
  soy_sound_win32_init_midi(pDataArray, pDataArray->filename);
  pDataArray->prepped = TRUE;
  soy_sound_win32_poll_messages(pDataArray);
  SLOG("Thread job finished, waiting to close...\n");
  return TRUE;
}

flag soy_sound_win32_audio_thread_func_wave(void* lpParam) {
  playbackDataWin32* pDataArray;
  pDataArray = (playbackDataWin32*)lpParam;
  soy_sound_win32_init_wave(pDataArray, pDataArray->filename);
  pDataArray->prepped = TRUE;
  soy_sound_win32_poll_messages(pDataArray);
  SLOG("Thread job finished, waiting to close...\n");
  return TRUE;
}

flag soy_sound_capture_events(soySound* ss, soyWindow sw) {
  if(ss == NULL) { return ERROR; }
  ss->msg = ((windowWin32*)sw.nativeWindow)->mmMsg;
  return TRUE;
}

flag soy_sound_create(soySound* ss, soyWindow* sw, const char* filepath) {
  HWND hwnd;
  if(ss == NULL || filepath == NULL) {
    SLOG("Error creating sound\n");
    return ERROR;
  }
  if(sw == NULL) {
    SLOG("Window handle is null, getting active window handle...\n");
    hwnd = GetActiveWindow();
  } else {
    hwnd = ((windowWin32*)sw->nativeWindow)->hwnd;
  }
  soy_sound_win32_create(ss, hwnd, filepath, WAVE);
  return TRUE;
}

flag soy_sound_is_active(soySound* ss) {
  if(ss == NULL) {
    return ERROR;
  }
  return (ss->data.prepped && !(ss->data.finished));
}

flag soy_sound_play(soySound* ss) {
  if(ss == NULL) {
    return ERROR;
  }
  ss->data.notifyMsg = ST_PLAY;
  return TRUE;
}

flag soy_sound_pause(soySound* ss) {
  if(ss == NULL) {
    return ERROR;
  }
  ss->data.notifyMsg = ST_PAUSE;
  return TRUE;
}

flag soy_sound_free(soySound* ss) {
  if(ss == NULL) { return FALSE; }
  soy_thread_free(&(ss->threadData));
  return TRUE;
}

#endif
