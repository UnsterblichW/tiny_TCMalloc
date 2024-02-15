#include"ConcurrentAlloc.h"

// 线程1执行方法
void Alloc1()
{// 两个线程调用ConncurrentAlloc测试能跑通不
	for (int i = 0; i < 5; ++i)
	{
		ConcurrentAlloc(6);
	}
}

// 线程2执行方法
void Alloc2()
{// 两个线程调用ConncurrentAlloc测试能跑通不
	for (int i = 0; i < 5; ++i)
	{
		ConcurrentAlloc(7);
	}
}

void AllocTest()
{
	std::thread t1(Alloc1);
	t1.join();

	std::thread t2(Alloc2);
	t2.join();
}

void ConcurrentAllocTest1()
{
	void* ptr1 = ConcurrentAlloc(5);
	void* ptr2 = ConcurrentAlloc(8);
	void* ptr3 = ConcurrentAlloc(4);
	void* ptr4 = ConcurrentAlloc(6);
	void* ptr5 = ConcurrentAlloc(3);

	cout << ptr1 << endl;
	cout << ptr2 << endl;
	cout << ptr3 << endl;
	cout << ptr4 << endl;
	cout << ptr5 << endl;
}

void ConcurrentAllocTest2()
{
	for (int i = 0; i < 1024; ++i)
	{
		void* ptr = ConcurrentAlloc(5);
		cout << ptr << endl;
	}

	void* ptr = ConcurrentAlloc(3);
	cout << "-----" << ptr << endl;
}

void TestConcurrentFree1()
{
	void* ptr1 = ConcurrentAlloc(5);
	void* ptr2 = ConcurrentAlloc(8);
	void* ptr3 = ConcurrentAlloc(4);
	void* ptr4 = ConcurrentAlloc(6);
	void* ptr5 = ConcurrentAlloc(3);
	void* ptr6 = ConcurrentAlloc(3);
	void* ptr7 = ConcurrentAlloc(3);

	ConcurrentFree(ptr1);
	ConcurrentFree(ptr2);
	ConcurrentFree(ptr3);
	ConcurrentFree(ptr4);
	ConcurrentFree(ptr5);
	ConcurrentFree(ptr6);
	ConcurrentFree(ptr7);
}

void MultiThreadAlloc1()
{
	std::vector<void*> v;
	for (size_t i = 0; i < 7; ++i)
	{
		void* ptr = ConcurrentAlloc(6);
		v.push_back(ptr);
	}

	for (auto e : v)
	{
		ConcurrentFree(e);
	}
}

void MultiThreadAlloc2()
{
	std::vector<void*> v;
	for (size_t i = 0; i < 7; ++i)
	{
		void* ptr = ConcurrentAlloc(16);
		v.push_back(ptr);
	}

	for (int i = 0; i < 7; ++i)
	{
		ConcurrentFree(v[i]);
	}
}

void TestMultiThread()
{
	std::thread t1(MultiThreadAlloc1);
	std::thread t2(MultiThreadAlloc2);

	t1.join();
	t2.join();
}

void TestAddressShift()
{
	// 两个页号
	PageID id1 = 2000;
	PageID id2 = 2001;
	// 通过页号找id1页的页内偏移
	char* p1 = (char*)(id1 << PAGE_SHIFT);
	char* p2 = (char*)(id2 << PAGE_SHIFT);
	while (p1 < p2)
	{
		cout << (void*)p1 << ":" << ((PageID)p1 >> PAGE_SHIFT) << endl;
		p1 += 8;
	}
}

void BigAlloc()
{
	void* p1 = ConcurrentAlloc(257 * 1024);
	ConcurrentFree(p1);

	void* p2 = ConcurrentAlloc(129 * 8 * 1024);
	ConcurrentFree(p2);
}


//
//// ntimes 一轮申请和释放内存的次数
//// rounds 轮次
//void BenchmarkMalloc(size_t ntimes, size_t nworks, size_t rounds)
//{
//	std::vector<std::thread> vthread(nworks);
//	std::atomic<size_t> malloc_costtime = 0;
//	std::atomic<size_t> free_costtime = 0;
//
//	for (size_t k = 0; k < nworks; ++k)
//	{
//		vthread[k] = std::thread([&, k]() {
//			std::vector<void*> v;
//			v.reserve(ntimes);
//
//			for (size_t j = 0; j < rounds; ++j)
//			{
//				size_t begin1 = clock();
//				for (size_t i = 0; i < ntimes; i++)
//				{
//					v.push_back(malloc(16));
//					//v.push_back(malloc((16 + i) % 8192 + 1));
//				}
//				size_t end1 = clock();
//
//				size_t begin2 = clock();
//				for (size_t i = 0; i < ntimes; i++)
//				{
//					free(v[i]);
//				}
//				size_t end2 = clock();
//				v.clear();
//
//				malloc_costtime += (end1 - begin1);
//				free_costtime += (end2 - begin2);
//			}
//			});
//	}
//
//	for (auto& t : vthread)
//	{
//		t.join();
//	}
//
//	printf("%u个线程并发执行%u轮次，每轮次malloc %u次: 花费：",
//		nworks, rounds, ntimes); cout << malloc_costtime << "ms" << endl;
//
//	printf("%u个线程并发执行%u轮次，每轮次free %u次: 花费：",
//		nworks, rounds, ntimes); cout << free_costtime << "ms" << endl;
//
//	printf("%u个线程并发malloc&free %u次，总计花费：",
//		nworks, nworks * rounds * ntimes); cout << malloc_costtime + free_costtime << "ms" << endl;
//}
//
//
//// 单轮次申请释放次数 线程数 轮次
//void BenchmarkConcurrentMalloc(size_t ntimes, size_t nworks, size_t rounds)
//{
//	std::vector<std::thread> vthread(nworks);
//	std::atomic<size_t> malloc_costtime = 0;
//	std::atomic<size_t> free_costtime = 0;
//
//	for (size_t k = 0; k < nworks; ++k)
//	{
//		vthread[k] = std::thread([&]() {
//			std::vector<void*> v;
//			v.reserve(ntimes);
//
//			for (size_t j = 0; j < rounds; ++j)
//			{
//				size_t begin1 = clock();
//				for (size_t i = 0; i < ntimes; i++)
//				{
//					v.push_back(ConcurrentAlloc(16));
//					//v.push_back(ConcurrentAlloc((16 + i) % 8192 + 1));
//				}
//				size_t end1 = clock();
//
//				size_t begin2 = clock();
//				for (size_t i = 0; i < ntimes; i++)
//				{
//					ConcurrentFree(v[i]);
//				}
//				size_t end2 = clock();
//				v.clear();
//
//				malloc_costtime += (end1 - begin1);
//				free_costtime += (end2 - begin2);
//			}
//			});
//	}
//
//	for (auto& t : vthread)
//	{
//		t.join();
//	}
//
//	printf("%u个线程并发执行%u轮次，每轮次malloc %u次: 花费：",
//		nworks, rounds, ntimes); cout << malloc_costtime << "ms" << endl;
//
//	printf("%u个线程并发执行%u轮次，每轮次free %u次: 花费：",
//		nworks, rounds, ntimes); cout << free_costtime << "ms" << endl;
//
//	printf("%u个线程并发malloc&free %u次，总计花费：",
//		nworks, nworks * rounds * ntimes); cout << malloc_costtime + free_costtime << "ms" << endl;
//}
//
//int main()
//{
//	size_t n = 1000;
//	cout << "==========================================================" << endl;
//	BenchmarkConcurrentMalloc(n, 4, 10);
//	cout << endl << endl;
//
//	BenchmarkMalloc(n, 4, 10);
//	cout << "==========================================================" << endl;
//
//	return 0;
//}


// ntimes 一轮申请和释放内存的次数
// rounds 轮次
void BenchmarkMalloc(size_t ntimes, size_t nworks, size_t rounds)
{
	std::vector<std::thread> vthread(nworks);
	std::atomic<size_t> malloc_costtime = 0;
	std::atomic<size_t> free_costtime = 0;

	for (size_t k = 0; k < nworks; ++k)
	{
		vthread[k] = std::thread([&, k]() {
			std::vector<void*> v;
			v.reserve(ntimes);

			for (size_t j = 0; j < rounds; ++j)
			{
				size_t begin1 = clock();
				for (size_t i = 0; i < ntimes; i++)
				{
					v.push_back(malloc(16));
					//v.push_back(malloc((16 + i) % 8192 + 1));
				}
				size_t end1 = clock();

				size_t begin2 = clock();
				for (size_t i = 0; i < ntimes; i++)
				{
					free(v[i]);
				}
				size_t end2 = clock();
				v.clear();

				malloc_costtime += (end1 - begin1);
				free_costtime += (end2 - begin2);
			}
			});
	}

	for (auto& t : vthread)
	{
		t.join();
	}

	printf("%u个线程并发执行%u轮次，每轮次malloc %u次: 花费：%u ms\n",
		nworks, rounds, ntimes, malloc_costtime.load());

	printf("%u个线程并发执行%u轮次，每轮次free %u次: 花费：%u ms\n",
		nworks, rounds, ntimes, free_costtime.load());

	printf("%u个线程并发malloc&free %u次，总计花费：%u ms\n",
		nworks, nworks * rounds * ntimes, malloc_costtime.load() + free_costtime.load());
}


// 单轮次申请释放次数 线程数 轮次
void BenchmarkConcurrentMalloc(size_t ntimes, size_t nworks, size_t rounds)
{
	std::vector<std::thread> vthread(nworks);
	std::atomic<size_t> malloc_costtime = 0;
	std::atomic<size_t> free_costtime = 0;

	for (size_t k = 0; k < nworks; ++k)
	{
		vthread[k] = std::thread([&]() {
			std::vector<void*> v;
			v.reserve(ntimes);

			for (size_t j = 0; j < rounds; ++j)
			{
				size_t begin1 = clock();
				for (size_t i = 0; i < ntimes; i++)
				{
					v.push_back(ConcurrentAlloc(16));
					//v.push_back(ConcurrentAlloc((16 + i) % 8192 + 1));
				}
				size_t end1 = clock();

				size_t begin2 = clock();
				for (size_t i = 0; i < ntimes; i++)
				{
					ConcurrentFree(v[i]);
				}
				size_t end2 = clock();
				v.clear();

				malloc_costtime += (end1 - begin1);
				free_costtime += (end2 - begin2);
			}
			});
	}

	for (auto& t : vthread)
	{
		t.join();
	}

	printf("%u个线程并发执行%u轮次，每轮次concurrent alloc %u次: 花费：%u ms\n",
		nworks, rounds, ntimes, malloc_costtime.load());

	printf("%u个线程并发执行%u轮次，每轮次concurrent dealloc %u次: 花费：%u ms\n",
		nworks, rounds, ntimes, free_costtime.load());

	printf("%u个线程并发concurrent alloc&dealloc %u次，总计花费：%u ms\n",
		nworks, nworks * rounds * ntimes, malloc_costtime.load() + free_costtime.load());
}


int main()
{
	//BigAlloc();

	//AllocTest();
	//ConcurrentAllocTest1();
	//ConcurrentAllocTest2();

	//TestAddressShift();

	//TestConcurrentFree1();
	//TestMultiThread();

	//void* ptr = ConcurrentAlloc(500 * 1024);

	size_t n = 10000;
	cout << "==========================================================" << endl;
	BenchmarkConcurrentMalloc(n, 4, 10);
	cout << endl << endl;

	BenchmarkMalloc(n, 4, 10);
	cout << "==========================================================" << endl;

	return 0;
}

//#include<iostream>
//using std::min;
//#include<Windows.h>
//
//int main()
//{
//	int a = std::min(10, 20);
//
//	return 0;
//}

//#include <stdio.h>
//#include <cstdlib>
//
//int main() {
//    int a = 10;
//    int b = 20;
//    a = min(a, b);
//    printf("The minimum value is: %d\n", a);
//    return 0;
//}