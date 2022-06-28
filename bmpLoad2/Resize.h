#pragma once


// Resize 대화 상자입니다.

class Resize : public CDialog
{
	DECLARE_DYNAMIC(Resize)

public:
	Resize(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~Resize();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_RESIZE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	int m_width;
	int m_height;
	BOOL m_ratio;
	int m_interpolation;
	afx_msg void OnEnChangeEditX();
	afx_msg void OnEnChangeEditY();
	afx_msg void OnBnClickedCheckRatio();
	int m_oldWidth;
	int m_oldHeight;
};
