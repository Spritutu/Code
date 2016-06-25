#include "StdAfx.h"
#include "Lock.h"


/********************************************************************************************************************************************************************/

//����ʵ��
/********************************************************************************************************************************************************************/
CLock::CLock( void )
{
	MUTEX_INIT(m_Lock);
}

CLock::~CLock( void )
{
	MUTEX_DEL(m_Lock);
}

void CLock::Lock( void )
{
	LOCK(m_Lock);
}

void CLock::UnLock( void )
{
	UNLOCK(m_Lock);
}


/********************************************************************************************************************************************************************/
