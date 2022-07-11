#pragma once
#include <atlimage.h>

#define MAX_LABEL 10000
#define MAX_CONTOUR 5000

typedef struct _ContourPoints {
	int num;
	int x[MAX_CONTOUR];
	int y[MAX_CONTOUR];
} ContourPoints;

void Binarization(CImage* image, CImage* obj, int w, int h, int th = -1);
int BinarizationIterative(CImage*, int, int);

int Labeling(CImage*, CImage*, int, int);

void ContourTracing(CImage*, CImage*, int, int);

void MorphologyErosion(CImage*, CImage*, int, int);
void MorphologyDilation(CImage*, CImage*, int, int);
void MorphologyOpening(CImage* image, CImage* obj, int w, int h);
void MorphologyClosing(CImage* image, CImage* obj, int w, int h);

void MorphologyGrayErosion(CImage*, CImage*, int, int);
void MorphologyGrayDilation(CImage*, CImage*, int, int);
void MorphologyGrayOpening(CImage*, CImage*, int, int);
void MorphologyGrayClosing(CImage*, CImage*, int, int);