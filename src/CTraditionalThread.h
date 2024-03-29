/**
 * @file		CTraditionalThread.h
 * @brief		Traditional Thread class (MsgQueue + Thread)
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
#pragma once

#include <cstdio>
#include <mutex>
#include <thread>
#include <cstdint>
#include <cstddef>
#include <memory>
#include <condition_variable>
#include "CLockedQueue.h"

class CTraditionalThread
{
public:
    CTraditionalThread();
    CTraditionalThread(std::uint32_t NumOfQueueMsg);
    virtual ~CTraditionalThread();
public:
	typedef enum{
		enNotify = 0,
		enQuit,
		enMsgID_MAX,
	}enMsgID_t;

	/**
	 * @breif Task Message Block
	 */
	typedef struct{
		enMsgID_t       	enMsgId;
		std::mutex   		*psyncMtx;
		std::uint32_t		*ptrDataForSrc;
		std::uint32_t		*ptrDataForDst;
		std::uint32_t       param[16];
	}stTaskMsgBlock_t;
protected:
	bool m_bRunning;

	std::mutex m_SyncMtx;
	std::shared_ptr<std::thread> m_pThread;
	LockedQueue<stTaskMsgBlock_t> *m_pMsgQueue;

	virtual bool GetMsg(stTaskMsgBlock_t& stTaskMsg) final;
	//virtual bool pGetMsg(stTaskMsgBlock_t& stTaskMsg) final;

	/**
	 * @brief Please Override
	 */
	virtual void MainLoop() = 0;

public:

	/**
	 * @brief Please Override
	 */
	virtual void StartThread() = 0;

    /**
     * @brief no override
     */
	virtual void StopThread() final;
	virtual void PostMsgQuitThread() final;
	virtual bool PostMsg(stTaskMsgBlock_t& stTaskMsg) final;
	virtual void WaitStop() final;
};
