#include "stdafx.h"
#include "Enhancement.h"
#include "Filter.h"

#include "Brightness.h"
#include "Contrast.h"
#include "Gamma.h"
#include "BitPlane.h"

#include <math.h>

void fnBrightness(CImage* image, CImage* obj, int w, int h)
{
	Brightness brightness;

	if (brightness.DoModal() == IDOK)
	{
		// ¹à±â Ã³¸®
		register int i, j;

		int value = brightness.m_edit_brightness;
		int pixel = 0;
		obj->Create(w,h,24);

		for (i = 0; i < w; i++)
		{
			for (j = 0; j < h; j++)
			{
				pixel = image->GetPixel(i,j) >> 16;
				pixel += value;;
				obj->SetPixel(i,j,limit(pixel));
			}
		}
	}
}

void fnContrast(CImage* image, CImage* obj, int w, int h)
{
	Contrast contrast;

	if (contrast.DoModal() == IDOK)
	{
		register int i, j;

		int value = contrast.m_edit_contrast;
		int pixel;
		obj->Create(w,h,24);

		for (j = 0; j < h; j++) {
			for (i = 0; i < w; i++) {
				pixel = image->GetPixel(j,i) >> 16;
				pixel = pixel + (pixel-128)*value/100;
				obj->SetPixel(j,i,limit(pixel));
			}
		}
	}
}

void fnGamma(CImage* image, CImage* obj, int w, int h)
{
	Gamma gamma;

	if (gamma.DoModal() == IDOK)
	{
		register int i, j;
		float g = gamma.m_edit_gamma;
		float invgamma = 1.f / g;
		int pixel;

		obj->Create(w,h,24);

		for (j = 0; j < h; j++)
		{
			for (i = 0; i < w; i++)
			{
				pixel = image->GetPixel(j,i) >> 16;
				pixel = (int)(pow((pixel/255.f), invgamma) * 255 + 0.5f);
				obj->SetPixel(j,i,limit(pixel));
			}
		}
	}
}

void fnHistogram(CImage* image, float histo[256], int w, int h)
{
	register int i, j;

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

void fnHistEqual(CImage* image, CImage* obj, int w, int h)
{
	register int i, j;
	float hist[256];

	fnHistogram(image, hist, w, h);

	if (obj->IsNull())
		obj->Create(w,h,24);

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
			value = (int) (cdf[(image->GetPixel(j,i) >> 16)] * 255.);
			obj->SetPixel(j, i, limit(value));
		}
	}
}

void fnAdd(CImage* image, CImage* obj, int w, int h)
{
	CImage image2;
	image2.Load("hole2.bmp");
	if (w != image2.GetWidth() || h != image2.GetHeight())
		return;

	register int i, j;
	int pixel;

	obj->Create(w,h,24);

	for (i = 0; i < w; i++)
	{
		for (j = 0; j < h; j++)
		{
			pixel = (image->GetPixel(i,j) >> 16) + (image2.GetPixel(i,j) >> 16);
			obj->SetPixel(i, j, limit(pixel));
		}
	}
}

void fnAnd(CImage* image, CImage* obj, int w, int h)
{
	CImage image2;
	image2.Load("gray128.bmp");
	if (w != image2.GetWidth() || h != image2.GetHeight())
		return;

	register int i, j;
	int value = 0;
	obj->Create(w,h,24);

	for (j = 0; j < h; j++)
	{
		for (i = 0; i < w; i++)
		{
			value = image->GetPixel(j,i) & image2.GetPixel(j,i);
			obj->SetPixel(j,i,value);
		}
	}
}

void fnBitPlane(CImage* image, CImage* obj, int w, int h)
{
	BitPlane bitplane;

	if (bitplane.DoModal() == IDOK)
	{
		register int i, j;
		int pixel = 0;
		int getpixel = 0;
		int bit = bitplane.m_bit;
		if (bit > 8 || bit < 1)
			return;

		obj->Create(w,h,24);

		for (i = 0; i < w; i++)
		{
			for (j = 0; j < h; j++)
			{
				getpixel = image->GetPixel(i,j) >> 16;
				pixel = (getpixel & (1 << (bit-1))) ? 255 : 0;
				obj->SetPixel(i,j,limit(pixel));
			}
		}
	}
}