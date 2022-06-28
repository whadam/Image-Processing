#pragma once


// Diffusion 대화 상자입니다.

class Diffusion : public CDialog
{
	DECLARE_DYNAMIC(Diffusion)

public:
	Diffusion(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~Diffusion();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIFFUSION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	float lambda;
	float k;
	int iter;
};
