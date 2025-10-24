

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

const int MAXN = 1005;
const int INF = INT_MAX;

// 带权图结构
struct WeightedGraph
{
    int adj[MAXN][MAXN]; // 邻接矩阵存储权重
    bool visited[MAXN];  // 访问标记
    int dist[MAXN];      // 距离数组
    int n;               // 顶点数

    void init(int vertices)
    {
        n = vertices;
        for (int i = 0; i <= n; i++)
        {
            for (int j = 0; j <= n; j++)
            {
                adj[i][j] = (i == j) ? 0 : INF; // 自己到自己距离为0，其他为无穷
            }
            visited[i] = false;
            dist[i] = INF;
        }
    }

    void addEdge(int u, int v, int w = 1)
    {
        adj[u][v] = w; // 有向边
        adj[v][u] = w; // 无向图，对称
    }

    void addDirectedEdge(int u, int v, int w)
    {
        adj[u][v] = w; // 有向边
    }
};

// 不带权最短路径 - BFS
// 实现思路：
// 1. 使用BFS遍历，每层距离递增1
// 2. 第一次访问到目标顶点时，即为最短路径
// 3. 适用于无权图或所有边权重相等的图
void bfsShortestPath(WeightedGraph &g, int start)
{
    queue<int> q;

    // 初始化
    for (int i = 1; i <= g.n; i++)
    {
        g.visited[i] = false;
        g.dist[i] = INF;
    }

    g.dist[start] = 0;
    g.visited[start] = true;
    q.push(start);

    while (!q.empty())
    {
        int curr = q.front();
        q.pop();

        // 遍历所有邻接顶点
        for (int next = 1; next <= g.n; next++)
        {
            // 检查是否存在边且权重为1（无权图的标准权重）
            if (g.adj[curr][next] == 1 && !g.visited[next])
            {
                g.visited[next] = true;
                g.dist[next] = g.dist[curr] + 1;
                q.push(next);
            }
        }
    }
}

// 带权最短路径 - Dijkstra算法
// 实现思路：
// 1. 初始化源点距离为0，其他点距离为无穷大
// 2. 选择距离最小的未访问顶点
// 3. 更新该顶点所有邻接顶点的距离（松弛操作）
// 4. 标记该顶点为已访问
// 5. 重复2-4直到所有顶点都被访问
void dijkstra(WeightedGraph &g, int start)
{
    // 优先队列：{距离, 顶点}
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // 初始化
    for (int i = 1; i <= g.n; i++)
    {
        g.visited[i] = false;
        g.dist[i] = INF;
    }

    g.dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty())
    {
        int currDist = pq.top().first;
        int curr = pq.top().second;
        pq.pop();

        if (g.visited[curr])
            continue;
        g.visited[curr] = true;

        // 松弛操作
        for (int next = 1; next <= g.n; next++)
        {
            if (g.adj[curr][next] < INF) // 如果存在边curr->next
            {
                int newDist = currDist + g.adj[curr][next];
                if (newDist < g.dist[next])
                {
                    g.dist[next] = newDist;
                    pq.push({newDist, next});
                }
            }
        }
    }
}

// 可以处理负权值最短路径 - Bellman-Ford算法
// 实现思路：
// 1. 初始化源点距离为0，其他点距离为无穷大
// 2. 进行V-1轮松弛操作
// 3. 每轮对所有边进行松弛
// 4. 第V轮检查是否还能松弛，如果能则存在负权环
bool bellmanFord(WeightedGraph &g, int start)
{
    // 存储所有边
    vector<tuple<int, int, int>> edges; // {from, to, weight}

    // 收集所有边
    for (int u = 1; u <= g.n; u++)
    {
        for (int v = 1; v <= g.n; v++)
        {
            if (g.adj[u][v] < INF) // 如果存在边u->v
            {
                edges.push_back({u, v, g.adj[u][v]});
            }
        }
    }

    // 初始化距离
    for (int i = 1; i <= g.n; i++)
    {
        g.dist[i] = INF;
    }
    g.dist[start] = 0;

    // 进行V-1轮松弛
    for (int i = 1; i < g.n; i++)
    {
        for (const auto &edge : edges)
        {
            int u = get<0>(edge);
            int v = get<1>(edge);
            int w = get<2>(edge);

            if (g.dist[u] != INF && g.dist[u] + w < g.dist[v])
            {
                g.dist[v] = g.dist[u] + w;
            }
        }
    }

    // 检查负权环
    for (const auto &edge : edges)
    {
        int u = get<0>(edge);
        int v = get<1>(edge);
        int w = get<2>(edge);

        if (g.dist[u] != INF && g.dist[u] + w < g.dist[v])
        {
            return false; // 存在负权环
        }
    }

    return true; // 不存在负权环
}

// Floyd-Warshall算法 - 所有顶点对最短路径
// 实现思路：
// 1. 使用邻接矩阵存储图
// 2. 三重循环：k为中间顶点，i,j为起点和终点
// 3. 如果通过k的路径更短，则更新距离
void floydWarshall(int graph[][MAXN], int n)
{
    int dist[MAXN][MAXN];

    // 初始化距离矩阵
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            dist[i][j] = graph[i][j];
        }
    }

    // 三重循环
    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (dist[i][k] != INF && dist[k][j] != INF)
                {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    // 输出结果
    cout << "所有顶点对最短距离:" << endl;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (dist[i][j] == INF)
            {
                cout << "INF ";
            }
            else
            {
                cout << dist[i][j] << " ";
            }
        }
        cout << endl;
    }
}

// 打印最短路径距离
void printDistances(WeightedGraph &g, int start)
{
    cout << "从顶点 " << start << " 到各顶点的最短距离:" << endl;
    for (int i = 1; i <= g.n; i++)
    {
        cout << "到顶点 " << i << ": ";
        if (g.dist[i] == INF)
        {
            cout << "INF" << endl;
        }
        else
        {
            cout << g.dist[i] << endl;
        }
    }
}

// 测试函数
int main()
{
    WeightedGraph g;
    g.init(5);

    // 构建示例带权图
    g.addEdge(1, 2, 4);
    g.addEdge(1, 3, 2);
    g.addEdge(2, 3, 1);
    g.addEdge(2, 4, 5);
    g.addEdge(3, 4, 8);
    g.addEdge(3, 5, 10);
    g.addEdge(4, 5, 2);

    cout << "=== BFS最短路径 (无权图) ===" << endl;
    bfsShortestPath(g, 1);
    printDistances(g, 1);

    cout << "\n=== Dijkstra最短路径 ===" << endl;
    dijkstra(g, 1);
    printDistances(g, 1);

    cout << "\n=== Bellman-Ford最短路径 ===" << endl;
    if (bellmanFord(g, 1))
    {
        cout << "不存在负权环" << endl;
        printDistances(g, 1);
    }
    else
    {
        cout << "存在负权环!" << endl;
    }

    return 0;
}

/*
最短路径算法复杂度分析（邻接矩阵实现）：

BFS (无权图最短路径):
- 时间复杂度：O(V²)
  * 每个顶点最多访问一次：O(V)
  * 每次访问需要检查所有可能的邻接顶点：O(V)
- 空间复杂度：O(V²) - 邻接矩阵 + O(V)队列和访问标记
- 特点：
  * 只适用于无权图或等权图
  * 保证找到最短路径（边数最少）
  * 邻接矩阵实现简单但空间开销大

Dijkstra算法:
- 时间复杂度：O(V² log V) - 使用优先队列
  * 每个顶点最多入队一次：O(V log V)
  * 每次松弛需要检查所有邻接顶点：O(V)
  * 总体：O(V² log V)
- 简单实现时间复杂度：O(V²) - 不使用优先队列
- 空间复杂度：O(V²) - 邻接矩阵
- 特点：
  * 适用于非负权图
  * 贪心算法，每次选择距离最小的顶点
  * 邻接矩阵查边效率高O(1)

Bellman-Ford算法:
- 时间复杂度：O(V³)
  * V-1轮松弛：O(V)
  * 每轮需要检查所有可能的边：O(V²)
  * 总体：O(V³)
- 空间复杂度：O(V²) - 邻接矩阵
- 特点：
  * 可以处理负权边
  * 可以检测负权环
  * 基于动态规划思想

Floyd-Warshall算法:
- 时间复杂度：O(V³)
- 空间复杂度：O(V²)
- 特点：
  * 计算所有顶点对之间的最短路径
  * 可以处理负权边（但不能有负权环）
  * 天然适合邻接矩阵实现
  * 实现简单，代码紧凑

邻接矩阵适用场景：
1. 稠密图（边数接近V²）
2. 需要频繁查询边是否存在
3. Floyd-Warshall等基于矩阵的算法
4. 小规模图且内存充足

选择建议：
1. 无权图：使用BFS
2. 非负权图，单源最短路径：使用Dijkstra
3. 有负权边，单源最短路径：使用Bellman-Ford
4. 所有顶点对最短路径：使用Floyd-Warshall
5. 稀疏图：优先选择邻接表 + Dijkstra
6. 稠密图：可以考虑Floyd-Warshall
*/