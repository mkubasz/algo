#include <iostream>
#include <cassert>
#include <vector>
#include <queue>
#include <limits>
#include <list>

typedef int vertex_t;
typedef double weight_t;
const weight_t max_weight = std::numeric_limits<double>::infinity();

struct neighbor {
    vertex_t target;
    weight_t weight;
    neighbor(vertex_t arg_target, weight_t arg_weight)
            : target(arg_target), weight(arg_weight) { }
};

typedef std::vector<std::vector<neighbor> > adjacency_list_t;
typedef std::pair<weight_t, vertex_t> weight_vertex_pair_t;


class Graph {
private:
    int vertex, number;
    adjacency_list_t adjacency_list;
public:
    void DijkstraComputePaths(vertex_t source,
                              const adjacency_list_t &adjacency_list,
                              std::vector<weight_t> &min_distance,
                              std::vector<vertex_t> &previous)
    {
        int n = static_cast<int>(adjacency_list.size());
        min_distance.clear();
        min_distance.resize(n, max_weight);
        min_distance[source] = 0;
        previous.clear();
        previous.resize(n, -1);
        std::priority_queue<weight_vertex_pair_t,
                std::vector<weight_vertex_pair_t>,
                std::greater<> > vertex_queue;
        vertex_queue.push(std::make_pair(min_distance[source], source));

        while (!vertex_queue.empty())
        {
            weight_t dist = vertex_queue.top().first;
            vertex_t u = vertex_queue.top().second;
            vertex_queue.pop();
            if (dist > min_distance[u])
                continue;
            const std::vector<neighbor> &neighbors = adjacency_list[u];
            for (auto neighbor : neighbors) {
                vertex_t v = neighbor.target;
                weight_t weight = neighbor.weight;
                weight_t distance_through_u = dist + weight;
                if (distance_through_u < min_distance[v]) {
                    min_distance[v] = distance_through_u;
                    previous[v] = u;
                    vertex_queue.push(std::make_pair(min_distance[v], v));
                }
            }
        }
    }

    std::vector<vertex_t> DijkstraGetShortestPathTo(
            vertex_t vertex, const std::vector<vertex_t> &previous)
    {
        std::vector<vertex_t> path;
        for ( ; vertex != -1; vertex = previous[vertex])
            path.emplace_back(vertex);
        return path;
    }

    Graph(int number, int v, int e) :adjacency_list(static_cast<unsigned long>(v + 1)) {
        vertex = v;
        this->number = number;
    }

    void addEdge(int b, int e, int w) {
        adjacency_list[b].push_back(neighbor(e, w));
    }

    void print_result() {

        std::cout << "Graf nr " << number << std::endl;

        for (int j = 2; j <= vertex; j++) {
            std::vector<weight_t> min_distance;
            std::vector<vertex_t> previous;
            DijkstraComputePaths(1, adjacency_list, min_distance, previous);
            std::vector<vertex_t> path = DijkstraGetShortestPathTo(j, previous);
            if(min_distance[j] == max_weight) {
                std::cout << "NIE ISTNIEJE DROGA Z " << 1 << " DO " << j << std::endl;
                continue;
            }
                for (unsigned long i = path.size()-1; i >= 0 ; i--) {
                    if(i == 0){
                        std::cout << path[i];
                        break;
                    }
                    std::cout << path[i] << "-";
                }
                std::cout << " " << min_distance[j] << std::endl;
            }
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
        Graph g(c+1, n, m);
        for (size_t i = 0; i < m; i++) {
            int b, e, w = 0;
            std::cin >> b >> e >> w;
            g.addEdge(b, e, w);
        }
        graphs.emplace_back(g);
    }
    for(auto &g: graphs){
        g.print_result();
    }
    return 0;
}