#include<iostream>
#include<windows.h>
using namespace std;

#define MAXSIZE 50
typedef char VerTexType;
typedef int ArcType;

typedef struct SqQueue//���帨������
{
    int* base;
    int front, rear;
} SqQueue;

void InitQueue(SqQueue& Q)//����ն�
{
    Q.base = new int[MAXSIZE];
    Q.front = Q.rear = 0;
}

void EnQueue(SqQueue& Q, int v)//���
{
    if (Q.front != (Q.rear + 1) % MAXSIZE)
    {
        Q.base[Q.rear] = v;
        Q.rear = (Q.rear + 1) % MAXSIZE;
    }
}

void DeQueue(SqQueue& Q, int& u)//����
{
    if (Q.front != Q.rear)
    {
        u = Q.base[Q.front];
        Q.front = (Q.front + 1) % MAXSIZE;
    }
}

typedef struct AMGraph//�����ڽӾ���ṹ
{
    VerTexType vexs[MAXSIZE];
    ArcType arcs[MAXSIZE][MAXSIZE];
    int vexnum, arcnum;
} AMGraph;

typedef struct ArcNode//�ڽӱ�߽ṹ
{
    int adjvex;
    ArcNode* nextarc;
} ArcNode;

typedef struct VexNode//�ڽӱ���ṹ
{
    VerTexType data;
    ArcNode* firstarc;
} AdjList[MAXSIZE];

typedef struct ALGraph//�ڽӱ�ṹ
{
    AdjList vertices;
    int vexnum, arcnum;
} ALGraph;

void CreateUDG(ALGraph& G)//��������ͼ�ڽӱ�
{
    cout << "����������ͼ���ܶ�������";
    cin >> G.vexnum;
    cout << "����������ͼ���ܱ�����";
    cin >> G.arcnum;
    for (int i = 0; i < G.vexnum; i++)//¼�붥��
    {
        cout << "�������" << i + 1 << "����������ƣ�";
        cin >> G.vertices[i].data;
    }
    for (int i = 0; i < G.vexnum; i++)//�߳�ʼ��
    {
        G.vertices[i].firstarc = NULL;
    }
    cout << "����߹�������������ʱ�ÿո�������磺a b" << endl;
    for (int i = 0; i < G.arcnum; i++)//¼���
    {
        VerTexType v1 = 0, v2 = 0;
        int x = -1, y = -1;
        while (x == -1 || y == -1)
        {
            cout << "�������" << i + 1 << "���߹������������㣺";
            cin >> v1 >> v2;
            for (int j = 0; j < G.vexnum; j++)
            {
                if (G.vertices[j].data == v1)
                {
                    x = j;
                    break;
                }
            }
            for (int j = 0; j < G.vexnum; j++)
            {
                if (G.vertices[j].data == v2)
                {
                    y = j;
                    break;
                }
            }
            if (x == -1 || y == -1)
                cout << "���������������������룡" << endl;
        }
        ArcNode* temp1 = new ArcNode, * temp2 = new ArcNode;
        temp1->adjvex = y;
        temp1->nextarc = G.vertices[x].firstarc;
        G.vertices[x].firstarc = temp1;
        temp2->adjvex = x;
        temp2->nextarc = G.vertices[y].firstarc;
        G.vertices[y].firstarc = temp2;
    }
}

void CreateUDG(AMGraph& G)//��������ͼ�ڽӾ���
{
    cout << "����������ͼ���ܶ�������";
    cin >> G.vexnum;
    cout << "����������ͼ���ܱ�����";
    cin >> G.arcnum;
    for (int i = 0; i < G.vexnum; i++)//¼�붥��
    {
        cout << "�������" << i + 1 << "����������ƣ�";
        cin >> G.vexs[i];
    }
    for (int i = 0; i < G.vexnum; i++)//�߳�ʼ��
    {
        for (int j = 0; j < G.vexnum; j++)
        {
            G.arcs[i][j] = 0;
        }
    }
    cout << "����߹�������������ʱ�ÿո�������磺a b" << endl;
    for (int i = 0; i < G.arcnum; i++)//¼���
    {
        VerTexType v1 = 0, v2 = 0;
        int x = -1, y = -1;
        while (x == -1 || y == -1)
        {
            cout << "�������" << i + 1 << "���߹������������㣺";
            cin >> v1 >> v2;
            for (int j = 0; j < G.vexnum; j++)
            {
                if (G.vexs[j] == v1)
                {
                    x = j;
                    break;
                }
            }
            for (int j = 0; j < G.vexnum; j++)
            {
                if (G.vexs[j] == v2)
                {
                    y = j;
                    break;
                }
            }
            if (x == -1 || y == -1)
                cout << "���������������������룡" << endl;
        }
        G.arcs[x][y] = 1;
        G.arcs[y][x] = 1;
    }
}

bool visited[MAXSIZE];

int FirstAdjVex(ALGraph& G, int v)//First����(�ڽӱ�)
{
    if (G.vertices[v].firstarc) 
        return G.vertices[v].firstarc->adjvex;
    return -1;
}

int NextAdjVex(ALGraph& G, int v, int w)//Next����(�ڽӱ�)
{
    ArcNode* temp = G.vertices[v].firstarc;
    while (temp) {
        if (temp->adjvex == w && temp->nextarc) 
            return temp->nextarc->adjvex;
        temp = temp->nextarc;
    }
    return -1;
}

void DFS(ALGraph& G, int v)//������ȱ���(�ڽӱ�)
{
    cout << G.vertices[v].data << " ";
    visited[v] = true;
    for (int w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w))
    {
        if (!visited[w])
            DFS(G, w);
    }
}

void BFS(ALGraph& G, int v)//������ȱ���(�ڽӱ�)
{
    cout << G.vertices[v].data << " ";
    visited[v] = true;
    SqQueue Q;
    InitQueue(Q);
    EnQueue(Q, v);
    while (Q.front != Q.rear)
    {
        int u = 0;
        DeQueue(Q, u);
        for (int w = FirstAdjVex(G, u); w >= 0; w = NextAdjVex(G, u, w))
        {
            if (!visited[w])
            {
                cout << G.vertices[w].data << " ";
                visited[w] = true;
                EnQueue(Q, w);
            }
        }
    }
}

int FirstAdjVex(AMGraph& G, int v)//First����(�ڽӾ���)
{
    for (int j = 0; j < G.vexnum; j++)
    {
        if (G.arcs[v][j])
            return j;
    }
    return -1;
}

int NextAdjVex(AMGraph& G, int v, int w)//Next����(�ڽӾ���)
{
    for (int j = w + 1; j < G.vexnum; j++)
    {
        if (G.arcs[v][j])
            return j;
    }
    return -1;
}

void DFS(AMGraph& G, int v)//������ȱ���(�ڽӾ���)
{
    cout << G.vexs[v] << " ";
    visited[v] = true;
    for (int w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w))
    {
        if (!visited[w])
            DFS(G, w);
    }
}

void BFS(AMGraph& G, int v)//������ȱ���(�ڽӾ���)
{
    cout << G.vexs[v] << " ";
    visited[v] = true;
    SqQueue Q;
    InitQueue(Q);
    EnQueue(Q, v);
    while (Q.front != Q.rear)
    {
        int u = 0;
        DeQueue(Q, u);
        for (int w = FirstAdjVex(G, u); w >= 0; w = NextAdjVex(G, u, w)) 
        {
            if (!visited[w]) 
            {
                cout << G.vexs[w] << " ";
                visited[w] = true;
                EnQueue(Q, w);
            }
        }
    }
}

void Test_Print(ALGraph& G)//��������ڽӱ� 
{
    cout << "�ڽӱ����£�" << endl;
    for (int i = 0; i < G.vexnum; i++) 
    {
        cout << G.vertices[i].data << " -> ";
        ArcNode* temp = G.vertices[i].firstarc;
        while (temp) 
        {
            cout << G.vertices[temp->adjvex].data << " -> ";
            temp = temp->nextarc;
        }
        cout << "NULL" << endl;
    }
}

void Test_Print(AMGraph& G)//��������ڽӾ���
{
    cout << "�ڽӾ������£�" << endl;
    for (int i = 0; i < G.vexnum; i++)
    {
        for (int j = 0; j < G.vexnum; j++)
        {
            cout << G.arcs[i][j] << " ";
        }
        cout << endl;
    }
}

void visited_Clear()//visited���黹ԭ
{
    for (int i = 0; visited[i]; i++)
    {
        visited[i] = false;
    }
}

int main()
{
    int v;
    cout << "----------�ڽӾ�����ز���----------" << endl;
    AMGraph AMG;
    CreateUDG(AMG);
    Test_Print(AMG);
    cout << "��������ȱ���������±�(��0��ʼ)��";
    cin >> v;
    cout << "��ȱ������(���±�" << v << "��ʼ)��";
    DFS(AMG, v);
    visited_Clear();
    cout << endl << "��ȱ������(���±�" << v << "��ʼ)��";
    BFS(AMG, v);
    visited_Clear();
    system("pause");
    system("cls");
    cout << "----------�ڽӱ���ز���----------" << endl;
    ALGraph ALG;
    CreateUDG(ALG);
    Test_Print(ALG);
    cout << "��������ȱ���������±�(��0��ʼ)��";
    cin >> v;
    cout << "��ȱ������(���±�" << v << "��ʼ)��";
    DFS(ALG, v);
    visited_Clear();
    cout << endl << "��ȱ������(���±�" << v << "��ʼ)��";
    BFS(ALG, v);
    visited_Clear();
    return 0;
}
