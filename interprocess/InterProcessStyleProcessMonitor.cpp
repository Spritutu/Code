#include "stdafx.h"
#include "InterProcessStyleProcessMonitor.h"
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/core/ignore_unused.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time.hpp>
#include <iostream>
using std::cout;
using std::endl;
CInterProcessStyleProcessMonitor::CInterProcessStyleProcessMonitor(const std::string& strSharedMemoryName, const std::string& strNamedMutexName, int nGap):
m_strNamedMutexName(strNamedMutexName),
m_strSharedMemoryName(strSharedMemoryName),
m_nMonitorGap(nGap)
{

}

CInterProcessStyleProcessMonitor::~CInterProcessStyleProcessMonitor(void)
{

}

void CInterProcessStyleProcessMonitor::MonitorProcess(void)
{
	try
	{
		//���ڴ洢��һ�εĴӹ����ڴ��ж�ȡ��ֵ
		static time_t oldSharedMemoryValue = 0;
		//��ǰ��ֵ
		time_t TempSharedMemoryValue = 0;
		//�ظ��Ĵ���
		static int nValueSameTimes = 0;
		//�򿪹����ڴ�
		boost::interprocess::shared_memory_object shm_obj(boost::interprocess::open_only,
			m_strSharedMemoryName.c_str(), boost::interprocess::read_only);
		boost::interprocess::named_mutex mutex(boost::interprocess::open_only, m_strNamedMutexName.c_str());
		while (true)
		{

			boost::this_thread::interruption_point();

			//ӳ�乲���ڴ�
			boost::interprocess::mapped_region region(shm_obj, boost::interprocess::read_only);

			if (mutex.timed_lock(boost::posix_time::second_clock::universal_time() + boost::posix_time::seconds(m_nMonitorGap * 3)))
			{
				memcpy(&TempSharedMemoryValue, region.get_address(), sizeof(time_t));
				mutex.unlock();

				if (TempSharedMemoryValue == oldSharedMemoryValue)
				{
					++nValueSameTimes;

					if (nValueSameTimes >= 3)
					{
						//��ʾ���ӽ����Ѿ�����
						cout << "the value is not change so the process " << m_strMonitorProcessName << " is dead!" << endl;
						break;
					}
				}
				else
				{
					oldSharedMemoryValue = TempSharedMemoryValue;
					nValueSameTimes = 0;
					
					boost::posix_time::ptime T = boost::posix_time::from_time_t(TempSharedMemoryValue);
					cout << boost::posix_time::to_iso_extended_string(T) << endl;

				}
				boost::this_thread::sleep(boost::posix_time::seconds(m_nMonitorGap));
			}
			//�ȴ�����ʱ
			else
			{
				//��ʾ�����Ѿ�����
				cout << "time out over 3 times so the process " <<m_strMonitorProcessName<<" is dead!" << endl;
				break;
			}
		}

		boost::interprocess::shared_memory_object::remove(m_strSharedMemoryName.c_str());
		boost::interprocess::named_mutex::remove(m_strNamedMutexName.c_str());
	}
	catch (boost::thread_interrupted& e)
	{
		boost::ignore_unused(e);
	}
	catch (boost::interprocess::interprocess_exception& e)
	{
		boost::ignore_unused(e);
	}
}

