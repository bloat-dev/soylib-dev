#ifndef SOYSTRING_H
#define SOYSTRING_H

#include "soycore.h"

#define SOY_MAX_CSTRING 1024

unsigned int soy_cstring_lentok(const char* str, char token, int tokIndex, unsigned int max) {
	unsigned int index = 0;
	while(index < max && (str[index] != '\0' && str[index] != token && tokIndex >= 0)) {
		if(str[index] == token) {
			tokIndex--;
		}
		index++;
	}
	if(index == max) {
		index = 0;
	}
	return index;
}

unsigned int soy_cstring_len(const char* str, unsigned int max) {
	unsigned int index = 0;
	while(index < max && str[index] != '\0') {
		index++;
	}
	if(index == max) {
		index = 0;
	}
	return index;
}

flag soy_cstring_copy(const char* orig, char* buffer, unsigned int startIndex, unsigned int bufSize) {	
	unsigned int i;
	unsigned int lenOrig;
	lenOrig = soy_cstring_len(orig, SOY_MAX_CSTRING);
	if(orig == NULL || buffer == NULL || startIndex >= lenOrig) {
		return ERROR;
	}
	i = startIndex;
	while(orig[i] != '\0' && i-startIndex < bufSize-1) {
		buffer[i-startIndex] = orig[i];
		i++;
	}
	buffer[i-startIndex] = '\0';
	return TRUE;
}

flag soy_cstring_reverse(const char* orig, char* buffer, unsigned int bufSize) {
	unsigned int i;
	unsigned int origLen;
	origLen = soy_cstring_len(orig, SOY_MAX_CSTRING);
	if(origLen+1 != bufSize) {
		SLOG("Buffer size must be same as the lenght of original string + 1");
		return ERROR;
	}
	i = 0;
	while(i < origLen) {
		buffer[i] = orig[origLen-i-1];
		i++;
	}
	buffer[i] = '\0';
	return TRUE;
}

flag soy_cstring_trim(const char* orig, char* buffer, char token, int index, unsigned int bufSize) {
	unsigned int startIndex;
	startIndex = soy_cstring_lentok(orig, token, index, SOY_MAX_CSTRING);
	if(startIndex > bufSize) {
		startIndex = bufSize;
	}
	soy_cstring_copy(orig, buffer, 0, startIndex+1);
	return TRUE;
}

flag soy_cstring_token(const char* orig, char* buffer, char token, int index, unsigned int bufSize) {
	unsigned int startIndex;
	startIndex = soy_cstring_lentok(orig, token, index, SOY_MAX_CSTRING);
	soy_cstring_copy(orig, buffer, startIndex, bufSize);
	return TRUE;
}

flag soy_cstring_cat(char* dest, const char* src) {
	int lendest= 0;
	int lensrc = 0;
	int index = 0;
	char* newString = NULL;
	lendest = soy_cstring_len(dest, SOY_MAX_CSTRING);
	lensrc = soy_cstring_len(src, SOY_MAX_CSTRING);
	newString =  soy_alloc(newString, sizeof(char)*(lendest+lensrc+1));
	for(; index < lendest; index++) {
		newString[index] = dest[index];
	}
	for(index = 0;index < lensrc; index++) {
		newString[index+lendest] = src[index];
	}
	soy_free(dest);
	dest = newString;
	return TRUE;
}

long s_decimal_divs[] = {
		1,
		10,
		100,
		1000,
		10000,
		100000,
		1000000,
		10000000,
		100000000,
		1000000000,
	};

#define SOY_INT_MAX_PERCISION 9
unsigned int soy_int_decimal_size(long n) {
	unsigned int numSize = 0;
	int iter = SOY_INT_MAX_PERCISION;
	int i = 0;
	if(n < 0) {
		n*=-1;
	}
	while(i < iter) {
		if(n/s_decimal_divs[i] < 10) {
			numSize = i+1;
			return numSize;
		}
		i++;
	}
	return numSize;
}

flag soy_int_to_cstring(long un, char* buffer, unsigned int bufferSize) {
	unsigned int numSize;
	unsigned int i;
	unsigned int iter = SOY_INT_MAX_PERCISION;
	flag sig = FALSE;
	int a;
	unsigned long n = (unsigned long) un;
	if(un < 0) {
		n = (unsigned long) (un*-1);
		sig = TRUE;
	}
	numSize = soy_int_decimal_size(n);
	if(bufferSize < numSize + (sig ? 1 : 0)) {
		SLOG("Buffer size smaller then needed\n");
		return ERROR;
	}
	i = 0;
	if(numSize > iter) { numSize = iter; }
	a = sig ? 0 : 1;
	for(i = 0; i < numSize; i++) {
		if(sig) {
			buffer[0] = '-';
		}
		switch(n/s_decimal_divs[i] - 10*(n/s_decimal_divs[i+1])) {
			case(0): buffer[numSize-i-a] = '0'; break;
			case(1): buffer[numSize-i-a] = '1'; break;
			case(2): buffer[numSize-i-a] = '2'; break;
			case(3): buffer[numSize-i-a] = '3'; break;
			case(4): buffer[numSize-i-a] = '4'; break;
			case(5): buffer[numSize-i-a] = '5'; break;
			case(6): buffer[numSize-i-a] = '6'; break;
			case(7): buffer[numSize-i-a] = '7'; break;
			case(8): buffer[numSize-i-a] = '8'; break;
			case(9): buffer[numSize-i-a] = '9'; break;
			default: buffer[numSize-i-a] = 'E'; break;
		}
	}
	buffer[i+(sig ? 1 : 0)] = '\0';
	return TRUE;
}

flag soy_float_to_cstring(double un, char* buffer, int percision, unsigned int bufferSize) {
	long wholeNum;
	long realNum;
	int nsW;
	double usn;
	char whole[SOY_INT_MAX_PERCISION];
	char real[SOY_INT_MAX_PERCISION];
	wholeNum = (long)un;
	usn = un - (double)wholeNum;
	usn -= 1.0;
	if(usn < 0.0) {
		usn*= -1.0;
	}
	realNum = (long) ((usn)*(double)(pow(10, percision)));
	nsW = soy_int_decimal_size(wholeNum);

	soy_int_to_cstring(wholeNum, whole, SOY_INT_MAX_PERCISION);
	soy_int_to_cstring(realNum, real, SOY_INT_MAX_PERCISION);

	soy_cstring_copy(whole, buffer, 0, bufferSize);
	soy_cstring_copy(".", buffer+nsW+1, 0, bufferSize);
	soy_cstring_copy(real, buffer+nsW+2 , 1, bufferSize);
	return TRUE;
}


#endif
