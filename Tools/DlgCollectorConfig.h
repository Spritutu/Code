#pragma once

#include "BaseDialog.h"
#include "afxcmn.h"
// CDlgCollectorConfig �Ի���

class CDlgCollectorConfig : public CBaseDialog
{
	DECLARE_DYNAMIC(CDlgCollectorConfig)

public:
	CDlgCollectorConfig(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgCollectorConfig();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_COLLECTOR_CONFIG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL CreateSelf(CWnd* pWnd) override;

	virtual void SaveConfig(void) override;

private:
	void DisplayConfigInfo(void);
public:
	virtual BOOL OnInitDialog();
private:
	CIPAddressCtrl m_IPAddress;
};
