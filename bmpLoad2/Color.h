#pragma once
#include <vector>

void Grayscale(CImage*, CImage*, int, int);

void RGB_TO_HSI(double R, double G, double B, double& H, double& S, double& I);
void HSI_TO_RGB(double H, double S, double I, double& R, double& G, double& B);

void RGB_TO_YUV(BYTE R, BYTE G, BYTE B, BYTE& Y, BYTE& U, BYTE& V);
void YUV_TO_RGB(BYTE Y, BYTE U, BYTE V, BYTE& R, BYTE& G, BYTE& B);

void ColorSplitRGB(CImage* image, std::vector<CImage*> objs, int w, int h, int cnt);
void ColorSplitHSI(CImage* image, std::vector<CImage*> objs, int w, int h, int cnt);
void ColorSplitYUV(CImage* image, std::vector<CImage*> objs, int w, int h, int cnt);

void ColorCombineRGB(std::vector<CImage*> objs, int w, int h, int cnt);
void ColorCombineHSI(std::vector<CImage*> objs, int w, int h, int cnt);
void ColorCombineYUV(std::vector<CImage*> objs, int w, int h, int cnt);

void ColorEdge(std::vector<CImage*> objs, int w, int h, int cnt);
double CalcDist(double, double, double);

void ColorHistEqual(std::vector<CImage*> objs, int w, int h, int cnt);