#include "pch.h"
#include "TaskCallback.h"

TaskCallback::TaskCallback(TaskEngine* pTaskEngine)
	:m_pTaskEngine(pTaskEngine)
{

}

TaskData::TaskData() :pCallback(NULL)
{
}
