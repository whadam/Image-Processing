
// bmpLoad2Dlg.h : 헤더 

#pragma once
#include "Image.h"
#include <vector>

// CbmpLoad2Dlg 대화 상자
class CbmpLoad2Dlg : public CDialogEx
{
// 생성입니다.
public:
	CbmpLoad2Dlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = 102 };

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
	CImage image;
	std::vector <CImage*> m_images;
	std::vector <Image*> m_dlgs;
	int w, h, cnt;

	void show(CImage* img);
	void CreateDlg(char*);
	void CreateDlg(char*, char*, char*);
	void reset();

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
	afx_msg void OnBnClickedBtnSaltpepper();
	afx_msg void OnBnClickedBtnMedean();
	afx_msg void OnBnClickedBtnDiffusion();
	afx_msg void OnBnClickedBtnAnd();
	afx_msg void OnBnClickedBtnTranslate();
	afx_msg void OnBnClickedBtnResize();
	afx_msg void OnBnClickedBtnRotate();
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
	afx_msg void OnBnClickedBtnHarris();
	afx_msg void OnBnClickedBtnGrayscale();
	afx_msg void OnBnClickedBtnSplitRgb();
	afx_msg void OnBnClickedBtnSplitHsi();
	afx_msg void OnBnClickedBtnSplitYuv();
	afx_msg void OnBnClickedBtnCombineRgb();
	afx_msg void OnBnClickedBtnCombineHsi();
	afx_msg void OnBnClickedBtnCombineYuv();
	afx_msg void OnBnClickedBtnColorEdge();
	afx_msg void OnBnClickedBtnColorHistEq();
	afx_msg void OnBnClickedBtnBinarize();
	afx_msg void OnBnClickedBtnBinarizationIter();
	afx_msg void OnBnClickedBtnLabeling();
	afx_msg void OnBnClickedBtnContourTracing();
	afx_msg void OnBnClickedBtnMorphErosion();
	afx_msg void OnBnClickedBtnMorphDilation();
	afx_msg void OnBnClickedBtnMorphOpening();
	afx_msg void OnBnClickedBtnMorphClosing();
	afx_msg void OnBnClickedBtnMorphGrayErosion();
	afx_msg void OnBnClickedBtnMorphGrayDilation();
	afx_msg void OnBnClickedBtnMorphGrayOpening();
	afx_msg void OnBnClickedBtnMorphGrayClosing();
};

template<typename T>
inline T limit(const T& value, const T& lower, const T& upper)
{
	return ((value > upper) ? upper : ((value < lower) ? lower : value));
}