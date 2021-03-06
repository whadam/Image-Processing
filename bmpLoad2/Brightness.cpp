// Brightness.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "bmpLoad2.h"
#include "Brightness.h"
#include "afxdialogex.h"


// Brightness 대화 상자입니다.

IMPLEMENT_DYNAMIC(Brightness, CDialog)

Brightness::Brightness(CWnd* pParent /*=NULL*/)
	: CDialog(Brightness::IDD, pParent)
	, m_edit_brightness(0)
{

}

Brightness::~Brightness()
{
}

void Brightness::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_BRIGHTNESS, m_slider_brightness);
	DDX_Text(pDX, IDC_EDIT_BRIGHTNESS, m_edit_brightness);
}

BOOL Brightness::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_slider_brightness.SetRange(-100,100);
	m_slider_brightness.SetTicFreq(20);
	m_slider_brightness.SetPageSize(20);

	return TRUE;
}


BEGIN_MESSAGE_MAP(Brightness, CDialog)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_EDIT_BRIGHTNESS, &Brightness::OnEnChangeEditBrightness)
END_MESSAGE_MAP()


// Brightness 메시지 처리기입니다.


void Brightness::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_slider_brightness.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
	{
		int nPos = m_slider_brightness.GetPos();
		m_edit_brightness = nPos;
		UpdateData(FALSE);
	}

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


void Brightness::OnEnChangeEditBrightness()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_slider_brightness.SetPos(m_edit_brightness);
}
