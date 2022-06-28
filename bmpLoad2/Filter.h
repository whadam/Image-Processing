#pragma once
#include <atlimage.h>

#define MAX_CORNER 500

typedef struct _LineParam {
	double rho;
	double ang;
} LineParam;

typedef struct _CornerPoints {
	int num;
	int x[MAX_CORNER];
	int y[MAX_CORNER];
} CornerPoints;

//void FilterMean(CImage*);
//void FilterWeightedMean(CImage*);
//void FilterGaussian(CImage*, double);
//
//void FilterLaplacian(CImage*);
//void FilterUnsharpMask(CImage*);
//
//void FilterNoiseGaussian(CImage*, int);
//void FilterNoiseSaltNPepper(CImage*, int);
//double FilterGaussianRand(double, double);
//
//void FilterMedean(CImage*);
//
//void FilterDiffusion(CImage*, float, float, int);
//
//void EdgeRoberts(CImage*);
//void EdgePrewitt(CImage*);
//void EdgeSobel(CImage*);

LineParam HoughLine(CImage*);

void DrawLine(CImage*, CImage*, LineParam, BYTE);
void DrawLine(CImage*, CImage*, int, int, int, int, BYTE);

CornerPoints HarrisCorner(CImage*, double);

template<typename T> 
inline int limit(T pixel)
{
	if (pixel > 255) {
		return (255 << 16) + (255 << 8) + 255;
	}
	else if (pixel < 0) return 0;
	else {
		return (pixel<<16) + (pixel<<8) + pixel;
	}
}
//template<typename T> 
//inline void swap(T& lha, T& rha)
//{
//	T tmp = lha;
//	lha = rha;
//	rha = tmp;
//}