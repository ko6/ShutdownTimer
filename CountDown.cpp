// CountDown.cpp : 实现文件
//

#include "stdafx.h"
#include "ShutdownTimer.h"
#include "CountDown.h"
#include "afxdialogex.h"
#include <vector>

extern std::vector<k_time> times;
// CCountDown 对话框

IMPLEMENT_DYNAMIC(CountDown, CDialogEx)

CountDown::CountDown(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_COUNTDOWN_DIALOG, pParent)
{

}

CountDown::~CountDown()
{
}

void CountDown::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, msg);
}


BEGIN_MESSAGE_MAP(CountDown, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &CountDown::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON1, &CountDown::OnBnClickedButton1)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON2, &CountDown::OnBnClickedButton2)
END_MESSAGE_MAP()


int t1;
///记录当前任务排序id 
int time_order;
CString m1;
CString m2;
// CCountDown 消息处理程序


void CountDown::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}




BOOL CountDown::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	CFont my_Font;//定义新的字体实例
	my_Font.CreatePointFont(320, TEXT("Arial"));//创建字体和大小
	msg.SetFont(&my_Font);//第一个框内的字体
							 //m_edit1 = "2020/3/11 21:14 星期三";
							 //update();
	//msg.SetWindowTextW(TEXT("将在00:02后关机"));
	//c_edit.SetFont())
	t1 = NULL;
	m2 = "";
	time_t now = time(0);
	int t2;
	for(int i=0;i<times.size();i++)
	{
		if (times[i].time_revise > -1) 
		{
			t2 =  times[i].time_t + times[i].time_revise - now;
		} else 
		{
			t2 = times[i].time_t - now;
		}
		//printf("任务%S，时间%d\n", times[i].action,t2);
		if (times[i].time_revise != -1 && t2 > -180   && (t1 ==NULL || t1>t2))
		{
			t1 = t2;
			m2 = times[i].action;
			time_order = i;
		}
	}


	printf("---\n任务%S，时间%d\n", m2, t1);


	SetTimer(0, 1000, NULL);



	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CountDown::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	t1--;
	if (t1 > 3600)
	{
		m1.Format(_T("将在%02d:%02d:%02d后%s"), t1 / 3600,(t1%3600)/60,t1%60,m2);
	}
	else if (t1 > 0) 
	{
		m1.Format(_T("将在%02d:%02d后%s"), t1 / 60, t1 % 60, m2);
	}
	else
	{
		m1.Format(_T("正在%s..."), m2);
	}
	

	msg.SetWindowTextW(m1);

	CDialogEx::OnTimer(nIDEvent);
}


void CountDown::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	//取消任务
	int i = MessageBox(_T("今天将不再执行此任务"), _T("是否取消任务？"), MB_OKCANCEL);

	printf("times[time_order].time_revise=%d\n", times[time_order].time_revise);
	if (i == 1)
	{
		//MessageBox(_T("1"));
		times[time_order].time_revise = -1;
		OnInitDialog();
	}
	printf("times[time_order].time_revise=%d\n", times[time_order].time_revise);
}

void CountDown::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//延迟10分钟执行
	int i = MessageBox(_T("任务将延迟10分钟执行"), _T("是否延迟执行任务？"), MB_OKCANCEL);
	printf("times[time_order].time_revise=%d\n", times[time_order].time_revise);
	if (i == 1)
	{
		//MessageBox(_T("1"));
		times[time_order].time_revise += 600;
		OnInitDialog();
	}
	printf("times[time_order].time_revise=%d\n", times[time_order].time_revise);
}
