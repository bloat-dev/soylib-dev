#ifndef SOY_WINDOW_OPENGL_H
#define SOY_WINDOW_OPENGL_H

#include "soycore.h"
#include "soycursors.h"

#define WGL_DRAW_TO_WINDOW_ARB         	  0x2001
#define WGL_ACCELERATION_ARB              0x2003
#define WGL_SWAP_METHOD_ARB               0x2007
#define WGL_SUPPORT_OPENGL_ARB            0x2010
#define WGL_DOUBLE_BUFFER_ARB             0x2011
#define WGL_PIXEL_TYPE_ARB                0x2013
#define WGL_COLOR_BITS_ARB                0x2014
#define WGL_DEPTH_BITS_ARB                0x2022
#define WGL_STENCIL_BITS_ARB              0x2023
#define WGL_FULL_ACCELERATION_ARB         0x2027
#define WGL_SWAP_EXCHANGE_ARB          	  0x2028
#define WGL_TYPE_RGBA_ARB              	  0x202B
#define WGL_CONTEXT_MAJOR_VERSION_ARB  	  0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB     0x2092
#define GL_ARRAY_BUFFER                   0x8892
#define GL_STATIC_DRAW                    0x88E4
#define GL_FRAGMENT_SHADER                0x8B30
#define GL_VERTEX_SHADER                  0x8B31
#define GL_COMPILE_STATUS                 0x8B81
#define GL_LINK_STATUS                    0x8B82
#define GL_INFO_LOG_LENGTH                0x8B84
#define GL_TEXTURE0                       0x84C0
#define GL_BGRA                           0x80E1
#define GL_ELEMENT_ARRAY_BUFFER           0x8893


typedef BOOL (WINAPI * PFNWGLCHOOSEPIXELFORMATARBPROC) (HDC hdc, const int *piAttribIList, const FLOAT *pfAttribFList, UINT nMaxFormats,
				                                                        int *piFormats, UINT *nNumFormats);
typedef HGLRC (WINAPI * PFNWGLCREATECONTEXTATTRIBSARBPROC) (HDC hDC, HGLRC hShareContext, const int *attribList);
typedef BOOL (WINAPI * PFNWGLSWAPINTERVALEXTPROC) (int interval);
typedef void (APIENTRY * PFNGLATTACHSHADERPROC) (GLuint program, GLuint shader);
typedef void (APIENTRY * PFNGLBINDBUFFERPROC) (GLenum target, GLuint buffer);
typedef void (APIENTRY * PFNGLBINDVERTEXARRAYPROC) (GLuint array);
typedef void (APIENTRY * PFNGLBUFFERDATAPROC) (GLenum target, ptrdiff_t size, const GLvoid *data, GLenum usage);
typedef void (APIENTRY * PFNGLCOMPILESHADERPROC) (GLuint shader);
typedef GLuint (APIENTRY * PFNGLCREATEPROGRAMPROC) (void);
typedef GLuint (APIENTRY * PFNGLCREATESHADERPROC) (GLenum type);
typedef void (APIENTRY * PFNGLDELETEBUFFERSPROC) (GLsizei n, const GLuint *buffers);
typedef void (APIENTRY * PFNGLDELETEPROGRAMPROC) (GLuint program);
typedef void (APIENTRY * PFNGLDELETESHADERPROC) (GLuint shader);
typedef void (APIENTRY * PFNGLDELETEVERTEXARRAYSPROC) (GLsizei n, const GLuint *arrays);
typedef void (APIENTRY * PFNGLDETACHSHADERPROC) (GLuint program, GLuint shader);
typedef void (APIENTRY * PFNGLENABLEVERTEXATTRIBARRAYPROC) (GLuint index);
typedef void (APIENTRY * PFNGLGENBUFFERSPROC) (GLsizei n, GLuint *buffers);
typedef void (APIENTRY * PFNGLGENVERTEXARRAYSPROC) (GLsizei n, GLuint *arrays);
typedef GLint (APIENTRY * PFNGLGETATTRIBLOCATIONPROC) (GLuint program, const char *name);
typedef void (APIENTRY * PFNGLGETPROGRAMINFOLOGPROC) (GLuint program, GLsizei bufSize, GLsizei *length, char *infoLog);
typedef void (APIENTRY * PFNGLGETPROGRAMIVPROC) (GLuint program, GLenum pname, GLint *params);
typedef void (APIENTRY * PFNGLGETSHADERINFOLOGPROC) (GLuint shader, GLsizei bufSize, GLsizei *length, char *infoLog);
typedef void (APIENTRY * PFNGLGETSHADERIVPROC) (GLuint shader, GLenum pname, GLint *params);
typedef void (APIENTRY * PFNGLLINKPROGRAMPROC) (GLuint program);
typedef void (APIENTRY * PFNGLSHADERSOURCEPROC) (GLuint shader, GLsizei count, const char* *string, const GLint *length);
typedef void (APIENTRY * PFNGLUSEPROGRAMPROC) (GLuint program);
typedef void (APIENTRY * PFNGLVERTEXATTRIBPOINTERPROC) (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride,
				                                                        const GLvoid *pointer);
typedef void (APIENTRY * PFNGLBINDATTRIBLOCATIONPROC) (GLuint program, GLuint index, const char *name);
typedef GLint (APIENTRY * PFNGLGETUNIFORMLOCATIONPROC) (GLuint program, const char *name);
typedef void (APIENTRY * PFNGLUNIFORMMATRIX4FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRY * PFNGLACTIVETEXTUREPROC) (GLenum texture);
typedef void (APIENTRY * PFNGLUNIFORM1IPROC) (GLint location, GLint v0);
typedef void (APIENTRY * PFNGLGENERATEMIPMAPPROC) (GLenum target);
typedef void (APIENTRY * PFNGLDISABLEVERTEXATTRIBARRAYPROC) (GLuint index);
typedef void (APIENTRY * PFNGLUNIFORM3FVPROC) (GLint location, GLsizei count, const GLfloat *value);
typedef void (APIENTRY * PFNGLUNIFORM4FVPROC) (GLint location, GLsizei count, const GLfloat *value);

PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;
PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT;

PFNGLATTACHSHADERPROC glAttachShader;
PFNGLBINDBUFFERPROC glBindBuffer;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
PFNGLBUFFERDATAPROC glBufferData;
PFNGLCOMPILESHADERPROC glCompileShader;
PFNGLCREATEPROGRAMPROC glCreateProgram;
PFNGLCREATESHADERPROC glCreateShader;
PFNGLDELETEBUFFERSPROC glDeleteBuffers;
PFNGLDELETEPROGRAMPROC glDeleteProgram;
PFNGLDELETESHADERPROC glDeleteShader;
PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
PFNGLDETACHSHADERPROC glDetachShader;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
PFNGLGENBUFFERSPROC glGenBuffers;
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
PFNGLGETPROGRAMIVPROC glGetProgramiv;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
PFNGLGETSHADERIVPROC glGetShaderiv;
PFNGLLINKPROGRAMPROC glLinkProgram;
PFNGLSHADERSOURCEPROC glShaderSource;
PFNGLUSEPROGRAMPROC glUseProgram;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
PFNGLACTIVETEXTUREPROC glActiveTexture;
PFNGLUNIFORM1IPROC glUniform1i;
PFNGLGENERATEMIPMAPPROC glGenerateMipmap;
PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
PFNGLUNIFORM3FVPROC glUniform3fv;
PFNGLUNIFORM4FVPROC glUniform4fv;

flag soy_gl_load_extension_list() {
	wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
	if(!wglChoosePixelFormatARB){ return FALSE; }

	wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
	if(!wglCreateContextAttribsARB){ return FALSE; }

	wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
	if(!wglSwapIntervalEXT){ return FALSE; }

	glAttachShader = (PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader");
	if(!glAttachShader){ return FALSE; }

	glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
	if(!glBindBuffer){ return FALSE; }

	glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)wglGetProcAddress("glBindVertexArray");
	if(!glBindVertexArray){ return FALSE; }

	glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
	if(!glBufferData){ return FALSE; }

	glCompileShader = (PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");
	if(!glCompileShader){ return FALSE; }

	glCreateProgram = (PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram");
	if(!glCreateProgram){ return FALSE; }

	glCreateShader = (PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader");
	if(!glCreateShader){ return FALSE; }

	glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)wglGetProcAddress("glDeleteBuffers");
	if(!glDeleteBuffers){ return FALSE; }

	glDeleteProgram = (PFNGLDELETEPROGRAMPROC)wglGetProcAddress("glDeleteProgram");
	if(!glDeleteProgram){ return FALSE; }

	glDeleteShader = (PFNGLDELETESHADERPROC)wglGetProcAddress("glDeleteShader");
	if(!glDeleteShader){ return FALSE; }

	glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)wglGetProcAddress("glDeleteVertexArrays");
	if(!glDeleteVertexArrays){ return FALSE; }

	glDetachShader = (PFNGLDETACHSHADERPROC)wglGetProcAddress("glDetachShader");
	if(!glDetachShader){ return FALSE; }

	glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glEnableVertexAttribArray");
	if(!glEnableVertexAttribArray){ return FALSE; }

	glGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
	if(!glGenBuffers){ return FALSE; }

	glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)wglGetProcAddress("glGenVertexArrays");
	if(!glGenVertexArrays){ return FALSE; }

	glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)wglGetProcAddress("glGetAttribLocation");
	if(!glGetAttribLocation){ return FALSE; }

	glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)wglGetProcAddress("glGetProgramInfoLog");
	if(!glGetProgramInfoLog){ return FALSE; }

	glGetProgramiv = (PFNGLGETPROGRAMIVPROC)wglGetProcAddress("glGetProgramiv");
	if(!glGetProgramiv){ return FALSE; }

	glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)wglGetProcAddress("glGetShaderInfoLog");
	if(!glGetShaderInfoLog){ return FALSE; }

	glGetShaderiv = (PFNGLGETSHADERIVPROC)wglGetProcAddress("glGetShaderiv");
	if(!glGetShaderiv){ return FALSE; }

	glLinkProgram = (PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram");
	if(!glLinkProgram){ return FALSE; }

	glShaderSource = (PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource");
	if(!glShaderSource){ return FALSE; }

	glUseProgram = (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram");
	if(!glUseProgram){ return FALSE; }

	glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)wglGetProcAddress("glVertexAttribPointer");
	if(!glVertexAttribPointer){ return FALSE; }

	glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)wglGetProcAddress("glBindAttribLocation");
	if(!glBindAttribLocation){ return FALSE; }

	glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation");
	if(!glGetUniformLocation){ return FALSE; }

	glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)wglGetProcAddress("glUniformMatrix4fv");
	if(!glUniformMatrix4fv){ return FALSE; }

	glActiveTexture = (PFNGLACTIVETEXTUREPROC)wglGetProcAddress("glActiveTexture");
	if(!glActiveTexture){ return FALSE; }

	glUniform1i = (PFNGLUNIFORM1IPROC)wglGetProcAddress("glUniform1i");
	if(!glUniform1i) { return FALSE; }

	glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)wglGetProcAddress("glGenerateMipmap");
	if(!glGenerateMipmap) { return FALSE; }

	glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glDisableVertexAttribArray");
	if(!glDisableVertexAttribArray) { return FALSE; }

	glUniform3fv = (PFNGLUNIFORM3FVPROC)wglGetProcAddress("glUniform3fv");
	if(!glUniform3fv) { return FALSE; }

	glUniform4fv = (PFNGLUNIFORM4FVPROC)wglGetProcAddress("glUniform4fv");
	if(!glUniform4fv) { return FALSE; }
	return TRUE;
}

#define SOY_CURSOR_COUNT 8

typedef enum enum_cursorType {
	CURSOR_ARROW,
	CURSOR_WAIT,
	CURSOR_MOVE,
	CURSOR_SIZEH,
	CURSOR_SIZEV,
	CURSOR_SIZEDLR,
	CURSOR_SIZEDRL,
	CURSOR_HAND,
	CURSOR_TEXT,
	CURSOR_CROSS
} cursorType;

typedef struct tag_windowWin32 {
	HWND hwnd;
	RECT windowRect;
	MSG msg;
	mediaMsg mmMsg;
	HDC deviceContext;
	HGLRC renderContext;
	flag fullscreen;
	cursorType cursorStyle;
	int instanceIndex;
	int x;
	int y;
	int width;
	int height;
	int titlebarHeight;
	int borderWidth;
} windowWin32;

static HCURSOR HCUR_WAIT;
static HCURSOR HCUR_ARROW;
static HCURSOR HCUR_TEXT;
static HCURSOR HCUR_HAND;
static HCURSOR HCUR_RESIZEH;
static HCURSOR HCUR_RESIZEV;
static HCURSOR HCUR_RESIZEDL;
static HCURSOR HCUR_RESIZEDR;
static HCURSOR HCUR_CROSS;
static HCURSOR HCUR_MOVE;
static HCURSOR HCUR_NORMAL;

HDC soy_window_win32_get_DC(windowWin32* window) {
	return window->deviceContext;
}

flag soy_window_win32_load_cursors() {
	HCUR_WAIT = LoadCursor(NULL, IDC_WAIT);
	HCUR_ARROW = LoadCursor(NULL, IDC_ARROW);
	HCUR_HAND = LoadCursor(NULL, IDC_HAND);
	HCUR_TEXT = LoadCursor(NULL, IDC_IBEAM);
	HCUR_RESIZEH = LoadCursor(NULL, IDC_SIZEWE);
	HCUR_RESIZEV = LoadCursor(NULL, IDC_SIZENS);
	HCUR_RESIZEDL = LoadCursor(NULL, IDC_SIZENWSE);
	HCUR_RESIZEDR = LoadCursor(NULL, IDC_SIZENESW);
	HCUR_MOVE = LoadCursor(NULL, IDC_SIZEALL);
	HCUR_NORMAL = LoadCursor(NULL, IDC_ARROW);
	return 0;
}

flag soy_gl_init_opengl(windowWin32* window, int vsync) {
	int attributeListInt[19];
	int pixelFormat[1];
	unsigned int formatCount;
	int result;
	PIXELFORMATDESCRIPTOR pfd;
	int attributeList[5];
	char* vendorString;
	char* rendererString;

	window->deviceContext = GetDC(window->hwnd);
	if(!(window->deviceContext)) {
		SLOG("OpenGL GetDC error!\n");
		return FALSE;
	}
	/* Support for OpenGL rendering. */
	attributeListInt[0] = WGL_SUPPORT_OPENGL_ARB;
	attributeListInt[1] = TRUE;
	/* Support for rendering to a window. */
	attributeListInt[2] = WGL_DRAW_TO_WINDOW_ARB;
	attributeListInt[3] = TRUE;
	/* Support for hardware acceleration. */
	attributeListInt[4] = WGL_ACCELERATION_ARB;
	attributeListInt[5] = WGL_FULL_ACCELERATION_ARB;
	/* Support for 24bit color. */
	attributeListInt[6] = WGL_COLOR_BITS_ARB;
	attributeListInt[7] = 24;
	/* Support for 24 bit depth buffer. */
	attributeListInt[8] = WGL_DEPTH_BITS_ARB;
	attributeListInt[9] = 24;
	/* Support for double buffer. */
	attributeListInt[10] = WGL_DOUBLE_BUFFER_ARB;
	attributeListInt[11] = TRUE;
	/* Support for swapping front and back buffer. */
	attributeListInt[12] = WGL_SWAP_METHOD_ARB;
	attributeListInt[13] = WGL_SWAP_EXCHANGE_ARB;
	/* Support for the RGBA pixel type. */
	attributeListInt[14] = WGL_PIXEL_TYPE_ARB;
	attributeListInt[15] = WGL_TYPE_RGBA_ARB;
	/* Support for a 8 bit stencil buffer. */
	attributeListInt[16] = WGL_STENCIL_BITS_ARB;
	attributeListInt[17] = 8;
	/* Null terminate the attribute list. */
	attributeListInt[18] = 0;

	result = wglChoosePixelFormatARB(window->deviceContext, attributeListInt, NULL, 1, pixelFormat, &formatCount);
	if(result != 1) {
		SLOG("OpenGL wglChoosePixelFormatARB error!\n");
		return FALSE;
	}
	result = SetPixelFormat(window->deviceContext, pixelFormat[0], &pfd);
	if(result != 1) {
		SLOG("OpenGL SetPixelFormat error!\n");
		return FALSE;
	}
	/* Set to OpenGL version 4.0 */
	attributeList[0] = WGL_CONTEXT_MAJOR_VERSION_ARB;
	attributeList[1] = 4;
	attributeList[2] = WGL_CONTEXT_MINOR_VERSION_ARB;
	attributeList[3] = 0;

	/* Null-terminate the attrib list */
	attributeList[4] = 0;

	window->renderContext = wglCreateContextAttribsARB(window->deviceContext, 0, attributeList);
	if(window->renderContext == NULL) {
		SLOG("OpenGL error!\n");
		return FALSE;
	}

	result = wglMakeCurrent(window->deviceContext, window->renderContext);
	if(result != 1) {
		SLOG("OpenGL error!\n");
		return FALSE;
	}

	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CW);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	vendorString = (char*)glGetString(GL_VENDOR);
	rendererString = (char*)glGetString(GL_RENDERER);
	SLOG2("Video card: \n %s\n %s\n", vendorString, rendererString);

	if(vsync == 0 ){
		result = wglSwapIntervalEXT(0);
	} else if (vsync == 1) {
		result = wglSwapIntervalEXT(1);
	}
	if(result != 1) {
		SLOG("OpenGL error!\n");
		return FALSE;
	}
	return TRUE;
}

flag soy_gl_init_extensions(HWND hwnd) {
	HDC deviceContext;
	HGLRC renderContext;
	PIXELFORMATDESCRIPTOR pixelFormat;
	int error;
	int bRes;

	deviceContext = GetDC(hwnd);
	if(!deviceContext)	{ return FALSE; }

	error = SetPixelFormat(deviceContext, 1, &pixelFormat);
	if(error != 1) { return FALSE; }

	renderContext = wglCreateContext(deviceContext);
	if(!renderContext) { return FALSE; }

	error = wglMakeCurrent(deviceContext, renderContext);
	if(error != 1) { return FALSE; }

	bRes = soy_gl_load_extension_list();
	if(!bRes) {
			SLOG("Failed to load GL Extensions!\n");
			return FALSE;
	}

	wglMakeCurrent(NULL,NULL);
	wglDeleteContext(renderContext);
	renderContext = NULL;

	ReleaseDC(hwnd, deviceContext);
	deviceContext = 0;
	return TRUE;
}

flag soy_gl_make_current(windowWin32* window) {
	wglMakeCurrent(window->deviceContext, window->renderContext);
	return TRUE;
}

/*********************/
/* win32 window code */
/*********************/

int FULL_SCREEN = 0;
int S_CENTERED = 0;

LRESULT CALLBACK winProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

#define S_MAX_WINDOWS 16
static windowWin32* s_instances[S_MAX_WINDOWS];
static int s_windowCount = 0;

WINDOWPLACEMENT global_wpc;
LONG HWNDStyle = 0;
LONG HWNDStyleEx = 0;

static flag s_add_instance_to_index(windowWin32* windowInstance) {
	flag ret = UNDEF;
	int wcnt = 0;
	int i = 0;
	windowInstance->titlebarHeight = SOY_DEFAULT_TITLEBAR_SIZE;
	windowInstance->borderWidth = SOY_DEFAULT_BORDER_SIZE;
	for(; i < S_MAX_WINDOWS; i++) {
		if(s_instances[i] == NULL) {
			s_instances[i] = windowInstance;
			windowInstance->instanceIndex = i;
			wcnt++;
			ret = TRUE;
			return ret;
		} else if(wcnt >= S_MAX_WINDOWS) {
			SLOG("Error: No free window slots!\n");
			return ret;
		}
	}

	ret = TRUE;
	s_windowCount = wcnt;
	return ret;
}

static flag s_remove_instance_from_index(int index) {
	flag ret = UNDEF;
	if(index > 0 && index < S_MAX_WINDOWS) {
		s_instances[index]->instanceIndex = -1;
		s_instances[index] = NULL;
		return ret;
	} else {
		ret = TRUE;
	}
	return ret;
}

flag soy_window_win32_change_title(windowWin32* window, const char* text) {
	return SetWindowText(window->hwnd, text)?0:-1;
}

flag soy_window_win32_switch_fullscreen(windowWin32* window) {
	LONG NewHwndStyle = 0;
	if(!window->fullscreen) {
		window->fullscreen = TRUE;
		GetWindowPlacement(window->hwnd, &global_wpc);
		if(HWNDStyle == 0) {
			HWNDStyle = GetWindowLong(window->hwnd, GWL_STYLE);
		}
		if(HWNDStyleEx == 0) {
			HWNDStyleEx = GetWindowLong(window->hwnd, GWL_EXSTYLE);
		}
		NewHwndStyle = HWNDStyleEx;
		NewHwndStyle &= ~WS_EX_WINDOWEDGE;

		SetWindowLong(window->hwnd, GWL_STYLE, NewHwndStyle | WS_POPUP);
		SetWindowLong(window->hwnd, GWL_EXSTYLE, NewHwndStyle | WS_EX_TOPMOST);
		ShowWindow(window->hwnd, SW_SHOWMAXIMIZED);
	} else {
		window->fullscreen = FALSE;
		SetWindowLong(window->hwnd, GWL_STYLE, HWNDStyle);
		SetWindowLong(window->hwnd, GWL_EXSTYLE, HWNDStyleEx);
		ShowWindow(window->hwnd, SW_SHOWNORMAL);
		SetWindowPlacement(window->hwnd, &global_wpc);
	}
	return TRUE;
}

flag soy_window_win32_create(
		windowWin32* window,
		int width,
		int height,
		int posX,
		int posY,
		const char* title
		) {
	HINSTANCE hInstance = GetModuleHandle(NULL);
	const char* winClassName = title;
	HWND hwnd;
	WNDCLASSEX wc;
	COLORREF colRef;
	flag result = UNDEF;
	s_add_instance_to_index(window);
	soy_window_win32_load_cursors();
	window->cursorStyle = CURSOR_ARROW;
	window->fullscreen = FALSE;
	wc.lpszClassName = winClassName;
	wc.lpfnWndProc = winProc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = HCUR_ARROW;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszMenuName = NULL;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	window->x = posX;
	window->y = posY;
	window->width = width;
	window->height = height;
	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return FALSE;
	}
	hwnd = CreateWindowEx(
		WS_EX_LAYERED,
		wc.lpszClassName,
		title,
		WS_POPUP,
		posX,
		posY,
		width,
		height,
		NULL,
		NULL,
		hInstance,
		NULL
		);
	if(hwnd == NULL) {
		MessageBox(NULL, "Failed to create Window!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return FALSE;
	}
#ifdef SOY_WINDOW_TRANSPARENT
	colRef = 0x00;
	if(!SetLayeredWindowAttributes(hwnd, colRef, 127, LWA_COLORKEY)) {
		SLOG1("Error setting window attribute: %ld\n", GetLastError());
	}
#else 
	colRef = 0x00;
	if(!SetLayeredWindowAttributes(hwnd, colRef, 255, LWA_ALPHA)) {
		SLOG1("Error setting window attribute: %ld\n", GetLastError());
	}
#endif
	result = TRUE;
	window->hwnd = hwnd;
	ShowWindow(hwnd, SW_SHOW);
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);
	window->deviceContext = GetDC(hwnd);
	if(!window->deviceContext) { SLOG("Problem getting device context\n"); }
	UpdateWindow(hwnd);
	result = TRUE;
	return result;
}

flag soy_window_win32_create_gl(
		windowWin32* window,
		int width,
		int height,
		int posX,
		int posY,
		const char* title
		) {
	HINSTANCE hInstance = GetModuleHandle(NULL);
	const char* winClassName = title;
	HWND hwnd;
	WNDCLASSEX wc;
	DEVMODE dmScSet;
	flag result = UNDEF;
	MSG msg;
	s_add_instance_to_index(window);
	soy_window_win32_load_cursors();
	window->cursorStyle = CURSOR_ARROW;
	window->fullscreen = FALSE;
	wc.lpszClassName = winClassName;
	wc.lpfnWndProc = winProc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = HCUR_ARROW;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszMenuName = NULL;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	window->x = posX;
	window->y = posY;
	window->width = width;
	window->height = height;

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return FALSE;
	}

	hwnd = CreateWindowA(
		wc.lpszClassName,
		title,
		WS_OVERLAPPEDWINDOW,
		0,
		0,
		0,
		0,
		NULL,
		NULL,
		hInstance,
		NULL
		);
	if(hwnd == NULL) {
		MessageBox(NULL, "Failed to create Window!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return FALSE;
	}
	ShowWindow(hwnd, SW_HIDE);
	result = soy_gl_init_extensions(hwnd);
	if(!result) {
		SLOG("Problem initializing OpenGL extensions...\n");
		return FALSE;
	}
	DestroyWindow(hwnd);
	hwnd = NULL;

	if (FULL_SCREEN) {
		memset(&dmScSet, 0, sizeof(dmScSet));
		dmScSet.dmSize = sizeof(dmScSet);
		dmScSet.dmPelsWidth = (unsigned long)width;
		dmScSet.dmPelsHeight = (unsigned long)height;
		dmScSet.dmBitsPerPel = 32;
		dmScSet.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		ChangeDisplaySettings(&dmScSet, CDS_FULLSCREEN);
		posX = 0;
		posY = 0;
	} else {
		ChangeDisplaySettings(NULL, 0);
		if(S_CENTERED) {
			posX = (GetSystemMetrics(SM_CXSCREEN)-width)/2;
			posY = (GetSystemMetrics(SM_CYSCREEN)-height)/2;
		}
	}
	GetMessage(&msg, NULL, 0, 0);
	hwnd = CreateWindowA(
		wc.lpszClassName,
		"sus",
		WS_OVERLAPPEDWINDOW,
		posX,
		posY,
		width,
		height,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	if (hwnd == NULL) {
		SLOG("Problem creating win32 window...\n");
		return FALSE;
	}

	window->hwnd = hwnd;
	result = soy_gl_init_opengl(window, 0);
	if (!result) {
		SLOG("Problem initializing OpenGL...\n");
		return FALSE;
	}
	ShowWindow(hwnd, SW_SHOW);
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);
	UpdateWindow(hwnd);
	window->deviceContext = GetDC(hwnd);
	if(!window->deviceContext) { SLOG("Problem getting device context\n"); }
	result = TRUE;
	return result;
}

flag soy_window_win32_poll_events(windowWin32* window) {

	GetWindowRect(window->hwnd, &window->windowRect);
	
	window->x = window->windowRect.left;
	window->y = window->windowRect.top;
	window->width = window->windowRect.right - window->windowRect.left;
	window->height = window->windowRect.bottom - window->windowRect.top;
	if(PeekMessage(&(window->msg), window->hwnd, 0, 0, PM_REMOVE)) {
		TranslateMessage(&(window->msg));
		DispatchMessage(&(window->msg));
	}
	return TRUE;
}

flag soy_window_win32_gl_quit(windowWin32* window) {
	if(window->renderContext) {
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(window->renderContext);
		window->renderContext = 0;
	}
	if(window->deviceContext) {
		ReleaseDC(window->hwnd, window->deviceContext);
		window->deviceContext = 0;
	}
	s_remove_instance_from_index(window->instanceIndex);
	if(window->hwnd == NULL) {
		return FALSE;
	}
	DestroyWindow(window->hwnd);
	return TRUE;
}

flag soy_window_win32_close(windowWin32* window) {
	SendMessage(window->hwnd, WM_CLOSE, 0, 0);
	return TRUE;
}

flag soy_window_win32_quit() {
	SLOG("Quitting\n");
	PostQuitMessage(0);
	return TRUE;
}

flag soy_window_win32_blit_pixels(windowWin32* win, void* memory, int memWidth, int memHeight) {
	BITMAPINFO info;
	info.bmiHeader.biSize = sizeof(info.bmiHeader);
	info.bmiHeader.biWidth = memWidth;
	info.bmiHeader.biHeight = -memHeight;
	info.bmiHeader.biPlanes = 1;
	info.bmiHeader.biBitCount = 32;
	info.bmiHeader.biCompression = BI_RGB;
	if(StretchDIBits(win->deviceContext, 0, 0, win->width, win->height,
				0, 0, memWidth, memHeight, memory, &info, DIB_RGB_COLORS, SRCCOPY) != 0) {
		return TRUE; 
	}
	SLOG1("Error in StretchDIBits %d\n", (int)GetLastError());
	return ERROR;
}

LRESULT CALLBACK winProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	int i = 0;
	int x;
	int y;
	RECT winRect;
	int BORDERWIDTH = SOY_DEFAULT_BORDER_SIZE;
	int TITLEBARWIDTH = SOY_DEFAULT_TITLEBAR_SIZE;
	for(i = 0; i < S_MAX_WINDOWS; i++) {
		switch(msg){
			case(WM_CLOSE): {
				if(s_instances[i] && s_instances[i]->hwnd == hwnd) {
					if(s_instances[i]->deviceContext) {
						ReleaseDC(s_instances[i]->hwnd, s_instances[i]->deviceContext);
						s_instances[i]->deviceContext = 0;
					}
					s_remove_instance_from_index(s_instances[i]->instanceIndex);
					if(s_instances[i]->hwnd == NULL) {
						return FALSE;
					}
					DestroyWindow(hwnd);
					return 0;
				
				}
				break;
			}
			case(WM_DESTROY): {
				if(s_instances[i] && s_instances[i]->hwnd == hwnd) {
				}
				break;
			}
			case(WM_KEYDOWN): {
				if(s_instances[i] && s_instances[i]->hwnd == hwnd) {
		
				}
				break;
			}


			case(WM_ERASEBKGND): {
				if(s_instances[i] && s_instances[i]->hwnd == hwnd) {
					return 1;
				}

				break;
			}


			case(WM_MOUSEMOVE): {
				if(s_instances[i] && s_instances[i]->hwnd == hwnd) {
				}
				break;
			}
			case(WM_PAINT): {
				if(s_instances[i] && s_instances[i]->hwnd == hwnd) {
				}
				break;
			}

			case(WM_NCHITTEST): {
				if(s_instances[i] && s_instances[i]->hwnd == hwnd) {
					GetWindowRect(hwnd, &winRect);
					x = GET_X_LPARAM(lParam)-winRect.left;
					y = GET_Y_LPARAM(lParam)-winRect.top;
	                BORDERWIDTH = s_instances[i]->borderWidth;
					TITLEBARWIDTH = s_instances[i]->titlebarHeight;
					if(x >= BORDERWIDTH && x <= winRect.right - winRect.left - BORDERWIDTH &&
						y >= BORDERWIDTH && y <= TITLEBARWIDTH) {
        	            s_instances[i]->cursorStyle = CURSOR_MOVE;
						return HTCAPTION;
					} else if (x > winRect.right - winRect.left - BORDERWIDTH*2 &&
						y > winRect.bottom - winRect.top - BORDERWIDTH*2) {
	                    s_instances[i]->cursorStyle = CURSOR_SIZEDLR;
						return HTBOTTOMRIGHT;
					} else if (x > winRect.right - winRect.left - BORDERWIDTH) {
	                    s_instances[i]->cursorStyle = CURSOR_SIZEH;
						return HTRIGHT;
					} else if (y > winRect.bottom - winRect.top - BORDERWIDTH) {
	                    s_instances[i]->cursorStyle = CURSOR_SIZEV;
						return HTBOTTOM;
					} else {
            	        s_instances[i]->cursorStyle = CURSOR_ARROW;
        	         return HTCLIENT;
					}
					break;
				}
				break;
			}

			case(WM_SIZING): {
				if(s_instances[i] && s_instances[i]->hwnd == hwnd) {
					GetWindowRect(hwnd, &(s_instances[i]->windowRect));
					s_instances[i]->x = s_instances[i]->windowRect.left;
					s_instances[i]->y = s_instances[i]->windowRect.top;
					s_instances[i]->width = s_instances[i]->windowRect.right - s_instances[i]->windowRect.left;
					s_instances[i]->height = s_instances[i]->windowRect.bottom - s_instances[i]->windowRect.top;
				}
				break;
			}

			case(WM_MOVING): {
				if(s_instances[i] && s_instances[i]->hwnd == hwnd) {
					GetWindowRect(hwnd, &(s_instances[i]->windowRect));
					s_instances[i]->x = s_instances[i]->windowRect.left;
					s_instances[i]->y = s_instances[i]->windowRect.top;
					s_instances[i]->width = s_instances[i]->windowRect.right - s_instances[i]->windowRect.left;
					s_instances[i]->height = s_instances[i]->windowRect.bottom - s_instances[i]->windowRect.top;
					SLOG("Moving canvas\n");
				}
				break;
			}

			case(WM_SETCURSOR): {
				if(s_instances[i] && s_instances[i]->hwnd == hwnd) {
					switch(s_instances[i]->cursorStyle) {
						case(CURSOR_ARROW): { SetCursor((HCUR_ARROW)); break; }
						case(CURSOR_WAIT): { SetCursor(HCUR_WAIT); break; }
						case(CURSOR_MOVE): { SetCursor(HCUR_MOVE); break; }
						case(CURSOR_SIZEH): { SetCursor(HCUR_RESIZEH); break; }
						case(CURSOR_SIZEV): { SetCursor(HCUR_RESIZEV); break; }
						case(CURSOR_SIZEDLR): { SetCursor(HCUR_RESIZEDL); break; }
						case(CURSOR_SIZEDRL): { SetCursor(HCUR_RESIZEDR); break; }
						case(CURSOR_HAND): { SetCursor(HCUR_HAND); break; }
						case(CURSOR_TEXT): { SetCursor(HCUR_TEXT); break; }
						case(CURSOR_CROSS): { SetCursor(HCUR_CROSS); break; }
						default: SetCursor(HCUR_ARROW); break;
					}	
					return TRUE;
				}
				break;
			}
			case(MM_MCINOTIFY): {
				if(s_instances[i] && s_instances[i]->hwnd == hwnd) {
					s_instances[i]->mmMsg.state = SM_NOTIFY;
					switch(wParam) {
						case(MCI_NOTIFY_ABORTED): { s_instances[i]->mmMsg.reason = SM_ABORTED;
													  SLOG("Media playback aborted\n"); break; }
						case(MCI_NOTIFY_FAILURE): { s_instances[i]->mmMsg.reason = SM_FAILURE;
													  SLOG("Media playback failure\n"); break; }
						case(MCI_NOTIFY_SUCCESSFUL): { s_instances[i]->mmMsg.reason = SM_SUCCESS;
													  SLOG("Media playback succesfully finished\n"); break; }
						case(MCI_NOTIFY_SUPERSEDED): { s_instances[i]->mmMsg.reason = SM_SUPERSEDED;
												  SLOG("Media playback superseded\n"); break; }
						default: break;
					}
					s_instances[i]->mmMsg.senderID = lParam;
				}
				break;
			}

			default: {
				return DefWindowProc(hwnd, msg, wParam, lParam);
			}
		}
	}
	return 0;
}

unsigned int soy_window_win32_desktop_res_x() {
	return GetSystemMetrics(SM_CXSCREEN);
}

unsigned int soy_window_win32_desktop_res_y() {
	return GetSystemMetrics(SM_CYSCREEN);
}

#endif
