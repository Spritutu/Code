// DlgReceiverConfig.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "EHPCSettingTool.h"
#include "DlgReceiverConfig.h"
#include <string>
#include <WS2tcpip.h>
#include <boost/format.hpp>
#include "Utility.h"
#include "ConfigManager.h"

// CDlgReceiverConfig �Ի���

IMPLEMENT_DYNAMIC(CDlgReceiverConfig, CBaseDialog)

CDlgReceiverConfig::CDlgReceiverConfig(CWnd* pParent /*=NULL*/)
	: CBaseDialog(IDD_DLG_RECEIVER_CONFIG, pParent)
{

}

CDlgReceiverConfig::~CDlgReceiverConfig()
{
}

void CDlgReceiverConfig::DoDataExchange(CDataExchange* pDX)
{
	CBaseDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SERVER_ADDRESS, m_ReportAddress);
	DDX_Control(pDX, IDC_SCHEUDER_SERVER_ADDRESS, m_ScheduerAddress);
}


BOOL CDlgReceiverConfig::CreateSelf(CWnd* pWnd)
{
	return Create(CDlgReceiverConfig::IDD, pWnd);
}

void CDlgReceiverConfig::SaveConfig(void)
{
	using namespace std;
	using namespace ConfigType;

	if (NULL == m_ReportAddress.GetSafeHwnd() || NULL == m_ScheduerAddress.GetSafeHwnd())
	{
		return;
	}
	RECEIVER_CONFIG_INFO ConfigInfo;
	//��ȡ�˿ں�
	ConfigInfo.nPort = GetDlgItemInt(IDC_PORT_NUM);
	BYTE IP1 = 0;
	BYTE IP2 = 0;
	BYTE IP3 = 0;
	BYTE IP4 = 0;
	//��ȡIP��ַ
	m_ReportAddress.GetAddress(IP1, IP2, IP3, IP4);
	string strIPAddressFormat("%1%.%2%.%3%.%4%");
	boost::format FT(strIPAddressFormat);
	FT % (int)IP1 % (int)IP2 % (int)IP3 % (int)IP4;
	ConfigInfo.strReportAddress = FT.str();
	ConfigInfo.nReportPort = GetDlgItemInt(IDC_SERVER_PORT);

	//��ȡIP��ַ
	m_ScheduerAddress.GetAddress(IP1, IP2, IP3, IP4);
	FT.clear();
	FT % (int)IP1 % (int)IP2 % (int)IP3 % (int)IP4;
	ConfigInfo.strScheduerAddress = FT.str();
	ConfigInfo.nScheduerPort = GetDlgItemInt(IDC_SCHEDUER_SERVER_PORT);

	//��ȡ·��
	string strConfigPath = Utility::GetExeDirecory() + string(R"(\)") + m_strConfigFileName;

	//����json�ļ�
	CConfigManager::CreateInstance().WriteReceiverConfigInfo(strConfigPath, &ConfigInfo);
}

BEGIN_MESSAGE_MAP(CDlgReceiverConfig, CBaseDialog)
END_MESSAGE_MAP()


// CDlgReceiverConfig ��Ϣ�������


BOOL CDlgReceiverConfig::OnInitDialog()
{
	CBaseDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	DisplayConfigInfo();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

void CDlgReceiverConfig::DisplayConfigInfo(void)
{
	using namespace std;
	ConfigType::RECEIVER_CONFIG_INFO ConfigInfo;

	//��ȡ·��
	string strConfigPath = Utility::GetExeDirecory() + string(R"(\)") + m_strConfigFileName;

	//���سɹ�
	if (CConfigManager::CreateInstance().ReadReceiverConfigInfo(strConfigPath, &ConfigInfo))
	{
		if (m_ReportAddress.GetSafeHwnd())
		{
			unsigned long nAddress = 0;
			inet_pton(AF_INET, ConfigInfo.strReportAddress.c_str(), &nAddress);

			nAddress = htonl(nAddress);
			//��IP��ַ����ת��
			m_ReportAddress.SetAddress(nAddress);
		}
		if (m_ScheduerAddress.GetSafeHwnd())
		{
			unsigned long nAddress = 0;
			inet_pton(AF_INET, ConfigInfo.strScheduerAddress.c_str(), &nAddress);

			nAddress = htonl(nAddress);
			//��IP��ַ����ת��
			m_ScheduerAddress.SetAddress(nAddress);
		}

		SetDlgItemInt(IDC_PORT_NUM, ConfigInfo.nPort);
		SetDlgItemInt(IDC_SERVER_PORT, ConfigInfo.nReportPort);
		SetDlgItemInt(IDC_SCHEDUER_SERVER_PORT, ConfigInfo.nScheduerPort);
	}
	else
	{
		if (m_ReportAddress.GetSafeHwnd())
		{
			unsigned long nAddress = 0;
			inet_pton(AF_INET, "127.0.0.1", &nAddress);

			nAddress = htonl(nAddress);
			//��IP��ַ����ת��
			m_ReportAddress.SetAddress(nAddress);
		}
		if (m_ScheduerAddress.GetSafeHwnd())
		{
			unsigned long nAddress = 0;
			inet_pton(AF_INET, "127.0.0.1", &nAddress);

			nAddress = htonl(nAddress);
			//��IP��ַ����ת��
			m_ScheduerAddress.SetAddress(nAddress);
		}

		SetDlgItemInt(IDC_PORT_NUM, 0);
		SetDlgItemInt(IDC_SERVER_PORT, 0);
		SetDlgItemInt(IDC_SCHEDUER_SERVER_PORT, 0);
	}
}
