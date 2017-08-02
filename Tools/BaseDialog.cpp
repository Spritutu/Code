/*******************************************************************************
Copyright(C):Envision. Co., Ltd.
FileName:BaseDialog.cpp
Description:Dialog�Ļ���,���жԻ��򶼴Ӵ�����
Author:xiaowei.han
Date:2016-9-11
Others:
Histroy:
*******************************************************************************/
#include "stdafx.h"
#include "BaseDialog.h"
IMPLEMENT_DYNAMIC(CBaseDialog,CBCGPDialog)
CBaseDialog::CBaseDialog( UINT nIDTemplate, CWnd* pParentWnd,BOOL bEnableLayout):
CBCGPDialog(nIDTemplate,pParentWnd)
{
	EnableLayout(bEnableLayout);
}

CBaseDialog::~CBaseDialog( void )
{
	//CBCGPMaskEdit
}


BOOL CBaseDialog::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	EnableVisualManagerStyle(TRUE,TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
BEGIN_MESSAGE_MAP(CBaseDialog, CBCGPDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()

BOOL CBaseDialog::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���

	if (WM_KEYDOWN == pMsg->message)
	{
		if (VK_RETURN == pMsg->wParam || VK_ESCAPE == pMsg->wParam)
		{
			return TRUE;
		}
	}
	return CBCGPDialog::PreTranslateMessage(pMsg);
}

void CBaseDialog::OnSize(UINT nType, int cx, int cy)
{
	CBCGPDialog::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	Invalidate(TRUE);
}


