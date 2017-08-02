#include "stdafx.h"
#include "TabNameMap.h"
#include <boost/assign.hpp>

CTabNameMap::CTabNameMap()
{
	InitTabMap();
}


CTabNameMap::~CTabNameMap()
{
}

std::string CTabNameMap::GetTabNameByConfigName(const std::string& strConfigName)
{
	using namespace std;
	auto Iter = m_TabMap.find(strConfigName);

	if (Iter != m_TabMap.end())
	{
		return Iter->second;
	}

	return string("");
}

void CTabNameMap::InitTabMap(void)
{
	using namespace boost::assign;

	insert(m_TabMap)("CollectorConfig.json","��Դ�ռ�ģ��")("NodeServiceConfig.json","�ڵ�ģ��")("TaskReceiverConfig.json","�������ģ��")("TaskScheduerConfig.json","�������ģ��")("TaskStatusManagerConfig.json","����״̬����ģ��");

}
