#pragma once
#include "stdafx.h"
#include "resource.h"

// Brightness ��ȭ �����Դϴ�.

class Brightness : public CDialog
{
	DECLARE_DYNAMIC(Brightness)

public:
	Brightness(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~Brightness();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_BRIGHTNESS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_slider_brightness;
	int m_edit_brightness;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnChangeEditBrightness();
};
