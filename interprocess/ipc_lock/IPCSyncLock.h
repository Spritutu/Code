/*********************************************************
Copyright(C):
FileName:IPCSyncLock.h
Descripton:����ͬ����
Author:xiaowei.han
Data:2018/01/15
Others:
History:
Version:1.0
*********************************************************/
#ifndef IPC_SYNC_LOCK_H
#define IPC_SYNC_LOCK_H
#include <string>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/noncopyable.hpp>
#include <boost/smart_ptr.hpp>
class CIPCSyncLock : boost::noncopyable
{
public:
	CIPCSyncLock(const std::string& strID,bool bCreateFlag = true);
	~CIPCSyncLock();

	//����ͬ����
	int CreateSyncLock();

	//����
	void Lock();

	//����
	void UnLock();
private:
	//ͬ�������ID
	std::string m_strID;
	//�Ƿ񴴽���־
	bool m_bCreateFlag;
	//ͬ����
	boost::shared_ptr<boost::interprocess::named_mutex> m_pLock;
};


#endif
