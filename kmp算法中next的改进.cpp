#include <iostream>
#include <string>

using namespace std;

#define MAXLEN 256
typedef struct
{
	char ch[MAXLEN + 1];//字符数组存储串
	int length;//串长
}SString;

int KMP(SString S, SString T, int pos)
{
	/*next[]*/
	int next[MAXLEN + 1];
	next[1] = 0;
	int i = 1, j = 0;
	while (i < T.length)
	{
		if (!j || T.ch[i] == T.ch[j])
		{
			i++;j++;
			next[i] = j;
		}
		else j = next[j];
	}
	cout << "next[]：";
	for (i = 1; i <= T.length; i++)
		cout << next[i] << " ";
	cout << endl;
	/*nextval[]*/
	int nextval[MAXLEN + 1];
	i = 1; nextval[1] = 0; j = 0;
	while (i < T.length)
	{
		if (!j || T.ch[i] == T.ch[j])
		{
			i++; j++;
			if (T.ch[i] != T.ch[j]) nextval[i] = j;
			else nextval[i] = nextval[j];
		}
		else j = nextval[j];
	}
	cout << "nextval[]：";
	for (i = 1; i <= T.length; i++)
		cout << nextval[i] << " ";
	cout << endl;
	/*KMP算法主体*/
	/*使用next[]进行匹配*/
	int n = 0;
	i = pos; j = 1;
	while (i <= S.length && j <= T.length)
	{
		n++;
		if (!j || S.ch[i] == T.ch[j])
		{
			i++; j++;
		}
		else j = next[j];
	}
	cout << "使用next[]共进行了" << n << "次字符匹配操作" << endl;
	/*使用nextval[]进行匹配*/
	n = 0;
	i = pos; j = 1;
	while (i <= S.length && j <= T.length)
	{
		n++;
		if (!j || S.ch[i] == T.ch[j])
		{
			i++; j++;
		}
		else j = nextval[j];
	}
	cout << "使用nextval[]共进行了" << n << "次字符匹配操作" << endl;
	if (j > T.length) return i - T.length;//匹配成功
	else return 0;//匹配失败
}

int main()
{
	SString S, T;
	string buf;
	/*输入模块*/
	cout << "请输入主串S：" << endl;
	cin >> buf;
	strcpy_s(S.ch + 1, MAXLEN, buf.c_str());
	S.length = buf.length();
	cout << "请输入模式串T：" << endl;
	cin >> buf;
	strcpy_s(T.ch + 1, MAXLEN, buf.c_str());
	T.length = buf.length();
	/*算法调用*/  
	int ret = KMP(S, T, 1);
	if (ret) cout << "匹配成功，T在S中首次出现的位置：" << ret << endl;
	else cout << "匹配失败" << endl;
	return 0;
}