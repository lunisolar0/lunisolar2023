#include<iostream>
#include<fstream>
using namespace std;

ifstream ifs;

typedef struct LinkHTNode //定义链式哈夫曼树节点
{
    LinkHTNode* left = NULL, * right = NULL, * next = NULL;
    string name;
    float locate = 0;
} *LinkHT;

void Create_LinkHT(LinkHT& H) //创建链式哈夫曼树
{
    ifs.open("1D chain clustering.txt", ios::in);
    cout << "输入节点名称和节点值(以# 0结束)：" << endl;
    for (int i = 0;; i++)
    {
        LinkHT temp = new LinkHTNode;
        cout << "请输入第" << i + 1 << "个节点的名称：";
        ifs >> temp->name;
        cout << temp->name << endl;
        cout << "请输入第" << i + 1 << "个节点的值：";
        ifs >> temp->locate;
        cout << temp->locate << endl;
        if (temp->name == "#" && temp->locate == 0)
            break;
        temp->left = NULL;
        temp->right = NULL;
        temp->next = H->next;
        H->next = temp;
    }
    ifs.close();
}

void Arrange_LinkHT(LinkHT& H) //哈夫曼树排列
{
    LinkHT af = H, a = H, bf = H, b = H;
    float min = 0;
    for (LinkHT i = H; i->next->next; i = i->next)
    {
        for (LinkHT j = i->next; j->next; j = j->next)
        {
            if (abs(i->next->locate - j->next->locate) < min || min == 0)
            {
                min = abs(i->next->locate - j->next->locate);
                af = i;
                a = i->next;
                bf = j;
                b = j->next;
            }
        }
    }
    af->next = a->next;
    a->next = NULL;
    if (bf == a)
        bf = af;
    bf->next = b->next;
    b->next = NULL;
    LinkHT temp = new LinkHTNode;
    temp->name = "#";
    temp->locate = (a->locate + b->locate) / 2;
    temp->left = a;
    temp->right = b;
    temp->next = H->next;
    H->next = temp;
}



void Print_LinkHT(LinkHT& H) //输出哈夫曼树
{
    if (!H)
        return;
    else
    {
        Print_LinkHT(H->left);
        if (H->name != "#")
            cout << H->locate << "，";
        Print_LinkHT(H->right);
    }
}

void Print_Cluster(LinkHT& H) //输出聚类结果
{
    cout << "聚类结果：" << endl;
    int num = 1;
    for (LinkHT i = H->next; i; i = i->next)
    {
        cout << "第" << num++ << "类：";
        Print_LinkHT(i);
        cout << endl;
    }
}

int main()
{
    LinkHT H = new LinkHTNode;
    H->next = NULL;
    Create_LinkHT(H);
    int step = 1;
    cout << "请输入需要聚成的类数：";
    cin >> step;
    while (step < 1)
    {
        cout << "您的输入有误，请重新输入！" << endl;
        cout << "请输入需要聚成的类数：";
        cin >> step;
    }
    while (1)
    {
        Arrange_LinkHT(H);
        LinkHT temp = H->next;
        for (int i = 0; i < step; i++)
        {
            temp = temp->next;
        }
        if (!temp)
            break;
    }
    Print_Cluster(H);
    return 0;
}
