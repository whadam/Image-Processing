
// bmpLoad2.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CbmpLoad2App:
// �� Ŭ������ ������ ���ؼ��� bmpLoad2.cpp�� �����Ͻʽÿ�.
//

class CbmpLoad2App : public CWinApp
{
public:
	CbmpLoad2App();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CbmpLoad2App theApp;