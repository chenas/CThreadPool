#pragma once
#include "CThread.h"
#include <vector>

class CThreadPoolMgrt
{
public:
	CThreadPoolMgrt(int poolSize = 3, int maxPoolSize = 5);
	virtual ~CThreadPoolMgrt(void);

	//加入任务
	bool PushJob(JobFunction jobFunc, WPARAM wParam, LPARAM lParam, JobCallBack cb);
	//获取线程池大小
	int GetPoolSize();

private:
	std::vector<CThread *> vThreads;
	int nMaxPoolSize;
};

