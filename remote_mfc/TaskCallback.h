#pragma once

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

private:
	TaskEngine* m_pTaskEngine;
};

