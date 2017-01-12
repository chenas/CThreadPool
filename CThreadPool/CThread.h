#pragma once

#include <Windows.h>
#include <stdio.h>

//要做的事情
typedef unsigned int(*JobFunction)(WPARAM wParam, LPARAM lParam);
//做完事情的回调函数
typedef void(*JobCallBack)(unsigned int nResult);

class CThread
{
public:
	CThread(void);
	virtual ~CThread(void);
	//判断线程是否繁忙
	bool IsWorking();
	//领取工作
	void DoJob(JobFunction job, WPARAM wParam, LPARAM lParam, JobCallBack cb);
private:
	//设置任务已经完成
	void setJobDone();
	//线程入口
	static DWORD WINAPI threadEntry(LPARAM lParam);

	bool bIsWorking;
	HANDLE hHandle;
	WPARAM wParam;
	LPARAM lParam;
	JobFunction jobFunction; //函数指针
	JobCallBack jobCallBack;

};

