#include "stdafx.h"
#pragma warning(disable:4251)
#include "StrAttrHandler.h"
#include <boost/smart_ptr.hpp>
#include "Utility.h"
#include "Log.h"

void CStrAttrHandler::WriteAttr(H5::DataSet& ElementDataSet, const Hdf5_Wrapper::DATA_ATTRIBUTE& AttributeElement)
{

#if 1
	using namespace H5;
	using namespace boost;

	if (AttributeElement.strAttrValueArray.empty())
	{
		return;
	}

	//���ֻ��һ��Ԫ��
	if (AttributeElement.strAttrValueArray.size() == 1)
	{
		auto nDataLen = AttributeElement.strAttrValueArray[0].length();
		//ָ������
		DataType ElementDataType(H5T_STRING, nDataLen);
		//ָ�����ݿռ�
		DataSpace AttrSpace(H5S_SCALAR);
		std::string strAttrKeyName = Utility::GB2312ToUTF8(AttributeElement.strKeyAttrName);
		Attribute ElementAttribute = ElementDataSet.createAttribute(strAttrKeyName, ElementDataType, AttrSpace/*, ElementPropList*/);
		//д������
		ElementAttribute.write(ElementDataType, AttributeElement.strAttrValueArray[0].c_str());
	}
	else
	{
		std::vector<std::string> ConvertResultArray;
		//�ַ���ת��ΪUTF-8
		for (auto& ElementData : AttributeElement.strAttrValueArray)
		{
			auto strConvertResult = Utility::GB2312ToUTF8(ElementData);
			ConvertResultArray.push_back(ElementData);
		}
		//�ҳ����ĳ��ȵ��ַ�������
		int nMaxLength = 0;
		for (auto& ElementData : ConvertResultArray)
		{
			if (ElementData.length() > nMaxLength)
			{
				nMaxLength = (int)ElementData.length();
			}
		}
		//��������Ҫд���ַ���
		int nStringDataSize = (int)ConvertResultArray.size();
		int nElementSize = nMaxLength;

		int nTotalSize = nStringDataSize * nElementSize;
		//�����ڴ�
		char* pContentData = new char[nTotalSize];

		if (nullptr != pContentData)
		{
			for (int i = 0; i < nStringDataSize; ++i)
			{
				memset(pContentData + (i * nElementSize), 0, nElementSize);
				memcpy(pContentData + (i * nElementSize), ConvertResultArray[i].c_str(), ConvertResultArray[i].length());
			}
		}
		//ָ������
		DataType ElementDataType(H5T_STRING, nElementSize);
		//�����ռ�
		hsize_t hStrTypeDims[1] = { 0 };
		hStrTypeDims[0] = nStringDataSize;
		DataSpace ElementDataSpace(1, hStrTypeDims);
		std::string strAttrKeyName = Utility::GB2312ToUTF8(AttributeElement.strKeyAttrName);
		Attribute ElementAttribute = ElementDataSet.createAttribute(strAttrKeyName, ElementDataType, ElementDataSpace/*, ElementPropList*/);
		//д������
		ElementAttribute.write(ElementDataType, pContentData);
		//�ͷ��ڴ�
		boost::checked_array_delete(pContentData);
	}
#else
	using namespace H5;
	StrType AttributeDataType(0, H5T_VARIABLE);
	DataSpace AttributeDataSpace(H5S_SCALAR);
	//��������
	//for (auto& AttributeElement : AttributeArray)
	{
		char* pValue = (char*)AttributeElement.pData;
		std::string strAttributeKeyName = Utility::GB2312ToUTF8(AttributeElement.strKeyAttrName);
		Attribute ElementAttribute = ElementDataSet.createAttribute(strAttributeKeyName, AttributeDataType, AttributeDataSpace);
		ElementAttribute.write(AttributeDataType, Utility::GB2312ToUTF8(pValue));
	}
#endif
}

void CStrAttrHandler::WriteAttr(H5::Group& GroupNode, const Hdf5_Wrapper::DATA_ATTRIBUTE& AttributeElement)
{
#if 1
	using namespace H5;
	using namespace boost;

	if (AttributeElement.strAttrValueArray.empty())
	{
		return;
	}

	//���ֻ��һ��Ԫ��
	if (AttributeElement.strAttrValueArray.size() == 1)
	{
		auto nDataLen = AttributeElement.strAttrValueArray[0].length();
		//ָ������
		DataType ElementDataType(H5T_STRING, nDataLen);
		//ָ�����ݿռ�
		DataSpace AttrSpace(H5S_SCALAR);
		//DSetCreatPropList ElementPropList;
		//hsize_t hChunkDims[1] = { 0 };
		//hChunkDims[0] = nDataLen;
		//ElementPropList.setChunk(1, hChunkDims);
		//ElementPropList.setDeflate(AttributeElement.nCompressLevel);
		std::string strAttrKeyName = Utility::GB2312ToUTF8(AttributeElement.strKeyAttrName);
		Attribute ElementAttribute = GroupNode.createAttribute(strAttrKeyName, ElementDataType, AttrSpace/*, ElementPropList*/);
		//д������
		ElementAttribute.write(ElementDataType, AttributeElement.strAttrValueArray[0].c_str());
	}
	else
	{
		std::vector<std::string> ConvertResultArray;
		//�ַ���ת��ΪUTF-8
		for (auto& ElementData : AttributeElement.strAttrValueArray)
		{
			auto strConvertResult = Utility::GB2312ToUTF8(ElementData);
			ConvertResultArray.push_back(ElementData);
		}
		//�ҳ����ĳ��ȵ��ַ�������
		int nMaxLength = 0;
		for (auto& ElementData : ConvertResultArray)
		{
			if (ElementData.length() > nMaxLength)
			{
				nMaxLength = (int)ElementData.length();
			}
		}
		//��������Ҫд���ַ���
		int nStringDataSize = (int)ConvertResultArray.size();
		int nElementSize = nMaxLength;

		int nTotalSize = nStringDataSize * nElementSize;
		//�����ڴ�
		char* pContentData = new char[nTotalSize];

		if (nullptr != pContentData)
		{
			for (int i = 0; i < nStringDataSize; ++i)
			{
				memset(pContentData + (i * nElementSize), 0, nElementSize);
				memcpy(pContentData + (i * nElementSize), ConvertResultArray[i].c_str(), ConvertResultArray[i].length());
			}
		}
		//ָ������
		DataType ElementDataType(H5T_STRING, nElementSize);
		//�����ռ�
		hsize_t hStrTypeDims[1] = { 0 };
		hStrTypeDims[0] = nStringDataSize;
		DataSpace ElementDataSpace(1, hStrTypeDims);
		//DSetCreatPropList ElementPropList;
		//hsize_t hChunkDims[1] = { 0 };
		//hChunkDims[0] = nStringDataSize;
		//ElementPropList.setChunk(1, hChunkDims);
		//ElementPropList.setDeflate(AttributeElement.nCompressLevel);
		std::string strAttrKeyName = Utility::GB2312ToUTF8(AttributeElement.strKeyAttrName);
		Attribute ElementAttribute = GroupNode.createAttribute(strAttrKeyName, ElementDataType, ElementDataSpace/*, ElementPropList*/);
		//д������
		ElementAttribute.write(ElementDataType, pContentData);
		//�ͷ��ڴ�
		boost::checked_array_delete(pContentData);
	}
#else
	using namespace H5;
	StrType AttributeDataType(0, H5T_VARIABLE);
	DataSpace AttributeDataSpace(H5S_SCALAR);
	//��������
	//for (auto& AttributeElement : AttributeArray)
	{
		std::string strAttributeKeyName = Utility::GB2312ToUTF8(AttributeElement.strKeyAttrName);
		Attribute ElementAttribute = GroupNode.createAttribute(strAttributeKeyName, AttributeDataType, AttributeDataSpace);
		ElementAttribute.write(AttributeDataType, AttributeElement.pData);
	}
#endif
}

void CStrAttrHandler::ReadAttr(H5::Attribute& Attr, H5::DataType& AttrDataType, std::vector<Hdf5_Wrapper::DATA_ATTRIBUTE>& AttributeArray)
{
	using namespace H5;
#if 1

	auto AttrDataSpace = Attr.getSpace();
	if (H5S_SCALAR == AttrDataSpace.getSimpleExtentType())
	{
		//��ȡ�ֽڳ���
		auto nAttrValueLen = Attr.getInMemDataSize();
		char* pData = new char[nAttrValueLen];
		if (nullptr != pData)
		{
			Attr.read(AttrDataType, pData);
			Hdf5_Wrapper::DATA_ATTRIBUTE DataAttribute;
			DataAttribute.strKeyAttrName = Utility::UTF8ToGB2312(Attr.getName());
			//DataAttribute.pData = pData;
			DataAttribute.Header.eumDataType = Hdf5_Wrapper::DATA_TYPE::STR_TYPE;
			DataAttribute.strAttrValueArray.push_back(std::string(pData, nAttrValueLen));
			AttributeArray.push_back(DataAttribute);
			delete[] pData;
			pData = nullptr;
		}
	}
	else if (H5S_SIMPLE == AttrDataSpace.getSimpleExtentType())
	{
		//��ȡ���г���
		auto nAttrValueLen = Attr.getInMemDataSize();
		char* pData = new char[nAttrValueLen];
		if (nullptr != pData)
		{
			Attr.read(AttrDataType, pData);
			Hdf5_Wrapper::DATA_ATTRIBUTE DataAttribute;
			DataAttribute.strKeyAttrName = Utility::UTF8ToGB2312(Attr.getName());
			//DataAttribute.pData = pData;
			DataAttribute.Header.eumDataType = Hdf5_Wrapper::DATA_TYPE::STR_TYPE;
			DataAttribute.strAttrValueArray.push_back(std::string(pData, nAttrValueLen));
			AttributeArray.push_back(DataAttribute);
			delete[] pData;
			pData = nullptr;
		}
	}
	else
	{
	}
	


#else
	//��ȡ�ֽ�
	auto nAttrValueLen = Attr.getInMemDataSize();
	auto AttrDataSpace = Attr.getSpace();
	if (H5S_SCALAR == AttrDataSpace.getSimpleExtentType())
	{
		char* pData = new char[nAttrValueLen];

		if (nullptr != pData)
		{
			Attr.read(AttrDataType, pData);
			Hdf5_Wrapper::DATA_ATTRIBUTE DataAttribute;
			DataAttribute.strKeyAttrName = Utility::UTF8ToGB2312(Attr.getName());
			DataAttribute.pData = pData;
			DataAttribute.Header.eumDataType = Hdf5_Wrapper::DATA_TYPE::STR_TYPE;
			AttributeArray.push_back(DataAttribute);
		}
	}
#endif
}
