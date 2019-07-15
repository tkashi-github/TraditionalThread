/**
 * @file		CSampleThread.h
 * @brief		Traditional Thread CSampleThread class (MsgQueue + Thread)
 * @author		Takashi Kashiwagi
 * @date		2019/7/15
 * @version     0.1.0
 * @details 
 * --
 * License Type (MIT License)
 * --
 * Copyright 2019 Takashi Kashiwagi
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a 
 * copy of this software and associated documentation files (the "Software"), 
 * to deal in the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included 
 * in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
 * DEALINGS IN THE SOFTWARE.
 *
 * @par Update:
 * - 2019/07/15: Takashi Kashiwagi: v0.1.0
 */

#include "CSampleThread.h"
#include <cstdio>
#include <iostream>
#include <stdio.h>

CSampleThread::CSampleThread() : CTraditionalThread()
{
	printf("[%s (%d)] ENTER\r\n", __func__, __LINE__);
}
CSampleThread::~CSampleThread()
{
	printf("[%s (%d)] EXIT\r\n", __func__, __LINE__);
}

void CSampleThread::MainLoop()
{
    printf("[%s (%d)] ENTER\r\n", __func__, __LINE__);
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
  	printf("[%s (%d)] EXIT\r\n", __func__, __LINE__);
    m_bRunning = false;
}
void CSampleThread::StartThread()
{
	m_pThread = std::make_shared<std::thread>(std::bind(&CSampleThread::MainLoop, this));

    m_pThread.get()->detach();
}