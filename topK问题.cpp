#include <bits/stdc++.h>

using namespace std;

clock_t tic, toc;

class topK
{
private:
	vector<int> array;
	int size;
	  //构造函数
public:topK(int n)
{
	size = n;
	init();
}
	  //赋值
private:void init()
{
	if (!array.size())
	{
		for (int i = 0; i < size; i++)
			array.push_back(i);
	}
	for (int i = size - 1; i; i--)
	{ //随机排序
		int j = rand() % (i + 1);
		swap(array[i], array[j]);
	}
}
	  //打印vector
public:void print()
{
	for (auto it : array) cout << it << " ";
	cout << endl;
}
	  //先排后找：O(nlogn)
public:void sortSearch(int k)
{
	init();
	tic = clock();
	sort(array.begin(), array.end());
	toc = clock();
	cout << array[k - 1] << endl;
	cout << "先排后找法用时：" << (double)(toc - tic) << "ms" << endl;
}
	  //类快排切分法：O(n)
public:void splitSearch(int k)
{
	init();
	tic = clock();
	int ret = splitSearchLaunch(0, size - 1, k);
	toc = clock();
	cout << ret << endl;
	cout << "类快排切分法用时：" << (double)(toc - tic) << "ms" << endl;
}
	  //启动函数(切分法)
private:int splitSearchLaunch(int lo, int hi, int k)
{
	int mi = split(lo, hi);
	if (mi == k - 1) return array[mi];
	return mi > k - 1 ? splitSearchLaunch(lo, mi - 1, k) : splitSearchLaunch(mi + 1, hi, k);
}
	  //切分函数
private:int split(int lo, int hi)
{
	int v = array[lo];
	int i = lo, j = hi + 1;
	while (i < j) 
	{
		while (++i <= hi && array[i] < v);
		while (--j >= lo && array[j] > v);
		if(i < j) swap(array[i], array[j]);
	}
	swap(array[lo], array[j]);
	return j;
}
	  //分组查找：O(n)
public:void groupingSearch(int k, int q)
{
	init();
	tic = clock();
	int ret = groupingSearchLaunch(array, k, q);
	toc = clock();
	cout << ret << endl;
	cout << "分组查找法用时(" << q << "个/组)" << "：" << (double)(toc - tic) << "ms" << endl;
}
	  //启动函数(分组法)
private:int groupingSearchLaunch(vector<int> nums, int k, int q)
{
	if (nums.size() < 9*q)
	{ //斩杀线
		sort(nums.begin(), nums.end());
		return nums[k - 1];
	}
	vector<int> mm;
	for (int i = 0; nums.size() - i >= q; i += q)
	{ //求每组中位数
		sort(nums.begin() + i, nums.begin() + i + q - 1);
		mm.push_back(nums[i + (q - 1) / 2]);
	}
	sort(mm.begin(), mm.end());
	int M = mm[(mm.size() - 1) / 2];
	vector<int> a1, a2, a3;
	for (auto it : nums)
	{ //分组
		if (it < M) a1.push_back(it);
		else if (it > M) a3.push_back(it);
		else a2.push_back(it);
	}
	if (a1.size() >= k) return groupingSearchLaunch(a1, k, q);
	else if (a1.size() + a2.size() < k) return groupingSearchLaunch(a3, k - a1.size() - a2.size(), q);
	else return nums[k - 1];
}
	  //优先队列：O(nlogk)
public:void heapSearch(int k)
{
	init();
	tic = clock();
	priority_queue<int, vector<int>, less<int>> maxHeap;
	for (auto it : array)
	{
		if (maxHeap.size() < k) maxHeap.push(it);
		else
		{
			if (it < maxHeap.top())
			{
				maxHeap.push(it);
				maxHeap.pop();
			}
		}
	}
	toc = clock();
	cout << maxHeap.top() << endl;
	cout << "优先队列法用时：" << (double)(toc - tic) << "ms" << endl;
}
};

int main()
{
	srand(time(NULL));
	topK* a = new topK(2000000);
	a->sortSearch(1226);
	a->splitSearch(1226);
	a->heapSearch(1226);
	for(int i = 5; i <= 31; i+=2)
	a->groupingSearch(1226, i);
	return 0;
}