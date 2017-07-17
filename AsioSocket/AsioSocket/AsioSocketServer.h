/**************************************************************************
Copyright(C):Envision. Co., Ltd.
FileName:AsioSocketServer.h
Description:����Asio�ķ����ģ��
Author:xiaowei.han
Date:2017/07/17
Others:
Histroy:
**************************************************************************/
#ifndef ASIO_SOCKET_SERVER_h
#define ASIO_SOCKET_SERVER_h
//��ʹ��STD�е�CHRONO
#define BOOST_ASIO_DISABLE_STD_CHRONO
#include <boost/asio.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/address.hpp>
#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <boost/smart_ptr.hpp>
#include "AsioSocketClient.h"

//�����첽�������ӵĻص�
using pAsyncAcceptCallBack = void(*)(CAsioSocketClient* pClient, bool bResult);

class CAsioSocketServer : boost::noncopyable
{

public:
	CAsioSocketServer(unsigned short usPort);
	~CAsioSocketServer();


public:

	//��ʼ����
	void StartWork(void);

	//ֹͣ����
	void StopWork(void);

	//��������֪ͨ
	void SetAcceptCallBack(pAsyncAcceptCallBack pCallBack);
	//ͬ����������
	boost::shared_ptr<CAsioSocketClient> SyncAccept(void);
	//�첽��������
	void AsyncAccept(void);
private:
	//IOService
	boost::asio::io_service m_IOService;
	//work ����ѭ�����˳�
	boost::asio::io_service::work m_Work;
	//�׽���
	boost::asio::ip::tcp::acceptor m_Acceptor;
	//�ص��ӿ�
	boost::function<void(CAsioSocketClient* pClient, bool bResult)> m_AcceptNotifier;
};
#endif

