
// remote_mfcDlg.h: 头文件
//

#pragma once
#include "PublicStructh.h"
#include "ListenersManager.h"
#include "TunnelHelpServer.h"
#include "OneTabDialog.h"
#include "Manager.h"
#include "TaskEngine.h"
//#include "TaskE"
#include <Map>

// 在头文件中定义消息
#define WM_UPDATE_HOST_INFO   (WM_USER + 100)

// 或者使用更安全的 RegisterWindowMessage
static UINT WM_UPDATE_HOSTINFO_MSG = ::RegisterWindowMessage(_T("WM_UPDATE_HOSTINFO"));

class ListenersManager;
class TunnelHelpServer;
class OneTabDialog;
class Manager;
class TaskEngine;
// CremotemfcDlg 对话框
class CremotemfcDlg : public CDialogEx
{
// 构造
public:
	CremotemfcDlg(CWnd* pParent = nullptr);	// 标准构造函数
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REMOTE_MFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	// 消息处理函数
	afx_msg LRESULT OnUpdateHostInfo(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	void saveDB();
	HostInfo hostInfoFromItem(int nRowIndex);
	void UpdateRowColor(int nRowIndex, const HostInfo& hostinfo);
	bool AddNewRow(const HostInfo& hostinfo);
	std::vector<std::shared_ptr<ListenersManager>> m_vecListenersManager;
	std::map<std::string, std::shared_ptr<Manager>> m_manageServers;
	std::mutex m_resourceLock;
	std::shared_ptr<TunnelHelpServer> m_pTunnelHelpServer;
	OneTabDialog* m_OneTabDialog;
	CListCtrl m_CList_Online;
	#define COLUMN_ONLINE_COUNT 12			// 在线列表的个数
	int m_Column_Online_Width = 0;		// 在线列表宽度和
	COLUMNSTRUCT m_Column_Online_Data[COLUMN_ONLINE_COUNT] =
	{
		{"id",				80	},
		{"sid",			80	},
		{"hostname",	180	},
		{"lan",		158	},
		{"username",	80	},
		{"pid",			50	},
		{"os",			50	},
		{"osType",			50},
		{"osArch",			50},
		{"protocol",			50},
		{"wan",			85},
		{"currentTime",			100},
	};

	std::string m_savePath;
	int		InitMyMenu();		// 初始化主页面上方菜单
	int		InitList();			// 初始化list控件信息
	int		InitTab();			// 初始化tab控件信息
	// 实际更新函数
	void RealUpdateHostInfo(const HostInfo& hostinfo);
	// 辅助结构体，用于传递数据
	struct UpdateHostInfoData
	{
		HostInfo info;
	};
	TaskEngine* m_pTaskEngine;
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnOpenLisrenersDialog();
	afx_msg void OnCreatorDialog();
	std::shared_ptr<ListenersManager> GetListenersManager();
	std::shared_ptr<Manager> RegistManageServer(std::string sid, std::shared_ptr<Manager>);
	CTabCtrl tab;
	// 更新接口 - 可以从任何线程调用
	void UpdateHostInfo(const HostInfo& hostinfo);
	TaskEngine* GetTaskEngine();
	std::shared_ptr<Manager> GetManager(std::string sid);
};
