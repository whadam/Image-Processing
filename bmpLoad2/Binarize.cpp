// Binarize.cpp : ?´Ñ‹ì½ ???”ª??…ë•²??
// ?œê? ?ŒìŠ¤??

#include "stdafx.h"
#include "bmpLoad2.h"
#include "Binarize.h"
#include "afxdialogex.h"


// Binarize ?????ê³¸ì˜„??…ë•²??

IMPLEMENT_DYNAMIC(Binarize, CDialog)

Binarize::Binarize(CWnd* pParent /*=NULL*/)
	: CDialog(Binarize::IDD, pParent)
	, m_edit_threshold(128)
{

}

Binarize::~Binarize()
{
}

void Binarize::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_THRESHOLD, m_edit_threshold);
	DDX_Control(pDX, IDC_EDIT_THRESHOLD, m_edit_threshold_control);
	DDX_Control(pDX, IDC_SLIDER_THRESHOLD, m_slider_control);
}


BEGIN_MESSAGE_MAP(Binarize, CDialog)
	ON_EN_CHANGE(IDC_EDIT_THRESHOLD, &Binarize::OnEnChangeEditThreshold)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// Binarize ï§Žë¶¿?†ï§ž? ï§£ì„Ž?æ¹²ê³—ì—¯??ˆë–Ž.
BOOL Binarize::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_slider_control.SetRange(0,255);
	m_slider_control.SetPageSize(32);
	m_slider_control.SetTicFreq(32);
	m_slider_control.SetPos(m_edit_threshold);

	return TRUE;
}

void Binarize::OnEnChangeEditThreshold()
{
	// TODO:  RICHEDIT ?Œâ‘¦?ƒæ¿¡?¼ì”¤ å¯ƒìŽŒ?? ???Œâ‘¦?ƒæ¿¡??
	// CDialog::OnInitDialog() ??¥ë‹”???????
	//??í€?ï§ë‰???ë¿?OR ?ê³—ê¶›??ë¿¬ ??¼ì ™??ENM_CHANGE ???˜’æ´¹ëªƒ? ï§žÂ€?ëº¥ë¸¯??CRichEditCtrl().SetEventMask()???ëª„í…§??? ??†ì‘ï§?
	// ?????” ï§Žë¶¿?†ï§ž???è¹‚ë?ê¶¡ï§ž? ??†ë’¿??ˆë–Ž.

	// TODO:  ??ë¦???Œâ‘¦?ƒæ¿¡????” ï§£ì„Ž?æ¹²??„ë¶¾ë±¶ç‘œ??°ë¶½???¸ë•²??
	UpdateData(TRUE);
	m_slider_control.SetPos(m_edit_threshold);
}


void Binarize::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: ??ë¦??ï§Žë¶¿?†ï§ž? ï§£ì„Ž?æ¹²??„ë¶¾ë±¶ç‘œ??°ë¶½? è«??ë¨?’— æ¹²ê³•??ª›ë¯ªì“£ ?ëª„í…§??¸ë•²??
	if (m_slider_control.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
	{
		int nPos = m_slider_control.GetPos();
		m_edit_threshold = nPos;
		UpdateData(FALSE);
	}

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
