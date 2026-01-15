// ListenersManager.cpp: 实现文件
//

#include "pch.h"
#include "remote_mfc.h"
#include "afxdialogex.h"
#include "ListenersManager.h"
#include "common/net/cotp.h"
#include "common/net/LisFacto.h"


// ListenersManager 对话框

IMPLEMENT_DYNAMIC(ListenersManager, CDialogEx)

ListenersManager::ListenersManager(CremotemfcDlg* pMainDlg, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent),
	m_pMainDlg(pMainDlg)
{

}

ListenersManager::~ListenersManager()
{
}

void ListenersManager::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_pProtocol);
	DDX_Control(pDX, IDC_EDIT1, m_pPortEdit);
}


BEGIN_MESSAGE_MAP(ListenersManager, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &ListenersManager::OnBnClickedButton1)
	//ON_CBN_SELCHANGE(IDC_COMBO1, &ListenersManager::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// ListenersManager 消息处理程序


void ListenersManager::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString protocol,strport;

	m_pProtocol.GetWindowText(protocol);
	m_pPortEdit.GetWindowText(strport);

	int port = _ttoi(strport);
	if ((port <= 0) || (protocol.IsEmpty())) {
		
		AfxMessageBox(L"协议或端口号无效");
		return;
	}

	m_pMainDlg->GetListenersManager()->Start(protocol, port);
}

int ListenersManager::Start(CString protocol, int port)
{
	int error = 0;

	CStringA strA(protocol);  // 先转为 ANSI
	int connType = ConnTypeFromStr(strA.GetString());

	//CString str;
	//str.Format(_T("%d"), connType);
	//OutputDebugStringW(str);

	std::shared_ptr<Listener> pListener = LisFacto::CreateListener(connType, 0, port);
	if (!pListener)
	{
		return 1;
	}

	error = pListener->Start();
	if (error)
	{
		return error;
	}

	CString key = BuildKey(protocol, port);
	ListenerInfo info = std::make_tuple(protocol, port, pListener);
	m_listeners.insert(std::make_pair(key, info));

	std::thread t(ListenThread, shared_from_this(), pListener);
	t.detach();

	return 0;
}

CString ListenersManager::BuildKey(CString protocol, int port)
{
	CString strKey;
	strKey.Format(_T("%s%d"), protocol, port);
	return strKey;
}

void ListenersManager::ListenThread(std::shared_ptr<ListenersManager> pSelf, std::shared_ptr<Listener> pListener)
{
	while (1) {
		MessageBoxA(0, 0, 0, 0);
	}
}


//void ListenersManager::OnCbnSelchangeCombo1()
//{
//	// TODO: 在此添加控件通知处理程序代码
//}
