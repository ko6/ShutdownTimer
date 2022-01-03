// ShutdownTimerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ShutdownTimer.h"
#include "ShutdownTimerDlg.h"
#include "afxdialogex.h"
#include <iostream>
#include "tinyxml2.h"
#include <vector>
#include <ctime>

#include <string>
#include <windows.h>

#include "RULE_EDIT_DIALOG.h"
#include "edit1.h"
#include "CountDown.h"

#pragma   comment(lib,   "Version.lib") 

#ifdef _DEBUG
#define new DEBUG_NEW
//printf("this is debug");
//debug = true;
#endif

#define WM_SHOWTASK (WM_USER+1)
#define IDR_SHOW 11
#define IDR_OTHER 12
#define IDR_EXIT 13

using namespace std;

//  struct k_rule
// {
// 	CString name;
// 	CString exclude;
// 	CString include;
// 	CString week;
// 	bool include_today;
// };
// 
//    struct k_time
// {
// 	CString name;
// 	CString time;
// 	CString action;
// 	CString rule;
// 	CString note;
// 	int time_t;
// };
// struct k_rule
// {
// 	CString name;
// 	CString exclude;
// 	CString include;
// 	CString week;
// 	bool include_today;
// };
// 	;


std::vector<k_rule> rules;

  std::vector<k_time> times;
  std::vector<CString> actions;
  ///要编辑的任务的名称 传递给任务编辑窗口
  CString edit_time_name;
// 
//   、、CString week[] = ["一"];
  ///记录应用数据是否有变更 false 没有    true 有  
  bool is_change;

  ///记录显示倒计时的时间
  int time_ShowCountDown;
  //初始化星期
  CString week[7] = { _T("日"),_T("一"),_T("二"),_T("三"),_T("四"),_T("五"),_T("六") };
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()

public:
	//virtual BOOL OnInitDialog();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	
END_MESSAGE_MAP()


void CShutdownTimerDlg::toTray(wchar_t* msg)//最小化到托盘
{
	NOTIFYICONDATA nid;
	nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	nid.hWnd = this->m_hWnd;
	nid.uID = IDR_MAINFRAME;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nid.uCallbackMessage = WM_SHOWTASK;//自定义的消息名称 
	nid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	wcscpy(nid.szTip,msg);//信息提示条为“OA” 
	Shell_NotifyIcon(NIM_ADD, &nid);//在托盘区添加图标 
	//ShowWindow(SW_HIDE);//隐藏主窗口
}

LRESULT CShutdownTimerDlg::OnShowTask(WPARAM wParam, LPARAM lParam)
{//wParam接收的是图标的ID，而lParam接收的是鼠标的行为
	if (wParam != IDR_MAINFRAME) return 1;
	switch (lParam)
	{
	case WM_LBUTTONUP://左键单击显示主界面
	{
		//this->ShowWindow(SW_SHOW);
		this->ShowWindow(SW_RESTORE);

		ModifyStyleEx(WS_EX_TOOLWINDOW, WS_EX_APPWINDOW);
		SetForegroundWindow();
		//DeleteTray();
	}break;
	case WM_RBUTTONUP://右击弹出菜单
	{
		LPPOINT lpoint = new tagPOINT;
		::GetCursorPos(lpoint);//得到鼠标位置
		CMenu menu;
		menu.CreatePopupMenu();
		//menu.AppendMenuW()
		menu.AppendMenuW(MFT_STRING, IDR_SHOW, _T("打开主界面"));
		menu.AppendMenuW(MFT_STRING, IDR_OTHER,_T( "其他"));
		menu.AppendMenuW(MFT_STRING, IDR_EXIT, _T("退出"));
		SetForegroundWindow();
	//	EnableMenuItem(menu, IDR_OTHER, MF_GRAYED);//"其他"菜单变灰
												   //menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x,lpoint->y,this);//显示菜单
		int xx = TrackPopupMenu(menu, TPM_RETURNCMD, lpoint->x, lpoint->y, NULL, this->m_hWnd, NULL);//显示菜单并获取选项ID
		if (xx==IDR_SHOW)
		{
			this->ShowWindow(SW_RESTORE);
			SetForegroundWindow();
			//DeleteTray();
		}
		else if (xx==IDR_OTHER) {
		//	MessageBox(TEXT("其他"));
			MessageBox(_T("你点击了“其他”菜单"), _T("提示"), MB_OK); }
		else if (xx == IDR_EXIT) {
			//OnBnClickedCancel(); 
			DestroyWindow();
	//		OnDestroy();
		//	CDialogEx::OnClose();
		}
		HMENU hmenu = menu.Detach();
		menu.DestroyMenu();
		delete lpoint;
	}break;
	case WM_LBUTTONDBLCLK:
	{
		//双击不处理
	}break;
	}
	return 0;
}

void CShutdownTimerDlg::DeleteTray()//销毁托盘图标
{
	NOTIFYICONDATA nid;
	nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	nid.hWnd = this->m_hWnd;
	nid.uID = IDR_MAINFRAME;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nid.uCallbackMessage = WM_SHOWTASK;
	nid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	wcscpy(nid.szTip, _T("OA"));
	Shell_NotifyIcon(NIM_DELETE, &nid);
}


// CShutdownTimerDlg 对话框



CShutdownTimerDlg::CShutdownTimerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SHUTDOWNTIMER_DIALOG, pParent)
	, m_edit1(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CShutdownTimerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_edit1);
	DDX_Control(pDX, IDC_EDIT1, c_edit);
	DDX_Control(pDX, IDC_LIST3, c_times_list);
}

BEGIN_MESSAGE_MAP(CShutdownTimerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CShutdownTimerDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CShutdownTimerDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CShutdownTimerDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CShutdownTimerDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CShutdownTimerDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CShutdownTimerDlg::OnBnClickedButton6)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON7, &CShutdownTimerDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CShutdownTimerDlg::OnBnClickedButton8)
	ON_WM_TIMER()
	ON_EN_CHANGE(IDC_EDIT1, &CShutdownTimerDlg::OnEnChangeEdit1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST3, &CShutdownTimerDlg::OnLvnItemchangedList3)
	ON_NOTIFY(LVN_ITEMACTIVATE, IDC_LIST3, &CShutdownTimerDlg::OnLvnItemActivateList3)
	ON_BN_CLICKED(IDC_BUTTON9, &CShutdownTimerDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CShutdownTimerDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CShutdownTimerDlg::OnBnClickedButton11)
	ON_MESSAGE(WM_SHOWTASK, OnShowTask)//消息映射
	ON_BN_CLICKED(IDC_BUTTON12, &CShutdownTimerDlg::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON13, &CShutdownTimerDlg::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON14, &CShutdownTimerDlg::OnBnClickedButton14)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

// CShutdownTimerDlg 消息处理程序

BOOL CShutdownTimerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	
	CString appTitle = _T("定时关机");
	CString sFileVersion = GetProductVersion(NULL);
	if (sFileVersion.CompareNoCase(_T("Error")) != 0)
	{
		appTitle.Format(_T("定时关机 v%s"), sFileVersion);
	}
	toTray(appTitle.AllocSysString());//设置托盘图标及标题


	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	
	//指定配置文件路径
	xmlPath = "./config.xml";

	//初始化action 添加action
	actions.push_back(_T("关机"));
	actions.push_back(_T("重启"));



	//设置标题字体
	//CFont my_Font;//定义新的字体实例
	my_Font.CreatePointFont(320, TEXT("Arial"));//创建字体和大小
	c_edit.SetFont(&my_Font);//第一个框内的字体
	//m_edit1 = "2020/3/11 21:14 星期三";
	//update();
	//更新界面上显示的时间
	CString text;
	time_t now = time(0);
	tm *today = localtime(&now);
	//printf("today is %d-%02d-%02d %02d:%02d:%02d , week is %d\n", today->tm_year + 1900, today->tm_mon + 1, today->tm_mday, today->tm_hour, today->tm_min, today->tm_sec, today->tm_wday);
	text.Format(_T("%d/%d/%d %02d:%02d 星期%s"), today->tm_year + 1900, today->tm_mon + 1, today->tm_mday, today->tm_hour, today->tm_min,week[ today->tm_wday]);
	//CString today_str, week_str;
	//today_str.Format(_T("%d-%d-%d"), today->tm_year + 1900, today->tm_mon + 1, today->tm_mday);
	//week_str.Format(_T("%d"), today->tm_wday);
	c_edit.SetWindowTextW(text);

//	c_edit.SetWindowTextW(TEXT(	"2020/3/11 21:14 星期三"));
		//c_edit.SetFont())
	
	//初始化任务列表框
	c_times_list.InsertColumn(0, TEXT("任务名称"),LVCFMT_LEFT, 100);
	c_times_list.InsertColumn(1, TEXT("日期规则"), LVCFMT_LEFT, 100);
	c_times_list.InsertColumn(2, TEXT("执行时间"), LVCFMT_LEFT, 100);
	c_times_list.InsertColumn(3, TEXT("任务内容"), LVCFMT_LEFT, 100);
	c_times_list.InsertColumn(4, TEXT("操作"), LVCFMT_LEFT, 100);

// 	c_rules_list.InsertItem(0, TEXT("任务1"));
// 	c_rules_list.SetItemText(0, 1, TEXT("每天"));
// 	c_rules_list.SetItemText(0, 2, TEXT("12:30"));
// 	c_rules_list.SetItemText(0, 3, TEXT("关机"));
// 	c_rules_list.SetItemText(0, 4, TEXT("编辑"));
// 
// 	c_rules_list.InsertItem(1, TEXT("任务2"));
// 	c_rules_list.SetItemText(1, 1, TEXT("法定工作日"));
// 	c_rules_list.SetItemText(1, 2, TEXT("开机30分钟后"));
// 	c_rules_list.SetItemText(1, 3, TEXT("关机"));
// 	c_rules_list.SetItemText(1, 4, TEXT("编辑"));

	

	c_times_list.SetExtendedStyle(c_times_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	
//	debug = true;
#ifdef _DEBUG
debug = true;
#endif

	if (debug)
	{
		AllocConsole();                     // 打开控制台资源	
		freopen("CONOUT$", "w", stdout);
	}

	init();



	SetTimer(0, 20000, NULL);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}


void CShutdownTimerDlg::init()
{
	is_change = FALSE;
	rules.clear();
	times.clear();

	//读取配置文件
	
	int errid = xml.LoadFile(xmlPath);
	if ( errid != 0)
	{
		if (errid == 3)//没找到配置文件
		{
			
			tinyxml2::XMLDeclaration* declaration = xml.NewDeclaration();
			xml.InsertFirstChild(declaration);

			tinyxml2::XMLElement* root = xml.NewElement(G2U("定时关机"));
			xml.InsertEndChild(root);
			
			root->SetAttribute("author", "koko");
			root->SetAttribute("version", "V0.0.1");

			tinyxml2::XMLElement* userNode = xml.NewElement("times");
			/*添加属性*/
			//userNode->SetAttribute("Name", "liangbaikai");
			//userNode->SetAttribute("Password ", "bbbbbb");
			root->InsertEndChild(userNode);

			userNode = xml.NewElement("rules");
			root->InsertEndChild(userNode);

		//	 xml.SaveFile(xmlPath);
			
	//		tinyxml2::XMLElement* root = xml.NewElement("times");
	//		xml.InsertEndChild(root);
			
			Save();
		}
		else {
			cout << "load xml file failed" << endl;
			return;
		}
	}

	
	
	//初始化日期规则
	
	k_rule rule;
	//内置几个日期规则，不读取配置文件中的数据
	rule.name = TEXT("法定工作日");
	rule.exclude = "2022-01-03,2022-01-31,2022-02-01,2022-02-02,2022-02-03,2022-02-04,2022-04-04,2022-04-05,2022-05-02,2022-05-03,2022-05-04,2022-06-03,2022-09-12,2022-10-03,2022-10-04,2022-10-05,2022-10-06,2022-10-07";
	rule.include = "2022-01-29,2022-01-30,2022-04-02,2022-04-24,2022-05-07,2022-10-08,2022-10-09";
	rule.week = "1,2,3,4,5";
	rules.push_back(rule);

	rule.name = TEXT("非工作日");
	rule.include = "2022-01-03,2022-01-31,2022-02-01,2022-02-02,2022-02-03,2022-02-04,2022-04-04,2022-04-05,2022-05-02,2022-05-03,2022-05-04,2022-06-03,2022-09-12,2022-10-03,2022-10-04,2022-10-05,2022-10-06,2022-10-07";
	rule.exclude = "2022-01-29,2022-01-30,2022-04-02,2022-04-24,2022-05-07,2022-10-08,2022-10-09";
	rule.week = "6,0";
	rules.push_back(rule);

	rule.name = TEXT("周一至周五");
	rule.include = "";
	rule.exclude = "";
	rule.week = "1,2,3,4,5";
	rules.push_back(rule);

	rule.name = TEXT("周六周日");
	rule.include = "";
	rule.exclude = "";
	rule.week = "6,0";
	rules.push_back(rule);

	rule.name = TEXT("每天");
	rule.include = "";
	rule.exclude = "";
	rule.week = "1,2,3,4,5,6,0";
	rules.push_back(rule);

	c_times_list.DeleteAllItems();


	tinyxml2::XMLElement* root = xml.RootElement();
	tinyxml2::XMLElement* userNode = root->FirstChildElement();

	//加载日期配置
	tinyxml2::XMLElement* rules_node = root->FirstChildElement("rules");
	if (rules_node != NULL)
	{
		cout << "rules_node:  " << rules_node->Name() << endl;
		tinyxml2::XMLElement* rule_node = rules_node->FirstChildElement("rule");
		while (rule_node)
		{
			//查询当前节点是否已经存在
			const char* name = U2G(rule_node->Attribute("name"));
			if (name)
			{//有name 判断name是否在现有数据中
				for (INT i = 0; i < rules.size(); i++)
				{
					wcout.imbue(locale("chs"));
					//MessageBox(rules[i].name);
					//MessageBox(CString(name));
					wcout << rules[i].name.GetString();
					cout << "<--已有数据  当前节点-->" << name << endl;
					if (rules[i].name && CString(name) == rules[i].name)
					{
						cout << "当前节点与已有数据重复，跳过" << endl;
						break;
					}

					if (i == rules.size() - 1)
					{//没有重复的
						cout << "当前节点不在已有数据中，新增 当前数据量： " << i + 1 << endl;
						k_rule rule;
						rule.name = name;
						rule.exclude = rule_node->Attribute("exclude");
						rule.include = rule_node->Attribute("include");
						rule.week = rule_node->Attribute("week");

						rules.push_back(rule);
						cout << "当前数据量： " << rules.size() << endl;

						//	RULE_EDIT_DIALOG dlg;
						//	dlg.rule_list.AddString(rule.name);

					}
				}

			}

			rule_node = rule_node->NextSiblingElement("rule");
		}

	}

	//加载任务配置
	rules_node = root->FirstChildElement("times");
	if (rules_node != NULL)
	{
		cout << "rules_node:  " << rules_node->Name() << endl;
		tinyxml2::XMLElement* rule_node = rules_node->FirstChildElement("time");
		while (rule_node)
		{
			//查询当前节点是否已经存_T(在)
			const char* name = U2G(rule_node->Attribute("name"));
			if (name)
			{//有name 判断name是否在现有数据中
				INT i = 0;
				for (i = 0; i < times.size(); i++)
				{
					//MessageBox(times[i].name);
					//MessageBox(CString(name));
					wcout << times[i].name.GetString();
					cout << "<--已有数据  当前节点-->" << name << endl;
					if (times[i].name && CString(name) == times[i].name)
					{
						cout << "当前节点与已有数据重复，跳过" << endl;
						break;
					}


				}

				if (i == times.size())
				{//没有重复的
					cout << "当任务前节点不在已有数据中，新增 当前数据量： " << i << endl;
					k_time time;
					time.name = name;
					time.action = U2G(rule_node->Attribute("action"));
					time.note = U2G(rule_node->Attribute("note"));
					time.rule = U2G(rule_node->Attribute("rule"));
					time.time = rule_node->Attribute("time");
					time.time_t = 0;
					time.time_revise = 0;
					times.push_back(time);
					printf("time.time_revise=%d   %d\n", time.time_revise,times[times.size()-1].time_revise);
					c_times_list.InsertItem(i, time.name);
					c_times_list.SetItemText(i, 1, time.rule);
					c_times_list.SetItemText(i, 2, time.time);
					c_times_list.SetItemText(i, 3, time.action);
					c_times_list.SetItemText(i, 4, TEXT("双击编辑"));

					cout << "当前数据量： " << times.size() << endl;

				}

			}

			rule_node = rule_node->NextSiblingElement("time");
		}

	}


	InitTimes();

}


void CShutdownTimerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CShutdownTimerDlg::OnPaint()
{

	

	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CShutdownTimerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int createXML(const char* xmlPath)
{
	tinyxml2::XMLDocument doc;
	if (3 != doc.LoadFile(xmlPath))
	{
		cout << "file has been existed !" << endl;
		return 0;
	}

	//添加申明可以使用如下两行
	tinyxml2::XMLDeclaration* declaration = doc.NewDeclaration();
	doc.InsertFirstChild(declaration);

	tinyxml2::XMLElement* root = doc.NewElement("XMLUSER");
	doc.InsertEndChild(root);


	tinyxml2::XMLElement* userNode = doc.NewElement("User");
	/*添加属性*/
	userNode->SetAttribute("Name", "liangbaikai");
	userNode->SetAttribute("Password ", "bbbbbb");
	root->InsertEndChild(userNode);

	return doc.SaveFile(xmlPath);
}

int addXML1(const char* xmlPath)
{
	tinyxml2::XMLDocument doc;
	if (doc.LoadFile(xmlPath) != 0)
	{
		cout << "load xml file failed" << endl;
		return false;
	}
	tinyxml2::XMLElement* root = doc.RootElement();
	tinyxml2::XMLElement* userNode = root->FirstChildElement("User");

	tinyxml2::XMLElement* gender = doc.NewElement("Gender");
	tinyxml2::XMLText* genderText = doc.NewText("man");
	gender->InsertFirstChild(genderText);
	userNode->InsertFirstChild(gender);

	tinyxml2::XMLElement* mobile = doc.NewElement("Mobile");
	mobile->InsertFirstChild(doc.NewText("188****6211"));
	userNode->InsertEndChild(mobile);

	tinyxml2::XMLElement* email = doc.NewElement("Email");
	email->InsertFirstChild(doc.NewText("1157***657@qq.com"));
	userNode->InsertEndChild(email);

	tinyxml2::XMLElement* userNode1 = doc.NewElement("User");
	userNode1->SetAttribute("Name", "Wenbaikai");
	userNode1->SetAttribute("Password ", "aaaaa");
	root->InsertEndChild(userNode1);

	tinyxml2::XMLElement* mobile1 = doc.NewElement("Mobile");
	mobile1->InsertFirstChild(doc.NewText("166****6666"));
	userNode1->InsertEndChild(mobile1);

	return doc.SaveFile(xmlPath);
}


int addXML2(const char* xmlPath)
{
	tinyxml2::XMLDocument doc;
	if (doc.LoadFile(xmlPath) != 0)
	{
		cout << "load xml file failed" << endl;
		return false;
	}
	tinyxml2::XMLElement* root = doc.RootElement();
	tinyxml2::XMLElement* userNode = doc.NewElement("Rule");

	//tinyxml2::XMLElement*gender = userNode->FirstChildElement("Gender");
	tinyxml2::XMLElement* age = doc.NewElement("Age");
	age->InsertFirstChild(doc.NewText(G2U("是上")));
	age->SetAttribute("age",TEXT("年芳二八"));
	userNode->InsertEndChild(age);

	//tinyxml2::XMLElement*mobile = userNode->FirstChildElement("Mobile");
	//mobile->SetAttribute("Location", "home");
	//tinyxml2::XMLElement* mobile1 = doc.NewElement("Mobile");
	//mobile1->SetAttribute("Location", "company");
	//mobile1->InsertFirstChild(doc.NewText("188****8888"));
	//userNode->InsertAfterChild(mobile, mobile1);
	root->InsertEndChild(userNode);
	return doc.SaveFile(xmlPath);
}

int deleteXML(const char* xmlPath)
{

	tinyxml2::XMLDocument doc;
	if (doc.LoadFile(xmlPath) != 0)
	{
		cout << "load xml file failed" << endl;
		return false;
	}
	tinyxml2::XMLElement* root = doc.RootElement();
	tinyxml2::XMLElement* userNode = root->FirstChildElement("User");
	tinyxml2::XMLElement*mobile = userNode->FirstChildElement("Mobile");
	userNode->DeleteChild(mobile);
	tinyxml2::XMLElement*mobile1 = userNode->FirstChildElement("Mobile");
	mobile1->DeleteAttribute("Location");
	return doc.SaveFile(xmlPath);
}

int changeXML(const char* xmlPath)
{
	tinyxml2::XMLDocument doc;
	if (doc.LoadFile(xmlPath) != 0)
	{
		cout << "load xml file failed" << endl;
		return false;
	}
	tinyxml2::XMLElement* root = doc.RootElement();
	tinyxml2::XMLElement* userNode = root->FirstChildElement("User");
	while (userNode != NULL)
	{
		if (0 == strncmp("liangbaikai", (userNode->Attribute("Name")), 11))
		{
			userNode->FirstChildElement("Age")->SetText("10000");
			userNode = userNode->NextSiblingElement();
		}
		else if ((0 == strncmp("Wenbaikai", (userNode->Attribute("Name")), 11)))
		{
			userNode->FirstChildElement("Mobile")->SetText("166****8888");
			userNode = userNode->NextSiblingElement();
		}
		else
		{
			userNode = userNode->NextSiblingElement();
		}
	}
	return doc.SaveFile(xmlPath);
}

int selectXML(const char* xmlPath)
{
	tinyxml2::XMLDocument doc;
	if (doc.LoadFile(xmlPath) != 0)
	{
		cout << "load xml file failed" << endl;
		return false;
	}
	
	tinyxml2::XMLElement* root = doc.RootElement();
	tinyxml2::XMLElement* userNode = root->FirstChildElement("User");
	//tinyxml2::XMLVisitor* v = userNode.Attribute()
	while (userNode != NULL)
	{
		cout << userNode->Name() << endl;
		const tinyxml2::XMLAttribute *attr = userNode->FirstAttribute();
		if (attr) {
			cout << attr->Name() << endl;
			attr = attr->Next();
			if (attr) {
				cout << attr->Name() << endl;
			}
		}
		//userNode->
		if (userNode->Attribute("Name") && 0 == strncmp("liangbaikai", (userNode->Attribute("Name")), 4))
		{
			cout << userNode->Attribute("Name") << endl;
			cout << userNode->Attribute("Password") << endl;
			cout << userNode->FirstChildElement("Age")->GetText() << endl;
			cout << userNode->FirstChildElement("Gender")->GetText() << endl;
			cout << userNode->FirstChildElement("Mobile")->GetText() << endl;
			cout << userNode->FirstChildElement("Email")->GetText() << endl;
			userNode = userNode->NextSiblingElement();
		}
		else
		{
			userNode = userNode->NextSiblingElement();
		}
	}
	return 0;
}
void CShutdownTimerDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

		int x;
		CString str;
		/*创建*/
		x = createXML("./xml/bbb.xml");
		str.Format(TEXT("创建文件结果是%d"), x);
		MessageBox(str);
		/*增*/
	//	addXML1("./xml/bbb.xml");/*添加性别，号码，邮箱*/ /*再添加一个用户*/
	//	addXML2("./xml/bbb.xml");/*在性别后面添加年龄，再添加一个号码*/
								 /*删*/
	//	deleteXML("./xml/bbb.xml");/*删除第一个号码，删除第二个号码的属性*/
								   /*改*/
	//	changeXML("./xml/bbb.xml");/*将liangbaikai的年龄改为10000岁，将wenbaikai的号码改为8888结尾*/
								   /*查*/
								   //selectXML("./xml/bbb.xml");/*将liangbaikai的信息打印出来*/

	//	selectXML("./xml/bbb.xml");/*将liangbaikai的信息打印出来*/
	
	

}


void CShutdownTimerDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	addXML1("./xml/bbb.xml");/*添加性别，号码，邮箱*/ /*再添加一个用户*/
}


void CShutdownTimerDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	addXML2("./xml/bbb.xml");/*在性别后面添加年龄，再添加一个号码*/
}


void CShutdownTimerDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	deleteXML("./xml/bbb.xml");/*删除第一个号码，删除第二个号码的属性*/
}


void CShutdownTimerDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	changeXML("./xml/bbb.xml");/*将liangbaikai的年龄改为10000岁，将wenbaikai的号码改为8888结尾*/
}


void CShutdownTimerDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码

	//AllocConsole();                     // 打开控制台资源

	//freopen("CONOUT$", "w+t", stdout);// 申请写
	//freopen("CONIN$", "r+t", stdin);  // 申请读
	printf("Hello World！n");          // 写数据
	cout << "ssss" << endl;
	//char ch = getchar();                // 读数据
	//FreeConsole();                      // 释放控制台资源
	//MessageBox(TEXT("sss"));

	selectXML("./xml/bbb.xml");/*将liangbaikai的信息打印出来*/
}


//UTF-8到GB2312的转换
char* U2G(const char* utf8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
	len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
	if (wstr) delete[] wstr;
	return str;
}

//GB2312到UTF-8的转换
char* G2U(const char* gb2312)
{
	int len = MultiByteToWideChar(CP_ACP, 0, gb2312, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_ACP, 0, gb2312, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	if (wstr) delete[] wstr;
	return str;
}

void CShutdownTimerDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	FreeConsole();                      // 释放控制台资源

}


void CShutdownTimerDlg::Save()
{
	tinyxml2::XMLElement* root = xml.RootElement();

	//更新times节点
	tinyxml2::XMLElement* times_node = root->FirstChildElement("times");
	if (times_node != NULL)
	{

		times_node->DeleteChildren();
	
		for (int i = 0; i < times.size(); i++) 
		{
			tinyxml2::XMLElement* time = times_node->InsertNewChildElement("time");
			const char *ch1;
			char temp[100];

			::wsprintfA(temp, "%ls", (LPCTSTR)times[i].name);
			ch1 =G2U(temp);
			time->SetAttribute("name", ch1);

			::wsprintfA(temp, "%ls", (LPCTSTR)times[i].action);
			ch1 = G2U(temp);
			time->SetAttribute("action", ch1);

			::wsprintfA(temp, "%ls", (LPCTSTR)times[i].time);
			ch1 = G2U(temp);
			time->SetAttribute("time", ch1);

			::wsprintfA(temp, "%ls", (LPCTSTR)times[i].rule);
			ch1 = G2U(temp);
			time->SetAttribute("rule", ch1);

			::wsprintfA(temp, "%ls", (LPCTSTR)times[i].note);
			ch1 = G2U(temp);
			time->SetAttribute("note", ch1);
		} 

	}

	//更新 rules 节点 ，删除内置规则，重新输出内置日期规则
	tinyxml2::XMLElement* rulesNode = root->FirstChildElement("rules");
	if (rulesNode != NULL)
	{
		rulesNode->DeleteChildren();

		for (int i = 0; i < rules.size(); i++)
		{
			tinyxml2::XMLElement* rule = rulesNode->InsertNewChildElement("rule");
			const char *ch1;
			char temp[1000];
			cout << rules[i].name << endl;
			::wsprintfA(temp, "%ls", (LPCTSTR)rules[i].name);
			ch1 = G2U(temp);
			rule->SetAttribute("name", ch1);
			cout << rules[i].exclude << endl;
			::wsprintfA(temp, "%ls", (LPCTSTR)rules[i].exclude);
			ch1 = G2U(temp);
			rule->SetAttribute("exclude", ch1);
			cout << rules[i].include << endl;
			::wsprintfA(temp, "%ls", (LPCTSTR)rules[i].include);
			ch1 = G2U(temp);
			rule->SetAttribute("include", ch1);
			cout << rules[i].week << endl;
			::wsprintfA(temp, "%ls", (LPCTSTR)rules[i].week);
			ch1 = G2U(temp);
			rule->SetAttribute("week", ch1);

		}
	}


	xml.SaveFile(xmlPath);



}

//************************************
// Method:    OnBnClickedButton7
// FullName:  CShutdownTimerDlg::OnBnClickedButton7
// Access:    public 
// Returns:   void
// Qualifier:
//************************************
void CShutdownTimerDlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码

	tinyxml2::XMLDocument doc;
	if (doc.LoadFile(xmlPath) != 0)
	{
		cout << "load xml file failed" << endl;
		return ;
	}

	tinyxml2::XMLElement* root = doc.RootElement();
	tinyxml2::XMLElement* userNode = root->FirstChildElement();
	
	//加载日期配置
	tinyxml2::XMLElement* rules_node = root->FirstChildElement("rules");
	if (rules_node != NULL)
	{
		cout << "rules_node:  " <<rules_node->Name() << endl;
		tinyxml2::XMLElement* rule_node = rules_node->FirstChildElement("rule");
		while (rule_node)
		{
			//查询当前节点是否已经存在
			const char* name =   U2G(rule_node->Attribute("name"));
			if (name) 
			{//有name 判断name是否在现有数据中
				for (INT i = 0; i < rules.size(); i++) 
				{
					wcout.imbue(locale("chs"));
					//MessageBox(rules[i].name);
					//MessageBox(CString(name));
					wcout << rules[i].name.GetString();
					cout  << "<--已有数据  当前节点-->" << name << endl;
					if (rules[i].name && CString(name) == rules[i].name)
					{
						cout << "当前节点与已有数据重复，跳过"  << endl;
						break;
					}

					if (i == rules.size()-1) 
					{//没有重复的
						cout << "当前节点不已有数据中，新增 当前数据量： " << i+1 <<endl;
						k_rule rule;
						rule.name = name;
						rule.exclude = rule_node->Attribute("exclude");
						rule.include = rule_node->Attribute("include");
						rule.week = rule_node->Attribute("week");
						
						rules.push_back(rule);
						cout << "当前数据量： " << rules.size() << endl;

					//	RULE_EDIT_DIALOG dlg;
					//	dlg.rule_list.AddString(rule.name);

					}
				}
			
			}

			rule_node = rule_node->NextSiblingElement("rule");
		}
		
	}

	//加载任务配置
	rules_node = root->FirstChildElement("times");
	if (rules_node != NULL)
	{
		cout << "rules_node:  " << rules_node->Name() << endl;
		tinyxml2::XMLElement* rule_node = rules_node->FirstChildElement("time");
		while (rule_node)
		{
			//查询当前节点是否已经存_T(在)
			const char* name = U2G(rule_node->Attribute("name"));
			if (name)
			{//有name 判断name是否在现有数据中
				INT i = 0;
				for (i = 0; i < times.size(); i++)
				{
					//MessageBox(times[i].name);
					//MessageBox(CString(name));
					wcout << times[i].name.GetString();
					cout <<"<--已有数据  当前节点-->"<<name << endl;
					if (times[i].name && CString(name) == times[i].name)
					{
						cout << "当前节点与已有数据重复，跳过" << endl;
						break;
					}

					
				}

				if (i == times.size() )
				{//没有重复的
					cout << "当任务前节点不在已有数据中，新增 当前数据量： " << i  << endl;
					k_time time;
					time.name = name;
					time.action = U2G(rule_node->Attribute("action"));
					time.note = U2G(rule_node->Attribute("note"));
					time.rule = U2G(rule_node->Attribute("rule"));
					time.time = rule_node->Attribute("time");

					times.push_back(time);

					c_times_list.InsertItem(i, time.name);
					c_times_list.SetItemText(i, 1, time.rule);
					c_times_list.SetItemText(i, 2, time.time);
					c_times_list.SetItemText(i, 3, time.action);
					c_times_list.SetItemText(i, 4, TEXT("双击编辑"));

					cout << "当前数据量： " << times.size() << endl;

				}

			}

			rule_node = rule_node->NextSiblingElement("time");
		}

	}

	return;
	//tinyxml2::XMLVisitor* v = userNode.Attribute()
	while (userNode != NULL)
	{
		cout << userNode->Name() << endl;

		tinyxml2::XMLElement * node = userNode->FirstChildElement();

		while (node)
		{
			cout << node->Name() << endl;

			const tinyxml2::XMLAttribute *attr = node->FirstAttribute();
			while (attr)
			{
				cout << attr->Name();
				cout << " = ";
				cout << U2G( attr->Value()) << endl;
				attr = attr->Next();
			}

			node = node->NextSiblingElement();

		}
		
		userNode = userNode->NextSiblingElement();
	}

}


void CShutdownTimerDlg::OnBnClickedButton8()
{
	
	// TODO: 在此添加控件通知处理程序代码

	// std::vector<k_rule>rules(0);

	InitTimes();

}


void CShutdownTimerDlg::InitTimes()
{
	//先取今天的日期
	time_t now = time(0);
	tm *today = localtime(&now);
	printf("today is %d-%02d-%02d %02d:%02d:%02d , week is %d\n", today->tm_year + 1900, today->tm_mon + 1, today->tm_mday, today->tm_hour, today->tm_min, today->tm_sec, today->tm_wday);
	CString today_str, week_str;
	today_str.Format(_T("%d-%02d-%02d"), today->tm_year + 1900, today->tm_mon + 1, today->tm_mday);
	week_str.Format(_T("%d"), today->tm_wday);
	printf("today_str = %S\n", today_str);
	//MessageBox(today_str);
	//cout << "today is"<< format today->tm_year+"-"+(today->tm_mon+"-"+today->tm_mday

	//遍历日期规则，判断今天是否满足规则
	for (int i = 0; i < rules.size(); i++)
	{
		setlocale(LC_CTYPE, "");
		printf("当前遍历的日期规则是：%S \n", rules[i].name, rules[i].name);
		//日期匹配两种条件
		//1 在week中，不在exclude中
		//2 不在week中，在include中
		if (rules[i].week.Find(week_str) > -1)
		{
			printf("%S 在 %S 中\n", week_str, rules[i].week);
			if (rules[i].exclude.Find(today_str) == -1)
			{
				printf("日期 %S 在 %S 中\n", today_str, rules[i].name);
				rules[i].include_today = TRUE;

			}
			else {
				printf("日期 %S 不在 %S 中\n", today_str, rules[i].name);
				rules[i].include_today = FALSE;
			}
		}
		else {
			printf("%S 不在 %S 中\n", week_str, rules[i].week);
			if (rules[i].include.Find(today_str) == -1)
			{
				printf("日期 %S 不在 %S 中\n", today_str, rules[i].name);
				rules[i].include_today = FALSE;
			}
			else {
				printf("日期 %S 在 %S 中\n", today_str, rules[i].name);
				rules[i].include_today = TRUE;
			}

		}


	}
	for (int i = 0; i < rules.size(); i++)
	{
		if (rules[i].include_today) {
			printf("today is %S\n", rules[i].name);
		}
		else {
			printf("today is not %S\n", rules[i].name);
		}

	}

	//遍历任务，判断任务执行时间
	for (int i = 0; i < times.size(); i++)
	{
		//print

		printf("当前遍历的任务是：%S   任务规则：%S   当前时间是：%d\n", times[i].name, times[i].rule, now);

		// 任务有设置执行时间，任务有计算后的执行时间戳，且时间戳未过期，则跳过 否则计算任务执行时间 考虑新增任务后倒计时重新计时的问题
		if (!times[i].time.IsEmpty() && !times[i].rule.IsEmpty())
		{

			if (times[i].time_t < now && times[i].time_t != -1)
			{
				printf("times[i].time_t is %d\n", times[i].time_t);
				//遍历规则，确定今天是否满足任务规则
				for (int j = 0; j < rules.size(); j++)
				{
					if (times[i].rule == rules[j].name)
					{
						printf("rule is %S\n", rules[j].name);
						if (rules[j].include_today && -1 != times[i].time_revise)
						{
							//包含今天
							printf("任务时间是：%S\n", times[i].time);
							if (times[i].time.Find(CString(":")) > -1)
							{//正计时，16：22
							//	today->tm_hour = 11;
							//	today->tm_sec = 22;
								today->tm_hour = _ttoi(times[i].time.Left(2));
								today->tm_min = _ttoi(times[i].time.Right(2));
								printf("任务时间 is %d-%02d-%02d %02d:%02d:%02d , time_t is %d\n", today->tm_year + 1900, today->tm_mon + 1, today->tm_mday, today->tm_hour, today->tm_min, today->tm_sec, mktime(today));
								times[i].time_t = mktime(today) + times[i].time_revise;
								printf("任务时间修正秒数：%d，修正后任务时间：%d\n", times[i].time_revise, times[i].time_t);
							}
							else
							{//倒计时 30
								times[i].time_t = now + 60 * _ttoi(times[i].time) + times[i].time_revise;
							}

						}
						else
						{
							//不包含今天
							times[i].time_t = -1;
						}
						break;
					}
				}
			}

		}

	}
}

void CShutdownTimerDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//printf("on timer %d");

	//更新界面上显示的时间
	CString text;
	time_t now = time(0);
	tm *today = localtime(&now);
	//printf("today is %d-%02d-%02d %02d:%02d:%02d , week is %d\n", today->tm_year + 1900, today->tm_mon + 1, today->tm_mday, today->tm_hour, today->tm_min, today->tm_sec, today->tm_wday);
	text.Format(_T("%d/%d/%d %02d:%02d 星期%s"),today->tm_year + 1900, today->tm_mon + 1, today->tm_mday, today->tm_hour, today->tm_min, week[today->tm_wday]);
	//CString today_str, week_str;
	//today_str.Format(_T("%d-%d-%d"), today->tm_year + 1900, today->tm_mon + 1, today->tm_mday);
	//week_str.Format(_T("%d"), today->tm_wday);
	c_edit.SetWindowTextW(text);



	
	int j = 0;
	for (INT i = 0; i < times.size(); i++) {
		if (times[i].time_revise > 0) 
		{
			j = times[i].time_t + times[i].time_revise;
		}
		else if(times[i].time_revise != -1)
		{
			j = times[i].time_t;
		}
		else 
		{
			//time_revise == -1   处理手动取消任务的场景
			j = 0;
		}

		if (j > now) {
			printf("任务%S倒计时：%d\n", times[i].name, j - now);
			if ( (j-now)<180 && now - time_ShowCountDown > 180) 
			{
				printf("j-now=%d", j - now);
				time_ShowCountDown = now;
				CountDown dlg;
				dlg.DoModal();
			}
		}
		else if(j > (now - 60))
		{
			if (times[i].action == _T("关机"))
			{
				system("shutdown -s -t 5");
			}
			else if(times[i].action == _T("重启"))
			{
				const char *ch1;
				char temp[100];
				::wsprintfA(temp, "echo 没有找到执行动作%ls的方法", (LPCTSTR)times[i].action);
				system(temp);
				//system("shutdown -r -t 5");
			}
			else
			{
				const char *ch1;
				char temp[100];
				::wsprintfA(temp, "echo 没有找到执行动作%ls的方法", (LPCTSTR)times[i].action);
				system(temp);

			}
			printf("执行任务：%S\n", times[i].name);
			times[i].time_t = -1;
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CShutdownTimerDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CShutdownTimerDlg::OnLvnItemchangedList3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	int r=c_times_list.GetSelectionMark();
	//int r3 = c_rules_list.GetNext;
	POSITION p = c_times_list.GetFirstSelectedItemPosition();
	int r2 = (int)c_times_list.GetNextSelectedItem(p);
	printf("你选择了第%d行 %d\n", r,r2);
}





void CShutdownTimerDlg::OnLvnItemActivateList3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	int r = c_times_list.GetSelectionMark();
	//int r3 = c_rules_list.GetNext;
	POSITION p = c_times_list.GetFirstSelectedItemPosition();
	int r2 = (int)c_times_list.GetNextSelectedItem(p);
	CString name;
	name = c_times_list.GetItemText(r2, 0);
	//MessageBox(name);
	printf("----你选择了第%d行 名称是%S %d\n", r,name, r2);
	EditTime(name);
}


void CShutdownTimerDlg::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码

	//todo 计算新任务不重复名称
	
	CString name;
	name.Format(TEXT("任务%d"), times.size()+1);
	EditTime(name);
	
//	CountDown dlg;
//	dlg.DoModal();
}

int CShutdownTimerDlg::EditTime(CString time_name)
{
	edit_time_name = time_name;
	RULE_EDIT_DIALOG dlg;

	int i1, i2;
	i1 = times.size();
	
	//rule_edit_dlg.DoModal();
	dlg.DoModal();
	//ShowWindow(dlg);
	i2 = times.size();


	printf("编辑前任务数:%d,\n编辑后任务数:%d,\n 保存结果:%S", i1, i2, xml.SaveFile(xmlPath));

	if (is_change)
	{
		Save();
		init();
	}	return i2;
}




void CShutdownTimerDlg::OnBnClickedButton10()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_HIDE);
	//ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);
}


void CShutdownTimerDlg::OnBnClickedButton11()
{
	// TODO: 在此添加控件通知处理程序代码
	ModifyStyleEx(WS_EX_TOOLWINDOW,WS_EX_APPWINDOW );
}


void CShutdownTimerDlg::OnBnClickedButton12()
{
	// TODO: 在此添加控件通知处理程序代码
	toTray(_T("定时关机 v1.0.2\r\n将在17：30 关机"));
}


void CShutdownTimerDlg::OnBnClickedButton13()
{
	// TODO: 在此添加控件通知处理程序代码
	DeleteTray();
}

///取文件版本信息
CString   GetProductVersion(LPCTSTR   lpszFileName)
{
	CString strVersion;
	TCHAR   szSrcfn[MAX_PATH];
	if (lpszFileName == NULL)
	{
		if (!::GetModuleFileName(NULL, szSrcfn, sizeof(szSrcfn)))
		{
			printf("Function <GetModuleFileName> unsuccessful!, ErrorCode:%d\n", ::GetLastError());
			return _T("Error");
		}
	}
	else
	{
		lstrcpy(szSrcfn, lpszFileName);
	}

	if (!CFileFind().FindFile(lpszFileName))
	{
		printf("%s is not Exist!\n", lpszFileName);
		return _T("Error");
	}

	BOOL bRet;
	DWORD   dwVerHnd = 0;
	DWORD   dwVerInfoSize = ::GetFileVersionInfoSize(szSrcfn, &dwVerHnd);
	if (!dwVerInfoSize)
	{
		printf("Function <GetFileVersionInfo> unsuccessful!, ErrorCode:%d\n", ::GetLastError());
		return _T("Error");
	}

	HANDLE     hMem;
	LPVOID     lpvMem;
	unsigned int uInfoSize = 0;
	VS_FIXEDFILEINFO * pFileInfo;

	hMem = ::GlobalAlloc(GMEM_MOVEABLE, dwVerInfoSize);
	lpvMem = ::GlobalLock(hMem);
	bRet = ::GetFileVersionInfo(szSrcfn, dwVerHnd, dwVerInfoSize, lpvMem);
	if (!bRet)
	{
		printf("Function <GetFileVersionInfo> unsuccessful!, ErrorCode:%d\n", ::GetLastError());
		return _T("Error");
	}

	bRet = ::VerQueryValue(lpvMem, (LPTSTR)_T("\\"), (LPVOID*)&pFileInfo, &uInfoSize);
	if (!bRet)
	{
		printf("Function <VerQueryValue> unsuccessful!\n");
		return _T("Error");
	}
	strVersion = _T('1.2.3.4');
	WORD nVer[4];
	nVer[0] = HIWORD(pFileInfo->dwProductVersionMS);
	nVer[1] = LOWORD(pFileInfo->dwProductVersionMS);
	nVer[2] = HIWORD(pFileInfo->dwProductVersionLS);
	nVer[3] = LOWORD(pFileInfo->dwProductVersionLS);
	printf("%S",strVersion);
	strVersion.Format(_T("%d.%d.%d.%d "), nVer[0], nVer[1], nVer[2], nVer[3]);
	printf("%S", strVersion);
	printf("%d.%d.%d.%d ", nVer[0], nVer[1], nVer[2], nVer[3]);
	::GlobalUnlock(hMem);
	::GlobalFree(hMem);

	return strVersion;
}

void CShutdownTimerDlg::OnBnClickedButton14()
{
	// TODO: 在此添加控件通知处理程序代码
		LPCTSTR sFilePath = NULL;
		CString appTitle = _T("定时关机");
		CString sFileVersion = GetProductVersion(NULL);
		if (sFileVersion.CompareNoCase(_T("Error")) != 0)
		    {
			appTitle.Format( _T("定时关机 v1=%s   v2=%S"), sFileVersion, sFileVersion.AllocSysString());
		    }
		printf("1%S   11%S\n", appTitle,sFileVersion);
		printf("2%S   22%S\n", appTitle.AllocSysString(), sFileVersion.AllocSysString());
}


void CShutdownTimerDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	ShowWindow(SW_HIDE);//隐藏主窗口
	//CDialogEx::OnClose();
}
