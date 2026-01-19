// FileBrowser.cpp: 实现文件
//

#include "pch.h"
#include "remote_mfc.h"
#include "afxdialogex.h"
#include "FileBrowser.h"


// FileBrowser 对话框

IMPLEMENT_DYNAMIC(FileBrowser, CDialogEx)

FileBrowser::FileBrowser(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG5, pParent)
{

}

FileBrowser::~FileBrowser()
{
}

void FileBrowser::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(FileBrowser, CDialogEx)
END_MESSAGE_MAP()


// FileBrowser 消息处理程序
