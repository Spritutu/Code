#pragma once
#include "AbstractAttrHanlder.h"
class CStrAttrHandler :
	public CAbstractAttrHanlder
{
public:
	CStrAttrHandler() =default;
	virtual ~CStrAttrHandler() = default;

public:
	//������
	virtual void WriteAttr(H5::DataSet& ElementDataSet, const Hdf5_Wrapper::DATA_ATTRIBUTE& AttributeElement) override;

	//д����
	virtual void WriteAttr(H5::Group& GroupNode, const Hdf5_Wrapper::DATA_ATTRIBUTE& AttributeElement) override;

	//������
	virtual void ReadAttr(H5::Attribute& Attr, H5::DataType& AttrDataType, std::vector<Hdf5_Wrapper::DATA_ATTRIBUTE>& AttributeArray) override;

};

