// Diffusion.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "bmpLoad2.h"
#include "Diffusion.h"
#include "afxdialogex.h"


// Diffusion 대화 상자입니다.

IMPLEMENT_DYNAMIC(Diffusion, CDialog)

Diffusion::Diffusion(CWnd* pParent /*=NULL*/)
	: CDialog(Diffusion::IDD, pParent)
	, lambda(0.25f)
	, k(4.f)
	, iter(4)
{

}

Diffusion::~Diffusion()
{
}

void Diffusion::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, lambda);
	DDX_Text(pDX, IDC_EDIT2, k);
	DDX_Text(pDX, IDC_EDIT3, iter);
}


BEGIN_MESSAGE_MAP(Diffusion, CDialog)
END_MESSAGE_MAP()


// Diffusion 메시지 처리기입니다.
