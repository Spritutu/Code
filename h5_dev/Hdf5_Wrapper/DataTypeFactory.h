#ifndef __DATA_TYPE_FACTORY_H__
#define __DATA_TYPE_FACTORY_H__
#include <H5Cpp.h>
#include "Hdf5_Wrapper.h"

class CAbstractDataTypeHandler
{
public:
	CAbstractDataTypeHandler(void) = default;
	virtual ~CAbstractDataTypeHandler(void) = default;
	//д����
	virtual void WriteDataSet(H5::Group& NodeGroup, Hdf5_Wrapper::LP_HDF5_DATA pData) = 0;
	//������
	virtual void ReadDataSet(H5::DataSet& NodeDataSet, Hdf5_Wrapper::LP_HDF5_DATA pData) = 0;
protected:
	//дDataset����
	void WriteAttribute(H5::DataSet& ElementDataSet, const std::vector<Hdf5_Wrapper::DATA_ATTRIBUTE>& AttributeArray);
	//����Dataset����
	void ReadAttribute(H5::DataSet& ElementDataSet, std::vector<Hdf5_Wrapper::DATA_ATTRIBUTE>& AttributeArray);
	//����ѹ������
	void ParseCompressProperty(H5::DataSet& ElementDataSet, int& nCompressLevel);
protected:
	//��������ռ�õ��ֽ���
	unsigned int m_nDataBytes;
};

//������
class CFloatDataTypeHandler : public CAbstractDataTypeHandler
{
public:
	CFloatDataTypeHandler(unsigned int nDataBytes)
	{
		m_nDataBytes = nDataBytes;
	}
	~CFloatDataTypeHandler() = default;

	void WriteDataSet(H5::Group& NodeGroup, Hdf5_Wrapper::LP_HDF5_DATA pData) override;

	//����DataSet
	void ReadDataSet(H5::DataSet& NodeDataSet, Hdf5_Wrapper::LP_HDF5_DATA pData) override;
};

#if 0
//����˫����
class CDoubleDataTypeHandler : public CAbstractDataTypeHandler
{
public:
	CDoubleDataTypeHandler() = default;
	~CDoubleDataTypeHandler() = default;

	void HandleDataSet(H5::Group& NodeGroup, Hdf5_Wrapper::LP_HDF5_DATA pData) override;

	//����DataSet
	void ParseDataSet(H5::DataSet& NodeDataSet, Hdf5_Wrapper::LP_HDF5_DATA pData) override;
};

//���������
class CShortDataTypeHandler : public CAbstractDataTypeHandler
{
public:
	CShortDataTypeHandler() = default;
	~CShortDataTypeHandler() = default;

	void HandleDataSet(H5::Group& NodeGroup, Hdf5_Wrapper::LP_HDF5_DATA pData) override;

	//����DataSet
	void ParseDataSet(H5::DataSet& NodeDataSet, Hdf5_Wrapper::LP_HDF5_DATA pData) override;
};

//��������
class CLongDataTypeHandler : public CAbstractDataTypeHandler
{
public:
	CLongDataTypeHandler() = default;
	~CLongDataTypeHandler() = default;

	void HandleDataSet(H5::Group& NodeGroup, Hdf5_Wrapper::LP_HDF5_DATA pData) override;

	//����DataSet
	void ParseDataSet(H5::DataSet& NodeDataSet, Hdf5_Wrapper::LP_HDF5_DATA pData) override;
};

//�����޷�������
class CUnsignedIntDataTypeHandler : public CAbstractDataTypeHandler
{
public:
	CUnsignedIntDataTypeHandler() = default;
	~CUnsignedIntDataTypeHandler() = default;

	void HandleDataSet(H5::Group& NodeGroup, Hdf5_Wrapper::LP_HDF5_DATA pData) override;

	//����DataSet
	void ParseDataSet(H5::DataSet& NodeDataSet, Hdf5_Wrapper::LP_HDF5_DATA pData) override;
};

//�����޷�������
class CUnsignedShortDataTypeHandler : public CAbstractDataTypeHandler
{
public:
	CUnsignedShortDataTypeHandler() = default;
	~CUnsignedShortDataTypeHandler() = default;

	void HandleDataSet(H5::Group& NodeGroup, Hdf5_Wrapper::LP_HDF5_DATA pData) override;

	//����DataSet
	void ParseDataSet(H5::DataSet& NodeDataSet, Hdf5_Wrapper::LP_HDF5_DATA pData) override;
};

//�����޷��ų�����
class CUnsignedLongDataTypeHandler : public CAbstractDataTypeHandler
{
public:
	CUnsignedLongDataTypeHandler() = default;
	~CUnsignedLongDataTypeHandler() = default;

	void HandleDataSet(H5::Group& NodeGroup, Hdf5_Wrapper::LP_HDF5_DATA pData) override;

	//����DataSet
	void ParseDataSet(H5::DataSet& NodeDataSet, Hdf5_Wrapper::LP_HDF5_DATA pData) override;
};

//�����޷�������
class CUnsignedLongLongDataTypeHandler : public CAbstractDataTypeHandler
{
public:
	CUnsignedLongLongDataTypeHandler() = default;
	~CUnsignedLongLongDataTypeHandler() = default;

	void HandleDataSet(H5::Group& NodeGroup, Hdf5_Wrapper::LP_HDF5_DATA pData) override;

	//����DataSet
	void ParseDataSet(H5::DataSet& NodeDataSet, Hdf5_Wrapper::LP_HDF5_DATA pData) override;
};

//�����޷�������
class CLongLongDataTypeHandler : public CAbstractDataTypeHandler
{
public:
	CLongLongDataTypeHandler() = default;
	~CLongLongDataTypeHandler() = default;

	void HandleDataSet(H5::Group& NodeGroup, Hdf5_Wrapper::LP_HDF5_DATA pData) override;

	//����DataSet
	void ParseDataSet(H5::DataSet& NodeDataSet, Hdf5_Wrapper::LP_HDF5_DATA pData) override;
};
#endif

//��������
class CIntDataTypeHandler : public CAbstractDataTypeHandler
{
public:
	CIntDataTypeHandler(unsigned int nDataBytes)
	{
		m_nDataBytes = nDataBytes;
	}
	~CIntDataTypeHandler() = default;

	void WriteDataSet(H5::Group& NodeGroup, Hdf5_Wrapper::LP_HDF5_DATA pData) override;

	//����DataSet
	void ReadDataSet(H5::DataSet& NodeDataSet, Hdf5_Wrapper::LP_HDF5_DATA pData) override;
};

class CStrDataTypeHandler : public CAbstractDataTypeHandler
{
public:
	CStrDataTypeHandler(unsigned int nDataBytes)
	{
		m_nDataBytes = nDataBytes;
	}
	~CStrDataTypeHandler() = default;

	void WriteDataSet(H5::Group& NodeGroup, Hdf5_Wrapper::LP_HDF5_DATA pData) override;

	//����DataSet
	void ReadDataSet(H5::DataSet& NodeDataSet, Hdf5_Wrapper::LP_HDF5_DATA pData) override;
};


class CDataTypeHandlerFactory
{
public:
	CDataTypeHandlerFactory() = default;
	~CDataTypeHandlerFactory() = default;

	static CAbstractDataTypeHandler* CreateDataTypeHandler(Hdf5_Wrapper::DATA_TYPE eumDataType,unsigned int nDataBytes);

	static CAbstractDataTypeHandler* CreateDataTypeHandler(int nHdf5DataType, unsigned int nDataBytes);
};
#endif
