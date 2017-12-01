/*********************************************************
Copyright(C):
FileName:H5_Wrapper.cpp
Descripton:HDF5 ��װ
Author:xiaowei.han
Data:2017/11/28
Others:
History:
Version:1.0
*********************************************************/
#include "stdafx.h"
#pragma warning(disable:4251)
#include "H5_Wrapper.h"
#include <H5Cpp.h>
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/core/ignore_unused.hpp>
#include <boost/scope_exit.hpp>
#include <boost/checked_delete.hpp>
#include <boost/smart_ptr.hpp>
#include "Log.h"
#include "Utility.h"
#include "DataTypeFactory.h"
#pragma comment(lib,"zlib.lib")
#pragma comment(lib,"szip.lib")
#pragma comment(lib,"hdf5.lib")
#pragma comment(lib,"hdf5_cpp.lib")

static void RecursiveWriteData(H5::Group& NodeGroup, Hdf5_Wrapper::LP_HDF5_DATA pData);

/*********************************************************
FunctionName:WriteHdf5File
FunctionDesc:������д��HDF5 �ļ�
InputParam:
OutputParam:
Return:
Author:xiaowei.han
*********************************************************/
int CH5Wrapper::WriteHdf5File(void)
{
	using namespace H5;
	//�����Ϸ����ж�
	if (nullptr == m_pData || m_strFilePath.empty())
	{
		ERROR_LOG("the param is invalid.");
		return -1;
	}
	try
	{
		Exception::dontPrint();
		H5File Writer(m_strFilePath, H5F_ACC_TRUNC);
		BOOST_SCOPE_EXIT(&Writer)
		{
			Writer.close();
		}BOOST_SCOPE_EXIT_END;	
		//�ݹ�д������
		RecursiveWriteData(Writer, m_pData);
		Writer.flush(H5F_SCOPE_GLOBAL);
	}
	catch (const Exception& e)
	{
		ERROR_LOG("WriteHdf5File raise a exception,the exception is [%s].", e.getDetailMsg().c_str());
		return -1;
	}

	return 0;
}

/*********************************************************
FunctionName:ReadHdf5File
FunctionDesc:
InputParam:
OutputParam:
Return:
Author:xiaowei.han
*********************************************************/
int CH5Wrapper::ReadHdf5File(void)
{
	try
	{
		using namespace boost::filesystem;

		if (!exists(m_strFilePath))
		{
			ERROR_LOG("the [%s] is not exits.", m_strFilePath.c_str());
			return -1;
		}
	}
	catch (const boost::filesystem::filesystem_error& e)
	{
		ERROR_LOG("catch a exception [%s].", e.what());
		return -1;
	}
	return 0;
}

/*********************************************************
FunctionName:SetData
FunctionDesc:
InputParam:
OutputParam:
Return:
Author:xiaowei.han
*********************************************************/
void CH5Wrapper::SetData(Hdf5_Wrapper::LP_HDF5_DATA pData)
{
	m_pData = pData;
}

/*********************************************************
FunctionName:SetFilePath
FunctionDesc:
InputParam:
OutputParam:
Return:
Author:xiaowei.han
*********************************************************/
void CH5Wrapper::SetFilePath(const std::string& strFilePath)
{
	m_strFilePath = strFilePath;
}

/*********************************************************
FunctionName:RecursiveWriteData
FunctionDesc:�ݹ鴴��Group
InputParam:
OutputParam:
Return:
Author:xiaowei.han
*********************************************************/
void RecursiveWriteData(H5::Group& NodeGroup, Hdf5_Wrapper::LP_HDF5_DATA pData)
{
	using namespace H5;
	//�����Ϸ����ж�
	if (nullptr == pData)
	{
		return;
	}

	//��������ӽڵ�
	if (pData->SubDataArray.empty())
	{
		//�����Ϸ����ж�
		{
			//�ж���������
			boost::scoped_ptr<CAbstractDataTypeHandler> pHandlder(CDataTypeHandlerFactory::CreateDataTypeHandler(pData->Header.eumDataType));

			if (pHandlder)
			{
				pHandlder->HandleDataSet(NodeGroup, pData);
			}
		}

	}
	//������ӽڵ�
	else
	{
		//����һ��Group
		std::string strGroupKeyName = Utility::GB2312ToUTF8(pData->strKeyName);
		auto ChildGroupNode = NodeGroup.createGroup(strGroupKeyName);
		StrType AttributeDataType(0, H5T_VARIABLE);
		DataSpace AttributeDataSpace(H5S_SCALAR);
		//��������
		for (auto& AttributeElement : pData->AttributeArray)
		{
			std::string strAttributeKeyName = Utility::GB2312ToUTF8(AttributeElement.strKeyAttrName);
			Attribute ElementAttribute = ChildGroupNode.createAttribute(strAttributeKeyName, AttributeDataType, AttributeDataSpace);
			ElementAttribute.write(AttributeDataType, Utility::GB2312ToUTF8(AttributeElement.strAttrValue));
		}
		for (auto& SubGroupElement : pData->SubDataArray)
		{
			RecursiveWriteData(ChildGroupNode, SubGroupElement);
		}
	}
}