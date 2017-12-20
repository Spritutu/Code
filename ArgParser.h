/*********************************************************
Copyright(C):
FileName:ArgParser.h
Descripton:�������������������洢������
Author:xiaowei.han
Data:2017/12/19
Others:
History:
Version:1.0
*********************************************************/
#ifndef __ARG_PARSER_H__
#define __ARG_PARSER_H__
#include <map>
#include <vector>
#include <boost/program_options.hpp>

//��������
enum PARAM_TYPE
{
	//������
	COMMAND_NO_TYPE = 0,
	//����
	COMMAND_INT_TYPE,
	//��������
	COMMAND_FLOAT_TYPE,
	//�ַ�������
	COMMAND_STR_TYPE
};

//������Դ
enum PARAM_SOURCE
{
	//��������������
	COMMAND_SOURCE = 0,
	//���������ļ�
	CONFIG_FILE_SOURCE,
	//����������λ������
	POSITION_COMMAND_SOURCE

};

struct _command_info
{
	//������(�����Ͷ�����,�ָ�)
	std::string strCommand;
	//��������
	PARAM_TYPE eumType;
	//��������ʾ��Ϣ
	std::string strCommandPrompt;
	//������Դ
	PARAM_SOURCE eumSource;

	_command_info() = default;

	_command_info(const std::string& strCommand, PARAM_TYPE eumType, const std::string& strCommandPrompt, PARAM_SOURCE eumSource)
	{
		this->strCommand = strCommand;
		this->eumType = eumType;
		this->strCommandPrompt = strCommandPrompt;
		this->eumSource = eumSource;
	}

};
using COMMAND_INFO = _command_info;
using LP_COMMAND_INFO = _command_info*;


class CArgParser
{
public:
	CArgParser() = default;
	~CArgParser() = default;

public:
	//������������Ϣ
	void AddCommandInfo(const LP_COMMAND_INFO pCommandInfo);

	//����������
	void ParseCommandInfo(int nArgc,char* argv[]);

	//��ȡ�����������ֵ
	bool GetCommandValue(const std::string& strCommand, void* pValue);

	//���������ļ�·��(���������Դ�������ļ���������������ô�·��)
	void SetConfigPath(const std::string& strConfigPath);

	//��ʾ������Ϣ
	std::string DisplayHelpInfo(void);
private:
	//�Բ�����Ϣ���з���
	void SortParamInfo(std::vector<COMMAND_INFO>& CommandSourceArray, std::vector<COMMAND_INFO>& ConfigSourceArray, std::vector<COMMAND_INFO>& PositionCommandSourceArray);
private:
	//����Ĳ�����Ϣ
	std::vector<COMMAND_INFO> m_commandInfo;
	//�����ļ���·��
	std::string m_strConfigPath;
	//�����еĴ洢��
	boost::program_options::variables_map m_VarInfo;
};



#endif
