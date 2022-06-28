#pragma once
#include "afxcmn.h"


// Gamma 대화 상자입니다.

class Gamma : public CDialog
{
	DECLARE_DYNAMIC(Gamma)

public:
	Gamma(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~Gamma();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_GAMMA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_slider_gamma;
	float m_edit_gamma;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnChangeEditGamma();
};
