// Resize.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "bmpLoad2.h"
#include "Resize.h"
#include "afxdialogex.h"


// Resize ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(Resize, CDialog)

Resize::Resize(CWnd* pParent /*=NULL*/)
	: CDialog(Resize::IDD, pParent)
	, m_width(0)
	, m_height(0)
	, m_ratio(TRUE)
	, m_interpolation(0)
	, m_oldWidth(0)
	, m_oldHeight(0)
{

}

Resize::~Resize()
{
}

void Resize::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_X, m_width);
	DDX_Text(pDX, IDC_EDIT_Y, m_height);
	DDX_Check(pDX, IDC_CHECK_RATIO, m_ratio);
	DDX_CBIndex(pDX, IDC_COMBO_INTERPOLATION, m_interpolation);
	DDX_Text(pDX, IDC_OLDWIDTH, m_oldWidth);
	DDX_Text(pDX, IDC_OLDHEIGHT, m_oldHeight);
}

BOOL Resize::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_width = m_oldWidth;
	m_height = m_oldHeight;

	UpdateData(FALSE);

	return TRUE;
}

BEGIN_MESSAGE_MAP(Resize, CDialog)
	ON_EN_CHANGE(IDC_EDIT_X, &Resize::OnEnChangeEditX)
	ON_EN_CHANGE(IDC_EDIT_Y, &Resize::OnEnChangeEditY)
	ON_BN_CLICKED(IDC_CHECK_RATIO, &Resize::OnBnClickedCheckRatio)
END_MESSAGE_MAP()


// Resize �޽��� ó�����Դϴ�.


void Resize::OnEnChangeEditX()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (GetDlgItem(IDC_COMBO_INTERPOLATION)->GetSafeHwnd() == NULL) return;

	if (m_ratio) {
		UpdateData(TRUE);
		m_height = m_width * m_oldHeight / m_oldWidth;
		UpdateData(FALSE);
	}
}


void Resize::OnEnChangeEditY()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (GetDlgItem(IDC_COMBO_INTERPOLATION)->GetSafeHwnd() == NULL) return;

	if (m_ratio) {
		UpdateData(TRUE);
		m_height = m_width * m_oldHeight / m_oldWidth;
		UpdateData(FALSE);
	}
}


void Resize::OnBnClickedCheckRatio()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	if (m_ratio) {
		m_height = m_width * m_oldHeight / m_oldWidth;
		UpdateData(FALSE);
	}
}
