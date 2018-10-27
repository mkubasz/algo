#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>

class Graph {
private:
    void union_set(int u, int v) {
        parent[u] = parent[v];
    }

    int find_set(int u) {
        if(u != parent[u])
            parent[u] = find_set(parent[u]);
        return parent[u];
    }

    int compute(){
        int sum = 0, u = 0, v = 0;
        std::sort(edges.begin(), edges.end());
        for (auto &it : edges) {
            u = find_set(it.second.first);
            v = find_set(it.second.second);
            if(u != v) {
                sum += it.first;
                union_set(u, v);
            }
        }
        return sum;
    }

public:
    std::vector<std::pair<int, std::pair<int,int>>> edges;
    std::vector<int> parent;

    explicit Graph(int size) {
        for(int i = 0; i <= size; i++) {
            parent.push_back(i);
        }
    }

    void push(int u, int v, int w) {
        edges.emplace_back(std::make_pair(w, std::make_pair(u,v)));
    }

    void printResult() {
        std::cout << compute() << std::endl;
    }
};

int main() {
    int z = 0;
    std::cin >> z;
    assert(z >= 1 && z <= 100);
    int n = 0, m = 0;
    std::vector<Graph> graphs;
    for(int c = 0; c < z; c++) {
        std::cin >> n >> m;
        assert(n >= 2 && n <= 20);
        Graph g(n);
        for (size_t i = 0; i < m; i++) {
            int u, v, w;
            std::cin >> u >> v >> w;
            g.push(u, v, w);
        }
        graphs.emplace_back(g);
    }
    for(int i = 0; i < z; i++){
        graphs[i].printResult();
    }
    return 0;
}