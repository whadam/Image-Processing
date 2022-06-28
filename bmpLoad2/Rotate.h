#pragma once


// Rotate 대화 상자입니다.

class Rotate : public CDialog
{
	DECLARE_DYNAMIC(Rotate)

public:
	Rotate(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~Rotate();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ROTATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_angel;
	int m_rotate;
};
