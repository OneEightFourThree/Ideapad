// AllSort.cpp : �������̨Ӧ�ó������ڵ㡣
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
	AllSort<int> sort;	//�������������
	vector<int> arr;	//���岢��ʼ��һ�������������������
	int len = 10;		//�������鳤��
	char ans = 'y';
	do
	{
		cout<<"�����������ʼ�����ͼ�Ԫ�ظ��� ����1ΪԪ����ȫ���ظ���2Ϊ�д����ظ�ֵ��"<<endl;
		int arrType = 1;	//1Ϊ��ȫ���ظ���2Ϊ�����ظ�ֵ
		cin>>arrType>>len;
		sort.InitArr(arr,len,arrType);

		//���󿪹�
		cout<<"�������������ͣ�0Ϊ����1Ϊ����"<<endl;
		bool upflag = false;	//����������������Ż��߽��ŵĿ���
		cin>>upflag;
		cout<<"�����������������ͣ�1Ϊ�������2Ϊ����3Ϊ����4ΪС���"<<endl;
		int isRand = 1;		//1Ϊ�������2Ϊ����3Ϊ����4ΪС���
		cin>>isRand;
		cout<<"�Ƿ��ӡ��������0Ϊ��1Ϊ��"<<endl;
		bool isPrint = false;	//�Ƿ�print
		cin>>isPrint;
		bool isMove = true;
		help(len,upflag,isRand,arrType);
		cout<<"/*************************�Ľ�ð�ݷ�**************************/"<<endl;
		sort.randArray(arr,len,isRand);
		sort.printArray(arr,isPrint);
		QueryPerformanceCounter(&startTime);
		sort.BubbleSort(arr,1,arr.size() - 1,upflag);
		QueryPerformanceCounter(&stopTime);
		sort.printArray(arr,isPrint);
		time = 1e3*(stopTime.QuadPart - startTime.QuadPart)/freq.QuadPart;
		cout<<"����ʱ��"<<time<<"����";
		cout<<"�ƶ�������"<<sort.getSortCount(isMove)<<" �Ƚϴ���"<<sort.getSortCount(!isMove)<<endl;

		cout<<"/*****************std::sort()��ע���޷�ͳ�ƴ�����************/"<<endl;
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
		cout<<"����ʱ��"<<time<<"���� ";
		cout<<"�ƶ�������"<<sort.getSortCount(isMove)<<" �Ƚϴ���"<<sort.getSortCount(!isMove)<<endl;

		cout<<"/**********************���뷨************************/"<<endl;
		sort.randArray(arr,len,isRand);	//��������
		sort.printArray(arr,isPrint);
		QueryPerformanceCounter(&startTime);
		sort.InsertSort(arr,0,arr.size() - 1,upflag);
		QueryPerformanceCounter(&stopTime);
		sort.printArray(arr,isPrint);
		time = 1e3*(stopTime.QuadPart - startTime.QuadPart)/freq.QuadPart;
		cout<<"����ʱ�䣺"<<time<<"���� ";
		cout<<"�ƶ�������"<<sort.getSortCount(isMove)<<"  �Ƚϴ���"<<sort.getSortCount(!isMove)<<endl;

		cout<<"/***********************���η�**************************/"<<endl;
		sort.randArray(arr,len,isRand);	//��������
		sort.printArray(arr,isPrint);
		QueryPerformanceCounter(&startTime);
		sort.MergeSort(arr,0,arr.size() - 1,upflag);
		QueryPerformanceCounter(&stopTime);
		sort.printArray(arr,isPrint);
		time = 1e3*(stopTime.QuadPart - startTime.QuadPart)/freq.QuadPart;
		cout<<"����ʱ��"<<time<<"����  ";
		cout<<"�ƶ�������"<<sort.getSortCount(isMove)<<"  �Ƚϴ���"<<sort.getSortCount(!isMove)<<endl;

		cout<<"/**************************���ŷ����������Ԫ��****************/"<<endl;
		sort.randArray(arr,len,isRand);	//��������
		sort.printArray(arr,isPrint);
		QueryPerformanceCounter(&startTime);
		sort.RandQuickSort(arr,0,arr.size() - 1,upflag);
		QueryPerformanceCounter(&stopTime);
		sort.printArray(arr,isPrint);
		time = 1e3*(stopTime.QuadPart - startTime.QuadPart)/freq.QuadPart;
		cout<<"����ʱ��"<<time<<"���� ";
		cout<<"�ƶ�����: "<<sort.getSortCount(isMove)<<" �Ƚϴ���"<<sort.getSortCount(!isMove)<<endl;

		cout<<"/***********************���ŷ�������ȡ�л���Ԫ��*******************/"<<endl;
		sort.randArray(arr,len,isRand);	//��������
		sort.printArray(arr,isPrint);
		QueryPerformanceCounter(&startTime);
		sort.thrWayQuickSort(arr,0,arr.size() - 1,upflag);
		QueryPerformanceCounter(&stopTime);
		sort.printArray(arr,isPrint);
		time = 1e3*(stopTime.QuadPart - startTime.QuadPart)/freq.QuadPart;
		cout<<"����ʱ�䣺"<<time<<"����  ";
		cout<<"�ƶ�������"<<sort.getSortCount(isMove)<<"  �Ƚϴ���"<<sort.getSortCount(!isMove)<<endl;

		cout<<"/***********************���ŷ���β�˻���Ԫ��************************/"<<endl;
		sort.randArray(arr,len,isRand);	//��������
		sort.printArray(arr,isPrint);
		QueryPerformanceCounter(&startTime);
		sort.QuickSort(arr,0,arr.size() - 1,upflag);
		QueryPerformanceCounter(&stopTime);
		sort.printArray(arr,isPrint);
		time = 1e3*(stopTime.QuadPart - startTime.QuadPart) / freq.QuadPart;
		cout<<"����ʱ�䣺"<<time<<"����";
		cout<<"�ƶ�������"<<sort.getSortCount(isMove)<<"  �Ƚϴ���"<<sort.getSortCount(!isMove)<<endl;

		cout<<"/*****************************ѡ��***************************/"<<endl;
		sort.randArray(arr,len,isRand);	//��������
		sort.printArray(arr,isPrint);
		QueryPerformanceCounter(&startTime);
		sort.SelectSort(arr,0,arr.size() - 1,upflag);
		QueryPerformanceCounter(&stopTime);
		sort.printArray(arr,isPrint);
		time = 1e3*(stopTime.QuadPart - startTime.QuadPart) / freq.QuadPart;
		cout<<"����ʱ�䣺"<<time<<"����";
		cout<<"�ƶ�������"<<sort.getSortCount(isMove)<<"  �Ƚϴ���"<<sort.getSortCount(!isMove)<<endl;

		cout<<"/************************ϣ����************************/"<<endl;
		sort.randArray(arr,len,isRand);	//��������
		sort.printArray(arr,isPrint);
		QueryPerformanceCounter(&startTime);
		sort.ShellSort(arr,0,arr.size() - 1,upflag);
		QueryPerformanceCounter(&stopTime);
		sort.printArray(arr,isPrint);
		time = 1e3*(stopTime.QuadPart - startTime.QuadPart) / freq.QuadPart;
		cout<<"����ʱ�䣺"<<time<<"����";
		cout<<"�ƶ�������"<<sort.getSortCount(isMove)<<"   �Ƚϴ�����"<<sort.getSortCount(!isMove)<<endl;

		cout<<"/************************������***********************/"<<endl;
		sort.randArray(arr,len,isRand);		//��������
		sort.printArray(arr,isPrint);
		QueryPerformanceCounter(&startTime);
		sort.HeapSort(arr,upflag);
		QueryPerformanceCounter(&stopTime);
		sort.printArray(arr,isPrint);
		time = 1e3*(stopTime.QuadPart - startTime.QuadPart)/freq.QuadPart;
		cout<<"����ʱ�䣺"<<time<<"����   ";
		cout<<"�ƶ�������"<<sort.getSortCount(isMove)<<"   �Ƚϴ���"<<sort.getSortCount(!isMove)<<endl;


		cout<<"/*************************������***********************/"<<endl;
		sort.randArray(arr,len,isRand);	//��������
		sort.printArray(arr,isPrint);
		QueryPerformanceCounter(&startTime);
		sort.CountSort(arr,arrType,len,upflag);
		QueryPerformanceCounter(&stopTime);
		sort.printArray(arr,isPrint);
		time = 1e3*(stopTime.QuadPart - startTime.QuadPart) /freq.QuadPart;
		cout<<"����ʱ�䣺"<<time<<"����  ";
		cout<<"�ƶ�������"<<sort.getSortCount(isMove)<<"  �Ƚϴ���"<<sort.getSortCount(!isMove)<<endl;

		cout<<"�Ƿ������y/n)?"<<endl;
		cin>>ans;
		arr.clear();
	}while(ans == 'y');
	system("pause");
	return 0;
}

void help(int len,bool Up,int IsRand,int arrType)
{
	cout<<"/************************��������************************/"<<endl;
	cout<<"��ǰ����Ԫ�ظ���Ϊ��"<<len<<endl;
	cout<<"ԭʼ�����Ԫ���ص㣺"<<endl;
	if(arrType == 1)
	{
		cout<<"  1�����ظ�ֵ"<<endl;
		cout<<"  2) ֵ�ֲ���0-"<<len - 1<<endl;
	}
	else if(arrType == 2)
	{
		cout<<"  1)�����ظ�ֵ"<<endl;
		cout<<"  2)���ظ�ֵ�ķֲ���0 - 5"<<endl;
	}

	if(IsRand == 1)
	{
		cout<<"  3)����ֲ�"<<endl;
	}
	else if(IsRand == 2)
	{
		cout<<"  3)��������"<<endl;
	}
	else if(IsRand == 3)
	{
		cout<<"  3)���򣺽���"<<endl;
	}
	else if(IsRand == 4)
	{
		cerr<<"  3)С����������ϳ��������ƣ�"<<endl;
	}
	else
	{
		cerr<<"IsRand��������"<<endl;
	}

	if(Up)
	{
		cout<<"�����򼴽�ִ�У�����"<<endl;
	}
	else
	{
		cout<<"�����򼴽�ִ�У�����"<<endl;
	}

	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&startTime);
	Sleep(500);
	QueryPerformanceCounter(&stopTime);
	time = 1e3*(stopTime.QuadPart - startTime.QuadPart)/freq.QuadPart;
	cout<<"��ĵ��Ե�Ƶ��Ϊ��"<<freq.QuadPart<<endl;
	cout<<"��ĵ���ִ��Sleep(500)���ĵ�ʱ��Ϊ��"<<time<<"����"<<endl;
}