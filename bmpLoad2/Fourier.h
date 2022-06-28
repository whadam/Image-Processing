#pragma once

class Fourier
{
public:
	Fourier(void);
	~Fourier(void);

public:
	int w, h;

	double** pRe;
	double** pIm;

public:
	int limit(int pixel);
	void SetImage(CImage* img);
	void GetImage(CImage* img);
	void GetSpectrumImage(CImage* img);
	void GetphaseImage(CImage* img);

	void DFT(int dir);
	void DFTRC(int dir);
	void FFT(int dir);

	void IdealLowpass(int cutoff);
	void IdealHighpass(int cutoff);
	void GaussianLowpass(int cutoff);
	void GaussianHighpass(int cutoff);

protected:
	void Free();
};

void DFT1d(double* re, double* im, int N, int dir);
void FFT1d(double* re, double* im, int N, int dir);
BOOL IsPowerOf2(int n);

template<typename T> 
inline void swap(T& lha, T& rha)
{
	T tmp = lha;
	lha = rha;
	rha = tmp;
}