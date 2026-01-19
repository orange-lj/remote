#pragma once
#include "afxdialogex.h"
#include "PluginManage.h"
#include "FileBrowser.h"


// OneTabDialog 对话框

class OneTabDialog : public CDialogEx
{
	DECLARE_DYNAMIC(OneTabDialog)

public:
	OneTabDialog(CWnd* pParent = nullptr);   // 标准构造函数
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
	
	// 子对话框指针
	PluginManage* m_pPluginManage;
	FileBrowser* m_pFileBrowser;
	
	virtual BOOL OnInitDialog();
	//afx_msg void OnTabChanged(NMHDR*, LRESULT*);
	afx_msg void OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
};
