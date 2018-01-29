/*********************************************************
Copyright(C):
FileName:AbstractH5Strategy.h
Descripton:�������ģʽ
Author:xiaowei.han
Data:2018/01/29
Others:
History:
Version:1.0
*********************************************************/
#pragma once
#include "Type.h"
class CAbstractH5Strategy
{
public:
	CAbstractH5Strategy();
	virtual ~CAbstractH5Strategy();


public:
	//��ȡH5
	virtual int ReadH5() = 0;
	//д��h5
	virtual int WriteH5(InnerType::LP_HDF5_WRITE_DATA pData) = 0;
};

