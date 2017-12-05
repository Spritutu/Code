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
#include "ErrorCode.h"
#pragma comment(lib,"zlib.lib")
#pragma comment(lib,"szip.lib")
#pragma comment(lib,"hdf5.lib")
#pragma comment(lib,"hdf5_cpp.lib")

static void RecursiveWriteData(H5::Group& NodeGroup, Hdf5_Wrapper::LP_HDF5_DATA pData);

//�ݹ����hdf5�ڵ�
static void RecursiveVisitNode(H5::Group& Node, Hdf5_Wrapper::LP_HDF5_DATA pData);
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
		return -ERROR_PARAM_INVALID;
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
		return ERROR_WRITE_HDF5_FAILED;
	}

	return ERROR_NO_ERROR;
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
	using namespace H5;
	using namespace Hdf5_Wrapper;
	//�ж��ļ��Ƿ����
	try
	{
		using namespace boost::filesystem;

		if (!exists(m_strFilePath))
		{
			ERROR_LOG("the [%s] is not exits.", m_strFilePath.c_str());
			return ERROR_FILE_NOT_EXIST;
		}
	}
	catch (const boost::filesystem::filesystem_error& e)
	{
		ERROR_LOG("catch a exception [%s].", e.what());
		return ERROR_JUDGE_FILE_EXCEPTION;
	}

	//�ж��ļ��Ƿ���Hdf5��ʽ��
	if (!H5File::isHdf5(m_strFilePath.c_str()))
	{
		ERROR_LOG("the file [%s] is not hdf5 format.", m_strFilePath.c_str());
		return ERROR_FILE_FORMAT_INVALID;
	}

	try
	{
		Exception::dontPrint();
		H5File Reader(m_strFilePath, H5F_ACC_RDONLY);
		BOOST_SCOPE_EXIT(&Reader)
		{
			Reader.close();
		}BOOST_SCOPE_EXIT_END;

#if 0
		//�ݹ�д������
		int nGroupCount = (int)Reader.getNumObjs();
		NECESSARY_LOG("the group size is [%d]", nGroupCount);
		for (int i = 0; i < nGroupCount; ++i)
		{		
			NECESSARY_LOG("the node name is [%s],the type is [%d].", Reader.getObjnameByIdx(i).c_str(),Reader.getObjTypeByIdx(i));
		}
#endif
		m_pData = new HDF5_DATA;
		if (nullptr != m_pData)
		{
			RecursiveVisitNode(Reader,m_pData);
		}
	}
	catch (const Exception& e)
	{
		ERROR_LOG("ReadHdf5File raise a exception,the exception is [%s].", e.getDetailMsg().c_str());
		return ERROR_READ_HDF5_FAILED;
	}
	return ERROR_NO_ERROR;
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
FunctionName:FreeData
FunctionDesc:
InputParam:
OutputParam:
Return:
Author:xiaowei.han
*********************************************************/
void CH5Wrapper::FreeData(void)
{

	RecursiveFreeData(m_pData);
	m_pData = nullptr;
	
}


void CH5Wrapper::RecursiveFreeData(Hdf5_Wrapper::LP_HDF5_DATA pData)
{
	if (nullptr == pData)
	{
		return;
	}

	//û���ӽڵ���
	if (pData->SubDataArray.empty())
	{
		if (nullptr != pData->pData)
		{
			delete[] pData->pData;
			pData->pData = nullptr;
		}
		//�ͷ��Լ�
		delete pData;
		pData = nullptr;
		return;
	}

	//�����ӽڵ�
	for (auto& ElementData : pData->SubDataArray)
	{
		RecursiveFreeData(ElementData);
		//�ͷ��Լ�
		delete ElementData;
		ElementData = nullptr;
	}

	//������ɾ��
	delete pData;
	pData = nullptr;
}

/*********************************************************
FunctionName:RecursiveVisitNode
FunctionDesc:�ݹ鴴��Group
InputParam:
OutputParam:
Return:
Author:xiaowei.han
*********************************************************/
void RecursiveVisitNode(H5::Group& Node, Hdf5_Wrapper::LP_HDF5_DATA pData)
{
	if (nullptr == pData)
	{
		return;
	}
	//��ȡ�ڵ�������
	int nObjNum = static_cast<int>(Node.getNumObjs());
	if (nObjNum <= 0)
	{
		return;
	}
	//���ڵ�
	pData->strKeyName = Utility::UTF8ToGB2312(Node.getObjName());
	using namespace H5;
	//��ȡ���Ը���
	int nAttrNum = static_cast<int>(Node.getNumAttrs());
	for (int i = 0; i < nAttrNum; ++i)
	{
		auto childAttr = Node.openAttribute(i);
		//��ȡattr
		StrType AttributeDataType(0, H5T_VARIABLE);
		std::string strAttriValue;
		childAttr.read(AttributeDataType, strAttriValue);
		//NECESSARY_LOG("the name is [%s],the value is [%s].", childAttr.getName().c_str(), strAttriValue.c_str());
		Hdf5_Wrapper::DATA_ATTRIBUTE DataAttribute;
		DataAttribute.strKeyAttrName = Utility::UTF8ToGB2312(childAttr.getName());
		DataAttribute.strAttrValue = Utility::UTF8ToGB2312(strAttriValue);
		pData->AttributeArray.push_back(std::move(DataAttribute));
		childAttr.close();
	}
	for (int i = 0; i < nObjNum; ++i)
	{
		//NECESSARY_LOG("the node name is [%s],the type is [%d].", Node.getObjnameByIdx(i).c_str(), Node.getObjTypeByIdx(i));
		auto SubNodeType = Node.getObjTypeByIdx(i);
		auto strNodeName = Node.getObjnameByIdx(i);
		switch (SubNodeType)
		{
		case H5G_GROUP:
		{
			Hdf5_Wrapper::LP_HDF5_DATA pSubData = new Hdf5_Wrapper::HDF5_DATA;
			if (nullptr != pSubData)
			{
				pSubData->strKeyName = Utility::UTF8ToGB2312(strNodeName);
				//��ӽ�ȥ
				pData->SubDataArray.push_back(pSubData);
				auto ChildGroupNode = Node.openGroup(strNodeName);
				RecursiveVisitNode(ChildGroupNode,pSubData);
				ChildGroupNode.close();
			}
		}
		break;
		case H5G_DATASET:
		{
			auto childDataset = Node.openDataSet(Node.getObjnameByIdx(i));

			Hdf5_Wrapper::LP_HDF5_DATA pSubData = new Hdf5_Wrapper::HDF5_DATA;
			if (nullptr != pSubData)
			{
				pSubData->strKeyName = Utility::UTF8ToGB2312(strNodeName);
				//��ӽ�ȥ
				pData->SubDataArray.push_back(pSubData);
				//�ж���������
				boost::scoped_ptr<CAbstractDataTypeHandler> pHandlder(CDataTypeHandlerFactory::CreateDataTypeHandler(childDataset.getTypeClass()));
				if (pHandlder)
				{
					pHandlder->ParseDataSet(childDataset, pSubData);
				}
			}
		}
		break;
		default:
			break;
		}	
	}
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