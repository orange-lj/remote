// PluginManage.cpp: 实现文件
//

#include "pch.h"
#include "remote_mfc.h"
#include "afxdialogex.h"
#include "PluginManage.h"


// PluginManage 对话框

IMPLEMENT_DYNAMIC(PluginManage, CDialogEx)

PluginManage::PluginManage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG4, pParent)
{

}

PluginManage::~PluginManage()
{
}

void PluginManage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(PluginManage, CDialogEx)
END_MESSAGE_MAP()


// PluginManage 消息处理程序
