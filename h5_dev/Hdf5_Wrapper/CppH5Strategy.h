/*********************************************************
Copyright(C):
FileName:CPPH5Strategy.h
Descripton:C++ģʽ����h5�㷨
Author:xiaowei.han
Data:2018/01/29
Others:
History:
Version:1.0
*********************************************************/
#pragma once
#include "AbstractH5Strategy.h"
class CCppH5Strategy :
	public CAbstractH5Strategy
{
public:
	CCppH5Strategy();
	~CCppH5Strategy();

public:
	//��ȡH5
	int ReadH5() override;
	//д��h5
	int WriteH5(InnerType::LP_HDF5_WRITE_DATA pData) override;
};

