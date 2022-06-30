#include "stdafx.h"
#include "Segment.h"
#include "Enhancement.h"
#include "Filter.h"

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

int Labeling(CImage* image, CImage* obj)
{
	register int i, j;

	int w = image->GetWidth();
	int h = image->GetHeight();

	// �ӽ÷� ���̺��� ������ �޸� ������ � ���̺� ����
	int** map = new int*[h];
	for (i = 0; i < h; i++) {
		map[i] = new int[w];
		memset(map[i],0,sizeof(int)*w);
	}
	int eq_tbl[MAX_LABEL][2] = {{0,},};

	// ù ��° ��ĵ - �ʱ� ���̺� ���� �� � ���̺� ����
	int label = 0, max1, min1, min_eq, max_eq;

	for (j = 1; j < h; j++) {
		for (i = 1; i < w; i++) {
			if (image->GetPixel(j,i) != 0) {
				// �ٷ� �� �ȼ��� ���� �ȼ� ��ο� ���̺��� �����ϴ� ���
				if ((map[j-1][i] != 0) && (map[j][i-1] != 0)) {
					if (map[j-1][i] == map[j][i-1]) {
						// �� ���̺��� ���� ���� ���
						map[j][i] = map[j-1][i];
					}
					else {
						// �� ���̺��� ���� �ٸ� ���
						max1 = max(map[j-1][i], map[j][i-1]);
						min1 = min(map[j-1][i], map[j][i-1]);

						map[j][i] = min1;

						// � ���̺� ����
						min_eq = min(eq_tbl[max1][1], eq_tbl[min1][1]);
						max_eq = max(eq_tbl[max1][1], eq_tbl[min1][1]);

						eq_tbl[max1][1] = min_eq;
						eq_tbl[min1][1] = min_eq;
					}
				}
				else if (map[j-1][i] != 0) {
					// �ٷ� �� �ȼ����� ���̺��� �����ϴ� ���
					map[j][i] = map[j-1][i];
				}
				else if (map[j][i-1] != 0) {
					// �ٷ� ���� �ȼ����� ���̺��� �����ϴ� ���
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

	// � ���̺� ����
	int temp;
	for (i = 1; i <= label; i++) {
		temp = eq_tbl[i][1];
		if (temp != eq_tbl[i][0]) {
			eq_tbl[i][1] = eq_tbl[temp][1];
		}
	}

	// � ���̺��� ���̺��� 1���� ���ʴ�� ������Ű��
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

	// �� ��° ��ĵ - � ���̺��� �̿��Ͽ� ��� �ȼ��� ������ ���̺� �ο�
	obj->Create(w,h,24);

	for (j = 1; j < h; j++) {
		for (i = 1; i < w; i++) {
			if (map[j][i] != 0) {
				temp = map[j][i];
				obj->SetPixel(j,i,limit(eq_tbl[temp][1]));
			}
		}
	}

	// �ӽ� �޸� ���� ����
	for (i = 0; i < h; i++) {
		delete [] map[i];
	}
	delete [] map;

	return (cnt-1);
}

ContourPoints ContourTracing(CImage* image, CImage* obj)
{
	register int i,j;

	int w = image->GetWidth();
	int h = image->GetHeight();

	int x, y, nx, ny, dold, d, cnt;
	int dir[8][2] = {
		{1,0}, {1,1}, {0,1}, {-1,1}, {-1,0}, {-1,-1}, {0,-1}, {1,-1}};

	ContourPoints cp;
	cp.num = 0;

	for (j = 0; j < h; j++) {
		for (i = 0; i < w; i++) {
			if (image->GetPixel(j,i) != 0) { // ��ü�� ���
				x = i;
				y = j;

				dold = d = cnt = 0;

				while (true) {
					nx = x + dir[d][0];
					ny = y + dir[d][1];

					if (nx < 0 || nx >= w || ny < 0 || ny >= h || (image->GetPixel(ny,nx)>>16) == 0) {
						// ���� ���⿡ �ִ� �ȼ��� ��ü�� �ƴ� ���
						// �ð� �������� ���� ������ �ٲٰ� �ٽ� �õ�.
						if (++d > 7) d = 0;
						cnt++;

						// 8�� ���� ��� background�� ���
						if (cnt >= 8) {
							cp.x[cp.num] = x;
							cp.y[cp.num] = y;
							cp.num++;

							break;
						}
					}
					else {
						// ���� ������ �ȼ��� ��ü�� ���,
						// ���� ���� �ܰ��� ������ ����
						cp.x[cp.num] = x;
						cp.y[cp.num] = y;
						cp.num++;

						if (cp.num >= MAX_CONTOUR) break; // �ܰ��� �ȼ��� �ʹ� ������ ���� ����

						// ���� �������� �̵�
						x = nx;
						y = ny;

						// ���� ���� �ʱ�ȭ
						cnt = 0;
						dold = d;
						d = (dold + 6) % 8; // d = dold - 2�� ���� ����
					}

					// ���������� ���ƿ԰�, ���� ������ �ʱ�ȭ�� ���
					// �ܰ��� ������ ������.
					if (x == i && y == j && d == 0) break;
				}
				// for ������ ���� �����ϱ� ���� i, j�� ����.
				i = w; j = h;
			}
		}
	}

	return cp;
}

void MorphologyErosion(CImage* image, CImage* obj)
{
	register int i, j;

	int w = image->GetWidth();
	int h = image->GetHeight();

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

void MorphologyDilation(CImage* image, CImage* obj)
{
	register int i, j;

	int w = image->GetWidth();
	int h = image->GetHeight();

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

void MorphologyGrayErosion(CImage* image, CImage* obj)
{
	register int i, j, m, n;

	int w = image->GetWidth();
	int h = image->GetHeight();

	int x, y ,pmin, pixel;
	for (j = 0; j < h; j++) {
		for (i = 0; i < w; i++) {
			pmin = 255;
			for (n = -1; n <= 1; n++) {
				for (m = -1; m <= 1; m++) {
					x = i + m;
					y = j + n;
					
					if (x >= 0 && x < w && y >= 0 && y < h) {
						pixel = image->GetPixel(y,x) >> 16;
						if (pixel < pmin) {
							pmin = pixel;
						}
					}
				}
			}
			obj->SetPixel(j,i,limit(pmin));
		}
	}
}

void MorphologyGrayDilation(CImage* image, CImage* obj)
{
	register int i, j, m, n;

	int w = image->GetWidth();
	int h = image->GetHeight();

	int x, y ,pmax, pixel;
	for (j = 0; j < h; j++) {
		for (i = 0; i < w; i++) {
			pmax = 0;
			for (n = -1; n <= 1; n++) {
				for (m = -1; m <= 1; m++) {
					x = i + m;
					y = j + n;
					
					if (x >= 0 && x < w && y >= 0 && y < h) {
						pixel = image->GetPixel(y,x) >> 16;
						if (pixel > pmax) {
							pmax = pixel;
						}
					}
				}
			}
			obj->SetPixel(j,i,limit(pmax));
		}
	}
}