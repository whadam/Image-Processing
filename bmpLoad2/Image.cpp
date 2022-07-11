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
	parent = (CbmpLoad2Dlg*)pParent;
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
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDC_BTN_APPLY, &Image::OnBnClickedBtnApply)
END_MESSAGE_MAP()


// Image �޽��� ó�����Դϴ�.

void Image::show(CImage* image, char* name)
{
	m_name = name;
	UpdateData(FALSE);
	tmp = image;
	if (image != nullptr)
	{
		CDC* dc;
		dc = m_image_control.GetDC();
		image->BitBlt(dc->m_hDC, 0,0, SRCCOPY);
		ReleaseDC(dc);
	}
}

void Image::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (tmp != nullptr)
		tmp->Destroy();
	/*if (parent->cnt >= 10)
		parent->reset();*/
	CDialog::OnOK();
}

void Image::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (nID == SC_CLOSE) { // X��ư���� ���� ��
		if (tmp != nullptr)
			tmp->Destroy();
		/*if (parent->cnt >= 10)
			parent->reset();*/
	}
	CDialog::OnSysCommand(nID, lParam);
}


void Image::OnBnClickedBtnApply()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	copy(tmp, &parent->image);
	parent->show(&parent->image);
	OnBnClickedOk();
}
