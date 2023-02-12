#include <iostream>
#include <time.h>
#include <fstream>
#include <math.h>

using namespace std;

ifstream ifs;

typedef struct City //城市
{
	string name;
	float x = 0, y = 0;
}Citys[200];

typedef struct CityList //城市组
{
	Citys citys;
	int length = 0;
}*CL;

void CreatList(CL& C) //创建城市组
{
	ifs.open("Simulated annealing algorithm TSP.txt", ios::in);
	cout << "输入节点名称和XY坐标(以# 0 0结束)：" << endl;
	for (int i = 0;; i++)
	{
		cout << "请输入第" << i + 1 << "个城市的名称：";
		ifs >> C->citys[i].name;
		cout << C->citys[i].name << endl;
		cout << "请输入第" << i + 1 << "个城市经度：";
		ifs >> C->citys[i].x;
		cout << C->citys[i].x << endl;
		cout << "请输入第" << i + 1 << "个城市纬度：";
		ifs >> C->citys[i].y;
		cout << C->citys[i].y << endl;
		if (C->citys[i].name == "#" && C->citys[i].x == 0 && C->citys[i].y == 0)
			break;
		C->length++;
	}
	ifs.close();
}

void PrintList(CL& C) //城市组输出
{
	for (int i = 0; i < C->length; i++)
	{
		cout << C->citys[i].name << "->";
	}
	cout << C->citys[0].name;
	cout << endl;
}

void ShuffleList(CL& C) //洗牌算法
{
	int i = C->length;
	while (i)
	{
		int j = rand() % i--;
		City temp = C->citys[j];
		C->citys[j] = C->citys[i];
		C->citys[i] = temp;
	}
}

double TravelList(CL& C) //当前顺序的周游距离
{
	double sum = 0;
	for (int i = 0; i < C->length; i++)
	{
		double distance;
		if (i < C->length - 1)
		{
			distance = sqrt(pow(C->citys[i].x - C->citys[i + 1].x, 2) + pow(C->citys[i].y - C->citys[i + 1].y, 2));
			sum = sum + distance;
		}
		else
		{
			distance = sqrt(pow(C->citys[i].x - C->citys[0].x, 2) + pow(C->citys[i].y - C->citys[0].y, 2));
			sum = sum + distance;
		}
	}
	return sum;
}

void CopyList(CL& C, CL& C1) //复制城市组
{
	for (int i = 0; i < C->length; i++)
	{
		C1->citys[i].name = C->citys[i].name;
		C1->citys[i].x = C->citys[i].x;
		C1->citys[i].y = C->citys[i].y;
	}
	C1->length = C->length;
}

double rand01() //生成0~1之间3位随机数
{
	int N = 999;
	int N1 = rand() % (N + 1);
	return (float)N1 / (float)1000;
}

void SA_TSP(CL& C) //模拟退火算法TSP
{
	double T = 10000, n = 15000, k = 0.999;
	for (int i = 0; i < n; i++)
	{
		double sum0, sum1;
		CL C1 = new CityList;
		CopyList(C, C1);
		ShuffleList(C1);
		sum0 = TravelList(C);
		sum1 = TravelList(C1);
		if (sum1 < sum0)
		{
			CL p = C;
			C = C1;
			delete p;
		}
		else if (rand01() < exp(-(sum1 - sum0) / T))
		{
			CL p = C;
			C = C1;
			delete p;
		}
		T = T * k;
	}
	PrintList(C);
	cout << TravelList(C) << endl;
}

int main()
{
	srand(time(NULL));
	CL C = new CityList;
	CreatList(C);
	for (int i = 0; i < 10; i++)
	{
		cout << "第" << i + 1 << "次模拟退火算法结果：" << endl;
		SA_TSP(C);
		cout << endl;
	}
	return 0;
}