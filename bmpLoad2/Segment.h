#pragma once
#include <atlimage.h>

#define MAX_LABEL 10000

void Binarization(CImage*, CImage*, int);
int BinarizationIterative(CImage*);

int Labeling(CImage*);