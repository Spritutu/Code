/**************************************************************************
Copyright(C):Envision. Co., Ltd.
FileName:MysqlConnector.h
Description:����Mysql��
Author:xiaowei.han
Date:2017/05/27
Others:
Histroy:
**************************************************************************/
#pragma once
#include <string>
#include <boost/thread/mutex.hpp>
#include <mysql.h>
#include <string>
#include <vector>
typedef struct _connector_element
{
	//�û���
	std::string strUserName;
	//����
	std::string strPassword;
	//IP��ַ
	std::string strIPAddress;
	//�˿ں�
	int nPort;
	//���ݿ�ʵ������
	std::string strMysqlInstance;

	_connector_element()
	{
		nPort = 3306;
	}

}CONNECTOR_ELEMENT,* LP_CONNECTOR_ELEMENT;

class CMysqlConnector
{

public:
	static CMysqlConnector& CreateInstance(void);

	//������������
	void SetConnectorElement(const CONNECTOR_ELEMENT& Element);

	//�������ݿ�
	bool ConnectDB(void);

	//�Ͽ����ݿ�����
	bool DisconnectDB(void);

	//ʵ�ֶϿ���������
	void PingDB(void);

	//ִ�зǲ�ѯ��SQL���
	bool RunNoQuerySQL(const std::string& strSQL);

	//ִ�в�ѯ��SQL���
	bool RunQuerySQL(const std::string& strSQL,std::vector<std::string>& ResultArray);
protected:
	CMysqlConnector();
	virtual ~CMysqlConnector();
private:
	//�������ݿ������
	CONNECTOR_ELEMENT m_ConnectorElement;

	//����mysql�Ķ���
	MYSQL* m_pConnectPtr;

	//�������ݿ����
	boost::mutex m_Lock;

	//��ʵ������
	static CMysqlConnector s_obj;
};

