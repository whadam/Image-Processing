#include "stdafx.h"
#include "Segment.h"
#include "Enhancement.h"
#include "Filter.h"
#include "Binarize.h"
#include "Image.h"

void Binarization(CImage* image, CImage* obj, int w, int h, int th)
{
	Binarize bi;
	register int i, j;
	int pixel;
	obj->Create(w,h,24);

	if (th == -1)
	{
		if (bi.DoModal() == IDOK)
		{
			th = bi.m_edit_threshold;

			for (j = 0; j < h; j++)
			{
				for (i = 0; i < w; i++)
				{
					pixel = (int)(image->GetPixel(j,i)>>16) > th ? 255:0;
					obj->SetPixelRGB(j,i,pixel,pixel,pixel);
				}
			}
		}
	}
	else
	{
		for (j = 0; j < h; j++)
		{
			for (i = 0; i < w; i++)
			{
				pixel = (int)(image->GetPixel(j,i)>>16) > th ? 255:0;
				obj->SetPixelRGB(j,i,pixel, pixel, pixel);
			}
		}
	}
}

int BinarizationIterative(CImage* image, int w, int h)
{
	register int i, j;
	float hist[256] = {0,};
	int T, Told;
	float sum = 0.f, a1, b1, u1, a2, b2, u2;

	fnHistogram(image, hist, w, h);

	for (i = 0; i < 256; i++)
		sum += (i*hist[i]);

	T = (int)sum;

	do
	{
		Told = T;

		a1 = b1 = 0;
		for (i = 0; i < Told; i++)
		{
			a1 += (i*hist[i]);
			b1 += hist[i];
		}
		u1 = a1/b1;

		a2 = b2 = 0;
		for (i = Told + 1; i < 256; i++)
		{
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

int Labeling(CImage* image, CImage* obj, int w, int h)
{
	register int i, j;

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
				if ((map[j-1][i] != 0) && (map[j][i-1] != 0)) {
					if (map[j-1][i] == map[j][i-1]) {
						// 두 레이블이 서로 같은 경우
						map[j][i] = map[j-1][i];
					}
					else {
						// 두 레이블이 서로 다른 경우
						max1 = max(map[j-1][i], map[j][i-1]);
						min1 = min(map[j-1][i], map[j][i-1]);

						map[j][i] = min1;

						// 등가 테이블 조정
						min_eq = min(eq_tbl[max1][1], eq_tbl[min1][1]);
						max_eq = max(eq_tbl[max1][1], eq_tbl[min1][1]);

						eq_tbl[max1][1] = min_eq;
						eq_tbl[min1][1] = min_eq;
					}
				}
				else if (map[j-1][i] != 0) {
					// 바로 위 픽셀에만 레이블이 존재하는 경우
					map[j][i] = map[j-1][i];
				}
				else if (map[j][i-1] != 0) {
					// 바로 왼쪽 픽셀에만 레이블이 존재하는 경우
					map[j][i] = map[j][i-1];
				}
				else {
					label++;
					map[j][i] = label;
					eq_tbl[label][0] = label;
					eq_tbl[label][1] = label;
				}
			}
		}
	}

	// 등가 테이블 정리
	int temp;
	for (i = 1; i <= label; i++) {
		temp = eq_tbl[i][1];
		if (temp != eq_tbl[i][0]) {
			eq_tbl[i][1] = eq_tbl[temp][1];
		}
	}

	// 등가 테이블의 레이블을 1부터 차례대로 증가시키기
	int* hash = new int[label+1];
	memset(hash, 0, sizeof(int)*(label+1));

	for (i = 1; i <= label; i++) {
		hash[eq_tbl[i][1]] = eq_tbl[i][1];
	}

	int cnt = 1;
	for (i = 1; i <= label; i++) {
		if (hash[i] != 0) {
			hash[i] = cnt++;
		}
	}

	for (i = 1; i <= label; i++) {
		eq_tbl[i][1] = hash[eq_tbl[i][1]];
	}

	delete [] hash;

	// 두 번째 스캔 - 등가 테이블을 이용하여 모든 픽셀에 고유의 레이블 부여
	obj->Create(w,h,24);

	for (j = 1; j < h; j++) {
		for (i = 1; i < w; i++) {
			if (map[j][i] != 0) {
				temp = map[j][i];
				obj->SetPixel(j,i,limit(eq_tbl[temp][1]));
			}
		}
	}

	// 임시 메모리 공간 해제
	for (i = 0; i < h; i++) {
		delete [] map[i];
	}
	delete [] map;

	return (cnt-1);
}

void ContourTracing(CImage* image, CImage* obj, int w, int h)
{
	register int i,j;

	int x, y, nx, ny, dold, d, cnt;
	int dir[8][2] = {
		{1,0}, {1,1}, {0,1}, {-1,1}, {-1,0}, {-1,-1}, {0,-1}, {1,-1}};

	ContourPoints cp;
	cp.num = 0;

	for (j = 0; j < h; j++) {
		for (i = 0; i < w; i++) {
			if (image->GetPixel(j,i) != 0) { // 객체인 경우
				x = i;
				y = j;

				dold = d = cnt = 0;

				while (true) {
					nx = x + dir[d][0];
					ny = y + dir[d][1];

					if (nx < 0 || nx >= w || ny < 0 || ny >= h || (image->GetPixel(ny,nx)>>16) == 0) {
						// 진행 방향에 있는 픽셀이 객체가 아닌 경우
						// 시계 방향으로 진행 방향을 바꾸고 다시 시도.
						if (++d > 7) d = 0;
						cnt++;

						// 8시 방향 모두 background인 경우
						if (cnt >= 8) {
							cp.x[cp.num] = x;
							cp.y[cp.num] = y;
							cp.num++;

							break;
						}
					}
					else {
						// 진행 방향의 픽셀이 객체일 경우,
						// 현재 점을 외곽전 정보에 저장
						cp.x[cp.num] = x;
						cp.y[cp.num] = y;
						cp.num++;

						if (cp.num >= MAX_CONTOUR) break; // 외곽선 픽셀이 너무 많으면 강제 종료

						// 진행 방향으로 이동
						x = nx;
						y = ny;

						// 방향 정보 초기화
						cnt = 0;
						dold = d;
						d = (dold + 6) % 8; // d = dold - 2와 같은 형태
					}

					// 시작점으로 돌아왔고, 진행 방향이 초기화된 경우
					// 외곽선 추적을 끝낸다.
					if (x == i && y == j && d == 0) break;
				}
				// for 루프를 강제 종료하기 위해 i, j값 조정.
				i = w; j = h;
			}
		}
	}

	obj->Create(w,h,24);
	for (i = 0; i < cp.num; i++)
		obj->SetPixelRGB(cp.y[i], cp.x[i], 255,255,255);
}

void MorphologyErosion(CImage* image, CImage* obj, int w, int h)
{
	register int i, j;

	for (j = 1; j < h-1; j++) {
		for (i = 1; i < w-1; i++) {
			if (obj->GetPixel(j,i) != 0) {
				if (image->GetPixel(j-1,i-1) == 0 ||
					image->GetPixel(j-1,i) == 0 ||
					image->GetPixel(j-1,i+1) == 0 ||
					image->GetPixel(j,i-1) == 0 ||
					image->GetPixel(j,i+1) == 0 ||
					image->GetPixel(j+1,i-1) == 0 ||
					image->GetPixel(j+1,i) == 0 ||
					image->GetPixel(j+1,i+1) == 0)
				{
					obj->SetPixel(j,i,0);
				}
			}
		}
	}
}

void MorphologyDilation(CImage* image, CImage* obj, int w, int h)
{
	register int i, j;

	for (j = 1; j < h-1; j++) {
		for (i = 1; i < w-1; i++) {
			if (obj->GetPixel(j,i) == 0) {
				if (image->GetPixel(j-1,i-1) != 0 ||
					image->GetPixel(j-1,i) != 0 ||
					image->GetPixel(j-1,i+1) != 0 ||
					image->GetPixel(j,i-1) != 0 ||
					image->GetPixel(j,i+1) != 0 ||
					image->GetPixel(j+1,i-1) != 0 ||
					image->GetPixel(j+1,i) != 0 ||
					image->GetPixel(j+1,i+1) != 0)
				{
					obj->SetPixelRGB(j,i,255,255,255);
				}
			}
		}
	}
}

void MorphologyOpening(CImage* image, CImage* obj, int w, int h)
{
	copy(image, obj);
	MorphologyErosion(image, obj,w,h);

	CImage tmp;
	copy(obj, &tmp);
	MorphologyDilation(&tmp, obj,w,h);
}

void MorphologyClosing(CImage* image, CImage* obj, int w, int h)
{
	copy(image, obj);
	MorphologyDilation(image, obj,w,h);

	CImage tmp;
	copy(obj, &tmp);
	MorphologyErosion(&tmp, obj,w,h);
}

void MorphologyGrayErosion(CImage* image, CImage* obj, int w, int h)
{
	register int i, j, m, n;

	if (obj->IsNull())
		obj->Create(w,h,24);

	int x, y ,pmin, pixel;
	for (j = 0; j < h; j++)
	{
		for (i = 0; i < w; i++)
		{
			pmin = 255;

			for (n = -1; n <= 1; n++)
			{
				for (m = -1; m <= 1; m++)
				{
					x = i + m;
					y = j + n;
					
					if (x >= 0 && x < w && y >= 0 && y < h)
					{
						pixel = image->GetPixel(y,x) >> 16;
						if (pixel < pmin)
							pmin = pixel;
					}
				}
			}
			obj->SetPixel(j,i,limit(pmin));
		}
	}
}

void MorphologyGrayDilation(CImage* image, CImage* obj, int w, int h)
{
	register int i, j, m, n;

	if (obj->IsNull())
		obj->Create(w,h,24);

	int x, y ,pmax, pixel;
	for (j = 0; j < h; j++)
	{
		for (i = 0; i < w; i++)
		{
			pmax = 0;
			for (n = -1; n <= 1; n++)
			{
				for (m = -1; m <= 1; m++)
				{
					x = i + m;
					y = j + n;
					
					if (x >= 0 && x < w && y >= 0 && y < h)
					{
						pixel = image->GetPixel(y,x) >> 16;
						if (pixel > pmax)
							pmax = pixel;
					}
				}
			}
			obj->SetPixel(j,i,limit(pmax));
		}
	}
}

void MorphologyGrayOpening(CImage* image, CImage* obj, int w, int h)
{
	MorphologyGrayErosion(image, obj, w,h);
	CImage tmp;
	copy(obj, &tmp);
	MorphologyGrayDilation(&tmp, obj, w,h);
}

void MorphologyGrayClosing(CImage* image, CImage* obj, int w, int h)
{
	MorphologyGrayDilation(image, obj, w,h);
	CImage tmp;
	copy(obj, &tmp);
	MorphologyGrayErosion(&tmp, obj, w,h);
}