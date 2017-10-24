/************************************************************************************
Copyright(C):
FileName:Utility.h
Description:�����ӿ�
Author:xiaowei.han
Date:2016-9-11
Others:
Histroy:
************************************************************************************/
#ifndef UTILITY_H
#define UTILITY_H
#include <string>
#include <boost/checked_delete.hpp>
namespace Utility
{
	//��ȡ��ִ���ļ��ľ���·��
	std::string GetExeDirecory(void);

    //���ֽ�����ֽ�ת��
    std::wstring MultiByte2WideChar(const char* szSrc);

    //���ֽ�����ֽ�ת��
    std::string WideChar2MultiByte(const wchar_t* szSrc);

#if 0
	//��Ӳ��λͼ�ļ�����λͼ
	HBITMAP LoadBitmapFromFile(const char* szBitmapFile);

	int AfxBCGPMessageBox(const CString& strText,UINT nType = MB_OK);

	BYTE CalCRC8(BYTE* pBuf,int nsize);

	//UTF-8->GBK
	std::string ConverUTF8ToGB2312( const std::string& strContent );

	//UTF-8->ASCII
	std::string ConverUTF8ToASCII(std::string& strContent);
#endif
}

//ɾ������ĺ���ģ��
template <typename T>
void SafeDeleter(T* p)
{
	using namespace boost;
	checked_delete(p);
}

template <typename T>
void SafeArrayDeleter(T* p)
{
	using namespace boost;
	checked_array_delete(p);
}
//���������С
#define ARRAY_SIZE(array)     (sizeof(array) / sizeof(array[0]))
#endif