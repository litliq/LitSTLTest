#include "windows.h"
#include "iostream"
#include "StlPtrTest.h"

#include <memory>   // 智能指针
#include <thread>
#include <mutex>
#include <chrono>
#include <ctime>
#include <iomanip>



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

	cout << endl << endl;
	system("pause");
}