

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
using namespace std;

const int MAXN = 1005;
const int INF = INT_MAX;

// 边结构（用于Kruskal算法）
struct Edge
{
    int u, v;   // 边的两个端点
    int weight; // 边的权重

    Edge(int u, int v, int w) : u(u), v(v), weight(w) {}

    // 用于排序的比较函数
    bool operator<(const Edge &other) const
    {
        return weight < other.weight;
    }
};

// 图结构
struct Graph
{
    int adj[MAXN][MAXN]; // 邻接矩阵存储权重
    vector<Edge> edges;  // 边集合（用于Kruskal算法）
    bool inMST[MAXN];    // 是否在MST中
    int key[MAXN];       // Prim算法中的key值
    int parent[MAXN];    // 父节点
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
            inMST[i] = false;
            key[i] = INF;
            parent[i] = -1;
        }
        edges.clear();
    }

    void addEdge(int u, int v, int w)
    {
        adj[u][v] = w;
        adj[v][u] = w; // 无向图
        edges.push_back(Edge(u, v, w));
    }
};

// 并查集结构（用于Kruskal算法）
struct UnionFind
{
    int parent[MAXN];
    int rank[MAXN];

    void init(int n)
    {
        for (int i = 0; i <= n; i++)
        {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    int find(int x)
    {
        if (parent[x] != x)
        {
            parent[x] = find(parent[x]); // 路径压缩
        }
        return parent[x];
    }

    bool unite(int x, int y)
    {
        int px = find(x), py = find(y);
        if (px == py)
            return false;

        // 按秩合并
        if (rank[px] < rank[py])
        {
            parent[px] = py;
        }
        else if (rank[px] > rank[py])
        {
            parent[py] = px;
        }
        else
        {
            parent[py] = px;
            rank[px]++;
        }
        return true;
    }
};

// Prim算法 - 最小生成树
// 实现思路：
// 1. 选择一个起始顶点，将其加入MST
// 2. 维护一个优先队列，存储连接MST和非MST顶点的边
// 3. 每次选择权重最小的边，将新顶点加入MST
// 4. 更新优先队列，添加新顶点的所有边
// 5. 重复2-4直到所有顶点都在MST中
vector<Edge> primMST(Graph &g)
{
    vector<Edge> mst;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // 初始化
    for (int i = 1; i <= g.n; i++)
    {
        g.inMST[i] = false;
        g.key[i] = INF;
        g.parent[i] = -1;
    }

    // 从顶点1开始
    g.key[1] = 0;
    pq.push({0, 1});

    while (!pq.empty())
    {
        int weight = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (g.inMST[u])
            continue;

        g.inMST[u] = true;

        // 如果不是起始顶点，添加边到MST
        if (g.parent[u] != -1)
        {
            mst.push_back(Edge(g.parent[u], u, weight));
        }

        // 更新邻接顶点的key值
        for (int v = 1; v <= g.n; v++)
        {
            if (g.adj[u][v] < INF) // 如果存在边u-v
            {
                int w = g.adj[u][v];
                if (!g.inMST[v] && w < g.key[v])
                {
                    g.key[v] = w;
                    g.parent[v] = u;
                    pq.push({w, v});
                }
            }
        }
    }

    return mst;
}

// Kruskal算法 - 最小生成树
// 实现思路：
// 1. 将所有边按权重从小到大排序
// 2. 初始化并查集，每个顶点为一个连通分量
// 3. 按顺序考虑每条边
// 4. 如果边的两个端点在不同连通分量中，添加这条边到MST
// 5. 合并两个连通分量
// 6. 重复3-5直到MST包含V-1条边
vector<Edge> kruskalMST(Graph &g)
{
    vector<Edge> mst;
    UnionFind uf;

    // 初始化并查集
    uf.init(g.n);

    // 按权重排序所有边
    vector<Edge> sortedEdges = g.edges;
    sort(sortedEdges.begin(), sortedEdges.end());

    // 遍历排序后的边
    for (const Edge &e : sortedEdges)
    {
        if (uf.unite(e.u, e.v))
        {
            mst.push_back(e);

            // 如果已经有V-1条边，MST构建完成
            if (mst.size() == g.n - 1)
            {
                break;
            }
        }
    }

    return mst;
}

// 计算MST的总权重
int calculateMSTWeight(const vector<Edge> &mst)
{
    int totalWeight = 0;
    for (const Edge &e : mst)
    {
        totalWeight += e.weight;
    }
    return totalWeight;
}

// 打印MST
void printMST(const vector<Edge> &mst, const string &algorithm)
{
    cout << "=== " << algorithm << " 最小生成树 ===" << endl;
    cout << "边: ";
    for (const Edge &e : mst)
    {
        cout << "(" << e.u << "-" << e.v << ":" << e.weight << ") ";
    }
    cout << endl;
    cout << "总权重: " << calculateMSTWeight(mst) << endl;
}

// 判断图是否连通（用于验证MST是否存在）
bool isConnected(Graph &g)
{
    vector<bool> visited(g.n + 1, false);
    queue<int> q;

    q.push(1);
    visited[1] = true;
    int visitedCount = 1;

    while (!q.empty())
    {
        int curr = q.front();
        q.pop();

        for (int next = 1; next <= g.n; next++)
        {
            if (g.adj[curr][next] < INF && !visited[next])
            {
                visited[next] = true;
                q.push(next);
                visitedCount++;
            }
        }
    }

    return visitedCount == g.n;
}

// 测试函数
int main()
{
    Graph g;
    g.init(6);

    // 构建示例图
    g.addEdge(1, 2, 4);
    g.addEdge(1, 3, 2);
    g.addEdge(2, 3, 1);
    g.addEdge(2, 4, 5);
    g.addEdge(3, 4, 8);
    g.addEdge(3, 5, 10);
    g.addEdge(4, 5, 2);
    g.addEdge(4, 6, 6);
    g.addEdge(5, 6, 3);

    // 检查图的连通性
    if (!isConnected(g))
    {
        cout << "图不连通，无法构建最小生成树!" << endl;
        return 1;
    }

    // Prim算法
    vector<Edge> primResult = primMST(g);
    printMST(primResult, "Prim算法");

    cout << endl;

    // Kruskal算法
    vector<Edge> kruskalResult = kruskalMST(g);
    printMST(kruskalResult, "Kruskal算法");

    // 验证两种算法结果的权重是否相同
    cout << "\n权重验证: ";
    if (calculateMSTWeight(primResult) == calculateMSTWeight(kruskalResult))
    {
        cout << "两种算法得到的MST权重相同 ✓" << endl;
    }
    else
    {
        cout << "两种算法得到的MST权重不同 ✗" << endl;
    }

    return 0;
}

/*
最小生成树算法复杂度分析（邻接矩阵实现）：

Prim算法:
- 时间复杂度：O(V² log V) - 使用优先队列
  * 每个顶点最多入队一次：O(V log V)
  * 每次需要检查所有可能的邻接顶点：O(V)
  * 总体：O(V² log V)
- 简单实现时间复杂度：O(V²) - 不使用优先队列，适用于稠密图
- 空间复杂度：O(V²) - 邻接矩阵
- 特点：
  * 从顶点的角度构建MST
  * 每次添加一个顶点到MST中
  * 邻接矩阵天然适合稠密图
  * 查边效率高O(1)

Kruskal算法:
- 时间复杂度：O(V² log V²) = O(V² log V)
  * 收集所有边：O(V²)
  * 排序所有边：O(V² log V²)
  * 并查集操作：O(V² α(V))
- 空间复杂度：O(V²) - 邻接矩阵 + 边集合
- 特点：
  * 从边的角度构建MST
  * 需要先收集所有边再排序
  * 邻接矩阵实现边数较多，不如邻接表高效

并查集优化:
- 路径压缩：使查找操作近似O(1)
- 按秩合并：保持树的平衡
- 总体操作复杂度：O(α(n))，实际应用中可视为常数

邻接矩阵实现特点:
1. 空间复杂度固定为O(V²)
2. 查边时间复杂度为O(1)
3. 适合稠密图或小规模图
4. Prim算法更适合邻接矩阵实现
5. 实现简单，无需复杂的数据结构

算法选择建议:
1. 稠密图：选择Prim算法（邻接矩阵实现）
2. 稀疏图：选择Kruskal算法（邻接表实现更优）
3. 小规模图：邻接矩阵实现简单直观
4. 内存受限：考虑邻接表实现

应用场景:
1. 网络设计（最小成本连接所有节点）
2. 电路设计（最小布线长度）
3. 聚类分析
4. 近似算法的基础组件
5. 图像分割
*/