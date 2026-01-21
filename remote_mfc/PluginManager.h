#pragma once
#include "Hostinfo.h"
#include "remote_mfcDlg.h"
#include "TaskCallback.h"
class CremotemfcDlg;
class PluginManager:public TaskCallback
{
public:
    PluginManager(HostInfo hostinfo, CremotemfcDlg* pMainWindow);

private:
    void loadPlugin();
    CString getPluginRootPath();
    HostInfo m_hostinfo;
    CremotemfcDlg* m_pMainWindow;
    std::map<CString, std::string> m_descriptions;
};

