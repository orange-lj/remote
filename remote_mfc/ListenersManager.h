#pragma once
#include "afxdialogex.h"
#include "remote_mfcDlg.h"
#include "../common/net/Listener.h"

typedef std::tuple<CString, int, std::shared_ptr<Listener> > ListenerInfo;

// ListenersManager 对话框
class CremotemfcDlg;
class ListenersManager : public CDialogEx, public std::enable_shared_from_this<ListenersManager>
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
public:
	afx_msg void OnBnClickedButton1();
	//afx_msg void OnCbnSelchangeCombo1();
	CComboBox m_pProtocol;
	CEdit m_pPortEdit;
	int Start(CString protocol, int port);
private:
	std::map<CString, ListenerInfo> m_listeners;
	CString BuildKey(CString protocol, int port);
	static void ListenThread(std::shared_ptr<ListenersManager> pSelf, std::shared_ptr<Listener> pListener);
	void ListenWorker(std::shared_ptr<Listener> pListener);
	static void ServiceThread(std::shared_ptr<ListenersManager> pSelf, std::shared_ptr<Conn> pConn);
	void ServiceWorker(std::shared_ptr<Conn> pConn);
};
