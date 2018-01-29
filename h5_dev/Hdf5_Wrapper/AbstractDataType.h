#pragma once
#include <string>
#include <H5Cpp.h>
class CAbstractDataType
{
public:
	CAbstractDataType();
	virtual ~CAbstractDataType();

public:
	virtual std::string GetDataTypeName() = 0;

	//������ȷ������
	virtual H5::DataType* CreateProperType() = 0;

};

