// SaltPepper.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "bmpLoad2.h"
#include "SaltPepper.h"
#include "afxdialogex.h"


// SaltPepper ��ȭ �����Դϴ�.

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


// SaltPepper �޽��� ó�����Դϴ�.
