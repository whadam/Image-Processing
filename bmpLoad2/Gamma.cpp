// Gamma.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "bmpLoad2.h"
#include "Gamma.h"
#include "afxdialogex.h"


// Gamma ��ȭ �����Դϴ�.

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


// Gamma �޽��� ó�����Դϴ�.


void Gamma::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	m_slider_gamma.SetPos((int)(m_edit_gamma*50));
}
