// Gaussian.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "bmpLoad2.h"
#include "Gaussian.h"
#include "afxdialogex.h"


// Gaussian ��ȭ �����Դϴ�.

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


// Gaussian �޽��� ó�����Դϴ�.
