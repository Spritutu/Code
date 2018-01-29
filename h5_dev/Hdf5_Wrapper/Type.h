/*********************************************************
Copyright(C):
FileName:Type.h
Descripton:�ڲ����Ͷ���
Author:xiaowei.han
Data:2018/01/26
Others:
History:
Version:1.0
*********************************************************/
#ifndef TYPE_H
#define TYPE_H
#include <vector>
#include "Utility.h"
namespace InnerType
{

	//Ҫ�洢����������
	enum class DATA_TYPE
	{
		NO_TYPE = 0,
		//��������
		FLOAT_TYPE = 1,
		//����
		INT_TYPE,
		//�ַ�������
		STR_TYPE,
		//��������
		COMPOSE_TYPE
	};

	//��������ͷ
	struct _data_header
	{
		//ά��
		int nRank;
		//ά����Ϣ
		int* pDimensionArray;
		//��������
		DATA_TYPE eumDataType;
		//��������ռ�õ��ֽ���
		unsigned int nDataByte;
		//�Ƿ������ ֻ�������
		bool bSign;

		_data_header()
		{
			nDataByte = 0;
			nRank = 0;
			pDimensionArray = nullptr;
			eumDataType = DATA_TYPE::NO_TYPE;
			bSign = true;
		}

		//�ƶ����캯��
		_data_header(_data_header&& CopyValue)
		{
			nRank = CopyValue.nRank;
			pDimensionArray = CopyValue.pDimensionArray;
			eumDataType = CopyValue.eumDataType;
			nDataByte = CopyValue.nDataByte;
			bSign = CopyValue.bSign;
			CopyValue.pDimensionArray = nullptr;
			
		}
		_data_header& operator=(_data_header&& CopyValue)
		{
			if (this == &CopyValue)
			{
				return *this;
			}
			nRank = CopyValue.nRank;
			pDimensionArray = CopyValue.pDimensionArray;
			eumDataType = CopyValue.eumDataType;
			nDataByte = CopyValue.nDataByte;
			bSign = CopyValue.bSign;
			CopyValue.pDimensionArray = nullptr;
			return *this;
		}

		~_data_header()
		{
			DELETE_ARRAY_POINTER(pDimensionArray);
		}

	};

	using DATA_HEADER = _data_header;
	using LP_DATA_HEADER = _data_header*;

	//��������
	struct _data_attribute
	{
		std::string strKeyAttrName;
		//����ͷ
		DATA_HEADER Header;
		//����
		void* pData;
		//�ַ�����Ϣ
		std::string strAttrValue;

		_data_attribute()
		{
			pData = nullptr;
		}

		_data_attribute(_data_attribute&& CopyValue)
		{
			strKeyAttrName = CopyValue.strKeyAttrName;
			Header = std::move(CopyValue.Header);
			pData = CopyValue.pData;
			CopyValue.pData = nullptr;
		}

		_data_attribute& operator=(_data_attribute&& CopyValue)
		{
			if (this == &CopyValue)
			{
				return *this;
			}
			strKeyAttrName = CopyValue.strKeyAttrName;
			Header = std::move(CopyValue.Header);
			pData = CopyValue.pData;
			CopyValue.pData = nullptr;
			return *this;
		}
		~_data_attribute()
		{
			DELETE_ARRAY_POINTER(pData);
		}

	};
	using DATA_ATTRIBUTE = _data_attribute;
	using LP_DATA_ATTRIBUTE = _data_attribute;


	//���ݶ���(�ⲿ�����ͷ��ڴ�)
	struct _hdf5_write_data
	{
		//hash���е�key
		std::string strKeyName;
		//��������
		std::vector<DATA_ATTRIBUTE> AttributeArray;
		//����ͷ
		DATA_HEADER Header;
		//������Ϣ
		void* pData;
		//ѹ����
		int nCompressLevel;
		//����Ϣ
		std::vector<_hdf5_write_data*> SubDataArray;

		_hdf5_write_data()
		{
			pData = nullptr;
			SubDataArray.clear();
			nCompressLevel = -1;
			AttributeArray.clear();
		}

		_hdf5_write_data(_hdf5_write_data&& CopyValue)
		{
			strKeyName = CopyValue.strKeyName;
			AttributeArray = std::move(CopyValue.AttributeArray);
			Header = std::move(Header);
			pData = CopyValue.pData;
			CopyValue.pData = nullptr;
			nCompressLevel = CopyValue.nCompressLevel;
			SubDataArray.swap(CopyValue.SubDataArray);
		}

		_hdf5_write_data& operator=(_hdf5_write_data&& CopyValue)
		{
			if (this == &CopyValue)
			{
				return *this;
			}

			strKeyName = CopyValue.strKeyName;
			AttributeArray = std::move(CopyValue.AttributeArray);
			Header = std::move(Header);
			pData = CopyValue.pData;
			CopyValue.pData = nullptr;
			nCompressLevel = CopyValue.nCompressLevel;
			SubDataArray.swap(CopyValue.SubDataArray);
			return *this;
		}

		~_hdf5_write_data()
		{
			DELETE_ARRAY_POINTER(pData);

			for (auto& SubElement : SubDataArray)
			{
				DELETE_POINTER(SubElement);
			}
		}

	};

	using HDF5_WRITE_DATA = _hdf5_write_data;
	using LP_HDF5_WRITE_DATA = _hdf5_write_data*;

}

#endif

