#ifndef ABSTRACT_KEEP_ALIVE_STRATEGY_H
#define ABSTRACT_KEEP_ALIVE_STRATEGY_H
#include <boost/thread.hpp>
#include <boost/smart_ptr.hpp>
class CAbstractKeepAliveStrategy
{
public:
	CAbstractKeepAliveStrategy();
	virtual ~CAbstractKeepAliveStrategy();


public:
	//�����������
	void SetKeepAliveGap(int nGap) { m_nKeepAliveGap = nGap; }
	
	int GetKeepAliveGap(void) const { return m_nKeepAliveGap; }

	//��ʼ����
	void StartKeepAlive(void);
	
	//ֹͣ����
	void StopKeepAlive(void);

	//ʵ��KeepAlive���麯��
	virtual void KeepAlive(void) = 0;
private:
	//����������ʱ��(��λ:s)
	int m_nKeepAliveGap;
	//�̶߳���
	boost::shared_ptr<boost::thread> m_KeepAliveThread;
};





#endif