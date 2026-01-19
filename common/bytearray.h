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
public:
	int SetSize(int len, unsigned char init_byte = 0);
public:
	int ReadF(wchar_t* path);
public:
	wchar_t* m_wbuffer;
	unsigned char* m_buffer; int m_size;
};