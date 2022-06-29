// Binarize.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "bmpLoad2.h"
#include "Binarize.h"
#include "afxdialogex.h"


// Binarize 대화 상자입니다.

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


// Binarize 메시지 처리기입니다.
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
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_slider_control.SetPos(m_edit_threshold);
}


void Binarize::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_slider_control.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
	{
		int nPos = m_slider_control.GetPos();
		m_edit_threshold = nPos;
		UpdateData(FALSE);
	}

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
