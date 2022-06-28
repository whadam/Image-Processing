// Gamma.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "bmpLoad2.h"
#include "Gamma.h"
#include "afxdialogex.h"


// Gamma 대화 상자입니다.

IMPLEMENT_DYNAMIC(Gamma, CDialog)

Gamma::Gamma(CWnd* pParent /*=NULL*/)
	: CDialog(Gamma::IDD, pParent)
	, m_edit_gamma(2.2f)
{

}

Gamma::~Gamma()
{
}

void Gamma::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_GAMMA, m_slider_gamma);
	DDX_Text(pDX, IDC_EDIT_GAMMA, m_edit_gamma);
	DDV_MinMaxFloat(pDX, m_edit_gamma, 0.20f, 5.00f);
}

BOOL Gamma::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_slider_gamma.SetRange(10, 250);
	m_slider_gamma.SetTicFreq(20);
	m_slider_gamma.SetPageSize(20);
	m_slider_gamma.SetPos((int)(m_edit_gamma*50));

	return TRUE;
}


BEGIN_MESSAGE_MAP(Gamma, CDialog)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_EDIT_GAMMA, &Gamma::OnEnChangeEditGamma)
END_MESSAGE_MAP()


// Gamma 메시지 처리기입니다.


void Gamma::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_slider_gamma.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
	{
		int nPos = m_slider_gamma.GetPos();
		m_edit_gamma = nPos/50.f;
		UpdateData(FALSE);
	}

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


void Gamma::OnEnChangeEditGamma()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_slider_gamma.SetPos((int)(m_edit_gamma*50));
}
