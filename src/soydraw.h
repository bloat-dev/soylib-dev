#ifndef SOY_DRAW_H
#define SOY_DRAW_H

#include "soycore.h"
#include "soyfont.h"
#include "soystring.h"
#include "soy3D.h"
#include <time.h>
#include <string.h>

typedef flag (*pfDrawParamFunc) (int param);

typedef struct tag_drawParams {
  soyPixel* memory;
  int memWidth;
  int memHeight;
  soyPixel colour;
  soyFont font;
  pfDrawParamFunc drawCb;

} drawParams;

int soy_draw_rgba_to_int(soyPixel colour) {
  int result = 0;
  /* 0000 0000 0000 0000 */
  result += colour.r << 12;
  result += colour.g << 8;
  result += colour.b << 4;
  result += colour.a;
  return result;
}

flag soy_draw_compare_colour(soyPixel col1, unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
  return (col1.r == r && col1.g == g && col1.b == b && col1.a == a);
}

flag soy_draw_set_colour(drawParams* params, unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
  params->colour.r = b;
  params->colour.g = g;
  params->colour.b = r;
  params->colour.a = a;
  return TRUE;
}

flag soy_draw_clear(drawParams* params) {
  int index = 0;
  if(params->memory == NULL) { return ERROR; }
  for(index = 0; index < params->memWidth*params->memHeight; index++) {
    params->memory[index] = params->colour;
  }
  return TRUE;
}

flag soy_draw_pixel(drawParams* params, int x, int y) {
  if(params->memory == NULL) { return ERROR; }
  if(x >= 0 && y >= 0 && x < params->memWidth && y < params->memHeight) {
    params->memory[x+y*params->memWidth] = params->colour;
  }
  return TRUE;
}

flag soy_draw_pixelcol(drawParams* params, int x, int y, soyPixel pixel) {
  if(params->memory == NULL) { return ERROR; }
  if(x >= 0 && y >= 0 && x < params->memWidth && y < params->memHeight) {
    params->memory[x+y*params->memWidth] = pixel;
  }
  return TRUE;
}
flag soy_draw_bitmap32(drawParams* params,
      int xPos, int yPos,
      soyPixel* src,
      int bmpWidth, int bmpHeight,
      int sizeWidth, int sizeHeight) {
	int x = 0;
	int y = 0;
    int drawRectX;
    int drawRectY;
    int destWidth, destHeight;
	double lines = 0.0;
	double sampleIndex = 0.0;
	double deltaHeight = (double)bmpHeight/(double)sizeHeight;
	double linesToFill = 0.0;
	double leftover = 0.0;
	int globalIndex = 0;
    unsigned int imageSize = bmpWidth*bmpHeight;
	soyPixel* dest;
    drawRectX = 0;
    drawRectY = 0;
    destWidth = params->memWidth;
    destHeight = params->memHeight;
    dest = params->memory;

    if(sizeWidth > destWidth) {
        drawRectX = sizeWidth - destWidth;
    }

    if(sizeHeight > destHeight) {
        drawRectY = sizeHeight - destHeight;
    }
    if(dest == NULL || src == NULL) { return ERROR; }

    if(x <= 0-sizeWidth || x > destWidth || y < 0-sizeHeight || y >= destHeight) { return FALSE; }
    for(y = 0; y < sizeHeight-1-drawRectY; y++) {
		linesToFill = deltaHeight; /* amount of rows required for correct scaling */
		for(x = 0; x < sizeWidth-drawRectX; x++) {
			sampleIndex = (((double)x*bmpWidth/sizeWidth)+lines);
			if((unsigned int)sampleIndex < imageSize  && src[(unsigned int)sampleIndex].r > 0 &&
               (unsigned int)sampleIndex < imageSize  && src[(unsigned int)sampleIndex].r > 0 &&
               (unsigned int)sampleIndex < imageSize  && src[(unsigned int)sampleIndex].r > 0) {
                soy_draw_pixelcol(params, x+xPos, y+yPos, src[(unsigned int)sampleIndex]);
			} else {
			}
			globalIndex++;
		}

		/* rows can't always be cleanly divided
		 * so an accumulator is used
		 * to figure out when to add a new line */

		while(leftover > 1.0) {
			lines-=bmpWidth;
			leftover -= 1.0;
		}
		while(linesToFill > 0.0) {
			lines+=bmpWidth;
			linesToFill -= 1.0;
		}
		leftover += linesToFill*(-1.0);
	}
	return TRUE;
}


flag soy_draw_line(drawParams* params, int x1, int y1, int x2, int y2) {
  int dx = abs(x2-x1);
  int sx = x1<x2 ? 1 : -1;
  int dy = -abs(y2-y1);
  int sy = y1<y2 ? 1 : -1;
  int err = dx+dy;
  int e2;
  if(params->memory == NULL) { return ERROR; }
  while(TRUE) {
    soy_draw_pixel(params, x1, y1);
    if(x1 == x2 && y1 == y2) {
      break;
    }
    e2 = 2*err;
    if(e2 > dy) {
      err+=dy;
      x1+=sx;
    }
    if(e2 <= dx) {
      err += dx;
      y1 += sy;
    }
  }
  return TRUE;
}

flag soy_draw_line_dds(drawParams* params, float x1, float y1, float x2, float y2) {
  float dx, dy, x, y, step;
  int i;
  if(params->memory == NULL) { return ERROR; }
  dx = (x2 - x1);
  dy = (y2 - y1);
  step = fabs(dx) >= fabs(dy) ? fabs(dx) : fabs(dy);
  dx /= step;
  dy /= step;
  x = x1;
  y = y1;
  i = 0;
  while(i <= abs((int)step)) {
    soy_draw_pixel(params, (int)x, (int)y);
    x += dx;
    y += dy;
    i += 1;
  }
  return TRUE;
}

flag soy_draw_ellipse(drawParams* params, int xm, int ym, int a, int b) {
  int x = -a;
  int y = 0;
  long int e2 = (long int)b*b;
  long int err = x*(2*e2+x)+e2;
  if(params->memory == NULL) { return ERROR; }
  do {
    soy_draw_pixel(params, xm-x, ym+y);
    soy_draw_pixel(params, xm+x, ym+y);
    soy_draw_pixel(params, xm+x, ym-y);
    soy_draw_pixel(params, xm-x, ym-y);
    e2 = 2*err;
    if(e2 >= (x*2+1)*(long int)b*b) {
      err+= (++x*2+1)*(long int)b*b;
    }
    if(e2 <= (y*2+1)*(long int)a*a) {
      err += (++y*2+1)*(long int)a*a;
    }
  } while (x <= 0);

  while(y++ < b) {
    soy_draw_pixel(params, xm, ym+y);
    soy_draw_pixel(params, xm, ym-y);
  }
  return TRUE;
}

flag soy_draw_rect(drawParams* params, int x1, int y1, int x2, int y2) {
  int temp;
  if(params->memory == NULL) { return ERROR; }
  if((x1 < params->memWidth*2 && x1 > -params->memWidth) ||
      (y1 < params->memHeight*2 && y1 > -params->memHeight)) {
    if(y1 > y2) {
     temp = y1;
     y1 = y2;
     y2 = temp;
    }
   if(x1 > x2) {
     temp = x1;
     x1 = x2;
     x2 = temp;
   }
   soy_draw_line(params, x1, y1, x2, y1);
   soy_draw_line(params, x1, y2, x2, y2);
   soy_draw_line(params, x1, y1, x1, y2);
   soy_draw_line(params, x2, y1, x2, y2);
  }
  return TRUE;
}

flag soy_draw_rect_fill(drawParams* params, int x1, int y1, int x2, int y2) {
  int i, j;
  if(params->memory == NULL) { return ERROR; }
  for(i = y1; i < y2; i++) {
    for(j = x1; j < x2; j++) {
      soy_draw_pixel(params, j, i);
    }
  }
  return TRUE;
}

flag soy_draw_text(drawParams* params, int x, int y, const char* text, int tlen, soyFont* font) {
  int strLen = 0;
  int gridSize = 0;
  unsigned char charIndex = 0;
  unsigned int bitmapSize;
  int index;
  int subX;
  int subY;
  unsigned int bmpWidth;
  unsigned int canvasIndex;
  unsigned int bitmapIndex;
  int step;
  int scaledX;
  int scaledY;
  int bitmapX;
  int bitmapY;
  float bmpSubX;
  float bmpSubY;
  int newLineCount;
  int canvX;
  float canXDiff;
  int posIndex;
  int nextKerning;
  soyPixel bitmapPixel;
  char curChar = 0;
  char prevChar = 0;
  int clipIndexX = 0;
  /*
  int clipIndexY = 0;
  */
  if(params->memory == NULL) { return ERROR; }
  bmpWidth = font->fontBitmapHandle->width;
  bitmapSize = font->fontBitmapHandle->width*font->fontBitmapHandle->height;
  gridSize = font->grid;
  step = bmpWidth/gridSize;
  if(x+step*font->scale <= 0 || x+step*font->scale >= params->memWidth ||
     y+step*font->scale <= 0 || y+step*font->scale >= params->memHeight) {
    return FALSE;
  }
  newLineCount = 0;
  canvX = 0;
  scaledY = (int)((float)step*font->scale);
  scaledX = (int)((float)step*font->scale);
  canvasIndex = 0;
  if(tlen < 0) {
    strLen = soy_cstring_len(text, 1024);
  } else {
    if(tlen < 1024) {
      strLen = tlen;
    } else {
      strLen = 1024-1;
    }
  }
  posIndex = x+y*params->memWidth;
  canXDiff = 0;
  for(index = 0; index < strLen; index++) {
    clipIndexX = (x+(int)(index*step*font->scale)+canXDiff);
    if(clipIndexX > params->memWidth || clipIndexX < 0) {
      return FALSE;
    }
    prevChar = curChar;
    curChar = text[index];
    if(curChar == '\n') {
      index++;
      canvX = 0;
      canXDiff = 0;
      curChar = text[index];
      newLineCount+=step*font->scale;
    }
    charIndex = (unsigned char) curChar;
    bitmapX = (charIndex%step)*step;
    bitmapY = (charIndex/step)*step;
    nextKerning = font->charInfo[(unsigned char)prevChar].kerning;
    if(canvX != 0) {
      canXDiff-=((float)(step-nextKerning)*font->scale)+font->globalKerning*font->scale;
    }
    for(subY = 0; subY < scaledY; subY++) {
      for(subX = 0; subX < scaledX; subX++) {
        canvasIndex =
          (int)((float)subX+canXDiff+canvX*step*font->scale)+(subY+newLineCount)*params->memWidth;
        bmpSubX = (float)subX/font->scale;
        bmpSubY = (float)subY/font->scale;
        bitmapIndex = bitmapX+(int)bmpSubX + (bitmapY+(int)bmpSubY) * bmpWidth;
        if(bitmapIndex > 0 && bitmapIndex < bitmapSize) {
          bitmapPixel = ((soyPixel*)font->fontBitmapHandle->bytes)[bitmapIndex];
          if(bitmapPixel.r == 255 && bitmapPixel.g == 255 && bitmapPixel.b == 255) {
            if(canvasIndex+posIndex > 0 &&
                canvasIndex+posIndex < (unsigned int) params->memWidth*params->memHeight) {
              soy_draw_pixel(
                  params,
                  canvasIndex%params->memWidth+x-4*font->scale,
                  canvasIndex/params->memWidth+y-4*font->scale);
            }
          }
        }
      }
    }
    canvX++;
  }
  return TRUE;
}

flag soy_draw_triangle_textured(drawParams* params, float x1, float y1, float u1, float v1, float w1,
                                                    float x2, float y2, float u2, float v2, float w2,
                                                    float x3, float y3, float u3, float v3, float w3,
                                                    soyBitmap* bitmap) {
  float dx1, dy1, dx2, dy2, px1, py1, px2, py2, step1, step2;
  int istep1, istep2;
  int i;
  soyPixel col;
  if(params->memory == NULL) { return ERROR; }
  if(y1 > y2) {
    soy_swap_float(&y1, &y2);
    soy_swap_float(&x1, &x2);
  }
  if(y1 > y3){
    soy_swap_float(&y1, &y3);
    soy_swap_float(&x1, &x3);
  }
  if(y2 > y3) {
    soy_swap_float(&y2, &y3);
    soy_swap_float(&x2, &x3);
  }
  col = params->colour;
  soy_draw_set_colour(params, 255, 255, 255,255);
  soy_draw_text(params, x1, y1, "top x1", 6, &params->font);
  soy_draw_text(params, x2, y2, "mid x2", 6, &params->font);
  soy_draw_text(params, x3, y3, "bot x3", 6, &params->font);
  params->colour = col;
  dx1 = (x2 - x1);
  dy1 = (y2 - y1);
  dx2 = (x3 - x1);
  dy2 = (y3 - y1);
  step1 = fabs(dx1) >= fabs(dy1) ? fabs(dx1) : fabs(dy1);
  step2 = fabs(dx2) >= fabs(dy2) ? fabs(dx2) : fabs(dy2);
  dx1 /= step1;
  dy1 /= step1;
  dx2 /= step2;
  dy2 /= step2;
  px1 = x1;
  py1 = y1;
  px2 = x1;
  py2 = y1;
  i = 0;
  istep1 = abs((int)step1);
  istep2 = abs((int)step2);
  i = 0;
  while(i <= istep1) {
    soy_draw_set_colour(params, 255,0,0,0);
    soy_draw_pixel(params, (int)px1, (int)py1);
    while(py2 < py1) {
      soy_draw_pixel(params, (int)px2, (int)py2);
      px2 += dx2;
      py2 += dy2;
    }

    /*
    params->drawCb(1000);
    */
    px1 += dx1;
    py1 += dy1;
    i++;
  }
  params->colour = col;
  i = 0;
  while(i <= abs((int)step2)) {
    soy_draw_pixel(params, (int)px2, (int)py2);
    i++;
  }
  return TRUE;
}
#endif
