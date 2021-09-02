#ifndef SOY_CANVAS_H
#define SOY_CANVAS_H

#include "soycore.h"
#define s_pixelSize 4

typedef struct tag_soyCanvas {
	flag initialized;
	void* memory;
	int x;
	int y;
	unsigned int width;
	unsigned int height;
	int pixelSize;
} soyCanvas;

flag soy_canvas_free(soyCanvas* canvas) {
	if(canvas) {
		if(canvas->memory) {
			soy_free(canvas->memory);
		}
	}
	return TRUE;
}

int soy_canvas_size(soyCanvas* canvas) {
	return (canvas->width*canvas->height);
}

soyPixel soy_canvas_sample(soyCanvas* canvas, int x, int y) {
	return ((soyPixel*)canvas->memory)[x+y*canvas->width];
}

flag soy_canvas_set(soyCanvas* canvas, int x, int y, soyPixel pixel) {
	if(x >= 0 && x < (int)canvas->width && y >= 0 && y < (int)canvas->height) {
		((soyPixel*)canvas->memory)[x+y*canvas->width] = pixel;
	}
	return TRUE;
}

flag soy_canvas_draw_pixel(soyCanvas* canvas,
		int x, int y,
		float r, float g, float b, float a) {

	soyPixel pix;
	pix.r = (unsigned char)(b*255);
	pix.g = (unsigned char)(g*255);
	pix.b = (unsigned char)(r*255);
	pix.a = (unsigned char)(a*255);

	if(x > (int)canvas->width-1 || x < 0 || y > (int)canvas->height-1 || y < 0) {
		return ERROR;
	}
	((soyPixel*)canvas->memory)[x+y*canvas->width] = pix;
	return TRUE;
}

flag soy_canvas_create(soyCanvas* canvas, int width, int height, int resolution) {
	void* newMem = NULL;
	SLOG2("Creating %d x %d canvas... ", width / resolution, height / resolution);
	if(canvas->memory && canvas->initialized) {
		soy_canvas_free(canvas);
	}
	canvas->pixelSize = resolution;
	canvas->x = 0;
	canvas->y = 0;
	canvas->width = width/resolution;
	canvas->height = height/resolution;
	newMem = soy_alloc(newMem,(canvas->width*canvas->height)*sizeof(soyPixel));
	if(newMem == NULL) {
		SLOG("Failed to allocate canvas memory...\n");
	}
	canvas->memory = newMem;
	canvas->initialized = TRUE;
	PCHECK(TRUE);
	return TRUE;
}

flag soy_canvas_resize(soyCanvas* canvas, int width, int height, int resolution) {
	SLOG("Resizing canvas...\n");
	soy_canvas_create(canvas, width, height, resolution);
	SLOG("Canvas resized\n");
	return TRUE;
}



#endif
