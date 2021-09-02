#ifndef SOY_FONT_H
#define SOY_FONT_H

#include "soycore.h"
#include "soybmp.h"

typedef struct tag_soyCharInfo {
  char kerning;
  char midline;
} soyCharInfo;

typedef struct tag_soyFont {
	soyBitmap* fontBitmapHandle;
    soyCharInfo charInfo[256];
    float globalKerning;
    float scale;
    int globalVertical;
    int grid;
} soyFont;

flag soy_font_set_bitmap(soyFont* font, soyBitmap* fontAtlas, int gridSize) {
  unsigned int x;
  unsigned int y;
  int kerningIndex;
  int midlineIndex;
  int charIndex;
  flag kCol;
  soyPixel tempPixel;

  kCol = FALSE;
  kerningIndex = 0;
  charIndex = 0;
  midlineIndex = 0;
  font->fontBitmapHandle = fontAtlas;
  font->grid = gridSize;
  for(y = 0; y < fontAtlas->height; y += gridSize) {
    for(x = 0; x < fontAtlas->width; x += gridSize) {
      kerningIndex = 0;
      midlineIndex = 0;
      tempPixel = ((soyPixel*)fontAtlas->bytes)[x+kerningIndex+y*fontAtlas->width];
      kCol = FALSE;
      while(!kCol && kerningIndex < gridSize) {
        tempPixel = ((soyPixel*)fontAtlas->bytes)[x+kerningIndex+y*fontAtlas->width];
        if(tempPixel.r == 255 && tempPixel.g == 255 && tempPixel.b == 0) {
          kCol = TRUE;
        }
        kerningIndex++;
      }
      kCol = FALSE;
      tempPixel = ((soyPixel*)fontAtlas->bytes)[x+(y+midlineIndex)*fontAtlas->width];
      while(!kCol && kerningIndex < gridSize) {
        if(tempPixel.r == 255 && tempPixel.g == 255 && tempPixel.b == 0) {         
          kCol = TRUE;
        }
        tempPixel = ((soyPixel*)fontAtlas->bytes)[x+(y+midlineIndex)*fontAtlas->width];
        midlineIndex++;
      }
      midlineIndex-=gridSize/2;
      if(charIndex < 255) {
        font->charInfo[charIndex].kerning = kerningIndex+font->globalKerning;
        font->charInfo[charIndex].midline = midlineIndex+font->globalVertical;
      }
      charIndex++;
    }
  }
  return TRUE;
}

flag soy_font_set_scale(soyFont* font, float scale) {
  font->scale = scale;
  return TRUE;
}

flag soy_font_set_vertical(soyFont* font, int value) {
  font->globalVertical = value;
  return TRUE;
}

flag soy_font_set_kerning(soyFont* font, float value) {
  font->globalKerning = value;
  return TRUE;
}

flag soy_font_set_atlas(soyFont* font, soyBitmap* fontAtlas, int gridSize) {
  if(font == NULL || fontAtlas == NULL) {
    return ERROR;
  }
  font->scale = 1;
  font->globalKerning = 1.0f;
  font->globalVertical = 0.0f;
  soy_font_set_bitmap(font, fontAtlas, gridSize);
  return TRUE;
}

#endif
