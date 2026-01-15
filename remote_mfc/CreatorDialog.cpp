// CreatorDialog.cpp: 实现文件
//

#include "pch.h"
#include "remote_mfc.h"
#include "afxdialogex.h"
#include "CreatorDialog.h"


// CreatorDialog 对话框

IMPLEMENT_DYNAMIC(CreatorDialog, CDialogEx)

CreatorDialog::CreatorDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

CreatorDialog::~CreatorDialog()
{
}

void CreatorDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CreatorDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CreatorDialog::OnBnClickedButton1)
END_MESSAGE_MAP()


// CreatorDialog 消息处理程序


void CreatorDialog::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//获取当前进程的所在路径
	WCHAR strTempW[MAX_PATH];
	//得到文件名
	GetModuleFileNameW(NULL, strTempW, MAX_PATH);  

	CStringW strCurrentPathW;

	strCurrentPathW = strTempW;

	strCurrentPathW = strCurrentPathW.Left(strCurrentPathW.ReverseFind('\\'));

	CStringW exePath = strCurrentPathW + "\\devenv.exe";
	OutputDebugStringW(exePath);
	saveFile(L":/raw/x64/devenv.exe", exePath);
}

bool CreatorDialog::saveFile(CString srcPath, CString newPath)
{
	// 打开源文件
	CFile srcFile;
	if (!srcFile.Open(srcPath, CFile::modeRead | CFile::shareDenyWrite)) {
		return false;
	}

	// 删除目标文件（如果存在）
	CFile::Remove(newPath);

	// 创建目标文件
	CFile dstFile;
	if (!dstFile.Open(newPath, CFile::modeCreate | CFile::modeWrite)) {
		srcFile.Close();
		return false;
	}

	// 读取源文件内容
	ULONGLONG fileLen = srcFile.GetLength();
	BYTE* buffer = new BYTE[(size_t)fileLen];
	srcFile.Read(buffer, (UINT)fileLen);

	// 写入目标文件
	dstFile.Write(buffer, (UINT)fileLen);

	// 清理
	delete[] buffer;
	srcFile.Close();
	dstFile.Close();
	return false;
}
