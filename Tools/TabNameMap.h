#pragma once

#include <map>
#include <string>
class CTabNameMap
{
public:
	CTabNameMap();
	virtual ~CTabNameMap();

public:
	//���������ļ����ƻ�ȡTab����
	std::string GetTabNameByConfigName(const std::string& strConfigName);

private:
	void InitTabMap(void);
private:
	//�����ļ�������tabҳ����һһ��Ӧ
	std::map<std::string, std::string> m_TabMap;
};

