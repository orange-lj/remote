#pragma once
#include "afxdialogex.h"
#include "PluginManager.h"
#include "FileBrowser.h"
#include "HostInfo.h"
#include "remote_mfcDlg.h"
#include "FileBrowser.h"
// OneTabDialog 对话框
class CremotemfcDlg;
class PluginManager;
class FileBrowser;
class OneTabDialog : public CDialogEx
{
	DECLARE_DYNAMIC(OneTabDialog)

public:
	OneTabDialog(CremotemfcDlg* pMainDlg, TaskEngine* pTaskEngine,CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~OneTabDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_funcTab;
	CImageList m_tabImg;
	

	CremotemfcDlg* m_pMainWindow;
	// 子对话框指针
	//PluginManager* m_pPluginManager;
	FileBrowser* m_pFileBrowser;
	TaskEngine* m_OneDialogEngine;
	virtual BOOL OnInitDialog();

	//afx_msg void OnTabChanged(NMHDR*, LRESULT*);
	afx_msg void OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
};
