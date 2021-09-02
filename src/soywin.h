#ifndef SOY_WINDOW_H
#define SOY_WINDOW_H

#include "soycore.h"
#include "soywin_win32_gl.h"

typedef enum enum_WinType {
	WIN32_NATIVE,
	WIN32_OPENGL
} WinType;

typedef struct tag_soyWindow soyWindow;
struct tag_soyWindow {
	void* nativeWindow;
	int width;
	int height;
	int x;
	int y;
	WinType type;
};

unsigned int soy_window_desktop_res_x() {
	return soy_window_win32_desktop_res_x();
}

unsigned int soy_window_desktop_res_y() {
	return soy_window_win32_desktop_res_y();
}

HDC soy_window_get_DC(soyWindow* win) {
	return soy_window_win32_get_DC((windowWin32*)win->nativeWindow);
}

flag soy_window_create(soyWindow* win, WinType type, int width, int height, int x, int y, const char* title) {
	flag result = UNDEF;
	windowWin32* nwptr = NULL;;
	nwptr = soy_alloc(nwptr, sizeof(windowWin32));
	win->type = type;
	win->width = width;
	win->height = height;
	win->x = x;
	win->y = y;
	if(nwptr == NULL) {
		SLOG("Error allocating native window handle\n");
		return FALSE;
	}
	win->nativeWindow = nwptr;
	((windowWin32*)win->nativeWindow)->borderWidth = SOY_DEFAULT_BORDER_SIZE;
	((windowWin32*)win->nativeWindow)->titlebarHeight = SOY_DEFAULT_TITLEBAR_SIZE;
	SLOG2("Creating %d x %d window... ", width, height);
	switch(type) {
		case(WIN32_NATIVE): {
			result = soy_window_win32_create(nwptr, width, height, x, y, title);
			break;
		}
		case(WIN32_OPENGL): {
			result = soy_window_win32_create_gl(nwptr, width, height, x, y, title);
			break;
		}
	}
	GetWindowRect(nwptr->hwnd, &nwptr->windowRect);
	PCHECK(result);
	return result;
}

flag soy_window_poll_events(soyWindow* win) {	
	soy_window_win32_poll_events((windowWin32*)win->nativeWindow);
	win->width = ((windowWin32*)win->nativeWindow)->width;
	win->height = ((windowWin32*)win->nativeWindow)->height;
	win->x = ((windowWin32*)win->nativeWindow)->x;
	win->y = ((windowWin32*)win->nativeWindow)->y;
	return TRUE;
}

flag soy_window_blit_pixels(soyWindow* win, void* memory, int width, int height, int res) {
	((windowWin32*)win->nativeWindow)->titlebarHeight = SOY_DEFAULT_TITLEBAR_SIZE*res;
	soy_window_win32_blit_pixels((windowWin32*)win->nativeWindow, memory, width, height);
	return TRUE;
}

flag soy_window_free(soyWindow* win) {
	SLOG1("Freeing window %p... ", (void*)win);
	soy_window_win32_close((windowWin32*)(win->nativeWindow));
	if(win) {
		if(win->nativeWindow) {
			soy_free(win->nativeWindow);
			win->nativeWindow = NULL;
		}
	}
	PCHECK(TRUE);
	return TRUE;
}

flag soy_window_quit() {
	soy_window_win32_quit();
	return TRUE;
}

flag soy_window_close(soyWindow* win) {
	soy_window_free(win);
	return TRUE;
}

#endif
