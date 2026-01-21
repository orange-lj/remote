#include "bytearray.h"

ByteArray::ByteArray()
{
	m_buffer = NULL;
	m_wbuffer = NULL;
	m_size = 0;

	SetSize(0);
}

ByteArray::ByteArray(int size)
{
	m_buffer = NULL;
	m_wbuffer = NULL;
	m_size = 0;

	SetSize(size);
}

int ByteArray::SetSize(int len, unsigned char init_byte)
{
	DELETE_BUF(m_buffer);
	m_size = len;
	m_buffer = new unsigned char[m_size + 2];
	m_wbuffer = (wchar_t*)m_buffer;

	memset(m_buffer, init_byte, len);
	memset(m_buffer + len, 0, 2);
	return 0;
}

int ByteArray::SetData(int offset, unsigned char* data, int len, int& cb)
{
	cb = len;

	memmove(m_buffer + offset, data, cb);

	return 0;
}

int ByteArray::BufCpy(unsigned char* buf, int len)
{
	int cb;

	if (int nRet = SetSize(len))
	{
		return nRet;
	}

	if (int nRet = SetData(0, buf, len, cb))
	{
		return nRet;
	}

	return 0;
}

int ByteArray::BufCat(unsigned char* buf, int len)
{
	ByteArray temp(m_size);

	int cb;

	if (int nRet = temp.SetData(0, m_buffer, m_size, cb))
	{
		return nRet;
	}

	if (int nRet = SetSize(m_size + len))
	{
		return nRet;
	}

	if (int nRet = SetData(0, temp.m_buffer, temp.m_size, cb))
	{
		return nRet;
	}

	if (int nRet = SetData(temp.m_size, buf, len, cb))
	{
		return nRet;
	}

	return 0;
}

std::string ByteArray::toStdString() const
{
	if (m_buffer == nullptr || m_size == 0)
		return "";

	// 直接构造 std::string，使用 m_buffer 作为数据源
	return std::string(reinterpret_cast<const char*>(m_buffer), m_size);
}

int ByteArray::ReadF(wchar_t* path)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

	std::string spath = converter.to_bytes(path);

	ifstream in(spath.c_str(), ios::in | ios::binary | ios::ate);

	long size = in.tellg();

	if (size == -1)
	{
		return 1;
	}

	SetSize(size);

	in.seekg(0, ios::beg);

	in.read((char*)m_buffer, size);

	in.close();
	return 0;
}
