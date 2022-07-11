#pragma once

void fnBrightness(CImage*, CImage*, int, int);
void fnContrast(CImage*, CImage*, int, int);
void fnGamma(CImage*, CImage*, int, int);
void fnHistogram(CImage*, float[], int, int);
void fnHistEqual(CImage*, CImage*, int, int);

void fnAdd(CImage*, CImage*, int, int);
void fnAnd(CImage*, CImage*, int, int);

void fnBitPlane(CImage*, CImage*, int, int);