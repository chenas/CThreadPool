#include "ThreadPoolMgrt.h"
#include <stdio.h>

//任务函数
unsigned int jobFunc(WPARAM x, LPARAM y)
{
	Sleep(2000);
	return x+y;
}

//回调函数
void callBack(unsigned int rtn)
{
	printf("result %d \n", rtn);
}

int main()
{
	CThreadPoolMgrt* pool = new CThreadPoolMgrt(4,10);
	while (true)
	{
		printf("Pool Size: %d \n", pool->GetPoolSize());
		while(pool->PushJob(jobFunc, 100, 200, callBack) == false){}
		while(pool->PushJob(jobFunc, 200, 200, callBack) == false){}
		while(pool->PushJob(jobFunc, 300, 200, callBack) == false){}
		while(pool->PushJob(jobFunc, 400, 200, callBack) == false){}
		Sleep(1000);
	}

	return 0;
}