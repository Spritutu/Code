/**************************************************************************
Copyright(C):Envision. Co., Ltd.
FileName:Queue.hpp
Description:ͬ������
Author:xiaowei.han
Date:2017/04/10
Others:
Histroy:
**************************************************************************/
#ifndef QUEUE_H
#define QUEUE_H
#include <boost/thread/condition_variable.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/atomic.hpp>
#include <boost/move/move.hpp>
#include <list>
//�����ģ�����
template <typename T,int nMaxElement = 100000>
class SyncQueue
{
public:
	SyncQueue(void)
	{
		m_nMaxElement = nMaxElement;
		m_bNeedExit = false;
	}
	~SyncQueue(void)
	{

	}

	/**************************************************************************
	@FunctionName:Put
	@FunctionDestription:����з���Ԫ��
	@InputParam:Element:Ҫ���뵽���е�Ԫ��
	@OutPutParam:None
	@ReturnValue:None
	**************************************************************************/
	void Put(const T& Element)
	{
		boost::unique_lock<boost::mutex> Lock(m_syncMutex);

		//�ж��Ƿ�Ϊ��
		m_PutCondition.wait(Lock, [this]()->bool 
		{
			return (!(static_cast<int>(m_ElementArray.size()) == m_nMaxElement) || m_bNeedExit);
		});

		//�����Ҫ�˳�
		if (m_bNeedExit)
		{
			return;
		}

		//����Ԫ��
		m_ElementArray.push_back(boost::move(Element));

		//֪ͨ��������
		m_GetCondition.notify_all();

	}

	/**************************************************************************
	@FunctionName:Get
	@FunctionDestription:�Ӷ���ȡԪ��
	@InputParam:None
	@OutPutParam:Element:�Ӷ���ȡ��Ԫ��
	@ReturnValue:None
	**************************************************************************/
	void Get(T& Element)
	{
		boost::unique_lock<boost::mutex> Lock(m_syncMutex);

		//�ж��Ƿ�Ϊ��
		m_GetCondition.wait(Lock, [this]()->bool
		{
			return (!(m_ElementArray.empty()) || m_bNeedExit);
		});

		//�����Ҫ�˳�
		if (m_bNeedExit)
		{
			return;
		}

		//��Ԫ��
		Element = m_ElementArray.front();

		m_ElementArray.pop_front();

		//֪ͨ��������
		m_PutCondition.notify_all();
	}

	/**************************************************************************
	@FunctionName:IsQueueEmpty
	@FunctionDestription:�ж϶����Ƿ�Ϊ��
	@InputParam:None
	@OutPutParam:None
	@ReturnValue:true:empty false:not empty.
	**************************************************************************/
	bool IsQueueEmpty(void)
	{
		bool bResult = true;
		{
			boost::lock_guard<boost::mutex> Lock(m_syncMutex);
			bResult = m_ElementArray.empty();
		}
		return bResult;

	}

	/**************************************************************************
	@FunctionName:GetQueueSize
	@FunctionDestription:��ȡ����Ԫ�ظ���
	@InputParam:None
	@OutPutParam:None
	@ReturnValue:����Ԫ�ظ���
	**************************************************************************/
	int GetQueueSize(void)
	{
		int nSize = 0;
		{
			boost::lock_guard<boost::mutex> Lock(m_syncMutex);
			nSize = static_cast<int>(m_ElementArray.size());
		}
		return nSize;
	}

	/**************************************************************************
	@FunctionName:StopQueue
	@FunctionDestription:ֹͣ�ȴ���Ϊ�˷�ֹ�����˳��������޷��˳�
	@InputParam:None
	@OutPutParam:None
	@ReturnValue:None
	**************************************************************************/
	void StopQueue(void)
	{
		{
			boost::lock_guard<boost::mutex> Lock(m_syncMutex);
			m_bNeedExit = true;
		}

		m_PutCondition.notify_all();
		m_GetCondition.notify_all();

	}

private:
	//������Ԫ�ظ���
	int m_nMaxElement;
	//���Ԫ�ص���������
	boost::condition_variable m_PutCondition;
	//��ȡԭɫ����������
	boost::condition_variable m_GetCondition;
	//����ͬ���Ļ�����
	boost::mutex m_syncMutex;
	//�Ƿ�����ı�־
	bool m_bNeedExit;
	//���Ԫ�ص�����
	std::list<T> m_ElementArray;
};





#endif