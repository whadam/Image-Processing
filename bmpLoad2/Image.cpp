// Image.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "bmpLoad2.h"
#include "Image.h"
#include "bmpLoad2Dlg.h"
#include "afxdialogex.h"

// Image 대화 상자입니다.

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


// Image 메시지 처리기입니다.

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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (tmp != nullptr)
		tmp->Destroy();
	/*if (parent->cnt >= 10)
		parent->reset();*/
	CDialog::OnOK();
}

void Image::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nID == SC_CLOSE) { // X버튼으로 종료 시
		if (tmp != nullptr)
			tmp->Destroy();
		/*if (parent->cnt >= 10)
			parent->reset();*/
	}
	CDialog::OnSysCommand(nID, lParam);
}


void Image::OnBnClickedBtnApply()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	copy(tmp, &parent->image);
	parent->show(&parent->image);
	OnBnClickedOk();
}
