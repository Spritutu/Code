#pragma once
#include <string>
namespace ConfigType
{
	//�Ѽ��ڵ���Դ�������ö���
	struct _collector_config_info
	{
		//�˿ں� 
		int nPort;
		//�ϱ�������IP��ַ
		std::string strReportAddress;
		//�ϱ��������˿ں�
		int nReportPort;

		_collector_config_info()
		{
			nPort = 0;
			strReportAddress = "127.0.0.1";
			nReportPort = 0;
		}
	};

	using COLLECTOR_CONFIG_INFO = _collector_config_info;
	using LP_COLLECTOR_CONFIG_INFO = _collector_config_info*;

	//״̬����ģ�����ö���
	struct _status_manager_config_info
	{
		//�˿ں�
		int nPort;
		//���ݿ������IP��ַ(MYSQL)
		std::string strDBAddress;
		//���ݿ�������˿ں�
		int nDBPort;
		//���ݿ�ʵ��(MYSQL)
		std::string strDBInstanceName;
		//���ݿ��û���
		std::string strUserName;
		//���ݿ�����
		std::string strPassword;

		_status_manager_config_info()
		{
			nPort = 0;
			strDBAddress = "127.0.0.1";
			nDBPort = 3306;
			strDBInstanceName = "";
			strUserName = "";
			strPassword = "";
		}
	};
	using STATUS_MANAGER_CONFIG_INFO = _status_manager_config_info;
	using LP_STATUS_MANAGER_CONFIG_INFO = _status_manager_config_info*;

	//����ģ�����ö���
	struct _scheduer_config_info
	{
		//�˿ں� 
		int nPort;
		//�ϱ���������IP��ַ
		std::string strReportAddress;
		//�ϱ��������Ķ˿ں�
		int nReportPort;

		_scheduer_config_info()
		{
			nPort = 0;
			strReportAddress = "127.0.0.1";
			nReportPort = 0;
		}
	};
	using SCHEDUER_CONFIG_INFO = _scheduer_config_info;
	using LP_SCHEDUER_CONFIG_INFO = _scheduer_config_info*;

	//��������ģ�����ö���
	struct _receiver_config_info
	{
		//�˿�
		int nPort;
		//�ϱ���������IP��ַ
		std::string strReportAddress;
		//�ϱ��������Ķ˿ں�
		int nReportPort;
		//���ȷ�������IP��ַ
		std::string strScheduerAddress;
		//���ȷ������Ķ˿ں�
		int nScheduerPort;

		_receiver_config_info()
		{
			nPort = 0;
			strReportAddress = "127.0.0.1";
			nReportPort = 0;
			strScheduerAddress = "127.0.0.1";
			nScheduerPort = 0;
		}
	};
	using RECEIVER_CONFIG_INFO = _receiver_config_info;
	using LP_RECEIVER_CONFIG_INFO = _receiver_config_info*;


	//����ڵ����ö���
	struct _node_config_info
	{
		//�˿ں�
		int nPort;
		//�����IP��ַ
		std::string strIPAddress;
		//�ϱ�ʱ����(s)
		int nReportGap;
		//���ķ�������IP��ַ
		std::string strCenterAddress;
		//���ķ������Ķ˿ں�
		int nCenterPort;
		//�ϱ���������IP��ַ
		std::string strReportAddress;
		//�ϱ��������Ķ˿ں�
		int nReportPort;

		_node_config_info()
		{
			nPort = 0;
			strIPAddress = "127.0.0.1";
			nReportGap = 15;
			strCenterAddress = "127.0.0.1";
			nCenterPort = 0;
			strReportAddress = "127.0.0.1";
			nReportPort = 0;
		}
	};
	using NODE_CONFIG_INFO = _node_config_info;
	using LP_NODE_CONFIG_INFO = _node_config_info*;

}
