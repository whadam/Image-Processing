#pragma once

// BitPlane ��ȭ �����Դϴ�.

class BitPlane : public CDialog
{
	DECLARE_DYNAMIC(BitPlane)

public:
	BitPlane(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~BitPlane();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_BITPLANE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	int m_bit;
};
