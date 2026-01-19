#include "bytearray.h"

ByteArray::ByteArray()
{
	m_buffer = NULL;
	m_wbuffer = NULL;
	m_size = 0;

	SetSize(0);
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
