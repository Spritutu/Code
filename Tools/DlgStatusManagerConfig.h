#pragma once

#include "BaseDialog.h"
#include "afxcmn.h"
// CDlgStatusManagerConfig �Ի���

class CDlgStatusManagerConfig : public CBaseDialog
{
	DECLARE_DYNAMIC(CDlgStatusManagerConfig)

public:
	CDlgStatusManagerConfig(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgStatusManagerConfig();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_STATUS_MANAGER_CONFIG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL CreateSelf(CWnd* pWnd) override;
	virtual void SaveConfig(void) override;
private:
	CIPAddressCtrl m_DBServerAddress;
public:
	virtual BOOL OnInitDialog();
private:
	void DisplayConfigInfo(void);
};
