/*********************************************************
Copyright(C):
FileName:FloatAttr.h
Descripton:�ַ������ԵĴ���
Author:xiaowei.han
Data:2018/01/29
Others:
History:
Version:1.0
*********************************************************/
#pragma once
#include "AbstractAttr.h"
class CFloatAttr :
	public CAbstractAttr
{
public:
	CFloatAttr();
	~CFloatAttr();

public:
	//������
	void WriteSelf(H5::DataSet& ElementDataSet) override;

	//д����
	void WriteSelf(H5::Group& GroupNode) override;
};

