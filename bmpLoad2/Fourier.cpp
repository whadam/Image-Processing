#include "stdafx.h"
#include "Fourier.h"
#include <math.h>

const double PI = acos(-1.0);

Fourier::Fourier(void) : w(0), h(0), pRe(NULL), pIm(NULL) {}
Fourier::~Fourier(void)
{
	Free();
}
void Fourier::Free()
{
	register int i;

	if (pRe) {
		for (i = 0; i < h; i++) {
			delete [] pRe[i];
		}
		delete [] pRe;
	}

	if (pIm) {
		for (i = 0; i < h; i++) {
			delete [] pIm[i];
		}
		delete [] pIm;
	}
}

int Fourier::limit(int pixel)
{
	if (pixel > 255) {
		return (255 << 16) + (255 << 8) + 255;
	}
	else if (pixel < 0) return 0;
	else {
		return (pixel<<16) + (pixel<<8) + pixel;
	}
}

void Fourier::SetImage(CImage* img)
{
	Free();

	register int i,j;

	w = img->GetWidth();
	h = img->GetHeight();

	pRe = new double*[h];
	pIm = new double*[h];

	for (i = 0; i < h; i++) {
		pRe[i] = new double[w];
		pIm[i] = new double[w];

		memset(pRe[i], 0, sizeof(double)*w);
		memset(pIm[i], 0, sizeof(double)*w);
	}

	for (j = 0; j < h; j++) {
		for (i = 0; i < w; i++) {
			pRe[j][i] = (double)(img->GetPixel(j,i)>>16);
		}
	}
}

void Fourier::GetImage(CImage* img)
{
	if (pRe == NULL) return;

	register int i, j;

	int pixel;
	for (j = 0; j < h; j++) {
		for (i = 0; i < w; i++) {
			pixel = pRe[j][i] + 0.5;
			img->SetPixel(j,i,limit(pixel));
		}
	}
}

void Fourier::GetSpectrumImage(CImage* img)
{
	register int i, j;

	// 스펙트럼 값을 저장할 임시 버퍼 메모리 공간 할당
	double** pSpectrum = new double*[h];
	for (i = 0; i < h; i++) {
		pSpectrum[i] = new double[w];
		memset(pSpectrum[i], 0, sizeof(double)*w);
	}

	// 복소수 값의 절대값을 로그 변환하여 저장
	// 정규화된 결과 이미지 생성을 위하여 스펙트럼의 최대값 계산
	double mag, max_value = 0;
	for (j = 0; j < h; j++) {
		for (i = 0; i < w; i++) {
			mag = sqrt(pRe[j][i]*pRe[j][i] + pIm[j][i]*pIm[j][i]);
			pSpectrum[j][i] = log(mag + 1);

			if (pSpectrum[j][i] > max_value) {
				max_value = pSpectrum[j][i];
			}
		}
	}

	// 출력 영상 생성, DFT 결과를 shift 하고,
	// 출력 영상의 최대값이 255가 되도록 grayscale 값 정규화
	int x, y, pixel;
	for (j = 0; j < h; j++) {
		for (i = 0; i < w; i++) {
			x = i + w/2;
			y = j + h/2;

			if (x >= w) x -= w;
			if (y >= h) y -= h;

			pixel = pSpectrum[y][x]*255/max_value;
			img->SetPixel(j,i,limit(pixel));
		}
	}

	// 임시 버퍼 메모리 공간 해제
	for (i = 0; i < h; i++) {
		delete [] pSpectrum[i];
	}
	delete [] pSpectrum;
}

void Fourier::GetphaseImage(CImage* img)
{
	register int i, j;

	// 위상각을 저장할 임시 버퍼 메모리 공간 할당
	double** pPhase = new double*[h];
	for (i = 0; i < h; i++) {
		pPhase[i] = new double[w];
		memset(pPhase[i], 0, sizeof(double)*w);
	}

	// 복소수 값의 위상각을 저장. atan2 함수의 반환 값은 -PI ~ PI 이다.
	for (j = 0; j < h; j++) {
		for (i = 0; i < w; i++) {
			pPhase[j][i] = atan2(pIm[j][i], pRe[j][i]); // radian 단위
		}
	}

	// 출력 영상 생성. DFT 결과를 shift하고,
	// 출력 영상의 최대값이 255가 되도록 garyscale 값을 정규화
	int x, y, pixel;
	for (j = 0; j < h; j++) {
		for (i = 0; i < w; i++) {
			x = i + w/2;
			y = j + h/2;

			if (x >= w) x -= w;
			if (y >= h) y -= h;

			pixel = pPhase[y][x]*128/PI + 128;
			img->SetPixel(j,i,limit(pixel));
		}
	}

	for (i = 0; i < h; i++) {
		delete [] pPhase[i];
	}
	delete [] pPhase;
}

void Fourier::DFT(int dir)
{
	if (pRe == NULL || pIm == NULL) return;

	register int i, j, x, y;

	// pRe, pIm과 동일한 메모리 공간을 임시로 생성
	double** re = new double*[h];
	double** im = new double*[h];

	for (i = 0; i < h; i++) {
		re[i] = new double[w];
		im[i] = new double[w];

		memcpy(re[i], pRe[i], sizeof(double)*w);
		memcpy(im[i], pIm[i], sizeof(double)*w);
	}

	// DFT
	double sum_re, sum_im, tmp;

	for (j = 0; j < h; j++) {
		for (i = 0; i < w; i++) {
			sum_re = sum_im = 0;

			for (y = 0; y < h; y++) {
				for (x = 0; x < w; x++) {
					tmp = 2*dir*PI * ((double)i*x/w + (double)j*y/h);
					sum_re += (re[y][x]*cos(tmp) - im[y][x]*sin(tmp));
					sum_im += (re[y][x]*sin(tmp) + im[y][x]*sin(tmp));
				}
			}

			pRe[j][i] = sum_re;
			pIm[j][i] = sum_im;

			if (dir == -1) { // backward transform
				pRe[j][i] /= (w*h);
				pIm[j][i] /= (w*h);
			}
		}
	}

	// 임시로 생성한 메모리 공간을 해제한다.
	for (j = 0; j < h; j++) {
		delete [] re[i], im[i];
	}
	delete [] re, im;
}

void Fourier::DFTRC(int dir)
{
	if (pRe == NULL || pIm == NULL) return;

	register int i, j;

	// row 단위 DFT (또는 역변환)
	double* re = new double[h];
	double* im = new double[h];

	memset(re, 0, sizeof(double)*w);
	memset(im, 0, sizeof(double)*w);

	for (j = 0; j < h; j++) {
		for (i = 0; i < w; i++) {
			re[i] = pRe[j][i];
			im[i] = pIm[j][i];
		}
		DFT1d(re, im, w, dir);
		for (i = 0; i < w; i++) {
			pRe[j][i] = re[i];
			pIm[j][i] = im[i];
		}
	}

	delete [] re, im;

	// column 단위 DFT (또는 역변환)
	re = new double[h];
	im = new double[h];

	memset(re, 0, sizeof(double)*w);
	memset(im, 0, sizeof(double)*w);

	for (i = 0; i < w; i++) {
		for (j = 0; j < h; j++) {
			re[j] = pRe[j][i];
			im[j] = pIm[j][i];
		}
		DFT1d(re,im,h,dir);
		for(j = 0; j < h; j++) {
			pRe[j][i] = re[j];
			pIm[j][i] = im[j];
		}
	}

	delete [] re, im;
}

void Fourier::FFT(int dir)
{
	if (pRe == NULL || pIm == NULL) return;
	if (!IsPowerOf2(w) || !IsPowerOf2(h)) return;

	register int i, j;

	// row 단위 FFT (or IFFT)
	double* re = new double[w];
	double* im = new double[w];

	memset(re,0,sizeof(double)*w);
	memset(im,0,sizeof(double)*w);

	for (j = 0; j < h; j++) {
		for (i = 0; i < w; i++) {
			re[i] = pRe[j][i];
			im[i] = pIm[j][i];
		}

		FFT1d(re, im, w, dir);

		for (i = 0; i < w; i++) {
			pRe[j][i] = re[i];
			pIm[j][i] = im[i];
		}
	}

	delete [] re, im;

	// column 단위 FFT (or IFFT)
	re = new double[h];
	im = new double[h];

	memset(re,0,sizeof(double)*h);
	memset(im,0,sizeof(double)*h);

	for (i = 0; i < w; i++) {
		for (j = 0; j < h; j++) {
			re[j] = pRe[j][i];
			im[j] = pIm[j][i];
		}

		FFT1d(re, im, h, dir);

		for (j = 0; j < h; j++) {
			pRe[j][i] = re[j];
			pIm[j][i] = im[j];
		}
	}

	delete [] re, im;
}

void Fourier::IdealLowpass(int cutoff)
{
	register int i, j;

	int w2 = w/2;
	int h2 = h/2;

	int x, y;
	for (j = 0; j < h; j++) {
		for (i = 0; i < w; i++) {
			x = i + w2;
			y = j + h2;

			if (x >= w) x -= w;
			if (y >= h) y -= h;

			if (sqrt((double)(x-w2)*(x-w2) + (y-h2)*(y-h2)) > cutoff) {
				pRe[j][i] = pIm[j][i] = 0;
			}
		}
	}
}

void Fourier::IdealHighpass(int cutoff)
{
	register int i, j;

	int w2 = w/2;
	int h2 = h/2;

	int x, y;
	for (j = 0; j < h; j++) {
		for (i = 0; i < w; i++) {
			x = i + w2;
			y = j + h2;

			if (x >= w) x -= w;
			if (y >= h) y -= h;

			if (sqrt((double)(x-w2)*(x-w2) + (y-h2)*(y-h2)) < cutoff) {
				pRe[j][i] = pIm[j][i] = 0;
			}
		}
	}
}

void Fourier::GaussianLowpass(int cutoff)
{
	register int i, j;

	int w2 = w/2;
	int h2 = h/2;

	int x, y;
	double dist2, hval;
	for (j = 0; j < h; j++) {
		for (i = 0; i < w; i++) {
			x = i + w2;
			y = j + h2;

			if (x >= w) x -= w;
			if (y >= h) y -= h;

			dist2 = (double) (x-w2)*(x-w2) + (y-h2)*(y-h2);

			hval = exp(-dist2 / (2*cutoff*cutoff));

			pRe[j][i] *= hval;
			pIm[j][i] *= hval;
		}
	}
}

void Fourier::GaussianHighpass(int cutoff)
{
	register int i, j;

	int w2 = w/2;
	int h2 = h/2;

	int x, y;
	double dist2, hval;
	for (j = 0; j < h; j++) {
		for (i = 0; i < w; i++) {
			x = i + w2;
			y = j + h2;

			if (x >= w) x -= w;
			if (y >= h) y -= h;

			dist2 = (double) (x-w2)*(x-w2) + (y-h2)*(y-h2);

			hval = 1.0 - exp(-dist2 / (2*cutoff*cutoff));

			pRe[j][i] *= hval;
			pIm[j][i] *= hval;
		}
	}
}

void DFT1d(double* re, double* im, int N, int dir)
{
	register int i, x;

	double* tr = new double[N];
	double* ti = new double[N];

	memcpy(tr, re, sizeof(double)*N);
	memcpy(ti, im, sizeof(double)*N);

	double sum_re, sum_im, tmp;

	for (i = 0; i < N; i++) {
		sum_re = sum_im = 0;

		for (x = 0; x < N; x++) {
			tmp = 2*dir*PI*((double)i*x/N);

			sum_re += (tr[x]*cos(tmp) + ti[x]*sin(tmp));
			sum_im += (ti[x]*cos(tmp) - tr[x]*sin(tmp));
		}

		re[i] = sum_re;
		im[i] = sum_im;
	}

	if (dir == -1) {
		for (i = 0; i < N; i++) {
			re[i] /= (double)N;
			im[i] /= (double)N;
		}
	}

	delete [] tr, ti;
}

void FFT1d(double* re, double* im, int N, int dir)
{
	register int i, j, k;

	// 입력 데이터의 순서 바꾸기
	int n2 = N >> 1;
	int nb = 0;

	while (N != (1 << nb)) nb++;

	for (i = 0, j = 0; i < N-1; i++) {
		if (i < j) {
			swap(re[i], re[j]);
			swap(im[i], im[j]);
		}
		k = n2;

		while (k <= j) {
			j -= k;
			k >>= 1;
		}

		j += k;
	}

	// Butterfly algorithm
	int i1, l, l1, l2;
	double c1, c2, t1, t2, u1, u2, z;

	c1 = -1.0;
	c2 = 0.0;
	l2 = 1;

	for (l = 0; l < nb; l++) {
		l1 = l2;
		l2 <<= 1;
		u1 = 1.0;
		u2 = 0.0;

		for (j = 0; j < l1; j++) {
			for (i = j; i < N; i += l2) {
				i1 = i + l1;
				t1 = u1 * re[i1] - u2 * im[i1];
				t2 = u1 * im[i1] + u2 * re[i1];
				re[i1] = re[i] - t1;
				im[i1] = im[i] - t2;
				re[i] += t1;
				im[i] += t2;
			}
			
			z = u1 * c1 - u2 * c2;
			u2 = u1 * c2 + u2 * c1;
			u1 = z;
		}

		c2 = sqrt((1.0 - c1) / 2.0);
		if (dir == 1) { // forward
			c2 = -c2;
		}
		c1 = sqrt((1.0+c1) / 2.0);
	}

	// Scaling for backward transform
	if (dir == -1) {
		for (i = 0; i < N; i++) {
			re[i] /= (double)N;
			im[i] /= (double)N;
		}
	}
}

BOOL IsPowerOf2(int n)
{
	int ref = 1;

	while (ref < n) ref <<= 1;

	if (ref == n) return TRUE;
	else return FALSE;
}