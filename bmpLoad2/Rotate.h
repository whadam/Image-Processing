#pragma once


// Rotate ��ȭ �����Դϴ�.

class Rotate : public CDialog
{
	DECLARE_DYNAMIC(Rotate)

public:
	Rotate(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~Rotate();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ROTATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	int m_angel;
	int m_rotate;
};
