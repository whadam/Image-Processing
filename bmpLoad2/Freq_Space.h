#pragma once


// Freq_Space ��ȭ �����Դϴ�.

class Freq_Space : public CDialog
{
	DECLARE_DYNAMIC(Freq_Space)

public:
	Freq_Space(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~Freq_Space();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_FREQ_SPACE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CString m_edit_type;
	CString m_edit_shape;
	int m_edit_cutoff;
	CString m_radius_range;
};
