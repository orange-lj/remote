#include "pch.h"
#include "PluginManager.h"
#include "remote_mfcDlg.h"
#include "../common/bytearray.h"
#include <locale>
#include <codecvt>
PluginManager::PluginManager(HostInfo hostinfo, CremotemfcDlg* pMainWindow)
	:m_pMainWindow(pMainWindow),
    TaskCallback(pMainWindow->GetTaskEngine()),
    m_hostinfo(hostinfo) 
{
    
    //loadPlugin();
}

//void PluginManager::loadPlugin()
//{
//    //获取插件根路径
//    CString rootPluginPath = getPluginRootPath();
//    for (auto pair : m_descriptions)  
//    {
//        CString pluginName = pair.first;
//        CString pluginPath = rootPluginPath + "\\" + pluginName;
//        CFile file;
//        if (!file.Open(pluginPath, CFile::modeRead | CFile::typeBinary)) {
//            return;
//        }
//        // 1. 获取文件大小
//        ULONGLONG fileSize = file.GetLength();
//        if (fileSize == 0)
//        {
//            file.Close();
//            return;
//        }
//        // 2. 分配 ByteArray
//        ByteArray pluginData;
//        pluginData.SetSize(static_cast<int>(fileSize));
//
//        // 3. 读取文件
//        UINT bytesRead = file.Read(pluginData.m_buffer, pluginData.m_size);
//        file.Close();
//        if (bytesRead != pluginData.m_size)
//        {
//            // 读取失败或不完整
//            return;
//        }
//        m_pMainWindow->GetTaskEngine()->pluginLoad(m_hostinfo.getSid(), pluginName, pluginData, this);
//    }
//
//}

//CString PluginManager::getPluginRootPath()
//{
//    WCHAR strTempW[MAX_PATH];
//    //得到文件名
//    GetModuleFileNameW(NULL, strTempW, MAX_PATH);
//
//    CString strCurrentPath;
//
//    strCurrentPath = strTempW;
//
//    strCurrentPath = strCurrentPath.Left(strCurrentPath.ReverseFind('\\'));
//    return strCurrentPath;
//}
