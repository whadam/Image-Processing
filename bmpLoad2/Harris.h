#pragma once


// Harris ��ȭ �����Դϴ�.

class Harris : public CDialog
{
	DECLARE_DYNAMIC(Harris)

public:
	Harris(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~Harris();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_HARRIS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	int m_edit_threshold;
};
