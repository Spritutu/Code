#pragma once

#include "BaseDialog.h"
#include "afxcmn.h"
// CDlgScheduerConfig �Ի���

class CDlgScheduerConfig : public CBaseDialog
{
	DECLARE_DYNAMIC(CDlgScheduerConfig)

public:
	CDlgScheduerConfig(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgScheduerConfig();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_SCHEDUER_CONFIG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL CreateSelf(CWnd* pWnd) override;
	virtual void SaveConfig(void) override;
private:
	CIPAddressCtrl m_IPAddress;
private:
	void DisplayConfigInfo(void);
public:
	virtual BOOL OnInitDialog();
};
