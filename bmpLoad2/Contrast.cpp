// Contrast.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "bmpLoad2.h"
#include "Contrast.h"
#include "afxdialogex.h"


// Contrast ��ȭ �����Դϴ�.

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


// Contrast �޽��� ó�����Դϴ�.


void Contrast::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	m_slider_contrast.SetPos(m_edit_contrast);
}
