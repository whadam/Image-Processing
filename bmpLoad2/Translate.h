#pragma once
#include "resource.h"

// Translate ��ȭ �����Դϴ�.

class Translate : public CDialog
{
	DECLARE_DYNAMIC(Translate)

public:
	Translate(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~Translate();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_TRANSLATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	int m_edit_x;
	int m_edit_y;
};
