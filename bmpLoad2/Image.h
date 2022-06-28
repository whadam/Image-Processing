#pragma once
#include "afxwin.h"


// Image ��ȭ �����Դϴ�.

class Image : public CDialog
{
	DECLARE_DYNAMIC(Image)

public:
	Image(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~Image();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_IMAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_image_control;

	void show(CImage* image, char*);
	afx_msg void OnBnClickedOk();
	CString m_name;
};

template<typename T>
inline void copy(T* src, T* dst)
{
	int i, j;
	int w = src->GetWidth();
	int h = src->GetHeight();

	dst->Destroy();
	dst->Create(w,h,24);

	for (i = 0; i < w; i++) {
		for (j = 0; j < h; j++) {
			dst->SetPixel(i,j,src->GetPixel(i,j));
		}
	}
}