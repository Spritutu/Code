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
#include <boost/function.hpp>
#include <string>
//������ɵĻص�
using pAsyncConnectCallBack = void(*)(bool bResult);
//������ɵĻص�
using pAsyncSendedCallBack = void(*)(unsigned int nDataLength);
//������ɵĻص�
using pAsyncReceivedCallBack = void(*)(char* pData,unsigned int nDataLength);
//����practorģʽ���׽���
class CAsioSocketClient
{
public:
	CAsioSocketClient();
	~CAsioSocketClient();

public:

	void StartWork();
	void StopWork();

	//ͬ������
	bool SyncConnect(const std::string strAddress, unsigned short usPort);
	bool SyncConnect(const char* szAddress, unsigned short usPort);

	//�첽����
	void AsyncConnect(const std::string strAddress, unsigned short usPort);
	void AsyncConnect(const char* szAddress, unsigned short usPort);

	//�첽��������
	void AsyncSendData(const char* pData, unsigned int nDataLength);

	//ͬ����������
	bool SyncSendData(const char* pData, unsigned int nDataLength,unsigned int& nSendLength);

	//�첽��������
	void AsyncReceiveData(char* pData, unsigned int nDataLength);

	//ͬ����������
	bool SyncRecvData(char* pBuffer, unsigned int nBufferLength,unsigned int& nRecvLength);

	//���ûص�
	void SetConnectCallBack(pAsyncConnectCallBack pFunction)
	{
		m_ConnectNotifier = pFunction;
	}

	void SetSendedCallBack(pAsyncSendedCallBack pFunction)
	{
		m_SendedNotifier = pFunction;
	}

	void SetReceivedCallBack(pAsyncReceivedCallBack pFunction)
	{
		m_ReceivedNotifier = pFunction;
	}
	//���û���������
	void SetBufferLength(unsigned int nLength)
	{
		m_nRecvBufferLength = nLength;
	}

private:
	//IOService
	boost::asio::io_service m_IOService;
	//work ����ѭ�����˳�
	boost::asio::io_service::work m_Work;
	//�׽���
	boost::asio::ip::tcp::socket m_AsioSocket;
	//����������ɵĻص�
	boost::function<void(bool)> m_ConnectNotifier;
	//���ڷ�����ɵĻص�
	boost::function<void(unsigned int nDataLength)> m_SendedNotifier;
	//���ڽ�����ɵĻص�
	boost::function<void(char* pData, unsigned int nDataLength)> m_ReceivedNotifier;
	//���ջ������Ĵ�С
	unsigned int m_nRecvBufferLength = 1024;
	//���ջ�����
	char* m_pRecvBuffer = nullptr;
};


#endif
