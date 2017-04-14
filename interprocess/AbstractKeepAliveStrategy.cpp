#include "stdafx.h"
#include "AbstractKeepAliveStrategy.h"
#include <boost/core/ignore_unused.hpp>
//Ĭ�ϵı���ʱ����
const int DEFAULT_KEEP_ALIVE_GAP = 5;


CAbstractKeepAliveStrategy::CAbstractKeepAliveStrategy():
m_nKeepAliveGap(DEFAULT_KEEP_ALIVE_GAP)
{

}

CAbstractKeepAliveStrategy::~CAbstractKeepAliveStrategy()
{

}

void CAbstractKeepAliveStrategy::StartKeepAlive(void)
{
	//�Ƿ����߳�
	if (m_KeepAliveThread)
	{
		return;
	}

	//lamda���ʽ
	auto pThreadFunc = [this]()->void
	{
		try
		{
			while (true)
			{
				//�����߳��ж�
				boost::this_thread::interruption_point();

				KeepAlive();

				boost::this_thread::sleep(boost::posix_time::seconds(m_nKeepAliveGap));
			}
		}
		catch (boost::thread_interrupted& e)
		{
			boost::ignore_unused(e);
		}
	};
	m_KeepAliveThread = boost::make_shared<boost::thread>(pThreadFunc);
}

void CAbstractKeepAliveStrategy::StopKeepAlive(void)
{
	if (m_KeepAliveThread)
	{
		m_KeepAliveThread->interrupt();
		m_KeepAliveThread->join();
	}
}
