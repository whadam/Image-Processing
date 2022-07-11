#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "resource.h"


// Binarize ��ȭ �����Դϴ�.

class Binarize : public CDialog
{
	DECLARE_DYNAMIC(Binarize)

public:
	Binarize(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~Binarize();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_BINARIZATION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	int m_edit_threshold;
	CEdit m_edit_threshold_control;
	CSliderCtrl m_slider_control;
	afx_msg void OnEnChangeEditThreshold();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
