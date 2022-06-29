
// bmpLoad2Dlg.h : 헤더 

#pragma once
#include "Image.h"
#include "Filter.h"
#include "Enhancement.h"

#define RGB2GRAY(r, g, b) (int)(0.299*(r) + 0.587*(g) + 0.114*(b))
//const int MAX_CORNER = 5000;

//typedef struct _LineParam {
//	double rho;	// 직선의 방정식의 ρ
//	double ang;	// theta θ
//} LineParam;
//
//typedef struct _CornerPoints {
//	int num;
//	int x[MAX_CORNER];
//	int y[MAX_CORNER];
//} CornerPoints;

// CbmpLoad2Dlg 대화 상자
class CbmpLoad2Dlg : public CDialogEx
{
// 생성입니다.
public:
	CbmpLoad2Dlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_BMPLOAD2_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_picture_control;
	CImage image, img1, img2, img3;
	Image* img;
	Image** arr;

	void show(CImage* img);

	afx_msg void OnBnClickedBtnImageopen();
	afx_msg void OnBnClickedBtnBrightness();
	afx_msg void OnBnClickedBtnContrast();
	afx_msg void OnBnClickedBntGamma();
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnBnClickedBtnHisteq();
	afx_msg void OnBnClickedBtnPlus();
	afx_msg void OnBnClickedBtnBitplane();
	afx_msg void OnBnClickedBtnRefresh();
	afx_msg void OnBnClickedBtnFiltermean();
	afx_msg void OnBnClickedBntGaussian();
	afx_msg void OnBnClickedBtnUnsharp();
	afx_msg void OnBnClickedBtnLaplacian();
	afx_msg void OnBnClickedBtnNoisegaussian();
	double GaussianRand(double mean, double std);
	afx_msg void OnBnClickedBtnSaltpepper();
	afx_msg void OnBnClickedBtnMedean();
	afx_msg void OnBnClickedBtnDiffusion();
	afx_msg void OnBnClickedBtnAnd();
	afx_msg void OnBnClickedBtnTranslate();
	afx_msg void OnBnClickedBtnResize();
	void Nearest(int w, int h, int nw, int nh);
	void Bilinear(int w, int h, int nw, int nh);
	void CubicConvolution(int w, int h, int nw, int nh);
	double cubic_interpolation(double v1, double v2, double v3, double v4, double d);
	afx_msg void OnBnClickedBtnRotate();
	void RotateAny(int angle, CImage* cpy);
	void Rotate90(CImage* cpy);
	void Rotate180(CImage* cpy);
	void Rotate270(CImage* cpy);
	afx_msg void OnBnClickedBtnMirror();
	afx_msg void OnBnClickedBtnFlip();
	afx_msg void OnBnClickedBtnDft();
	afx_msg void OnBnClickedBtnDftrc();
	afx_msg void OnBnClickedBtnFft();
	afx_msg void OnBnClickedBtnIdealLowpass();
	afx_msg void OnBnClickedBtnIdealHighpass();
	afx_msg void OnBnClickedBtnGaussianLowpass();
	afx_msg void OnBnClickedBtnGaussianHighpass();
	afx_msg void OnBnClickedBtnEdgeRobert();
	afx_msg void OnBnClickedBtnEdgePrewitt();
	afx_msg void OnBnClickedBtnEdgeSobel();
	afx_msg void OnBnClickedBtnHough();
	LineParam HoughLine();
	void DrawLine(CImage*, LineParam, BYTE);
	void DrawLine(CImage*, int, int, int, int, BYTE);
	afx_msg void OnBnClickedBtnHarris();
	CornerPoints HarrisCorner(int th);
	afx_msg void OnBnClickedBtnGrayscale();
	void RGB_TO_HSI(double, double, double, double&, double&, double&);
	void HSI_TO_RGB(double, double, double, double&, double&, double&);
	void RGB_TO_YUV(BYTE, BYTE, BYTE, BYTE&, BYTE&, BYTE&);
	void YUV_TO_RGB(BYTE, BYTE, BYTE, BYTE&, BYTE&, BYTE&);
	void InitImages();
	afx_msg void OnBnClickedBtnSplitRgb();
	afx_msg void OnBnClickedBtnSplitHsi();
	afx_msg void OnBnClickedBtnSplitYuv();
	afx_msg void OnBnClickedBtnCombineRgb();
	afx_msg void OnBnClickedBtnCombineHsi();
	afx_msg void OnBnClickedBtnCombineYuv();
	afx_msg void OnBnClickedBtnColorEdge();
	double CalcDist(double, double, double);
	afx_msg void OnBnClickedBtnColorHistEq();
	afx_msg void OnBnClickedBtnBinarize();
	afx_msg void OnBnClickedBtnBinarizationIter();
};

//template<typename T> 
//inline int limit(T pixel)
//{
//	if (pixel > 255) {
//		return (255 << 16) + (255 << 8) + 255;
//	}
//	else if (pixel < 0) return 0;
//	else {
//		return (pixel<<16) + (pixel<<8) + pixel;
//	}
//}

template<typename T>
inline T limit(const T& value, const T& lower, const T& upper)
{
	return ((value > upper) ? upper : ((value < lower) ? lower : value));
}