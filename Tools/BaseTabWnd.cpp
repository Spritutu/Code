/*******************************************************************************
Copyright(C):Envision. Co., Ltd.
FileName:BaseTabWnd.cpp
Description:TabWnd����
Author:xiaowei.han
Date:2016-9-11
Others:
Histroy:
*******************************************************************************/
#include "stdafx.h"
#include "BaseTabWnd.h"

IMPLEMENT_DYNCREATE(CBaseTabWnd,CBCGPTabWnd)
CBaseTabWnd::CBaseTabWnd( CWnd* pParenWnd ):
m_pParentWnd(pParenWnd)
{
	m_bAutoDestoyWindow = TRUE;
	m_bAutoSizeWindow = TRUE;
}

CBaseTabWnd::~CBaseTabWnd( void )
{

}

/*****************************************************************************
@FunctionName : ����Tab������ָ��
@FunctionDescription : ����Tab������ָ��
@inparam  : pParentWnd:������ָ��
@outparam :  
@return : 
*****************************************************************************/
void CBaseTabWnd::SetTabParentWnd( CWnd* pParentWnd )
{
	m_pParentWnd = pParentWnd;
}

/*****************************************************************************
@FunctionName : ��ȡTab������ָ��
@FunctionDescription : ��ȡTab������ָ��
@inparam  : 
@outparam :  
@return : Tab������ָ��
*****************************************************************************/
CWnd* CBaseTabWnd::GetTabParentWnd( void ) const
{
	return m_pParentWnd;
}

unsigned int CBaseTabWnd::s_nTabBaseID = 100;
