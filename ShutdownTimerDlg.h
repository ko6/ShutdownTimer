
// ShutdownTimerDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include <vector>
#include "edit1.h"
#include "tinyxml2.h"

// CShutdownTimerDlg 对话框
class CShutdownTimerDlg : public CDialogEx
{
// 构造
public:
	CShutdownTimerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SHUTDOWNTIMER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	edit1 rule_edit_dlg;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnDestroy();
	afx_msg
		void Save();
	void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();

	///计算任务执行时间
	void InitTimes();
	///是否是调试模式，调试模式下打开控制台
	bool debug;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnEnChangeEdit1();
	afx_msg LRESULT OnShowTask(WPARAM wParam, LPARAM lParam);//图标恢复

	CFont my_Font;//定义新的字体实例

private:
	CString m_edit1;
	CEdit c_edit;
	CListCtrl c_times_list;
	

	///存放读取的xml数据
	tinyxml2::XMLDocument xml;
	char* xmlPath;

	///可能会重复初始化的内容 比如修改了配置后、添加了任务后
	void init();

	void toTray(wchar_t* msg);//最小化到托盘 设置托盘提示信息
	void DeleteTray();//删除托盘图标


public:
	CListBox c_list_rules;
	

	afx_msg void OnLvnItemchangedList3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemActivateList3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton9();

	int EditTime(CString name);

	//std::vector<k_rule>rules;
	//extern vector<k_time>times;
	//extern	std::vector<k_rule> rules;

	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnClose();
	afx_msg void OnBnClickedButton15();
};
char* G2U(const char* gb2312);
char* U2G(const char* utf8);
CString   GetProductVersion(LPCTSTR   lpszFileName);
//vector<k_time>times;

/*extern rules;*/



