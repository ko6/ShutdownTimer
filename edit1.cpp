// edit1.cpp : 实现文件
//

#include "stdafx.h"
#include "ShutdownTimer.h"
#include "edit1.h"
#include "afxdialogex.h"
#include <vector>
#include <locale.h>
// edit1 对话框
// extern struct k_rule
// {
// 	CString name;
// 	CString exclude;
// 	CString include;
// 	CString week;
// 	bool include_today;
// };
// RULE_EDIT_DIALOG 对话框
extern std::vector<k_rule>rules;

IMPLEMENT_DYNAMIC(edit1, CDialogEx)

edit1::edit1(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_EDIT1_DIALOG, pParent)
{

}

edit1::~edit1()
{
}

BOOL edit1::OnInitDialog()
{
	CDialog::OnInitDialog();

	/// TODO: Add your control notification handler code here

	return true;

}


void edit1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(edit1, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &edit1::OnBnClickedButton1)
END_MESSAGE_MAP()


// edit1 消息处理程序


void edit1::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString x;
	x.Format(_T("rulese.size=%d"), rules.size());
	MessageBox(x);
	for (int i = 0; i < rules.size(); i++)
	{
		setlocale(LC_CTYPE, "");
		//rule_list.AddString(rules[i+1].name);
		printf("%d %S\n", i, rules[i].name);
	}

}
