#include <iostream>
#include <cassert>
#include <vector>

class Graph {
private:
    std::vector<std::vector<int>> arr;
    int size = 0;
    int connections = 0;
    bool result = false;
    bool bipartite = true;

    void dfs() {
        int discover[size];
        int counter = 0;
        for (int i = 0; i < size; i++) {
            discover[i] = -1;
        }
        for(int i = 0; i < size; i++) {
            if(discover[i] == -1) {
                int color[size];
                color[0] = 0;
                dfs_visit(counter, discover, i, color);
                connections++;
            }
        }
    }

    void dfs_visit(int& counter, int discover[], int v, int color[]) {
        counter++;
        discover[v] = 0;

        for (int i = 0; i < size; i++) {
            if(arr[v][i] != 0 && discover[i] == -1){
                color[i] = !color[v];
                dfs_visit(counter, discover, i, color);
            }
            else if(arr[v][i] != 0 && discover[i] == 1) {
                if(color[i] == color[v]) {
                    bipartite = false;
                }
                result = true;
            }

        }
        counter++;
        discover[v] = 1;
    }

public:
    explicit Graph(std::vector<std::vector<int>> arr, int size){
        this->arr = std::move(arr);
        this->size = size;
        dfs();
    }

    bool is_bipartite() {
        return bipartite;
    }

    bool is_connectivity() {
        return connections == 1;
    }

    bool is_cycled() {
        return result;
    }

    bool is_tree() {
        return is_connectivity() && !is_cycled();
    }

    void printResult(int id) {
        std::cout << "Graf " << id << std::endl;
        std::cout << "Dwudzielny " << (is_bipartite() ? "TAK" : "NIE") << std::endl;
        std::cout << "Spojny " << (is_connectivity() ? "TAK" : "NIE") <<" (" << connections << ")" << std::endl;
        std::cout << "Cykle " << (is_cycled() ? "TAK" : "NIE") << std::endl;
        std::cout << "Drzewo " << (is_tree() ? "TAK" : "NIE") << std::endl;
    }
};

int main() {
    int z = 0;
    std::cin >> z;
    assert(z >= 1 && z <= 100);
    int n = 0;
    std::vector<Graph> graphs;
    for(int c = 0; c < z; c++) {
        std::vector<std::vector<int>> arr;
        std::cin >> n;
        assert(n >= 2 && n <= 20);
        for (size_t i = 0; i < n; i++) {
            std::vector<int> row;
            for (size_t j = 0; j < n; j++) {
                int tmp = 0;
                std::cin >> tmp;
                row.push_back(tmp);
            }
            arr.push_back(row);
        }
        graphs.emplace_back(Graph(arr, n));
    }
    for(int i = 0; i < z; i++){
        graphs[i].printResult(i+1);
    }
    return 0;
}