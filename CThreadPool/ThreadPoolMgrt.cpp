#include "ThreadPoolMgrt.h"


CThreadPoolMgrt::CThreadPoolMgrt(int poolSize, int maxPoolSize):nMaxPoolSize(maxPoolSize)
{
	std::vector<CThread *>().swap(vThreads);
	for (int i = 0; i<poolSize; i++)
	{
		CThread* c = new CThread();
		vThreads.push_back(c);
	}
}

CThreadPoolMgrt::~CThreadPoolMgrt(void)
{
	std::vector<CThread *>::iterator it = vThreads.begin();
	for (; it!=vThreads.end(); it++)
	{
		delete *it;
	}
}

bool CThreadPoolMgrt::PushJob(JobFunction jobFunc, WPARAM wParam, LPARAM lParam, JobCallBack cb)
{
	std::vector<CThread *>::iterator it = vThreads.begin();
	for (; it != vThreads.end(); it++)
	{
		CThread* tmp = *it;
		if (!tmp->IsWorking())
		{
			tmp->DoJob(jobFunc, wParam, lParam, cb);
			return true;
		}
	}
	if (vThreads.size() < this->nMaxPoolSize)
	{
		CThread* thread = new CThread();
		vThreads.push_back(thread);
		thread->DoJob(jobFunc, wParam, lParam, cb);
	}
	else
	{
		///任务没有被领取
		///如果有队列，可以加入队列里面
		return false;
	}

	return true;
}

int CThreadPoolMgrt::GetPoolSize()
{
	return vThreads.size();
}