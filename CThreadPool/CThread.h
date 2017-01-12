#pragma once

#include <Windows.h>
#include <stdio.h>

//Ҫ��������
typedef unsigned int(*JobFunction)(WPARAM wParam, LPARAM lParam);
//��������Ļص�����
typedef void(*JobCallBack)(unsigned int nResult);

class CThread
{
public:
	CThread(void);
	virtual ~CThread(void);
	//�ж��߳��Ƿ�æ
	bool IsWorking();
	//��ȡ����
	void DoJob(JobFunction job, WPARAM wParam, LPARAM lParam, JobCallBack cb);
private:
	//���������Ѿ����
	void setJobDone();
	//�߳����
	static DWORD WINAPI threadEntry(LPARAM lParam);

	bool bIsWorking;
	HANDLE hHandle;
	WPARAM wParam;
	LPARAM lParam;
	JobFunction jobFunction; //����ָ��
	JobCallBack jobCallBack;

};

