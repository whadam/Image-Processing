// BitPlane.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "bmpLoad2.h"
#include "BitPlane.h"
#include "afxdialogex.h"


// BitPlane ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(BitPlane, CDialog)

BitPlane::BitPlane(CWnd* pParent /*=NULL*/)
	: CDialog(BitPlane::IDD, pParent)
	, m_bit(0)
{

}

BitPlane::~BitPlane()
{
}

void BitPlane::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_BIT, m_bit);
}


BEGIN_MESSAGE_MAP(BitPlane, CDialog)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// BitPlane �޽��� ó�����Դϴ�.