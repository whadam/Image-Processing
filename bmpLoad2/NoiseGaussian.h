#pragma once


// NoiseGaussian ��ȭ �����Դϴ�.

class NoiseGaussian : public CDialog
{
	DECLARE_DYNAMIC(NoiseGaussian)

public:
	NoiseGaussian(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~NoiseGaussian();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_NOISEGAUSSIAN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	double m_deviation;
};
