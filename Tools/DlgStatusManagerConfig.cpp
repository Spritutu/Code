// DlgStatusManagerConfig.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "EHPCSettingTool.h"
#include "DlgStatusManagerConfig.h"
#include <string>
#include <WS2tcpip.h>
#include <boost/format.hpp>
#include "Utility.h"
#include "ConfigManager.h"

// CDlgStatusManagerConfig �Ի���

IMPLEMENT_DYNAMIC(CDlgStatusManagerConfig, CBaseDialog)

CDlgStatusManagerConfig::CDlgStatusManagerConfig(CWnd* pParent /*=NULL*/)
	: CBaseDialog(IDD_DLG_STATUS_MANAGER_CONFIG, pParent)
{

}

CDlgStatusManagerConfig::~CDlgStatusManagerConfig()
{
}

void CDlgStatusManagerConfig::DoDataExchange(CDataExchange* pDX)
{
	CBaseDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SERVER_ADDRESS, m_DBServerAddress);
}


BOOL CDlgStatusManagerConfig::CreateSelf(CWnd* pWnd)
{
	return Create(CDlgStatusManagerConfig::IDD, pWnd);
}

void CDlgStatusManagerConfig::SaveConfig(void)
{
	using namespace std;
	using namespace ConfigType;
	if (NULL == m_DBServerAddress.GetSafeHwnd())
	{
		return;
	}

	STATUS_MANAGER_CONFIG_INFO ConfigInfo;
	//��ȡ�˿ں�
	ConfigInfo.nPort = GetDlgItemInt(IDC_PORT_NUM);

	BYTE IP1 = 0;
	BYTE IP2 = 0;
	BYTE IP3 = 0;
	BYTE IP4 = 0;
	//��ȡIP��ַ
	m_DBServerAddress.GetAddress(IP1, IP2, IP3, IP4);
	string strIPAddressFormat("%1%.%2%.%3%.%4%");
	boost::format FT(strIPAddressFormat);
	FT % (int)IP1 % (int)IP2 % (int)IP3 % (int)IP4;
	ConfigInfo.strDBAddress = FT.str();
	ConfigInfo.nDBPort = GetDlgItemInt(IDC_SERVER_PORT);

	CWnd* pWnd = GetDlgItem(IDC_DB_INSTANCE_NAME);

	if (nullptr != pWnd && NULL != pWnd->GetSafeHwnd())
	{
		CString strInstanceName;
		pWnd->GetWindowText(strInstanceName);
#ifdef _UNICODE
		ConfigInfo.strDBInstanceName = Utility::WideChar2MultiByte(strInstanceName.GetBuffer(0));
#else
		ConfigInfo.strDBInstanceName = strInstanceName.GetBuffer(0);
#endif
	}

	pWnd = GetDlgItem(IDC_DB_USER_NAME);

	if (nullptr != pWnd && NULL != pWnd->GetSafeHwnd())
	{
		CString strUserName;
		pWnd->GetWindowText(strUserName);
#ifdef _UNICODE
		ConfigInfo.strUserName = Utility::WideChar2MultiByte(strUserName.GetBuffer(0));
#else
		ConfigInfo.strUserName = strUserName.GetBuffer(0);
#endif
	}

	pWnd = GetDlgItem(IDC_DB_PASSWORD);

	if (nullptr != pWnd && NULL != pWnd->GetSafeHwnd())
	{
		CString strPassword;
		pWnd->GetWindowText(strPassword);
#ifdef _UNICODE
		ConfigInfo.strPassword = Utility::WideChar2MultiByte(strPassword.GetBuffer(0));
#else
		ConfigInfo.strPassword = strPassword.GetBuffer(0);
#endif
	}

	//��ȡ·��
	string strConfigPath = Utility::GetExeDirecory() + string(R"(\)") + m_strConfigFileName;

	//����json�ļ�
	CConfigManager::CreateInstance().WriteStatusManagerConfigInfo(strConfigPath, &ConfigInfo);
}

BEGIN_MESSAGE_MAP(CDlgStatusManagerConfig, CBaseDialog)
END_MESSAGE_MAP()


// CDlgStatusManagerConfig ��Ϣ�������


BOOL CDlgStatusManagerConfig::OnInitDialog()
{
	CBaseDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	DisplayConfigInfo();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

void CDlgStatusManagerConfig::DisplayConfigInfo(void)
{
	using namespace std;
	ConfigType::STATUS_MANAGER_CONFIG_INFO ConfigInfo;

	//��ȡ·��
	string strConfigPath = Utility::GetExeDirecory() + string(R"(\)") + m_strConfigFileName;

	//���سɹ�
	if (CConfigManager::CreateInstance().ReadStatusManagerConfigInfo(strConfigPath, &ConfigInfo))
	{
		if (m_DBServerAddress.GetSafeHwnd())
		{
			unsigned long nAddress = 0;
			inet_pton(AF_INET, ConfigInfo.strDBAddress.c_str(), &nAddress);

			nAddress = htonl(nAddress);
			//��IP��ַ����ת��
			m_DBServerAddress.SetAddress(nAddress);
		}

		SetDlgItemInt(IDC_PORT_NUM, ConfigInfo.nPort);
		SetDlgItemInt(IDC_SERVER_PORT, ConfigInfo.nDBPort);

		CWnd* pWnd = GetDlgItem(IDC_DB_INSTANCE_NAME);
		if (nullptr != pWnd && pWnd->GetSafeHwnd())
		{
			pWnd->SetWindowText(CString(ConfigInfo.strDBInstanceName.c_str()));
		}
		pWnd = GetDlgItem(IDC_DB_USER_NAME);
		if (nullptr != pWnd && pWnd->GetSafeHwnd())
		{
			pWnd->SetWindowText(CString(ConfigInfo.strUserName.c_str()));
		}
		pWnd = GetDlgItem(IDC_DB_PASSWORD);
		if (nullptr != pWnd && pWnd->GetSafeHwnd())
		{
			pWnd->SetWindowText(CString(ConfigInfo.strPassword.c_str()));
		}
	}
	else
	{
		if (m_DBServerAddress.GetSafeHwnd())
		{
			unsigned long nAddress = 0;
			inet_pton(AF_INET, ConfigInfo.strDBAddress.c_str(), &nAddress);
			//��IP��ַ����ת��
			nAddress = htonl(nAddress);
			m_DBServerAddress.SetAddress(nAddress);
		}
		SetDlgItemInt(IDC_PORT_NUM, ConfigInfo.nPort);
		SetDlgItemInt(IDC_SERVER_PORT, ConfigInfo.nDBPort);

		CWnd* pWnd = GetDlgItem(IDC_DB_INSTANCE_NAME);
		if (nullptr != pWnd && pWnd->GetSafeHwnd())
		{
			pWnd->SetWindowText(CString(ConfigInfo.strDBInstanceName.c_str()));
		}
		pWnd = GetDlgItem(IDC_DB_USER_NAME);
		if (nullptr != pWnd && pWnd->GetSafeHwnd())
		{
			pWnd->SetWindowText(CString(ConfigInfo.strUserName.c_str()));
		}
		pWnd = GetDlgItem(IDC_DB_PASSWORD);
		if (nullptr != pWnd && pWnd->GetSafeHwnd())
		{
			pWnd->SetWindowText(CString(ConfigInfo.strPassword.c_str()));
		}
	}
}
