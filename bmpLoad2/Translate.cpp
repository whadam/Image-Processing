// Translate.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "bmpLoad2.h"
#include "Translate.h"
#include "afxdialogex.h"


// Translate 대화 상자입니다.

IMPLEMENT_DYNAMIC(Translate, CDialog)

Translate::Translate(CWnd* pParent /*=NULL*/)
	: CDialog(Translate::IDD, pParent)
	, m_edit_x(0)
	, m_edit_y(0)
{

}

Translate::~Translate()
{
}

void Translate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_X, m_edit_x);
	DDX_Text(pDX, IDC_EDIT_Y, m_edit_y);
}


BEGIN_MESSAGE_MAP(Translate, CDialog)
END_MESSAGE_MAP()


// Translate 메시지 처리기입니다.
