// OneTabDialog.cpp: 实现文件
//

#include "pch.h"
#include "remote_mfc.h"
#include "afxdialogex.h"
#include "OneTabDialog.h"
#include "FileBrowser.h"
#include "PluginManage.h"

// OneTabDialog 对话框

IMPLEMENT_DYNAMIC(OneTabDialog, CDialogEx)

OneTabDialog::OneTabDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
	, m_pPluginManage(nullptr)
	, m_pFileBrowser(nullptr)
{
	
}

OneTabDialog::~OneTabDialog()
{
	// 释放子对话框内存
	if (m_pPluginManage)
	{
		delete m_pPluginManage;
		m_pPluginManage = nullptr;
	}
	if (m_pFileBrowser)
	{
		delete m_pFileBrowser;
		m_pFileBrowser = nullptr;
	}
}

void OneTabDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_funcTab);
}

BOOL OneTabDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_tabImg.Create(24, 24, ILC_COLOR32 | ILC_MASK, 3, 3);
	m_tabImg.Add(AfxGetApp()->LoadIcon(IDI_ICON3));
	m_tabImg.Add(AfxGetApp()->LoadIcon(IDI_ICON3));

	m_funcTab.SetImageList(&m_tabImg);
	m_funcTab.DeleteAllItems();

	TCITEM item = { 0 };
	item.mask = TCIF_IMAGE;

	item.iImage = 0; m_funcTab.InsertItem(0, &item);
	item.iImage = 1; m_funcTab.InsertItem(1, &item);

	// 获取对话框客户区大小
	CRect rc;
	GetClientRect(&rc);
	
	// 让 m_funcTab 填满整个对话框
	m_funcTab.MoveWindow(rc);
	
	// 获取 Tab 控件的显示区域(去掉tab页签后的区域)
	// 注意:这里要重新获取 Tab 控件的客户区,因为 MoveWindow 后坐标系统已经是相对于 Tab 控件的
	m_funcTab.GetClientRect(&rc);
	m_funcTab.AdjustRect(FALSE, &rc);

	// 创建子对话框并设置到调整后的区域
	m_pPluginManage = new PluginManage();
	m_pPluginManage->Create(IDD_DIALOG4, &m_funcTab);
	m_pPluginManage->MoveWindow(&rc);

	m_pFileBrowser = new FileBrowser();
	m_pFileBrowser->Create(IDD_DIALOG5, &m_funcTab);
	m_pFileBrowser->MoveWindow(&rc);

	// 默认显示第一个
	m_pPluginManage->ShowWindow(SW_SHOW);
	m_pFileBrowser->ShowWindow(SW_HIDE);
	return 0;
}


BEGIN_MESSAGE_MAP(OneTabDialog, CDialogEx)
	//ON_NOTIFY(TCN_SELCHANGE, IDC_FUNC_TAB, &OneTabDialog::OnTabChanged)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &OneTabDialog::OnTcnSelchangeTab1)
END_MESSAGE_MAP()



void OneTabDialog::OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// 获取当前选中的tab索引
	int idx = m_funcTab.GetCurSel();
	
	// 根据索引显示/隐藏对应的子对话框
	if (m_pPluginManage)
		m_pPluginManage->ShowWindow(idx == 0 ? SW_SHOW : SW_HIDE);
	if (m_pFileBrowser)
		m_pFileBrowser->ShowWindow(idx == 1 ? SW_SHOW : SW_HIDE);
	
	*pResult = 0;
}
