#pragma once


// Diffusion ��ȭ �����Դϴ�.

class Diffusion : public CDialog
{
	DECLARE_DYNAMIC(Diffusion)

public:
	Diffusion(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~Diffusion();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIFFUSION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	float lambda;
	float k;
	int iter;
};
