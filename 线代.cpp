#include <iostream>

using namespace std;

class Det //行列式类
{
private:
	int matrix[10][10] = {}; //存储行列式
	int step = 0; //行列式阶数
	int valua = 0; //行列式的值

//行列式输入
public:void DetInput(Det& det)
{
	cout << "请输入行列式阶数：";
	cin >> det.step;
	cout << "请输入行列式：" << endl;
	for (int i = 0; i < det.step; i++)
	{
		for (int j = 0; j < det.step; j++)
			cin >> det.matrix[i][j];
	}
	det.valua = DetCalculate(det);
}

//行列式输出
public:void DetOutput(Det det)
{
	cout << "行列式输出如下：" << endl;
	for (int i = 0; i < det.step; i++)
	{
		for (int j = 0; j < det.step; j++)
			cout << det.matrix[i][j] << " ";
		cout << endl;
	}
	cout << "该行列式的值为：" << det.valua << endl;
}

//求行列式余子式
public:Det MinorDet(int x, int y, Det det)
{
	Det Mdet;
	Mdet.step = det.step - 1;
	int Mi = 0, Mj = 0;
	for (int i = 0; i < det.step; i++)
	{
		for (int j = 0; j < det.step; j++)
		{
			if (i != x && j != y)
			{
				Mdet.matrix[Mi][Mj] = det.matrix[i][j];
				if (Mj == Mdet.step - 1) Mj = 0, Mi++;
				else Mj++;
			}
		}
	}
	return Mdet;
}

//行列式求值
private:int DetCalculate(Det det)
{
	if (det.step == 1) return det.matrix[0][0];
	int sum = 0;
	for (int i = 0; i < det.step; i++)
	{
		if (i % 2 == 0) sum = sum + det.matrix[i][0] * DetCalculate(MinorDet(i, 0, det));
		else sum = sum - det.matrix[i][0] * DetCalculate(MinorDet(i, 0, det));
	}
	return sum;
}

};

int main()
{
	Det* det = new Det; //创建对象
	det->Det::DetInput(*det); //录入行列式
	det->Det::DetOutput(*det); //输出行列式及其值
	delete det;
	return 0;
}