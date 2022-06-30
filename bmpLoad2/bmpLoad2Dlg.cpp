
// bmpLoad2Dlg.cpp : 구현 파일

#include "stdafx.h"
#include "bmpLoad2.h"
#include "bmpLoad2Dlg.h"
#include "afxdialogex.h"
#include "afxwin.h"

#include "Brightness.h"
#include "Contrast.h"
#include "Gamma.h"
#include "BitPlane.h"
#include "Gaussian.h"
#include "NoiseGaussian.h"
#include "SaltPepper.h"
#include "Diffusion.h"
#include "Translate.h"
#include "Resize.h"
#include "Rotate.h"
#include "Fourier.h"
#include "Freq_Space.h"
#include "Harris.h"
#include "Segment.h"
#include "Binarize.h"

#include <Windows.h>
#include <math.h>
#include <algorithm>
#include <string.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const double PI = acos(-1.0);


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CbmpLoad2Dlg 대화 상자

CbmpLoad2Dlg::CbmpLoad2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CbmpLoad2Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CbmpLoad2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC, m_picture_control);
}

BEGIN_MESSAGE_MAP(CbmpLoad2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_IMAGEOPEN, &CbmpLoad2Dlg::OnBnClickedBtnImageopen)
	ON_BN_CLICKED(IDC_BTN_BRIGHTNESS, &CbmpLoad2Dlg::OnBnClickedBtnBrightness)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CbmpLoad2Dlg::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_HISTEQ, &CbmpLoad2Dlg::OnBnClickedBtnHisteq)
	ON_BN_CLICKED(IDC_BTN_PLUS, &CbmpLoad2Dlg::OnBnClickedBtnPlus)
	ON_BN_CLICKED(IDC_BTN_BITPLANE, &CbmpLoad2Dlg::OnBnClickedBtnBitplane)
	ON_BN_CLICKED(IDC_BTN_REFRESH, &CbmpLoad2Dlg::OnBnClickedBtnRefresh)
	ON_BN_CLICKED(IDC_BTN_FILTERMEAN, &CbmpLoad2Dlg::OnBnClickedBtnFiltermean)
	ON_BN_CLICKED(IDC_BNT_GAUSSIAN, &CbmpLoad2Dlg::OnBnClickedBntGaussian)
	ON_BN_CLICKED(IDC_BTN_UNSHARP, &CbmpLoad2Dlg::OnBnClickedBtnUnsharp)
	ON_BN_CLICKED(IDC_BTN_LAPLACIAN, &CbmpLoad2Dlg::OnBnClickedBtnLaplacian)
	ON_BN_CLICKED(IDC_BTN_NOISEGAUSSIAN, &CbmpLoad2Dlg::OnBnClickedBtnNoisegaussian)
	ON_BN_CLICKED(IDC_BTN_SALTPEPPER, &CbmpLoad2Dlg::OnBnClickedBtnSaltpepper)
	ON_BN_CLICKED(IDC_BTN_MEDEAN, &CbmpLoad2Dlg::OnBnClickedBtnMedean)
	ON_BN_CLICKED(IDC_BTN_DIFFUSION, &CbmpLoad2Dlg::OnBnClickedBtnDiffusion)
	ON_BN_CLICKED(IDC_BTN_CONTRAST, &CbmpLoad2Dlg::OnBnClickedBtnContrast)
	ON_BN_CLICKED(IDC_BNT_GAMMA, &CbmpLoad2Dlg::OnBnClickedBntGamma)
	ON_BN_CLICKED(IDC_BTN_AND, &CbmpLoad2Dlg::OnBnClickedBtnAnd)
	ON_BN_CLICKED(IDC_BTN_TRANSLATE, &CbmpLoad2Dlg::OnBnClickedBtnTranslate)
	ON_BN_CLICKED(IDC_BTN_RESIZE, &CbmpLoad2Dlg::OnBnClickedBtnResize)
	ON_BN_CLICKED(IDC_BTN_ROTATE, &CbmpLoad2Dlg::OnBnClickedBtnRotate)
	ON_BN_CLICKED(IDC_BTN_MIRROR, &CbmpLoad2Dlg::OnBnClickedBtnMirror)
	ON_BN_CLICKED(IDC_BTN_FLIP, &CbmpLoad2Dlg::OnBnClickedBtnFlip)
	ON_BN_CLICKED(IDC_BTN_DFT, &CbmpLoad2Dlg::OnBnClickedBtnDft)
	ON_BN_CLICKED(IDC_BTN_DFTRC, &CbmpLoad2Dlg::OnBnClickedBtnDftrc)
	ON_BN_CLICKED(IDC_BTN_FFT, &CbmpLoad2Dlg::OnBnClickedBtnFft)
	ON_BN_CLICKED(IDC_BTN_IDEAL_LOWPASS, &CbmpLoad2Dlg::OnBnClickedBtnIdealLowpass)
	ON_BN_CLICKED(IDC_BTN_IDEAL_HIGHPASS, &CbmpLoad2Dlg::OnBnClickedBtnIdealHighpass)
	ON_BN_CLICKED(IDC_BTN_GAUSSIAN_LOWPASS, &CbmpLoad2Dlg::OnBnClickedBtnGaussianLowpass)
	ON_BN_CLICKED(IDC_BTN_GAUSSIAN_HIGHPASS, &CbmpLoad2Dlg::OnBnClickedBtnGaussianHighpass)
	ON_BN_CLICKED(IDC_BTN_EDGE_ROBERT, &CbmpLoad2Dlg::OnBnClickedBtnEdgeRobert)
	ON_BN_CLICKED(IDC_BTN_EDGE_PREWITT, &CbmpLoad2Dlg::OnBnClickedBtnEdgePrewitt)
	ON_BN_CLICKED(IDC_BTN_EDGE_SOBEL, &CbmpLoad2Dlg::OnBnClickedBtnEdgeSobel)
	ON_BN_CLICKED(IDC_BTN_HOUGH, &CbmpLoad2Dlg::OnBnClickedBtnHough)
	ON_BN_CLICKED(IDC_BTN_HARRIS, &CbmpLoad2Dlg::OnBnClickedBtnHarris)
	ON_BN_CLICKED(IDC_BTN_SPLIT_RGB, &CbmpLoad2Dlg::OnBnClickedBtnSplitRgb)
	ON_BN_CLICKED(IDC_BTN_SPLIT_HSI, &CbmpLoad2Dlg::OnBnClickedBtnSplitHsi)
	ON_BN_CLICKED(IDC_BTN_GRAYSCALE, &CbmpLoad2Dlg::OnBnClickedBtnGrayscale)
	ON_BN_CLICKED(IDC_BTN_SPLIT_YUV, &CbmpLoad2Dlg::OnBnClickedBtnSplitYuv)
	ON_BN_CLICKED(IDC_BTN_COMBINE_RGB, &CbmpLoad2Dlg::OnBnClickedBtnCombineRgb)
	ON_BN_CLICKED(IDC_BTN_COMBINE_HSI, &CbmpLoad2Dlg::OnBnClickedBtnCombineHsi)
	ON_BN_CLICKED(IDC_BTN_COMBINE_YUV, &CbmpLoad2Dlg::OnBnClickedBtnCombineYuv)
	ON_BN_CLICKED(IDC_BTN_COLOR_EDGE, &CbmpLoad2Dlg::OnBnClickedBtnColorEdge)
	ON_BN_CLICKED(IDC_BTN_COLOR_HIST_EQ, &CbmpLoad2Dlg::OnBnClickedBtnColorHistEq)
	ON_BN_CLICKED(IDC_BTN_BINARIZE, &CbmpLoad2Dlg::OnBnClickedBtnBinarize)
	ON_BN_CLICKED(IDC_BTN_BINARIZATION_ITER, &CbmpLoad2Dlg::OnBnClickedBtnBinarizationIter)
	ON_BN_CLICKED(IDC_BTN_LABELING, &CbmpLoad2Dlg::OnBnClickedBtnLabeling)
	ON_BN_CLICKED(IDC_BTN_CONTOUR_TRACING, &CbmpLoad2Dlg::OnBnClickedBtnContourTracing)
	ON_BN_CLICKED(IDC_BTN_MORPH_EROSION, &CbmpLoad2Dlg::OnBnClickedBtnMorphErosion)
	ON_BN_CLICKED(IDC_BTN_MORPH_DILATION, &CbmpLoad2Dlg::OnBnClickedBtnMorphDilation)
	ON_BN_CLICKED(IDC_BTN_MORPH_OPENING, &CbmpLoad2Dlg::OnBnClickedBtnMorphOpening)
	ON_BN_CLICKED(IDC_BTN_MORPH_CLOSING, &CbmpLoad2Dlg::OnBnClickedBtnMorphClosing)
	ON_BN_CLICKED(IDC_BTN_MORPH_GRAY_EROSION, &CbmpLoad2Dlg::OnBnClickedBtnMorphGrayErosion)
	ON_BN_CLICKED(IDC_BTN_MORPH_GRAY_DILATION, &CbmpLoad2Dlg::OnBnClickedBtnMorphGrayDilation)
	ON_BN_CLICKED(IDC_BTN_MORPH_GRAY_OPENING, &CbmpLoad2Dlg::OnBnClickedBtnMorphGrayOpening)
	ON_BN_CLICKED(IDC_BTN_MORPH_GRAY_CLOSING, &CbmpLoad2Dlg::OnBnClickedBtnMorphGrayClosing)
END_MESSAGE_MAP()


// CbmpLoad2Dlg 메시지 처리기

BOOL CbmpLoad2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	arr = new Image*[3];

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CbmpLoad2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CbmpLoad2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CbmpLoad2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CbmpLoad2Dlg::show(CImage* img)
{
	CDC* dc;
	dc = m_picture_control.GetDC();
	img->BitBlt(dc->m_hDC, 0,0, SRCCOPY);
	ReleaseDC(dc);
}

void CbmpLoad2Dlg::OnBnClickedBtnImageopen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!image.IsNull())
	{
		image.Destroy();
	}
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, NULL);
	char path[128];
	GetCurrentDirectory(128, path);
	dlg.m_ofn.lpstrInitialDir = path;

	CString filename;
	if (IDOK == dlg.DoModal())
	{
		filename = dlg.GetFileName();
	}
	else return;

	image.Load(CT2CA(filename));

	show(&image);
}

void CbmpLoad2Dlg::OnBnClickedBtnRefresh()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!image.IsNull())
		image.Destroy();
	//image.Load("lenna.bmp");
	image.Load("peppers.bmp");
	show(&image);
}

void CbmpLoad2Dlg::OnBnClickedBtnSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	image.Save("result.bmp", Gdiplus::ImageFormatBMP);
}

void CbmpLoad2Dlg::OnBnClickedBtnBrightness()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Brightness brightness;

	if (brightness.DoModal() == IDOK)
	{
		// 밝기 처리
		register int i, j;

		int value = brightness.m_edit_brightness;
		int pixel = 0;

		int w = image.GetWidth();
		int h = image.GetHeight();

		for (i = 0; i < w; i++)
		{
			for (j = 0; j < h; j++)
			{
				pixel = image.GetPixel(i,j) >> 16;
				pixel += value;
				if (pixel > 255) pixel = 255;
				else if (pixel < 0) pixel = 0;
				pixel += (pixel << 16) + (pixel << 8);
				image.SetPixel(i,j,pixel);
			}
		}

		show(&image);
	}
}

void CbmpLoad2Dlg::OnBnClickedBtnContrast()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Contrast contrast;

	if (contrast.DoModal() == IDOK)
	{
		register int i, j;

		int a = contrast.m_edit_contrast;
		unsigned char pixel;
		int value;

		int w = image.GetWidth();
		int h = image.GetHeight();

		for (j = 0; j < h; j++) {
			for (i = 0; i < w; i++) {
				pixel = image.GetPixel(j,i);
				value = pixel + (pixel-128)*a/100;
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				value += (value << 16) + (value << 8);
				image.SetPixel(j,i,value);
			}
		}

		show(&image);
	}
}

void CbmpLoad2Dlg::OnBnClickedBntGamma()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Gamma gamma;

	if (gamma.DoModal() == IDOK)
	{
		register int i, j;
		float g = gamma.m_edit_gamma;

		float invgamma = 1.f / g;

		int w = image.GetWidth();
		int h = image.GetHeight();

		int pixel;
		for (j = 0; j < h; j++) {
			for (i = 0; i < w; i++) {
				pixel = image.GetPixel(j,i) >> 16;
				pixel = pow((pixel/255.f), invgamma) * 255 + 0.5f;
				if (pixel > 255) pixel = 255;
				else if (pixel < 0) pixel = 0;
				pixel += (pixel << 16) + (pixel << 8);
				image.SetPixel(j,i,pixel);
			}
		}

		show(&image);
	}
}

void CbmpLoad2Dlg::OnBnClickedBtnHisteq()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	HistEqul(&image, &obj);

	img = new Image(this);
	img->Create(IDD_IMAGE);
	img->ShowWindow(SW_SHOW);
	img->show(&obj, "Histogram Equlize");
}

void CbmpLoad2Dlg::OnBnClickedBtnPlus()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	register int i, j;

	CImage image2;
	if (!image2.IsNull())
	{
		image2.Destroy();
	}
	image2.Load("hole2.bmp");

	int w = image.GetWidth();
	int h = image.GetHeight();

	if (w != image2.GetWidth() || h != image2.GetHeight())
	{
		return;
	}

	CImage result;
	result.Create(w,h,24);
	int value = 0;

	for (i = 0; i < w; i++)
	{
		for (j = 0; j < h; j++)
		{
			value = (image.GetPixel(i,j) >> 16) + (image2.GetPixel(i,j) >> 16);
			if (value > 255) value = 255;
			else if (value < 0) value = 0;
			value += (value << 16) + (value << 8);
			result.SetPixel(i, j, value);
		}
	}
	copy(&result, &image);
	show(&image);
}

void CbmpLoad2Dlg::OnBnClickedBtnAnd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	register int i, j;

	CImage image2;
	if (!image2.IsNull()) image2.Destroy();
	image2.Load("gray128.bmp");

	int w = image.GetWidth();
	int h = image.GetHeight();

	if (w != image2.GetWidth() || h != image2.GetHeight()) return;

	CImage result;
	result.Create(w,h,24);
	int value = 0;

	for (j = 0; j < h; j++) {
		for (i = 0; i < w; i++) {
			value = image.GetPixel(j,i) & image2.GetPixel(j,i);
			result.SetPixel(j,i,value);
		}
	}

	copy(&result, &image);

	show(&image);
}

void CbmpLoad2Dlg::OnBnClickedBtnBitplane()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BitPlane bitplane;

	if (bitplane.DoModal() == IDOK)
	{
		register int i, j;

		int w = image.GetWidth();
		int h = image.GetHeight();

		CImage result;
		copy(&image, &result);

		int pixel = 0;
		int getpixel = 0;
		int bit = bitplane.m_bit;
		for (i = 0; i < w; i++)
		{
			for (j = 0; j < h; j++)
			{
				getpixel = result.GetPixel(i,j) >> 16;
				pixel = (getpixel & (1 << bit-1)) ? 255 : 0;
				pixel += (pixel << 16) + (pixel << 8);
				image.SetPixel(i,j,pixel);
			}
		}

		show(&image);
	}
}

void CbmpLoad2Dlg::OnBnClickedBtnFiltermean()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	register int i, j;

	int w = image.GetWidth();
	int h = image.GetHeight();

	CImage result;
	copy(&image, &result);

	int temp;
	for (i = 1; i < w-1; i++) {
		for (j = 1; j < h-1; j++) {
			temp = 0;
			temp = (result.GetPixel(i-1,j-1) & 255) + (result.GetPixel(i-1,j) & 255) + (result.GetPixel(i-1,j+1) & 255) +
				(result.GetPixel(i,j-1) & 255) +	(result.GetPixel(i,j) & 255)	+ (result.GetPixel(i,j+1) & 255) +
				(result.GetPixel(i+1,j-1) & 255) + (result.GetPixel(i+1,j) & 255) + (result.GetPixel(i+1,j+1) & 255);
			temp = temp / 9. + 0.5;
			if (temp > 255) temp = 255;
			else if (temp < 0) temp = 0;
			temp += (temp << 16) + (temp << 8);
			image.SetPixel(i,j,temp);
		}
	}

	show(&image);
}

void CbmpLoad2Dlg::OnBnClickedBntGaussian()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Gaussian gaussian;

	if (gaussian.DoModal() == IDOK)
	{
		register int i,j,k,x;

		int w = image.GetWidth();
		int h = image.GetHeight();

		double sigma = gaussian.m_sigma;
		int dim = (int) max(3.0, 2*4*sigma + 1.0);
		if (dim % 2 == 0) dim++;
		int dim2 = (int) dim/2;

		double* pMask = new double[dim];
		for (i = 0; i < dim; i++) {
			x = i - dim2;
			pMask[i] = exp(-(x*x)/(2*sigma*sigma)) / (sqrt(2*PI)*sigma);
		}

		double** buf = new double*[h];
		for (i = 0; i < h; i++) {
			buf[i] = new double[w];
			memset(buf[i], 0, sizeof(double)*w);
		}

		double sum1, sum2;
		for (i = 0; i < w; i++) {
			for (j = 0; j < h; j++) {
				sum1 = sum2 = 0;

				for (k = 0; k < dim; k++) {
					x = k - dim2 + j;
					if (x >= 0 && x < h) {
						sum1 += pMask[k];
						sum2 += (pMask[k] * (image.GetPixel(x,i) >> 16));
					}
				}

				buf[j][i] = sum2 / sum1;
			}
		}

		int value = 0;
		for (j = 0; j < h; j++) {
			for (i = 0; i < w; i++) {
				sum1 = sum2 = 0;

				for (k = 0; k < dim; k++) {
					x = k - dim2 + i;
					if (x >= 0 && x < w) {
						sum1 += pMask[k];
						sum2 += (pMask[k] * buf[j][x]);
					}
				}
				value = sum2 / sum1;
				value += (value << 16) + (value << 8);
				image.SetPixel(j,i,value);
			}
		}

		show(&image);

		for (i = 0; i < h; i++) {
			delete [] buf[i];
		}
		delete [] pMask, buf;
	}
}

void CbmpLoad2Dlg::OnBnClickedBtnUnsharp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	register int i, j;

	int w = image.GetWidth();
	int h = image.GetHeight();

	CImage result;
	copy(&image, &result);

	int temp;
	for (i = 1; i < w-1; i++) {
		for (j = 1; j < h-1; j++) {
			temp = 5*(result.GetPixel(i,j) >> 16) - (result.GetPixel(i-1,j) >> 16) - (result.GetPixel(i,j-1) >> 16)
				- (result.GetPixel(i+1,j) >> 16) - (result.GetPixel(i,j+1) >> 16);
			if (temp > 255) temp = 255;
			else if (temp < 0) temp = 0;
			temp += (temp << 16) + (temp << 8);
			image.SetPixel(i,j,temp);
		}
	}

	show(&image);
}

void CbmpLoad2Dlg::OnBnClickedBtnLaplacian()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	register int i, j;

	int w = image.GetWidth();
	int h = image.GetHeight();

	CImage result;
	copy(&image, &result);

	int temp;
	for (j = 1; j < h-1; j++) {
		for (i = 1; i < w-1; i++) {
			temp = 4*(result.GetPixel(j,i) >> 16) - (result.GetPixel(j-1,i) >> 16) - (result.GetPixel(j,i+1) >> 16)
				- (result.GetPixel(j+1,i) >> 16) - (result.GetPixel(j,i-1) >> 16);
			if (temp > 255) temp = 255;
			else if (temp < 0) temp = 0;
			temp += (temp << 16) + (temp << 8);
			image.SetPixel(j,i,temp);
		}
	}

	show(&image);
}

void CbmpLoad2Dlg::OnBnClickedBtnNoisegaussian()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	NoiseGaussian NG;

	if (NG.DoModal() == IDOK)
	{
		register int i, j;

		int w = image.GetWidth();
		int h = image.GetHeight();

		double amount = NG.m_deviation;

		srand((unsigned)time(NULL));

		double rnd;
		int value;
		for (j = 0; j < h; j++) {
			for (i = 0; i < w; i++) {
				rnd = GaussianRand(0, amount);
				value = (image.GetPixel(j,i) >> 16) + rnd;
				value += (value << 16) + (value << 8);
				image.SetPixel(j,i,value);
			}
		}

		show(&image);
	}
}

double CbmpLoad2Dlg::GaussianRand(double mean, double std)
{
	double x1, x2, radius, factor, y1;
	static double y2;
	static int use_last = 0;

	if (use_last) {
		y1 = y2;
		use_last = 0;
	}
	else {
		do {
			x1 = 2.0 * rand() / RAND_MAX - 1.0;
			x2 = 2.0 * rand() / RAND_MAX - 1.0;
			radius = x1 * x1 + x2 * x2;
		} while (radius < 0.00000001 || radius >= 1.0);

		factor = sqrt((-2.0 * log(radius)) / radius);

		y1 = x1 * factor;
		y2 = x2 * factor;

		use_last = 1;
	}

	return (mean + y1*std);
}

void CbmpLoad2Dlg::OnBnClickedBtnSaltpepper()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SaltPepper SP;

	if (SP.DoModal() == IDOK)
	{
		register int i, j;

		int w = image.GetWidth();
		int h = image.GetHeight();

		double amount = SP.m_deviation;

		srand((unsigned)time(NULL));

		int rnd;
		for (j = 0; j < h; j++) {
			for (i = 0; i < w; i++) {
				rnd = (int) (rand() * 100 / RAND_MAX);

				if (rnd < amount/2) image.SetPixel(j,i,0);
				else if (rnd < amount) image.SetPixel(j,i,0xffffffff);
			}
		}

		show(&image);
	}
}

void CbmpLoad2Dlg::OnBnClickedBtnMedean()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	register int i, j;

	int w = image.GetWidth();
	int h = image.GetHeight();

	CImage img;
	copy(&image, &img);

	int m[9], pixel;
	for (j = 1; j < h-1; j++) {
		for (i = 1; i < w-1; i++) {
			m[0] = img.GetPixel(j-1,i-1) >> 16;
			m[1] = img.GetPixel(j-1,i) >> 16;
			m[2] = img.GetPixel(j-1,i+1) >> 16;
			m[3] = img.GetPixel(j,i-1) >> 16;
			m[4] = img.GetPixel(j,i) >> 16;
			m[5] = img.GetPixel(j,i+1) >> 16;
			m[6] = img.GetPixel(j+1,i-1) >> 16;
			m[7] = img.GetPixel(j+1,i) >> 16;
			m[8] = img.GetPixel(j+1,i+1) >> 16;

			std::sort(m, m+9);

			pixel = (m[4] << 16) + (m[4] << 8) + m[4];
			image.SetPixel(j,i,pixel);
		}
	}

	show(&image);
}

void CbmpLoad2Dlg::OnBnClickedBtnDiffusion()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Diffusion diffusion;

	if (diffusion.DoModal() == IDOK)
	{
		register int i, x, y;

		int w = image.GetWidth();
		int h = image.GetHeight();

		float lambda = diffusion.lambda;
		float k = diffusion.k;
		int iter = diffusion.iter;
		float k2 = k*k;

		float gradn, grads, grade, gradw;
		float gcn, gcs, gce, gcw;
		float tmp;

		float** cpy = new float*[h];
		for (i = 0; i < h; i++) {
			cpy[i] = new float[w];
			memset(cpy[i], 0, sizeof(float)*w);
		}

		float** buf = new float*[h];
		for (i = 0; i < h; i++) {
			buf[i] = new float[w];
			memset(buf[i], 0, sizeof(float)*w);
		}

		for (y = 0; y < h; y++) {
			for (x = 0; x < w; x++) {
				cpy[y][x] = buf[y][x] = (float) ((unsigned char)image.GetPixel(y,x));
			}
		}

		for (i = 0; i < iter; i++) {
			for (y = 1; y < h-1; y++) {
				for (x = 1; x < w-1; x++) {
					tmp = cpy[y][x];

					gradn = cpy[y-1][x] - tmp;
					grads = cpy[y+1][x] - tmp;
					grade = cpy[y][x-1] - tmp;
					gradw = cpy[y][x+1] - tmp;
					gcn = gradn / (1.0f + gradn*gradn/k2);
					gcs = grads / (1.0f + grads*grads/k2);
					gce = grade / (1.0f + grade*grade/k2);
					gcw = gradw / (1.0f + gradw*gradw/k2);

					buf[y][x] = cpy[y][x] + lambda*(gcn+gcs+gce+gcw);
				}
			}

			for (y = 0; y < h; y++) {
				memcpy(cpy[y], buf[y], sizeof(float)*w);
			}
		}

		for (y = 0; y < h; y++) {
			for (x = 0; x < w; x++) {
				i = buf[y][x];
				i += (i << 16) + (i << 8);
				image.SetPixel(y,x,i);
			}
		}

		show(&image);

		for (i = 0; i < h; i++) {
			delete [] buf[i], cpy[i];
		}
		delete [] buf, cpy;
	}
}

void CbmpLoad2Dlg::OnBnClickedBtnTranslate()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Translate translate;

	if (translate.DoModal() == IDOK)
	{
		register int i, j;

		int w = image.GetWidth();
		int h = image.GetHeight();

		CImage result;
		result.Create(w,h,24);

		int x, y;

		for (j = 0; j < h; j++) {
			for (i = 0; i < w; i++) {
				x = i - translate.m_edit_x;
				y = j - translate.m_edit_y;
				if (x >= 0 && x < w && y >= 0 && y < h) {
					result.SetPixel(j,i,image.GetPixel(y,x));
				}
			}
		}

		show(&result);
	}
}

void CbmpLoad2Dlg::OnBnClickedBtnResize()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Resize resize;
	resize.m_oldWidth = image.GetWidth();
	resize.m_oldHeight = image.GetHeight();

	if (resize.DoModal() == IDOK)
	{
		int w = image.GetWidth();
		int h = image.GetHeight();
		int nw = resize.m_width;
		int nh = resize.m_height;

		if (resize.m_interpolation == 0) Nearest(w,h,nw,nh);
		else if (resize.m_interpolation == 1) Bilinear(w,h,nw,nh);
		else if (resize.m_interpolation == 2) CubicConvolution(w,h,nw,nh);
	}
}

void CbmpLoad2Dlg::Nearest(int w, int h, int nw, int nh)
{
	register int i, j;

	obj.Create(nw,nh,24);

	int x,y;

	for (j = 0; j < nh; j++) {
		for (i = 0; i < nw; i++) {
			x = (int)w*i/nw;
			y = (int)h*j/nh;

			obj.SetPixel(j,i,image.GetPixel(y,x));
		}
	}

	copy(&obj, &image);

	show(&image);
}

void CbmpLoad2Dlg::Bilinear(int w, int h, int nw, int nh)
{
	register int i, j;

	obj.Create(nw,nh,24);

	int x1, x2, y1, y2;
	double rx, ry, p, q, temp;

	for (j = 0; j < nh; j++) {
		for (i = 0; i < nw; i++) {
			rx = (double)w*i/nw;
			ry = (double)h*j/nh;

			x1 = (int)rx;
			y1 = (int)ry;
			x2 = x1 + 1;
			if (x2 == w) x2 = w - 1;
			y2 = y1 + 1;
			if (y2 == h) y2 = h - 1;

			p = rx - x1;
			q = ry - y1;

			temp = (1.0-p) * (1.0-q) * (image.GetPixel(y1,x1) >> 16)
				+ p * (1.0-q) * (image.GetPixel(y1,x2) >> 16)
				+ (1.0-p) * q * (image.GetPixel(y2,x1) >> 16)
				+ p * q * (image.GetPixel(y2,x2) >> 16);
			x1 = temp;
			x1 += (x1 << 16) + (x1 << 8);
			obj.SetPixel(j,i,x1);
		}
	}

	copy(&obj, &image);

	show(&image);
}

void CbmpLoad2Dlg::CubicConvolution(int w, int h, int nw, int nh)
{
	register int i, j;

	obj.Create(nw,nh,24);

	int x1, x2, x3, x4, y1, y2, y3, y4;
	double v1, v2, v3, v4, v, rx, ry, p, q;

	for (j = 0; j < nh; j++) {
		for (i = 0; i < nw; i++) {
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

			v1 = cubic_interpolation((image.GetPixel(y1,x1) >> 16),(image.GetPixel(y1,x2) >> 16),(image.GetPixel(y1,x3) >> 16),(image.GetPixel(y1,x4) >> 16), p);
			v2 = cubic_interpolation((image.GetPixel(y2,x1) >> 16),(image.GetPixel(y2,x2) >> 16),(image.GetPixel(y2,x3) >> 16),(image.GetPixel(y2,x4) >> 16), p);
			v3 = cubic_interpolation((image.GetPixel(y3,x1) >> 16),(image.GetPixel(y3,x2) >> 16),(image.GetPixel(y3,x3) >> 16),(image.GetPixel(y3,x4) >> 16), p);
			v4 = cubic_interpolation((image.GetPixel(y4,x1) >> 16),(image.GetPixel(y4,x2) >> 16),(image.GetPixel(y4,x3) >> 16),(image.GetPixel(y4,x4) >> 16), p);

			v = cubic_interpolation(v1,v2,v3,v4,q);
			x1 = v;
			x1 += (x1 << 16) + (x1 << 8);
			obj.SetPixel(j,i,x1);
		}
	}

	copy(&obj, &image);

	show(&image);
}

double CbmpLoad2Dlg::cubic_interpolation(double v1, double v2, double v3, double v4, double d)
{
	double v, p1, p2, p3, p4;

	p1 = v2;
	p2 = -v1 + v3;
	p3 = 2*(v1-v2) + v3 - v4;
	p4 = -v1 + v2 -v3 + v4;

	v = p1 + d*(p2 + d*(p3 + d*p4));

	return v;
}

void CbmpLoad2Dlg::OnBnClickedBtnRotate()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Rotate rotate;

	if (rotate.DoModal() == IDOK)
	{
		int angle = rotate.m_angel;
		CImage cpy;

		switch (rotate.m_rotate) {
		case 0:
			Rotate90(&cpy);
			break;
		case 1:
			Rotate180(&cpy);
			break;
		case 2:
			Rotate270(&cpy);
			break;
		case 3:
			RotateAny(angle, &cpy);
		}

		copy(&cpy, &image);
		show(&image);
	}
}

void CbmpLoad2Dlg::RotateAny(int angle, CImage* cpy)
{
	register int i, j;

	int w = image.GetWidth();
	int h = image.GetHeight();

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

	cpy->Create(nw,nh,24);

	int x1, x2, y1, y2;
	double rx, ry, p, q, temp;

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

			temp = (1.0-p)*(1.0-q)*(image.GetPixel(y1,x1)>>16) + p*(1.0-q)*(image.GetPixel(y1,x2)>>16)
				+ (1.0-p)*q*(image.GetPixel(y2,x1)>>16) + p*q*(image.GetPixel(y2,x2)>>16);
			x1 = temp;
			x1 += (x1 << 16) + (x1 << 8);
			cpy->SetPixel(j-miny, i-minx, x1);
		}
	}
}

void CbmpLoad2Dlg::Rotate90(CImage* cpy)
{
	register int i, j;

	int w = image.GetWidth();
	int h = image.GetHeight();

	cpy->Create(h,w,24);

	int pixel;

	for (i = 0; i < w; i++) {
		for (j = 0; j < h; j++) {
			pixel = image.GetPixel(i,j);
			cpy->SetPixel(h-1-j,i,pixel);
		}
	}
}

void CbmpLoad2Dlg::Rotate180(CImage* cpy)
{
	register int i, j;

	int w = image.GetWidth();
	int h = image.GetHeight();

	cpy->Create(w,h,24);

	int pixel;

	for (i = 0; i < w; i++) {
		for (j = 0; j < h; j++) {
			pixel = image.GetPixel(i,j);
			cpy->SetPixel(w-1-i, h-1-j,pixel);
		}
	}
}

void CbmpLoad2Dlg::Rotate270(CImage* cpy)
{
	register int i, j;

	int w = image.GetWidth();
	int h = image.GetHeight();

	cpy->Create(h,w,24);

	int pixel;

	for (i = 0; i < w; i++) {
		for (j = 0; j < h; j++) {
			pixel = image.GetPixel(i,j);
			cpy->SetPixel(j,w-1-i,pixel);
		}
	}
}

void CbmpLoad2Dlg::OnBnClickedBtnMirror()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	register int i, j;

	int w = image.GetWidth();
	int h = image.GetHeight();

	CImage cpy;
	cpy.Create(w,h,24);

	int pixel;

	for (i = 0; i < w; i++) {
		for (j = 0; j < h; j++) {
			pixel = image.GetPixel(i,j);
			cpy.SetPixel(w-1-i,j,pixel);
		}
	}
	copy(&cpy, &image);
	show(&image);
}

void CbmpLoad2Dlg::OnBnClickedBtnFlip()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	register int i, j;

	int w = image.GetWidth();
	int h = image.GetHeight();

	CImage cpy;
	cpy.Create(w,h,24);

	int pixel;

	for (i = 0; i < w; i++) {
		for (j = 0; j < h; j++) {
			pixel = image.GetPixel(i,j);
			cpy.SetPixel(i,h-1-j,pixel);
		}
	}
	copy(&cpy, &image);
	show(&image);
}

void CbmpLoad2Dlg::OnBnClickedBtnDft()
{
	// 오래 걸림
	// disabled

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int w = image.GetWidth();
	int h = image.GetHeight();

	Fourier fourier;
	fourier.SetImage(&image);
	fourier.DFT(1);

	CImage cpy;
	cpy.Create(w,h,24);

	fourier.GetSpectrumImage(&cpy);
	img = new Image(this);
	img->Create(IDD_IMAGE);
	img->ShowWindow(SW_SHOW);
	img->show(&cpy, "Spectrum");

	fourier.GetphaseImage(&cpy);
	img = new Image(this);
	img->Create(IDD_IMAGE);
	img->ShowWindow(SW_SHOW);
	img->show(&cpy, "Phase");

	fourier.DFT(-1);
	fourier.GetImage(&cpy);
	img = new Image(this);
	img->Create(IDD_IMAGE);
	img->ShowWindow(SW_SHOW);
	img->show(&cpy, "IDFT");
}

void CbmpLoad2Dlg::OnBnClickedBtnDftrc()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int w = image.GetWidth();
	int h = image.GetHeight();

	Fourier fourier;
	fourier.SetImage(&image);
	fourier.DFTRC(1);

	CImage cpy;
	cpy.Create(w,h,24);

	fourier.GetSpectrumImage(&cpy);
	img = new Image(this);
	img->Create(IDD_IMAGE);
	img->ShowWindow(SW_SHOW);
	img->show(&cpy, "Spectrum");

	fourier.GetphaseImage(&cpy);
	img = new Image(this);
	img->Create(IDD_IMAGE);
	img->ShowWindow(SW_SHOW);
	img->show(&cpy, "Phase");

	fourier.DFTRC(-1);
	fourier.GetImage(&cpy);
	img = new Image(this);
	img->Create(IDD_IMAGE);
	img->ShowWindow(SW_SHOW);
	img->show(&cpy, "IDFTRC");
}

void CbmpLoad2Dlg::OnBnClickedBtnFft()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int w = image.GetWidth();
	int h = image.GetHeight();

	if (!IsPowerOf2(w) || !IsPowerOf2(h)) return;

	Fourier fourier;
	fourier.SetImage(&image);
	fourier.FFT(1);

	CImage cpy;
	cpy.Create(w,h,24);

	fourier.GetSpectrumImage(&cpy);
	img = new Image(this);
	img->Create(IDD_IMAGE);
	img->ShowWindow(SW_SHOW);
	img->show(&cpy, "Spectrum");

	fourier.GetphaseImage(&cpy);
	img = new Image(this);
	img->Create(IDD_IMAGE);
	img->ShowWindow(SW_SHOW);
	img->show(&cpy, "Phase");

	fourier.FFT(-1);
	fourier.GetImage(&cpy);
	img = new Image(this);
	img->Create(IDD_IMAGE);
	img->ShowWindow(SW_SHOW);
	img->show(&cpy, "IFFT");
}

void CbmpLoad2Dlg::OnBnClickedBtnIdealLowpass()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int w = image.GetWidth();
	int h = image.GetHeight();

	if (!IsPowerOf2(w) || !IsPowerOf2(h)) return;

	Freq_Space fs;
	fs.m_edit_type = "Lowpass Filter";
	fs.m_edit_shape = "Ideal";
	fs.m_radius_range.Format("(0 ~ %d)", min(w/2, h/2));

	if (fs.DoModal() == IDOK)
	{
		Fourier fourier;
		fourier.SetImage(&image);
		fourier.FFT(1);
		fourier.IdealLowpass(fs.m_edit_cutoff);
		fourier.FFT(-1);

		obj.Create(w,h,24);

		fourier.GetImage(&obj);
		img = new Image(this);
		img->Create(IDD_IMAGE);
		img->ShowWindow(SW_SHOW);
		img->show(&obj, "Ideal Lowpass Filtering");
	}
}

void CbmpLoad2Dlg::OnBnClickedBtnIdealHighpass()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int w = image.GetWidth();
	int h = image.GetHeight();

	if (!IsPowerOf2(w) || !IsPowerOf2(h)) return;

	Freq_Space fs;
	fs.m_edit_type = "Highpass Filter";
	fs.m_edit_shape = "Ideal";
	fs.m_radius_range.Format("(0 ~ %d)", min(w/2, h/2));

	if (fs.DoModal() == IDOK)
	{
		Fourier fourier;
		fourier.SetImage(&image);
		fourier.FFT(1);
		fourier.IdealHighpass(fs.m_edit_cutoff);
		fourier.FFT(-1);

		obj.Create(w,h,24);

		fourier.GetImage(&obj);
		img = new Image(this);
		img->Create(IDD_IMAGE);
		img->ShowWindow(SW_SHOW);
		img->show(&obj, "Ideal Highpass Filtering");
	}
}

void CbmpLoad2Dlg::OnBnClickedBtnGaussianLowpass()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int w = image.GetWidth();
	int h = image.GetHeight();

	if (!IsPowerOf2(w) || !IsPowerOf2(h)) return;

	Freq_Space fs;
	fs.m_edit_type = "Lowpass Filter";
	fs.m_edit_shape = "Gaussian";
	fs.m_radius_range.Format("(0 ~ %d)", min(w/2, h/2));

	if (fs.DoModal() == IDOK)
	{
		Fourier fourier;
		fourier.SetImage(&image);
		fourier.FFT(1);
		fourier.GaussianLowpass(fs.m_edit_cutoff);
		fourier.FFT(-1);

		obj.Create(w,h,24);

		fourier.GetImage(&obj);
		img = new Image(this);
		img->Create(IDD_IMAGE);
		img->ShowWindow(SW_SHOW);
		img->show(&obj, "Gaussian Lowpass Filtering");
	}
}

void CbmpLoad2Dlg::OnBnClickedBtnGaussianHighpass()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int w = image.GetWidth();
	int h = image.GetHeight();

	if (!IsPowerOf2(w) || !IsPowerOf2(h)) return;

	Freq_Space fs;
	fs.m_edit_type = "Highpass Filter";
	fs.m_edit_shape = "Gaussian";
	fs.m_radius_range.Format("(0 ~ %d)", min(w/2, h/2));

	if (fs.DoModal() == IDOK)
	{
		Fourier fourier;
		fourier.SetImage(&image);
		fourier.FFT(1);
		fourier.GaussianHighpass(fs.m_edit_cutoff);
		fourier.FFT(-1);

		obj.Create(w,h,24);

		fourier.GetImage(&obj);
		img = new Image(this);
		img->Create(IDD_IMAGE);
		img->ShowWindow(SW_SHOW);
		img->show(&obj, "Gaussian Highpass Filtering");
	}
}

void CbmpLoad2Dlg::OnBnClickedBtnEdgeRobert()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	register int i, j;

	int w = image.GetWidth();
	int h = image.GetHeight();

	obj.Create(w,h,24);

	int h1, h2;
	double hval;
	for (j = 1; j < h-1; j++) {
		for (i = 1; i < w-1; i++) {
			h1 = (image.GetPixel(j,i)>>16) - (image.GetPixel(j-1,i-1)>>16);
			h2 = (image.GetPixel(j,i)>>16) - (image.GetPixel(j-1,i+1)>>16);

			hval = sqrt((double)h1*h1 + h2*h2);

			obj.SetPixel(j,i,limit((int)hval));
		}
	}

	img = new Image(this);
	img->Create(IDD_IMAGE);
	img->ShowWindow(SW_SHOW);
	img->show(&obj, "Edge Robert");
}

void CbmpLoad2Dlg::OnBnClickedBtnEdgePrewitt()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	EdgePrewitt(&image, &obj);

	img = new Image(this);
	img->Create(IDD_IMAGE);
	img->ShowWindow(SW_SHOW);
	img->show(&obj, "Edge Prewitt");
}

void CbmpLoad2Dlg::OnBnClickedBtnEdgeSobel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	register int i, j;

	int w = image.GetWidth();
	int h = image.GetHeight();

	obj.Create(w,h,24);

	int h1, h2;
	double hval;
	for (j = 1; j < h-1; j++) {
		for (i = 1; i < w-1; i++) {
			h1 = (image.GetPixel(j+1,i-1)>>16) + 2*(image.GetPixel(j+1,i)>>16) + (image.GetPixel(j+1,i+1)>>16)
				- (image.GetPixel(j-1,i-1)>>16) - 2*(image.GetPixel(j-1,i)>>16) - (image.GetPixel(j-1,i+1)>>16);
			h2 = (image.GetPixel(j-1,i+1)>>16) + 2*(image.GetPixel(j,i+1)>>16) + (image.GetPixel(j+1,i+1)>>16)
				- (image.GetPixel(j-1,i-1)>>16) - 2*(image.GetPixel(j,i-1)>>16) - (image.GetPixel(j+1,i-1)>>16);

			hval = sqrt((double)h1*h1 + h2*h2);

			obj.SetPixel(j,i,limit((int)hval));
		}
	}

	img = new Image(this);
	img->Create(IDD_IMAGE);
	img->ShowWindow(SW_SHOW);
	img->show(&obj, "Edge Sobel");
}

void CbmpLoad2Dlg::OnBnClickedBtnHough()
{
	// 에러 있음
	// disabled

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int w = image.GetWidth();
	int h = image.GetHeight();

	obj.Create(w, h, 24);

	LineParam line = HoughLine();
	DrawLine(&obj, line, 255);

	img = new Image(this);
	img->Create(IDD_IMAGE);
	img->ShowWindow(SW_SHOW);
	img->show(&obj, "Hough");
}

LineParam CbmpLoad2Dlg::HoughLine()
{
	register int i, j;

	int w = image.GetWidth();
	int h = image.GetHeight();

	int num_rho = (int)(sqrt((double)w*w + h*h)*2);
	int num_ang = 360;

	// 0~PI 각도에 해당하는 sin, cos 함수의 값을 룩업테이블에 저장
	double* tsin = new double[num_ang];
	double* tcos = new double[num_ang];

	for (i = 0; i < num_rho; i++) {
		tsin[i] = (double)sin(i*PI/num_ang);
		tcos[i] = (double)cos(i*PI/num_ang);
	}

	// 축적 배열(accumulate array) 생성
	int** arr = new int*[num_rho];
	for (i = 0; i < num_rho; i++) {
		arr[i] = new int[num_ang];
		memset(arr[i], 0, sizeof(int)*num_ang);
	}

	int m,n;
	for (j = 0; j < h; j++) {
		for (i = 0; i < w; i++) {
			if ((image.GetPixel(j,i)>>16) > 128) {
				for (n = 0; n < num_ang; n++) {
					m = (int) floor(i*tsin[n] + j*tcos[n] + 0.5);
					m += (num_rho/2);

					arr[m][n]++;
				}
			}
		}
	}

	// 축적 배열에서 최대값 찾기
	LineParam line;
	line.rho = line.ang = 0;

	int arr_max = 0;
	for (m = 0; m < num_rho; m++) {
		for (n = 0; n < num_ang; n++) {
			if (arr[m][n] > arr_max) {
				arr_max = arr[m][n];
				line.rho = m - (num_rho/2);
				line.ang = n*180.0/num_ang;
			}
		}
	}

	// 동적 할당 메모리 해제
	delete [] tsin, tcos;
	for (i = 0; i < num_rho; i++) {
		delete [] arr[i];
	}
	delete arr;

	return line;
}

void CbmpLoad2Dlg::DrawLine(CImage* obj, LineParam line, BYTE c)
{
	register int x, y;

	int w = image.GetWidth();
	int h = image.GetHeight();

	// 수직선인 경우
	if (line.ang == 90) {
		x = (int)(line.rho + 0.5);

		for (y = 0; y < h; y++) {
			obj->SetPixel(y,x,limit(c));	// byte를 int로 형 변환하고 비트 시프트 해야하는지
		}

		return;
	}

	// (rho, ang) 파라미터를 이용하여 직선의 시작 좌표와 끝 좌표를 계산
	int x1 = 0;
	int y1 = (int) floor(line.rho / cos(line.ang*PI/180) + 0.5);
	int x2 = w - 1;
	int y2 = (int) floor((line.rho - x2*sin(line.ang*PI/180)) / cos(line.ang*PI/180) + 0.5);

	DrawLine(obj, x1, y1, x2, y2, c);
}

void CbmpLoad2Dlg::DrawLine(CImage* obj, int x1, int y1, int x2, int y2, BYTE c)
{
	register int x, y;
	double m;

	int w = image.GetWidth();
	int h = image.GetHeight();

	// 수직선인 경우
	if (x1 == x2) {
		if (y1 > y2) {
			swap(y1, y2);
		}

		for (y = y1; y <= y2; y++) {
			obj->SetPixel(y,x1,limit(c));
		}

		return;
	}

	// (x1, y1)에서 (x2, y2)까지 직선 그리기
	m = (double) (y2-y1)/(x2-x1);

	if ((m > -1) && (m < 1)) {
		if (x1 > x2) {
			swap(x1, x2);
			swap(y1, y2);
		}

		for (x = x1; x <= x2; x++) {
			y = (int)floor(m*(x-x1) + y1 + 0.5);
			if (y > 0 && y < h) {
				obj->SetPixel(y,x,limit(c));
			}
		}
	}
	else {
		if (y1 > y2) {
			swap(x1, x2);
			swap(y1, y2);
		}

		for (y = y1; y <= y2; y++) {
			x = (int)floor((y-y1) / m + x1 + 0.5);
			if (y >= 0 && y < h) {
				obj->SetPixel(y,x,limit(c));
			}
		}
	}
}

void CbmpLoad2Dlg::OnBnClickedBtnHarris()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Harris harris;

	if (harris.DoModal() == IDOK)
	{
		int th = harris.m_edit_threshold;
		CornerPoints cp;
		cp = HarrisCorner(th);

		obj.Create(image.GetWidth(), image.GetHeight(), 24);
		copy(&image, &obj);

		register int i, x, y;
		for (i = 0; i < cp.num; i++) {
			x = cp.x[i];
			y = cp.y[i];

			obj.SetPixel(y-1,x-1,0);
			obj.SetPixel(y-1,x,0);
			obj.SetPixel(y-1,x+1,0);
			obj.SetPixel(y,x-1,0);
			obj.SetPixel(y,x,0);
			obj.SetPixel(y,x+1,0);
			obj.SetPixel(y+1,x-1,0);
			obj.SetPixel(y+1,x,0);
			obj.SetPixel(y+1,x+1,0);
		}

		img = new Image(this);
		img->Create(IDD_IMAGE);
		img->ShowWindow(SW_SHOW);
		img->show(&obj, "Harris Corner Points");
	}
}

CornerPoints CbmpLoad2Dlg::HarrisCorner(int th)
{
	register int i, j, x, y;

	int w = image.GetWidth();
	int h = image.GetHeight();

	double** dx2 = new double*[h];
	double** dy2 = new double*[h];
	double** dxy = new double*[h];

	for (i = 0; i < h; i++) {
		dx2[i] = new double[w];
		dy2[i] = new double[w];
		dxy[i] = new double[w];
		memset(dx2[i], 0, sizeof(double)*w);
		memset(dy2[i], 0, sizeof(double)*w);
		memset(dxy[i], 0, sizeof(double)*w);
	}

	double tx, ty, tmp;
	tx = ty = tmp = 0;
	for (j = 1; j < h-1; j++) {
		for (i = 1; i < w-1; i++) {
			// GetPixel return type이 colorref이고 unsigned라 -가 나오면 매우 큰 값으로 바뀌어 하나씩 수행
			tx = image.GetPixel(j-1,i+1)>>16;
			tx += image.GetPixel(j,i+1)>>16;
			tx += image.GetPixel(j+1,i+1)>>16;
			tx -= image.GetPixel(j-1,i-1)>>16;
			tx -= image.GetPixel(j,i-1)>>16;
			tx -= image.GetPixel(j+1,i+1)>>16;
			tx /= 6.0;

			ty = image.GetPixel(j+1,i-1)>>16;
			ty += image.GetPixel(j+1,i)>>16;
			ty += image.GetPixel(j+1,i+1)>>16;
			ty -= image.GetPixel(j-1,i-1)>>16;
			ty -= image.GetPixel(j-1,i)>>16;
			ty -= image.GetPixel(j-1,i+1)>>16;
			ty /= 6.0;

			dx2[j][i] = tx*tx;
			tmp = ty * ty;
			dy2[j][i] = ty*ty;
			dxy[j][i] = tx*ty;
		}
	}

	// Gaussian Filtering
	double** gdx2 = new double*[h];
	double** gdy2 = new double*[h];
	double** gdxy = new double*[h];

	for (i = 0; i < h; i++) {
		gdx2[i] = new double[w];
		gdy2[i] = new double[w];
		gdxy[i] = new double[w];
		memset(gdx2[i], 0, sizeof(double)*w);
		memset(gdy2[i], 0, sizeof(double)*w);
		memset(gdxy[i], 0, sizeof(double)*w);
	}

	double g[5][5] = {{1,4,6,4,1}, {4,16,24,16,4}, {6,24,36,24,6}, {4,16,24,16,4}, {1,4,6,4,1}};

	for (y = 0; y < 5; y++) {
		for (x = 0; x < 5; x++) {
			g[y][x] /= 256.;
		}
	}

	double tx2, ty2, txy;
	for (j = 2; j < h-2; j++) {
		for (i = 2; i < w-2; i++) {
			tx2 = ty2 = txy = 0;

			for (y = 0; y < 5; y++) {
				for (x = 0; x < 5; x++) {
					tx2 += (dx2[j+y-2][i+x-2]*g[y][x]);
					ty2 += (dy2[j+y-2][i+x-2]*g[y][x]);
					txy += (dxy[j+y-2][i+x-2]*g[y][x]);
				}
			}

			gdx2[j][i] = tx2;
			gdy2[j][i] = ty2;
			gdxy[j][i] = txy;
		}
	}

	// 코너 응답 함수 생성
	double** crf = new double*[h];
	for (i = 0; i < h; i++) {
		crf[i] = new double[w];
		memset(crf[i], 0, sizeof(double)*w);
	}

	double k = 0.04;
	for (j = 2; j < h-2; j++) {
		for (i = 2; i < w-2; i++) {
			tmp = (gdx2[j][i]*gdy2[j][i] - gdxy[j][i]*gdxy[j][i]) - k*(gdx2[j][i] + gdy2[j][i])*(gdx2[j][i] + gdy2[j][i]);
			crf[j][i] = tmp;
		}
	}

	// 임계값보다 큰 국지적 최대값을 찾아 코너 포인트로 결정
	CornerPoints cp;
	cp.num = 0;

	for (j = 2; j < h-2; j++) {
		for (i = 2; i < w-2; i++) {
			if (crf[j][i] > th) {
				if (crf[j][i] > crf[j-1][i] && crf[j][i] > crf[j-1][i+1] &&
					crf[j][i] > crf[j][i+1] && crf[j][i] > crf[j+1][i+1] &&
					crf[j][i] > crf[j+1][i] && crf[j][i] > crf[j+1][i-1] &&
					crf[j][i] > crf[j][i-1] && crf[j][i] > crf[j-1][i-1]) {
						if (cp.num < MAX_CORNER) {
							cp.x[cp.num] = i;
							cp.y[cp.num] = j;
							cp.num++;
						}
				}
			}
		}
	}

	// 동적 할당 메모리 해제
	for (i = 0; i < h; i++) {
		delete [] dx2[i], dy2[i], dxy[i], gdx2[i], gdy2[i], gdxy[i], crf[i];
	}
	delete [] dx2, dy2, dxy, gdx2, gdy2, gdxy, crf;

	return cp;
}

void CbmpLoad2Dlg::OnBnClickedBtnGrayscale()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	register int i,j;

	int w = image.GetWidth();
	int h = image.GetHeight();

	obj.Create(w,h,24);

	BYTE r, g ,b;
	for (j = 0; j < h; j++) {
		for (i = 0; i < w; i++) {
			r = image.GetPixel(j,i);
			g = image.GetPixel(j,i) >> 8;
			b = image.GetPixel(j,i) >> 16;

			obj.SetPixel(j,i,limit(RGB2GRAY(r,g,b)));
		}
	}

	img = new Image(this);
	img->Create(IDD_IMAGE);
	img->ShowWindow(SW_SHOW);
	img->show(&obj, "Grayscale");
}

void CbmpLoad2Dlg::RGB_TO_HSI(double R, double G, double B, double& H, double& S, double& I)
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

void CbmpLoad2Dlg::HSI_TO_RGB(double H, double S, double I, double& R, double& G, double& B)
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

void CbmpLoad2Dlg::RGB_TO_YUV(BYTE R, BYTE G, BYTE B, BYTE& Y, BYTE& U, BYTE& V)
{
	Y = 0.299*R + 0.587*G + 0.144*B + 0.5;
	U = -0.169*R - 0.331*G + 0.500*B + 128 + 0.5;
	V = 0.500*R - 0.419*G - 0.081*B + 128 + 0.5;
}

void CbmpLoad2Dlg::YUV_TO_RGB(BYTE Y, BYTE U, BYTE V, BYTE& R, BYTE& G, BYTE& B)
{
	R = limit((int)(Y + 1.4075*(V-128) + 0.5));
	G = limit((int)(Y - 0.3455*(U-128) - 0.7169*(V-128) + 0.5));
	B = limit((int)(Y + 1.7790*(U-128) + 0.5));
}

void CbmpLoad2Dlg::InitImages()
{
	if (!img1.IsNull()) img1.Destroy();
	if (!img2.IsNull()) img2.Destroy();
	if (!img3.IsNull()) img3.Destroy();
}

void CbmpLoad2Dlg::OnBnClickedBtnSplitRgb()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	register int i, j;

	int w = image.GetWidth();
	int h = image.GetHeight();

	unsigned char r, g, b;

	InitImages();
	img1.Create(w,h,24);
	img2.Create(w,h,24);
	img3.Create(w,h,24);

	int pixel;
	for (j = 0; j < h; j++) {
		for (i = 0; i < w; i++) {
			pixel = image.GetPixel(j,i);
			r = pixel;
			g = pixel >> 8;
			b = pixel >> 16;

			img1.SetPixel(j,i,limit(r));
			img2.SetPixel(j,i,limit(g));
			img3.SetPixel(j,i,limit(b));
		}
	}

	arr[0] = new Image(this);
	arr[0]->Create(IDD_IMAGE);
	arr[0]->ShowWindow(SW_SHOW);
	arr[0]->show(&img1, "Red");

	arr[1] = new Image(this);
	arr[1]->Create(IDD_IMAGE);
	arr[1]->ShowWindow(SW_SHOW);
	arr[1]->show(&img2, "Green");

	arr[2] = new Image(this);
	arr[2]->Create(IDD_IMAGE);
	arr[2]->ShowWindow(SW_SHOW);
	arr[2]->show(&img3, "Blue");
}

void CbmpLoad2Dlg::OnBnClickedBtnSplitHsi()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	register int i, j;

	int w = image.GetWidth();
	int h = image.GetHeight();

	double r, g, b, hh, ss, ii;

	InitImages();
	img1.Create(w,h,24);
	img2.Create(w,h,24);
	img3.Create(w,h,24);

	int pixel;
	for (j = 0; j < h; j++) {
		for (i = 0; i < w; i++) {
			pixel = image.GetPixel(j,i);
			r = (pixel & 0xFF) / 255.;
			g = ((pixel & 0xFF00) >> 8) / 255.;
			b = ((pixel & 0xFF0000) >> 16) / 255.;

			RGB_TO_HSI(r,g,b,hh,ss,ii);

			img1.SetPixel(j,i,limit((int)(hh*255 + 0.5)));
			img2.SetPixel(j,i,limit((int)(ss*255 + 0.5)));
			img3.SetPixel(j,i,limit((int)(ii*255 + 0.5)));
		}
	}

	arr[0]->ShowWindow(SW_SHOW);
	arr[0]->show(&img1, "Hue");

	arr[1]->ShowWindow(SW_SHOW);
	arr[1]->show(&img2, "Saturation");

	arr[2]->ShowWindow(SW_SHOW);
	arr[2]->show(&img3, "Intensity");
}

void CbmpLoad2Dlg::OnBnClickedBtnSplitYuv()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	register int i, j;

	int w = image.GetWidth();
	int h = image.GetHeight();

	InitImages();
	img1.Create(w,h,24);
	img2.Create(w,h,24);
	img3.Create(w,h,24);

	BYTE r, g, b, y, u, v;
	int pixel;

	for (j = 0; j < h; j++) {
		for (i = 0; i < w; i++) {
			pixel = image.GetPixel(j,i);
			r = pixel & 0xFF;
			g = (pixel & 0xFF00) >> 8;
			b = (pixel & 0xFF0000) >> 16;

			RGB_TO_YUV(r,g,b,y,u,v);
			img1.SetPixel(j,i,limit(y));
			img2.SetPixel(j,i,limit(u));
			img3.SetPixel(j,i,limit(v));
		}
	}

	arr[0]->ShowWindow(SW_SHOW);
	arr[0]->show(&img1, "Y, 휘도");

	arr[1]->ShowWindow(SW_SHOW);
	arr[1]->show(&img2, "U, 청색 색차");

	arr[2]->ShowWindow(SW_SHOW);
	arr[2]->show(&img3, "V, 적색 색차");
}

void CbmpLoad2Dlg::OnBnClickedBtnCombineRgb()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (img1.IsNull() || img2.IsNull() || img3.IsNull()) return;

	register int i, j;

	int w = image.GetWidth();
	int h = image.GetHeight();

	if (img2.GetWidth() != w || img2.GetHeight() != h || img3.GetWidth() != w || img3.GetHeight() != h) return;

	obj.Create(w,h,24);

	BYTE r,g,b;

	for (j = 0; j < h; j++) {
		for (i = 0; i < w; i++) {
			r = img1.GetPixel(j,i);
			g = img2.GetPixel(j,i);
			b = img3.GetPixel(j,i);

			obj.SetPixelRGB(j,i,r,g,b);
		}
	}

	InitImages();
	arr[0]->ShowWindow(SW_HIDE);
	arr[1]->ShowWindow(SW_HIDE);
	arr[2]->ShowWindow(SW_HIDE);

	img = new Image(this);
	img->Create(IDD_IMAGE);
	img->ShowWindow(SW_SHOW);
	img->show(&obj, "Combine RGB");
}

void CbmpLoad2Dlg::OnBnClickedBtnCombineHsi()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (img1.IsNull() || img2.IsNull() || img3.IsNull()) return;

	register int i, j;

	int w = image.GetWidth();
	int h = image.GetHeight();

	if (img2.GetWidth() != w || img2.GetHeight() != h || img3.GetWidth() != w || img3.GetHeight() != h) return;

	obj.Create(w,h,24);

	double r,g,b,hh,ss,ii;

	for (j = 0; j < h; j++) {
		for (i = 0; i < w; i++) {
			hh = (double) (img1.GetPixel(j,i) >> 16) / 255.;
			ss = (double) (img2.GetPixel(j,i) >> 16) / 255.;
			ii = (double) (img3.GetPixel(j,i) >> 16) / 255.;

			HSI_TO_RGB(hh,ss,ii,r,g,b);
			r = r*255 + 0.5;
			g = g*255 + 0.5;
			b = b*255 + 0.5;
			obj.SetPixelRGB(j,i,limit((int)r),limit((int)g),limit((int)b));
		}
	}

	InitImages();
	arr[0]->ShowWindow(SW_HIDE);
	arr[1]->ShowWindow(SW_HIDE);
	arr[2]->ShowWindow(SW_HIDE);

	img = new Image(this);
	img->Create(IDD_IMAGE);
	img->ShowWindow(SW_SHOW);
	img->show(&obj, "Combine HSI");
}

void CbmpLoad2Dlg::OnBnClickedBtnCombineYuv()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (img1.IsNull() || img2.IsNull() || img3.IsNull()) return;

	register int i, j;

	int w = image.GetWidth();
	int h = image.GetHeight();

	if (img2.GetWidth() != w || img2.GetHeight() != h || img3.GetWidth() != w || img3.GetHeight() != h) return;

	obj.Create(w,h,24);

	BYTE y,u,v,r,g,b;

	for (j = 0; j < h; j++) {
		for (i = 0; i < w; i++) {
			y = img1.GetPixel(j,i)>>16;
			u = img2.GetPixel(j,i)>>16;
			v = img3.GetPixel(j,i)>>16;
			YUV_TO_RGB(y,u,v,r,g,b);

			obj.SetPixelRGB(j,i,r,g,b);
		}
	}

	InitImages();
	arr[0]->ShowWindow(SW_HIDE);
	arr[1]->ShowWindow(SW_HIDE);
	arr[2]->ShowWindow(SW_HIDE);

	img = new Image(this);
	img->Create(IDD_IMAGE);
	img->ShowWindow(SW_SHOW);
	img->show(&obj, "Combine YUV");
}

void CbmpLoad2Dlg::OnBnClickedBtnColorEdge()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	register int i, j;

	int w = image.GetWidth();
	int h = image.GetHeight();

	OnBnClickedBtnSplitYuv();
	CImage obj1, obj2, obj3;
	EdgePrewitt(&img1, &obj1);
	EdgePrewitt(&img2, &obj2);
	EdgePrewitt(&img3, &obj3);
	InitImages();

	obj.Create(w,h,24);

	int tmp;
	for (j = 0; j < h; j++) {
		for (i = 0; i < w; i++) {
			tmp = CalcDist(obj1.GetPixel(j,i)>>16, obj2.GetPixel(j,i)>>16, obj3.GetPixel(j,i)>>16);
			obj.SetPixel(j,i,limit(tmp));
		}
	}

	img = new Image(this);
	img->Create(IDD_IMAGE);
	img->ShowWindow(SW_SHOW);
	img->show(&obj, "Color Edge");
}

double CbmpLoad2Dlg::CalcDist(double x, double y, double z)
{
	return sqrt(x*x + y*y + z*z);
}

void CbmpLoad2Dlg::OnBnClickedBtnColorHistEq()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnBnClickedBtnSplitYuv();

	HistEqul(&img1, &obj);
	copy(&obj, &img1);
	OnBnClickedBtnCombineYuv();
}

void CbmpLoad2Dlg::OnBnClickedBtnBinarize()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Binarize bi;

	if (bi.DoModal() == IDOK) {
		Binarization(&image, &obj, bi.m_edit_threshold);

		img = new Image(this);
		img->Create(IDD_IMAGE);
		img->ShowWindow(SW_SHOW);
		img->show(&obj, "Binarization");
	}
}

void CbmpLoad2Dlg::OnBnClickedBtnBinarizationIter()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Binarize bi;

	int th = BinarizationIterative(&image);

	char str[32] = "Binarization\nTreshold: ";
	char tmp[4];
	sprintf_s(tmp,"%d", th);
	std::strcat(str,tmp);

	Binarization(&image, &obj, th);

	img = new Image(this);
	img->Create(IDD_IMAGE);
	img->ShowWindow(SW_SHOW);
	img->show(&obj, str);
}

void CbmpLoad2Dlg::OnBnClickedBtnLabeling()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nLabel = Labeling(&image, &obj);

	char str[32] = "레이블 개수 = ";
	char tmp[6];
	sprintf_s(tmp,"%d", nLabel);
	std::strcat(str,tmp);

	img = new Image(this);
	img->Create(IDD_IMAGE);
	img->ShowWindow(SW_SHOW);
	img->show(&obj, str);
}

void CbmpLoad2Dlg::OnBnClickedBtnContourTracing()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ContourPoints cp = ContourTracing(&image, &obj);

	register int i;

	int w = image.GetWidth();
	int h = image.GetHeight();

	obj.Create(w,h,24);
	for (i = 0; i < cp.num; i++) {
		obj.SetPixelRGB(cp.y[i], cp.x[i], 255,255,255);
	}

	img = new Image(this);
	img->Create(IDD_IMAGE);
	img->ShowWindow(SW_SHOW);
	img->show(&obj, "Contour Tracing");
}

void CbmpLoad2Dlg::OnBnClickedBtnMorphErosion()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	copy(&image, &obj);
	MorphologyErosion(&image, &obj);

	img = new Image(this);
	img->Create(IDD_IMAGE);
	img->ShowWindow(SW_SHOW);
	img->show(&obj, "Morphology Erosion");
}

void CbmpLoad2Dlg::OnBnClickedBtnMorphDilation()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	copy(&image, &obj);
	MorphologyDilation(&image, &obj);

	img = new Image(this);
	img->Create(IDD_IMAGE);
	img->ShowWindow(SW_SHOW);
	img->show(&obj, "Morphology Dilation");
}

void CbmpLoad2Dlg::OnBnClickedBtnMorphOpening()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	copy(&image, &obj);
	MorphologyErosion(&image, &obj);
	CImage tmp;
	copy(&obj, &tmp);
	MorphologyDilation(&tmp, &obj);

	img = new Image(this);
	img->Create(IDD_IMAGE);
	img->ShowWindow(SW_SHOW);
	img->show(&obj, "Morphology Opening");
}

void CbmpLoad2Dlg::OnBnClickedBtnMorphClosing()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	copy(&image, &obj);
	MorphologyDilation(&image, &obj);
	CImage tmp;
	copy(&obj, &tmp);
	MorphologyErosion(&tmp, &obj);
	
	img = new Image(this);
	img->Create(IDD_IMAGE);
	img->ShowWindow(SW_SHOW);
	img->show(&obj, "Morphology Closing");
}

void CbmpLoad2Dlg::OnBnClickedBtnMorphGrayErosion()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	obj.Create(image.GetWidth(), image.GetHeight(), 24);
	MorphologyGrayErosion(&image, &obj);

	img = new Image(this);
	img->Create(IDD_IMAGE);
	img->ShowWindow(SW_SHOW);
	img->show(&obj, "Morphology Gray Erosion");
}

void CbmpLoad2Dlg::OnBnClickedBtnMorphGrayDilation()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	obj.Create(image.GetWidth(), image.GetHeight(), 24);
	MorphologyGrayDilation(&image, &obj);

	img = new Image(this);
	img->Create(IDD_IMAGE);
	img->ShowWindow(SW_SHOW);
	img->show(&obj, "Morphology Gray Dilation");
}

void CbmpLoad2Dlg::OnBnClickedBtnMorphGrayOpening()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	obj.Create(image.GetWidth(), image.GetHeight(), 24);
	MorphologyGrayErosion(&image, &obj);
	CImage tmp;
	copy(&obj, &tmp);
	MorphologyGrayDilation(&tmp, &obj);

	img = new Image(this);
	img->Create(IDD_IMAGE);
	img->ShowWindow(SW_SHOW);
	img->show(&obj, "Morphology Gray Opening");
}

void CbmpLoad2Dlg::OnBnClickedBtnMorphGrayClosing()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	obj.Create(image.GetWidth(), image.GetHeight(), 24);
	MorphologyGrayDilation(&image, &obj);
	CImage tmp;
	copy(&obj, &tmp);
	MorphologyGrayErosion(&tmp, &obj);

	img = new Image(this);
	img->Create(IDD_IMAGE);
	img->ShowWindow(SW_SHOW);
	img->show(&obj, "Morphology Gray Closing");
}
