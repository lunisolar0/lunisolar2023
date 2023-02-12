#include <iostream>
#include <windows.h>
#include <time.h>
using namespace std;

int comparisons = 0, accesses = 0; //数据比较次数，数组访问次数

typedef struct List
{
	int a[100] = {}; //存储数组
	int length = 0; //排序表长度
}List;

//顺序表随机初始化
void List_Init(List& L)
{
	L.length = 48;
	for (int i = 0; i < L.length; i++)
		L.a[i] = ((i + 1) / 10 + 1) * 10;
	/*for (int i = L.length - 1; i; i--)
	{
		int j = rand() % i;
		swap(L.a[i], L.a[j]);
	}*/
}

//可视化(数组)
void List_Print(int a[])
{
	system("cls");
	for (int i = 0; i < 48; i++)
	{
		for (int j = 0; j < a[i]; j++)
			cout << "*";
		cout << endl;
	}
}

//可视化(顺序表)
void List_Print(List L)
{
	system("cls");
	for (int i = 0; i < L.length; i++)
	{
		for (int j = 0; j < L.a[i]; j++)
			cout << "*";
		cout << endl;
	}
}

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
			List_Print(L);
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
			List_Print(L);
			accesses++;
		}
		L.a[left] = temp; //插入元素
		List_Print(L);
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
				List_Print(L);
				comparisons++;
				accesses += 3;
			}
		}
		h /= 3;
	}
}

//下沉(堆排序)
void sink(List& L, int start, int end)
{
	int largest = start; //默认start为largest
	int left = largest * 2 + 1; //left存储start左孩子下标
	int right = largest * 2 + 2; //right存储start右孩子下标
	if (left > end) return; //若下标超界，则结束
	if (left <= end && L.a[left] > L.a[largest]) largest = left; //判断左孩子值是否比当前largest大，若是则迭代
	if (right <= end && L.a[right] > L.a[largest]) largest = right; //判断右孩子值是否比当前largset大，若是则迭代
	if (largest != start)
	{ //若在上一步中发生了迭代，则下沉并递归
		swap(L.a[largest], L.a[start]);
		List_Print(L);
		sink(L, largest, end);
	}
}

//堆排序
void HeapSort(List& L)
{
	int N = L.length;
	//初始化，i从最后一个父节点开始调整
	for (int i = N / 2 - 1; i >= 0; i--)
		sink(L, i, N - 1);
	//先将第一个元素和已经排好的元素前一位做交换，再从新调整(刚调整的元素之前的元素)，直到排序完毕
	for (int i = N - 1; i > 0; i--)
	{
		swap(L.a[0], L.a[i]);
		List_Print(L);
		sink(L, 0, i - 1);
	}
}

//归并子函数
void Merge(int sourceArr[], int tempArr[], int startIndex, int midIndex, int endIndex)
{
	int i = startIndex, j = midIndex + 1, k = startIndex;
	while (i != midIndex + 1 && j != endIndex + 1)
	{
		if (sourceArr[i] > sourceArr[j])
		{
			tempArr[k++] = sourceArr[j++];
			List_Print(sourceArr);
		}
		else
		{
			tempArr[k++] = sourceArr[i++];
			List_Print(sourceArr);
		}
	}
	while (i != midIndex + 1)
	{
		tempArr[k++] = sourceArr[i++];
		List_Print(sourceArr);
	}
	while (j != endIndex + 1)
	{
		tempArr[k++] = sourceArr[j++];
		List_Print(sourceArr);
	}
	for (i = startIndex; i <= endIndex; i++)
	{
		sourceArr[i] = tempArr[i];
		List_Print(sourceArr);
	}
}

//归并排序
void MergeSort(int sourceArr[], int tempArr[], int startIndex, int endIndex)
{
	int midIndex;
	if (startIndex < endIndex)
	{
		midIndex = startIndex + (endIndex - startIndex) / 2;//避免溢出int
		MergeSort(sourceArr, tempArr, startIndex, midIndex);
		MergeSort(sourceArr, tempArr, midIndex + 1, endIndex);
		Merge(sourceArr, tempArr, startIndex, midIndex, endIndex);
	}
}

int main()
{
	srand((int)time(NULL));
	List L1;
	List_Init(L1);
	List L = L1;
	system("pause");
	//InsertionSort(L); //直接插入排序
	//InsertionSort_Binary(L); //二分插入排序
	//ShellSort(L); //希尔排序
	HeapSort(L); //堆排序
	//int b[48] = {};
	//MergeSort(L.a, b, 0, 47); //归并排序
	system("pause");
	return 0;
}
