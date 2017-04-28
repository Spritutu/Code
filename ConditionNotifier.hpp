/**********************************************************
*��Ȩ����:xiaowei.han
*�ļ�����:ConditionNotifier.hpp
*��������:���������������߳�֪ͨ��
*����:xiaowei.han
*����:2017/04/27
**********************************************************/
#ifndef CONDITION_NOTIFIER_HPP
#define CONDITION_NOTIFIER_HPP
#include <boost/thread/condition_variable.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/lock_types.hpp>
class ConditionNotifier
{

public:
	ConditionNotifier() = default;
	~ConditionNotifier() = default;

public:
	void Wait(void)
	{
		auto Pred = [this]()->bool
		{
			return !m_bWait;
		};
		
		boost::unique_lock<boost::mutex> Lock(m_Mutex);
		m_CV.wait(Lock, Pred);
	}

	void Notify(void)
	{
		{
		  boost::unique_lock<boost::mutex> Lock(m_Mutex);
		  m_bWait = false;
		}
		m_CV.notify_one();
	}
private:
	boost::mutex m_Mutex;
	//�����߳�֪ͨ����������
	boost::condition_variable m_CV;
	//�Ƿ���Ҫ�ȴ���־
	bool m_bWait = true;

};

#endif