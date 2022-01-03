// RULE_EDIT_DIALOG.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ShutdownTimer.h"
#include "RULE_EDIT_DIALOG.h"
#include "afxdialogex.h"

#include "ShutdownTimerDlg.h"
#include <vector>
#include <locale.h>

// RULE_EDIT_DIALOG �Ի���
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


// RULE_EDIT_DIALOG ��Ϣ�������


BOOL RULE_EDIT_DIALOG::OnInitDialog()
{

	CDialogEx::OnInitDialog();

// 	// ��������...���˵�����ӵ�ϵͳ�˵��С�
// 
// 	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	//SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	//SetIcon(m_hIcon, FALSE);		// ����Сͼ��

//	rule_list.AddString(L"h");
	

	 IsNewRule = TRUE;

	///����ִ�ж��� Ĭ���ǹػ�
	CString action = _T("�ػ�");
	time_name = edit_time_name;
	UpdateData(FALSE);
	///����ִ�е����ڹ���Ĭ���ǡ����������ա�
	CString rule = _T("����������");
	//Ĭ�ϰ���ʱ�� ָ��ʱ��17��30
	time_type = 0;
	time_h.LimitText(2);
	time_m.LimitText(2);
	time_countdown.LimitText(2);
	time_h.SetWindowTextW(_T("17"));
	time_m.SetWindowTextW(_T("30"));
	OnBnClickedRadio1();
	UpdateData(FALSE);
	x = 1;

	//���������б�����������ƴ����������б��У�����Ϊ�Ǳ༭�������񣬼�������������Ϣ
	for (int i = 0; i < times.size(); i++) 
	{
		if (times[i].name == edit_time_name) 
		{
			IsNewRule = FALSE;
			time_order = i;
			action = times[i].action;
			rule = times[i].rule;
			if ((times[i].time.GetLength() ==5)&&( times[i].time.Find(CString(":")) == 2))
			{//����ʱ��16��22
				time_h.SetWindowTextW(times[i].time.Left(2));
				time_m.SetWindowTextW(times[i].time.Right(2));
				//����ʱ������ѡ��״̬
				//OnBnClickedRadio1();
				//���»�����ѡ��λ��
				OnEnUpdateEdit2();
			}
			else
			{//����ʱ 30
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
		//x.Format(_T("%S"), "�й�");
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	help_msg = _T("�������ƣ���¼����������ƣ����޸ġ�");
	UpdateData(FALSE);
}


void RULE_EDIT_DIALOG::OnCbnSetfocusCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	help_msg = _T("���ڹ���ѡ����������һ��ִ�С�\r\n���û���ʺϵ����ڹ��򣬿��԰�������������ڹ���");
	UpdateData(FALSE);
}


void RULE_EDIT_DIALOG::OnCbnSetfocusCombo2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	help_msg = _T("ִ�ж�����ѡ��������ָ��ʱ��ִ��ʲô������\r\n�ػ�����رռ�������������������������");
	UpdateData(FALSE);
}


void RULE_EDIT_DIALOG::OnEnSetfocusEdit3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	help_msg = _T("����ע����д������ı�ע��Ϣ�����ڸ�����¼���������Ϣ�������ա�");
	UpdateData(FALSE);
}


void RULE_EDIT_DIALOG::OnEnSetfocusEdit2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//Сʱ�༭��
	sliderTarget = 1;
	ChangeSliderTarget();
	OnEnUpdateEdit2();
	UpdateData(TRUE);
	help_msg = _T("ָ��ʱ�䣺ָ��һ����ȷ��ʱ��ִ�����񣬱���17��30 \r\n����������ָ������������ٷ���ִ���������ڵ���ʱ������ 30 ");
	UpdateData(FALSE);
}



void RULE_EDIT_DIALOG::OnEnUpdateEdit2()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	sliderTarget = 2;
	ChangeSliderTarget();
	OnEnUpdateEdit4();
	UpdateData(TRUE);
	help_msg = _T("ָ��ʱ�䣺ָ��һ����ȷ��ʱ��ִ�����񣬱���17��30 \r\n����������ָ������������ٷ���ִ���������ڵ���ʱ������ 30 ");
	UpdateData(FALSE);
	
}


void RULE_EDIT_DIALOG::OnEnUpdateEdit4()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	sliderTarget = 3;
	ChangeSliderTarget();
	OnEnUpdateEdit6();
	UpdateData(TRUE);
	help_msg = _T("ָ��ʱ�䣺ָ��һ����ȷ��ʱ��ִ�����񣬱���17��30 \r\n����������ָ������������ٷ���ִ���������ڵ���ʱ������ 30 ");
	UpdateData(FALSE);
}


void RULE_EDIT_DIALOG::OnEnUpdateEdit6()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// �������Խ� EM_SETEVENTMASK ��Ϣ���͵��ÿؼ���
	// ͬʱ�� ENM_UPDATE ��־�������㵽 lParam �����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
//	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
//	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
//	// ���������� CRichEditCtrl().SetEventMask()��
//	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
//
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
//	// �˹���Ҫ�� Windows Vista ����߰汾��
//	// _WIN32_WINNT ���ű��� >= 0x0600��
//	NMTRBTHUMBPOSCHANGING *pNMTPC = reinterpret_cast<NMTRBTHUMBPOSCHANGING *>(pNMHDR);
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//
//	
//	*pResult = 0;
//
//	
//
//}


void RULE_EDIT_DIALOG::ChangeSliderTarget()
{
	//�޸Ļ�������Ӧ������� 0������  1����ӦСʱ 2����Ӧ���� 3����Ӧ1-99
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

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
	printf("��ǰλ����%d", pos);
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	help_msg = _T("ָ��ʱ�䣺ָ��һ����ȷ��ʱ��ִ�����񣬱���17��30 \r\n����������ָ������������ٷ���ִ���������ڵ���ʱ������ 30 ");
	UpdateData(FALSE);
}


void RULE_EDIT_DIALOG::OnNMGetCustomSplitRectRadio2(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	help_msg = _T("ָ��ʱ�䣺ָ��һ����ȷ��ʱ��ִ�����񣬱���17��30 \r\n����������ָ������������ٷ���ִ���������ڵ���ʱ������ 30 ");
	UpdateData(FALSE);
}




void RULE_EDIT_DIALOG::OnBnSetfocusRadio1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void RULE_EDIT_DIALOG::OnBnClickedRadio2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	printf("OnBnClickedRadio2()");
	help_msg = _T("ָ��ʱ�䣺ָ��һ����ȷ��ʱ��ִ�����񣬱���17��30 \r\n����������ָ������������ٷ���ִ���������ڵ���ʱ������ 30 ");

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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	help_msg = _T("ָ��ʱ�䣺ָ��һ����ȷ��ʱ��ִ�����񣬱���17��30 \r\n����������ָ������������ٷ���ִ���������ڵ���ʱ������ 30 ");
	
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}







//void RULE_EDIT_DIALOG::OnEnKillfocusEdit2()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
// 	sliderTarget = 0;
// 	ChangeSliderTarget();
//}


//void RULE_EDIT_DIALOG::OnEnKillfocusEdit4()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
// 	sliderTarget = 0;
// 	ChangeSliderTarget();
//}


//void RULE_EDIT_DIALOG::OnEnKillfocusEdit6()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
// 	sliderTarget = 0;
// 	ChangeSliderTarget();
//}


void RULE_EDIT_DIALOG::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//���¼�¼����״̬
	
	is_change = TRUE;


	//�������� �����񣺱��������񣬱������������ظ�  �������޸ľ�����
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
		printf("�������Ϣ����\n name:%S\n rule:%S\n time:%S\n action:%S \n note:%S\n", times[time_order].name, times[time_order].rule, times[time_order].time, times[time_order].action, times[time_order].note);

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

		printf("��������Ϣ����\n name:%S\n rule:%S\n time:%S\n action:%S \n note:%S\n",new_time.name, new_time.rule, new_time.time, new_time.action, new_time.note);
		
	}

	CDialog::OnOK();
}


void RULE_EDIT_DIALOG::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnBnClickedRadio2();
}
