// Binarize.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "bmpLoad2.h"
#include "Binarize.h"
#include "afxdialogex.h"


// Binarize ��ȭ �����Դϴ�.

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


// Binarize �޽��� ó�����Դϴ�.
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
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	m_slider_control.SetPos(m_edit_threshold);
}


void Binarize::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (m_slider_control.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
	{
		int nPos = m_slider_control.GetPos();
		m_edit_threshold = nPos;
		UpdateData(FALSE);
	}

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
