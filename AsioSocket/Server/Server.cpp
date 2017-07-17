// Server.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <cstring>
#include <boost/thread.hpp>
#include "AsioSocketServer.h"

//����ͬ����������
static void TestSyncAccept(void);
//�����첽��������
static void TestAsyncAccept(void);

//���ӳɹ��Ļص�����
static void AcceptCallBack(CAsioSocketClient* pClient, bool bResult);

void AcceptCallBack(CAsioSocketClient* pClient, bool bResult)
{
	using namespace std;
	if (bResult)
	{
		cout << "New Connection Comes." << endl;
	}
	else
	{
		cout << "New Connection Comes failed." << endl;
	}
}

int main()
{
	
	//TestAsyncAccept();
	TestAsyncAccept();
    return 0;
}


void TestSyncAccept(void)
{
	using namespace std;
	auto p = new CAsioSocketServer(10024);
	if (nullptr == p)
	{
		cout << "new failed." << endl;
		return;
	}
	while (true)
	{
		auto NewSocket = p->SyncAccept();
		if (NewSocket)
		{
			cout << "Oh,New Connect comes." << endl;
			char szData[] = "hello,I comes.";
			auto nSize = strlen(szData);
			NewSocket->AsyncSendData(szData, (unsigned int)nSize);
			boost::this_thread::sleep(boost::posix_time::seconds(3));
		}
	}
	delete p;
	p = nullptr;
}

void TestAsyncAccept(void)
{
	using namespace std;
	auto p = new CAsioSocketServer(10024);
	if (nullptr == p)
	{
		cout << "new failed." << endl;
		return;
	}
	p->SetAcceptCallBack(AcceptCallBack);
	p->AsyncAccept();
	p->StartWork();
	delete p;
	p = nullptr;
}

