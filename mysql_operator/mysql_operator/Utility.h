/************************************************************************************
Copyright(C):Envision. Co., Ltd.
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
}

//ɾ������ĺ�
#define  DELETE_ARRAY_POINTER(p)              if (nullptr != p)    \
{                    \
	delete []p;   \
	p = nullptr;  \
}

//ɾ��������ָ��
#define  DELETE_POINTER(p)                             if (nullptr != p)    \
{                   \
	delete p;   \
	p = nullptr;  \
}   

//���������С
#define ARRAY_SIZE(array)     (sizeof(array) / sizeof(array[0]))
#endif