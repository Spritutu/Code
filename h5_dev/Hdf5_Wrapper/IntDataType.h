#pragma once
#include "AbstractDataType.h"
class CIntDataType :
	public CAbstractDataType
{
public:
	CIntDataType(unsigned int nDataBytes,bool bSign);
	~CIntDataType();


public:
	std::string GetDataTypeName() override;

	H5::DataType* CreateProperType() override;


private:
	//����ռ�õ��ֽ���
	unsigned int m_nDataBytes = 4;
	bool m_bSign = true;
};

