// SaltPepper.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "bmpLoad2.h"
#include "SaltPepper.h"
#include "afxdialogex.h"


// SaltPepper 대화 상자입니다.

IMPLEMENT_DYNAMIC(SaltPepper, CDialog)

SaltPepper::SaltPepper(CWnd* pParent /*=NULL*/)
	: CDialog(SaltPepper::IDD, pParent)
	, m_deviation(0)
{

}

SaltPepper::~SaltPepper()
{
}

void SaltPepper::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DEVIATION, m_deviation);
}


BEGIN_MESSAGE_MAP(SaltPepper, CDialog)
END_MESSAGE_MAP()


// SaltPepper 메시지 처리기입니다.
