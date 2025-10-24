

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

const int MAXN = 1005;

// 有向图结构
struct DirectedGraph
{
    int adj[MAXN][MAXN]; // 邻接矩阵
    int indegree[MAXN];  // 入度数组
    bool visited[MAXN];  // DFS访问标记
    int n;               // 顶点数

    void init(int vertices)
    {
        n = vertices;
        for (int i = 0; i <= n; i++)
        {
            for (int j = 0; j <= n; j++)
            {
                adj[i][j] = 0; // 0表示无边
            }
            indegree[i] = 0;
            visited[i] = false;
        }
    }

    void addEdge(int u, int v)
    {
        if (adj[u][v] == 0) // 避免重复边
        {
            adj[u][v] = 1; // 1表示有边
            indegree[v]++; // v的入度增加
        }
    }
};

// 常规实现拓扑排序 (Kahn算法)
// 实现思路：
// 1. 计算所有顶点的入度
// 2. 将入度为0的顶点加入队列
// 3. 队列不空时，取出一个顶点并输出
// 4. 删除该顶点的所有出边，更新邻接顶点的入度
// 5. 如果某个邻接顶点入度变为0，加入队列
// 6. 重复3-5直到队列为空
vector<int> topologicalSortKahn(DirectedGraph &g)
{
    vector<int> result;
    queue<int> q;
    vector<int> tempIndegree(g.n + 1);

    // 复制入度数组（避免修改原数组）
    for (int i = 1; i <= g.n; i++)
    {
        tempIndegree[i] = g.indegree[i];
        if (tempIndegree[i] == 0)
        {
            q.push(i);
        }
    }

    while (!q.empty())
    {
        int curr = q.front();
        q.pop();
        result.push_back(curr);

        // 删除当前顶点的所有出边
        for (int next = 1; next <= g.n; next++)
        {
            if (g.adj[curr][next]) // 如果存在边curr->next
            {
                tempIndegree[next]--;
                if (tempIndegree[next] == 0)
                {
                    q.push(next);
                }
            }
        }
    }

    // 检查是否存在环
    if (result.size() != g.n)
    {
        cout << "图中存在环，无法进行拓扑排序!" << endl;
        result.clear();
    }

    return result;
}

// DFS实现拓扑排序
// 实现思路：
// 1. 对每个未访问的顶点进行DFS
// 2. 在DFS中，先递归访问所有邻接顶点
// 3. 当前顶点的所有邻接顶点都访问完后，将当前顶点压入栈
// 4. 最后栈中元素的顺序就是拓扑排序的结果
void dfsTopological(DirectedGraph &g, int v, stack<int> &topoStack)
{
    g.visited[v] = true;

    // 递归访问所有邻接顶点
    for (int next = 1; next <= g.n; next++)
    {
        if (g.adj[v][next] && !g.visited[next])
        {
            dfsTopological(g, next, topoStack);
        }
    }

    // 当前顶点的所有后继都已访问，将其压入栈
    topoStack.push(v);
}

vector<int> topologicalSortDFS(DirectedGraph &g)
{
    vector<int> result;
    stack<int> topoStack;

    // 重置访问标记
    for (int i = 1; i <= g.n; i++)
    {
        g.visited[i] = false;
    }

    // 对所有未访问的顶点进行DFS
    for (int i = 1; i <= g.n; i++)
    {
        if (!g.visited[i])
        {
            dfsTopological(g, i, topoStack);
        }
    }

    // 从栈中取出元素即为拓扑排序结果
    while (!topoStack.empty())
    {
        result.push_back(topoStack.top());
        topoStack.pop();
    }

    return result;
}

// 检测有向图中的环 (DFS方法)
bool hasCycleDFS(DirectedGraph &g, int v, vector<int> &color)
{
    color[v] = 1; // 标记为正在访问

    for (int next = 1; next <= g.n; next++)
    {
        if (g.adj[v][next]) // 如果存在边v->next
        {
            if (color[next] == 1)
            {
                return true; // 发现后向边，存在环
            }
            if (color[next] == 0 && hasCycleDFS(g, next, color))
            {
                return true;
            }
        }
    }

    color[v] = 2; // 标记为已完成访问
    return false;
}

bool detectCycle(DirectedGraph &g)
{
    vector<int> color(g.n + 1, 0); // 0:未访问, 1:正在访问, 2:已完成

    for (int i = 1; i <= g.n; i++)
    {
        if (color[i] == 0)
        {
            if (hasCycleDFS(g, i, color))
            {
                return true;
            }
        }
    }
    return false;
}

// 测试函数
int main()
{
    DirectedGraph g;
    g.init(6);

    // 构建示例DAG (有向无环图)
    // 课程依赖关系: 1->2, 1->3, 2->4, 3->4, 3->5, 4->6, 5->6
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 4);
    g.addEdge(3, 5);
    g.addEdge(4, 6);
    g.addEdge(5, 6);

    cout << "Kahn算法拓扑排序: ";
    vector<int> kahnResult = topologicalSortKahn(g);
    for (int v : kahnResult)
    {
        cout << v << " ";
    }
    cout << endl;

    cout << "DFS拓扑排序: ";
    vector<int> dfsResult = topologicalSortDFS(g);
    for (int v : dfsResult)
    {
        cout << v << " ";
    }
    cout << endl;

    cout << "是否存在环: " << (detectCycle(g) ? "是" : "否") << endl;

    return 0;
}

/*
拓扑排序复杂度分析（邻接矩阵实现）：

Kahn算法 (BFS-based):
- 时间复杂度：O(V²)
  * 每个顶点入队出队一次：O(V)
  * 每次需要检查该顶点的所有可能出边：O(V)
  * 总体：O(V²)
- 空间复杂度：O(V²) - 邻接矩阵 + O(V)队列和入度数组
- 特点：
  * 基于入度的概念，直观易懂
  * 可以同时检测有向图中的环
  * 邻接矩阵实现查边效率高O(1)

DFS拓扑排序:
- 时间复杂度：O(V²)
  * 每个顶点访问一次：O(V)
  * 每次访问需要检查所有可能的邻接顶点：O(V)
  * 总体：O(V²)
- 空间复杂度：O(V²) - 邻接矩阵 + O(V)递归栈和访问标记
- 特点：
  * 基于深度优先搜索
  * 结果是后序遍历的逆序
  * 实现相对简洁

环检测:
- 时间复杂度：O(V²)
- 空间复杂度：O(V²)
- 使用三色标记法：白色(未访问)、灰色(正在访问)、黑色(已完成)

邻接矩阵优势：
1. 查询边是否存在：O(1)时间
2. 添加/删除边：O(1)时间
3. 适合稠密图
4. 实现简单直观

应用场景：
1. 课程安排问题 (先修课程依赖)
2. 任务调度 (任务间的依赖关系)
3. 编译顺序 (模块依赖)
4. 死锁检测
5. 继承关系排序
*/