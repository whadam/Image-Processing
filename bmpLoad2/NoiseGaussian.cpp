// NoiseGaussian.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "bmpLoad2.h"
#include "NoiseGaussian.h"
#include "afxdialogex.h"


// NoiseGaussian ��ȭ �����Դϴ�.

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


// NoiseGaussian �޽��� ó�����Դϴ�.
