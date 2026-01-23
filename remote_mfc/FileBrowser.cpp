// FileBrowser.cpp: 实现文件
//

#include "pch.h"
#include "remote_mfc.h"
#include "afxdialogex.h"
#include "FileBrowser.h"
#include "remote_mfcDlg.h"
#include "../common/proto.h"


// FileBrowser 对话框

IMPLEMENT_DYNAMIC(FileBrowser, CDialogEx)

FileBrowser::FileBrowser(TaskEngine* pTaskEngine,CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG5, pParent),
    m_FileEngine(pTaskEngine),
    TaskCallback(pTaskEngine)
{
}

FileBrowser::~FileBrowser()
{
}

int FileBrowser::Result(uint32_t command, uint32_t error, std::vector<CString> savedArgs, std::any replyData)
{
    if (command == CMD_PLUGIN_FILE_DISK)
    {
        if (error)
        {
            MessageBox(_T("Fetch disk info failed"), _T("Error"), MB_OK | MB_ICONINFORMATION);
        }
        else
        {
            // 从 replyData 中提取磁盘信息列表
            auto diskinfos = std::any_cast<std::vector<std::pair<CString, int>>>(replyData);
            updateDiskList(diskinfos);
        }
    }
    return 0;
}

void FileBrowser::updateDiskList(std::vector<std::pair<CString, int>> diskinfos)
{
    // 清空远程目录 ComboBox
    m_Remote_Directory_ComboBox.ResetContent();

    // 遍历磁盘信息列表,添加到 ComboBox
    for (auto& diskinfo : diskinfos)
    {
        // diskinfo.first 是磁盘名称,diskinfo.second 是磁盘类型
        CString diskName = diskinfo.first;
        int diskType = diskinfo.second;

        // 将磁盘添加到 ComboBox
        int index = m_Remote_Directory_ComboBox.AddString(diskName);
        
        // 可以将磁盘类型存储在 ItemData 中,以便后续使用
        if (index != CB_ERR)
        {
            m_Remote_Directory_ComboBox.SetItemData(index, diskType);
        }
    }

    // 如果有磁盘,默认选择第一个
    if (diskinfos.size() > 0)
    {
        m_Remote_Directory_ComboBox.SetCurSel(0);
    }
}

void FileBrowser::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO1, m_Local_Directory_ComboBox);
    DDX_Control(pDX, IDC_COMBO2, m_Remote_Directory_ComboBox);
    DDX_Control(pDX, IDC_LIST2, m_list_local);
    DDX_Control(pDX, IDC_LIST1, m_list_remote);
}

LRESULT FileBrowser::OnExecTask(WPARAM wParam, LPARAM lParam)
{
    auto* msg = reinterpret_cast<ExecTaskMsg*>(lParam);

    auto& callbacks = m_FileEngine->m_callbacks;
    auto it = callbacks.find(msg->tid);

    if (it != callbacks.end())
    {
        int execResult =
            it->second.pCallback->Result(
                msg->command,
                msg->error,
                it->second.savedArgs,
                msg->replyData
            );

        if (execResult != CALLBACK_EXEC_CONTINUE)
        {
            callbacks.erase(it);
        }
    }

    *(msg->pRet) = 0;
    msg->pEvent->set();

    delete msg;
    return 0;
}


BEGIN_MESSAGE_MAP(FileBrowser, CDialogEx)
	ON_MESSAGE(WM_EXEC_TASK, &FileBrowser::OnExecTask)
    ON_BN_CLICKED(IDC_BUTTON1, &FileBrowser::OnBnClickedButton1)
END_MESSAGE_MAP()


// FileBrowser 消息处理程序


void FileBrowser::OnBnClickedButton1()
{
    // TODO: 在此添加控件通知处理程序代码
    m_FileEngine->fileDiskList(m_FileEngine->m_pMainWindow->m_hostinfo.getSid(), this);
}
