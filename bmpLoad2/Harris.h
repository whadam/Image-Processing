#pragma once


// Harris 대화 상자입니다.

class Harris : public CDialog
{
	DECLARE_DYNAMIC(Harris)

public:
	Harris(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~Harris();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_HARRIS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_edit_threshold;
};
