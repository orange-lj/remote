#pragma once

#include "TaskCallback.h"
#include "../common/bytearray.h"
#include <string>
#include <vector>
#include <map>
#include <atomic>
#include <cstdint>
class CremotemfcDlg;
class TaskEngine {
public:
    explicit TaskEngine(CremotemfcDlg* pMainWindow);
    int pluginLoad(std::string sid, CString pluginName, ByteArray pluginData, TaskCallback* pCallback);
    ByteArray buildPacket(std::string sid, uint32_t cmd, ByteArray taskData, uint64_t& tid);
private:
    int AddTask(std::string sid, uint64_t tid, ByteArray packet, TaskCallback* pCallback, std::vector<CString> savedArgs);
private:
    CremotemfcDlg* m_pMainWindow;
    std::atomic<uint64_t> m_tidCounter;
    std::map<uint64_t, TaskData> m_callbacks;

};