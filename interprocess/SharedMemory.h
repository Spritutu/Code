/*********************************************************
Copyright(C):
FileName:SharedMemory.h
Descripton:ʵ�ֿ�ƽ̨��IPC
Author:xiaowei.han
Data:2018/01/12
Others:
History:
Version:1.0
*********************************************************/
#ifndef __SHARED_MEMORY_H__
#define __SHARED_MEMORY_H__
#include <string>
#include <boost/smart_ptr.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
class CSharedMemory
{

public:
	CSharedMemory(const std::string& strID,unsigned int nCapacity);
	~CSharedMemory();

	//����һƬ�����ڴ�����
	int CreateSharedMemory(void);

	//ӳ��һƬ�Ѿ����ڵ��ڴ�����
	int OpenSharedMemory(void);

	//�ر�ӳ����ڴ�����
	int CloseSharedMemory(void);

	//�����ڴ�д����
	int WriteDataToSharedMemory(char* pData, unsigned int nDataLength);

	//�ӹ����ڴ��ȡ����
	int ReadDataFromSharedMemory(char* pData, unsigned int nDataLength);

private:
	//�����ڴ�ı�ʶ��
	std::string m_strID;
	//�����ڴ�ռ������
	unsigned int m_nCapacity;
	//�Ѿ�ռ�õ��ڴ�����
	unsigned int m_nUseBytes = 0;
	//�����ڴ�
	boost::shared_ptr<boost::interprocess::shared_memory_object> m_pSharedMemObj;
};




#endif
