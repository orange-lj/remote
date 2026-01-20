
// remote_mfcDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "remote_mfc.h"
#include "remote_mfcDlg.h"
#include "afxdialogex.h"
#include "CreatorDialog.h"
#include <locale>
#include <codecvt>
#include <fstream>
#include <iostream>
#include <sstream>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CremotemfcDlg 对话框



CremotemfcDlg::CremotemfcDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_REMOTE_MFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	WCHAR strTempW[MAX_PATH];
	//得到文件名
	GetModuleFileNameW(NULL, strTempW, MAX_PATH);
	// 去掉文件名
	WCHAR* pLastSlash = wcsrchr(strTempW, L'\\');
	if (pLastSlash)
	{
		*pLastSlash = L'\0';
	}
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	std::wstring wstrDir(strTempW);
	m_savePath = converter.to_bytes(strTempW) + "\\hlist.db";

	m_pTunnelHelpServer = std::make_shared<TunnelHelpServer>(this);
	m_pTunnelHelpServer->Start();
	//m_pTunnelHelpServer = std::make_shared<TunnelHelpServer>(this);
}

void CremotemfcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_CList_Online);
	DDX_Control(pDX, IDC_TAB1, tab);
}

BEGIN_MESSAGE_MAP(CremotemfcDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_COMMAND(ID_32772, &CremotemfcDlg::OnOpenLisrenersDialog)
	ON_COMMAND(ID_32773, &CremotemfcDlg::OnCreatorDialog)
	ON_REGISTERED_MESSAGE(WM_UPDATE_HOSTINFO_MSG, OnUpdateHostInfo)
END_MESSAGE_MAP()


// CremotemfcDlg 消息处理程序

LRESULT CremotemfcDlg::OnUpdateHostInfo(WPARAM wParam, LPARAM lParam)
{
	UpdateHostInfoData* pData = (UpdateHostInfoData*)wParam;
	if (pData)
	{
		try
		{
			RealUpdateHostInfo(pData->info);
		}
		catch (...)
		{
			// 异常处理
			TRACE(_T("Exception in OnUpdateHostInfo\n"));
		}

		// 释放动态分配的内存
		delete pData;
	}
	return 0;
}

BOOL CremotemfcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	// 初始化菜单控件
	InitMyMenu();	
	// 初始化列表控件
	InitList();		
	// 初始化tab控件
	InitTab();
	//---------改变窗口大小触发动态调整-------|
	CRect rect;
	GetWindowRect(&rect);
	rect.bottom += 50;
	rect.right += 30;
	MoveWindow(rect);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CremotemfcDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CremotemfcDlg::OnPaint()
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
HCURSOR CremotemfcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CremotemfcDlg::saveDB()
{
	// 删除旧文件
	DeleteFileA(m_savePath.c_str());
	// 创建并写入文件
	std::ofstream outFile(m_savePath, std::ios::out | std::ios::binary);
	if (!outFile.is_open())
	{
		return;
	}
	// 构建数据
	std::stringstream ss;

	int nItemCount = m_CList_Online.GetItemCount();
	for (int i = 0; i < nItemCount; i++)
	{
		// 从列表项构建HostInfo
		HostInfo hostinfo = hostInfoFromItem(i);

		// 添加到字符串流
		ss << hostinfo.toString() << "\n";
	}

	// 写入文件
	outFile << ss.str();
	outFile.close();
}


HostInfo CremotemfcDlg::hostInfoFromItem(int nRowIndex)
{
	HostInfo hostinfo;

	for (int i = 0; i < HostInfo::COUNT; i++)
	{
		CStringA cstrA(m_CList_Online.GetItemText(nRowIndex, i));
		std::string str = cstrA.GetString();
		hostinfo.set(i, str);
	}
	return hostinfo;
}

void CremotemfcDlg::UpdateRowColor(int nRowIndex, const HostInfo& hostinfo)
{
	std::string strOnline = hostinfo.get(HostInfo::ONLINE);

	bool bOnline = false;
	if (strOnline == HOST_STATUS_ONLINE) {

		bOnline = true;
	}
	//for (int i = 0; i < HostInfo::COUNT; i++)
	//{
		if (bOnline)
		{
			m_CList_Online.SetTextColor(RGB(0, 0, 255));      // 蓝色
		}
		else
		{
			m_CList_Online.SetTextColor(RGB(128, 128, 128));  // 灰色
		}
	//}
}

bool CremotemfcDlg::AddNewRow(const HostInfo& hostinfo)
{
	if (!m_CList_Online.GetSafeHwnd())
		return false;

	// 1. 先插入一个空行（选择插入位置）
	int nInsertPos = 0;  // 插入到第一行，保持最新在最上面
	// 或者插入到最后：int nInsertPos = m_CList_Online.GetItemCount();

	// 插入行，并设置第一列的数据
	std::string strFirstCol = hostinfo.get(HostInfo::HOSTID);
	int nNewRow = m_CList_Online.InsertItem(nInsertPos, CString(strFirstCol.c_str()));

	if (nNewRow < 0)
		return false;

	// 2. 设置其他列的数据（从第1列开始，因为第0列已经在InsertItem中设置了）
	for (int j = 1; j < HostInfo::COUNT; j++)
	{
		CString strValue(hostinfo.get(j).c_str());
		m_CList_Online.SetItemText(nNewRow, j, strValue);
	}

	// 3. 设置行颜色
	UpdateRowColor(nNewRow, hostinfo);
	return true;
}

int CremotemfcDlg::InitMyMenu()
{
	HMENU hmenu;
	hmenu = LoadMenu(NULL, MAKEINTRESOURCE(IDR_MENU1)); // 载入菜单资源
	::SetMenu(this->GetSafeHwnd(), hmenu);                  // 为窗口设置菜单

	return 0;
}

int CremotemfcDlg::InitList()
{
	// CLR_NONE没有背景色。图像是透明的。
	m_CList_Online.SetTextBkColor(CLR_NONE);
	m_CList_Online.SetBkColor(CLR_NONE);
	m_CList_Online.SetTextColor(RGB(255, 0, 0));

	/*m_CList_Message.SetTextBkColor(CLR_NONE);
	m_CList_Message.SetBkColor(CLR_NONE);*/
	// m_CList_Message.SetTextColor(RGB(255, 0, 0));

	// 设置list可选中
	m_CList_Online.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	//m_CList_Message.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	// 计算控件宽度
	for (int i = 0; i < COLUMN_ONLINE_COUNT; i++)
	{
		CString columnTitle(m_Column_Online_Data[i].title); // 将 title 转换为 CString
		m_CList_Online.InsertColumn(i, columnTitle, LVCFMT_LEFT, m_Column_Online_Data[i].nWidth);
		m_Column_Online_Width += m_Column_Online_Data[i].nWidth;
	}
	return 0;
}

int CremotemfcDlg::InitTab()
{
	//tab.InsertItem(0, _T("事件"));
	//tab.InsertItem(0, _T("监听"));
	tab.InsertItem(0, _T("控制台"));
	m_OneTabDialog = new OneTabDialog();
	m_OneTabDialog->Create(IDD_DIALOG3, &tab);

	m_OneTabDialog->SetParent(&tab);

	// 设置对话框位置和大小
	CRect rcTab;
	tab.GetClientRect(&rcTab);
	tab.AdjustRect(FALSE, &rcTab);

	m_OneTabDialog->MoveWindow(&rcTab);
	m_OneTabDialog->ShowWindow(SW_SHOW);
	// 你可以根据实际需要调整偏移和大小
	//rcTab.top += 30; // 下移一点，避免tab头部
	//rcTab.bottom -= 5;
	//rcTab.left += 5;
	//rcTab.right -= 5;

	tab.SetCurSel(0);
	return 0;
}

void CremotemfcDlg::RealUpdateHostInfo(const HostInfo& hostinfo)
{
	// 检查控件是否有效
	if (!m_CList_Online.GetSafeHwnd())
		return;

	bool bFound = false;
	int nItemCount = m_CList_Online.GetItemCount();

	std::string strSessionID = hostinfo.get(HostInfo::SESSIONID);
	CString cstrSessionID(strSessionID.c_str());  // 转换为CString
	for (int i = 0; i < nItemCount; i++)
	{
		CString strItemSession = m_CList_Online.GetItemText(i, 1); // 假设sessionid在第1列
		if (strItemSession == cstrSessionID)
		{
			// 更新已存在的行
			for (int j = 0; j < HostInfo::COUNT; j++) {
				
				// 将std::string转换为CString
				CString strValue(hostinfo.get(j).c_str());
				// 使用SetItemText设置每个单元格的内容
				m_CList_Online.SetItemText(i, j, strValue);
			}
			UpdateRowColor(i, hostinfo);
			bFound = true;
			break;
		}
	}
	// 如果没找到，添加新行
	if (!bFound)
	{
		AddNewRow(hostinfo);
	}

	saveDB();
}



void CremotemfcDlg::OnSize(UINT nType, int cx, int cy)
{
	//double dcx = cx;     //对话框的总宽度
	//CDialogEx::OnSize(nType, cx, cy);

	//if (SIZE_MINIMIZED == nType)//当窗口最小化避免大小为0造成崩溃直接返回
	//	return;

	//if (m_CList_Online.m_hWnd != NULL)
	//{
	//	CRect rc;
	//	rc.left = 1;			// 列表的左坐标
	//	rc.top = 80;			// 列表的上坐标
	//	rc.right = cx - 1;		// 列表的右坐标
	//	rc.bottom = cy - 160;	// 列表的下坐标
	//	m_CList_Online.MoveWindow(rc);

	//	for (int i = 0; i < COLUMN_ONLINE_COUNT; i++) {     // 遍历每一个列
	//		double dd = m_Column_Online_Data[i].nWidth;     // 得到当前列的宽度
	//		dd /= m_Column_Online_Width;                    // 看一看当前宽度占总长度的几分之几
	//		dd *= dcx;                                      // 用原来的长度乘以所占的几分之几得到当前的宽度
	//		int lenth = dd;                                 // 转换为int 类型
	//		m_CList_Online.SetColumnWidth(i, (lenth));      // 设置当前的宽度
	//	}
	//}
}


void CremotemfcDlg::OnOpenLisrenersDialog()
{
	// TODO: 在此添加命令处理程序代码
	// 创建新的 ListenersManager 实例
	auto pListenersManager = std::make_shared<ListenersManager>(this);

	// 创建对话框
	if (!pListenersManager->Create(IDD_DIALOG1, &tab))
	{
		AfxMessageBox(_T("ListenersManager 创建失败！"));
		return;
	}

	// 添加到管理列表
	m_vecListenersManager.push_back(pListenersManager);

	// 创建唯一的 tab 标题
	int nIndex = m_vecListenersManager.size();
	CString strTabTitle;
	strTabTitle.Format(_T("监听器 %d"), nIndex);

	// 插入新的 tab（插入到控制台tab之前）
	int nInsertIndex = tab.GetItemCount(); // 在控制台tab之前插入
	if (nInsertIndex < 0) nInsertIndex = 0;
	tab.InsertItem(nInsertIndex, strTabTitle);

	// 设置对话框的父窗口为 tab 控件
	pListenersManager->SetParent(&tab);

	// 设置对话框位置和大小
	CRect rcTab;
	tab.GetClientRect(&rcTab);
	tab.AdjustRect(FALSE, &rcTab);

	pListenersManager->MoveWindow(&rcTab);

	// 隐藏其他页面
	if (m_OneTabDialog)
	{
		m_OneTabDialog->ShowWindow(SW_HIDE);
	}
	for (auto& dlg : m_vecListenersManager)
	{
		if (dlg && dlg != pListenersManager)
		{
			dlg->ShowWindow(SW_HIDE);
		}
	}

	pListenersManager->ShowWindow(SW_SHOW);

	// 切换到新创建的 tab
	tab.SetCurSel(nInsertIndex);
}


void CremotemfcDlg::OnCreatorDialog()
{
	// TODO: 在此添加命令处理程序代码
	CreatorDialog dialog(this);
	dialog.DoModal();
}

std::shared_ptr<ListenersManager> CremotemfcDlg::GetListenersManager()
{
	int nCurrentTab = tab.GetCurSel();
	if (nCurrentTab >= 0 && nCurrentTab <= (int)m_vecListenersManager.size())
	{
		return m_vecListenersManager[nCurrentTab-1];
	}
	return nullptr;
}

std::shared_ptr<Manager> CremotemfcDlg::RegistManageServer(std::string sid, std::shared_ptr<Manager> pManager)
{
	std::lock_guard<std::mutex> guard(m_resourceLock);
	std::shared_ptr<Manager> pPrev;
	auto iter = m_manageServers.find(sid);
	if (iter != m_manageServers.end())
	{
		pPrev = iter->second;
	}
	m_manageServers[sid] = pManager;
	return pPrev;
}

void CremotemfcDlg::UpdateHostInfo(const HostInfo& hostinfo)
{
	// 获取主窗口线程ID
	DWORD dwMainThreadId = 0;
	if (AfxGetApp() && AfxGetApp()->m_pMainWnd)
	{
		//dwMainThreadId = AfxGetApp()->m_pMainWnd->GetWindowThreadProcessId();
	}

	// 获取当前线程ID
	DWORD dwCurrentThreadId = ::GetCurrentThreadId();

	// 如果在主线程，直接处理
	if (dwCurrentThreadId == dwMainThreadId)
	{
		RealUpdateHostInfo(hostinfo);
	}
	else
	{
		// 在非主线程，发送消息到主线程
		// 动态分配数据，确保生命周期跨线程
		UpdateHostInfoData* pData = new UpdateHostInfoData;
		pData->info = hostinfo;

		// 使用PostMessage异步发送，不阻塞工作线程
		if (GetSafeHwnd() != NULL)
		{
			::PostMessage(GetSafeHwnd(), WM_UPDATE_HOSTINFO_MSG,
				(WPARAM)pData, 0);
		}
		else
		{
			// 如果窗口句柄无效，清理内存
			delete pData;
		}
	}
}

