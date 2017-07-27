/************************************************************************************
Copyright(C):Envision. Co., Ltd.
FileName:Utility.cpp
Description:�����ӿ�
Author:xiaowei.han
Date:2016-9-11
Others:
Histroy:
************************************************************************************/
#include "stdafx.h"
#include "Utility.h"
#ifdef _WIN32
#include <Windows.h>
#endif
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
/*****************************************************************************
FunctionName:GetExeDirecory
FunctionDescription:��ȡ��ִ���ļ����ڵ�Ŀ¼
@param
@param
@Return Value:��ִ���ļ����ڵ�Ŀ¼
******************************************************************************/
std::string Utility::GetExeDirecory( void )
{
	std::string strPath;

#ifdef _WIN32
	char szPath[MAX_PATH] = {0};

	if (0 != GetModuleFileNameA(NULL,szPath,sizeof(szPath)))
	{
		strPath = szPath;
		int nPos = (int)strPath.rfind('\\');
		if (std::string::npos != nPos)
		{
			strPath = strPath.substr(0,nPos);
		}
	}
#else
	strPath = boost::filesystem::initial_path().string();
#endif
	return strPath;
}

/*****************************************************************************
* @�������� : MultiByte2WideChar
* @�������� : ���ֽ�����ֽ�ת��
* @author : xiaowei.han
* @date : 2016/7/1 12:34
* @version : ver 1.0
* @inparam : 
* @outparam : 
*****************************************************************************/
std::wstring Utility::MultiByte2WideChar( const char* szSrc )
{
    std::wstring strResult;
    if (NULL != szSrc)
    {
        int nNum = MultiByteToWideChar(CP_ACP,0,szSrc,-1,NULL,0);   
        wchar_t *pwText = new wchar_t[nNum];
        if(NULL != pwText)
        {
            MultiByteToWideChar(CP_ACP,0,szSrc,-1,pwText,nNum);

            strResult = pwText;

            DELETE_ARRAY_POINTER(pwText);
        }     
    }

    return strResult;
}

/*****************************************************************************
* @�������� : WideChar2MultiByte
* @�������� : ���ֽ�����ֽ�ת��
* @author : xiaowei.han
* @date : 2016/7/1 12:34
* @version : ver 1.0
* @inparam : 
* @outparam : 
*****************************************************************************/
std::string Utility::WideChar2MultiByte( const wchar_t* szSrc )
{
    std::string strResult;
    if (NULL != szSrc)
    {
        int nNum = WideCharToMultiByte(CP_ACP,NULL,szSrc,-1,NULL,0,NULL,FALSE);
        char *psText = new char[nNum];
        if(NULL != psText)
        {
            WideCharToMultiByte(CP_ACP,NULL,szSrc,-1,psText,nNum,NULL,FALSE);

            strResult = psText;
            DELETE_ARRAY_POINTER(psText);
        }
        
    }
    
    return strResult;
   
}





