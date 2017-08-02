
// EHPCSettingToolDlg.h : ͷ�ļ�
//

#pragma once
#include <string>
#include <vector>
#include <boost/ptr_container/ptr_vector.hpp>
#include "BaseTabWnd.h"
#include "TabNameMap.h"
#include "BaseDialog.h"
// CEHPCSettingToolDlg �Ի���
class CEHPCSettingToolDlg : public CBCGPDialog
{
// ����
public:
	CEHPCSettingToolDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EHPCSETTINGTOOL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


private:
	//��ʼ���ؼ�
	void InitDisplay(void);
private:
	//TabWnd
	CBaseTabWnd m_TabWnd;
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);


private:
	//�����������ļ��Ƿ����
	void DetectConfigFile(std::vector<std::string>& ConfigFileArray);
public:
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnBnClickedBtnQuit();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

private:
	CTabNameMap m_TabMap;
	boost::ptr_vector<CBaseDialog> m_TabPtrArray;
};
