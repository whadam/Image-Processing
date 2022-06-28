// Freq_Space.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "bmpLoad2.h"
#include "Freq_Space.h"
#include "afxdialogex.h"


// Freq_Space 대화 상자입니다.

IMPLEMENT_DYNAMIC(Freq_Space, CDialog)

Freq_Space::Freq_Space(CWnd* pParent /*=NULL*/)
	: CDialog(Freq_Space::IDD, pParent)
	, m_edit_type(_T(""))
	, m_edit_shape(_T(""))
	, m_edit_cutoff(0)
	, m_radius_range(_T(""))
{

}

Freq_Space::~Freq_Space()
{
}

void Freq_Space::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TYPE, m_edit_type);
	DDX_Text(pDX, IDC_EDIT_SHAPE, m_edit_shape);
	DDX_Text(pDX, IDC_EDIT_RADIUS, m_edit_cutoff);
	DDX_Text(pDX, IDC_CUTOFF_RANGE, m_radius_range);
}


BEGIN_MESSAGE_MAP(Freq_Space, CDialog)
END_MESSAGE_MAP()


// Freq_Space 메시지 처리기입니다.
