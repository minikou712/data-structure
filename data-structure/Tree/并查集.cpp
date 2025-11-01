#include <iostream>
#include <vector>

using namespace std;

// 并查集类
class UnionFind {
private:
    vector<int> parent; // 存储每个节点的父节点
    vector<int> rank;   // 存储每个节点的秩（树的深度）

public:
    // 初始化并查集
    UnionFind(int size) {
        parent.resize(size);
        rank.resize(size, 1); // 初始时每个节点的秩为1
        for (int i = 0; i < size; ++i) {
            parent[i] = i; // 每个节点的父节点初始化为自己
        }
    }

    // 查找操作，带路径压缩
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // 递归查找并压缩路径
        }
        return parent[x];
    }

    // 合并操作，按秩合并
    void unionSet(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX; // 将秩小的树挂到秩大的树上
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX] += 1; // 如果秩相同，增加新根的秩
            }
        }
    }

    // 判断两个节点是否属于同一集合
    bool isConnected(int x, int y) {
        return find(x) == find(y);
    }
};

int main() {
    // 初始化一个大小为10的并查集
    UnionFind uf(10);

    // 合并一些节点
    uf.unionSet(1, 2);
    uf.unionSet(2, 3);
    uf.unionSet(4, 5);

    // 检查连接情况
    cout << "1和3是否连通: " << (uf.isConnected(1, 3) ? "是" : "否") << endl;
    cout << "1和4是否连通: " << (uf.isConnected(1, 4) ? "是" : "否") << endl;

    // 合并更多节点
    uf.unionSet(3, 4);

    // 再次检查连接情况
    cout << "1和4是否连通: " << (uf.isConnected(1, 4) ? "是" : "否") << endl;

    return 0;
}