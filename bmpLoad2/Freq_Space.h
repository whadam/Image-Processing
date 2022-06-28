#pragma once


// Freq_Space 대화 상자입니다.

class Freq_Space : public CDialog
{
	DECLARE_DYNAMIC(Freq_Space)

public:
	Freq_Space(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~Freq_Space();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_FREQ_SPACE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_edit_type;
	CString m_edit_shape;
	int m_edit_cutoff;
	CString m_radius_range;
};
