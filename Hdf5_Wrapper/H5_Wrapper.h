/*********************************************************
Copyright(C):
FileName:H5_Wrapper.h
Descripton:HDF5 ��װ
Author:xiaowei.han
Data:2017/11/28
Others:
History:
Version:1.0
*********************************************************/
#ifndef __H5_WRAPPER_H__
#define __H5_WRAPPER_H__
#include "Hdf5_Wrapper.h"
class CH5Wrapper
{
public:
	CH5Wrapper() = default;
	~CH5Wrapper() = default;
public:
	//дHdf5�ļ�
	int WriteHdf5File(void);
	//��ȡhdf5�ļ�
	int ReadHdf5File(void);
	//����Ҫд������
	void SetData(Hdf5_Wrapper::LP_HDF5_DATA pData);
	//�����ļ�·��
	void SetFilePath(const std::string& strFilePath);
private:
	//��д������
	Hdf5_Wrapper::LP_HDF5_DATA m_pData = nullptr;
	//HDF5�ļ����ڵ�·��
	std::string m_strFilePath;
};

#endif
