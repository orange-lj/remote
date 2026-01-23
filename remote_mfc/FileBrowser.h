#pragma once
#include "afxdialogex.h"
#include "MyEvent.h"
#include "TaskEngine.h"
#include <any>
#include <utility>
#include <vector>
#define WM_EXEC_TASK (WM_USER + 200)

struct ExecTaskMsg
{
	uint64_t tid;
	int error;
	uint32_t command;
	std::any replyData;
	MyEvent* pEvent;
	uint32_t* pRet;
};

// FileBrowser 对话框

class FileBrowser : public CDialogEx, public TaskCallback
{
	DECLARE_DYNAMIC(FileBrowser)

public:
	FileBrowser(TaskEngine* pTaskEngine,CWnd* pParent = nullptr);   // 标准构造函数
	~FileBrowser();
	int Result(uint32_t command, uint32_t error, std::vector<CString> savedArgs, std::any replyData);
	void updateDiskList(std::vector<std::pair<CString, int >>);
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG5 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg LRESULT OnExecTask(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

private:
	TaskEngine* m_FileEngine;
public:
	CComboBox m_Local_Directory_ComboBox;
	CComboBox m_Remote_Directory_ComboBox;
	CListCtrl m_list_local;
	CListCtrl m_list_remote;
	afx_msg void OnBnClickedButton1();
};
