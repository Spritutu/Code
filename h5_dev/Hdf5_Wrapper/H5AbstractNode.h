/*********************************************************
Copyright(C):
FileName:H5AbstractNode.h
Descripton:���ģʽ����
Author:xiaowei.han
Data:2018/01/26
Others:
History:
Version:1.0
*********************************************************/
#ifndef H5_ABSTRACT_NODE_H
#define H5_ABSTRACT_NODE_H
#include <string>
#include <list>
#include <H5Cpp.h>
class CAbstractAttr;

class CH5AbstractNode
{
public:
	CH5AbstractNode(const std::string& strName) :m_strName(strName)
	{

	}
	virtual ~CH5AbstractNode() = default;


public:
	//��ȡ����
	std::string GetName(void)
	{
		return m_strName;
	}

	//��������
	void SetName(const std::string& strName)
	{
		m_strName = strName;
	}

	//��ȡ��������
	std::string GetAbsoluteName(void);

	//���ø��ڵ�
	void SetParentNode(CH5AbstractNode* pParentNode)
	{
		m_pParent = pParentNode;
	}

	CH5AbstractNode* GetParentNode(void)
	{
		return m_pParent;
	}

	//��ȡ���Ը���
	unsigned int GetAttrNum();

	//����ӽڵ�
	virtual void AppendChild(CH5AbstractNode* pChildNode){}

	//�Ƴ��ӽڵ�
	virtual void RemoveChild(CH5AbstractNode* pChildNode){}

	//��ȡ�ڵ����
	virtual unsigned int GetChildNum(void) = 0;

	//��������
	virtual int CreateSelfToFile(H5::H5File& H5Root) = 0;
protected:
	//�ڵ�����
	std::string m_strName;
	//�ӽڵ�
	std::list<CH5AbstractNode*> m_ChildList;
	//���ڵ���Ϣ
	CH5AbstractNode* m_pParent = nullptr;
	//������Ϣ
	std::list<CAbstractAttr*> m_AttrList;
};

#endif