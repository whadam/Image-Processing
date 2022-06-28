// Harris.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "bmpLoad2.h"
#include "Harris.h"
#include "afxdialogex.h"


// Harris 대화 상자입니다.

IMPLEMENT_DYNAMIC(Harris, CDialog)

Harris::Harris(CWnd* pParent /*=NULL*/)
	: CDialog(Harris::IDD, pParent)
	, m_edit_threshold(20000)
{

}

Harris::~Harris()
{
}

void Harris::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_THRESHOLD, m_edit_threshold);
}


BEGIN_MESSAGE_MAP(Harris, CDialog)
END_MESSAGE_MAP()


// Harris 메시지 처리기입니다.
