#pragma once
#include "afxcmn.h"


// Contrast ��ȭ �����Դϴ�.

class Contrast : public CDialog
{
	DECLARE_DYNAMIC(Contrast)

public:
	Contrast(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~Contrast();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CONTRAST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_slider_contrast;
	int m_edit_contrast;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnChangeEditContrast();
};
