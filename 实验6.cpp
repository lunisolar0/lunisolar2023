#include <iostream>

using namespace std;

int comparisons = 0, accesses = 0; //数据比较次数，数组访问次数

typedef struct List
{
	int a[100] = {}; //存储数组
	int length = 0; //排序表长度
}List;

//顺序表录入
void List_In(List& L)
{
	cout << "请输入顺序表长度：";
	cin >> L.length;
	cout << "请输入顺序表存储的数据(以空格隔开)：" << endl;
	for (int i = 0; i < L.length; i++)
		cin >> L.a[i];
}

//顺序表输出
void List_out(List L)
{
	cout << "排序结果：";
	for (int i = 0; i < L.length; i++)
		cout << L.a[i] << " ";
	cout << endl;
	cout << "数据比较次数：" << comparisons << endl;
	cout << "数组访问次数：" << accesses << endl;
}

//直接插入排序
void InsertionSort(List& L)
{
	for (int i = 1; i < L.length; i++)
	{ //从第二个元素开始遍历
		for (int j = i; j && L.a[j - 1] > L.a[j]; j--)
		{ //通过交换相邻元素来将插入元素插入至对应位置
			swap(L.a[j], L.a[j - 1]);
			comparisons++;
			accesses += 3;
		}
	}
}

//二分插入排序
void InsertionSort_Binary(List& L)
{
	for (int i = 1; i < L.length; i++) 
	{
		int temp = L.a[i]; //暂存元素值
		accesses++;
		int left = 0, right = i - 1;
		while (left <= right) 
		{ //二分查找L.a[i]应插入的位置
			int mid = (left + right) / 2;
			if (temp < L.a[mid]) right = mid - 1;
			else left = mid + 1;
			comparisons++;
		}
		for (int j = i - 1; j >= left; j--)
		{ //大于插入元素的元素后移
			L.a[j + 1] = L.a[j];
			accesses++;
		}
		L.a[left] = temp; //插入元素
		accesses++;
	}
}

//希尔排序
void ShellSort(List& L)
{
	int h = 1;
	while (h < L.length / 3) h = h * 3 + 1;
	while (h)
	{ 
		for (int i = h; i < L.length; i++)
		{
			for (int j = i - h; j >= 0 && L.a[j] > L.a[j + h]; j -= h)
			{
				swap(L.a[j], L.a[j + h]);
				comparisons++;
				accesses += 3;
			}
		}
		h /= 3;
	}
}

int main()
{
	srand(time(NULL));
	List L1;
	List_In(L1);
	List L = L1;
	InsertionSort(L);
	cout << "InsertionSort";
	List_out(L);
	L = L1, comparisons = 0, accesses = 0;
	InsertionSort_Binary(L);
	cout << "InsertionSort_Binary";
	List_out(L);
	L = L1, comparisons = 0, accesses = 0;
	ShellSort(L);
	cout << "ShellSort";
	List_out(L);
	return 0;
}