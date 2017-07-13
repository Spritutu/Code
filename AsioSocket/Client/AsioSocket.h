/**************************************************************************
Copyright(C):
FileName:AsioSocket.h
Description:����Asio���Ƶ�Socket
Author:xiaowei.han
Date:2017/07/13
Others:
Histroy:
**************************************************************************/
#ifndef ASIO_SOCKET_H
#define ASIO_SOCKET_H
//��ʹ��STD�е�CHRONO
#define BOOST_ASIO_DISABLE_STD_CHRONO
#include <boost/asio.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/address.hpp>
#include <string>
//����practorģʽ���׽���
class CAsioSocketClient
{
public:
	CAsioSocketClient();
	~CAsioSocketClient() = default;

public:
	//ͬ������
	bool AsyncConnect(const std::string strAddress, unsigned short usPort);
	bool AsyncConnect(const char* szAddress, unsigned short usPort);
private:
	//IOService
	boost::asio::io_service m_IOService;
	//work ����ѭ�����˳�
	boost::asio::io_service::work m_Work;
	//�׽���
	boost::asio::ip::tcp::socket m_AsioSocket;
};


#endif
