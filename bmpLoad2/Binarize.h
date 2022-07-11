#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "resource.h"


// Binarize 대화 상자입니다.

class Binarize : public CDialog
{
	DECLARE_DYNAMIC(Binarize)

public:
	Binarize(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~Binarize();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_BINARIZATION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	int m_edit_threshold;
	CEdit m_edit_threshold_control;
	CSliderCtrl m_slider_control;
	afx_msg void OnEnChangeEditThreshold();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
