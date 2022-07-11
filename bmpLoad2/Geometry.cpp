#include "stdafx.h"
#include "Geometry.h"
#include "Filter.h"
#include "Translate.h"
#include "Resize.h"
#include "Rotate.h"

#include <math.h>

const double PI = acos(-1.0);

void fnTranslate(CImage* image, CImage* obj, int w, int h)
{
	Translate translate;

	if (translate.DoModal() == IDOK)
	{
		register int i, j;
		int x, y;

		obj->Create(w,h,24);

		for (j = 0; j < h; j++)
		{
			for (i = 0; i < w; i++)
			{
				x = i - translate.m_edit_y;
				y = j - translate.m_edit_x;
				if (x >= 0 && x < w && y >= 0 && y < h)
					obj->SetPixel(j,i,image->GetPixel(y,x));
			}
		}
	}
}

char* fnResize(CImage* image, CImage* obj, int w, int h)
{
	Resize resize;
	resize.m_oldWidth = image->GetWidth();
	resize.m_oldHeight = image->GetHeight();

	if (resize.DoModal() == IDOK)
	{
		int nw = resize.m_width;
		int nh = resize.m_height;
		obj->Create(nw,nh,24);

		if (resize.m_interpolation == 0) 
		{
			fnResizeNearest(image, obj, w, h, nw,nh);
			return "Resize Nearest";
		}
		else if (resize.m_interpolation == 1)
		{
			fnResizeBilinear(image, obj, w, h, nw,nh);
			return "Resie Bilinear";
		}
		else if (resize.m_interpolation == 2)
		{
			fnResizeCubic(image, obj, w, h, nw,nh);
			return "Resize Cubic Convolution";
		}
	}
	return nullptr;
}

void fnResizeNearest(CImage* image, CImage* obj, int w, int h, int nw, int nh)
{
	register int i, j;
	int x,y;

	for (j = 0; j < nh; j++)
	{
		for (i = 0; i < nw; i++)
		{
			x = (int)w*i/nw;
			y = (int)h*j/nh;

			obj->SetPixel(j,i,image->GetPixel(y,x));
		}
	}
}

void fnResizeBilinear(CImage* image, CImage* obj, int w, int h, int nw, int nh)
{
	register int i, j;
	int x1, x2, y1, y2;
	double rx, ry, p, q, temp;

	for (j = 0; j < nh; j++)
	{
		for (i = 0; i < nw; i++)
		{
			rx = (double)w*i/nw;
			ry = (double)h*j/nh;

			x1 = (int)rx;
			y1 = (int)ry;
			x2 = x1 + 1;
			if (x2 == w)
				x2 = w - 1;
			y2 = y1 + 1;
			if (y2 == h)
				y2 = h - 1;

			p = rx - x1;
			q = ry - y1;

			temp = (1.0-p) * (1.0-q) * (image->GetPixel(y1,x1) >> 16)
				+ p * (1.0-q) * (image->GetPixel(y1,x2) >> 16)
				+ (1.0-p) * q * (image->GetPixel(y2,x1) >> 16)
				+ p * q * (image->GetPixel(y2,x2) >> 16);
			obj->SetPixel(j,i,limit((int)temp));
		}
	}
}

void fnResizeCubic(CImage* image, CImage* obj, int w, int h, int nw, int nh)
{
	register int i, j;
	int x1, x2, x3, x4, y1, y2, y3, y4;
	double v1, v2, v3, v4, v, rx, ry, p, q;

	for (j = 0; j < nh; j++)
	{
		for (i = 0; i < nw; i++)
		{
			rx = (double)w*i/nw;
			ry = (double)h*j/nh;

			x2 = (int)rx;
			x1 = x2 - 1;
			if (x1 < 0) x1 = 0;
			x3 = x2 + 1;
			if (x3 >= w) x3 = w - 1;
			x4 = x2 + 2;
			if (x4 >= w) x4 = w - 1;
			p = rx - x2;

			y2 = (int)ry;
			y1 = y2 - 1;
			if (y1 < 0) y1 = 0;
			y3 = y2 + 1;
			if (y3 >= h) y3 = h - 1;
			y4 = y2 + 2;
			if (y4 >= h) y4 = h - 1;
			q = ry - y2;

			v1 = fnCubic_interpolation((image->GetPixel(y1,x1) >> 16),(image->GetPixel(y1,x2) >> 16),(image->GetPixel(y1,x3) >> 16),(image->GetPixel(y1,x4) >> 16), p);
			v2 = fnCubic_interpolation((image->GetPixel(y2,x1) >> 16),(image->GetPixel(y2,x2) >> 16),(image->GetPixel(y2,x3) >> 16),(image->GetPixel(y2,x4) >> 16), p);
			v3 = fnCubic_interpolation((image->GetPixel(y3,x1) >> 16),(image->GetPixel(y3,x2) >> 16),(image->GetPixel(y3,x3) >> 16),(image->GetPixel(y3,x4) >> 16), p);
			v4 = fnCubic_interpolation((image->GetPixel(y4,x1) >> 16),(image->GetPixel(y4,x2) >> 16),(image->GetPixel(y4,x3) >> 16),(image->GetPixel(y4,x4) >> 16), p);

			v = fnCubic_interpolation(v1,v2,v3,v4,q);
			obj->SetPixel(j,i, limit((int)v));
		}
	}
}

double fnCubic_interpolation(double v1, double v2, double v3, double v4, double d)
{
	double v, p1, p2, p3, p4;

	p1 = v2;
	p2 = -v1 + v3;
	p3 = 2*(v1-v2) + v3 - v4;
	p4 = -v1 + v2 -v3 + v4;

	v = p1 + d*(p2 + d*(p3 + d*p4));

	return v;
}

void fnRotate(CImage* image, CImage* obj, int w, int h)
{
	Rotate rotate;

	if (rotate.DoModal() == IDOK)
	{
		int angle = rotate.m_angel;

		obj->Create(w,h,24);

		switch (rotate.m_rotate)
		{
		case 0:
			fnRotate90(image, obj, w, h);
			break;
		case 1:
			fnRotate180(image, obj, w, h);
			break;
		case 2:
			fnRotate270(image, obj, w, h);
			break;
		case 3:
			fnRotateAny(image, obj, w, h, angle);
		}
	}
}

void fnRotate90(CImage* image, CImage* obj, int w, int h)
{
	register int i, j;
	int pixel;

	for (i = 0; i < w; i++)
	{
		for (j = 0; j < h; j++)
		{
			pixel = image->GetPixel(i,j);
			obj->SetPixel(h-1-j,i,pixel);
		}
	}
}

void fnRotate180(CImage* image, CImage* obj, int w, int h)
{
	register int i, j;
	int pixel;

	for (i = 0; i < w; i++)
	{
		for (j = 0; j < h; j++)
		{
			pixel = image->GetPixel(i,j);
			obj->SetPixel(w-1-i, h-1-j,pixel);
		}
	}
}

void fnRotate270(CImage* image, CImage* obj, int w, int h)
{
	register int i, j;
	int pixel;

	for (i = 0; i < w; i++)
	{
		for (j = 0; j < h; j++)
		{
			pixel = image->GetPixel(i,j);
			obj->SetPixel(j,w-1-i,pixel);
		}
	}
}

void fnRotateAny(CImage* image, CImage* obj, int w, int h, int angle)
{
	register int i, j;

	double rad = (angle*PI)/180;
	double cos_value = cos(rad);
	double sin_value = sin(rad);

	int nx, ny, minx, miny, maxx, maxy, nw, nh;

	minx = maxx = miny = maxy = 0;

	nx = (int) floor(w*cos_value + 0.5);
	ny = (int) floor(w*sin_value + 0.5);
	minx = (minx < nx) ? minx:nx;
	maxx = (maxx > nx) ? maxx:nx;
	miny = (miny < ny) ? miny:ny;
	maxy = (maxy > ny) ? maxy:ny;

	nx = (int) floor(-h*sin_value + 0.5);
	ny = (int) floor(h*cos_value + 0.5);
	minx = (minx < nx) ? minx:nx;
	maxx = (maxx > nx) ? maxx:nx;
	miny = (miny < ny) ? miny:ny;
	maxy = (maxy > ny) ? maxy:ny;

	nx = (int) floor(w*cos_value - h*sin_value + 0.5);
	ny = (int) floor(w*sin_value + h*cos_value + 0.5);
	minx = (minx < nx) ? minx:nx;
	maxx = (maxx > nx) ? maxx:nx;
	miny = (miny < ny) ? miny:ny;
	maxy = (maxy > ny) ? maxy:ny;

	nw = maxx - minx;
	nh = maxy - miny;

	int x1, x2, y1, y2;
	double rx, ry, p, q, temp;
	obj->Destroy();
	obj->Create(nw, nh, 24);

	for (j = miny; j < maxy; j++) {
		for (i = minx; i < maxx; i++) {
			rx = i*cos_value + j*sin_value;
			ry = -i*sin_value + j*cos_value;

			if (rx < 0 || rx > w-1 || ry < 0 || ry > h-1) continue;

			x1 = (int)rx;
			y1 = (int)ry;

			x2 = x1+1;
			if (x2 == w) x2 = w-1;
			y2 = y1+1;
			if (y2 == h) y2 = h-1;

			p = rx - x1;
			q = ry - y1;

			temp = (1.0-p)*(1.0-q)*(image->GetPixel(y1,x1)>>16) + p*(1.0-q)*(image->GetPixel(y1,x2)>>16)
				+ (1.0-p)*q*(image->GetPixel(y2,x1)>>16) + p*q*(image->GetPixel(y2,x2)>>16);
			obj->SetPixel(j-miny, i-minx, limit((int)temp));
		}
	}
}

void fnMirror(CImage* image, CImage* obj, int w, int h)
{
	register int i, j;
	int pixel;

	obj->Create(w,h,24);

	for (i = 0; i < w; i++)
	{
		for (j = 0; j < h; j++)
		{
			pixel = image->GetPixel(i,j);
			obj->SetPixel(w-1-i,j,pixel);
		}
	}
}

void fnFlip(CImage* image, CImage* obj, int w, int h)
{
	register int i, j;
	int pixel;

	obj->Create(w,h,24);

	for (i = 0; i < w; i++)
	{
		for (j = 0; j < h; j++)
		{
			pixel = image->GetPixel(i,j);
			obj->SetPixel(i,h-1-j,pixel);
		}
	}
}