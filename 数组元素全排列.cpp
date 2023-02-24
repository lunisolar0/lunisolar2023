#include <iostream>

using namespace std;

#define LENGTH 5

void Init_arr(int a[], int length)
{
	for (int i = 0; i < length; i++)
	{
		a[i] = i + 1;
	}
}

void Print_arr(int a[], int lo, int hi)
{
	for (int i = lo; i <= hi; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}

void Perm_arr(int a[], int lo, int hi)
{
	if (lo > hi)
	{
		Print_arr(a, 0, 2);
		return;
	}
	for (int i = lo; i < LENGTH; i++)
	{
		swap(a[lo], a[i]);
		Perm_arr(a, lo + 1, hi);
		swap(a[lo], a[i]);
	}
}

int Perm_Calculate(int length, int p)
{
	int sum = 1;
	for (; p; length--, p--)
	{
		sum = sum * length;
	}
	return sum;
}

int main()
{
	int a[LENGTH] = {};
	Init_arr(a, LENGTH);
	cout << "有" << Perm_Calculate(5, 3) << "种组合：" << endl;
	Perm_arr(a, 0, 2);
	return 0;
}