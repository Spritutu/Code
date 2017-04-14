#ifndef MONITOR_PROCESS_H
#define MONITOR_PROCESS_H
#include <vector>
#include <boost/smart_ptr.hpp>
class CAbstractProcessMonitor;
class CMonitorProcess
{

public:
	//��ʵ��
	static CMonitorProcess& CreateInstance(void);

	//ע���ؽ���
	void RegisterProcessMonitor(boost::shared_ptr<CAbstractProcessMonitor> pMonitor);

	//��ʼ���
	void StartMonitorProcess(void);

	//ֹͣ���
	void StopMonitorProcess(void);

protected:
	CMonitorProcess(void) { }
	~CMonitorProcess(void) {}

private:
	static CMonitorProcess s_MonitorProcessObj;

	std::vector<boost::shared_ptr<CAbstractProcessMonitor>> m_MonitorArray;
};


#endif