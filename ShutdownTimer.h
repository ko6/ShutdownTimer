
// ShutdownTimer.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CShutdownTimerApp: 
// 有关此类的实现，请参阅 ShutdownTimer.cpp
//

class CShutdownTimerApp : public CWinApp
{
public:
	CShutdownTimerApp();
	

// 重写
public:
	virtual BOOL InitInstance();

// 实现

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
	///时间戳 保存任务执行的具体时间 -1：表示任务不在今天执行
	int time_t;
	///秒 调整时间秒数，用于处理延迟执行任务的功能 正数：表示延迟执行任务的秒数 -1：表示取消任务，今天不再执行
	int time_revise;
};