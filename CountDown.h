#pragma once
#include "afxwin.h"


// CCountDown 对话框

class CountDown : public CDialogEx
{
	DECLARE_DYNAMIC(CountDown)

public:
	CountDown(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CountDown();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COUNTDOWN_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit msg;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton2();
};
