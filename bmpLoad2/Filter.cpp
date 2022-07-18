#include "stdafx.h"
#include "Filter.h"

#include "Fourier.h"
#include "Gaussian.h"
#include "NoiseGaussian.h"
#include "SaltPepper.h"
#include "Diffusion.h"
#include "Harris.h"

#include <math.h>
#include <algorithm>

const double PI = acos(-1.0);

void fnMean(CImage* image, CImage* obj, int w, int h)
{
	register int i, j;
	int temp;

	obj->Create(w,h,24);

	for (i = 1; i < w-1; i++) {
		for (j = 1; j < h-1; j++) {
			temp = 0;
			temp = (image->GetPixel(i-1,j-1) & 255) + (image->GetPixel(i-1,j) & 255) + (image->GetPixel(i-1,j+1) & 255) +
				(image->GetPixel(i,j-1) & 255) +	(image->GetPixel(i,j) & 255)	+ (image->GetPixel(i,j+1) & 255) +
				(image->GetPixel(i+1,j-1) & 255) + (image->GetPixel(i+1,j) & 255) + (image->GetPixel(i+1,j+1) & 255);
			temp = (int)(temp / 9. + 0.5);
			obj->SetPixel(i,j,limit(temp));
		}
	}
}

void fnGaussian(CImage* image, CImage* obj, int w, int h)
{
	Gaussian gaussian;

	if (gaussian.DoModal() == IDOK)
	{
		register int i,j,k,x;
		obj->Create(w,h,24);

		double sigma = gaussian.m_sigma;
		int dim = (int) max(3.0, 2*4*sigma + 1.0);
		if (dim % 2 == 0) dim++;
		int dim2 = (int) dim/2;

		double* pMask = new double[dim];
		for (i = 0; i < dim; i++) {
			x = i - dim2;
			pMask[i] = exp(-(x*x)/(2*sigma*sigma)) / (sqrt(2*PI)*sigma);
		}

		double** buf = new double*[h];
		for (i = 0; i < h; i++) {
			buf[i] = new double[w];
			memset(buf[i], 0, sizeof(double)*w);
		}

		double sum1, sum2;
		for (i = 0; i < w; i++) {
			for (j = 0; j < h; j++) {
				sum1 = sum2 = 0;

				for (k = 0; k < dim; k++) {
					x = k - dim2 + j;
					if (x >= 0 && x < h) {
						sum1 += pMask[k];
						sum2 += (pMask[k] * (image->GetPixel(x,i) >> 16));
					}
				}

				buf[j][i] = sum2 / sum1;
			}
		}

		int value = 0;
		for (j = 0; j < h; j++) {
			for (i = 0; i < w; i++) {
				sum1 = sum2 = 0;

				for (k = 0; k < dim; k++) {
					x = k - dim2 + i;
					if (x >= 0 && x < w) {
						sum1 += pMask[k];
						sum2 += (pMask[k] * buf[j][x]);
					}
				}
				value = (int)(sum2 / sum1);
				value += (value << 16) + (value << 8);
				obj->SetPixel(j,i,value);
			}
		}

		for (i = 0; i < h; i++) {
			delete [] buf[i];
		}
		delete [] pMask, buf;
	}
}

void fnUnsharpMask(CImage* image, CImage* obj, int w, int h)
{
	register int i, j;
	int cTemp;

	obj->Create(w,h,24);

	for (i = 1; i < w-1; i++)
	{
		for (j = 1; j < h-1; j++)
		{
			cTemp = 5*(image->GetPixel(i,j) >> 16) - (image->GetPixel(i-1,j) >> 16) - (image->GetPixel(i,j-1) >> 16)
				- (image->GetPixel(i+1,j) >> 16) - (image->GetPixel(i,j+1) >> 16);
			obj->SetPixel(i,j,limit(cTemp));
		}
	}
}

void fnLaplacian(CImage* image, CImage* obj, int w, int h)
{
	register int i, j;
	int value;

	obj->Create(w,h,24);

	for (j = 1; j < h-1; j++) {
		for (i = 1; i < w-1; i++) {
			value = 4*(image->GetPixel(j,i) >> 16) - (image->GetPixel(j-1,i) >> 16) - (image->GetPixel(j,i+1) >> 16)
				- (image->GetPixel(j+1,i) >> 16) - (image->GetPixel(j,i-1) >> 16);
			obj->SetPixel(j,i,limit(value));
		}
	}
}

void fnNoiseGaussian(CImage* image, CImage* obj, int w, int h)
{
	NoiseGaussian NG;

	if (NG.DoModal() == IDOK)
	{
		register int i, j;
		double amount = NG.m_deviation;
		srand((unsigned)time(NULL));
		double rnd;
		int value;

		obj->Create(w,h,24);

		for (j = 0; j < h; j++)
		{
			for (i = 0; i < w; i++)
			{
				rnd = fnGaussianRand(0, amount);
				value = (image->GetPixel(j,i) >> 16) + rnd;
				obj->SetPixel(j,i,limit(value));
			}
		}
	}
}

void fnNoiseSaltNPepper(CImage* image, CImage* obj, int w, int h)
{
	SaltPepper SP;

	if (SP.DoModal() == IDOK)
	{
		register int i, j;
		double amount = SP.m_deviation;

		srand((unsigned)time(NULL));

		int rnd;
		for (j = 0; j < h; j++) {
			for (i = 0; i < w; i++) {
				rnd = (int) (rand() * 100 / RAND_MAX);

				if (rnd < amount/2) obj->SetPixel(j,i,0);
				else if (rnd < amount) obj->SetPixel(j,i,0xffffffff);
			}
		}
	}
}

double fnGaussianRand(double mean, double std)
{
	double x1, x2, radius, factor, y1;
	static double y2;
	static int use_last = 0;

	if (use_last) {
		y1 = y2;
		use_last = 0;
	}
	else {
		do {
			x1 = 2.0 * rand() / RAND_MAX - 1.0;
			x2 = 2.0 * rand() / RAND_MAX - 1.0;
			radius = x1 * x1 + x2 * x2;
		} while (radius < 0.00000001 || radius >= 1.0);

		factor = sqrt((-2.0 * log(radius)) / radius);

		y1 = x1 * factor;
		y2 = x2 * factor;

		use_last = 1;
	}

	return (mean + y1*std);
}

void fnMedean(CImage* image, CImage* obj, int w, int h)
{
	register int i, j;

	obj->Create(w,h,24);

	int m[9], pixel;
	for (j = 1; j < h-1; j++) {
		for (i = 1; i < w-1; i++) {
			m[0] = image->GetPixel(j-1,i-1) >> 16;
			m[1] = image->GetPixel(j-1,i) >> 16;
			m[2] = image->GetPixel(j-1,i+1) >> 16;
			m[3] = image->GetPixel(j,i-1) >> 16;
			m[4] = image->GetPixel(j,i) >> 16;
			m[5] = image->GetPixel(j,i+1) >> 16;
			m[6] = image->GetPixel(j+1,i-1) >> 16;
			m[7] = image->GetPixel(j+1,i) >> 16;
			m[8] = image->GetPixel(j+1,i+1) >> 16;

			std::sort(m, m+9);

			pixel = (m[4] << 16) + (m[4] << 8) + m[4];
			obj->SetPixel(j,i,pixel);
		}
	}
}

void fnDiffusion(CImage* image, CImage* obj, int w, int h)
{
	Diffusion diffusion;

	if (diffusion.DoModal() == IDOK)
	{
		register int i, x, y;

		float lambda = diffusion.lambda;
		float k = diffusion.k;
		int iter = diffusion.iter;
		float k2 = k*k;

		float gradn, grads, grade, gradw;
		float gcn, gcs, gce, gcw;
		float tmp;

		obj->Create(w,h,24);

		float** cpy = new float*[h];
		for (i = 0; i < h; i++) {
			cpy[i] = new float[w];
			memset(cpy[i], 0, sizeof(float)*w);
		}

		float** buf = new float*[h];
		for (i = 0; i < h; i++) {
			buf[i] = new float[w];
			memset(buf[i], 0, sizeof(float)*w);
		}

		for (y = 0; y < h; y++) {
			for (x = 0; x < w; x++) {
				cpy[y][x] = buf[y][x] = (float) ((unsigned char)image->GetPixel(y,x));
			}
		}

		for (i = 0; i < iter; i++) {
			for (y = 1; y < h-1; y++) {
				for (x = 1; x < w-1; x++) {
					tmp = cpy[y][x];

					gradn = cpy[y-1][x] - tmp;
					grads = cpy[y+1][x] - tmp;
					grade = cpy[y][x-1] - tmp;
					gradw = cpy[y][x+1] - tmp;
					gcn = gradn / (1.0f + gradn*gradn/k2);
					gcs = grads / (1.0f + grads*grads/k2);
					gce = grade / (1.0f + grade*grade/k2);
					gcw = gradw / (1.0f + gradw*gradw/k2);

					buf[y][x] = cpy[y][x] + lambda*(gcn+gcs+gce+gcw);
				}
			}

			for (y = 0; y < h; y++) {
				memcpy(cpy[y], buf[y], sizeof(float)*w);
			}
		}

		for (y = 0; y < h; y++) {
			for (x = 0; x < w; x++) {
				i = buf[y][x];
				i += (i << 16) + (i << 8);
				obj->SetPixel(y,x,i);
			}
		}


		for (i = 0; i < h; i++) {
			delete [] buf[i], cpy[i];
		}
		delete [] buf, cpy;
	}
}

void fnEdgeRoberts(CImage* image, CImage* obj, int w, int h)
{
	register int i, j;

	obj->Create(w,h,24);

	int h1, h2;
	double hval;
	for (j = 1; j < h-1; j++) {
		for (i = 1; i < w-1; i++) {
			h1 = (image->GetPixel(j,i)>>16) - (image->GetPixel(j-1,i-1)>>16);
			h2 = (image->GetPixel(j,i)>>16) - (image->GetPixel(j-1,i+1)>>16);

			hval = sqrt((double)h1*h1 + h2*h2);

			obj->SetPixel(j,i,limit((int)hval));
		}
	}
}

void fnEdgePrewitt(CImage* img, CImage* obj, int w, int h)
{
	register int i, j;

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

void fnEdgeSobel(CImage* image, CImage* obj, int w, int h)
{
	register int i, j;

	obj->Create(w,h,24);

	int h1, h2;
	double hval;
	for (j = 1; j < h-1; j++) {
		for (i = 1; i < w-1; i++) {
			h1 = (image->GetPixel(j+1,i-1)>>16) + 2*(image->GetPixel(j+1,i)>>16) + (image->GetPixel(j+1,i+1)>>16)
				- (image->GetPixel(j-1,i-1)>>16) - 2*(image->GetPixel(j-1,i)>>16) - (image->GetPixel(j-1,i+1)>>16);
			h2 = (image->GetPixel(j-1,i+1)>>16) + 2*(image->GetPixel(j,i+1)>>16) + (image->GetPixel(j+1,i+1)>>16)
				- (image->GetPixel(j-1,i-1)>>16) - 2*(image->GetPixel(j,i-1)>>16) - (image->GetPixel(j+1,i-1)>>16);

			hval = sqrt((double)h1*h1 + h2*h2);

			obj->SetPixel(j,i,limit((int)hval));
		}
	}
}

LineParam fnHoughLine(CImage* image, int w, int h)
{
	register int i, j;

	int num_rho = (int)(sqrt((double)w*w + h*h)*2);
	const int num_ang = 360;

	// 0~PI 각도에 해당하는 sin, cos 함수의 값을 룩업테이블에 저장
	/*double* tsin = new double[num_ang];
	double* tcos = new double[num_ang];*/
	double tsin[num_ang];
	double tcos[num_ang];

	for (i = 0; i < num_ang; i++)
	{
		tsin[i] = (double)std::sin(i*PI/num_ang);
		tcos[i] = (double)std::cos(i*PI/num_ang);
	}

	// 축적 배열(accumulate dlgsay) 생성
	int** arr = new int*[num_rho];

	for (i = 0; i < num_rho; i++)
	{
		arr[i] = new int[num_ang];
		memset(arr[i], 0, sizeof(int)*num_ang);
	}

	int m,n;
	for (j = 0; j < h; j++)
	{
		for (i = 0; i < w; i++)
		{
			if ((image->GetPixel(j,i)>>16) > 128)
			{
				for (n = 0; n < num_ang; n++)
				{
					m = (int) floor(j*tsin[n] + i*tcos[n] + 0.5);
					m += (num_rho/2);

					arr[m][n]++;
				}
			}
		}
	}

	// 축적 배열에서 최대값 찾기
	LineParam line;
	line.rho = line.ang = 0;

	int arr_max = 0;
	for (m = 0; m < num_rho; m++)
	{
		for (n = 0; n < num_ang; n++)
		{
			if (arr[m][n] > arr_max)
			{
				arr_max = arr[m][n];
				line.rho = m - (num_rho/2);
				line.ang = n*180.0/num_ang;
			}
		}
	}

	// 동적 할당 메모리 해제
	//delete [] tsin, tcos;
	for (i = 0; i < num_rho; i++)
		delete [] arr[i];
	delete [] arr;

	return line;
}

void fnDrawLine(CImage* obj, LineParam line, BYTE c, int w, int h)
{
	register int x, y;
	obj->Create(w,h,24);

	// 수직선인 경우
	if (line.ang == 90)
	{
		x = (int)(line.rho + 0.5);

		for (y = 0; y < h; y++)
			obj->SetPixel(y,x,limit(c));	// byte를 int로 형 변환하고 비트 시프트 해야하는지

		return;
	}

	// (rho, ang) 파라미터를 이용하여 직선의 시작 좌표와 끝 좌표를 계산
	int x1 = 0;
	int y1 = (int) floor(line.rho / cos(line.ang*PI/180) + 0.5);
	int x2 = w - 1;
	int y2 = (int) floor((line.rho - x2*sin(line.ang*PI/180)) / cos(line.ang*PI/180) + 0.5);

	fnDrawLine(obj, x1, y1, x2, y2, c, w, h);
}

void fnDrawLine(CImage* obj, int x1, int y1, int x2, int y2, BYTE c, int w, int h)
{
	register int x, y;
	double m;

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
				obj->SetPixel(x,y,limit(c));
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
				obj->SetPixel(x,y,limit(c));
			}
		}
	}
}

void fnHarrisCorner(CImage* image, CImage* obj, int w, int h)
{
	Harris harris;

	if (harris.DoModal() == IDOK)
	{
		int th = harris.m_edit_threshold;

		CornerPoints cp;
		cp = fnCornerPoints(image, w, h, th);

		register int i, x, y;
		for (i = 0; i < cp.num; i++) {
			x = cp.x[i];
			y = cp.y[i];

			obj->SetPixel(y-1,x-1,0);
			obj->SetPixel(y-1,x,0);
			obj->SetPixel(y-1,x+1,0);
			obj->SetPixel(y,x-1,0);
			obj->SetPixel(y,x,0);
			obj->SetPixel(y,x+1,0);
			obj->SetPixel(y+1,x-1,0);
			obj->SetPixel(y+1,x,0);
			obj->SetPixel(y+1,x+1,0);
		}
	}
}

_CornerPoints fnCornerPoints(CImage* image, int w, int h, double th)
{
	register int i, j, x, y;

	double** dx2 = new double*[h];
	double** dy2 = new double*[h];
	double** dxy = new double*[h];

	for (i = 0; i < h; i++)
	{
		dx2[i] = new double[w];
		dy2[i] = new double[w];
		dxy[i] = new double[w];
		memset(dx2[i], 0, sizeof(double)*w);
		memset(dy2[i], 0, sizeof(double)*w);
		memset(dxy[i], 0, sizeof(double)*w);
	}

	double tx, ty, tmp;
	tx = ty = tmp = 0;
	for (j = 1; j < h-1; j++)
	{
		for (i = 1; i < w-1; i++)
		{
			// GetPixel return type이 colorref이고 unsigned라 -가 나오면 매우 큰 값으로 바뀌어 하나씩 수행
			tx = image->GetPixel(j-1,i+1)>>16;
			tx += image->GetPixel(j,i+1)>>16;
			tx += image->GetPixel(j+1,i+1)>>16;
			tx -= image->GetPixel(j-1,i-1)>>16;
			tx -= image->GetPixel(j,i-1)>>16;
			tx -= image->GetPixel(j+1,i+1)>>16;
			tx /= 6.0;

			ty = image->GetPixel(j+1,i-1)>>16;
			ty += image->GetPixel(j+1,i)>>16;
			ty += image->GetPixel(j+1,i+1)>>16;
			ty -= image->GetPixel(j-1,i-1)>>16;
			ty -= image->GetPixel(j-1,i)>>16;
			ty -= image->GetPixel(j-1,i+1)>>16;
			ty /= 6.0;

			dx2[j][i] = tx*tx;
			tmp = ty * ty;
			dy2[j][i] = ty*ty;
			dxy[j][i] = tx*ty;
		}
	}

	// Gaussian Filtering
	double** gdx2 = new double*[h];
	double** gdy2 = new double*[h];
	double** gdxy = new double*[h];

	for (i = 0; i < h; i++)
	{
		gdx2[i] = new double[w];
		gdy2[i] = new double[w];
		gdxy[i] = new double[w];
		memset(gdx2[i], 0, sizeof(double)*w);
		memset(gdy2[i], 0, sizeof(double)*w);
		memset(gdxy[i], 0, sizeof(double)*w);
	}

	double g[5][5] = {{1,4,6,4,1}, {4,16,24,16,4}, {6,24,36,24,6}, {4,16,24,16,4}, {1,4,6,4,1}};

	for (y = 0; y < 5; y++)
	{
		for (x = 0; x < 5; x++)
		{
			g[y][x] /= 256.;
		}
	}

	double tx2, ty2, txy;
	for (j = 2; j < h-2; j++)
	{
		for (i = 2; i < w-2; i++)
		{
			tx2 = ty2 = txy = 0;

			for (y = 0; y < 5; y++)
			{
				for (x = 0; x < 5; x++)
				{
					tx2 += (dx2[j+y-2][i+x-2]*g[y][x]);
					ty2 += (dy2[j+y-2][i+x-2]*g[y][x]);
					txy += (dxy[j+y-2][i+x-2]*g[y][x]);
				}
			}

			gdx2[j][i] = tx2;
			gdy2[j][i] = ty2;
			gdxy[j][i] = txy;
		}
	}

	// 코너 응답 함수 생성
	double** crf = new double*[h];

	for (i = 0; i < h; i++)
	{
		crf[i] = new double[w];
		memset(crf[i], 0, sizeof(double)*w);
	}

	double k = 0.04;

	for (j = 2; j < h-2; j++)
	{
		for (i = 2; i < w-2; i++)
		{
			tmp = (gdx2[j][i]*gdy2[j][i] - gdxy[j][i]*gdxy[j][i]) - k*(gdx2[j][i] + gdy2[j][i])*(gdx2[j][i] + gdy2[j][i]);
			crf[j][i] = tmp;
		}
	}

	// 임계값보다 큰 국지적 최대값을 찾아 코너 포인트로 결정
	CornerPoints cp;
	cp.num = 0;

	for (j = 2; j < h-2; j++)
	{
		for (i = 2; i < w-2; i++)
		{
			if (crf[j][i] > th)
			{
				if (crf[j][i] > crf[j-1][i] && crf[j][i] > crf[j-1][i+1] &&
					crf[j][i] > crf[j][i+1] && crf[j][i] > crf[j+1][i+1] &&
					crf[j][i] > crf[j+1][i] && crf[j][i] > crf[j+1][i-1] &&
					crf[j][i] > crf[j][i-1] && crf[j][i] > crf[j-1][i-1])
				{
					if (cp.num < MAX_CORNER)
					{
						cp.x[cp.num] = i;
						cp.y[cp.num] = j;
						cp.num++;
					}
				}
			}
		}
	}

	// 동적 할당 메모리 해제
	for (i = 0; i < h; i++)
		delete [] dx2[i], dy2[i], dxy[i], gdx2[i], gdy2[i], gdxy[i], crf[i];
	delete [] dx2, dy2, dxy, gdx2, gdy2, gdxy, crf;

	return cp;
}