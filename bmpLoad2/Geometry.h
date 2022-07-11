#pragma once

void fnTranslate(CImage*, CImage*, int, int);

char* fnResize(CImage*, CImage*, int, int);
void fnResizeNearest(CImage*, CImage*, int w, int h, int nw, int nh);
void fnResizeBilinear(CImage*, CImage*, int, int, int nw, int nh);
void fnResizeCubic(CImage*, CImage*, int, int, int nw, int nh);
double fnCubic_interpolation(double v1, double v2, double v3, double v4, double d);

void fnRotate(CImage*, CImage*, int, int);
void fnRotate90(CImage*, CImage*, int, int);
void fnRotate180(CImage*, CImage*, int, int);
void fnRotate270(CImage*, CImage*, int, int);
void fnRotateAny(CImage*, CImage*, int, int, int);

void fnMirror(CImage*, CImage*, int, int);
void fnFlip(CImage*, CImage*, int, int);