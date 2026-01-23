#include "pch.h"
#include "TaskCallback.h"

TaskCallback::TaskCallback(TaskEngine* pTaskEngine)
	:m_pTaskEngine(pTaskEngine)
{

}

TaskCallback::~TaskCallback()
{
}

int TaskCallback::Result(uint32_t command, uint32_t error, std::vector<CString> savedArgs, std::any replyData)
{
	return CALLBACK_EXEC_DONE;
}

TaskData::TaskData() :pCallback(NULL)
{
}
