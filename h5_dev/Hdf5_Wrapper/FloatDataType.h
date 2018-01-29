#pragma once
#include "AbstractDataType.h"
class CFloatDataType :
	public CAbstractDataType
{
public:
	CFloatDataType(unsigned int nDataByte);
	~CFloatDataType();

public:
	std::string GetDataTypeName() override;

	H5::DataType* CreateProperType() override;

private:
	//����ռ�õ��ֽ���
	unsigned int m_nDataBytes = 4;
};

