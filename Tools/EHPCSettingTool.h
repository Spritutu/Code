
// EHPCSettingTool.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CEHPCSettingToolApp: 
// �йش����ʵ�֣������ EHPCSettingTool.cpp
//

class CEHPCSettingToolApp : public CBCGPWinApp
{
public:
	CEHPCSettingToolApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CEHPCSettingToolApp theApp;