#pragma once
#include "CThread.h"
#include <vector>

class CThreadPoolMgrt
{
public:
	CThreadPoolMgrt(int poolSize = 3, int maxPoolSize = 5);
	virtual ~CThreadPoolMgrt(void);

	//��������
	bool PushJob(JobFunction jobFunc, WPARAM wParam, LPARAM lParam, JobCallBack cb);
	//��ȡ�̳߳ش�С
	int GetPoolSize();

private:
	std::vector<CThread *> vThreads;
	int nMaxPoolSize;
};

