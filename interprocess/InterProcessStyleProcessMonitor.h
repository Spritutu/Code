#ifndef INTER_PROCESS_STYLE_PROCESS_MONITOR_H
#define INTER_PROCESS_STYLE_PROCESS_MONITOR_H
#include <string>
#include "AbstractProcessMonitor.h"
class CInterProcessStyleProcessMonitor : public CAbstractProcessMonitor
{
public:
	CInterProcessStyleProcessMonitor(const std::string& strSharedMemoryName, const std::string& strNamedMutexName,int nGap);
	~CInterProcessStyleProcessMonitor(void);



public:
	void MonitorProcess(void) override;
private:
	//���ڽ���ͨ�ŵĹ����ڴ�����
	std::string m_strSharedMemoryName;
	//���ڽ���ͬ������������������
	std::string m_strNamedMutexName;
	//�������
	int m_nMonitorGap;
};

#endif