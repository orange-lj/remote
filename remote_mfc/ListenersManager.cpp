// ListenersManager.cpp: 实现文件
//

#include "pch.h"
#include "remote_mfc.h"
#include "afxdialogex.h"
#include "ListenersManager.h"


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
}


BEGIN_MESSAGE_MAP(ListenersManager, CDialogEx)
END_MESSAGE_MAP()


// ListenersManager 消息处理程序
