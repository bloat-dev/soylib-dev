#ifndef SOYCORE_H
#define SOYCORE_H

/*  Windows does not define the S_ISREG and S_ISDIR macros in stat.h, so we do.
 *  We have to define _CRT_INTERNAL_NONSTDC_NAMES 1 before #including sys/stat.h
 *  in order for Microsoft's stat.h to define names like S_IFMT, S_IFREG, and S_IFDIR,
 *  rather than just defining  _S_IFMT, _S_IFREG, and _S_IFDIR as it normally does.
 */

#define _CRT_INTERNAL_NONSTDC_NAMES 1
#include <sys/stat.h>
#include <sys/types.h>
#if !defined(S_ISREG) && defined(S_IFMT) && defined(S_IFREG)
#define S_ISREG(m) (((m) & S_IFMT) == S_IFREG)
#endif
#if !defined(S_ISDIR) && defined(S_IFMT) && defined(S_IFDIR)
#define S_ISDIR(m) (((m) & S_IFMT) == S_IFDIR)
#endif

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#include <stdio.h>
#include <windows.h>
#include <windowsx.h>
#include <winsock.h>

#include <gl/gl.h>

#include <direct.h>
#include <shlwapi.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <immintrin.h>
#include <mmsystem.h>

#define SLOGERR(x) if(!x) { printf("[soyerr] ERROR at: %s, line: %d\n", __FILE__, __LINE__ ); }
#define SLOGINF(x) printf("[soyinf] INFO at: %s, line: %d\n", __FILE__, __LINE__ )

#define VERBOSE_PREFIX

#ifdef VERBOSE_PREFIX
#define SLOGPREFIX printf("[%s][%d] > ", __FILE__, __LINE__)
#else
#define SLOGPREFIX while(0)


#endif

#define DEBUG_OUTPUT

#ifdef DEBUG_OUTPUT
#define ENDL printf("\n")
#define SLOG(x) SLOGPREFIX; printf(x)
#define SLOG1(x, a1) SLOGPREFIX; printf(x, a1)
#define SLOG2(x, a1, a2) SLOGPREFIX; printf(x, a1, a2)
#define SLOG3(x, a1, a2, a3) SLOGPREFIX; printf(x, a1, a2, a3)
#define SLOG4(x, a1, a2, a3, a4) SLOGPREFIX; printf(x, a1, a2, a3, a4)
#define SLOG5(x, a1, a2, a3, a4, a5) SLOGPREFIX; printf(x, a1, a2, a3, a4, a5)
#define SLOG6(x, a1, a2, a3, a4, a5, a6) SLOGPREFIX; printf(x, a1, a2, a3, a4, a5, a6)
#define SLOG7(x, a1, a2, a3, a4, a5, a6, a7) SLOGPREFIX; printf(x, a1, a2, a3, a4, a5, a6, a7)
#define SLOG8(x, a1, a2, a3, a4, a5, a6, a7, a8) SLOGPREFIX; printf(x, a1, a2, a3, a4, a5, a6, a7, a8)
#define SLOG9(x, a1, a2, a3, a4, a5, a6, a7, a8, a9) SLOGPREFIX; printf(x, a1, a2, a3, a4, a5, a6, a7, a8, a9)
#define SLOG10(x, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10) SLOGPREFIX; printf(x, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10)
#else
#define ENDL while(0) {}
#define SLOG(x) while(0) {}
#define SLOG1(x, a1) while(0) {}
#define SLOG2(x, a1, a2) while(0) {}
#define SLOG3(x, a1, a2, a3) while(0) {}
#define SLOG4(x, a1, a2, a3, a4) while(0) {}
#define SLOG5(x, a1, a2, a3, a4, a5) while(0) {}
#define SLOG6(x, a1, a2, a3, a4, a5, a6) while(0) {}
#define SLOG7(x, a1, a2, a3, a4, a5, a6, a7) while(0) {}
#define SLOG8(x, a1, a2, a3, a4, a5, a6, a7, a8) while(0) {}
#define SLOG9(x, a1, a2, a3, a4, a5, a6, a7, a8, a9) while(0) {}
#define SLOG10(x, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10) while(0) {}
#endif

#define SPRINT(x) printf(x)
#define PCHECK(x) printf("%s\n", (x)?"done":"error")

#define ASSERT(x) if(!(x)) \
		printf("ABORTING PROGRAM - FATAL ERROR at: %s, line: %d, time: %s\n", __FILE__, __LINE__, __TIME__); \
		exit(-1);

#define flag int
#define UNDEF 0
#define FALSE 0
#define TRUE 1
#define S_MAX_DIR 256
#define S_MAX_STRING 512
#define S_MAX_LSTRING 1024
#define S_MAX_THREADS 64

typedef __int8 int8;
typedef __int16 int16;
typedef __int32 int32;
typedef __int64 int64;

typedef UINT8 uint8;
typedef UINT16 uint16;
typedef UINT32 uint32;
typedef UINT64 uint64;


#define MAX_FLT FLT_MAX
#define MAX_DBL DBL_MAX
#define MAX_LDBL LDBL_MAX

#define MAX_S8 127
#define MAX_U8 255
#define MAX_S16 32767
#define MAX_U16 65535
#define MAX_S32 2147483647
#define MAX_U32 4294967295
#define MAX_S64 9223372036854775807
#define MAX_U64 18446744073709551615

#define SOY_PI 3.141592653
#define SOY_2PI 6.283185307
#define SOY_E 2.71828

#define SOY_DEFAULT_TITLEBAR_SIZE 18
#define SOY_DEFAULT_BORDER_SIZE 3

uint64 Kilobytes(int size){
	return 1024*(uint64)size;
}
uint64 Megabytes(int size){
	return 1024*Kilobytes(size);
}
uint64 Gigabytes(int size){
	return 1024*Megabytes(size);
}
uint64 Terabytes(int size){
	return 1024*Gigabytes(size);
}

void* soy_alloc(void* ptr, size_t size) {
	void* res;
	int err;
	res = VirtualAlloc(ptr, size, MEM_COMMIT, PAGE_READWRITE);
	if (res == NULL) {
		err = GetLastError();
		SLOG2("Problem allocating memory at %p | %d\n", ptr, err);
	}
	return res;
}

flag soy_free(void* ptr) {
	flag res = UNDEF;
	int err;
	if (VirtualFree(ptr, 0, MEM_RELEASE) == 0) {
		err = GetLastError();
		SLOG2("Error freeing memory %p | %d\n", ptr, err);
		res = ERROR;
	}
	return res;
}

typedef struct tag_soyPixelF {
	float r;
	float g;
	float b;
	float a;
} soyPixelF;

typedef struct tag_soyPixel {
	unsigned char r; 
	unsigned char g;
	unsigned char b;
	unsigned char a;
} soyPixel; /* 32 */

soyPixel soy_pixel(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
	soyPixel p;
	p.r = r;
	p.g = g;
	p.b = b;
	p.a = a;
	return p;
}

flag soy_swap_float(float* a, float* b) {
	float c = *a;
	*a = *b;
	*b = c;
	return TRUE;
}

flag soy_swap_double(double* a, double* b) {
	double c = *a;
	*a = *b;
	*b = c;
	return TRUE;
}

flag soy_swap_int(int* a, int* b) {
	int c = *a;
	*a = *b;
	*b = c;
	return TRUE;
}

flag soy_swap_char(char* a, char* b) {
	char c = *a;
	*a = *b;
	*b = c;
	return TRUE;
}

typedef union uni_simdPixel {
	soyPixel raw[4];
	__m128i packed;
} simdPixel;

#define SIMDPIXEL_SIZE 4

typedef struct tag_i2D {
	int x;
	int y;
} i2D;

typedef struct tag_i3D {
	int x;
	int y;
	int z;
} i3D;

typedef struct tag_i4D {
	int x;
	int y;
	int z;
	int w;
} i4D;

typedef struct tag_f2D {
	float x;
	float y;
} f2D;

typedef struct tag_f3D {
	float x;
	float y;
	float z;
} f3D;

typedef struct tag_f4D {
	float x;
	float y;
	float z;
	float w;
} f4D;

#define SOY_INT_PERCISION 8

int high_percision_int_divide(int a, int b) {
  return (a<<SOY_INT_PERCISION)/b;
}
typedef enum enum_notifyState {
	SM_NONE,
	SM_NOTIFY
} notifyState;

typedef enum enum_notifyReason {
	SM_ABORTED,
	SM_FAILURE,
	SM_SUCCESS,
	SM_SUPERSEDED
} notifyReason;

typedef struct tag_mediaMsg {
	notifyState state;
	notifyReason reason;
	int senderID;
} mediaMsg;

typedef flag (*pfUserFuncDelta) (double delta);
typedef flag (*pfUserFunc) ();
typedef flag (*pfResizeFunc) (int width, int height);

double soy_lerp(double start, double end, double t) {
	return (1.0 - t) * start + t * end;
}

#endif
