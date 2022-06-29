#include "stdafx.h"
#include "Segment.h"
#include "Enhancement.h"

void Binarization(CImage* image, CImage* obj, int th)
{
	register int i, j;

	int w = image->GetWidth();
	int h = image->GetHeight();

	obj->Create(w,h,24);

	int pixel;
	for (j = 0; j < h; j++) {
		for (i = 0; i < w; i++) {
			pixel = (image->GetPixel(j,i)>>16) > th ? 255:0;
			obj->SetPixelRGB(j,i,pixel,pixel,pixel);
		}
	}
}

int BinarizationIterative(CImage* image)
{
	register int i, j;

	int w = image->GetWidth();
	int h = image->GetHeight();

	float hist[256] = {0,};

	Histogram(image, hist);

	int T, Told;

	float sum = 0.f;
	for (i = 0; i < 256; i++) {
		sum += (i*hist[i]);
	}

	T = (int)sum;

	float a1, b1, u1, a2, b2, u2;
	do {
		Told = T;

		a1 = b1 = 0;
		for (i = 0; i < Told; i++) {
			a1 += (i*hist[i]);
			b1 += hist[i];
		}
		u1 = a1/b1;

		a2 = b2 = 0;
		for (i = Told + 1; i < 256; i++) {
			a2 += (i*hist[i]);
			b2 += hist[i];
		}
		u2 = a2/b2;

		if (b1 == 0) b1 = 1.f;
		if (b2 == 0) b2 = 1.f;

		T = (int) ((u1+u2)/2);
	} while (T != Told);

	return T;
}

int Labeling(CImage* image)
{
	register int i, j;
	
	int w = image->GetWidth();
	int h = image->GetHeight();

	// 임시로 레이블을 저장할 메모리 공간과 등가 테이블 생성
	int** map = new int*[h];
	for (i = 0; i < h; i++) {
		map[i] = new int[w];
		memset(map[i],0,sizeof(int)*w);
	}
	int eq_tbl[MAX_LABEL][2] = {{0,},};

	// 첫 번째 스캔 - 초기 레이블 지정 및 등가 테이블 생성
	int label = 0, max1, min1, min_eq, max_eq;

	for (j = 1; j < h; j++) {
		for (i = 1; i < w; i++) {
			if (image->GetPixel(j,i) != 0) {
				// 바로 위 픽셀과 왼쪽 픽셀 모두에 레이블이 존재하는 경우
			}
		}
	}
}