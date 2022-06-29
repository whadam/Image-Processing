// Image.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "bmpLoad2.h"
#include "Image.h"
#include "bmpLoad2Dlg.h"
#include "afxdialogex.h"


// Image ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(Image, CDialog)

Image::Image(CWnd* pParent /*=NULL*/)
	: CDialog(Image::IDD, pParent)
	, m_name(_T(""))
{

}

Image::~Image()
{
}

void Image::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IMAGE, m_image_control);
	DDX_Text(pDX, IDC_NAME, m_name);
}

BEGIN_MESSAGE_MAP(Image, CDialog)
	ON_BN_CLICKED(IDOK, &Image::OnBnClickedOk)
END_MESSAGE_MAP()


// Image �޽��� ó�����Դϴ�.

void Image::show(CImage* image, char* name)
{
	m_name = name;
	UpdateData(FALSE);
	CDC* dc;
	dc = m_image_control.GetDC();
	image->BitBlt(dc->m_hDC, 0,0, SRCCOPY);
	ReleaseDC(dc);
}

void Image::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialog::OnOK();
}