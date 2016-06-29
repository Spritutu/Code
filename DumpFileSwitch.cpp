/*******************************************************************************
Copyright(C):Envision. Co., Ltd.
FileName:DumpFileSwitch.cpp
Description:Dump�ļ�������
Author:xiaowei.han
Date:2016/6/29 12:43
Others:
Histroy:
*******************************************************************************/
#include "stdafx.h"
#include "DumpFileSwitch.h"
#include <ImageHlp.h>
#include <Windows.h>
#include <string>
#pragma warning(disable:4996)
#pragma comment(lib,"dbghelp.lib")
static std::string s_DumpFilePath = "";
static bool IsDataSectionNeeded(const wchar_t* szModuleName);
static void CreateMiniDump(EXCEPTION_POINTERS* pep,const TCHAR* szFilename);
static BOOL CALLBACK MiniDumpCallback(PVOID pParam,const PMINIDUMP_CALLBACK_INPUT pInput,PMINIDUMP_CALLBACK_OUTPUT pOutput);
static LONG __stdcall CustomUnhandledExceptionFilter(PEXCEPTION_POINTERS pExceptionInfo);
/*****************************************************************************
* @�������� : CreateInstance
* @�������� : ������ʵ��
* @author : xiaowei.han
* @date : 2016/6/29 13:33
* @version : ver 1.0
* @inparam : 
* @outparam : 
*****************************************************************************/
CDumpFileSwitch& CDumpFileSwitch::CreateInstance( void )
{
    static CDumpFileSwitch s_DumpFileSwitch;
    return s_DumpFileSwitch;
}

/*****************************************************************************
* @�������� : CDumpFileSwitch
* @�������� : ���캯��
* @author : xiaowei.han
* @date : 2016/6/29 13:33
* @version : ver 1.0
* @inparam : 
* @outparam : 
*****************************************************************************/
CDumpFileSwitch::CDumpFileSwitch( void )
{

}

/*****************************************************************************
* @�������� : CDumpFileSwitch
* @�������� : ��������
* @author : xiaowei.han
* @date : 2016/6/29 13:33
* @version : ver 1.0
* @inparam : 
* @outparam : 
*****************************************************************************/
CDumpFileSwitch::~CDumpFileSwitch( void )
{

}

void CDumpFileSwitch::SetDumpFilePath( const char* szDumpFilePath )
{
    if (NULL == szDumpFilePath)
    {
        return;
    }

    s_DumpFilePath = szDumpFilePath;
}

void CDumpFileSwitch::OpenSwitch( void )
{
    SetUnhandledExceptionFilter(CustomUnhandledExceptionFilter);
}


void CDumpFileSwitch::OpenSwitchWithReg( int nType,const char* szExeName )
{
    if (NULL == szExeName || nType < 1 || nType > 2)
    {
        return;
    }

    HKEY hReg = NULL;
    std::string strSubKey = std::string("SOFTWARE\\Microsoft\\Windows\\Windows Error Reporting\\LocalDumps") + std::string("\\") + std::string(szExeName);
    LONG lResult = RegCreateKeyEx(HKEY_LOCAL_MACHINE,strSubKey.c_str(),0
                                  ,NULL,0,KEY_WRITE,NULL,&hReg,NULL);

    if (ERROR_SUCCESS != lResult)
    {
        return;
    }

    lResult = RegSetValueEx(hReg,"DumpFolder",0,REG_EXPAND_SZ,(const BYTE*)s_DumpFilePath.c_str(),s_DumpFilePath.length());

    if (ERROR_SUCCESS != lResult)
    {
        return;
    }

    int nMaxDumpFileNum = 10;
    lResult = RegSetValueEx(hReg,"DumpCount",0,REG_DWORD,(const BYTE*)&nMaxDumpFileNum,sizeof(nMaxDumpFileNum));
    if (ERROR_SUCCESS != lResult)
    {
        return;
    }
    int nCustomDumpFlags = 0;
    lResult = RegSetValueEx(hReg,"CustomDumpFlags",0,REG_DWORD,(const BYTE*)&nCustomDumpFlags,sizeof(nCustomDumpFlags));
    if (ERROR_SUCCESS != lResult)
    {
        return;
    }

    lResult = RegSetValueEx(hReg,"DumpType",0,REG_DWORD,(const BYTE*)&nType,sizeof(nType));
    if (ERROR_SUCCESS != lResult)
    {
        return;
    }
}

bool IsDataSectionNeeded( const wchar_t* szModuleName )
{
    if (NULL == szModuleName)
    {
        return false;
    }

    wchar_t szFileName[_MAX_FNAME] = L"";
    _wsplitpath(szModuleName,NULL,NULL,szFileName,NULL);
    if(wcsicmp(szFileName,L"ntdll") == 0)
    {
        return true;
    }

    return false;
}

void CreateMiniDump( EXCEPTION_POINTERS* pep,const TCHAR* szFilename )
{
    HANDLE hFile = CreateFile(szFilename,GENERIC_READ | GENERIC_WRITE,
        0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );
    if( ( hFile != NULL ) && ( hFile != INVALID_HANDLE_VALUE ) )
    {
        MINIDUMP_EXCEPTION_INFORMATION mdei;
        mdei.ThreadId           = GetCurrentThreadId();
        mdei.ExceptionPointers  = pep;
        mdei.ClientPointers     = FALSE;
        MINIDUMP_CALLBACK_INFORMATION mci;
        mci.CallbackRoutine     = (MINIDUMP_CALLBACK_ROUTINE)MiniDumpCallback;
        mci.CallbackParam       = 0;
        MINIDUMP_TYPE mdt       = (MINIDUMP_TYPE)(MiniDumpWithPrivateReadWriteMemory |
            MiniDumpWithDataSegs |
            MiniDumpWithHandleData |
            0x00000800 |
            0x00001000 |
            MiniDumpWithUnloadedModules );
        MiniDumpWriteDump( GetCurrentProcess(), GetCurrentProcessId(),
            hFile, mdt, (pep != 0) ? &mdei : 0, 0, &mci );
        CloseHandle( hFile );
        hFile = NULL;
    }

}

BOOL CALLBACK MiniDumpCallback( PVOID pParam,const PMINIDUMP_CALLBACK_INPUT pInput,PMINIDUMP_CALLBACK_OUTPUT pOutput )
{
    if( pInput == NULL || pOutput == NULL)
    {
        return FALSE;
    }
    switch(pInput->CallbackType)
    {
    case ModuleCallback:
        if( pOutput->ModuleWriteFlags & ModuleWriteDataSeg )
        {
            if( !IsDataSectionNeeded( pInput->Module.FullPath ) )
            {
                pOutput->ModuleWriteFlags &= (~ModuleWriteDataSeg);
            }
        }
    case IncludeModuleCallback:
    case IncludeThreadCallback:
    case ThreadCallback:
    case ThreadExCallback:
        return TRUE;
    default:
        break;
    }
    return FALSE;
}

LONG __stdcall CustomUnhandledExceptionFilter(PEXCEPTION_POINTERS pExceptionInfo)
{
    CreateMiniDump(pExceptionInfo,s_DumpFilePath.c_str());
    return EXCEPTION_EXECUTE_HANDLER;
}