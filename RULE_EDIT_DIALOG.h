#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include <vector>
#include "ShutdownTimerDlg.h"

// RULE_EDIT_DIALOG 对话框

class RULE_EDIT_DIALOG : public CDialogEx
{
	DECLARE_DYNAMIC(RULE_EDIT_DIALOG)

public:
	RULE_EDIT_DIALOG(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~RULE_EDIT_DIALOG();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RULE_EDIT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP();
	int sliderTarget;
protected:
	HICON m_hIcon;
protected:
//	CComboBox rule_list;

	CComboBox rule_list1;
	///当前编辑的任务的名称
	CString time_name;
	
	CComboBox rule_actions;
	afx_msg void OnEnSetfocusEdit1();
	CString help_msg;
	afx_msg void OnCbnSetfocusCombo1();
	afx_msg void OnCbnSetfocusCombo2();
	afx_msg void OnEnSetfocusEdit3();
	CEdit time_m;
	CEdit time_h;
	CSliderCtrl time_slider;
	///任务执行时间的类型
	///0 指定时间   1 倒计时
	int time_type;

	afx_msg void OnEnSetfocusEdit2();

//	afx_msg void OnTRBNThumbPosChangingSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg
		void ChangeSliderTarget();
	void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	afx_msg void OnNMGetCustomSplitRectRadio1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMGetCustomSplitRectRadio2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnSetfocusEdit4();
	afx_msg void OnBnSetfocusRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio1();
	CStatic idc_static_1;
	afx_msg void OnStnClickedStatic1();
	CEdit time_countdown;
//	afx_msg void OnEnChangeEdit2();
//	afx_msg void OnEnChangeEdit4();
	afx_msg void OnEnSetfocusEdit6();
//	afx_msg void OnEnChangeEdit6();
	afx_msg void OnEnUpdateEdit6();
	afx_msg void OnEnUpdateEdit4();
	afx_msg void OnEnUpdateEdit2();
//	afx_msg void OnEnKillfocusEdit2();
//	afx_msg void OnEnKillfocusEdit4();
//	afx_msg void OnEnKillfocusEdit6();
	CStatic idc_static_countdown1;
	CStatic idc_static_countdown2;
	CString time_remark;
	afx_msg void OnBnClickedButton1();
private:
	///是否是新增任务
	BOOL IsNewRule;
	///记录编辑已有任务时，当前任务在原任务列表中所在的位置 
	int time_order;

public:
	afx_msg void OnBnClickedButton2();
};

