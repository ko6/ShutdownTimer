#pragma once


// edit1 �Ի���

class edit1 : public CDialogEx
{
	DECLARE_DYNAMIC(edit1)

public:
	edit1(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~edit1();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EDIT1_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
