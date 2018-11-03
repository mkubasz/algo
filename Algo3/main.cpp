#include <utility>
#include <iostream>
#include <cassert>
#include <vector>

using Matrix = std::vector<std::vector<int>>;

class Graph {
private:
    Matrix matrix;
    int size = 0;
    int color_size = 0;

    bool check(int v, int i, const int color[]) {
        for(int j = 0; j < size; j++) {
            if(matrix[v][j] && i == color[j])
                return false;
        }
        return true;
    }

    bool coloring(int color[], int v) {
        if(size == v)
            return true;

        for(int i = 1; i <= color_size; i++) {
            if(check(v, i, color)) {
                color[v] = i;
                if(coloring(color, v+1))
                    return true;
                color[v] = 0;
            }
        }
        return false;
    }

public:
    explicit Graph(Matrix arr,int n,int k) {
        this->matrix = std::move(arr);
        size = n;
        color_size = k;
    }

    void printResult() {
        int color[size];
        for(int i = 0; i < size; i++) {
            color[i] = 0;
        }
        if(!coloring(color, 0)) {
            std::cout << "NIE" << std::endl;
            return;
        }
        for(auto& it : color) {
            std::cout << it << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    int z = 0;
    std::cin >> z;
    assert(z >= 1);
    int n = 0, k = 0;
    std::vector<Graph> graphs;
    for(int c = 0; c < z; c++) {
        Matrix arr;
        std::cin >> n >> k;
        assert(n >= 1 && k <= 20);
        for (size_t i = 0; i < n; i++) {
            std::vector<int> row;
            for (size_t j = 0; j < n; j++) {
                int tmp = 0;
                std::cin >> tmp;
                row.push_back(tmp);
            }
            arr.push_back(row);
        }
        graphs.emplace_back(Graph(arr, n, k));
    }
    for(int i = 0; i < z; i++){
        graphs[i].printResult();
    }    return 0;
}