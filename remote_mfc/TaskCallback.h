#pragma once
#include <any>

#define CALLBACK_EXEC_ERROR     1
#define CALLBACK_EXEC_DONE      2
#define CALLBACK_EXEC_CONTINUE  3

class TaskCallback;
class TaskEngine;

struct TaskData
{
    TaskCallback* pCallback;
    std::vector<CString> savedArgs;

    TaskData();
};

class TaskCallback
{
public:
	TaskCallback(TaskEngine* pTaskEngine);
    virtual ~TaskCallback();
    virtual int Result(uint32_t command, uint32_t error, std::vector<CString> savedArgs, std::any replyData);

private:
	TaskEngine* m_pTaskEngine;
};

