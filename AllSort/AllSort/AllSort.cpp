// AllSort.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "iostream"
#include <vector>
#include <Windows.h>
#include "AllSort.h"
#include <stdio.h>
#include <algorithm>
#include <functional>

using namespace std;

LARGE_INTEGER freq;
LARGE_INTEGER startTime,stopTime;
double time;

void help(int len,bool Up,int IsRand,int arrType);
void initArr();

int _tmain(int argc, _TCHAR* argv[])
{
	system("color 0A");
	AllSort<int> sort;	//定义排序类对象
	vector<int> arr;	//定义并初始化一个容器，进行数组操作
	int len = 10;		//控制数组长度
	char ans = 'y';
	do
	{
		cout<<"请输入数组初始化类型及元素个数 ：（1为元素完全不重复，2为有大量重复值）"<<endl;
		int arrType = 1;	//1为完全不重复，2为大量重复值
		cin>>arrType>>len;
		sort.InitArr(arr,len,arrType);

		//各大开关
		cout<<"请输入排序类型，0为降序，1为升序"<<endl;
		bool upflag = false;	//控制所有排序的升排或者降排的开关
		cin>>upflag;
		cout<<"请输入数组的随机类型：1为纯随机，2为升序，3为降序，4为小随机"<<endl;
		int isRand = 1;		//1为纯随机，2为升序，3为降序，4为小随机
		cin>>isRand;
		cout<<"是否打印排序结果：0为否，1为是"<<endl;
		bool isPrint = false;	//是否print
		cin>>isPrint;
		bool isMove = true;
		help(len,upflag,isRand,arrType);
		cout<<"/*************************改进冒泡法**************************/"<<endl;
		sort.randArray(arr,len,isRand);
		sort.printArray(arr,isPrint);
		QueryPerformanceCounter(&startTime);
		sort.BubbleSort(arr,1,arr.size() - 1,upflag);
		QueryPerformanceCounter(&stopTime);
		sort.printArray(arr,isPrint);
		time = 1e3*(stopTime.QuadPart - startTime.QuadPart)/freq.QuadPart;
		cout<<"消耗时间"<<time<<"毫秒";
		cout<<"移动次数："<<sort.getSortCount(isMove)<<" 比较次数"<<sort.getSortCount(!isMove)<<endl;

		cout<<"/*****************std::sort()（注：无法统计次数）************/"<<endl;
		sort.beforSort();
		sort.randArray(arr,len,isRand);
		sort.printArray(arr,isPrint);
		QueryPerformanceCounter(&startTime);
		if(upflag)
		{
			std::sort(arr.begin(),arr.end(),std::less<int>());
		}
		else
		{
			std::sort(arr.begin(),arr.end(),std::greater<int>());
		}

		QueryPerformanceCounter(&stopTime);
		sort.printArray(arr,isPrint);
		time = 1e3*(stopTime.QuadPart - startTime.QuadPart)/freq.QuadPart;
		cout<<"消耗时间"<<time<<"毫秒 ";
		cout<<"移动次数："<<sort.getSortCount(isMove)<<" 比较次数"<<sort.getSortCount(!isMove)<<endl;

		cout<<"/**********************插入法************************/"<<endl;
		sort.randArray(arr,len,isRand);	//打乱数组
		sort.printArray(arr,isPrint);
		QueryPerformanceCounter(&startTime);
		sort.InsertSort(arr,0,arr.size() - 1,upflag);
		QueryPerformanceCounter(&stopTime);
		sort.printArray(arr,isPrint);
		time = 1e3*(stopTime.QuadPart - startTime.QuadPart)/freq.QuadPart;
		cout<<"消耗时间："<<time<<"毫秒 ";
		cout<<"移动次数："<<sort.getSortCount(isMove)<<"  比较次数"<<sort.getSortCount(!isMove)<<endl;

		cout<<"/***********************分治法**************************/"<<endl;
		sort.randArray(arr,len,isRand);	//捣乱数组
		sort.printArray(arr,isPrint);
		QueryPerformanceCounter(&startTime);
		sort.MergeSort(arr,0,arr.size() - 1,upflag);
		QueryPerformanceCounter(&stopTime);
		sort.printArray(arr,isPrint);
		time = 1e3*(stopTime.QuadPart - startTime.QuadPart)/freq.QuadPart;
		cout<<"消耗时间"<<time<<"毫秒  ";
		cout<<"移动次数："<<sort.getSortCount(isMove)<<"  比较次数"<<sort.getSortCount(!isMove)<<endl;

		cout<<"/**************************快排法（随机划界元）****************/"<<endl;
		sort.randArray(arr,len,isRand);	//打乱数组
		sort.printArray(arr,isPrint);
		QueryPerformanceCounter(&startTime);
		sort.RandQuickSort(arr,0,arr.size() - 1,upflag);
		QueryPerformanceCounter(&stopTime);
		sort.printArray(arr,isPrint);
		time = 1e3*(stopTime.QuadPart - startTime.QuadPart)/freq.QuadPart;
		cout<<"消耗时间"<<time<<"毫秒 ";
		cout<<"移动次数: "<<sort.getSortCount(isMove)<<" 比较次数"<<sort.getSortCount(!isMove)<<endl;

		cout<<"/***********************快排法（三数取中划界元）*******************/"<<endl;
		sort.randArray(arr,len,isRand);	//打乱数组
		sort.printArray(arr,isPrint);
		QueryPerformanceCounter(&startTime);
		sort.thrWayQuickSort(arr,0,arr.size() - 1,upflag);
		QueryPerformanceCounter(&stopTime);
		sort.printArray(arr,isPrint);
		time = 1e3*(stopTime.QuadPart - startTime.QuadPart)/freq.QuadPart;
		cout<<"消耗时间："<<time<<"毫秒  ";
		cout<<"移动次数："<<sort.getSortCount(isMove)<<"  比较次数"<<sort.getSortCount(!isMove)<<endl;

		cout<<"/***********************快排法（尾端划界元）************************/"<<endl;
		sort.randArray(arr,len,isRand);	//打乱数组
		sort.printArray(arr,isPrint);
		QueryPerformanceCounter(&startTime);
		sort.QuickSort(arr,0,arr.size() - 1,upflag);
		QueryPerformanceCounter(&stopTime);
		sort.printArray(arr,isPrint);
		time = 1e3*(stopTime.QuadPart - startTime.QuadPart) / freq.QuadPart;
		cout<<"消耗时间："<<time<<"毫秒";
		cout<<"移动次数："<<sort.getSortCount(isMove)<<"  比较次数"<<sort.getSortCount(!isMove)<<endl;

		cout<<"/*****************************选择法***************************/"<<endl;
		sort.randArray(arr,len,isRand);	//打乱数组
		sort.printArray(arr,isPrint);
		QueryPerformanceCounter(&startTime);
		sort.SelectSort(arr,0,arr.size() - 1,upflag);
		QueryPerformanceCounter(&stopTime);
		sort.printArray(arr,isPrint);
		time = 1e3*(stopTime.QuadPart - startTime.QuadPart) / freq.QuadPart;
		cout<<"消耗时间："<<time<<"毫秒";
		cout<<"移动次数："<<sort.getSortCount(isMove)<<"  比较次数"<<sort.getSortCount(!isMove)<<endl;

		cout<<"/************************希尔法************************/"<<endl;
		sort.randArray(arr,len,isRand);	//打乱数组
		sort.printArray(arr,isPrint);
		QueryPerformanceCounter(&startTime);
		sort.ShellSort(arr,0,arr.size() - 1,upflag);
		QueryPerformanceCounter(&stopTime);
		sort.printArray(arr,isPrint);
		time = 1e3*(stopTime.QuadPart - startTime.QuadPart) / freq.QuadPart;
		cout<<"消耗时间："<<time<<"毫秒";
		cout<<"移动次数："<<sort.getSortCount(isMove)<<"   比较次数："<<sort.getSortCount(!isMove)<<endl;

		cout<<"/************************堆排序法***********************/"<<endl;
		sort.randArray(arr,len,isRand);		//打乱数组
		sort.printArray(arr,isPrint);
		QueryPerformanceCounter(&startTime);
		sort.HeapSort(arr,upflag);
		QueryPerformanceCounter(&stopTime);
		sort.printArray(arr,isPrint);
		time = 1e3*(stopTime.QuadPart - startTime.QuadPart)/freq.QuadPart;
		cout<<"消耗时间："<<time<<"毫秒   ";
		cout<<"移动次数："<<sort.getSortCount(isMove)<<"   比较次数"<<sort.getSortCount(!isMove)<<endl;


		cout<<"/*************************计数序法***********************/"<<endl;
		sort.randArray(arr,len,isRand);	//打乱数组
		sort.printArray(arr,isPrint);
		QueryPerformanceCounter(&startTime);
		sort.CountSort(arr,arrType,len,upflag);
		QueryPerformanceCounter(&stopTime);
		sort.printArray(arr,isPrint);
		time = 1e3*(stopTime.QuadPart - startTime.QuadPart) /freq.QuadPart;
		cout<<"消耗时间："<<time<<"毫秒  ";
		cout<<"移动次数："<<sort.getSortCount(isMove)<<"  比较次数"<<sort.getSortCount(!isMove)<<endl;

		cout<<"是否继续（y/n)?"<<endl;
		cin>>ans;
		arr.clear();
	}while(ans == 'y');
	system("pause");
	return 0;
}

void help(int len,bool Up,int IsRand,int arrType)
{
	cout<<"/************************综上所述************************/"<<endl;
	cout<<"当前数组元素个数为："<<len<<endl;
	cout<<"原始数组的元素特点："<<endl;
	if(arrType == 1)
	{
		cout<<"  1）无重复值"<<endl;
		cout<<"  2) 值分布：0-"<<len - 1<<endl;
	}
	else if(arrType == 2)
	{
		cout<<"  1)大量重复值"<<endl;
		cout<<"  2)非重复值的分布：0 - 5"<<endl;
	}

	if(IsRand == 1)
	{
		cout<<"  3)随机分布"<<endl;
	}
	else if(IsRand == 2)
	{
		cout<<"  3)有序：升序"<<endl;
	}
	else if(IsRand == 3)
	{
		cout<<"  3)有序：降序"<<endl;
	}
	else if(IsRand == 4)
	{
		cerr<<"  3)小随机（总体上呈有序趋势）"<<endl;
	}
	else
	{
		cerr<<"IsRand参数错误！"<<endl;
	}

	if(Up)
	{
		cout<<"各排序即将执行：升序"<<endl;
	}
	else
	{
		cout<<"各排序即将执行：降序"<<endl;
	}

	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&startTime);
	Sleep(500);
	QueryPerformanceCounter(&stopTime);
	time = 1e3*(stopTime.QuadPart - startTime.QuadPart)/freq.QuadPart;
	cout<<"你的电脑的频率为："<<freq.QuadPart<<endl;
	cout<<"你的电脑执行Sleep(500)消耗的时间为："<<time<<"毫秒"<<endl;
}