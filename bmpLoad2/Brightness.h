#pragma once
#include "stdafx.h"
#include "resource.h"

// Brightness 대화 상자입니다.

class Brightness : public CDialog
{
	DECLARE_DYNAMIC(Brightness)

public:
	Brightness(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~Brightness();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_BRIGHTNESS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_slider_brightness;
	int m_edit_brightness;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnChangeEditBrightness();
};
