#pragma once


// SaltPepper 대화 상자입니다.

class SaltPepper : public CDialog
{
	DECLARE_DYNAMIC(SaltPepper)

public:
	SaltPepper(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~SaltPepper();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SALTPEPPER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	double m_deviation;
};
