// RULE_EDIT_DIALOG.cpp : 实现文件
//

#include "stdafx.h"
#include "ShutdownTimer.h"
#include "RULE_EDIT_DIALOG.h"
#include "afxdialogex.h"

#include "ShutdownTimerDlg.h"
#include <vector>
#include <locale.h>

// RULE_EDIT_DIALOG 对话框
extern std::vector<k_rule>rules;
extern std::vector<k_time> times;
extern std::vector<CString> actions;
extern CString edit_time_name;
IMPLEMENT_DYNAMIC(RULE_EDIT_DIALOG, CDialogEx)
extern bool is_change;
int x;

RULE_EDIT_DIALOG::RULE_EDIT_DIALOG(CWnd * pParent)
	: CDialogEx(IDD_RULE_EDIT_DIALOG, pParent)
	, time_name(_T(""))
	, help_msg(_T(""))
	, time_type(0)
	, time_remark(_T(""))
{
//	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

RULE_EDIT_DIALOG::~RULE_EDIT_DIALOG()
{
}

void RULE_EDIT_DIALOG::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_COMBO1, rule_list1);
	DDX_Text(pDX, IDC_EDIT1, time_name);
	DDX_Control(pDX, IDC_COMBO2, rule_actions);
	DDX_Control(pDX, IDC_EDIT4, time_m);
	DDX_Control(pDX, IDC_EDIT2, time_h);
	DDX_Control(pDX, IDC_SLIDER1, time_slider);
	DDX_Radio(pDX, IDC_RADIO1, time_type);
	DDX_Text(pDX, IDC_EDIT5, help_msg);
	DDX_Control(pDX, IDC_STATIC_1, idc_static_1);
	DDX_Control(pDX, IDC_EDIT6, time_countdown);
	DDX_Control(pDX, IDC_STATIC_countdown1, idc_static_countdown1);
	DDX_Control(pDX, IDC_STATIC_countdown2, idc_static_countdown2);
	DDX_Text(pDX, IDC_EDIT3, time_remark);
}


BEGIN_MESSAGE_MAP(RULE_EDIT_DIALOG, CDialogEx)
	ON_WM_CREATE()
	ON_EN_SETFOCUS(IDC_EDIT1, &RULE_EDIT_DIALOG::OnEnSetfocusEdit1)
	ON_CBN_SETFOCUS(IDC_COMBO1, &RULE_EDIT_DIALOG::OnCbnSetfocusCombo1)
	ON_CBN_SETFOCUS(IDC_COMBO2, &RULE_EDIT_DIALOG::OnCbnSetfocusCombo2)
	ON_EN_SETFOCUS(IDC_EDIT3, &RULE_EDIT_DIALOG::OnEnSetfocusEdit3)
	ON_EN_SETFOCUS(IDC_EDIT2, &RULE_EDIT_DIALOG::OnEnSetfocusEdit2)
//	ON_NOTIFY(TRBN_THUMBPOSCHANGING, IDC_SLIDER1, &RULE_EDIT_DIALOG::OnTRBNThumbPosChangingSlider1)
	ON_WM_HSCROLL()
	ON_NOTIFY(NM_GETCUSTOMSPLITRECT, IDC_RADIO1, &RULE_EDIT_DIALOG::OnNMGetCustomSplitRectRadio1)
	ON_NOTIFY(NM_GETCUSTOMSPLITRECT, IDC_RADIO2, &RULE_EDIT_DIALOG::OnNMGetCustomSplitRectRadio2)
	ON_EN_SETFOCUS(IDC_EDIT4, &RULE_EDIT_DIALOG::OnEnSetfocusEdit4)
	ON_BN_SETFOCUS(IDC_RADIO1, &RULE_EDIT_DIALOG::OnBnSetfocusRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &RULE_EDIT_DIALOG::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO1, &RULE_EDIT_DIALOG::OnBnClickedRadio1)
	ON_STN_CLICKED(IDC_STATIC_1, &RULE_EDIT_DIALOG::OnStnClickedStatic1)
//	ON_EN_CHANGE(IDC_EDIT2, &RULE_EDIT_DIALOG::OnEnChangeEdit2)
//	ON_EN_CHANGE(IDC_EDIT4, &RULE_EDIT_DIALOG::OnEnChangeEdit4)
	ON_EN_SETFOCUS(IDC_EDIT6, &RULE_EDIT_DIALOG::OnEnSetfocusEdit6)
//	ON_EN_CHANGE(IDC_EDIT6, &RULE_EDIT_DIALOG::OnEnChangeEdit6)
	ON_EN_UPDATE(IDC_EDIT6, &RULE_EDIT_DIALOG::OnEnUpdateEdit6)
	ON_EN_UPDATE(IDC_EDIT4, &RULE_EDIT_DIALOG::OnEnUpdateEdit4)
	ON_EN_UPDATE(IDC_EDIT2, &RULE_EDIT_DIALOG::OnEnUpdateEdit2)
//	ON_EN_KILLFOCUS(IDC_EDIT2, &RULE_EDIT_DIALOG::OnEnKillfocusEdit2)
//	ON_EN_KILLFOCUS(IDC_EDIT4, &RULE_EDIT_DIALOG::OnEnKillfocusEdit4)
//	ON_EN_KILLFOCUS(IDC_EDIT6, &RULE_EDIT_DIALOG::OnEnKillfocusEdit6)
ON_BN_CLICKED(IDC_BUTTON1, &RULE_EDIT_DIALOG::OnBnClickedButton1)
ON_BN_CLICKED(IDC_BUTTON2, &RULE_EDIT_DIALOG::OnBnClickedButton2)
END_MESSAGE_MAP()


// RULE_EDIT_DIALOG 消息处理程序


BOOL RULE_EDIT_DIALOG::OnInitDialog()
{

	CDialogEx::OnInitDialog();

// 	// 将“关于...”菜单项添加到系统菜单中。
// 
// 	// IDM_ABOUTBOX 必须在系统命令范围内。
// 	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
// 	ASSERT(IDM_ABOUTBOX < 0xF000);
// 
// 	CMenu* pSysMenu = GetSystemMenu(FALSE);
// 	if (pSysMenu != NULL)
// 	{
// 		BOOL bNameValid;
// 		CString strAboutMenu;
// 		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
// 		ASSERT(bNameValid);
// 		if (!strAboutMenu.IsEmpty())
// 		{
// 			pSysMenu->AppendMenu(MF_SEPARATOR);
// 			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
// 		}
// 	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	//SetIcon(m_hIcon, TRUE);			// 设置大图标
	//SetIcon(m_hIcon, FALSE);		// 设置小图标

//	rule_list.AddString(L"h");
	

	 IsNewRule = TRUE;

	///任务执行动作 默认是关机
	CString action = _T("关机");
	time_name = edit_time_name;
	UpdateData(FALSE);
	///任务执行的日期规则，默认是“法定工作日”
	CString rule = _T("法定工作日");
	//默认办理时间 指定时间17：30
	time_type = 0;
	time_h.LimitText(2);
	time_m.LimitText(2);
	time_countdown.LimitText(2);
	time_h.SetWindowTextW(_T("17"));
	time_m.SetWindowTextW(_T("30"));
	OnBnClickedRadio1();
	UpdateData(FALSE);
	x = 1;

	//遍历任务列表，如果任务名称存在于任务列表中，则认为是编辑已有任务，加载已有事项信息
	for (int i = 0; i < times.size(); i++) 
	{
		if (times[i].name == edit_time_name) 
		{
			IsNewRule = FALSE;
			time_order = i;
			action = times[i].action;
			rule = times[i].rule;
			if ((times[i].time.GetLength() ==5)&&( times[i].time.Find(CString(":")) == 2))
			{//正计时，16：22
				time_h.SetWindowTextW(times[i].time.Left(2));
				time_m.SetWindowTextW(times[i].time.Right(2));
				//更新时间类型选择状态
				//OnBnClickedRadio1();
				//更新滑动条选择位置
				OnEnUpdateEdit2();
			}
			else
			{//倒计时 30
				printf("else\n");
				OnBnClickedRadio2();
				time_countdown.SetWindowTextW(times[i].time);
				
			//	OnEnUpdateEdit6();
			}
			time_remark = times[i].note;


			UpdateData(FALSE);
			break;
		}
	}
		


	printf("size=%d\n",rules.size());
	int cursel = 0;
	
	for (int i = 0; i < rules.size(); i++) 
	{
		setlocale(LC_CTYPE, "");
		//CString x;
		//x.Format(_T("%S"), "中国");
		printf("%d  %S\n", i, rules[i].name);
		//rule_list1.AddString(x);
		rule_list1.AddString(rules[i].name);
		if (rules[i].name == rule) 
		{
			cursel = i;
		}
		
	}
	rule_list1.SetCurSel(cursel);

	cursel = 0;
	
	for (int i = 0; i < actions.size(); i++)
	{
		rule_actions.AddString(actions[i]);
		if (actions[i] == action)
		{
			cursel = i;
		}
	}
	rule_actions.SetCurSel(cursel);




	return TRUE;
}





void RULE_EDIT_DIALOG::OnEnSetfocusEdit1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	help_msg = _T("任务名称，记录本任务的名称，可修改。");
	UpdateData(FALSE);
}


void RULE_EDIT_DIALOG::OnCbnSetfocusCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	help_msg = _T("日期规则：选择本任务在哪一天执行。\r\n如果没有适合的日期规则，可以按需自行添加日期规则。");
	UpdateData(FALSE);
}


void RULE_EDIT_DIALOG::OnCbnSetfocusCombo2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	help_msg = _T("执行动作：选择本任务在指定时间执行什么操作。\r\n关机：会关闭计算机；重启：会重启计算机。");
	UpdateData(FALSE);
}


void RULE_EDIT_DIALOG::OnEnSetfocusEdit3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	help_msg = _T("任务备注：填写本任务的备注信息。用于辅助记录任务相关信息。可留空。");
	UpdateData(FALSE);
}


void RULE_EDIT_DIALOG::OnEnSetfocusEdit2()
{
	// TODO: 在此添加控件通知处理程序代码
	//小时编辑框
	sliderTarget = 1;
	ChangeSliderTarget();
	OnEnUpdateEdit2();
	UpdateData(TRUE);
	help_msg = _T("指定时间：指定一个精确的时间执行任务，比如17：30 \r\n程序启动后：指程序启动后多少分钟执行任务，属于倒计时，比如 30 ");
	UpdateData(FALSE);
}



void RULE_EDIT_DIALOG::OnEnUpdateEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CString h1;
	int h2;
	time_h.GetWindowTextW(h1);
	h2 = _ttoi(h1);
	if (h2 > 23) 
	{
		h2 = 23;
		time_h.SetWindowTextW(_T("23"));
	}
	int pos = time_slider.GetPos();
	if (h2 != pos) {
		time_slider.SetPos(h2);
	}
	

}

void RULE_EDIT_DIALOG::OnEnSetfocusEdit4()
{
	// TODO: 在此添加控件通知处理程序代码
	sliderTarget = 2;
	ChangeSliderTarget();
	OnEnUpdateEdit4();
	UpdateData(TRUE);
	help_msg = _T("指定时间：指定一个精确的时间执行任务，比如17：30 \r\n程序启动后：指程序启动后多少分钟执行任务，属于倒计时，比如 30 ");
	UpdateData(FALSE);
	
}


void RULE_EDIT_DIALOG::OnEnUpdateEdit4()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CString h1;
	int h2;
	time_m.GetWindowTextW(h1);
	h2 = _ttoi(h1);
	if (h2 > 59)
	{
		h2 = 59;
		time_m.SetWindowTextW(_T("59"));
	}
	int pos = time_slider.GetPos();
	if (h2 != pos) {
		time_slider.SetPos(h2);
	}


}


void RULE_EDIT_DIALOG::OnEnSetfocusEdit6()
{
	// TODO: 在此添加控件通知处理程序代码
	sliderTarget = 3;
	ChangeSliderTarget();
	OnEnUpdateEdit6();
	UpdateData(TRUE);
	help_msg = _T("指定时间：指定一个精确的时间执行任务，比如17：30 \r\n程序启动后：指程序启动后多少分钟执行任务，属于倒计时，比如 30 ");
	UpdateData(FALSE);
}


void RULE_EDIT_DIALOG::OnEnUpdateEdit6()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数，以将 EM_SETEVENTMASK 消息发送到该控件，
	// 同时将 ENM_UPDATE 标志“或”运算到 lParam 掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CString h1;
	int h2;
	time_countdown.GetWindowTextW(h1);
	h2 = _ttoi(h1);
	if (h2 > 99)
	{
		h2 = 99;
		time_countdown.SetWindowTextW(_T("99"));
	}
	int pos = time_slider.GetPos();
	if (h2 != pos) {
		time_slider.SetPos(h2);
	}
	printf("h2=%d,pos=%d", h2, pos);

}


//void RULE_EDIT_DIALOG::OnEnChangeEdit6()
//{
//	// TODO:  如果该控件是 RICHEDIT 控件，它将不
//	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
//	// 函数并调用 CRichEditCtrl().SetEventMask()，
//	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
//
//	// TODO:  在此添加控件通知处理程序代码
//	CString h1;
//	int h2;
//	time_countdown.GetWindowTextW(h1);
//	h2 = _ttoi(h1);
//	if (h2 > 99)
//	{
//		h2 = 99;
//		time_countdown.SetWindowTextW(_T("99"));
//	}
//	int pos = time_slider.GetPos();
//	if (h2 != pos) {
//		time_slider.SetSelection(h2, h2);
//	}
//
//
//}


//void RULE_EDIT_DIALOG::OnTRBNThumbPosChangingSlider1(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	// 此功能要求 Windows Vista 或更高版本。
//	// _WIN32_WINNT 符号必须 >= 0x0600。
//	NMTRBTHUMBPOSCHANGING *pNMTPC = reinterpret_cast<NMTRBTHUMBPOSCHANGING *>(pNMHDR);
//	// TODO: 在此添加控件通知处理程序代码
//
//	
//	*pResult = 0;
//
//	
//
//}


void RULE_EDIT_DIALOG::ChangeSliderTarget()
{
	//修改滑动条对应的输入框 0：禁用  1：对应小时 2：对应分钟 3：对应1-99
	switch (sliderTarget)
	{
	case 0:
		time_slider.EnableWindow(FALSE);
		break;
	case 1:
		time_slider.EnableWindow(TRUE);
		time_slider.SetRange(0, 23, TRUE);
		break;
	case 2:
		time_slider.EnableWindow(TRUE);
		time_slider.SetRange(0, 59, TRUE);
		break;
	case 3:
		time_slider.EnableWindow(TRUE);
		time_slider.SetRange(1, 99, TRUE);
		break;
	default:
		break;
	}
}


void RULE_EDIT_DIALOG::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
	CString h1;
	int h2;
	switch (sliderTarget)
	{
	case 1:
		time_h.GetWindowTextW(h1);
		break;
	case 2:
		time_m.GetWindowTextW(h1);
		break;
	case 3:
		time_countdown.GetWindowTextW(h1);
		break;
	default:
		break;
	}
	h2 = _ttoi(h1);
	int pos = time_slider.GetPos();
	printf("当前位置是%d", pos);
	if (h2 != pos) 
	{
		h1.Format(_T("%02d"), pos);
		switch (sliderTarget)
		{
		case 1:
			time_h.SetWindowTextW(h1);
			break;
		case 2:
			time_m.SetWindowTextW(h1);
			break;
		case 3:
			time_countdown.SetWindowTextW(h1);
			break;
		default:
			break;
		}
	}
}


void RULE_EDIT_DIALOG::OnNMGetCustomSplitRectRadio1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	help_msg = _T("指定时间：指定一个精确的时间执行任务，比如17：30 \r\n程序启动后：指程序启动后多少分钟执行任务，属于倒计时，比如 30 ");
	UpdateData(FALSE);
}


void RULE_EDIT_DIALOG::OnNMGetCustomSplitRectRadio2(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	help_msg = _T("指定时间：指定一个精确的时间执行任务，比如17：30 \r\n程序启动后：指程序启动后多少分钟执行任务，属于倒计时，比如 30 ");
	UpdateData(FALSE);
}




void RULE_EDIT_DIALOG::OnBnSetfocusRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
}


void RULE_EDIT_DIALOG::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	printf("OnBnClickedRadio2()");
	help_msg = _T("指定时间：指定一个精确的时间执行任务，比如17：30 \r\n程序启动后：指程序启动后多少分钟执行任务，属于倒计时，比如 30 ");

	time_h.ShowWindow(FALSE);
	idc_static_1.ShowWindow(FALSE);
	time_m.ShowWindow(FALSE);
	time_countdown.ShowWindow(TRUE);
	idc_static_countdown1.ShowWindow(TRUE);
	idc_static_countdown2.ShowWindow(TRUE);
	time_type = 1;
	sliderTarget = 3;	
	UpdateData(FALSE);
	ChangeSliderTarget();
	time_countdown.SetFocus();

}


void RULE_EDIT_DIALOG::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	help_msg = _T("指定时间：指定一个精确的时间执行任务，比如17：30 \r\n程序启动后：指程序启动后多少分钟执行任务，属于倒计时，比如 30 ");
	
	time_h.ShowWindow(TRUE);
	idc_static_1.ShowWindow(TRUE);
	time_m.ShowWindow(TRUE);
	time_countdown.ShowWindow(FALSE);
	idc_static_countdown1.ShowWindow(FALSE);
	idc_static_countdown2.ShowWindow(FALSE);
	time_type = 0;
	sliderTarget = 1;
	ChangeSliderTarget();
	time_h.SetFocus();
	UpdateData(FALSE);
}



void RULE_EDIT_DIALOG::OnStnClickedStatic1()
{
	// TODO: 在此添加控件通知处理程序代码
}







//void RULE_EDIT_DIALOG::OnEnKillfocusEdit2()
//{
//	// TODO: 在此添加控件通知处理程序代码
// 	sliderTarget = 0;
// 	ChangeSliderTarget();
//}


//void RULE_EDIT_DIALOG::OnEnKillfocusEdit4()
//{
//	// TODO: 在此添加控件通知处理程序代码
// 	sliderTarget = 0;
// 	ChangeSliderTarget();
//}


//void RULE_EDIT_DIALOG::OnEnKillfocusEdit6()
//{
//	// TODO: 在此添加控件通知处理程序代码
// 	sliderTarget = 0;
// 	ChangeSliderTarget();
//}


void RULE_EDIT_DIALOG::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	//更新记录更新状态
	
	is_change = TRUE;


	//保存任务 新任务：遍历旧任务，避免任务名称重复  旧任务：修改旧数据
	UpdateData(TRUE);
	//IsNewRule = FALSE;
	if (!IsNewRule) 
	{
		times[time_order].name = time_name;
		rule_list1.GetLBText(rule_list1.GetCurSel(), times[time_order].rule);
		rule_actions.GetLBText(rule_actions.GetCurSel(), times[time_order].action);
		if (time_type == 1)
		{
			time_countdown.GetWindowTextW(times[time_order].time);
		}
		else
		{
			CString str1, str2;
			time_h.GetWindowTextW(str1);
			time_m.GetWindowTextW(str2);
			times[time_order].time.Format(_T("%02s:%02s"), str1, str2);
		}
		times[time_order].note = time_remark;
		printf("变更后信息如下\n name:%S\n rule:%S\n time:%S\n action:%S \n note:%S\n", times[time_order].name, times[time_order].rule, times[time_order].time, times[time_order].action, times[time_order].note);

	}
	else
	{
		k_time new_time;
		new_time.name = time_name;
		rule_list1.GetLBText(rule_list1.GetCurSel() , new_time.rule);
		rule_actions.GetLBText(rule_actions.GetCurSel(), new_time.action);
		if (time_type == 1)
		{
			time_countdown.GetWindowTextW(new_time.time);
		}
		else
		{
			CString str1, str2;
			time_h.GetWindowTextW(str1);
			time_m.GetWindowTextW(str2);
			new_time.time.Format(_T("%02s:%02s"), str1, str2);
		}
		new_time.note = time_remark;

		times.push_back(new_time);

		printf("新任务信息如下\n name:%S\n rule:%S\n time:%S\n action:%S \n note:%S\n",new_time.name, new_time.rule, new_time.time, new_time.action, new_time.note);
		
	}

	CDialog::OnOK();
}


void RULE_EDIT_DIALOG::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedRadio2();
}
