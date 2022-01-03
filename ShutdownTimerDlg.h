
// ShutdownTimerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include <vector>
#include "edit1.h"
#include "tinyxml2.h"

// CShutdownTimerDlg �Ի���
class CShutdownTimerDlg : public CDialogEx
{
// ����
public:
	CShutdownTimerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SHUTDOWNTIMER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	edit1 rule_edit_dlg;

	// ���ɵ���Ϣӳ�亯��
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

	///��������ִ��ʱ��
	void InitTimes();
	///�Ƿ��ǵ���ģʽ������ģʽ�´򿪿���̨
	bool debug;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnEnChangeEdit1();
	afx_msg LRESULT OnShowTask(WPARAM wParam, LPARAM lParam);//ͼ��ָ�

	CFont my_Font;//�����µ�����ʵ��

private:
	CString m_edit1;
	CEdit c_edit;
	CListCtrl c_times_list;
	

	///��Ŷ�ȡ��xml����
	tinyxml2::XMLDocument xml;
	char* xmlPath;

	///���ܻ��ظ���ʼ�������� �����޸������ú�����������
	void init();

	void toTray(wchar_t* msg);//��С�������� ����������ʾ��Ϣ
	void DeleteTray();//ɾ������ͼ��


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



