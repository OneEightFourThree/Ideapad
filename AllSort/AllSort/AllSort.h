#include "iostream"
#include "vector"
using namespace std;

template<class DataType>
class AllSort
{
public:
	AllSort()
	{
		//�ƶ�������ʼ��
		countSortMove = 0;
		//�Ƚϴ�����ʼ��
		countSortCmp = 0;
		//��ʼ������ʱ�Ĳ��ظ���
		countNum = 5;
	}
	~AllSort()
	{}
	//��ӡ����
	void printArray(vector<DataType> &a,bool isPrint);
	//����Ԫ��
	void swap(DataType *a,DataType *b);
	//��ʼ������
	void InitArr(vector<DataType> &a,int len,int arrType);
	//ð������
	void BubbleSort(vector<DataType> &a,int l,int r,bool Up = true);
	//��������
	void InsertSort(vector<DataType> &a,int l,int r,bool Up = true);
	//��������
	void QuickSort(vector<DataType> &a,int l,int r,bool UP = true);
	//����
	int Partition(vector<DataType> &a,int l,int r,bool Up = true);
	//�����������
	void RandQuickSort(vector<DataType> &a,int l,int r,bool Up = true);
	//�������
	int RandPartition(vector<DataType> &a,int l,int r,bool Up = true);
	//����ȡ�п�������
	void thrWayQuickSort(vector<DataType> &a,int l,int r,bool Up = true);
	//����ȡ�л���
	int thrWayPartition(vector<DataType> &a,int l,int r,bool Up = true);
	//�ֶ���֮����
	void MergeSort(vector<DataType> &a,int l,int r,bool Up = true);
	void Merge(vector<DataType> &a,int p,int q,int r,bool Up = true);
	//��������
	void CountSort(vector<DataType> &a,int arrType,int len,bool Up = true);
	//ϴ�Ʋ����������һ�������е�N��Ԫ��
	void randArray(vector<DataType> &a,unsigned int nmint ,int isRand);
	//ѡ������
	void SelectSort(vector<DataType> &a,int l,int r,bool Up = true);
	//ϣ������
	void ShellSort(vector<DataType> &a,int l,int r,bool Up = true);
	//���е�����
	int Left(int i);
	//���е�����
	int Right(int i);
	//���ֶ�����
	void KeepMaxHeap(vector<DataType> &a,int len,int heapsize,bool Up);
	//����
	void BuildMaxHeap(vector<DataType> &a,bool Up);
	//������
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
		//�ƶ�������ʼ��
		countSortMove = 0;
		//�Ƚϴ�����ʼ��
		countSortCmp = 0;
	}
private:
	//�ƶ�����
	int countSortMove;
	//�Ƚϴ���
	int countSortCmp;
	//��ʼ������ʱ�Ĳ��ظ����ݸ���
	int countNum;
};

//����Ԫ��
template<typename DataType>
void AllSort<DataType>::swap(DataType *a,DataType *b)
{
	DataType temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

//��ʼ������
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

//�������һ������n��Ԫ��
template<typename DataType>
void AllSort<DataType>::randArray(vector<DataType> &a,unsigned int n,int isRand)
{
	if(n > a.size())
	{
		cerr<<"�޷�����ָ��������Ԫ��"<<endl;
		exit(1);
	}
	if(isRand == 1)//�������
	{
		unsigned int index,i;
		for(i = 0;i < n;i++)	//�������е�ÿһ��Ԫ�ض������漴����
		{
			index = rand() % n;	//����0 ��n - 1֮������λ����
			if(index != i)
			{
				swap(&a[i],&a[index]);
			}
		}
	}
	else if(isRand == 2)	//����
	{
		bool upflag = true;
		this->ShellSort(a,0,a.size() - 1,upflag);
	}
	else if(isRand == 3)	//����
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
			index = rand() % gap + i;	//���� i �� j ֮������λ����
			if(index != i && index < n)
			{
				swap(&a[i],&a[index]);
			}
		}
	}
	else
	{
		cerr<<"isRand������������randArray() ����"<<endl;
		return;
	}
}

//��ӡ����
template<typename DataType>
void AllSort<DataType>::printArray(vector<DataType> &a,bool isPrint)
{
	if(isPrint)
	{
		cout<<"�������ҽ��Ϊ��";
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

//ϣ������
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
			int temp = a[i];	//�ݴ�ؼ�����
			int j = i;
			countSortCmp++;
			if(Up)
			{
				while(j - gap >= low && temp < a[j - gap])
				{
					a[j] = a[j - gap];		//����
					j = j - gap;			//ǰ������
					countSortCmp++;
					countSortMove++;
				}
			}
			else
			{
				while(j - gap >= low && temp > a[j - gap])
				{
					a[j] = a[j - gap];	//����
					j = j - gap;		//ǰ������
					countSortCmp++;
					countSortMove++;
				}
			}
			a[j] = temp;
			countSortMove = countSortMove + 2;
		}
	}
}

//����������򻮽纯��
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

//�������������е㺯��
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
//����������е㺯��
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

///��������
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

//��������Ļ��纯��
template<typename DataType>
int AllSort<DataType>::Partition(vector<DataType> &a,int low,int high,bool Up)
{
	int pivotkey = a[high];		//ѡ����Ԫ������׼Ԫ��
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
//�ϲ����򷨣����η���
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

//���η��ĺϲ�����
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
		L[n1] = Max;	//�ڱ�Ԫ��λ��
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
		L[n1] = Min	;//�ڱ�Ԫ��λ��
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

//ѡ������
template<typename DataType>
void AllSort<DataType>::SelectSort(vector<DataType> &a,int low,int high,bool Up)
{
	beforSort();
	DataType min;
	DataType max;

	for(int i = low;i <= high;i++)
	{
		//�ҵ���Сֵ����λ�ã�׼����a[i]������
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
					min = a[j];	//��ǰ��Сֵ
					index = j;	//��ǰ��Сֵ��λ��
					countSortMove++;
				}
			}
			else
			{
				if(a[j] > max)
				{
					max = a[j];	//��ǰ���ֵ
					index = j;	//��ǰ���ֵ��λ��
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
//ð������
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
				if(a[j - 1] > a[j])	//��������
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

//��������
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

//���ֶѵ�����
template <typename DataType>
void AllSort<DataType>::KeepMaxHeap(vector<DataType> &a,int i,int heapsize,bool Up)//ʹa[i]���Ԫ���½����������������Ҫ��Ļ���
{
	int l = Left(i);
	int r = Right(i);
	int largest = 0;
	int min = 0;
	if(Up)
	{
		if(l <= heapsize && a[l] > a[i])	//�����ӱ�
		{
			largest = l;
		}
		else
		{
			largest = i;
		}

		if(r <= heapsize && a[r] > a[largest]) //���ϴ��������ӱ�
		{
			largest = r;
		}
	}
	else
	{
		if(l <= heapsize && a[l] < a[i])	//�����ӱ�
		{
			min = l;
		}
		else
		{
			min = i;
		}
		if(r <= heapsize && a[r] < a[min])	//���ϴ��������ӱ�
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

//�����ѣ����������������
template <typename DataType>
void AllSort<DataType>::BuildMaxHeap(vector<DataType> &a,bool Up)
{
	int heapsize = a.size() - 1;
	for(int i = heapsize / 2;i > 0;i--)
	{
		KeepMaxHeap(a,i,heapsize,Up);	//heapsize / 2��a.size - 1������������Ҷ������ֻ���0 ~ heapsize/2������
	}
}

//������
template <typename DataType>
void AllSort<DataType>::HeapSort(vector<DataType> &a,bool Up)
{
	beforSort();
	BuildMaxHeap(a,Up);	//ʹ�����Ϊ����
	int heapsize = a.size() - 1;
	for(int i = a.size() - 1;i > 0;i--)
	{
		swap(&a[0],&a[i]);
		countSortMove = countSortMove + 3;
		heapsize--;
		KeepMaxHeap(a,0,heapsize,Up);	//���ֶѵ�����
	}
}


//��������
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
	DataType* Cout = new DataType[nLen];	//����ռ䣬���ڼ���
	//��ʼ������Ϊ0
	for(int i = 0;i < k;++i)
	{
		Cout[i] = 0;
	}
	//ͳ��Ԫ�س��ִ���������������Ԫ��a[i]�ĳ��ִ����������������Cout[a[i]]��
	for(int i = 0;i < nLen;++i)
	{
		++Cout[a[i]];
	}
	//ͳ��С�ڵ��ڵ�ǰλ��i��Ԫ�ظ���
	for(int i = 1;i < nLen; ++i)
	{
		Cout[i]+= Cout[i - 1];
	}

	DataType* Sort = new DataType[nLen];		//����ռ䣬���ڴ��������

	for(int i = 0;i < nLen;++i)
	{
		--Cout[a[i]];
		Sort[Cout[a[i]]] = a[i];
	}

	//������������Ƶ�ԭ��������
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
	//�ͷ�����Ŀռ�
	delete[] Cout;
	Cout = NULL;
	delete[] Sort;
	Sort = NULL;
}

