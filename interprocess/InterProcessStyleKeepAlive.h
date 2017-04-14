/**************************************************************************
Copyright(C):
FileName:InterProcessStyleKeepAlive.h
Description:ʹ�ý��̼�ͨ�ŷ�ʽ��������
Author:xiaowei.han
Date:2017/03/31
Others:
Histroy:
**************************************************************************/
#ifndef INTER_PROCESS_STYLE_KEEP_ALIVE_H
#define INTER_PROCESS_STYLE_KEEP_ALIVE_H
#include <string>
#include "AbstractKeepAliveStrategy.h"
class CInterProcessStyleKeepAlive : public CAbstractKeepAliveStrategy
{

public:
	CInterProcessStyleKeepAlive(const std::string& strSharedMemoryName, const std::string& strNamedMutexName);
	~CInterProcessStyleKeepAlive(void);
	//ʵ��KeepAlive���麯��
	void KeepAlive(void) override;


private:
	//��ʼ�������ڴ�
	void InitSharedMemory(void);
	//����ʼ�������ڴ�
	void UnInitSharedMemory(void);
	//��ʼ������������
	void InitNamedMutex(void);
	//����ʼ������������
	void UnInitNamedMutex(void);
private:
	//���ڽ���ͬ������������������
	std::string m_strNamedMutexName;
	//���ڽ���ͨ�ŵĹ����ڴ�����
	std::string m_strSharedMemoryName;
};
#endif