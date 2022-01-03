#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include <vector>
#include "ShutdownTimerDlg.h"

// RULE_EDIT_DIALOG �Ի���

class RULE_EDIT_DIALOG : public CDialogEx
{
	DECLARE_DYNAMIC(RULE_EDIT_DIALOG)

public:
	RULE_EDIT_DIALOG(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~RULE_EDIT_DIALOG();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RULE_EDIT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP();
	int sliderTarget;
protected:
	HICON m_hIcon;
protected:
//	CComboBox rule_list;

	CComboBox rule_list1;
	///��ǰ�༭�����������
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
	///����ִ��ʱ�������
	///0 ָ��ʱ��   1 ����ʱ
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
	///�Ƿ�����������
	BOOL IsNewRule;
	///��¼�༭��������ʱ����ǰ������ԭ�����б������ڵ�λ�� 
	int time_order;

public:
	afx_msg void OnBnClickedButton2();
};

