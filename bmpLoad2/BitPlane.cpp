// BitPlane.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "bmpLoad2.h"
#include "BitPlane.h"
#include "afxdialogex.h"


// BitPlane 대화 상자입니다.

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


// BitPlane 메시지 처리기입니다.