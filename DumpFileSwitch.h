/*******************************************************************************
Copyright(C):Envision. Co., Ltd.
FileName:DumpFileSwitch.h
Description:Dump�ļ�������
Author:xiaowei.han
Date:2016/6/29 12:43
Others:
Histroy:
*******************************************************************************/
#ifndef DUMP_FILE_SWITCH_H
#define DUMP_FILE_SWITCH_H
#include <Windows.h>
class CDumpFileSwitch
{
public:
    static CDumpFileSwitch& CreateInstance(void);

    void SetDumpFilePath(const char* szDumpFilePath);
    void OpenSwitch(void);
    //ͨ���޸�ע�������dmp�ļ� ��1:minidump 2:fulldump��
    void OpenSwitchWithReg(int nType,const char* szExeName);
private:
    CDumpFileSwitch(void);
    ~CDumpFileSwitch(void);
};



#endif