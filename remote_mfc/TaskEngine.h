#pragma once

#include "TaskCallback.h"
#include "../common/bytearray.h"
#include "remote_mfcDlg.h"
#include <string>
#include <vector>
#include <map>
#include <atomic>
#include <cstdint>
#include <any>
class CremotemfcDlg;
class FileBrowser;
class TaskEngine {
public:
    explicit TaskEngine(CremotemfcDlg* pMainWindow);
    int pluginLoad(std::string sid, CString pluginName, ByteArray pluginData, TaskCallback* pCallback);
    ByteArray buildPacket(std::string sid, uint32_t cmd, ByteArray taskData, uint64_t& tid);
    void execTask(uint64_t tid, int error, uint32_t command, const std::any& replyData);
    int fileDiskList(std::string sid, TaskCallback* pCallback);
private:
    int AddTask(std::string sid, uint64_t tid, ByteArray packet, TaskCallback* pCallback, std::vector<CString> savedArgs);

public:
    CremotemfcDlg* m_pMainWindow;
    std::atomic<uint64_t> m_tidCounter;
    std::map<uint64_t, TaskData> m_callbacks;
    //FileBrowser* m_pFileBrowser;
};