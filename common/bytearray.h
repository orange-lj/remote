#pragma once
#include <iostream>  
#include <fstream>
#include <string>
#include <memory>
#include <thread>
#include <locale>
#include <codecvt>
using namespace std;
#define DELETE_BUF(p) if(p){delete p; p=NULL;}
class ByteArray {

public:
	ByteArray();
	ByteArray(int size);
public:
	int SetSize(int len, unsigned char init_byte = 0);
	int SetData(int offset, unsigned char* data, int len, int& cb);
	int BufCpy(unsigned char* buf, int len);
	int BufCat(unsigned char* buf, int len);
	std::string toStdString() const;
public:
	int ReadF(wchar_t* path);
public:
	wchar_t* m_wbuffer;
	unsigned char* m_buffer; int m_size;
};