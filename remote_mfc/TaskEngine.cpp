#include "TaskEngine.h"
#include "pch.h"
#include "../common/proto.h"
#include "remote_mfcDlg.h"
#include "FileBrowser.h"
TaskEngine::TaskEngine(CremotemfcDlg* pMainWindow)
	:m_pMainWindow(pMainWindow),
	m_tidCounter(10)
{

}

int TaskEngine::pluginLoad(std::string sid, CString pluginName, ByteArray pluginData, TaskCallback* pCallback)
{
	uint64_t tid;

	CStringA pluginNameA(pluginName);   
	const char* nameBuf = pluginNameA.GetString();

	uint32_t namelen = (uint32_t)strlen(nameBuf);
	uint32_t datalen = (uint32_t)pluginData.m_size;

	// 2. 计算总长度
	int totalLen =
		sizeof(uint32_t) +      // namelen
		sizeof(uint32_t) +      // datalen
		namelen +               // name
		datalen;                // data

	// 3. 分配 taskData
	ByteArray taskData;
	taskData.SetSize(totalLen);

	// 4. 按顺序拷贝
	unsigned char* p = taskData.m_buffer;

	memcpy(p, &namelen, sizeof(namelen));
	p += sizeof(namelen);

	memcpy(p, &datalen, sizeof(datalen));
	p += sizeof(datalen);

	memcpy(p, nameBuf, namelen);
	p += namelen;

	memcpy(p, pluginData.m_buffer, datalen);

	ByteArray packet = buildPacket(sid, CMD_PLUGIN_LOAD, taskData, tid);
	std::vector<CString> savedArgs;
	savedArgs.push_back(pluginName);
	return AddTask(sid, tid, packet, pCallback, savedArgs);
}

ByteArray TaskEngine::buildPacket(std::string sid, uint32_t cmd, ByteArray taskData, uint64_t& tid)
{
	PACKET_HEADER header = { 0 };
	
	header.id = m_tidCounter++;
	header.cmd = cmd;
	header.error = 0;
	header.length = taskData.m_size;

	tid = header.id;
	ByteArray packet;

	packet.BufCpy((unsigned char*)&header, sizeof(PACKET_HEADER));
	packet.BufCat(taskData.m_buffer, taskData.m_size);
	return packet;
}

int TaskEngine::AddTask(std::string sid, uint64_t tid, ByteArray packet, TaskCallback* pCallback, std::vector<CString> savedArgs)
{
	if (pCallback)
	{
		TaskData taskData;
		taskData.pCallback = pCallback;
		taskData.savedArgs = savedArgs;

		m_callbacks.insert(std::make_pair(tid, taskData));
	}

	auto pManageServer = m_pMainWindow->GetManager(sid);
	if (!pManageServer)
	{
		//server is not connected
		return 1;
	}
	else
	{
		std::string strPacket = packet.toStdString();
		pManageServer->Write(strPacket);
	}

	return 0;
}

void TaskEngine::execTask(uint64_t tid, int error, uint32_t command, const std::any& replyData)
{
	MyEvent event(false, true);
	uint32_t ret = 0;
	auto* msg = new ExecTaskMsg{
		tid,
		error,
		command,
		replyData,
		&event,
		&ret
	};
	// 投递到 GUI 线程
	m_pMainWindow->GetOneTabDialog()->m_pFileBrowser->PostMessage(WM_EXEC_TASK, 0, (LPARAM)msg);
	event.wait();
}

int TaskEngine::fileDiskList(std::string sid, TaskCallback* pCallback)
{
	uint64_t tid;
	ByteArray emptyData;
	ByteArray packet = buildPacket(sid, CMD_PLUGIN_FILE_DISK, emptyData, tid);

	std::vector<CString> savedArgs;

	return AddTask(sid, tid, packet, pCallback, savedArgs);
}
