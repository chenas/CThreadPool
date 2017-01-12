#include "CThread.h"


CThread::CThread(void)
{
	this->bIsWorking = false;
	this->wParam = 0;
	this->lParam = 0;
	this->jobCallBack = 0;
	this->jobFunction = 0;
	this->hHandle = CreateThread(0,0,(LPTHREAD_START_ROUTINE)threadEntry,this,0,0);
	printf("new thread %08X \n", this->hHandle);
}


CThread::~CThread(void)
{
	if (hHandle != INVALID_HANDLE_VALUE)
	{
		
		jobCallBack = 0;
		jobFunction = 0;
		ResumeThread(hHandle);
		WaitForSingleObject(hHandle, INFINITE);
		CloseHandle(hHandle);
	}
}

bool CThread::IsWorking()
{
	return this->bIsWorking;
}

void CThread::DoJob(JobFunction job, WPARAM wParam, LPARAM lParam, JobCallBack cb)
{
	this->jobFunction = job;
	this->jobCallBack = cb;
	this->wParam = wParam;
	this->lParam = lParam;
	//唤醒线程
	ResumeThread(hHandle);
}

void CThread::setJobDone()
{
	this->bIsWorking = false;
	//job done 挂起线程
	SuspendThread(hHandle);
}

DWORD WINAPI CThread::threadEntry(LPARAM lParam)
{
	CThread* pThis = (CThread*)lParam;
	while(true)
	{
		if (pThis->jobFunction == INVALID_HANDLE_VALUE || pThis->jobCallBack == INVALID_HANDLE_VALUE)
		{
			break; //跳出循环，线程终止
		}
		if (pThis->jobCallBack == 0 || pThis->jobFunction == 0)
		{
			continue; //跳过本次循环
		}
		pThis->bIsWorking = true;
		unsigned int rtn = pThis->jobFunction(pThis->wParam, pThis->lParam);
		printf("thread %08X job result %d \n", pThis->hHandle, rtn);
		pThis->jobCallBack(rtn);
		pThis->setJobDone();
	}
	return 0;
}