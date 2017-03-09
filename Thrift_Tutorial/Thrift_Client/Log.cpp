/**************************************************************************************************************************************************
��Ȩ����:
�ļ�����:log.cpp
��������:��ɴ�ӡ��־�Ĺ���
����:hanxiaowei
�������:2013-07-29
**************************************************************************************************************************************************/
#include "stdafx.h"
#include "log.h"
#include "Lock.h"

#ifdef _WIN32
#pragma warning(disable:4996)
#pragma warning(disable:4251)
#pragma warning(disable:4554)
#endif

//����������󳤶�
#define  BUFFER_MAX_SIZE          (1024 * 10)

//��־�ļ����������
#define  LOG_MAX_SIZE                 (100 * 1024 * 1024)

//����ͬ������
static CLock s_Lock;

//��¼�ļ��ﵽ��־�ĵȼ��Ĵ���
static unsigned int s_nTimes = 1;

/********************************************************************************************************************************************************************/
//�����ļ����ʵ��
/********************************************************************************************************************************************************************/
CHandleFile::CHandleFile( void ):
m_pFile(NULL)
{

}

CHandleFile::~CHandleFile( void )
{
	if (NULL != m_pFile)
	{
		fclose(m_pFile);
		m_pFile = NULL;
	}

}

/*****************************************************************************************************************************************
��������:Open
��������:���ļ�
�������:szName:Ҫ�򿪵��ļ�����
�������:��
����ֵ:true:�ɹ� false:ʧ��
*****************************************************************************************************************************************/
bool CHandleFile::Open( const char* szName )
{
	if (NULL == szName)
	{
		return false;
	}

	//����Ѿ���
	if (IsOpen())
	{
		return true;
	}

	m_pFile = fopen(szName,"a+");

	if (NULL == m_pFile)
	{
		return false;
	}

	return true;


}

/*****************************************************************************************************************************************
��������:Close
��������:�ر��ļ�
�������:��
�������:��
����ֵ:true:�ɹ� false:ʧ��
*****************************************************************************************************************************************/
void CHandleFile::Close( void )
{
	if (NULL != m_pFile)
	{
		fclose(m_pFile);
		m_pFile = NULL;
	}

}

/*****************************************************************************************************************************************
��������:Write
��������:���ļ���д������
�������:pData:Ҫд������� nDataLen:д�����ݵĳ��� 
�������:uWriteLen:ʵ��д������ݵĳ���
����ֵ:true:�ɹ� false:ʧ��
*****************************************************************************************************************************************/
bool CHandleFile::Write( void* pData,unsigned int nDataLen,unsigned int& uWriteLen )
{
	uWriteLen = 0;
	//����ļ���δ��
	if (!IsOpen())
	{
		return false;
	}

	int nAlreadyWriteByte = 0;

	nAlreadyWriteByte = (int)fwrite(pData,1,nDataLen,m_pFile);

	//д��ʧ��
	if (nAlreadyWriteByte <= 0)
	{
		return false;
	}
	uWriteLen = nAlreadyWriteByte;
	return true;
}

/*****************************************************************************************************************************************
��������:Read
��������:���ļ��ж�ȡ����
�������:pData:��Ŷ�ȡ���ݵĻ����� nDataLen:Ҫ��ȡ���ֽ���
�������:uReadLen:ʵ�ʶ�ȡ�����ݵĳ���
����ֵ:true:�ɹ� false:ʧ��
*****************************************************************************************************************************************/
bool CHandleFile::Read( void* pData,unsigned int nDataLen,unsigned int& uReadLen )
{
	uReadLen = 0;

	if (!IsOpen())
	{
		return false;
	}

	int nReadByte = 0;

	nReadByte = (int)fread(pData,1,nDataLen,m_pFile);

	//��ȡʧ��
	if (nReadByte <= 0)
	{
		return false;
	}

	uReadLen = nReadByte;

	return true;
}

/*****************************************************************************************************************************************
��������:IsOpen
��������:�ж��ļ��Ƿ��Ѿ���
�������:��
�������:��
����ֵ:true:�Ѿ��� false:û�д�
*****************************************************************************************************************************************/
bool CHandleFile::IsOpen( void )
{
	if (NULL == m_pFile)
	{
		return false;
	}
	return true;
}

/*****************************************************************************************************************************************
��������:SeekFilePos
��������:�����ļ�ָ��λ��
�������:Pos:���õ����λ�� loffset:������õ�ƫ���� ��������ƣ�������ǰ��
�������:��
����ֵ:true:���óɹ� false:����ʧ��
*****************************************************************************************************************************************/
bool CHandleFile::SeekFilePos( FILEPOS Pos,long loffset )
{
	if (!IsOpen())
	{
		return false;
	}

	int nResult = 0;
	switch (Pos)
	{
	case POS_CURRENT:
		nResult = fseek(m_pFile,loffset,SEEK_CUR);
		break;
	case POS_HEAD:
		nResult = fseek(m_pFile,loffset,SEEK_SET);
		break;
	case POS_TAIL:
		nResult = fseek(m_pFile,loffset,SEEK_END);
		break;
	default:
		break;
	}

	//����ʧ��
	if (0 != nResult)
	{
		return false;
	}
	return true;
}

/*****************************************************************************************************************************************
��������:GetFileSize
��������:��ȡ�ļ��Ĵ�С
�������:��
�������:��
����ֵ:�ļ��Ĵ�С
*****************************************************************************************************************************************/
unsigned long CHandleFile::GetFileSize( void )
{
	if (!IsOpen())
	{
		return -1;
	}

	//���õ��ļ�β
	if (!SeekFilePos(POS_TAIL,0))
	{
		return -1;
	}

	long lSize = ftell(m_pFile);
	return lSize;
}


/********************************************************************************************************************************************************************/

//��־���ʵ��
/********************************************************************************************************************************************************************/
/*****************************************************************************************************************************************
��������:CreateInstance
��������:������־���Ψһʵ��
�������:��
�������:��
����ֵ:Ψһʵ����ָ��
*****************************************************************************************************************************************/
CLog& CLog::CreateInstance( void )
{
	//Ψһ��һ����־ʵ����
	return s_Log;
}

/*****************************************************************************************************************************************
��������:SetLogPath
��������:������־�ļ��Ĵ��Ŀ¼
�������:szLogDir:�����־��Ŀ¼
�������:��
����ֵ:��
*****************************************************************************************************************************************/
void CLog::SetLogPath( const char* szLogDir )
{
	if (NULL == szLogDir)
	{
		return;
	}
	m_strLogDir = szLogDir;
}

/*****************************************************************************************************************************************
��������:SetLogLevel
��������:������־����
�������:loglevel:��־�ĵȼ�
�������:��
����ֵ:��
*****************************************************************************************************************************************/
void CLog::SetLogLevel( LOGLEVEL loglevel )
{
	m_loglevel = loglevel;
}

/*****************************************************************************************************************************************
��������:WriteLog
��������:��ӡ��־��Ϣ
�������:loglevel:��־�ĵȼ� szFormat:��ӡ�ĸ�ʽ  ...�����
�������:��
����ֵ:��
*****************************************************************************************************************************************/
void CLog::WriteLog( LOGLEVEL loglevel,const char* szFormat,... )
{
	if (NULL == szFormat)
	{
		return;
	}
	//�鿴��ӡ�ȼ��Ƿ���Ҫ��ӡ
	if (loglevel < m_loglevel)
	{
		return;
	}

	//����ͬ��
	s_Lock.Lock();
	char szLogContent[BUFFER_MAX_SIZE] = {0};
	va_list varg;
	va_start(varg,szFormat);
	vsprintf(szLogContent,szFormat,varg);
	va_end(varg);

	//�õ�ϵͳʱ��
	time_t logtime;
	time(&logtime);
	struct tm *plogtime = NULL; 
	plogtime = localtime(&logtime);
	char szTime[MAX_PATH] = {0};
	char szDayTime[MAX_PATH] = {0};
	//��ʱ���ʽ��Ϊ�ַ���
	sprintf(szTime,"%02d-%02d-%02d %02d:%02d:%02d",plogtime->tm_year + 1900,plogtime->tm_mon + 1,plogtime->tm_mday,plogtime->tm_hour,plogtime->tm_min,plogtime->tm_sec);
	//�ж�ǰ׺
	if (m_strLogPrefix.empty())
	{
		sprintf(szDayTime,"%s_%02d_%02d_%02d","log",plogtime->tm_year + 1900,plogtime->tm_mon + 1,plogtime->tm_mday);
	}
	else
	{
		sprintf(szDayTime,"%s_%02d_%02d_%02d",m_strLogPrefix.c_str(),plogtime->tm_year + 1900,plogtime->tm_mon + 1,plogtime->tm_mday);
	}
	char szLogLevel[MAX_PATH] = {0};
	switch (loglevel)
	{
	case LOG_DEBUG:
		strncpy(szLogLevel," [DEBUG] ",strlen(" [DEBUG] "));
		break;
	case LOG_INFO:
		strncpy(szLogLevel," [INFO] ",strlen(" [INFO] "));
		break;
	case LOG_WARN:
		strncpy(szLogLevel," [WARN] ",strlen(" [WARN] "));
		break;
	case LOG_ERROR:
		strncpy(szLogLevel," [ERROR] ",strlen(" [ERROR] "));
		break;
	case LOG_FATAL:
		strncpy(szLogLevel," [FATAL] ",strlen(" [FATAL] "));
		break;
	case LOG_NECESSARY:
		strncpy(szLogLevel," [NECESSARY] ",strlen(" [NECESSARY] "));
		break;
	default:
		break;
	}
	//�鿴�Ƿ����
	char szLogName[MAX_PATH] = {0};
	while (1)
	{
		memset(szLogName,0,sizeof(szLogName));
#ifdef _WIN32
		sprintf(szLogName,"%s\\%s_%d.dat",m_strLogDir.c_str(),szDayTime,s_nTimes);
		if (0 == _access(szLogName,0))
#else
		sprintf(szLogName,"%s/%s_%d.dat",m_strLogDir.c_str(),szDayTime,s_nTimes);
		if (0 == access(szLogName,0))
#endif
		{
			//�鿴�ļ��Ĵ�С���Ƿ񳬹�100M
			CHandleFile file;
			if (file.Open(szLogName))
			{
				unsigned long lSize = file.GetFileSize();
				file.Close();
				//�������100M
				if (lSize >= LOG_MAX_SIZE)
				{
					s_nTimes++;
					continue;
					//����ǰ��д�˶��ٸ���־�ļ���
				}
				//���������100M
				else
				{
					break;
				}
			}	
		}
		//�������������ļ������˳�ѭ��
		else
		{
			break;
		}
	}
	//��ʼд�ļ�
	string strContent = string(szTime) + string(szLogLevel) + string(szLogContent) + string("\n");

	char szContent[BUFFER_MAX_SIZE] = {0};
	strncpy(szContent,strContent.c_str(),strContent.length());

	CHandleFile Writefile;

	if (Writefile.Open(szLogName))
	{
		unsigned int nWriteLength = 0;
		Writefile.Write(szContent,(unsigned int)strContent.length(),nWriteLength);
		Writefile.Close();
	}
	s_Lock.UnLock();
}

CLog::CLog( void )
{
	m_loglevel = LOG_DEBUG;
}

CLog::~CLog( void )
{

}

void CLog::SetLogNamePrefix( const char* szPrefix )
{
	if (NULL == szPrefix)
	{
		return;
	}

	m_strLogPrefix = szPrefix;

}

CLog CLog::s_Log;

/********************************************************************************************************************************************************************/