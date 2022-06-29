#include "stdafx.h"
#include "Enhancement.h"

void Histogram(CImage* image, float histo[256])
{
	register int i, j;

	int w = image->GetWidth();
	int h = image->GetHeight();

	int tmp[256];
	memset(tmp,0,sizeof(int)*256);

	for (j = 0; j < h; j++) {
		for (i = 0; i < w; i++) {
			tmp[(image->GetPixel(j,i)>>16)]++;
		}
	}

	float area = (float)w*h;
	for (i = 0; i < 256; i++) {
		histo[i] = tmp[i] / area;
	}
}

void HistEqul(CImage* image, CImage* obj)
{
	register int i, j;
	float hist[256];

	int w = image->GetWidth();
	int h = image->GetHeight();
	obj->Create(w,h,24);

	int count[256];
	memset(count, 0, sizeof(int)*256);
	for (j = 0; j < h; j++)
	{
		for (i = 0; i < w; i++)
		{
			count[(image->GetPixel(j,i) >> 16)]++;
		}
	}

	float area = (float)w*h;
	for (i = 0; i < 256; i++)
	{
		hist[i] = count[i] / area;
	}

	double cdf[256] = {0.0, };
	cdf[0] = hist[0];
	for (i = 1; i < 256; i++)
	{
		cdf[i] = cdf[i-1] + hist[i];
	}

	int value = 0;

	for (j = 0; j < h; j++)
	{
		for (i = 0; i < w; i++)
		{
			value = cdf[(image->GetPixel(j,i) >> 16)] * 255;
			if (value > 255) value = 255;
			else if (value < 0) value = 0;
			value += (value << 16) + (value << 8);
			obj->SetPixel(j, i, value);
		}
	}
}