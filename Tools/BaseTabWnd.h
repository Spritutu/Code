/*******************************************************************************
Copyright(C):Envision. Co., Ltd.
FileName:BaseTabWnd.h
Description:TabWnd����
Author:xiaowei.han
Date:2016-9-11
Others:
Histroy:
*******************************************************************************/
#ifndef BASE_TAB_WND_H
#define BASE_TAB_WND_H

class CBaseTabWnd : public CBCGPTabWnd
{
	DECLARE_DYNCREATE(CBaseTabWnd)
public:
	CBaseTabWnd(CWnd* pParenWnd = NULL);
	~CBaseTabWnd(void);

	//����Tab�ĸ�����ָ��
	void SetTabParentWnd(CWnd* pParentWnd);

	//��ȡTab�ĸ�����ָ��
	CWnd* GetTabParentWnd(void) const;

protected:
	//������ָ��
	CWnd* m_pParentWnd;
public:
	//����TabWnd��ID����ַ
	static unsigned int s_nTabBaseID;
};


#endif