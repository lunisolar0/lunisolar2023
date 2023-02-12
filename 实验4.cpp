#include<iostream>
#include<windows.h>
using namespace std;

#define MAXSIZE 50
typedef char VerTexType;
typedef int ArcType;

typedef struct SqQueue//定义辅助队列
{
    int* base;
    int front, rear;
} SqQueue;

void InitQueue(SqQueue& Q)//构造空队
{
    Q.base = new int[MAXSIZE];
    Q.front = Q.rear = 0;
}

void EnQueue(SqQueue& Q, int v)//入队
{
    if (Q.front != (Q.rear + 1) % MAXSIZE)
    {
        Q.base[Q.rear] = v;
        Q.rear = (Q.rear + 1) % MAXSIZE;
    }
}

void DeQueue(SqQueue& Q, int& u)//出队
{
    if (Q.front != Q.rear)
    {
        u = Q.base[Q.front];
        Q.front = (Q.front + 1) % MAXSIZE;
    }
}

typedef struct AMGraph//定义邻接矩阵结构
{
    VerTexType vexs[MAXSIZE];
    ArcType arcs[MAXSIZE][MAXSIZE];
    int vexnum, arcnum;
} AMGraph;

typedef struct ArcNode//邻接表边结构
{
    int adjvex;
    ArcNode* nextarc;
} ArcNode;

typedef struct VexNode//邻接表顶点结构
{
    VerTexType data;
    ArcNode* firstarc;
} AdjList[MAXSIZE];

typedef struct ALGraph//邻接表结构
{
    AdjList vertices;
    int vexnum, arcnum;
} ALGraph;

void CreateUDG(ALGraph& G)//创建无向图邻接表
{
    cout << "请输入无向图的总顶点数：";
    cin >> G.vexnum;
    cout << "请输入无向图的总边数：";
    cin >> G.arcnum;
    for (int i = 0; i < G.vexnum; i++)//录入顶点
    {
        cout << "请输入第" << i + 1 << "个顶点的名称：";
        cin >> G.vertices[i].data;
    }
    for (int i = 0; i < G.vexnum; i++)//边初始化
    {
        G.vertices[i].firstarc = NULL;
    }
    cout << "输入边关联的两个顶点时用空格隔开，如：a b" << endl;
    for (int i = 0; i < G.arcnum; i++)//录入边
    {
        VerTexType v1 = 0, v2 = 0;
        int x = -1, y = -1;
        while (x == -1 || y == -1)
        {
            cout << "请输入第" << i + 1 << "条边关联的两个顶点：";
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
                cout << "您的输入有误，请重新输入！" << endl;
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

void CreateUDG(AMGraph& G)//创建无向图邻接矩阵
{
    cout << "请输入无向图的总顶点数：";
    cin >> G.vexnum;
    cout << "请输入无向图的总边数：";
    cin >> G.arcnum;
    for (int i = 0; i < G.vexnum; i++)//录入顶点
    {
        cout << "请输入第" << i + 1 << "个顶点的名称：";
        cin >> G.vexs[i];
    }
    for (int i = 0; i < G.vexnum; i++)//边初始化
    {
        for (int j = 0; j < G.vexnum; j++)
        {
            G.arcs[i][j] = 0;
        }
    }
    cout << "输入边关联的两个顶点时用空格隔开，如：a b" << endl;
    for (int i = 0; i < G.arcnum; i++)//录入边
    {
        VerTexType v1 = 0, v2 = 0;
        int x = -1, y = -1;
        while (x == -1 || y == -1)
        {
            cout << "请输入第" << i + 1 << "条边关联的两个顶点：";
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
                cout << "您的输入有误，请重新输入！" << endl;
        }
        G.arcs[x][y] = 1;
        G.arcs[y][x] = 1;
    }
}

bool visited[MAXSIZE];

int FirstAdjVex(ALGraph& G, int v)//First函数(邻接表)
{
    if (G.vertices[v].firstarc) 
        return G.vertices[v].firstarc->adjvex;
    return -1;
}

int NextAdjVex(ALGraph& G, int v, int w)//Next函数(邻接表)
{
    ArcNode* temp = G.vertices[v].firstarc;
    while (temp) {
        if (temp->adjvex == w && temp->nextarc) 
            return temp->nextarc->adjvex;
        temp = temp->nextarc;
    }
    return -1;
}

void DFS(ALGraph& G, int v)//深度优先遍历(邻接表)
{
    cout << G.vertices[v].data << " ";
    visited[v] = true;
    for (int w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w))
    {
        if (!visited[w])
            DFS(G, w);
    }
}

void BFS(ALGraph& G, int v)//广度优先遍历(邻接表)
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

int FirstAdjVex(AMGraph& G, int v)//First函数(邻接矩阵)
{
    for (int j = 0; j < G.vexnum; j++)
    {
        if (G.arcs[v][j])
            return j;
    }
    return -1;
}

int NextAdjVex(AMGraph& G, int v, int w)//Next函数(邻接矩阵)
{
    for (int j = w + 1; j < G.vexnum; j++)
    {
        if (G.arcs[v][j])
            return j;
    }
    return -1;
}

void DFS(AMGraph& G, int v)//深度优先遍历(邻接矩阵)
{
    cout << G.vexs[v] << " ";
    visited[v] = true;
    for (int w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w))
    {
        if (!visited[w])
            DFS(G, w);
    }
}

void BFS(AMGraph& G, int v)//广度优先遍历(邻接矩阵)
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

void Test_Print(ALGraph& G)//测试输出邻接表 
{
    cout << "邻接表如下：" << endl;
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

void Test_Print(AMGraph& G)//测试输出邻接矩阵
{
    cout << "邻接矩阵如下：" << endl;
    for (int i = 0; i < G.vexnum; i++)
    {
        for (int j = 0; j < G.vexnum; j++)
        {
            cout << G.arcs[i][j] << " ";
        }
        cout << endl;
    }
}

void visited_Clear()//visited数组还原
{
    for (int i = 0; visited[i]; i++)
    {
        visited[i] = false;
    }
}

int main()
{
    int v;
    cout << "----------邻接矩阵相关操作----------" << endl;
    AMGraph AMG;
    CreateUDG(AMG);
    Test_Print(AMG);
    cout << "请输入深度遍历的起点下标(从0开始)：";
    cin >> v;
    cout << "深度遍历结果(从下标" << v << "开始)：";
    DFS(AMG, v);
    visited_Clear();
    cout << endl << "广度遍历结果(从下标" << v << "开始)：";
    BFS(AMG, v);
    visited_Clear();
    system("pause");
    system("cls");
    cout << "----------邻接表相关操作----------" << endl;
    ALGraph ALG;
    CreateUDG(ALG);
    Test_Print(ALG);
    cout << "请输入深度遍历的起点下标(从0开始)：";
    cin >> v;
    cout << "深度遍历结果(从下标" << v << "开始)：";
    DFS(ALG, v);
    visited_Clear();
    cout << endl << "广度遍历结果(从下标" << v << "开始)：";
    BFS(ALG, v);
    visited_Clear();
    return 0;
}
