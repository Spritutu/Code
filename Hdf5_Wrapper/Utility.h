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
namespace Utility
{
	//��ȡ��ִ���ļ��ľ���·��
	std::string GetExeDirecory(void);

    //���ֽ�����ֽ�ת��
    std::wstring MultiByte2WideChar(const char* szSrc);

    //���ֽ�����ֽ�ת��
    std::string WideChar2MultiByte(const wchar_t* szSrc);

	//UTF-8->GBK
	std::string GB2312ToUTF8(const std::string& strContent);
#if 0
	//��Ӳ��λͼ�ļ�����λͼ
	HBITMAP LoadBitmapFromFile(const char* szBitmapFile);

	int AfxBCGPMessageBox(const CString& strText,UINT nType = MB_OK);

	BYTE CalCRC8(BYTE* pBuf,int nsize);



	//UTF-8->ASCII
	std::string ConverUTF8ToASCII(std::string& strContent);
#endif
}

//ɾ������ĺ�
#define  DELETE_ARRAY_POINTER(p)              if (NULL != p)    \
{                    \
	delete []p;   \
	p = NULL;  \
}

//ɾ��������ָ��
#define  DELETE_POINTER(p)                             if (NULL != p)    \
{                   \
	delete p;   \
	p = NULL;  \
}   

//���������С
#define ARRAY_SIZE(array)     (sizeof(array) / sizeof(array[0]))
#endif