/*********************************************************
Copyright(C):
FileName:ArgParser.cpp
Descripton:�������������������洢������
Author:xiaowei.han
Data:2017/12/19
Others:
History:
Version:1.0
*********************************************************/
#include "stdafx.h"
#include "ArgParser.h"
#include <sstream>
#include <algorithm>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>

/*********************************************************
FunctionName:AddCommandInfo
FunctionDesc:�����������ʾ
InputParam:
OutputParam:
Return:
Author:xiaowei.han
*********************************************************/
void CArgParser::AddCommandInfo(const LP_COMMAND_INFO pCommandInfo)
{
	if (nullptr == pCommandInfo)
	{
		return;
	}
	m_commandInfo.emplace_back(pCommandInfo->strCommand, pCommandInfo->eumType, pCommandInfo->strCommandPrompt,pCommandInfo->eumSource);
}

/*********************************************************
FunctionName:ParseCommandInfo
FunctionDesc:
InputParam:
OutputParam:
Return:
Author:xiaowei.han
*********************************************************/
void CArgParser::ParseCommandInfo(int nArgc, char* argv[])
{
	//�����Ϸ����ж�
	if (nArgc <= 0 || nullptr == argv || m_commandInfo.empty())
	{
		return;
	}
	using namespace std;
	using namespace boost::program_options;
	//��Դ�������еĲ�����Ϣ
	vector<COMMAND_INFO> CommandSourceArray;
	//��Դ��������λ����Ϣ�Ĳ�����Ϣ
	vector<COMMAND_INFO> PositionCommandSourceArray;
	//��Դ�������ļ��Ĳ�����Ϣ
	vector<COMMAND_INFO> ConfigSourceArray;
	//���з���
	SortParamInfo(CommandSourceArray, ConfigSourceArray, PositionCommandSourceArray);

	if (!CommandSourceArray.empty())
	{
		//����������
		options_description Opt("commands usage.");
		for (auto& V : CommandSourceArray)
		{
			switch (V.eumType)
			{
			case COMMAND_NO_TYPE:
				Opt.add_options()(V.strCommand.c_str(),V.strCommandPrompt.c_str());
				break;
			case COMMAND_INT_TYPE:
				Opt.add_options()(V.strCommand.c_str(), value<int>(), V.strCommandPrompt.c_str());
				break;
			case COMMAND_FLOAT_TYPE:
				Opt.add_options()(V.strCommand.c_str(), value<double>(), V.strCommandPrompt.c_str());
				break;
			case COMMAND_STR_TYPE:
				Opt.add_options()(V.strCommand.c_str(), value<string>(), V.strCommandPrompt.c_str());
				break;
			default:
				break;
			}
		}

		if (!PositionCommandSourceArray.empty())
		{
			positional_options_description PositionOpt;

			for (int i = 0; i < (int)PositionCommandSourceArray.size(); ++i)
			{
				//��ǰע��
				switch (PositionCommandSourceArray[i].eumType)
				{
				case COMMAND_INT_TYPE:
					Opt.add_options()(PositionCommandSourceArray[i].strCommand.c_str(), value<int>(), PositionCommandSourceArray[i].strCommandPrompt.c_str());
					break;
				case COMMAND_FLOAT_TYPE:
					Opt.add_options()(PositionCommandSourceArray[i].strCommand.c_str(), value<double>(), PositionCommandSourceArray[i].strCommandPrompt.c_str());
					break;
				case COMMAND_STR_TYPE:
					Opt.add_options()(PositionCommandSourceArray[i].strCommand.c_str(), value<string>(), PositionCommandSourceArray[i].strCommandPrompt.c_str());
					break;
				default:
					break;
				}

				//��������һ��
				if (i == (int)PositionCommandSourceArray.size() - 1)
				{
					PositionOpt.add(PositionCommandSourceArray[i].strCommand.c_str(), -1);
				}
				else
				{
					PositionOpt.add(PositionCommandSourceArray[i].strCommand.c_str(), 1);
				}
			}
			//��ʼ����
			auto Result = command_line_parser(nArgc, argv).options(Opt).positional(PositionOpt).run();
			//������
			store(Result, m_VarInfo);
		}
		//ֱ�ӽ���
		else
		{
			auto Result = parse_command_line(nArgc, argv, Opt);
			//������
			store(Result, m_VarInfo);
		}
	}

	if (!ConfigSourceArray.empty())
	{

		if (boost::filesystem::exists(m_strConfigPath))
		{
			//����������
			options_description Opt("config");
			for (auto& V : ConfigSourceArray)
			{
				switch (V.eumType)
				{
				case COMMAND_INT_TYPE:
					Opt.add_options()(V.strCommand.c_str(), value<int>(), V.strCommandPrompt.c_str());
					break;
				case COMMAND_FLOAT_TYPE:
					Opt.add_options()(V.strCommand.c_str(), value<double>(), V.strCommandPrompt.c_str());
					break;
				case COMMAND_STR_TYPE:
					Opt.add_options()(V.strCommand.c_str(), value<string>(), V.strCommandPrompt.c_str());
					break;
				default:
					break;
				}
			}

			auto Result = parse_config_file<char>(m_strConfigPath.c_str(), Opt, true);

			store(Result, m_VarInfo);
		}
	}

	//֪ͨ
	notify(m_VarInfo);
}

/*********************************************************
FunctionName:GetCommandValue
FunctionDesc:
InputParam:
OutputParam:
Return:
Author:xiaowei.han
*********************************************************/
bool CArgParser::GetCommandValue(const std::string& strCommand, void* pValue)
{
	if (strCommand.empty() || nullptr == pValue)
	{
		return false;
	}

	//����key�Ҷ�Ӧ������
	auto FindPred = [strCommand](const COMMAND_INFO& Element)->bool
	{
		if (boost::contains(Element.strCommand,strCommand))
		{
			return true;
		}
		return false;
	};

	auto Iter = std::find_if(m_commandInfo.begin(), m_commandInfo.end(), FindPred);

	if (Iter == m_commandInfo.end())
	{
		return false;
	}

	if (!m_VarInfo.count(strCommand))
	{
		return false;
	}

	
	switch (Iter->eumType)
	{
	case COMMAND_NO_TYPE:
		break;
	case COMMAND_INT_TYPE:
	{
		*(int*)pValue = m_VarInfo[strCommand].as<int>();
	}
		break;
	case COMMAND_FLOAT_TYPE:
	{
		*(double*)pValue = m_VarInfo[strCommand].as<double>();
	}
		break;
	case COMMAND_STR_TYPE:
	{
		*(std::string*)pValue = m_VarInfo[strCommand].as<std::string>();
	}
		break;
	default:
		break;
	}
	return true;
}

/*********************************************************
FunctionName:SetConfigPath
FunctionDesc:���������ļ���·��
InputParam:
OutputParam:
Return:
Author:xiaowei.han
*********************************************************/
void CArgParser::SetConfigPath(const std::string& strConfigPath)
{
	m_strConfigPath = strConfigPath;
}


std::string CArgParser::DisplayHelpInfo(void)
{
	using namespace std;
	using namespace boost::program_options;

	string strResult;

	//��Դ�������еĲ�����Ϣ
	vector<COMMAND_INFO> CommandSourceArray;
	//��Դ��������λ����Ϣ�Ĳ�����Ϣ
	vector<COMMAND_INFO> PositionCommandSourceArray;
	//��Դ�������ļ��Ĳ�����Ϣ
	vector<COMMAND_INFO> ConfigSourceArray;
	//���з���
	SortParamInfo(CommandSourceArray, ConfigSourceArray, PositionCommandSourceArray);

	if (!CommandSourceArray.empty())
	{
		//����������
		options_description HelpOpt("commands usage.");
		for (auto& V : CommandSourceArray)
		{
			switch (V.eumType)
			{
			case COMMAND_NO_TYPE:
				HelpOpt.add_options()(V.strCommand.c_str(), V.strCommandPrompt.c_str());
				break;
			case COMMAND_INT_TYPE:
				HelpOpt.add_options()(V.strCommand.c_str(), value<int>(), V.strCommandPrompt.c_str());
				break;
			case COMMAND_FLOAT_TYPE:
				HelpOpt.add_options()(V.strCommand.c_str(), value<double>(), V.strCommandPrompt.c_str());
				break;
			case COMMAND_STR_TYPE:
				HelpOpt.add_options()(V.strCommand.c_str(), value<string>(), V.strCommandPrompt.c_str());
				break;
			default:
				break;
			}
		}

		stringstream OutPut;

		HelpOpt.print(OutPut);

		strResult = OutPut.str();
	}

	return strResult;
}

/*********************************************************
FunctionName:SortParamInfo
FunctionDesc:������Ϣ����
InputParam:
OutputParam:
Return:
Author:xiaowei.han
*********************************************************/
void CArgParser::SortParamInfo(std::vector<COMMAND_INFO>& CommandSourceArray, std::vector<COMMAND_INFO>& ConfigSourceArray, std::vector<COMMAND_INFO>& PositionCommandSourceArray)
{
	CommandSourceArray.clear();
	ConfigSourceArray.clear();
	PositionCommandSourceArray.clear();
	//��ʼ����
	for (auto& Element : m_commandInfo)
	{
		switch (Element.eumSource)
		{
			//Դ�����������е�
		case COMMAND_SOURCE:
			CommandSourceArray.emplace_back(Element.strCommand, Element.eumType, Element.strCommandPrompt, Element.eumSource);
			break;
			//Դ�����������е�λ�õ�
		case POSITION_COMMAND_SOURCE:
			PositionCommandSourceArray.emplace_back(Element.strCommand, Element.eumType, Element.strCommandPrompt, Element.eumSource);
			break;
			//Դ�����������ļ���
		case CONFIG_FILE_SOURCE:
			ConfigSourceArray.emplace_back(Element.strCommand, Element.eumType, Element.strCommandPrompt, Element.eumSource);
			break;
		default:
			break;
		}
	}
}
