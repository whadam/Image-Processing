#pragma once

// BitPlane 대화 상자입니다.

class BitPlane : public CDialog
{
	DECLARE_DYNAMIC(BitPlane)

public:
	BitPlane(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~BitPlane();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_BITPLANE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_bit;
};
