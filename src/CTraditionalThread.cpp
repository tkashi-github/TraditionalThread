#include "CTraditionalThread.h"
#include <iostream>
#include <thread>
#include <exception>

CTraditionalThread::CTraditionalThread()
{
	printf("[%s (%d)] ENTER\r\n", __func__, __LINE__);
	m_pMsgQueue = new LockedQueue<stTaskMsgBlock_t>(32);
}

CTraditionalThread::CTraditionalThread(std::uint32_t NumOfQueueMsg)
{
	printf("[%s (%d)] ENTER\r\n", __func__, __LINE__);
	m_pMsgQueue = new LockedQueue<stTaskMsgBlock_t>(NumOfQueueMsg);
}

CTraditionalThread::~CTraditionalThread()
{
	delete m_pMsgQueue;
	printf("[%s (%d)] EXIT\r\n", __func__, __LINE__);
}

/**
 * @brief MainLoop : Implementation Example
void CTraditionalThread::MainLoop()
{
    std::cout << "Thread : Start " << std::endl;
    m_bRunning =true;
    for(;;)
    {
        stTaskMsgBlock_t stTaskMsg;

        if(GetMsg(stTaskMsg) != false)
        {
            switch(stTaskMsg.enMsgId)
            {
            case enNotify:
                std::cout << "Thread : enNotify " << std::endl;
                break;
            case enQuit:
				std::cout << "Thread : enQuit " << std::endl;
                break;
            default:
                break;
            }
            if(stTaskMsg.psyncMtx != NULL)
            {
                stTaskMsg.psyncMtx->unlock();
            }

            if(stTaskMsg.ptrDataForDst != NULL)
            {
                delete[] stTaskMsg.ptrDataForDst;
            }

            if(stTaskMsg.enMsgId == enQuit)
            {
                break;
            }
        }
    }
    std::cout << "Thread :end"<< std::endl;
    m_bRunning = false;
}
 */

/**
 * @brief StartThread : Implementation Example
void CTraditionalThread::StartThread()
{
	m_pThread = std::make_shared<std::thread>(std::bind(&CTraditionalThread::MainLoop, this));

    m_pThread.get()->detach();
}
 */

void CTraditionalThread::StopThread()
{
	PostMsgQuitThread();
}

bool CTraditionalThread::PostMsg(stTaskMsgBlock_t &stTaskMsg)
{
	if (m_pMsgQueue != NULL)
	{
		m_pMsgQueue->enqueue(stTaskMsg);
		return true;
	}
	else
	{
		return false;
	}
}

bool CTraditionalThread::GetMsg(stTaskMsgBlock_t &stTaskMsg)
{
	if (m_pMsgQueue != NULL)
	{
		stTaskMsg = m_pMsgQueue->dequeue();
		return true;
	}
	else
	{
		return false;
	}
}

#if 0
bool CTraditionalThread::pGetMsg(stTaskMsgBlock_t &stTaskMsg)
{
	if (m_pMsgQueue != NULL)
	{
		if (false == m_pMsgQueue->pdequeue(stTaskMsg))
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		return false;
	}
}
#endif
void CTraditionalThread::PostMsgQuitThread()
{
	stTaskMsgBlock_t stTaskMsg;

	stTaskMsg.enMsgId = enQuit;

	PostMsg(stTaskMsg);
	std::cout << "PostMsgQuitThread : END" << std::endl;
}

void CTraditionalThread::WaitStop()
{
	while (m_bRunning != false)
	{
		/* NOP */
	}
}
