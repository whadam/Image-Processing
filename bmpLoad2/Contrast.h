#pragma once
#include "afxcmn.h"


// Contrast 대화 상자입니다.

class Contrast : public CDialog
{
	DECLARE_DYNAMIC(Contrast)

public:
	Contrast(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~Contrast();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CONTRAST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_slider_contrast;
	int m_edit_contrast;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnChangeEditContrast();
};
