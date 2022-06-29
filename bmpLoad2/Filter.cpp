#include "stdafx.h"
#include "Filter.h"
#include "Fourier.h"
#include <math.h>
#include <algorithm>

const double PI = acos(-1.0);

void Mean(CImage* img)
{

}

void WeightedMean(CImage* img)
{

}

void Guassian(CImage* img, double sigma)
{

}

void Laplacian(CImage* img)
{

}

void UnsharpMask(CImage* img)
{

}

void NoiseGaussian(CImage* img, int amount)
{

}

void NoiseSaltNPepper(CImage* img, int amount)
{

}

double GaussianRand(double mean, double std)
{
	return 0.0;
}

void Medean(CImage* img)
{

}

void Diffusion(CImage* img, float lambda, float k, int iter)
{

}

void EdgeRoberts(CImage* img)
{

}

void EdgePrewitt(CImage* img, CImage* obj)
{
	register int i, j;
	int w = img->GetWidth();
	int h = img->GetHeight();

	obj->Create(w,h,24);

	int h1, h2;
	double hval;
	for (j = 1; j < h-1; j++) {
		for (i = 1; i < w-1; i++) {
			h1 = (img->GetPixel(j+1,i-1)>>16) + (img->GetPixel(j+1,i)>>16) + (img->GetPixel(j+1,i+1)>>16)
				- (img->GetPixel(j-1,i-1)>>16) - (img->GetPixel(j-1,i)>>16) - (img->GetPixel(j-1,i+1)>>16);
			h2 = (img->GetPixel(j-1,i+1)>>16) + (img->GetPixel(j,i+1)>>16) + (img->GetPixel(j+1,i+1)>>16)
				- (img->GetPixel(j-1,i-1)>>16) - (img->GetPixel(j,i-1)>>16) - (img->GetPixel(j+1,i-1)>>16);

			hval = sqrt((double)h1*h1 + h2*h2);

			obj->SetPixel(j,i,limit((int)hval));
		}
	}
}

void EdgeSobel(CImage* img)
{

}

//LineParam HoughLine(CImage* img)
//{
//	register int i, j;
//
//	int w = img->GetWidth();
//	int h = img->GetHeight();
//
//	int num_rho = (int)(sqrt((double)w*w + h*h)*2);
//	int num_ang = 360;
//
//	// 0~PI 각도에 해당하는 sin, cos 함수의 값을 룩업테이블에 저장
//	double* tsin = new double[num_ang];
//	double* tcos = new double[num_ang];
//
//	for (i = 0; i < num_rho; i++) {
//		tsin[i] = (double)sin(i*PI/num_ang);
//		tcos[i] = (double)cos(i*PI/num_ang);
//	}
//
//	// 축적 배열(accumulate array) 생성
//	int** arr = new int*[num_rho];
//	for (i = 0; i < num_rho; i++) {
//		arr[i] = new int[num_ang];
//		memset(arr[i], 0, sizeof(int)*num_ang);
//	}
//
//	int m,n;
//	for (j = 0; j < h; j++) {
//		for (i = 0; i < w; i++) {
//			if ((img->GetPixel(j,i)>>16) > 128) {
//				for (n = 0; n < num_ang; n++) {
//					m = (int) floor(i*tsin[n] + j*tcos[n] + 0.5);
//					m += (num_rho/2);
//
//					arr[m][n]++;
//				}
//			}
//		}
//	}
//
//	// 축적 배열에서 최대값 찾기
//	LineParam line;
//	line.rho = line.ang = 0;
//
//	int arr_max = 0;
//	for (m = 0; m < num_rho; m++) {
//		for (n = 0; n < num_ang; n++) {
//			if (arr[m][n] > arr_max) {
//				arr_max = arr[m][n];
//				line.rho = m - (num_rho/2);
//				line.ang = n*180.0/num_ang;
//			}
//		}
//	}
//
//	// 동적 할당 메모리 해제
//	delete [] tsin, tcos;
//	for (i = 0; i < num_rho; i++) {
//		delete [] arr[i];
//	}
//	delete arr;
//
//	return line;
//}

void DrawLine(CImage* img, CImage* obj, LineParam line, BYTE c)
{
	register int x, y;

	int w = img->GetWidth();
	int h = img->GetHeight();

	// 수직선인 경우
	if (line.ang == 90) {
		x = (int)(line.rho + 0.5);

		for (y = 0; y < h; y++) {
			obj->SetPixel(y,x,limit(c));	// byte를 int로 형 변환하고 비트 시프트 해야하는지
		}

		return;
	}

	// (rho, ang) 파라미터를 이용하여 직선의 시작 좌표와 끝 좌표를 계산
	int x1 = 0;
	int y1 = (int) floor(line.rho / cos(line.ang*PI/180) + 0.5);
	int x2 = w - 1;
	int y2 = (int) floor((line.rho - x2*sin(line.ang*PI/180)) / cos(line.ang*PI/180) + 0.5);

	DrawLine(img, obj, x1, y1, x2, y2, c);
}

void DrawLine(CImage* img, CImage* obj, int x1, int y1, int x2, int y2, BYTE c)
{
	register int x, y;
	double m;

	int w = img->GetWidth();
	int h = img->GetHeight();

	// 수직선인 경우
	if (x1 == x2) {
		if (y1 > y2) {
			swap(y1, y2);
		}

		for (y = y1; y <= y2; y++) {
			obj->SetPixel(y,x1,limit(c));
		}

		return;
	}

	// (x1, y1)에서 (x2, y2)까지 직선 그리기
	m = (double) (y2-y1)/(x2-x1);

	if ((m > -1) && (m < 1)) {
		if (x1 > x2) {
			swap(x1, x2);
			swap(y1, y2);
		}

		for (x = x1; x <= x2; x++) {
			y = (int)floor(m*(x-x1) + y1 + 0.5);
			if (y > 0 && y < h) {
				obj->SetPixel(y,x,limit(c));
			}
		}
	}
	else {
		if (y1 > y2) {
			swap(x1, x2);
			swap(y1, y2);
		}

		for (y = y1; y <= y2; y++) {
			x = (int)floor((y-y1) / m + x1 + 0.5);
			if (y >= 0 && y < h) {
				obj->SetPixel(y,x,limit(c));
			}
		}
	}
}

//CornerPoints HarrisCorner(CImage* img, double th)
//{
//	
//}