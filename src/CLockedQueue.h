
#pragma once

#include <cstdint>
#include <mutex>
#include <deque>
#include <condition_variable>
#include <functional> // ref

template <class T>
struct LockedQueue
{
	explicit LockedQueue(std::uint32_t NumOfElements)
		: NumOfElements(NumOfElements)
	{
	}

	void enqueue(const T &x)
	{
		std::unique_lock<std::mutex> lock(m_mtxQueue);
		c_enq.wait(lock, [this] { return data.size() != NumOfElements; });
		data.push_back(x);
		c_deq.notify_one();
	}

	T dequeue()
	{
		std::unique_lock<std::mutex> lock(m_mtxQueue);
		c_deq.wait(lock, [this] { return !data.empty(); });
		T ret = data.front();
		data.pop_front();
		c_enq.notify_one();
		return ret;
	}
	bool pdequeue(const T &x)
	{
		bool bret = false;

		if(data.empty() == false)
		{
			x = data.front();
			data.pop_front();
			c_enq.notify_one();
			bret = true;
		}
		
		return bret;
	}

private:
	std::mutex m_mtxQueue;
	std::deque<T> data;
	std::uint32_t NumOfElements;
	std::condition_variable c_enq;
	std::condition_variable c_deq;
};
