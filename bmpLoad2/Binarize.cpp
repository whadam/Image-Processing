// Binarize.cpp : ?�ы쁽 ???��??�땲??
// ?��? ?�스??

#include "stdafx.h"
#include "bmpLoad2.h"
#include "Binarize.h"
#include "afxdialogex.h"


// Binarize ?????곸옄??�땲??

IMPLEMENT_DYNAMIC(Binarize, CDialog)

Binarize::Binarize(CWnd* pParent /*=NULL*/)
	: CDialog(Binarize::IDD, pParent)
	, m_edit_threshold(128)
{

}

Binarize::~Binarize()
{
}

void Binarize::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_THRESHOLD, m_edit_threshold);
	DDX_Control(pDX, IDC_EDIT_THRESHOLD, m_edit_threshold_control);
	DDX_Control(pDX, IDC_SLIDER_THRESHOLD, m_slider_control);
}


BEGIN_MESSAGE_MAP(Binarize, CDialog)
	ON_EN_CHANGE(IDC_EDIT_THRESHOLD, &Binarize::OnEnChangeEditThreshold)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// Binarize 硫붿?�吏? 泥섎?�湲곗엯??�떎.
BOOL Binarize::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_slider_control.SetRange(0,255);
	m_slider_control.SetPageSize(32);
	m_slider_control.SetTicFreq(32);
	m_slider_control.SetPos(m_edit_threshold);

	return TRUE;
}

void Binarize::OnEnChangeEditThreshold()
{
	// TODO:  RICHEDIT ?�⑦?�濡?�씤 寃쎌?? ???�⑦?�濡??
	// CDialog::OnInitDialog() ??�닔???????
	//??��?留덉???�?OR ?곗궛??�뿬 ??�젙??ENM_CHANGE ???��洹몃? 吏?뺥븯??CRichEditCtrl().SetEventMask()???몄텧??? ??�쑝�?
	// ?????�� 硫붿?�吏???蹂�?궡吏? ??�뒿??�떎.

	// TODO:  ??�???�⑦?�濡????�� 泥섎?�湲??�붾뱶瑜??�붽???�땲??
	UpdateData(TRUE);
	m_slider_control.SetPos(m_edit_threshold);
}


void Binarize::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: ??�??硫붿?�吏? 泥섎?�湲??�붾뱶瑜??�붽? �??�?�� 湲곕??��믪쓣 ?몄텧??�땲??
	if (m_slider_control.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
	{
		int nPos = m_slider_control.GetPos();
		m_edit_threshold = nPos;
		UpdateData(FALSE);
	}

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
