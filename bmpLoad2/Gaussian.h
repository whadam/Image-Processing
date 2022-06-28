#pragma once


// Gaussian 대화 상자입니다.

class Gaussian : public CDialog
{
	DECLARE_DYNAMIC(Gaussian)

public:
	Gaussian(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~Gaussian();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_GAUSSIAN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	double m_sigma;
};
