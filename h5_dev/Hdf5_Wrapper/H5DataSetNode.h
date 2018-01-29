/*********************************************************
Copyright(C):
FileName:H5DataSetNode.h
Descripton:���ģʽҶ�ӽڵ����
Author:xiaowei.han
Data:2018/01/29
Others:
History:
Version:1.0
*********************************************************/
#ifndef H5_DATA_SET_NODE_H
#define H5_DATA_SET_NODE_H
#include "H5AbstractNode.h"
class CH5DataSetNode :
	public CH5AbstractNode
{
public:
	CH5DataSetNode() = default;
	~CH5DataSetNode() =default;

public:
	//��ȡ�ڵ����
	unsigned int GetChildNum(void) override;

	//��������
	int CreateSelfToFile(H5::H5File& H5Root) override;
};

#endif