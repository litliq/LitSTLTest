#include "windows.h"
#include "iostream"
#include "StlPtrTest.h"

#include <memory>   // 智能指针
#include <thread>
#include <mutex>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <algorithm>



using namespace std;


// 智能指针
void AutoPtrTest()
{
	std::auto_ptr<CStlPtrTest> ptr(new CStlPtrTest());
	ptr->PrintName();
}

// 共享智能指针
void SharedPtrTest()
{
	std::shared_ptr<CStlPtrTest> ptr(new CStlPtrTest());
	cout << "ptr references num: " << ptr.use_count() << endl;

	std::shared_ptr<CStlPtrTest> ptr2(new CStlPtrTest());
	cout << "ptr2 references num: " << ptr2.use_count() << endl;

	std::shared_ptr<CStlPtrTest> ptr3 = ptr;
	cout << "ptr3 references num: " << ptr3.use_count() << endl;

	ptr.reset();

	cout << "ptr reset, ptr3 references num: " << ptr3.use_count() << endl;
	ptr3->PrintName();

	ptr3.reset();
	cout << "ptr3 reset, ptr3 references num: " << ptr3.use_count() << endl;
}

// 线程函数
void ThreadTest(int iTest)
{
	std::mutex mutex;
	std::lock_guard<std::mutex> lock(mutex);
	Sleep(1000);
	cout << "ThreadTest: " << iTest << endl;
}

// 线程和锁
void ThreadAndLockTest()
{
	cout << "thread start\n";
	std::thread thread(&ThreadTest, 13);
	thread.join();    // 结合
//	thread.detach();  // 分离
	cout << "thread end\n\n";
}

// 时间
void DateTest()
{
	std::chrono::system_clock::time_point tp = std::chrono::system_clock::now();
	std::time_t tmCur = std::chrono::system_clock::to_time_t(tp);

	tm *tmPtr = std::localtime(&tmCur);
	cout << std::put_time(tmPtr, "%Y-%m-%d %X") << endl;

	std::chrono::high_resolution_clock::time_point tp2 = std::chrono::high_resolution_clock::now();
	Sleep(1000);
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - tp);
	cout << time_span.count() << endl << endl;
}

// 快速排序
int SortComp(int iFisrt, int iSecond)
{
	// 从大到小排序
	return iFisrt > iSecond;
}

void SortTest()
{
	srand((unsigned)time(0)); // 随机种子

	const int iNum = 10;
	int szVal[iNum] = {0};
	printf("before sort, val: \n");
	int i = 0;
	for (; i < iNum; i++)
	{
		szVal[i] = rand() % 100;
		if (0 == i)
		{
			printf("%d", szVal[i]);
		}
		else
		{
			printf(",%d", szVal[i]);
		}	
	}

	// 排序
	std::sort(szVal, szVal + iNum, SortComp);

	printf("\nafter sort,val: \n");
	for (i = 0; i < iNum; i++)
	{
		if (0 == i)
		{
			printf("%d", szVal[i]);
		}
		else
		{
			printf(",%d", szVal[i]);
		}	
	}
}

int main()
{
	cout << "Hello STL\n\n";

	// 智能指针
	AutoPtrTest();
	cout << endl;

	// 共享智能指针
	SharedPtrTest();
	cout << endl;

	// 线程和锁
	ThreadAndLockTest();

	// 时间
	DateTest();

	// 排序
	SortTest();

	cout << endl << endl;
	system("pause");
}