#pragma once


// Gaussian ��ȭ �����Դϴ�.

class Gaussian : public CDialog
{
	DECLARE_DYNAMIC(Gaussian)

public:
	Gaussian(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~Gaussian();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_GAUSSIAN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	double m_sigma;
};
