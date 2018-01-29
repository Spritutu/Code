// Hdf5_Wrapper.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Hdf5_Wrapper.h"
#include "H5_Wrapper.h"
#include "Log.h"
#include "Authenticate.h"
#include "ErrorCode.h"

/*********************************************************
FunctionName:Data2Hdf5
FunctionDesc:
InputParam:
OutputParam:
Return:0:�ɹ� ��0:������
Author:xiaowei.han
*********************************************************/
int Hdf5_Wrapper::Data2Hdf5(const char* szFilePath, const LP_HDF5_DATA pData)
{

	if (!CAuthentication::CreateInstance().AuthCall())
	{
		return ERROR_SIGNATURE_EXPIRED;
	}


	//�����Ϸ����ж�
	if (nullptr == szFilePath || nullptr == pData)
	{
		ERROR_LOG("the param is invalid.");
		return ERROR_PARAM_INVALID;
	}
	CH5Wrapper Wrapper;
	
	Wrapper.SetData(pData);
	Wrapper.SetFilePath(szFilePath);
	return Wrapper.WriteHdf5File();
}

/*********************************************************
FunctionName:Hdf52Data
FunctionDesc:��ȡHDF5���ݵ��ڴ�
InputParam:
OutputParam:
Return:0:�ɹ� ��0:������
Author:xiaowei.han
*********************************************************/
int Hdf5_Wrapper::Hdf52Data(const char* szFilePath, LP_HDF5_DATA* pData)
{

	if (!CAuthentication::CreateInstance().AuthCall())
	{
		return ERROR_SIGNATURE_EXPIRED;
	}

	//�����Ϸ����ж�
	if (nullptr == szFilePath || nullptr == pData)
	{
		ERROR_LOG("the param is invalid.");
		return ERROR_PARAM_INVALID;
	}
	CH5Wrapper Wrapper;
	Wrapper.SetFilePath(szFilePath);
	int nResult = Wrapper.ReadHdf5File();

	if (0 == nResult)
	{
		*pData = Wrapper.GetData();
	}

	return nResult;
}

/*********************************************************
FunctionName:RecursiveFreeData
FunctionDesc:
InputParam:
OutputParam:
Return:
Author:xiaowei.han
*********************************************************/
static void RecursiveFreeData(Hdf5_Wrapper::LP_HDF5_DATA pData)
{
	if (nullptr == pData)
	{
		return;
	}
	using namespace Hdf5_Wrapper;
	//�ͷ�attr����
	for (auto& AttrElement : pData->AttributeArray)
	{
		if (nullptr != AttrElement.pData)
		{
			delete[] AttrElement.pData;
			AttrElement.pData = nullptr;
		}
	}
	//û���ӽڵ���
	if (pData->SubDataArray.empty())
	{
		//�ͷ�DataSet������
		if (nullptr != pData->pData)
		{
			delete[]pData->pData;
			pData->pData = nullptr;
		}
	}
	else
	{
		//�����ӽڵ�
		for (auto& ElementData : pData->SubDataArray)
		{
			RecursiveFreeData(ElementData);
			//�ͷ��Լ�
			if (nullptr != ElementData)
			{
				delete ElementData;
				ElementData = nullptr;
			}
		}
		pData->SubDataArray.clear();
	}
}

/*********************************************************
FunctionName:RecyleData
FunctionDesc:�����ڴ�
InputParam:
OutputParam:
Return:0:�ɹ� ��0:������
Author:xiaowei.han
*********************************************************/
int Hdf5_Wrapper::RecyleData(LP_HDF5_DATA* pData)
{
	if (nullptr != pData)
	{
		RecursiveFreeData(*pData);

		if (nullptr != *pData)
		{
			delete *pData;
			*pData = nullptr;
		}
	}
	return ERROR_NO_ERROR;
}

