#include <iostream>
#include <time.h>

using namespace std;

double rand01() //生成0~1之间4位随机数
{
	int N = 9999;
	int N1 = rand() % (N + 1);
	return (float)N1 / (float)10000;
}

int main()
{
	srand(time(NULL));
	double rate = 1, n = 0, money = 0;
	double rate0 = 1, n0 = 0, money0 = 0;
	cout << "请输入初始资金（元）：";
	cin >> money;
	n = money / rate;
	money0 = money;
	rate0 = rate;
	n0 = n;
	cout << "初始净值：" << rate0 << endl;
	cout << "初始份额：" << n0 << endl;
	for (int i = 0; i < 10000; i++)
	{
		cout << i + 1 << "天后：" << endl;
		double change = (rand01() - 0.5);
		cout << "今日涨跌幅：" << change << "%" << endl;
		double change_money = 0, change_n = 0;
		rate = rate * (1 + change / 100);
		money = n * rate;
		cout << "当前净值：" << rate << endl;
		cout << "当前份额：" << n << endl;
		cout << "当前资金：" << money << endl;
		cout << "请输入资金调整金额（元）：";
		change_money = 0;
		cout << "0" << endl;
		money0 = money0 + change_money;
		change_n = change_money / rate;
		n = n + change_n;
		cout << "调整后的资金金额：" << n * rate << endl << endl;
	}
	cout << "净投资额：" << money0 << endl;
	cout << "当前持有金额：" << money << endl;
	cout << "净赚：" << money - money0 << endl;
}