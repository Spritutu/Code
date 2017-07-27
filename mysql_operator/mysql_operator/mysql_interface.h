#ifndef MYSQL_INTERFACE_H
#define MYSQL_INTERFACE_H
#include <string>
#include <vector>

#ifdef _WIN32
#ifndef MYSQL_INTERFACE_EXPORT
#define MYSQL_DLL_INTERFACE  extern "C" _declspec(dllimport)

#else
#define MYSQL_DLL_INTERFACE  extern "C" _declspec(dllexport)
#endif

#else
#define MYSQL_DLL_INTERFACE  
#endif



//�����ݿ�
MYSQL_DLL_INTERFACE bool OpenDB(const std::string& strAddress, int nPort,const std::string& strUserName, const std::string& strPassword, const std::string& strDBInstance);
//�ر����ݿ�
MYSQL_DLL_INTERFACE bool CloseDB(void);
//ִ��ping���ݿ��
MYSQL_DLL_INTERFACE void PingDB(void);
//ִ�зǲ�ѯ��SQL���
MYSQL_DLL_INTERFACE bool RunNoQuerySQL(const std::string& strSQL);
//ִ�в�ѯ��SQL���
MYSQL_DLL_INTERFACE bool RunQuerySQL(const std::string& strSQL, std::vector<std::string>& ResultArray);





#endif
