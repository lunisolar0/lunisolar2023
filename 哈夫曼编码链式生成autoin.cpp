#include <iostream>
#include <string>
#include <fstream>
using namespace std;

ifstream ifs;

typedef struct LinkHTNode //定义链式哈夫曼树
{
    LinkHTNode* left, * right, * next;
    char data;
    int weight;
} *LinkHT;

/*定义编码表*/
typedef struct CodeElem //编码单元
{
    char name = {};
    string code = {};
}CodeElem;

typedef struct CodeList //编码表
{
    CodeElem ce[100];
    int length = 0;
} CodeList;

LinkHT Create_LinkHT() //创建链式哈夫曼树
{
    LinkHT H = new LinkHTNode;
    H->next = NULL;
    ifs.open("HT coding.txt", ios::in);
    int n = 0;
    cout << "输入节点数据和节点权重(以# 0结束)：" << endl;
    for (int i = 0;; i++)
    {
        LinkHT temp = new LinkHTNode;
        cout << "请输入第" << i + 1 << "个节点的数据：";
        ifs >> temp->data;
        cout << temp->data << endl;
        cout << "请输入第" << i + 1 << "个节点的权重：";
        ifs >> temp->weight;
        cout << temp->weight << endl;
        if (temp->data == '#' && temp->weight == 0)
            break;
        temp->left = NULL;
        temp->right = NULL;
        temp->next = H->next;
        H->next = temp;
        n++;
    }
    H->data = (char)n;
    return H;
    ifs.close();
}

void Arrange_LinkHT(LinkHT& H) //哈夫曼树编码
{
    LinkHT p1 = H, p2 = H, p1f = H, p2f = H, temp = H;
    int min = 0;
    while (temp->next)
    {
        if (min == 0 || temp->next->weight < min)
        {
            min = temp->next->weight;
            p1f = temp;
            p1 = temp->next;
        }
        temp = temp->next;
    }
    temp = H;
    min = 0;
    while (temp->next)
    {
        if (min == 0 || temp->next->weight < min)
        {
            if (temp != p1f)
            {
                min = temp->next->weight;
                p2f = temp;
                p2 = temp->next;
            }
        }
        temp = temp->next;
    }
    p1f->next = p1->next;
    p1->next = NULL;
    if (p2f == p1)
        p2f = p1f;
    p2f->next = p2->next;
    p2->next = NULL;
    temp = new LinkHTNode;
    temp->data = '#';
    temp->weight = p1->weight + p2->weight;
    temp->left = p1;
    temp->right = p2;
    temp->next = H->next;
    H->next = temp;
    if (H->next->next)
    {
        Arrange_LinkHT(H);
    }
}

void Translate_LinkHT(LinkHT& H, CodeList& CL) //哈夫曼树解码
{
    if (H->data != '#')
    {
        CL.ce[++CL.length].name = H->data;
        CL.ce[CL.length].code = CL.ce[0].code;
        while (1)
        {
            char temp = CL.ce[0].code.back();
            CL.ce[0].code.pop_back();
            if (temp == '0' || CL.ce[0].code.empty()) break;
        }
    }
    else
    {
        CL.ce[0].code = CL.ce[0].code + '0';
        Translate_LinkHT(H->left, CL);
        CL.ce[0].code = CL.ce[0].code + '1';
        Translate_LinkHT(H->right, CL);
    }
}

void print_LinkHT(LinkHT& H) //中序输出哈夫曼树
{
    if (!H)
        return;
    else
    {
        print_LinkHT(H->left);
        cout << H->data << H->weight << " -> ";
        print_LinkHT(H->right);
    }
}

void print_CL(CodeList& CL) //编码表输出
{
    cout << "哈夫曼编码表如下：" << endl;
    for (int i = 1; i <= CL.length; i++)
    {
        cout << CL.ce[i].name << "：";
        cout << CL.ce[i].code << endl;
    }
}

int main()
{
    LinkHT H = Create_LinkHT();
    Arrange_LinkHT(H);
    CodeList CL;
    Translate_LinkHT(H->next, CL);
    print_CL(CL);
    return 0;
}
