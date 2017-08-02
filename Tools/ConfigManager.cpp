#include "stdafx.h"
#include "ConfigManager.h"
#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/encodedstream.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/writer.h>
#include <boost/scope_exit.hpp>
#include <boost/functional/factory.hpp>
#include <cstdio>
#include <cstring>
#include <fstream>
#include "Utility.h"

CConfigManager& CConfigManager::CreateInstance(void)
{
	return s_Obj;
}

CConfigManager::CConfigManager()
{
}


CConfigManager::~CConfigManager()
{
}

bool CConfigManager::ReadCollectorConfigInfo(const std::string& strConfigPath, ConfigType::LP_COLLECTOR_CONFIG_INFO pConfigInfo)
{
	if (strConfigPath.empty() || nullptr == pConfigInfo)
	{
		return false;
	}
	using namespace rapidjson;
	//�������ļ�
	FILE* fp = fopen(strConfigPath.c_str(), "rb");
	if (nullptr == fp)
	{
		return false;
	}

	BOOST_SCOPE_EXIT(&fp)
	{
		if (nullptr != fp)
		{
			fclose(fp);
			fp = nullptr;
		}
	}BOOST_SCOPE_EXIT_END

	//��ȡ�ļ�����
	fseek(fp, 0, SEEK_END);
	int nFileLength = static_cast<int>(ftell(fp));
	if (nFileLength <= 0)
	{
		return false;
	}
	//�����ڴ�
	char* pBuffer = new char[nFileLength + 1];
	if (nullptr == pBuffer)
	{
		return false;
	}
	BOOST_SCOPE_EXIT(&pBuffer)
	{
		if (nullptr != pBuffer)
		{
			DELETE_ARRAY_POINTER(pBuffer);
		}
	}BOOST_SCOPE_EXIT_END
	memset(pBuffer, 0, nFileLength + 1);

	fseek(fp, 0, SEEK_SET);
	FileReadStream bis(fp, pBuffer, nFileLength + 1);
	AutoUTFInputStream<unsigned, FileReadStream> eis(bis);
	Document Parser;
	Parser.ParseStream<0, AutoUTF<unsigned> >(eis);
	if (Parser.HasParseError())
	{
		return false;
	}

	//��ȡ�˿ں�
	if (!Parser.HasMember("Port") || !Parser["Port"].IsInt())
	{
		return false;
	}
	pConfigInfo->nPort = Parser["Port"].GetInt();
	//��ȡIP��ַ
	if (!Parser.HasMember("StatusManagerAddress") || !Parser["StatusManagerAddress"].IsString())
	{
		return false;
	}
	pConfigInfo->strReportAddress = Parser["StatusManagerAddress"].GetString();
	

	//��ȡ�˿ں�
	if (!Parser.HasMember("StatusManagerPort") || !Parser["StatusManagerPort"].IsInt())
	{
		return false;
	}
	pConfigInfo->nReportPort = Parser["StatusManagerPort"].GetInt();
	
	return true;
}

bool CConfigManager::WriteCollectorConfigInfo(const std::string& strConfigPath, const ConfigType::LP_COLLECTOR_CONFIG_INFO pConfigInfo)
{
	if (strConfigPath.empty() || nullptr == pConfigInfo)
	{
		return false;
	}
	using namespace rapidjson;
	using namespace std;
	
	Document document;
	document.SetObject();

	auto& allocator = document.GetAllocator();

	//���Ӷ˿�
	document.AddMember("Port", pConfigInfo->nPort, allocator);
	//����IP��ַ
	document.AddMember("StatusManagerAddress", StringRef(pConfigInfo->strReportAddress.c_str()), allocator);
	//���Ӷ˿ں�
	document.AddMember("StatusManagerPort", pConfigInfo->nReportPort, allocator);

	std::ofstream ofs(strConfigPath);

	BOOST_SCOPE_EXIT(&ofs)
	{
		if (ofs.is_open())
		{
			ofs.close();
		}
	}BOOST_SCOPE_EXIT_END
	OStreamWrapper osw(ofs);
	Writer<OStreamWrapper> writer(osw);
	if (!document.Accept(writer))
	{
		return false;
	}
	return true;
}

bool CConfigManager::ReadNodeConfigInfo(const std::string& strConfigPath, ConfigType::LP_NODE_CONFIG_INFO pConfigInfo)
{
	if (strConfigPath.empty() || nullptr == pConfigInfo)
	{
		return false;
	}
	using namespace rapidjson;
	//�������ļ�
	FILE* fp = fopen(strConfigPath.c_str(), "rb");
	if (nullptr == fp)
	{
		return false;
	}

	BOOST_SCOPE_EXIT(&fp)
	{
		if (nullptr != fp)
		{
			fclose(fp);
			fp = nullptr;
		}
	}BOOST_SCOPE_EXIT_END

	//��ȡ�ļ�����
	fseek(fp, 0, SEEK_END);
	int nFileLength = static_cast<int>(ftell(fp));
	if (nFileLength <= 0)
	{
		return false;
	}
	//�����ڴ�
	char* pBuffer = new char[nFileLength + 1];
	if (nullptr == pBuffer)
	{
		return false;
	}
	BOOST_SCOPE_EXIT(&pBuffer)
	{
		if (nullptr != pBuffer)
		{
			DELETE_ARRAY_POINTER(pBuffer);
		}
	}BOOST_SCOPE_EXIT_END
	memset(pBuffer, 0, nFileLength + 1);
	fseek(fp, 0, SEEK_SET);
	FileReadStream bis(fp, pBuffer, nFileLength + 1);
	AutoUTFInputStream<unsigned, FileReadStream> eis(bis);
	Document Parser;
	Parser.ParseStream<0, AutoUTF<unsigned> >(eis);
	if (Parser.HasParseError())
	{
		return false;
	}

	//�ڵ������IP��ַ
	if (!Parser.HasMember("IPAddress") || !Parser["IPAddress"].IsString())
	{
		return false;
	}
	pConfigInfo->strIPAddress = Parser["IPAddress"].GetString();

	//��ȡ�˿ں�
	if (!Parser.HasMember("Port") || !Parser["Port"].IsInt())
	{
		return false;
	}
	pConfigInfo->nPort = Parser["Port"].GetInt();


	//��ȡ�ϱ����
	if (!Parser.HasMember("ReportGap") || !Parser["ReportGap"].IsInt())
	{
		return false;
	}
	pConfigInfo->nReportGap = Parser["ReportGap"].GetInt();

	//��ȡ�Ѽ���Դ������IP��ַ
	if (!Parser.HasMember("CenterAddress") || !Parser["CenterAddress"].IsString())
	{
		return false;
	}
	pConfigInfo->strCenterAddress = Parser["CenterAddress"].GetString();

	//��ȡ�Ѽ���Դ�������˿ں�
	if (!Parser.HasMember("CenterPort") || !Parser["CenterPort"].IsInt())
	{
		return false;
	}
	pConfigInfo->nCenterPort = Parser["CenterPort"].GetInt();


	//��ȡIP��ַ
	if (!Parser.HasMember("StatusManagerAddress") || !Parser["StatusManagerAddress"].IsString())
	{
		return false;
	}
	pConfigInfo->strReportAddress = Parser["StatusManagerAddress"].GetString();


	//��ȡ�˿ں�
	if (!Parser.HasMember("StatusManagerPort") || !Parser["StatusManagerPort"].IsInt())
	{
		return false;
	}
	pConfigInfo->nReportPort = Parser["StatusManagerPort"].GetInt();


	return true;
}

bool CConfigManager::WriteNodeConfigInfo(const std::string& strConfigPath, const ConfigType::LP_NODE_CONFIG_INFO pConfigInfo)
{
	if (strConfigPath.empty() || nullptr == pConfigInfo)
	{
		return false;
	}
	using namespace rapidjson;
	using namespace std;
	Document document;
	document.SetObject();
	auto& allocator = document.GetAllocator();
	//����IP��ַ
	document.AddMember("IPAddress", StringRef(pConfigInfo->strIPAddress.c_str()), allocator);
	//���Ӷ˿�
	document.AddMember("Port", pConfigInfo->nPort, allocator);
	//���Ӷ˿ں�
	document.AddMember("ReportGap", pConfigInfo->nReportGap, allocator);
	//���Ӷ˿ں�
	document.AddMember("StatusManagerAddress", StringRef(pConfigInfo->strReportAddress.c_str()), allocator);
	//���Ӷ˿ں�
	document.AddMember("StatusManagerPort", pConfigInfo->nReportPort, allocator);

	//���Ӷ˿ں�
	document.AddMember("CenterAddress", StringRef(pConfigInfo->strCenterAddress.c_str()), allocator);
	//���Ӷ˿ں�
	document.AddMember("CenterPort", pConfigInfo->nCenterPort, allocator);
	std::ofstream ofs(strConfigPath);

	BOOST_SCOPE_EXIT(&ofs)
	{
		if (ofs.is_open())
		{
			ofs.close();
		}
	}BOOST_SCOPE_EXIT_END
	OStreamWrapper osw(ofs);
	Writer<OStreamWrapper> writer(osw);
	if (!document.Accept(writer))
	{
		return false;
	}
	return true;
}

bool CConfigManager::ReadStatusManagerConfigInfo(const std::string& strConfigPath, ConfigType::LP_STATUS_MANAGER_CONFIG_INFO pConfigInfo)
{
	if (strConfigPath.empty() || nullptr == pConfigInfo)
	{
		return false;
	}

	using namespace rapidjson;
	//�������ļ�
	FILE* fp = fopen(strConfigPath.c_str(), "rb");
	if (nullptr == fp)
	{
		return false;
	}

	BOOST_SCOPE_EXIT(&fp)
	{
		if (nullptr != fp)
		{
			fclose(fp);
			fp = nullptr;
		}
	}BOOST_SCOPE_EXIT_END

	//��ȡ�ļ�����
	fseek(fp, 0, SEEK_END);
	int nFileLength = static_cast<int>(ftell(fp));
	if (nFileLength <= 0)
	{
		return false;
	}
	//�����ڴ�
	char* pBuffer = new char[nFileLength + 1];
	if (nullptr == pBuffer)
	{
		return false;
	}
	BOOST_SCOPE_EXIT(&pBuffer)
	{
		if (nullptr != pBuffer)
		{
			DELETE_ARRAY_POINTER(pBuffer);
		}
	}BOOST_SCOPE_EXIT_END
	memset(pBuffer, 0, nFileLength + 1);

	fseek(fp, 0, SEEK_SET);
	FileReadStream bis(fp, pBuffer, nFileLength + 1);
	AutoUTFInputStream<unsigned, FileReadStream> eis(bis);
	Document Parser;
	Parser.ParseStream<0, AutoUTF<unsigned> >(eis);
	if (Parser.HasParseError())
	{
		return false;
	}

	//��ȡ�˿ں�
	if (!Parser.HasMember("Port") || !Parser["Port"].IsInt())
	{
		return false;
	}
	pConfigInfo->nPort = Parser["Port"].GetInt();
	//��ȡIP��ַ
	if (!Parser.HasMember("DBPort") || !Parser["DBPort"].IsInt())
	{
		return false;
	}
	pConfigInfo->nDBPort = Parser["DBPort"].GetInt();

	//���ݿ������IP��ַ
	if (!Parser.HasMember("DBIPAddress") || !Parser["DBIPAddress"].IsString())
	{
		return false;
	}
	pConfigInfo->strDBAddress = Parser["DBIPAddress"].GetString();

	//���ݿ�ʵ��
	if (!Parser.HasMember("DBInstanceName") || !Parser["DBInstanceName"].IsString())
	{
		return false;
	}
	pConfigInfo->strDBInstanceName = Parser["DBInstanceName"].GetString();

	//���ݿ��û���
	if (!Parser.HasMember("DBUserName") || !Parser["DBUserName"].IsString())
	{
		return false;
	}
	pConfigInfo->strUserName = Parser["DBUserName"].GetString();

	//���ݿ�����
	if (!Parser.HasMember("DBPassword") || !Parser["DBPassword"].IsString())
	{
		return false;
	}
	pConfigInfo->strPassword = Parser["DBPassword"].GetString();

	return true;
}

bool CConfigManager::WriteStatusManagerConfigInfo(const std::string& strConfigPath, const ConfigType::LP_STATUS_MANAGER_CONFIG_INFO pConfigInfo)
{
	if (strConfigPath.empty() || nullptr == pConfigInfo)
	{
		return false;
	}

	using namespace rapidjson;
	using namespace std;
	Document document;
	document.SetObject();
	auto& allocator = document.GetAllocator();
	//���Ӷ˿�
	document.AddMember("Port", pConfigInfo->nPort, allocator);

	document.AddMember("DBIPAddress", StringRef(pConfigInfo->strDBAddress.c_str()), allocator);

	document.AddMember("DBPort", pConfigInfo->nDBPort, allocator);

	//���Ӷ˿ں�
	document.AddMember("DBInstanceName", StringRef(pConfigInfo->strDBInstanceName.c_str()), allocator);

	//���Ӷ˿ں�
	document.AddMember("DBUserName", StringRef(pConfigInfo->strUserName.c_str()), allocator);

	//���Ӷ˿ں�
	document.AddMember("DBPassword", StringRef(pConfigInfo->strPassword.c_str()), allocator);

	std::ofstream ofs(strConfigPath);

	BOOST_SCOPE_EXIT(&ofs)
	{
		if (ofs.is_open())
		{
			ofs.close();
		}
	}BOOST_SCOPE_EXIT_END
	OStreamWrapper osw(ofs);
	Writer<OStreamWrapper> writer(osw);
	if (!document.Accept(writer))
	{
		return false;
	}
	return true;
}

bool CConfigManager::ReadScheduerConfigInfo(const std::string& strConfigPath, ConfigType::LP_SCHEDUER_CONFIG_INFO pConfigInfo)
{
	if (strConfigPath.empty() || nullptr == pConfigInfo)
	{
		return false;
	}
	using namespace rapidjson;
	//�������ļ�
	FILE* fp = fopen(strConfigPath.c_str(), "rb");
	if (nullptr == fp)
	{
		return false;
	}

	BOOST_SCOPE_EXIT(&fp)
	{
		if (nullptr != fp)
		{
			fclose(fp);
			fp = nullptr;
		}
	}BOOST_SCOPE_EXIT_END

	//��ȡ�ļ�����
	fseek(fp, 0, SEEK_END);
	int nFileLength = static_cast<int>(ftell(fp));
	if (nFileLength <= 0)
	{
		return false;
	}
	//�����ڴ�
	char* pBuffer = new char[nFileLength + 1];
	if (nullptr == pBuffer)
	{
		return false;
	}
	BOOST_SCOPE_EXIT(&pBuffer)
	{
		if (nullptr != pBuffer)
		{
			DELETE_ARRAY_POINTER(pBuffer);
		}
	}BOOST_SCOPE_EXIT_END
	memset(pBuffer, 0, nFileLength + 1);

	fseek(fp, 0, SEEK_SET);
	FileReadStream bis(fp, pBuffer, nFileLength + 1);
	AutoUTFInputStream<unsigned, FileReadStream> eis(bis);
	Document Parser;
	Parser.ParseStream<0, AutoUTF<unsigned> >(eis);
	if (Parser.HasParseError())
	{
		return false;
	}

	//��ȡ�˿ں�
	if (!Parser.HasMember("Port") || !Parser["Port"].IsInt())
	{
		return false;
	}
	pConfigInfo->nPort = Parser["Port"].GetInt();
	//��ȡIP��ַ
	if (!Parser.HasMember("StatusManagerAddress") || !Parser["StatusManagerAddress"].IsString())
	{
		return false;
	}
	pConfigInfo->strReportAddress = Parser["StatusManagerAddress"].GetString();


	//��ȡ�˿ں�
	if (!Parser.HasMember("StatusManagerPort") || !Parser["StatusManagerPort"].IsInt())
	{
		return false;
	}
	pConfigInfo->nReportPort = Parser["StatusManagerPort"].GetInt();

	return true;
}

bool CConfigManager::WriteScheduerConfigInfo(const std::string& strConfigPath, const ConfigType::LP_SCHEDUER_CONFIG_INFO pConfigInfo)
{
	if (strConfigPath.empty() || nullptr == pConfigInfo)
	{
		return false;
	}

	using namespace rapidjson;
	using namespace std;

	Document document;
	document.SetObject();

	auto& allocator = document.GetAllocator();

	//���Ӷ˿�
	document.AddMember("Port", pConfigInfo->nPort, allocator);
	//����IP��ַ
	document.AddMember("StatusManagerAddress", StringRef(pConfigInfo->strReportAddress.c_str()), allocator);
	//���Ӷ˿ں�
	document.AddMember("StatusManagerPort", pConfigInfo->nReportPort, allocator);

	std::ofstream ofs(strConfigPath);

	BOOST_SCOPE_EXIT(&ofs)
	{
		if (ofs.is_open())
		{
			ofs.close();
		}
	}BOOST_SCOPE_EXIT_END
	OStreamWrapper osw(ofs);
	Writer<OStreamWrapper> writer(osw);
	if (!document.Accept(writer))
	{
		return false;
	}
	return true;
}

bool CConfigManager::ReadReceiverConfigInfo(const std::string& strConfigPath, ConfigType::LP_RECEIVER_CONFIG_INFO pConfigInfo)
{
	if (strConfigPath.empty() || nullptr == pConfigInfo)
	{
		return false;
	}
	using namespace rapidjson;
	//�������ļ�
	FILE* fp = fopen(strConfigPath.c_str(), "rb");
	if (nullptr == fp)
	{
		return false;
	}

	BOOST_SCOPE_EXIT(&fp)
	{
		if (nullptr != fp)
		{
			fclose(fp);
			fp = nullptr;
		}
	}BOOST_SCOPE_EXIT_END

	//��ȡ�ļ�����
	fseek(fp, 0, SEEK_END);
	int nFileLength = static_cast<int>(ftell(fp));
	if (nFileLength <= 0)
	{
		return false;
	}
	//�����ڴ�
	char* pBuffer = new char[nFileLength + 1];
	if (nullptr == pBuffer)
	{
		return false;
	}
	BOOST_SCOPE_EXIT(&pBuffer)
	{
		if (nullptr != pBuffer)
		{
			DELETE_ARRAY_POINTER(pBuffer);
		}
	}BOOST_SCOPE_EXIT_END
	memset(pBuffer, 0, nFileLength + 1);

	fseek(fp, 0, SEEK_SET);
	FileReadStream bis(fp, pBuffer, nFileLength + 1);
	AutoUTFInputStream<unsigned, FileReadStream> eis(bis);
	Document Parser;
	Parser.ParseStream<0, AutoUTF<unsigned> >(eis);
	if (Parser.HasParseError())
	{
		return false;
	}

	//��ȡ�˿ں�
	if (!Parser.HasMember("Port") || !Parser["Port"].IsInt())
	{
		return false;
	}
	pConfigInfo->nPort = Parser["Port"].GetInt();
	//��ȡIP��ַ
	if (!Parser.HasMember("StatusManagerAddress") || !Parser["StatusManagerAddress"].IsString())
	{
		return false;
	}
	pConfigInfo->strReportAddress = Parser["StatusManagerAddress"].GetString();


	//��ȡ�˿ں�
	if (!Parser.HasMember("StatusManagerPort") || !Parser["StatusManagerPort"].IsInt())
	{
		return false;
	}
	pConfigInfo->nReportPort = Parser["StatusManagerPort"].GetInt();

	//��ȡIP��ַ
	if (!Parser.HasMember("ScheduerAddress") || !Parser["ScheduerAddress"].IsString())
	{
		return false;
	}
	pConfigInfo->strScheduerAddress = Parser["ScheduerAddress"].GetString();

	//��ȡ�˿ں�
	if (!Parser.HasMember("ScheduerPort") || !Parser["ScheduerPort"].IsInt())
	{
		return false;
	}
	pConfigInfo->nScheduerPort = Parser["ScheduerPort"].GetInt();

	return true;
}

bool CConfigManager::WriteReceiverConfigInfo(const std::string& strConfigPath, const ConfigType::LP_RECEIVER_CONFIG_INFO pConfigInfo)
{
	if (strConfigPath.empty() || nullptr == pConfigInfo)
	{
		return false;
	}

	using namespace rapidjson;
	using namespace std;
	Document document;
	document.SetObject();
	auto& allocator = document.GetAllocator();
	//���Ӷ˿�
	document.AddMember("Port", pConfigInfo->nPort, allocator);

	document.AddMember("StatusManagerAddress", StringRef(pConfigInfo->strReportAddress.c_str()), allocator);

	document.AddMember("StatusManagerPort", pConfigInfo->nReportPort, allocator);

	//���Ӷ˿ں�
	document.AddMember("ScheduerAddress", StringRef(pConfigInfo->strScheduerAddress.c_str()), allocator);

	//���Ӷ˿ں�
	document.AddMember("ScheduerAddress", pConfigInfo->nScheduerPort, allocator);

	std::ofstream ofs(strConfigPath);

	BOOST_SCOPE_EXIT(&ofs)
	{
		if (ofs.is_open())
		{
			ofs.close();
		}
	}BOOST_SCOPE_EXIT_END
	OStreamWrapper osw(ofs);
	Writer<OStreamWrapper> writer(osw);
	if (!document.Accept(writer))
	{
		return false;
	}
	return true;
}

CConfigManager CConfigManager::s_Obj;
