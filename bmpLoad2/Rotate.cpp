// Rotate.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "bmpLoad2.h"
#include "Rotate.h"
#include "afxdialogex.h"


// Rotate ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(Rotate, CDialog)

Rotate::Rotate(CWnd* pParent /*=NULL*/)
	: CDialog(Rotate::IDD, pParent)
	, m_angel(0)
	, m_rotate(0)
{

}

Rotate::~Rotate()
{
}

void Rotate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ANGLE, m_angel);
	DDX_Radio(pDX, IDC_RADIO_90, m_rotate);
}


BEGIN_MESSAGE_MAP(Rotate, CDialog)
END_MESSAGE_MAP()


// Rotate �޽��� ó�����Դϴ�.
