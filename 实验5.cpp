#include <iostream>
#include <fstream>
#include <windows.h>
#define MAXSIZE 30

using namespace std;

ifstream ifs;

typedef struct ElemType //数据元素定义
{
	int Key = 0;
	string otherinfo;

}ElemType;

typedef struct SSTable //顺序查找表定义
{
	ElemType* R;
	int length;
}SSTable;

void InitList_SSTable(SSTable& L) //初始化查找表
{
	L.R = new ElemType[MAXSIZE];
	L.length = 0;
}

void Insert_SSTable(SSTable& L, int n) //查找表元素插入
{
	for (int i = 1; i <= n; i++)
	{
		int temp_Key;
		string temp_otherinfo;
		cout << "请输入第" << i << "位学生的姓名：";
		ifs >> temp_otherinfo;
		cout << temp_otherinfo << endl;
		cout << "请输入第" << i << "位学生的学号：";
		ifs >> temp_Key;
		cout << temp_Key << endl;
		L.R[i].Key = temp_Key;
		L.R[i].otherinfo = temp_otherinfo;
	}
	L.length = n;
}

int Search_Seq(SSTable ST, int key) //顺序查找
{
	ST.R[0].Key = key;
	int i;
	for (i = ST.length; ST.R[i].Key != key; i--);
	return i;
}

int Search_Bin(SSTable ST, int key) //二分查找
{
	int low = 1, high = ST.length;
	while (low <= high)
	{
		int mid = (low + high) / 2;
		if (ST.R[mid].Key > key) high = mid - 1;
		else if (ST.R[mid].Key < key) low = mid + 1;
		else return mid;
	}
	return 0;
}

void bubble(SSTable& L) //冒泡排序
{
	for (int i = 1; i < L.length; i++)
	{
		for (int j = i + 1; j <= L.length; j++)
		{
			if (L.R[i].Key > L.R[j].Key)
			{
				ElemType temp;
				temp = L.R[i];
				L.R[i] = L.R[j];
				L.R[j] = temp;
			}
		}
	}
}

void Show_End(SSTable& L, int result, ElemType& testkey) //查找结果输出
{
	testkey = L.R[result];
}

void Print_SSTable(SSTable& L) //查找表输出
{
	for (int i = 1; i <= L.length; i++)
	{
		cout << "第" << i << "位学生的姓名：" << L.R[i].otherinfo << endl;
		cout << "第" << i << "位学生的学号：" << L.R[i].Key << endl;
	}
}

int main()
{
	int n;
	SSTable L;
	InitList_SSTable(L);
	ifs.open("search.txt", ios::in);
	cout << "请输入查找表元素个数：";
	ifs >> n;
	cout << n << endl;
	Insert_SSTable(L, n);
	cout << "请输入要查找的学号：";
	int key;
	cin >> key;
	int result = Search_Seq(L, key);
	if (!result) cout << "查无此人" << endl;
	else
	{
		ElemType testkey;
		Show_End(L, result, testkey);
		cout << "已找到：" << endl;
		cout << "姓名：" << testkey.otherinfo << endl;
		cout << "学号：" << testkey.Key << endl;
	}
	system("pause");
	bubble(L);
	system("cls");
	cout << "查找表已按学号从小到大排序：" << endl;
	Print_SSTable(L);
	cout << "请输入要查找的学号：";
	cin >> key;
	result = Search_Bin(L, key);
	if (!result) cout << "查无此人" << endl;
	else
	{
		ElemType testkey;
		Show_End(L, result, testkey);
		cout << "已找到：" << endl;
		cout << "姓名：" << testkey.otherinfo << endl;
		cout << "学号：" << testkey.Key << endl;
	}
	return 0;
}