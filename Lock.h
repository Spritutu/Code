#pragma once

//ͷ�ļ�
/**************************************************************************************************************************************************/
#ifdef _WIN32
#include <stdio.h>
#include <Windows.h>
#include <map>
#include <string>
#include <stdarg.h>
#include <time.h>
#include <io.h>
//����Linux�������ڵ�ͷ�ļ�
#else
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <pthread.h>
#include <map>
#include <string>
#include <stdarg.h>
#include <string.h>
#endif

//�궨��
/************************************************************************************************************************************************/
#ifdef _WIN32
//���Ĳ���
typedef CRITICAL_SECTION    Mutex;
#define MUTEX_INIT(x)   InitializeCriticalSection(&x)
#define LOCK(x)             EnterCriticalSection(&x)
#define UNLOCK(x)         LeaveCriticalSection(&x)
#define MUTEX_DEL(x)    DeleteCriticalSection(&x)
#else
typedef int HANDLE;
#define INVALID_HANDLE_VALUE  (-1)
//#define NULL                                        (0)
//���Ĳ���
typedef pthread_mutex_t  Mutex;
#define MUTEX_INIT(x)   x = PTHREAD_MUTEX_INITIALIZER
#define LOCK(x)             pthread_mutex_lock(&x)
#define UNLOCK(x)         pthread_mutex_unlock(&x)
#define MUTEX_DEL(x)    pthread_mutex_destroy(&x)
#define MAX_PATH          (260)
#endif

//�ٽ���
class CLock
{
public:
	CLock(void);
	~CLock(void);

	void Lock(void);
	void UnLock(void);
private:
	Mutex m_Lock;
};

