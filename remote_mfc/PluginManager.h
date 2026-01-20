#pragma once
#include "Hostinfo.h"
#include "remote_mfcDlg.h"
class CremotemfcDlg;
class PluginManager:public TaskCallback
{
private:
    HostInfo m_hostinfo;
    CremotemfcDlg* m_pMainWindow;
};

