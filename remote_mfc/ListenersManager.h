#pragma once
#include "afxdialogex.h"


// ListenersManager 对话框
class CremotemfcDlg;
class ListenersManager : public CDialogEx
{
	DECLARE_DYNAMIC(ListenersManager)

public:
	ListenersManager(CremotemfcDlg* pMainDlg, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ListenersManager();
private:
	CremotemfcDlg* m_pMainDlg;  // 指向主对话框的指针
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
