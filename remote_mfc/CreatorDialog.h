#pragma once
#include "afxdialogex.h"


// CreatorDialog 对话框

class CreatorDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CreatorDialog)

public:
	CreatorDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CreatorDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
private:
	bool saveFile(CString srcPath, CString newPath);
};
