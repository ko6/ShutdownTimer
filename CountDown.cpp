// CountDown.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ShutdownTimer.h"
#include "CountDown.h"
#include "afxdialogex.h"
#include <vector>

extern std::vector<k_time> times;
// CCountDown �Ի���

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
///��¼��ǰ��������id 
int time_order;
CString m1;
CString m2;
// CCountDown ��Ϣ�������


void CountDown::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}




BOOL CountDown::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	CFont my_Font;//�����µ�����ʵ��
	my_Font.CreatePointFont(320, TEXT("Arial"));//��������ʹ�С
	msg.SetFont(&my_Font);//��һ�����ڵ�����
							 //m_edit1 = "2020/3/11 21:14 ������";
							 //update();
	//msg.SetWindowTextW(TEXT("����00:02��ػ�"));
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
		//printf("����%S��ʱ��%d\n", times[i].action,t2);
		if (times[i].time_revise != -1 && t2 > -180   && (t1 ==NULL || t1>t2))
		{
			t1 = t2;
			m2 = times[i].action;
			time_order = i;
		}
	}


	printf("---\n����%S��ʱ��%d\n", m2, t1);


	SetTimer(0, 1000, NULL);



	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CountDown::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	t1--;
	if (t1 > 3600)
	{
		m1.Format(_T("����%02d:%02d:%02d��%s"), t1 / 3600,(t1%3600)/60,t1%60,m2);
	}
	else if (t1 > 0) 
	{
		m1.Format(_T("����%02d:%02d��%s"), t1 / 60, t1 % 60, m2);
	}
	else
	{
		m1.Format(_T("����%s..."), m2);
	}
	

	msg.SetWindowTextW(m1);

	CDialogEx::OnTimer(nIDEvent);
}


void CountDown::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//ȡ������
	int i = MessageBox(_T("���콫����ִ�д�����"), _T("�Ƿ�ȡ������"), MB_OKCANCEL);

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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�ӳ�10����ִ��
	int i = MessageBox(_T("�����ӳ�10����ִ��"), _T("�Ƿ��ӳ�ִ������"), MB_OKCANCEL);
	printf("times[time_order].time_revise=%d\n", times[time_order].time_revise);
	if (i == 1)
	{
		//MessageBox(_T("1"));
		times[time_order].time_revise += 600;
		OnInitDialog();
	}
	printf("times[time_order].time_revise=%d\n", times[time_order].time_revise);
}
