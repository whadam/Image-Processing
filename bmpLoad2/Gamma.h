#pragma once
#include "afxcmn.h"


// Gamma ��ȭ �����Դϴ�.

class Gamma : public CDialog
{
	DECLARE_DYNAMIC(Gamma)

public:
	Gamma(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~Gamma();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_GAMMA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_slider_gamma;
	float m_edit_gamma;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnChangeEditGamma();
};
