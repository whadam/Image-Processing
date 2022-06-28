#pragma once
#include "afxwin.h"


// Image 대화 상자입니다.

class Image : public CDialog
{
	DECLARE_DYNAMIC(Image)

public:
	Image(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~Image();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_IMAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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