#include <bits/stdc++.h>

using namespace std;

clock_t tic, toc;

ifstream Fin;

//string转wstring类型
wstring string2wstring(string str)
{
	wstring result;
	int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
	if (len < 0)return result;
	wchar_t* buffer = new wchar_t[len + 1];
	if (buffer == NULL)return result;
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);
	buffer[len] = '\0';
	result.append(buffer);
	delete[] buffer;
	return result;
}

//物品属性(0/1背包)
struct articles 
{
	string name;
	int weight = 0;
	int value = 0;
};

//0/1背包
class backpack
{
private:
	vector<articles> list; //物品清单
	int M; //背包载重
	int maxValue; //最大价值
public:backpack(int M)
{
	this->M = M;
	initList();
	solution();
}
	  //初始化物品清单
private:void initList()
{
	cout << "请输入物品名称,重量,价值(各属性以空格分开并以# 0 0结束)：" << endl;
	Fin.open("list.txt");
	while (1)
	{
		articles temp;
		Fin >> temp.name >> temp.weight >> temp.value;
		cout << temp.name << " " << temp.weight << " " << temp.value << endl;
		if (temp.name == "#" && temp.value == 0 && temp.weight == 0) break;
		list.push_back(temp);
	}
	Fin.close();
}
	   //输出对象
public:void print()
{
	cout << "物品清单如下：" << endl;
	for (auto it : list) cout << "name:" << it.name << "\tweight:" << it.weight << "\tvalue:" << it.value << endl;
	cout << "背包载重：" << M << endl;
	cout << "最大价值：" << maxValue << endl;
}
	  //求最大价值
private:void solution()
{
	vector<int> dp(M + 1, 0);
	cout << "规划迭代表如下：" << endl;
	cout << "Weight" << " \t";
	for (int i = 0; i <= 10; i++) cout << i << " \t";
	cout << endl;
	for (auto it : list)
	{
		for (int i = M; i >= 0; i--)
		{
			if (i - it.weight >= 0) dp[i] = max(dp[i - it.weight] + it.value, dp[i]);
		}
		cout << it.name << "\t";
		for (auto it2 : dp) cout << it2 << "\t";
		cout << endl;
	}
	maxValue = dp[M];
}
};

//最长公共子序列
class maxCommonSubQueue
{
private:
	string str1, str2;
	int maxNum;
	  //构造函数
public:maxCommonSubQueue()
{
	init();
	solution();
}
	  //初始化函数
private:void init()
{
	Fin.open("maxCommonSubQueue.txt");
	cout << "请输入str1：" << endl;
	Fin >> str1;
	cout << str1 << endl;
	cout << "请输入str2：" << endl;
	Fin >> str2;
	cout << str2 << endl;
	Fin.close();
}
	  //解决方法
private:void solution()
{
	wstring ws1 = string2wstring(str1), ws2 = string2wstring(str2);
	vector<int> dp(ws2.size(), 0);
	for (int i = 0; i < ws1.size(); i++)
	{
		for (int j = 0; j < ws2.size(); j++)
		{
			if (ws1[i] == ws2[j]) dp[j]++;
			if (j - 1 >= 0 && dp[j - 1] > dp[j]) dp[j] = dp[j - 1];
		}
	}
	maxNum = dp[ws2.size() - 1];
}
	  //输出函数
public:void printNum()
{
	cout << "最长公共子序列长度为：" << maxNum << endl;
}
};

int main()
{
	backpack* a = new backpack(10);
	a->print();
	maxCommonSubQueue* b = new maxCommonSubQueue;
	b->printNum();
	return 0;
}
