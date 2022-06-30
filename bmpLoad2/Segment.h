#pragma once
#include <atlimage.h>

#define MAX_LABEL 10000
#define MAX_CONTOUR 5000

typedef struct _ContourPoints {
	int num;
	int x[MAX_CONTOUR];
	int y[MAX_CONTOUR];
} ContourPoints;

void Binarization(CImage*, CImage*, int);
int BinarizationIterative(CImage*);

int Labeling(CImage*, CImage*);

ContourPoints ContourTracing(CImage*, CImage*);

void MorphologyErosion(CImage*, CImage*);
void MorphologyDilation(CImage*, CImage*);

void MorphologyGrayErosion(CImage*, CImage*);
void MorphologyGrayDilation(CImage*, CImage*);