#pragma once


// edit1 对话框

class edit1 : public CDialogEx
{
	DECLARE_DYNAMIC(edit1)

public:
	edit1(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~edit1();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EDIT1_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
