#ifndef __HDF5_WRAPPER_H__
#define __HDF5_WRAPPER_H__
#include <vector>
#include <string>
namespace Hdf5_Wrapper
{
	//Ҫ�洢����������
	enum class DATA_TYPE
	{
		//��������
		FLOAT_TYPE = 1,
		//����
		INT_TYPE,
		//�ַ�������
		STR_TYPE
	};

	//��������ͷ
	struct _data_header
	{
		//ά��
		int nRank;
		//ά����Ϣ
		std::vector<int> DimensionArray;
		//��������
		DATA_TYPE eumDataType;
		//��������ռ�õ��ֽ���
		unsigned int nDataByte;

		_data_header()
		{
			nDataByte = 0;
			nRank = 0;
			DimensionArray.clear();
			eumDataType = DATA_TYPE::INT_TYPE;
		}

		void Reset()
		{
			nRank = 0;
			DimensionArray.clear();
			eumDataType = DATA_TYPE::INT_TYPE;
		}
	};

	using DATA_HEADER = _data_header;
	using LP_DATA_HEADER = _data_header*;

	//��������ͷ
	struct _data_attribute
	{
		std::string strKeyAttrName;
		//����ͷ
		DATA_HEADER Header;
		//����
		void* pData;
		//�ַ�����Ϣ
		std::vector<std::string> strAttrValueArray;
		_data_attribute()
		{
			pData = nullptr;
		}
	};
	using DATA_ATTRIBUTE = _data_attribute;
	using LP_DATA_ATTRIBUTE = _data_attribute;

	//���ݶ���(�ⲿ�����ͷ��ڴ�)
	struct _hdf5_data
	{
		//hash���е�key
		std::string strKeyName;
		//��������
		std::vector<DATA_ATTRIBUTE> AttributeArray;
		//����ͷ
		DATA_HEADER Header;
		//�ַ�����Ϣ
		std::vector<std::string> stringData;
		//������Ϣ
		void* pData;
		//ѹ����
		int nCompressLevel;
		//����Ϣ
		std::vector<_hdf5_data*> SubDataArray;

		_hdf5_data()
		{
			pData = nullptr;
			SubDataArray.clear();
			nCompressLevel = 4;
			stringData.clear();
		}

		void Reset()
		{
			pData = nullptr;
			SubDataArray.clear();
			Header.Reset();
			AttributeArray.clear();
			strKeyName.clear();
			stringData.clear();
		}

	};

	using HDF5_DATA = _hdf5_data;
	using LP_HDF5_DATA = _hdf5_data*;


	//�ڴ�����->HDF5�ļ�
	int Data2Hdf5(const char* szFilePath,const LP_HDF5_DATA pData);

	//HDF5->�ڴ�����
	int Hdf52Data(const char* szFilePath, LP_HDF5_DATA* pData);

	//�����ڴ�
	int RecyleData(LP_HDF5_DATA* pData);

}





#endif
