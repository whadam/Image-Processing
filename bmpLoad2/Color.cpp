#include "stdafx.h"
#include "Color.h"
#include "Filter.h"
#include "bmpLoad2Dlg.h"
#include "Enhancement.h"

#include <math.h>

#define RGB2GRAY(r, g, b) (int)(0.299*(r) + 0.587*(g) + 0.114*(b))
const double PI = acos(-1.0);

void Grayscale(CImage* image, CImage* obj, int w, int h)
{
	register int i,j;

	obj->Create(w,h,24);
	
	BYTE r, g ,b;
	for (j = 0; j < h; j++) {
		for (i = 0; i < w; i++) {
			r = image->GetPixel(j,i);
			g = image->GetPixel(j,i) >> 8;
			b = image->GetPixel(j,i) >> 16;

			obj->SetPixel(j,i,limit(RGB2GRAY(r,g,b)));
		}
	}
}

void RGB_TO_HSI(double R, double G, double B, double& H, double& S, double& I)
{
	I = (R+G+B) / 3;

	if ((R == G) && (G == B)) { // GRAYSCALE인 경우
		S = 0;
		H = 0;
	}
	else {
		double min_rgb, temp;

		min_rgb = min(min(R,G), B);

		S = 1 - (min_rgb / I);
		temp = ((R-G)+(R-B)) / (2*sqrt((R-G)*(R-G) + (R-B)*(G-B)));

		H = acos(temp)*180 / PI;

		if (B > G) H = 360 - H;

		H /= 360;
	}
}

void HSI_TO_RGB(double H, double S, double I, double& R, double& G, double& B)
{
	if (I == 0.0) { // 검정색
		R = 0.0;
		G = 0.0;
		B = 0.0;
		return;
	}

	if (S == 0.0) { // grayscale
		R = I;
		G = I;
		B = I;
		return;
	}

	H *= 360; // [0,1] 범위를 [0,360] 각도 범위로 변경

	if (H <= 120) {
		B = I*(1-S);
		R = I*(1 + S*cos(H*PI/180)/cos((60-H)*PI/180));
		R = limit(R, 0., 1.);
		G = 3*I - (R+B);
	}
	else if (H <= 240) {
		H -= 120;

		R = I*(1-S);
		G = I*(1+S*cos(H*PI/180)/cos((60-H)*PI/180));
		G = limit(G, 0., 1.);
		B = 3*I - (R+G);
	}
	else {
		H -= 240;

		G = I*(1-S);
		B = I*(1+S*cos(H*PI/180)/cos((60-H)*PI/180));
		B = limit(B, 0., 1.);
		R = 3*I - (G+B);
	}
}

void RGB_TO_YUV(BYTE R, BYTE G, BYTE B, BYTE& Y, BYTE& U, BYTE& V)
{
	Y = 0.299*R + 0.587*G + 0.144*B + 0.5;
	U = -0.169*R - 0.331*G + 0.500*B + 128 + 0.5;
	V = 0.500*R - 0.419*G - 0.081*B + 128 + 0.5;
}

void YUV_TO_RGB(BYTE Y, BYTE U, BYTE V, BYTE& R, BYTE& G, BYTE& B)
{
	R = limit((int)(Y + 1.4075*(V-128) + 0.5));
	G = limit((int)(Y - 0.3455*(U-128) - 0.7169*(V-128) + 0.5));
	B = limit((int)(Y + 1.7790*(U-128) + 0.5));
}

void ColorSplitRGB(CImage* image, std::vector<CImage*> objs, int w, int h, int cnt)
{
	register int i, j;
	unsigned char r, g, b;
	int pixel;

	for (i = cnt; i < cnt+3; i++)
		objs[i]->Create(w,h,24);

	for (j = 0; j < h; j++) {
		for (i = 0; i < w; i++) {
			pixel = image->GetPixel(j,i);
			r = pixel;
			g = pixel >> 8;
			b = pixel >> 16;

			objs[cnt]->SetPixel(j,i,limit((int)r));
			objs[cnt+1]->SetPixel(j,i,limit((int)g));
			objs[cnt+2]->SetPixel(j,i,limit((int)b));
		}
	}
}

void ColorSplitHSI(CImage* image, std::vector<CImage*> objs, int w, int h, int cnt)
{
	register int i, j;
	double r, g, b, hh, ss, ii;
	int pixel;

	for (i = cnt; i < cnt+3; i++)
		objs[i]->Create(w,h,24);

	for (j = 0; j < h; j++) {
		for (i = 0; i < w; i++) {
			pixel = image->GetPixel(j,i);
			r = (pixel & 0xFF) / 255.;
			g = ((pixel & 0xFF00) >> 8) / 255.;
			b = ((pixel & 0xFF0000) >> 16) / 255.;

			RGB_TO_HSI(r,g,b,hh,ss,ii);

			objs[cnt]->SetPixel(j,i,limit((int)(hh*255 + 0.5)));
			objs[cnt+1]->SetPixel(j,i,limit((int)(ss*255 + 0.5)));
			objs[cnt+2]->SetPixel(j,i,limit((int)(ii*255 + 0.5)));
		}
	}
}

void ColorSplitYUV(CImage* image, std::vector<CImage*> objs, int w, int h, int cnt)
{
	register int i, j;
	BYTE r, g, b, y, u, v;
	int pixel;

	for (i = cnt; i < cnt+3; i++)
		objs[i]->Create(w,h,24);

	for (j = 0; j < h; j++)
	{
		for (i = 0; i < w; i++)
		{
			pixel = image->GetPixel(j,i);
			r = pixel & 0xFF;
			g = (pixel & 0xFF00) >> 8;
			b = (pixel & 0xFF0000) >> 16;

			RGB_TO_YUV(r,g,b,y,u,v);
			objs[cnt]->SetPixel(j,i,limit(y));
			objs[cnt+1]->SetPixel(j,i,limit(u));
			objs[cnt+2]->SetPixel(j,i,limit(v));
		}
	}
}

void ColorCombineRGB(std::vector<CImage*> objs, int w, int h, int cnt)
{
	register int i, j;
	BYTE r,g,b;

	objs[cnt]->Create(w,h,24);

	for (j = 0; j < h; j++)
	{
		for (i = 0; i < w; i++)
		{
			r = objs[cnt-3]->GetPixel(j,i);
			g = objs[cnt-2]->GetPixel(j,i);
			b = objs[cnt-1]->GetPixel(j,i);

			objs[cnt]->SetPixelRGB(j,i,r,g,b);
		}
	}
}

void ColorCombineHSI(std::vector<CImage*> objs, int w, int h, int cnt)
{
	register int i, j;
	double r,g,b,hh,ss,ii;

	objs[cnt]->Create(w,h,24);

	for (j = 0; j < h; j++)
	{
		for (i = 0; i < w; i++)
		{
			hh = (double) (objs[cnt-3]->GetPixel(j,i) >> 16) / 255.;
			ss = (double) (objs[cnt-2]->GetPixel(j,i) >> 16) / 255.;
			ii = (double) (objs[cnt-1]->GetPixel(j,i) >> 16) / 255.;

			HSI_TO_RGB(hh,ss,ii,r,g,b);
			r = r*255 + 0.5;
			g = g*255 + 0.5;
			b = b*255 + 0.5;
			objs[cnt]->SetPixelRGB(j,i,limit((int)r),limit((int)g),limit((int)b));
		}
	}
}

void ColorCombineYUV(std::vector<CImage*> objs, int w, int h, int cnt)
{
	register int i, j;
	BYTE y,u,v,r,g,b;

	objs[cnt]->Create(w,h,24);

	for (j = 0; j < h; j++)
	{
		for (i = 0; i < w; i++)
		{
			y = objs[cnt-3]->GetPixel(j,i)>>16;
			u = objs[cnt-2]->GetPixel(j,i)>>16;
			v = objs[cnt-1]->GetPixel(j,i)>>16;
			YUV_TO_RGB(y,u,v,r,g,b);

			objs[cnt]->SetPixelRGB(j,i,r,g,b);
		}
	}
}

void ColorEdge(std::vector<CImage*> objs, int w, int h, int cnt)
{
	register int i, j;

	CImage tmp1, tmp2, tmp3;
	
	fnEdgePrewitt(objs[cnt-3], &tmp1, w, h);
	fnEdgePrewitt(objs[cnt-2], &tmp2, w, h);
	fnEdgePrewitt(objs[cnt-1], &tmp3, w, h);

	objs[cnt]->Create(w,h,24);

	int pixel;
	for (j = 0; j < h; j++)
	{
		for (i = 0; i < w; i++)
		{
			pixel = CalcDist(tmp1.GetPixel(j,i)>>16, (tmp2.GetPixel(j,i)>>16) * 0.5, (tmp3.GetPixel(j,i)>>16) * 0.5);
			objs[cnt]->SetPixel(j,i,limit(pixel));
		}
	}
}

double CalcDist(double x, double y, double z)
{
	return sqrt(x*x + y*y + z*z);
}

void ColorHistEqual(std::vector<CImage*> objs, int w, int h, int cnt)
{
	fnHistEqual(objs[cnt-3], objs[cnt-3], w, h);

	ColorCombineYUV(objs, w, h, cnt);
}