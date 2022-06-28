#pragma once


// Resize ��ȭ �����Դϴ�.

class Resize : public CDialog
{
	DECLARE_DYNAMIC(Resize)

public:
	Resize(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~Resize();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_RESIZE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
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
