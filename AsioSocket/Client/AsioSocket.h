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

//����practorģʽ���׽���
class CAsioSocket
{
public:
	CAsioSocket() = default;
	~CAsioSocket() = default;


};


#endif
