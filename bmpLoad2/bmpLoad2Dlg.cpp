
// bmpLoad2Dlg.cpp : 구현 파일

#include "stdafx.h"
#include "bmpLoad2.h"
#include "bmpLoad2Dlg.h"
#include "afxdialogex.h"
#include "afxwin.h"
#include "Enhancement.h"
#include "Geometry.h"
#include "resource.h"

#include "Fourier.h"
#include "Freq_Space.h"
#include "Harris.h"
#include "Segment.h"
#include "Color.h"
#include "Filter.h"

#include <Windows.h>
#include <math.h>
#include <algorithm>
#include <string.h>
#include <ctime>

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
	for (int i = 0; i < 12; i++)
	{
		m_images.push_back(new CImage);
		m_dlgs.push_back(new Image(this));
		m_dlgs[i]->Create(IDD_IMAGE);
	}
	cnt = 0;

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
	w = img->GetWidth();
	h = img->GetHeight();
	CDC* dc;
	dc = m_picture_control.GetDC();
	dc->CloseFigure();
	img->BitBlt(dc->m_hDC, 0,0, SRCCOPY);
	ReleaseDC(dc);
}

void CbmpLoad2Dlg::CreateDlg(char* str)
{
	m_dlgs[cnt]->ShowWindow(SW_SHOW);
	m_dlgs[cnt]->show(m_images[cnt], str);
	cnt++;
	if (cnt >= 10)
		reset();
}

void CbmpLoad2Dlg::CreateDlg(char* str1, char* str2, char* str3)
{
	m_dlgs[cnt]->ShowWindow(SW_SHOW);
	m_dlgs[cnt]->show(m_images[cnt], str1);

	m_dlgs[cnt+1]->ShowWindow(SW_SHOW);
	m_dlgs[cnt+1]->show(m_images[cnt+1], str2);

	m_dlgs[cnt+2]->ShowWindow(SW_SHOW);
	m_dlgs[cnt+2]->show(m_images[cnt+2], str3);

	cnt += 3;
	if (cnt >= 10)
		reset();
}

void CbmpLoad2Dlg::OnBnClickedBtnImageopen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	reset();
	image.Destroy();

	CFileDialog fdlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, NULL);
	char path[128];
	GetCurrentDirectory(128, path);
	fdlg.m_ofn.lpstrInitialDir = path;

	CString filename;
	if (IDOK == fdlg.DoModal())
	{
		filename = fdlg.GetFileName();
	}
	else return;

	image.Load(CT2CA(filename));

	show(&image);
}

void CbmpLoad2Dlg::OnBnClickedBtnRefresh()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	reset();
	image.Destroy();
	image.Load("lenna.bmp");
	show(&image);
}

void CbmpLoad2Dlg::reset()
{
	for (auto a : m_images)
		a->Destroy();
	cnt = 0;
}

void CbmpLoad2Dlg::OnBnClickedBtnSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!image.IsNull())
		image.Save("result.bmp", Gdiplus::ImageFormatBMP);
}

void CbmpLoad2Dlg::OnBnClickedBtnBrightness()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (image == nullptr) return;

	fnBrightness(&image, m_images[cnt], w, h);

	CreateDlg("Brightness");
}

void CbmpLoad2Dlg::OnBnClickedBtnContrast()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (image == nullptr) return;

	fnContrast(&image, m_images[cnt], w, h);

	CreateDlg("Contrast");
}

void CbmpLoad2Dlg::OnBnClickedBntGamma()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (image == nullptr) return;

	fnGamma(&image, m_images[cnt], w, h);
	
	CreateDlg("Gamma");
}

void CbmpLoad2Dlg::OnBnClickedBtnHisteq()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (image == nullptr) return;

	fnHistEqual(&image, m_images[cnt], w, h);

	CreateDlg("Histogram Equlize");
}

void CbmpLoad2Dlg::OnBnClickedBtnPlus()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (image == nullptr) return;

	fnAdd(&image, m_images[cnt], w, h);
	if (m_images[cnt]->IsNull())
		return;

	CreateDlg("Add");
}

void CbmpLoad2Dlg::OnBnClickedBtnAnd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (image == nullptr) return;

	fnAnd(&image, m_images[cnt], w, h);
	if (m_images[cnt]->IsNull())
		return;

	CreateDlg("And");
}

void CbmpLoad2Dlg::OnBnClickedBtnBitplane()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (image == nullptr) return;

	fnBitPlane(&image, m_images[cnt], w, h);
	if (m_images[cnt]->IsNull())
		return;

	CreateDlg("Bit Plane");
}

void CbmpLoad2Dlg::OnBnClickedBtnFiltermean()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (image == nullptr) return;

	fnMean(&image, m_images[cnt], w, h);

	CreateDlg("Filter Mean");
}

void CbmpLoad2Dlg::OnBnClickedBntGaussian()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (image == nullptr) return;

	fnGaussian(&image, m_images[cnt], w, h);

	CreateDlg("Gaussian");
}

void CbmpLoad2Dlg::OnBnClickedBtnUnsharp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (image == nullptr) return;

	fnUnsharpMask(&image, m_images[cnt], w, h);

	CreateDlg("Unsharp Mask");
}

void CbmpLoad2Dlg::OnBnClickedBtnLaplacian()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (image == nullptr) return;

	fnLaplacian(&image, m_images[cnt], w, h);

	CreateDlg("Laplacian");
}

void CbmpLoad2Dlg::OnBnClickedBtnNoisegaussian()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (image == nullptr) return;

	fnNoiseGaussian(&image, m_images[cnt], w, h);

	CreateDlg("Noise Gaussian");
}

void CbmpLoad2Dlg::OnBnClickedBtnSaltpepper()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (image == nullptr) return;

	copy(&image, m_images[cnt]);
	fnNoiseSaltNPepper(&image, m_images[cnt], w, h);

	CreateDlg("Noise Salt and Pepper");
}

void CbmpLoad2Dlg::OnBnClickedBtnMedean()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (image == nullptr) return;

	fnMedean(&image, m_images[cnt], w, h);

	CreateDlg("Medean");
}

void CbmpLoad2Dlg::OnBnClickedBtnDiffusion()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (image == nullptr) return;

	fnDiffusion(&image, m_images[cnt], w, h);

	CreateDlg("Diffusion");
}

void CbmpLoad2Dlg::OnBnClickedBtnTranslate()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (image == nullptr) return;

	fnTranslate(&image, m_images[cnt], w, h);

	CreateDlg("Translate");
}

void CbmpLoad2Dlg::OnBnClickedBtnResize()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (image == nullptr) return;

	char* str = fnResize(&image, m_images[cnt], w, h);

	CreateDlg(str);
}

void CbmpLoad2Dlg::OnBnClickedBtnRotate()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (image == nullptr) return;

	fnRotate(&image, m_images[cnt], w, h);

	CreateDlg("Rotate");
}

void CbmpLoad2Dlg::OnBnClickedBtnMirror()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (image == nullptr) return;

	fnMirror(&image, m_images[cnt], w, h);

	CreateDlg("Mirror");
}

void CbmpLoad2Dlg::OnBnClickedBtnFlip()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (image == nullptr) return;

	fnFlip(&image, m_images[cnt], w, h);

	CreateDlg("Flip");
}

void CbmpLoad2Dlg::OnBnClickedBtnDft()
{
	// 오래 걸림
	// disabled

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (image == nullptr) return;

	Fourier fourier;
	fourier.SetImage(&image);
	fourier.DFT(1);

	CImage cpy;
	cpy.Create(w,h,24);

	//fourier.GetSpectrumImage(&cpy);
	//dlg = new Image(this);
	//dlg->Create(IDD_IMAGE);
	//dlg->ShowWindow(SW_SHOW);
	//dlg->show(&cpy, "Spectrum");

	//fourier.GetphaseImage(&cpy);
	//dlg = new Image(this);
	//dlg->Create(IDD_IMAGE);
	//dlg->ShowWindow(SW_SHOW);
	//dlg->show(&cpy, "Phase");

	//fourier.DFT(-1);
	//fourier.GetImage(&cpy);
	//dlg = new Image(this);
	//dlg->Create(IDD_IMAGE);
	//dlg->ShowWindow(SW_SHOW);
	//dlg->show(&cpy, "IDFT");
}

void CbmpLoad2Dlg::OnBnClickedBtnDftrc()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (image == nullptr) return;

	/*clock_t start, finish;
	start = clock();*/

	Fourier fourier;
	fourier.SetImage(&image);
	fourier.DFTRC(1);

	fourier.GetSpectrumImage(m_images[cnt]);
	CreateDlg("Spectrum");

	fourier.GetphaseImage(m_images[cnt]);
	CreateDlg("Phase");

	fourier.DFTRC(-1);
	fourier.GetImage(m_images[cnt]);
	CreateDlg("IDFTRC");

	/*finish = clock();
	double duration = (double) (finish - start) / CLOCKS_PER_SEC;
	char str[32];
	sprintf_s(str, "debug\n%f sec", duration);

	CreateDlg(str);*/
}

void CbmpLoad2Dlg::OnBnClickedBtnFft()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (image == nullptr) return;
	if (!IsPowerOf2(w) || !IsPowerOf2(h)) return;

	/*clock_t start, finish;
	start = clock();*/

	Fourier fourier;
	fourier.SetImage(&image);
	fourier.FFT(1);
	
	fourier.GetSpectrumImage(m_images[cnt]);
	CreateDlg("Spectrum");

	fourier.GetphaseImage(m_images[cnt]);
	CreateDlg("Phase");

	fourier.FFT(-1);
	fourier.GetImage(m_images[cnt]);
	CreateDlg("IDFFT");

	/*finish = clock();
	double duration = (double) (finish - start) / CLOCKS_PER_SEC;
	char str[32];
	sprintf_s(str, "release\n%f sec", duration);

	CreateDlg(str);*/
}

void CbmpLoad2Dlg::OnBnClickedBtnIdealLowpass()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (image == nullptr) return;
	if (!IsPowerOf2(w) || !IsPowerOf2(h)) return;
	//clock_t start = 0, finish;

	Freq_Space fs;
	fs.m_edit_type = "Lowpass Filter";
	fs.m_edit_shape = "Ideal";
	fs.m_radius_range.Format("(0 ~ %d)", min(w/2, h/2));

	if (fs.DoModal() == IDOK)
	{
		//start = clock();

		Fourier fourier;
		fourier.SetImage(&image);
		fourier.FFT(1);
		fourier.IdealLowpass(fs.m_edit_cutoff);
		fourier.FFT(-1);

		fourier.GetImage(m_images[cnt]);
		CreateDlg("Ideal Lowpass Filtering");
	}

	/*if (start == 0)
		return;
	finish = clock();
	double duration = (double) (finish - start) / CLOCKS_PER_SEC;
	char str[32];
	sprintf_s(str, "%f sec", duration);
	dlg = new Image(this);
	dlg->Create(IDD_IMAGE);
	dlg->ShowWindow(SW_SHOW);
	dlg->show(nullptr, str);*/
}

void CbmpLoad2Dlg::OnBnClickedBtnIdealHighpass()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (image == nullptr) return;
	if (!IsPowerOf2(w) || !IsPowerOf2(h)) return;
	//clock_t start = 0, finish;

	Freq_Space fs;
	fs.m_edit_type = "Highpass Filter";
	fs.m_edit_shape = "Ideal";
	fs.m_radius_range.Format("(0 ~ %d)", min(w/2, h/2));

	if (fs.DoModal() == IDOK)
	{
		//start = clock();

		Fourier fourier;
		fourier.SetImage(&image);
		fourier.FFT(1);
		fourier.IdealHighpass(fs.m_edit_cutoff);
		fourier.FFT(-1);

		fourier.GetImage(m_images[cnt]);
		CreateDlg("Ideal Highpass Filtering");
	}

	/*finish = clock();
	double duration = (double) (finish - start) / CLOCKS_PER_SEC;
	char str[32];
	sprintf_s(str, "%f sec", duration);
	dlg = new Image(this);
	dlg->Create(IDD_IMAGE);
	dlg->ShowWindow(SW_SHOW);
	dlg->show(nullptr, str);*/
}

void CbmpLoad2Dlg::OnBnClickedBtnGaussianLowpass()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (image == nullptr) return;
	if (!IsPowerOf2(w) || !IsPowerOf2(h)) return;
	//clock_t start = 0, finish;

	Freq_Space fs;
	fs.m_edit_type = "Lowpass Filter";
	fs.m_edit_shape = "Gaussian";
	fs.m_radius_range.Format("(0 ~ %d)", min(w/2, h/2));

	if (fs.DoModal() == IDOK)
	{
		//start = clock();

		Fourier fourier;
		fourier.SetImage(&image);
		fourier.FFT(1);
		fourier.GaussianLowpass(fs.m_edit_cutoff);
		fourier.FFT(-1);

		fourier.GetImage(m_images[cnt]);
		CreateDlg("Gaussian Lowpass FIltering");
	}

	/*finish = clock();
	double duration = (double) (finish - start) / CLOCKS_PER_SEC;
	char str[32];
	sprintf_s(str, "%f sec", duration);
	CreateDlg(str);*/
}

void CbmpLoad2Dlg::OnBnClickedBtnGaussianHighpass()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (image == nullptr) return;
	if (!IsPowerOf2(w) || !IsPowerOf2(h)) return;
	//clock_t start = 0, finish;

	Freq_Space fs;
	fs.m_edit_type = "Highpass Filter";
	fs.m_edit_shape = "Gaussian";
	fs.m_radius_range.Format("(0 ~ %d)", min(w/2, h/2));

	if (fs.DoModal() == IDOK)
	{
		//start = clock();

		Fourier fourier;
		fourier.SetImage(&image);
		fourier.FFT(1);
		fourier.GaussianHighpass(fs.m_edit_cutoff);
		fourier.FFT(-1);

		fourier.GetImage(m_images[cnt]);
		CreateDlg("Gaussian Highpass Filtering");
	}

	/*finish = clock();
	double duration = (double)(finish - start) / CLOCKS_PER_SEC;
	char str[32];
	sprintf_s(str, "%f sec", duration);
	CreateDlg(str);*/
}

void CbmpLoad2Dlg::OnBnClickedBtnEdgeRobert()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (image == nullptr) return;

	fnEdgeRoberts(&image, m_images[cnt], w, h);

	CreateDlg("Edge Robert");
}

void CbmpLoad2Dlg::OnBnClickedBtnEdgePrewitt()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (image == nullptr) return;

	fnEdgePrewitt(&image, m_images[cnt], w, h);

	CreateDlg("Edge Prewitt");
}

void CbmpLoad2Dlg::OnBnClickedBtnEdgeSobel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (image == nullptr) return;

	fnEdgeSobel(&image, m_images[cnt], w,h);

	CreateDlg("Edge Sobel");
}

void CbmpLoad2Dlg::OnBnClickedBtnHough()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (image == nullptr) return;

	LineParam line = fnHoughLine(&image, w, h);
	fnDrawLine(m_images[cnt], line, 255, w, h);

	char str[64] = "Hough\nrho: ", tmp[16];
	sprintf_s(tmp, "%f", line.rho);
	std::strcat(str,tmp);
	std::strcat(str,"\nang: ");
	sprintf_s(tmp, "%f", line.ang);
	std::strcat(str,tmp);

	CreateDlg(str);
}

void CbmpLoad2Dlg::OnBnClickedBtnHarris()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (image == nullptr) return;

	m_images[cnt]->Create(w,h,24);
	copy(&image, m_images[cnt]);
	fnHarrisCorner(&image, m_images[cnt], w, h);

	CreateDlg("Harris Corner Points");
}

void CbmpLoad2Dlg::OnBnClickedBtnGrayscale()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (image == nullptr) return;

	Grayscale(&image, m_images[cnt], w, h);

	CreateDlg("Gray Scale");
}

void CbmpLoad2Dlg::OnBnClickedBtnSplitRgb()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (image == nullptr) return;

	ColorSplitRGB(&image, m_images, w, h, cnt);
	
	CreateDlg("Red", "Green", "Blue");
}

void CbmpLoad2Dlg::OnBnClickedBtnSplitHsi()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (image == nullptr) return;

	ColorSplitHSI(&image, m_images, w, h, cnt);

	CreateDlg("Hue", "Saturation", "Intensity");
}

void CbmpLoad2Dlg::OnBnClickedBtnSplitYuv()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (image == nullptr) return;

	ColorSplitYUV(&image, m_images, w,h,cnt);
	
	CreateDlg("Y, luminance", "U, chroma blue", "V, chroma red");
}

void CbmpLoad2Dlg::OnBnClickedBtnCombineRgb()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (image == nullptr) return;
	if (m_images[cnt-3]->IsNull() || m_images[cnt-2]->IsNull() || m_images[cnt-1]->IsNull()) return;
	if (m_images[cnt-2]->GetWidth() != w || m_images[cnt-2]->GetHeight() != h || m_images[cnt-1]->GetWidth() != w || m_images[cnt-1]->GetHeight() != h) return;

	ColorCombineRGB(m_images, w, h, cnt);

	CreateDlg("Combine RGB");
}

void CbmpLoad2Dlg::OnBnClickedBtnCombineHsi()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (image == nullptr) return;
	if (m_images[cnt-3]->IsNull() || m_images[cnt-2]->IsNull() || m_images[cnt-1]->IsNull()) return;
	if (m_images[cnt-2]->GetWidth() != w || m_images[cnt-2]->GetHeight() != h || m_images[cnt-1]->GetWidth() != w || m_images[cnt-1]->GetHeight() != h) return;

	ColorCombineHSI(m_images, w, h, cnt);

	CreateDlg("Combine HSI");
}

void CbmpLoad2Dlg::OnBnClickedBtnCombineYuv()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (image == nullptr) return;
	if (m_images[cnt-3]->IsNull() || m_images[cnt-2]->IsNull() || m_images[cnt-1]->IsNull()) return;
	if (m_images[cnt-2]->GetWidth() != w || m_images[cnt-2]->GetHeight() != h || m_images[cnt-1]->GetWidth() != w || m_images[cnt-1]->GetHeight() != h) return;

	ColorCombineYUV(m_images, w, h, cnt);

	CreateDlg("Combine YUV");
}

void CbmpLoad2Dlg::OnBnClickedBtnColorEdge()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (image == nullptr) return;

	OnBnClickedBtnSplitYuv();
	if (m_images[cnt-3]->IsNull() || m_images[cnt-2]->IsNull() || m_images[cnt-1]->IsNull()) return;
	
	ColorEdge(m_images, w, h, cnt);

	CreateDlg("Color Edge");
}

void CbmpLoad2Dlg::OnBnClickedBtnColorHistEq()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (image == nullptr) return;

	OnBnClickedBtnSplitYuv();
	if (m_images[cnt-3]->IsNull() || m_images[cnt-2]->IsNull() || m_images[cnt-1]->IsNull()) return;

	ColorHistEqual(m_images, w, h, cnt);
	
	CreateDlg("Color Histogram Equalize");
}

void CbmpLoad2Dlg::OnBnClickedBtnBinarize()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (image == nullptr) return;

	Binarization(&image, m_images[cnt], w, h);

	CreateDlg("Binarization");
}

void CbmpLoad2Dlg::OnBnClickedBtnBinarizationIter()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (image == nullptr) return;

	int th = BinarizationIterative(&image, w, h);
	Binarization(&image, m_images[cnt], w, h, th);

	char str[32] = "Binarization\nTreshold: ";
	char tmp[4];
	sprintf_s(tmp,"%d", th);
	std::strcat(str,tmp);
	CreateDlg(str);
}

void CbmpLoad2Dlg::OnBnClickedBtnLabeling()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// b_abcdef.bmp, apply -> Histogram Equal
	if (image == nullptr) return;

	int nLabel = Labeling(&image, m_images[cnt],w,h);

	char str[32] = "label count = ";
	char tmp[6];
	sprintf_s(tmp,"%d", nLabel);
	std::strcat(str,tmp);
	CreateDlg(str);
}

void CbmpLoad2Dlg::OnBnClickedBtnContourTracing()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// char.bmp, boat.bmp
	if (image == nullptr) return;

	ContourTracing(&image, m_images[cnt], w, h);

	CreateDlg("Contour Tracing");
}

void CbmpLoad2Dlg::OnBnClickedBtnMorphErosion()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (image == nullptr) return;

	copy(&image, m_images[cnt]);
	MorphologyErosion(&image, m_images[cnt],w,h);

	CreateDlg("Morphology Erosion");
}

void CbmpLoad2Dlg::OnBnClickedBtnMorphDilation()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (image == nullptr) return;

	copy(&image, m_images[cnt]);
	MorphologyDilation(&image, m_images[cnt],w,h);

	CreateDlg("Morphology Dilation");
}

void CbmpLoad2Dlg::OnBnClickedBtnMorphOpening()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (image == nullptr) return;

	MorphologyOpening(&image, m_images[cnt], w,h);

	CreateDlg("Morphology Opening");
}

void CbmpLoad2Dlg::OnBnClickedBtnMorphClosing()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (image == nullptr) return;

	MorphologyClosing(&image, m_images[cnt],w,h);

	CreateDlg("Morphology Closing");
}

void CbmpLoad2Dlg::OnBnClickedBtnMorphGrayErosion()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (image == nullptr) return;

	MorphologyGrayErosion(&image, m_images[cnt],w,h);

	CreateDlg("Morphology Gray Erosion");
}

void CbmpLoad2Dlg::OnBnClickedBtnMorphGrayDilation()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (image == nullptr) return;

	MorphologyGrayDilation(&image, m_images[cnt], w,h);

	CreateDlg("Morphology Gray Dilation");
}

void CbmpLoad2Dlg::OnBnClickedBtnMorphGrayOpening()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (image == nullptr) return;

	MorphologyGrayOpening(&image, m_images[cnt], w,h);

	CreateDlg("Morphology Gray Opening");
}

void CbmpLoad2Dlg::OnBnClickedBtnMorphGrayClosing()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (image == nullptr) return;

	MorphologyGrayClosing(&image, m_images[cnt], w,h);

	CreateDlg("Morphology Gray Closing");
}
