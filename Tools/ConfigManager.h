#pragma once
#include <string>
#include "ConfigType.h"
class CConfigManager
{

public:
	static CConfigManager& CreateInstance(void);
private:
	CConfigManager();
	~CConfigManager();

public:
	//�����Ѽ��ڵ���Դ����
	bool ReadCollectorConfigInfo(const std::string& strConfigPath, ConfigType::LP_COLLECTOR_CONFIG_INFO pConfigInfo);
	//�����Ѽ��ڵ���Դ����
	bool WriteCollectorConfigInfo(const std::string& strConfigPath, const ConfigType::LP_COLLECTOR_CONFIG_INFO pConfigInfo);

	//���ؽڵ���Դ����
	bool ReadNodeConfigInfo(const std::string& strConfigPath, ConfigType::LP_NODE_CONFIG_INFO pConfigInfo);
	//����ڵ���Դ����
	bool WriteNodeConfigInfo(const std::string& strConfigPath, const ConfigType::LP_NODE_CONFIG_INFO pConfigInfo);

	//����״̬������Դ����
	bool ReadStatusManagerConfigInfo(const std::string& strConfigPath, ConfigType::LP_STATUS_MANAGER_CONFIG_INFO pConfigInfo);
	//����״̬������Դ����
	bool WriteStatusManagerConfigInfo(const std::string& strConfigPath, const ConfigType::LP_STATUS_MANAGER_CONFIG_INFO pConfigInfo);

	//���ص�����Դ����
	bool ReadScheduerConfigInfo(const std::string& strConfigPath, ConfigType::LP_SCHEDUER_CONFIG_INFO pConfigInfo);
	//���������Դ����
	bool WriteScheduerConfigInfo(const std::string& strConfigPath, const ConfigType::LP_SCHEDUER_CONFIG_INFO pConfigInfo);

	//���ؽ���������Դ����
	bool ReadReceiverConfigInfo(const std::string& strConfigPath, ConfigType::LP_RECEIVER_CONFIG_INFO pConfigInfo);
	//�������������Դ����
	bool WriteReceiverConfigInfo(const std::string& strConfigPath, const ConfigType::LP_RECEIVER_CONFIG_INFO pConfigInfo);
private:
	static CConfigManager s_Obj;
};

