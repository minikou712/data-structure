
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

const int MAXN = 1005;

// 图的邻接矩阵表示
struct Graph
{
    int adj[MAXN][MAXN]; // 邻接矩阵
    bool visited[MAXN];  // 访问标记
    int n;               // 顶点数

    void init(int vertices)
    {
        n = vertices;
        // 初始化邻接矩阵
        for (int i = 0; i <= n; i++)
        {
            for (int j = 0; j <= n; j++)
            {
                adj[i][j] = 0; // 0表示无边
            }
            visited[i] = false;
        }
    }

    void addEdge(int u, int v)
    {
        adj[u][v] = 1; // 1表示有边
        adj[v][u] = 1; // 无向图，对称
    }
};

// DFS - 深度优先搜索
// 实现思路：
// 1. 从起始顶点开始，标记为已访问
// 2. 递归访问所有未访问的邻接顶点
// 3. 回溯到上一层继续搜索
void dfs(Graph &g, int start)
{
    cout << start << " ";
    g.visited[start] = true;

    // 遍历所有邻接顶点
    for (int next = 1; next <= g.n; next++)
    {
        if (g.adj[start][next] && !g.visited[next])
        {
            dfs(g, next);
        }
    }
}

// DFS非递归实现（使用栈）
void dfsIterative(Graph &g, int start)
{
    stack<int> s;
    s.push(start);

    while (!s.empty())
    {
        int curr = s.top();
        s.pop();

        if (!g.visited[curr])
        {
            cout << curr << " ";
            g.visited[curr] = true;

            // 将邻接顶点压入栈中
            for (int next = g.n; next >= 1; next--) // 逆序遍历保持顺序
            {
                if (g.adj[curr][next] && !g.visited[next])
                {
                    s.push(next);
                }
            }
        }
    }
}

// BFS - 广度优先搜索
// 实现思路：
// 1. 使用队列存储待访问的顶点
// 2. 从起始顶点开始，标记为已访问并入队
// 3. 队列不空时，取出队首元素，访问其所有未访问的邻接顶点
// 4. 将未访问的邻接顶点标记并入队
void bfs(Graph &g, int start)
{
    queue<int> q;
    g.visited[start] = true;
    q.push(start);

    while (!q.empty())
    {
        int curr = q.front();
        q.pop();
        cout << curr << " ";

        // 遍历所有邻接顶点
        for (int next = 1; next <= g.n; next++)
        {
            if (g.adj[curr][next] && !g.visited[next])
            {
                g.visited[next] = true;
                q.push(next);
            }
        }
    }
}

// 连通分量检测
int countConnectedComponents(Graph &g)
{
    int components = 0;

    // 重置访问标记
    for (int i = 1; i <= g.n; i++)
    {
        g.visited[i] = false;
    }

    for (int i = 1; i <= g.n; i++)
    {
        if (!g.visited[i])
        {
            components++;
            dfs(g, i); // 访问这个连通分量的所有顶点
        }
    }

    return components;
}

// 测试函数
int main()
{
    Graph g;
    g.init(6);

    // 构建示例图
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 5);
    g.addEdge(5, 6);

    cout << "DFS遍历: ";
    dfs(g, 1);
    cout << endl;

    // 重置访问标记
    for (int i = 1; i <= g.n; i++)
    {
        g.visited[i] = false;
    }

    cout << "BFS遍历: ";
    bfs(g, 1);
    cout << endl;

    cout << "连通分量数: " << countConnectedComponents(g) << endl;

    return 0;
}

/*
图搜索算法复杂度分析（邻接矩阵实现）：

DFS (深度优先搜索):
- 时间复杂度：O(V²)
  * 每个顶点访问一次：O(V)
  * 每次访问需要检查所有可能的邻接顶点：O(V)
  * 总体：O(V²)
- 空间复杂度：O(V²) - 邻接矩阵存储 + O(V)递归栈和访问标记
- 特点：
  * 沿着路径深入搜索，直到无路可走再回溯
  * 适用于路径搜索、连通性检测、拓扑排序
  * 邻接矩阵实现简单但空间开销大

BFS (广度优先搜索):
- 时间复杂度：O(V²)
  * 每个顶点访问一次：O(V)
  * 每次访问需要检查所有可能的邻接顶点：O(V)
  * 总体：O(V²)
- 空间复杂度：O(V²) - 邻接矩阵存储 + O(V)队列和访问标记
- 特点：
  * 按层次逐步扩展搜索范围
  * 适用于最短路径搜索（无权图）、层序遍历
  * 保证找到的路径是最短的（边数最少）

邻接矩阵 vs 邻接表：
- 邻接矩阵：
  * 时间复杂度：O(V²)，适合稠密图
  * 空间复杂度：O(V²)
  * 查找边的时间：O(1)
  * 添加/删除边的时间：O(1)

- 邻接表：
  * 时间复杂度：O(V + E)，适合稀疏图
  * 空间复杂度：O(V + E)
  * 查找边的时间：O(degree)
  * 添加边的时间：O(1)

应用场景：
1. DFS适用于：路径搜索、连通性判断、环检测、拓扑排序
2. BFS适用于：最短路径、层次遍历、最少步数问题
3. 邻接矩阵适用于：稠密图、需要频繁查询边是否存在的场景
*/