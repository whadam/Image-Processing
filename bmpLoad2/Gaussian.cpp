// Gaussian.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "bmpLoad2.h"
#include "Gaussian.h"
#include "afxdialogex.h"


// Gaussian 대화 상자입니다.

IMPLEMENT_DYNAMIC(Gaussian, CDialog)

Gaussian::Gaussian(CWnd* pParent /*=NULL*/)
	: CDialog(Gaussian::IDD, pParent)
	, m_sigma(0)
{

}

Gaussian::~Gaussian()
{
}

void Gaussian::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_GAUSSIAN, m_sigma);
}


BEGIN_MESSAGE_MAP(Gaussian, CDialog)
END_MESSAGE_MAP()


// Gaussian 메시지 처리기입니다.
