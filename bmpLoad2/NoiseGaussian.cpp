// NoiseGaussian.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "bmpLoad2.h"
#include "NoiseGaussian.h"
#include "afxdialogex.h"


// NoiseGaussian 대화 상자입니다.

IMPLEMENT_DYNAMIC(NoiseGaussian, CDialog)

NoiseGaussian::NoiseGaussian(CWnd* pParent /*=NULL*/)
	: CDialog(NoiseGaussian::IDD, pParent)
	, m_deviation(0)
{

}

NoiseGaussian::~NoiseGaussian()
{
}

void NoiseGaussian::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DEVIATION, m_deviation);
}


BEGIN_MESSAGE_MAP(NoiseGaussian, CDialog)
END_MESSAGE_MAP()


// NoiseGaussian 메시지 처리기입니다.
