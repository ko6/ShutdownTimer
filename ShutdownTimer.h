
// ShutdownTimer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CShutdownTimerApp: 
// �йش����ʵ�֣������ ShutdownTimer.cpp
//

class CShutdownTimerApp : public CWinApp
{
public:
	CShutdownTimerApp();
	

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CShutdownTimerApp theApp;
struct k_rule
{
	CString name;
	CString exclude;
	CString include;
	CString week;
	bool include_today;
};
struct k_time
{
	CString name;
	CString time;
	CString action;
	CString rule;
	CString note;
	///ʱ��� ��������ִ�еľ���ʱ�� -1����ʾ�����ڽ���ִ��
	int time_t;
	///�� ����ʱ�����������ڴ����ӳ�ִ������Ĺ��� ��������ʾ�ӳ�ִ����������� -1����ʾȡ�����񣬽��첻��ִ��
	int time_revise;
};