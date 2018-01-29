/*********************************************************
Copyright(C):
FileName:H5GroupNode.h
Descripton:��ڵ���
Author:xiaowei.han
Data:2018/01/29
Others:
History:
Version:1.0
*********************************************************/
#ifndef H5_GROUP_NODE_H
#define H5_GROUP_NODE_H
#include "H5AbstractNode.h"
class CH5GroupNode : public CH5AbstractNode
{
public:
	CH5GroupNode() = default;
	~CH5GroupNode() = default;
public:

	//����ӽڵ�
	void AppendChild(CH5AbstractNode* pChildNode) override;

	//�Ƴ��ӽڵ�
	void RemoveChild(CH5AbstractNode* pChildNode) override;

	//��ȡ�ڵ����
	unsigned int GetChildNum(void) override;

	//��������
	int CreateSelfToFile(H5::H5File& H5Root) override;
};
#endif

