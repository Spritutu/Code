// DlgCollectorConfig.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "EHPCSettingTool.h"
#include "DlgCollectorConfig.h"
#include <string>
#include <WS2tcpip.h>
#include <boost/format.hpp>
#include "Utility.h"
#include "ConfigManager.h"
// CDlgCollectorConfig �Ի���

IMPLEMENT_DYNAMIC(CDlgCollectorConfig, CBaseDialog)

CDlgCollectorConfig::CDlgCollectorConfig(CWnd* pParent /*=NULL*/)
	: CBaseDialog(IDD_DLG_COLLECTOR_CONFIG, pParent)
{

}

CDlgCollectorConfig::~CDlgCollectorConfig()
{
}

void CDlgCollectorConfig::DoDataExchange(CDataExchange* pDX)
{
	CBaseDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SERVER_ADDRESS, m_IPAddress);
}

BOOL CDlgCollectorConfig::CreateSelf(CWnd* pWnd)
{
	return Create(CDlgCollectorConfig::IDD, pWnd);
}

void CDlgCollectorConfig::SaveConfig(void)
{
	using namespace std;
	using namespace ConfigType;
	if (NULL == m_IPAddress.GetSafeHwnd())
	{
		return;
	}

	COLLECTOR_CONFIG_INFO ConfigInfo;

	BYTE IP1 = 0;
	BYTE IP2 = 0;
	BYTE IP3 = 0;
	BYTE IP4 = 0;
	//��ȡIP��ַ
	m_IPAddress.GetAddress(IP1, IP2, IP3, IP4);
	string strIPAddressFormat("%1%.%2%.%3%.%4%");
	boost::format FT(strIPAddressFormat);
	FT % (int)IP1 % (int)IP2 % (int)IP3 % (int)IP4;
	ConfigInfo.strReportAddress = FT.str();

	//��ȡ�˿ں�
	ConfigInfo.nPort = GetDlgItemInt(IDC_PORT_NUM);
	ConfigInfo.nReportPort = GetDlgItemInt(IDC_SERVER_PORT);

	//��ȡ·��
	string strConfigPath = Utility::GetExeDirecory() + string(R"(\)") + m_strConfigFileName;

	//����json�ļ�
	CConfigManager::CreateInstance().WriteCollectorConfigInfo(strConfigPath, &ConfigInfo);
}

void CDlgCollectorConfig::DisplayConfigInfo(void)
{
	using namespace std;
	ConfigType::COLLECTOR_CONFIG_INFO ConfigInfo;

	//��ȡ·��
	string strConfigPath = Utility::GetExeDirecory() + string(R"(\)") + m_strConfigFileName;

	//���سɹ�
	if (CConfigManager::CreateInstance().ReadCollectorConfigInfo(strConfigPath, &ConfigInfo))
	{
		if (m_IPAddress.GetSafeHwnd())
		{
			unsigned long nAddress = 0;
			inet_pton(AF_INET, ConfigInfo.strReportAddress.c_str(), &nAddress);

			nAddress = htonl(nAddress);
			//��IP��ַ����ת��
			m_IPAddress.SetAddress(nAddress);
		}

		SetDlgItemInt(IDC_PORT_NUM, ConfigInfo.nPort);
		SetDlgItemInt(IDC_SERVER_PORT, ConfigInfo.nReportPort);
	}
	else
	{
		if (m_IPAddress.GetSafeHwnd())
		{
			unsigned long nAddress = 0;
			inet_pton(AF_INET, "127.0.0.1", &nAddress);
			//��IP��ַ����ת��
			nAddress = htonl(nAddress);
			m_IPAddress.SetAddress(nAddress);
		}
		SetDlgItemInt(IDC_PORT_NUM, 0);
		SetDlgItemInt(IDC_SERVER_PORT, 0);
	}

}

BEGIN_MESSAGE_MAP(CDlgCollectorConfig, CBaseDialog)
END_MESSAGE_MAP()


// CDlgCollectorConfig ��Ϣ�������


BOOL CDlgCollectorConfig::OnInitDialog()
{
	CBaseDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	DisplayConfigInfo();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
