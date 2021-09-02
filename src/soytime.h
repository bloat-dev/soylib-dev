#ifndef SOY_TIME_H

#define SOY_TIME_H
#include "soycore.h"

typedef struct tag_soyTimer {
	LARGE_INTEGER startingTime;
	LARGE_INTEGER endingTime;
	LARGE_INTEGER elapsedMicroseconds;
	LARGE_INTEGER frequency;
} soyTimer;

flag soy_time_init(soyTimer* ts) {
	ts->startingTime.HighPart = 0;
	ts->startingTime.LowPart = 0;
	ts->startingTime.QuadPart = 0;
	ts->endingTime.HighPart = 0;
	ts->endingTime.LowPart = 0;
	ts->endingTime.QuadPart = 0;
	ts->elapsedMicroseconds.HighPart = 0;
	ts->elapsedMicroseconds.LowPart = 0;
	ts->elapsedMicroseconds.QuadPart = 0;
	ts->frequency.HighPart = 0;
	ts->frequency.LowPart = 0;
	ts->frequency.QuadPart = 0;
	return TRUE;
}

void soy_time_start(soyTimer* ts) {
	QueryPerformanceFrequency(&(ts->frequency));
	QueryPerformanceCounter(&(ts->startingTime));
}

double soy_time_delta(soyTimer* ts) {
	return (double)(ts->elapsedMicroseconds.QuadPart)*0.001;
}

void soy_time_end(soyTimer* ts) {
	QueryPerformanceCounter(&(ts->endingTime));
	ts->elapsedMicroseconds.QuadPart = ts->endingTime.QuadPart - ts->startingTime.QuadPart;
	ts->elapsedMicroseconds.QuadPart *= 1000000;
	ts->elapsedMicroseconds.QuadPart /= ts->frequency.QuadPart;
}
#endif
