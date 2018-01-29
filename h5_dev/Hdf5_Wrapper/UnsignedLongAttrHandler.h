#pragma once
#include "AbstractAttrHanlder.h"
class CUnsignedLongAttrHandler :
	public CAbstractAttrHanlder
{
public:
	CUnsignedLongAttrHandler() = default;
	~CUnsignedLongAttrHandler() = default;

public:
	//������
	virtual void WriteAttr(H5::DataSet& ElementDataSet, const Hdf5_Wrapper::DATA_ATTRIBUTE& AttributeElement);

	//д����
	virtual void WriteAttr(H5::Group& GroupNode, const Hdf5_Wrapper::DATA_ATTRIBUTE& AttributeElement);

	//������
	virtual void ReadAttr(H5::Attribute& Attr, H5::DataType& AttrDataType, std::vector<Hdf5_Wrapper::DATA_ATTRIBUTE>& AttributeArray);
};

