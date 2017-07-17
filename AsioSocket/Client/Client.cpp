// Client.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <cstring>
#include <boost/thread.hpp>
#include "AsioSocketClient.h"

void Display(bool bResult)
{
	using namespace std;
	if (bResult)
	{
		cout << "Succeed!" << endl;
	}
	else
	{
		cout << "Failed!" << endl;
	}
}

void SendResult(unsigned int nDataLength)
{

	using namespace std;

	cout << "send succeed,the length = " << nDataLength << endl;

}
int main()
{

	char szData[] = "hello,Asio,It is very good.";
	using namespace std;
	using namespace boost;
	CAsioSocketClient Client;

	Client.SetConnectCallBack(Display);
	Client.SetSendedCallBack(SendResult);
	Client.AsyncConnect("172.24.32.240", 10024);



	auto ThreadHandler = [&]()
	{
		Client.StartWork();
	};
	//���������߳�
	boost::thread T(ThreadHandler);


	cout << "�����������ʾ���в���!" << endl;

	cout << "send:��������" << endl;
	cout << "quit:�˳�����" << endl;

	while (true)
	{
		string strOperation;

		cin >> strOperation;

		if (strOperation == "send")
		{
			string strContent;
			cout << "��������Ҫ���͵�����:" << endl;
			cin >> strContent;

			Client.AsyncSendData(strContent.c_str(), (unsigned int)strContent.length());
		}
		else if (strOperation == "quit")
		{
			Client.StopWork();
			T.join();
			break;
		}
		else
		{

		}

	}
    return 0;
}

