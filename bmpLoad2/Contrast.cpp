// Contrast.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "bmpLoad2.h"
#include "Contrast.h"
#include "afxdialogex.h"


// Contrast 대화 상자입니다.

IMPLEMENT_DYNAMIC(Contrast, CDialog)

Contrast::Contrast(CWnd* pParent /*=NULL*/)
	: CDialog(Contrast::IDD, pParent)
	, m_edit_contrast(0)
{

}

Contrast::~Contrast()
{
}

void Contrast::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_CONTRAST, m_slider_contrast);
	DDX_Text(pDX, IDC_EDIT_CONTRAST, m_edit_contrast);
}

BOOL Contrast::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_slider_contrast.SetRange(-100,100);
	m_slider_contrast.SetTicFreq(20);
	m_slider_contrast.SetPageSize(20);

	return TRUE;
}


BEGIN_MESSAGE_MAP(Contrast, CDialog)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_EDIT_CONTRAST, &Contrast::OnEnChangeEditContrast)
END_MESSAGE_MAP()


// Contrast 메시지 처리기입니다.


void Contrast::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_slider_contrast.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
	{
		int nPos = m_slider_contrast.GetPos();
		m_edit_contrast = nPos;
		UpdateData(FALSE);
	}

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


void Contrast::OnEnChangeEditContrast()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_slider_contrast.SetPos(m_edit_contrast);
}
