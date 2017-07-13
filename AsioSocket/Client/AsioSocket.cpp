
/**************************************************************************
Copyright(C):
FileName:AsioSocket.cpp
Description:����Asio���Ƶ�Socket
Author:xiaowei.han
Date:2017/07/13
Others:
Histroy:
**************************************************************************/
#include "stdafx.h"
#include "AsioSocket.h"

CAsioSocketClient::CAsioSocketClient():
	m_Work(m_IOService),
	m_AsioSocket(m_IOService)
{

}

/*******************************************************************
*��������:AsyncConnect
*��������:ͬ�����ӷ�����
*�������:
*�������:
*����ֵ:
*����:xiaowei.han
*����:2017/07/13 22:51:32
*******************************************************************/
bool CAsioSocketClient::AsyncConnect(const std::string strAddress, unsigned short usPort)
{
	if (strAddress.empty())
	{
		return false;
	}

	//����Remot Endpoint
	auto RemoteAddress = boost::asio::ip::address::from_string(strAddress);
	boost::asio::ip::tcp::endpoint RemotePoint(RemoteAddress,usPort);
	boost::system::error_code ec;
	m_AsioSocket.connect(RemotePoint, ec);

	if (ec)
	{
		return false;
	}

	return true;

}

/*******************************************************************
*��������:AsyncConnect
*��������:ͬ�����ӷ�����
*�������:
*�������:
*����ֵ:
*����:xiaowei.han
*����:2017/07/13 22:51:32
*******************************************************************/
bool CAsioSocketClient::AsyncConnect(const char* szAddress, unsigned short usPort)
{

	return AsyncConnect(std::string(szAddress), usPort);

}
