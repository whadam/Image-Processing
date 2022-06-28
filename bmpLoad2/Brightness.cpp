// Brightness.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "bmpLoad2.h"
#include "Brightness.h"
#include "afxdialogex.h"


// Brightness ��ȭ �����Դϴ�.

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


// Brightness �޽��� ó�����Դϴ�.


void Brightness::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	m_slider_brightness.SetPos(m_edit_brightness);
}
