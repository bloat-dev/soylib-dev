#ifndef SOY_BMP_H
#define SOY_BMP_H

#include <stdlib.h>
#include <stdio.h>
#include "soycore.h"

typedef enum enum_BMPState {
  INITIALIZED,
  UNDEFINED
} BMPState;

typedef enum enum_bmpType {
  BMP_MONO,
  BMP_256,
  BMP_16,
  BMP_24
} bmpType;

typedef struct tag_soyBitmap {
  unsigned long imageSize;
  unsigned long rawSize;
  int headerSize;
  int compressionMethod;
  int width;
  int height;
  int padding;
  int pixelFormat;
  unsigned char* bytes;
  const char* name;
  BMPState state;
} soyBitmap;

flag soy_bitmap_free_pixels(soyBitmap* bitmap) {
  SLOG1("Deleting memory of bitmap - %s...\n", bitmap->name);
  soy_free(bitmap->bytes);
  bitmap->bytes = NULL;
  return TRUE;
}

flag soy_bitmap_free(soyBitmap* bitmap) {
  soy_bitmap_free_pixels(bitmap);
  SLOG1("%s Bitmap freed\n", bitmap->name);
  return TRUE;
}


flag soy_bitmap_init(soyBitmap* bitmap) {
  bitmap->state = UNDEFINED;
  bitmap->bytes = NULL;
  return TRUE;
}

soyBitmap* soy_bitmap_new() {
  soyBitmap* newBmp;
  newBmp = calloc(1, sizeof(soyBitmap));
  if(newBmp != NULL) {
    newBmp->state = UNDEFINED;
    newBmp->bytes = NULL;
  }
  return newBmp;
}

/*
 * Bitmap Import
 *
 * Parameters:
 *
 * 1: soyBitmap* bmp        -> pointer to a soyBitmap struct. Should be uninitialized when passed to this function
 * 2: const char* filepath  -> path to the bmp file. Must include .bmp extension
 * 3: const char bmpFormat  -> array of chars representing the desired output format e.g.: {'r', 'g', 'b', 'a' }
 *                             *Null terminator character and everything after it will be ignored
 */

#define RED 2
#define GREEN 1
#define BLUE 0
#define ALPHA 3
#define NULLCOL 4

flag soy_bitmap_import(soyBitmap* bmp, const char* filepath, const char bmpFormat[]) {
  FILE* file = NULL;
  unsigned char* tempBuffer = NULL;
  unsigned long int fileSize = 0;
  unsigned long int resultSize = 0;
  unsigned int parsedInt = 0;
  unsigned short parsedShort = 0;
  unsigned int index = 0;
  unsigned int indexH = 0;
  unsigned int indexC = 0;
  unsigned int width = 0;
  unsigned int height = 0;
  unsigned short pixelFormat = 0;
  unsigned short pixelFormatInternal = 0;
  unsigned int headerSize = 0;
  unsigned int dataStartIndex = 0;
  unsigned int rawSize = 0;
  int padding = 0;
  int padInternal = 0;
  unsigned int fc1, fc2, fc3, fc4;
  unsigned short sc1, sc2;
  char compressionMethod = 0;
  char* pixelBufer = NULL;
  char* pixel = NULL;
  unsigned char tempChar;
  soyPixel tempPixel;
  int pixelIndex = 0;
  int bmpFormatStrLen = 0;

  if(bmp == NULL) {
    SLOG("soyBitmap was NULL\n");
    return ERROR;
  }

  if(bmp->state == INITIALIZED) {
    SLOG("Freeing previous array\n");
    soy_free(bmp->bytes);
  } else {
    bmp->state = INITIALIZED;
  }

  bmp->name = filepath;

  while(bmpFormat[bmpFormatStrLen] != '\0') {
    if(bmpFormatStrLen > 4) {
      SLOG("Invalid format\n");
        return ERROR;
      }
    bmpFormatStrLen++;
  }

  pixelBufer = soy_alloc(pixelBufer, sizeof(char)* bmpFormatStrLen);
  pixel = soy_alloc(pixel, sizeof(char)* bmpFormatStrLen);
  if(!pixelBufer || !pixel || bmpFormatStrLen <= 0) {
    SLOG("Unsupported format size\n");
    soy_free(pixel);
    soy_free(pixelBufer);
    return ERROR;
  }

  for(; pixelIndex < bmpFormatStrLen; pixelIndex++) {
    pixel[pixelIndex] = 0;
    switch(bmpFormat[pixelIndex]) {
      case('r'): {
                   pixelBufer[pixelIndex] = RED;
                   break;
                 }
      case('g'): {
                   pixelBufer[pixelIndex] = GREEN;
                   break;
                 }
      case('b'): {
                   pixelBufer[pixelIndex] = BLUE;
                   break;
                 }
      case('a'): {
                   pixelBufer[pixelIndex] = ALPHA;
                   break;
                 }
      case('n'): {
                   pixelBufer[pixelIndex] = NULLCOL;
                   break;
                 }
      default:   {
                   break;
                 }
    }
  }

  file = fopen(filepath, "rb");
  if(!file) {
    SLOG1("Could not open file: %s \n", filepath);
    soy_free(pixelBufer);
    soy_free(pixel);
    return ERROR;
  }
  fseek(file, 0, SEEK_END);
  fileSize = ftell(file);
  rewind(file);
  SLOG1("Filesize: %ld bytes \n", fileSize);
  tempBuffer = soy_alloc(tempBuffer, fileSize*sizeof(unsigned char));
  if(!tempBuffer) {
    SLOG1("Could not allocate enough memory: %ld bytes \n", fileSize);
    soy_free(tempBuffer);
    soy_free(pixelBufer);
    soy_free(pixel);

    return ERROR;
  }

  resultSize = fread(tempBuffer, 1, fileSize, file);
  if(resultSize != fileSize) {
    SLOG2("Could not read file: %s, error at %ld bytes \n", filepath, resultSize);
    soy_free(tempBuffer);
    soy_free(pixelBufer);
    soy_free(pixel);
    return ERROR;
  }
  fclose(file);

  if(tempBuffer[0] == 'B' && tempBuffer[1] == 'M') {
    /*
    SLOG("Found BMP file descriptor... \n");
    */
  }

  fc1 = tempBuffer[2];
  fc2 = tempBuffer[3] << 8;
  fc3 = tempBuffer[4] << 16;
  fc4 = tempBuffer[5] << 24;
  parsedInt = fc1 | fc2 | fc3 | fc4;
  /*
  SLOG2("Parsed size: %d / Actual size: %ld \n", parsedInt, fileSize);
  */
  if(parsedInt != fileSize) {
    SLOG("Failed to parse filesize, aborting... \n");
    soy_free(tempBuffer);
    soy_free(pixelBufer);
    soy_free(pixel);

    return ERROR;
  }

  fc1 = tempBuffer[10];
  fc2 = tempBuffer[11] << 8;
  fc3 = tempBuffer[12] << 16;
  fc4 = tempBuffer[13] << 24;
  parsedInt = fc1 | fc2 | fc3 | fc4;
  dataStartIndex = parsedInt;
  /*
  SLOG1("Starting index of image data: %d \n", parsedInt);
  */

  fc1 = tempBuffer[14];
  fc2 = tempBuffer[15] << 8;
  fc3 = tempBuffer[16] << 16;
  fc4 = tempBuffer[17] << 24;
  parsedInt = fc1 | fc2 | fc3 | fc4;
  headerSize = parsedInt;
  /*
  SLOG1("Size of header: %d \n", headerSize);
  */
  fc1 = tempBuffer[18];
  fc2 = tempBuffer[19] << 8;
  fc3 = tempBuffer[20] << 16;
  fc4 = tempBuffer[21] << 24;
  parsedInt = fc1 | fc2 | fc3 | fc4;

  width = parsedInt;
  /*
  SLOG1("Width: %d\n", width);
  */
  fc1 = tempBuffer[22];
  fc2 = tempBuffer[23] << 8;
  fc3 = tempBuffer[24] << 16;
  fc4 = tempBuffer[25] << 24;
  parsedInt = fc1 | fc2 | fc3 | fc4;

  height = parsedInt;
  /*
  SLOG1("Height: %d\n", height);
  */
  sc1 = tempBuffer[28];
  sc2 = tempBuffer[29] << 8;
  parsedShort = sc1 | sc2;
  pixelFormat = parsedShort;
  /*
  SLOG1("Pixel format: %d \n", pixelFormat);
  */
  compressionMethod = tempBuffer[30];
  /*
  SLOG1("Compression method: %d \n", compressionMethod);
  */
  fc1 = tempBuffer[34];
  fc2 = tempBuffer[35] << 8;
  fc3 = tempBuffer[36] << 16;
  fc4 = tempBuffer[37] << 24;
  parsedInt = fc1 | fc2 | fc3 | fc4;

  rawSize = parsedInt;
  SLOG1("Raw image size: %d \n", rawSize);

  padding = 0;
  while((width*3+padding)%4 != 0) {
    padding++;
  }
  /*
  SLOG1("Padding: %d \n", padding);
  SLOG1("Format: %s \n", bmpFormat);
  SLOG1("Format size: %d \n", bmpFormatStrLen);
  */
  index = 0;

  switch(pixelFormat) {
    case(24): {
                pixelFormatInternal = 3;
                break;
              }
    case(8): {
                pixelFormatInternal = 0;
                SLOG1("Format: %d not currently supported\n", pixelFormat);
                break;
              }
    case(4): {
                pixelFormatInternal = 0;
                SLOG1("Format: %d not currently supported\n", pixelFormat);
                break;
              }
    case(1): {
                pixelFormatInternal = 0;
                SLOG1("Format: %d not currently supported\n", pixelFormat);
                break;
              }

  }
  if(!pixelFormatInternal) {
    soy_free(tempBuffer);
    soy_free(pixelBufer);
    soy_free(pixel);
    return ERROR;
  }

  bmp->headerSize = headerSize;
  bmp->rawSize = rawSize;
  bmp->imageSize = width*height*bmpFormatStrLen;
  bmp->bytes = soy_alloc(bmp->bytes, bmp->imageSize*sizeof(unsigned char));
  bmp->width = width;
  bmp->height = height;
  bmp->padding = padding;
  bmp->pixelFormat = pixelFormat;
  bmp->compressionMethod = compressionMethod;

  padInternal = 0;
  indexC = 0;
  for(index = 0; index < width*height; index++) {    
    for(pixelIndex = 0; pixelIndex < 4; pixelIndex++) {
      if(pixelBufer[pixelIndex] < ALPHA) {
        bmp->bytes[(bmp->imageSize-4)-index*4+pixelIndex]
        = tempBuffer[dataStartIndex+index*pixelFormatInternal+pixelBufer[pixelIndex]+padInternal];
      } else if(pixelBufer[pixelIndex] == NULLCOL) {
       bmp->bytes[(bmp->imageSize-4)-index*4+pixelIndex] = 255;
      } else if (pixelBufer[pixelIndex] == ALPHA) {
        if(tempBuffer[dataStartIndex+index*pixelFormatInternal+pixelBufer[pixelIndex]+padInternal] == 255) {
          bmp->bytes[(bmp->imageSize-4)-index*4+pixelIndex] = 255;
        } else {
          bmp->bytes[(bmp->imageSize-4)-index*4+pixelIndex] = 0;
        }
      }
    }
    if((index+1)%(width) == 0) {
      padInternal+= padding;
    }
  }

  
  /* flip the image */
  pixelIndex = 0;  
  for(indexC = 0; indexC < height; indexC++) {
    for(indexH = 0; indexH < width/2; indexH++) {
      tempPixel = ((soyPixel*)bmp->bytes)[(indexC+1)*width - indexH-1];
      ((soyPixel*)bmp->bytes)[(indexC+1)*width-indexH-1] = ((soyPixel*)bmp->bytes)[indexH+(indexC)*width];
      ((soyPixel*)bmp->bytes)[indexH+(indexC)*width] = tempPixel;
    }
  }
  
  /* fix bgr to rgb */
  for(index = 0; index < width*height; index++) {
    tempChar = ((soyPixel*)bmp->bytes)[index].r;
    ((soyPixel*)bmp->bytes)[index].r = ((soyPixel*)bmp->bytes)[index].b;
    ((soyPixel*)bmp->bytes)[index].b = tempChar;
  }
  /*
  SLOG("Bitmap copied to internal format \n");
  SLOG("Import success! \n\n");
  */
  soy_free(pixelBufer);
  soy_free(pixel);
  soy_free(tempBuffer);
  SLOG1("Loaded bitmap: %s\n", filepath);
  return TRUE;
}

flag soy_bitmap_create(soyBitmap* bmp, const char* filepath) {
  flag ret = UNDEF;
  soy_bitmap_init(bmp);
  ret = soy_bitmap_import(bmp, filepath, "rgba");
  return ret;
}

#endif
