#include <iostream>
#include <iomanip>

using std::cout;
using std::cin;
using std::endl;

class Det
{ //行列式类
private:
	int a[10][10] = {}; //存储行列式
	int step = 0; //行列式阶数
	int valua = 0; //行列式的值

//行列式初始化
public:void DetInit()
{
	cout << "请输入行列式阶数：";
	cin >> step;
	cout << "请输入行列式：" << endl;
	for (int i = 0; i < step; i++)
		for (int j = 0; j < step; j++)
			cin >> a[i][j];
	valua = DetCalculate();
}

//行列式输出
public:void DetPrint()
{
	cout << "行列式输出如下：" << endl;
	for (int i = 0; i < step; i++)
	{
		cout << "|";
		for (int j = 0; j < step; j++)
		{
			if(!j) cout << std::setw(2) << a[i][j];
			else cout <<std::setw(3)<< a[i][j];
		}
		cout << "|" << endl;
	}
	cout << "该行列式的值为：" << valua << endl;
}

//行列式求值
private:int DetCalculate()
{
	if (step == 1) return a[0][0]; //结束递归
	int sum = 0;
	for (int i = 0; i < step; i++)
	{ //按第一列展开
		if (i % 2 == 0) sum = sum + a[i][0] * MinorDet(i, 0).valua;
		else sum = sum - a[i][0] * MinorDet(i, 0).valua;
	}
	return sum;
}

//求余子式
public:Det MinorDet(int x, int y)
{
	Det Md;
	Md.step = this->step - 1; //余子式阶数
	int Mi = 0, Mj = 0;
	for (int i = 0; i < this->step; i++)
	{ //余子式各位置元素
		for (int j = 0; j < this->step; j++)
		{
			if (i != x && j != y)
			{
				Md.a[Mi][Mj] = this->a[i][j];
				if (Mj == Md.step - 1) Mj = 0, Mi++;
				else Mj++;
			}
		}
	}
	Md.valua = Md.DetCalculate(); //余子式的值
	return Md;
}

};

int main()
{
	Det* d = new Det;
	d->DetInit();
	d->DetPrint();
	delete d;
	return 0;
}
