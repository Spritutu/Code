#pragma once
#include <boost/asio/io_service.hpp>
#include <boost/asio/serial_port.hpp>
#include <string>
typedef struct _comproperty
{
	//���ڱ��
	std::string strSerialPort;
	//������
	unsigned int nBaudRate;
	//ͨ���ֽ�λ��
	int nDataBits;
	//(0:1��ֹͣλ 1:1.5��ֹͣλ(Linux�ݲ�֧��1.5��ֹͣλ) 2:2��ֹͣλ)
	int nStopBits;
	//(0:��ʹ��У��  1:����У�� 2:ż��У�� 3:���У�飨Linux��û�д�� 4:�ո�У��)
	int nPairty;
	//(0:��ʹ������ 1:ʹ��Ӳ������)
	bool bFlowControl;
	_comproperty()
	{
		strSerialPort = "";
		nBaudRate = 9600;
		nDataBits = 8;
		nStopBits = 0;
		nPairty = 0;
		bFlowControl = false;
	}
}COMPROPERTY, *LPCOMPROPERTY;

class CSerialPortService
{
public:
	CSerialPortService();
	~CSerialPortService();


	void SetSerialPortOption(const COMPROPERTY& Options)
	{
		m_SerialOption = Options;
	}

	//��������
	void StartSerialPortService(void);

	//ֹͣ����
	void StopSerialPortService(void);

	//���ô�������ʼ�ɼ�
	void AsyncWriteData(BYTE* pData, int nDataLength);
private:
	//�������֪ͨ
	void ReadHandler(const boost::system::error_code& ec, std::size_t bytes_transferred);

	//�ж��Ƿ�����������
	int HandlerData(BYTE* pData,int nDataLength);

	//����CRCУ���
	BYTE CalCRC8(BYTE* pBuf, unsigned int nsize);

	//�������֪ͨ
	void WriteHandler(BYTE* pData, int nDataLength, const boost::system::error_code& ec, std::size_t bytes_transferred);

private:
	//��ʼ������
	bool InitSerialPort(void);
	//���ջ�����
	BYTE* m_pRecvBuffer;
	//�Ѿ�ռ�õ��ֽ�
	int m_nUseBufferBytes;
	//����ͨ��������
	COMPROPERTY m_SerialOption;
	//IoService
	boost::asio::io_service m_IoService;
	boost::asio::io_service::work m_Work;
	boost::asio::serial_port m_SerialPort;
};

