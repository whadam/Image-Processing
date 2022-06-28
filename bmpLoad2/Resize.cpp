// Resize.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "bmpLoad2.h"
#include "Resize.h"
#include "afxdialogex.h"


// Resize 대화 상자입니다.

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


// Resize 메시지 처리기입니다.


void Resize::OnEnChangeEditX()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (GetDlgItem(IDC_COMBO_INTERPOLATION)->GetSafeHwnd() == NULL) return;

	if (m_ratio) {
		UpdateData(TRUE);
		m_height = m_width * m_oldHeight / m_oldWidth;
		UpdateData(FALSE);
	}
}


void Resize::OnEnChangeEditY()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (GetDlgItem(IDC_COMBO_INTERPOLATION)->GetSafeHwnd() == NULL) return;

	if (m_ratio) {
		UpdateData(TRUE);
		m_height = m_width * m_oldHeight / m_oldWidth;
		UpdateData(FALSE);
	}
}


void Resize::OnBnClickedCheckRatio()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	if (m_ratio) {
		m_height = m_width * m_oldHeight / m_oldWidth;
		UpdateData(FALSE);
	}
}
