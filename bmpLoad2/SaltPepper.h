#pragma once


// SaltPepper ��ȭ �����Դϴ�.

class SaltPepper : public CDialog
{
	DECLARE_DYNAMIC(SaltPepper)

public:
	SaltPepper(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~SaltPepper();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SALTPEPPER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	double m_deviation;
};
