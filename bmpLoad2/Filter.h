#pragma once

#define MAX_CORNER 5000

typedef struct _LineParam {
	double rho;
	double ang;
} LineParam;

typedef struct _CornerPoints {
	int num;
	int x[MAX_CORNER];
	int y[MAX_CORNER];
} CornerPoints;

void fnMean(CImage*, CImage*, int, int);
void fnGaussian(CImage*, CImage*, int, int);

void fnUnsharpMask(CImage*, CImage*, int, int);
void fnLaplacian(CImage*, CImage*, int, int);

void fnNoiseGaussian(CImage*, CImage*, int, int);
void fnNoiseSaltNPepper(CImage*, CImage*, int, int);
double fnGaussianRand(double, double);

void fnMedean(CImage*, CImage*, int, int);

void fnDiffusion(CImage*, CImage*, int, int);

void fnEdgeRoberts(CImage*, CImage*, int, int);
void fnEdgePrewitt(CImage*, CImage*, int, int);
void fnEdgeSobel(CImage*, CImage*, int, int);

LineParam fnHoughLine(CImage*, int, int);

void fnDrawLine(CImage*, LineParam, BYTE, int, int);
void fnDrawLine(CImage*, int, int, int, int, BYTE, int , int);

void fnHarrisCorner(CImage*, CImage*, int, int);
_CornerPoints fnCornerPoints(CImage*, int, int, double);


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