/*********************************************************
Copyright(C):
FileName:H5Contex.cpp
Descripton:���ڽ���h5�ļ���ִ��������
Author:xiaowei.han
Data:2018/01/29
Others:
History:
Version:1.0
*********************************************************/
#include "stdafx.h"
#include "H5Contex.h"
#include "AbstractH5Strategy.h"
#include "ErrorCode.h"

/*********************************************************
FunctionName:SetH5Strategy
FunctionDesc:����ִ���㷨
InputParam:
OutputParam:
Return:
Author:xiaowei.han
*********************************************************/
void CH5Contex::SetH5Strategy(CAbstractH5Strategy* pHandler)
{
	m_pStrategyHandler = pHandler;
}

/*********************************************************
FunctionName:ReadH5
FunctionDesc:��ȡhdf5�ļ�
InputParam:
OutputParam:
Return:
Author:xiaowei.han
*********************************************************/
int CH5Contex::ReadH5()
{
	if (nullptr == m_pStrategyHandler)
	{
		return ERROR_PARAM_INVALID;
	}

	return m_pStrategyHandler->ReadH5();
}

/*********************************************************
FunctionName:WriteH5
FunctionDesc:дhdf5�ļ�
InputParam:
OutputParam:
Return:
Author:xiaowei.han
*********************************************************/
int CH5Contex::WriteH5(InnerType::LP_HDF5_WRITE_DATA pData)
{
	if (nullptr == m_pStrategyHandler)
	{
		return ERROR_PARAM_INVALID;
	}

	return m_pStrategyHandler->WriteH5(pData);
}
