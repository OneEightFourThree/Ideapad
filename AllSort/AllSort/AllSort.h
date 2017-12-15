#include "iostream"
#include "vector"
using namespace std;

template<class DataType>
class AllSort
{
public:
	AllSort()
	{
		//移动次数初始化
		countSortMove = 0;
		//比较次数初始化
		countSortCmp = 0;
		//初始化数据时的不重复数
		countNum = 5;
	}
	~AllSort()
	{}
	//打印数组
	void printArray(vector<DataType> &a,bool isPrint);
	//交换元素
	void swap(DataType *a,DataType *b);
	//初始化数组
	void InitArr(vector<DataType> &a,int len,int arrType);
	//冒泡排序法
	void BubbleSort(vector<DataType> &a,int l,int r,bool Up = true);
	//插入排序法
	void InsertSort(vector<DataType> &a,int l,int r,bool Up = true);
	//快速排序法
	void QuickSort(vector<DataType> &a,int l,int r,bool UP = true);
	//划界
	int Partition(vector<DataType> &a,int l,int r,bool Up = true);
	//随机快速排序法
	void RandQuickSort(vector<DataType> &a,int l,int r,bool Up = true);
	//随机划界
	int RandPartition(vector<DataType> &a,int l,int r,bool Up = true);
	//三者取中快速排序法
	void thrWayQuickSort(vector<DataType> &a,int l,int r,bool Up = true);
	//三者取中划界
	int thrWayPartition(vector<DataType> &a,int l,int r,bool Up = true);
	//分而治之排序法
	void MergeSort(vector<DataType> &a,int l,int r,bool Up = true);
	void Merge(vector<DataType> &a,int p,int q,int r,bool Up = true);
	//计数排序
	void CountSort(vector<DataType> &a,int arrType,int len,bool Up = true);
	//洗牌策略随机打乱一个数组中的N个元素
	void randArray(vector<DataType> &a,unsigned int nmint ,int isRand);
	//选择排序法
	void SelectSort(vector<DataType> &a,int l,int r,bool Up = true);
	//希尔排序
	void ShellSort(vector<DataType> &a,int l,int r,bool Up = true);
	//堆中的左子
	int Left(int i);
	//堆中的右子
	int Right(int i);
	//保持堆性质
	void KeepMaxHeap(vector<DataType> &a,int len,int heapsize,bool Up);
	//建堆
	void BuildMaxHeap(vector<DataType> &a,bool Up);
	//堆排序
	void HeapSort(vector<DataType> &a,bool Up);
	int getSortCount(bool IsMove)
	{
		if(IsMove)
		{
			return countSortMove;
		}
		else
		{
			return countSortCmp;
		}
	}
	void beforSort()
	{
		//移动次数初始化
		countSortMove = 0;
		//比较次数初始化
		countSortCmp = 0;
	}
private:
	//移动次数
	int countSortMove;
	//比较次数
	int countSortCmp;
	//初始化数据时的不重复数据个数
	int countNum;
};

//交换元素
template<typename DataType>
void AllSort<DataType>::swap(DataType *a,DataType *b)
{
	DataType temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

//初始化数组
template<typename DataType>
void AllSort<DataType>::InitArr(vector<DataType> &a,int len,int arrType)
{
	if(arrType == 1)
	{
		for(int i = 0; i < len; i++)
			a.push_back(i);
	}
	else if(arrType == 2)
	{
		for(int i = 0;i < len; i++)
		{
			int key = i % countNum;
			a.push_back(key);
		}
	}
}

//随机打乱一个数组n个元素
template<typename DataType>
void AllSort<DataType>::randArray(vector<DataType> &a,unsigned int n,int isRand)
{
	if(n > a.size())
	{
		cerr<<"无法打乱指定数量的元素"<<endl;
		exit(1);
	}
	if(isRand == 1)//随机打乱
	{
		unsigned int index,i;
		for(i = 0;i < n;i++)	//将数组中的每一个元素都进行随即打乱
		{
			index = rand() % n;	//产生0 到n - 1之间的随机位置数
			if(index != i)
			{
				swap(&a[i],&a[index]);
			}
		}
	}
	else if(isRand == 2)	//升序
	{
		bool upflag = true;
		this->ShellSort(a,0,a.size() - 1,upflag);
	}
	else if(isRand == 3)	//降序
	{
		bool upflag = false;
		this->ShellSort(a,0,a.size() - 1,upflag);
	}
	else if(isRand == 4)
	{
		unsigned int gap = 5;
		unsigned int index,i;
		for(i = 0;i < n;i++)
		{
			index = rand() % gap + i;	//产生 i 到 j 之间的随机位置数
			if(index != i && index < n)
			{
				swap(&a[i],&a[index]);
			}
		}
	}
	else
	{
		cerr<<"isRand参数错误！来自randArray() 函数"<<endl;
		return;
	}
}

//打印数组
template<typename DataType>
void AllSort<DataType>::printArray(vector<DataType> &a,bool isPrint)
{
	if(isPrint)
	{
		cout<<"排序或打乱结果为：";
		for(unsigned int i = 0;i < a.size();i++)
		{
			cout<<a[i]<<" ";
			if((i + 1) % 27 == 0)
			{
				cout<<endl;
			}
		}
		cout<<endl;
	}
}

//希尔排序
template<typename DataType>
void AllSort<DataType>::ShellSort(vector<DataType> &a,int low,int high,bool Up)
{
	beforSort();
	int gap = high - low + 1;
	while(gap > 1)
	{
		gap = gap / 3 + 1;
		for(int i = low + gap;i <= high;++i)
		{
			int temp = a[i];	//暂存关键数据
			int j = i;
			countSortCmp++;
			if(Up)
			{
				while(j - gap >= low && temp < a[j - gap])
				{
					a[j] = a[j - gap];		//后移
					j = j - gap;			//前置索引
					countSortCmp++;
					countSortMove++;
				}
			}
			else
			{
				while(j - gap >= low && temp > a[j - gap])
				{
					a[j] = a[j - gap];	//后移
					j = j - gap;		//前置索引
					countSortCmp++;
					countSortMove++;
				}
			}
			a[j] = temp;
			countSortMove = countSortMove + 2;
		}
	}
}

//随机快速排序划界函数
int stepRandQuickSort = 1;
template<typename DataType>
void AllSort<DataType>::RandQuickSort(vector<DataType> &a,int low,int high,bool Up)
{
	int pivotKey = 0;
	if(stepRandQuickSort == 1)
	{
		beforSort();
		stepRandQuickSort = 0;
	}
	if(low < high)
	{
		pivotKey = RandPartition(a,low,high,Up);
		RandQuickSort(a,low,pivotKey-1,Up);
		RandQuickSort(a,pivotKey+1,high,Up);
	}
}

//随机快速排序的中点函数
template <typename DataType>
int AllSort<DataType>::RandPartition(vector<DataType> &a,int low,int high,bool Up)
{
	int randPivotKey = rand() % (high - low + 1) + low;
	this->swap(&a[randPivotKey],&a[high]);
	countSortMove = countSortMove + 3;
	return Partition(a,low,high,Up);
}

int stepthrWayQuickSort = 1;
template<typename DataType>
void AllSort<DataType>::thrWayQuickSort(vector<DataType> &a,int low,int high,bool Up)
{
	if(stepthrWayQuickSort == 1)
	{
		beforSort();
		stepthrWayQuickSort = 0;
	}
	int pivotKey = 0;
	if(low < high)
	{
		pivotKey = thrWayPartition(a,low,high,Up);
		thrWayQuickSort(a,low,pivotKey - 1,Up);
		thrWayQuickSort(a,pivotKey + 1,high,Up);
	}
}
//快速排序的中点函数
template<typename DataType>
int AllSort<DataType>::thrWayPartition(vector<DataType> &a,int low,int high,bool Up)
{
	int PivotKey1 = rand() % (high - low + 1) + low;
	int PivotKey2 = rand() % (high - low + 1) + low;
	int PivotKey3 = rand() % (high - low + 1) + low;

	int midkey = PivotKey1;
	if(PivotKey1 <= PivotKey2 && PivotKey2 <= PivotKey3)
	{
		midkey = PivotKey2;
		countSortCmp = countSortCmp + 2;
	}
	else if(PivotKey2 <= PivotKey1 && PivotKey1 <= PivotKey3)
	{
		midkey = PivotKey1;
		countSortCmp = countSortCmp + 2;
	}else 
	{
		midkey = PivotKey3;
	}
	this->swap(&a[midkey],&a[high]);
	countSortMove = countSortMove + 3;
	return Partition(a,low,high,Up);
}

///快速排序
int stepQuickSort = 1;
template <typename DataType>
void AllSort<DataType>::QuickSort(vector<DataType> &a,int low,int high,bool Up)
{
	if(stepQuickSort == 1)
	{
		beforSort();
		stepQuickSort = 0;
	}
	int mid = 0;
	if(low < high)
	{
		mid = Partition(a,low,high,Up);
		QuickSort(a,low,mid - 1,Up);
		QuickSort(a,mid + 1,high,Up);
	}
}

//快速排序的划界函数
template<typename DataType>
int AllSort<DataType>::Partition(vector<DataType> &a,int low,int high,bool Up)
{
	int pivotkey = a[high];		//选择主元，即基准元素
	int i = low - 1;
	if(Up)
	{
		for(int j = low;j < high;j++)
		{
			countSortCmp++;
			if(a[j] < pivotkey && i != j)
			{
				i++;
				swap(&a[i],&a[j]);
				countSortMove = countSortMove + 3;
			}
		}
	}
	else
	{
		for(int j = low; j < high;j++)
		{
			countSortCmp++;
			if(a[j] > pivotkey)
			{
				i++;
				swap(&a[i],&a[j]);
				countSortMove = countSortMove + 3;
			}
		}
	}
	i++;
	swap(&a[i],&a[high]);
	countSortMove = countSortMove + 3;
	return i;
}

int stepMerge = 1;
//合并排序法（分治法）
template <typename DataType>
void AllSort<DataType>::MergeSort(vector<DataType> &a,int low,int high,bool Up)
{
	if(stepMerge = 1)
	{
		beforSort();
		stepMerge = 0;
	}
	if(low < high)
	{
		int mid = (low + high) / 2;
		MergeSort(a,low,mid,Up);
		MergeSort(a,mid + 1,high,Up);
		Merge(a,low,mid,high,Up);
	}

}

//分治法的合并函数
template <typename DataType>
void AllSort<DataType>::Merge(vector<DataType> &a,int low,int mid,int high,bool Up)
{
	int n1 = mid - low + 1,n2 = high - mid;
	long Max = 99999999;
	long Min = -99999999;
	int *L = new int[n1 + 1];
	int *R = new int[n2 + 2];
	if(L == NULL || R == NULL)
	{
		exit(1);
	}
	int i = 0;
	for(;i < n1;i++)
	{
		L[i] = a[low + i];
		countSortMove++;
	}
	int j = 0;
	for(;j < n2;j++)
	{
		R[j] = a[mid + j + 1];
		countSortMove++;
	}

	i = 0,j = 0;
	int k = 0;
	if(Up)
	{
		L[n1] = Max;	//哨兵元素位置
		R[n2] = Max;
		for(k = low;k <= high;k++)
		{
			if(L[i] <= R[j])
			{
				a[k] = L[i];
				i++;
				countSortMove++;
			}
			else
			{
				a[k] = R[j];
				j++;
				countSortMove++;
			}
			countSortCmp++;
		}
	}
	else
	{
		L[n1] = Min	;//哨兵元素位置
		R[n2] = Min;	//
		for(k = low;k <= high; k++)
		{
			if(L[i] >= R[j])
			{
				a[k] = L[i];
				i++;
				countSortMove++;
			}
			else
			{
				a[k] = R[j];
				j++;
				countSortMove++;
			}
			countSortCmp++;
		}
	}
	delete[]L;
	delete[]R;
}

//选择排序法
template<typename DataType>
void AllSort<DataType>::SelectSort(vector<DataType> &a,int low,int high,bool Up)
{
	beforSort();
	DataType min;
	DataType max;

	for(int i = low;i <= high;i++)
	{
		//找到最小值及其位置（准备与a[i]调换）
		min = a[i];
		max = a[i];
		int index = i;
		for(int j = i + 1; j <= high; j++)
		{
			countSortCmp++;
			if(Up)
			{
				if(a[j] < min)
				{
					min = a[j];	//当前最小值
					index = j;	//当前最小值的位置
					countSortMove++;
				}
			}
			else
			{
				if(a[j] > max)
				{
					max = a[j];	//当前最大值
					index = j;	//当前最大值的位置
					countSortMove++;
				}
			}
		}
		if(Up)
		{
			swap(&a[i],&a[index]);
			countSortMove = countSortMove + 3;
		}
		else
		{
			swap(&a[i],&a[index]);
			countSortMove = countSortMove + 3;
		}
	}
}
//冒泡排序
template<typename DataType>
void AllSort<DataType>::BubbleSort(vector<DataType> &a,int l,int r,bool Up)
{
	beforSort();
	bool flag = false;
	for(int i = l;i < r;i++)
	{
		flag = false;
		for(int j = r ; j >=  i + 1;j--)
		{
			countSortCmp++;
			if(Up)
			{
				if(a[j - 1] > a[j])	//调换次序
				{
					this->swap(&a[j - 1],&a[j]);
					countSortMove = countSortMove + 3;
					flag = true;
				}
			}
			else
			{
				if(a[j - 1] < a[j])
				{
					this->swap(&a[j - 1],&a[j]);
					countSortMove = countSortMove + 3;
					flag = true;
				}
			}
		}
		if(!flag)
		{
			break;
		}
	}
}

//插入排序
template <typename DataType>
void AllSort<DataType>::InsertSort(vector<DataType> &a,int l,int r,bool Up)
{
	beforSort();
	DataType key;
	if(Up)
	{
		for(int i = l + 1; i <= r;i++)
		{
			key = a[i];
			int j = i - 1;
			countSortCmp++;
			while(j >= 1 && a[j] > key)
			{
				a[j + 1] = a[j];
				j--;
				countSortMove++;
				countSortCmp++;
			}
			a[j + 1] = key;
			countSortMove = countSortMove + 2;
		}
	}
	else
	{
		for(int i = l + 1;i <= r;i++)
		{
			key = a[i];
			int j = i - 1;
			countSortCmp++;
			while(j >= 1 && a[j] < key)
			{
				a[j + 1] = a[j];
				j--;
				countSortMove++;
				countSortCmp++;
			}
			a[j + 1] = key;
			countSortMove = countSortMove + 2;
		}
	}
}




template<typename DataType>
int AllSort<DataType>::Left(int i)
{
	return 2 * i + 1;
}

template <typename DataType>
int AllSort<DataType>::Right(int i)
{
	return 2 * i + 2;
}

//保持堆的性质
template <typename DataType>
void AllSort<DataType>::KeepMaxHeap(vector<DataType> &a,int i,int heapsize,bool Up)//使a[i]这个元素下降（如果不满足最大根要求的话）
{
	int l = Left(i);
	int r = Right(i);
	int largest = 0;
	int min = 0;
	if(Up)
	{
		if(l <= heapsize && a[l] > a[i])	//与左子比
		{
			largest = l;
		}
		else
		{
			largest = i;
		}

		if(r <= heapsize && a[r] > a[largest]) //将较大者与右子比
		{
			largest = r;
		}
	}
	else
	{
		if(l <= heapsize && a[l] < a[i])	//与左子比
		{
			min = l;
		}
		else
		{
			min = i;
		}
		if(r <= heapsize && a[r] < a[min])	//将较大者与右子比
		{
			min = r;
		}
	}

	countSortCmp = countSortCmp+2;
	if(Up)
	{
		if(largest != i)
		{
			swap(&a[i],&a[largest]);
			countSortMove = countSortMove + 3;
			KeepMaxHeap(a,largest,heapsize,Up);
		}
	}
	else
	{
		if(min != i)
		{
			swap(&a[i],&a[min]);
			countSortMove = countSortMove + 3;
			KeepMaxHeap(a,min,heapsize,Up);
		}
	}

}

//创建堆，将数组调整成最大堆
template <typename DataType>
void AllSort<DataType>::BuildMaxHeap(vector<DataType> &a,bool Up)
{
	int heapsize = a.size() - 1;
	for(int i = heapsize / 2;i > 0;i--)
	{
		KeepMaxHeap(a,i,heapsize,Up);	//heapsize / 2到a.size - 1的整数都是树叶，所以只需对0 ~ heapsize/2作处理
	}
}

//堆排序
template <typename DataType>
void AllSort<DataType>::HeapSort(vector<DataType> &a,bool Up)
{
	beforSort();
	BuildMaxHeap(a,Up);	//使数组成为最大堆
	int heapsize = a.size() - 1;
	for(int i = a.size() - 1;i > 0;i--)
	{
		swap(&a[0],&a[i]);
		countSortMove = countSortMove + 3;
		heapsize--;
		KeepMaxHeap(a,0,heapsize,Up);	//保持堆的性质
	}
}


//计数排序
template <typename DataType>
void AllSort<DataType>::CountSort(vector<DataType> &a,int arrType,int len,bool Up)
{
	int nLen = len;
	int k = 0;
	if(arrType == 1)
	{
		k = nLen;
	}
	else
	{
		k = countNum;
	}
	countSortCmp = 0;
	DataType* Cout = new DataType[nLen];	//申请空间，用于计数
	//初始化计数为0
	for(int i = 0;i < k;++i)
	{
		Cout[i] = 0;
	}
	//统计元素出现次数计数。即数组元素a[i]的出现次数，将其结果存放在Cout[a[i]]中
	for(int i = 0;i < nLen;++i)
	{
		++Cout[a[i]];
	}
	//统计小于等于当前位置i的元素个数
	for(int i = 1;i < nLen; ++i)
	{
		Cout[i]+= Cout[i - 1];
	}

	DataType* Sort = new DataType[nLen];		//申请空间，用于存放排序结果

	for(int i = 0;i < nLen;++i)
	{
		--Cout[a[i]];
		Sort[Cout[a[i]]] = a[i];
	}

	//排序结束，复制到原来数组中
	if(Up == true)
	{
		for(int i = 0;i < nLen;++i)
		{
			a[i] = Sort[i];
		}
	}
	else
	{
		for(int i = 0;i < nLen;++i)
		{
			a[i] = Sort[nLen - i - 1];
		}
	}
	//释放申请的空间
	delete[] Cout;
	Cout = NULL;
	delete[] Sort;
	Sort = NULL;
}

