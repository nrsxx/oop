#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

class edge {
private:

public:
    int capacity;
    int current_flow;
    edge(int cap) {
        capacity = cap;
        current_flow = 0;
    }
};

class network {
private:
    int size;
    std::vector<std::vector<edge> > edges;
    std::vector<int> distances_from_source;

    int pass_flow() {
        bool flag = false;
        std::queue<int> queue_for_dfs;
        std::vector<int> parents;
        parents.resize(size);
        parents[0] = 0;
        distances_from_source[0] = 0;
        for (int i = 1; i < size; ++i) {
            distances_from_source[i] = -1;
        }
        queue_for_dfs.push(0);
        int cur_vertex;
        while (queue_for_dfs.size() > 0 && cur_vertex != size - 1) {
            cur_vertex = queue_for_dfs.front();
            queue_for_dfs.pop();
            if (cur_vertex == size - 1) {
                flag = true;
            }
            for (int i = 0; i < size; ++i) {
                if (distances_from_source[i] == -1 && edges[cur_vertex][i].capacity - edges[cur_vertex][i].current_flow > 0) {
                    distances_from_source[i] = distances_from_source[cur_vertex] + 1;
                    queue_for_dfs.push(i);
                    parents[i] = cur_vertex;
                }
            }
        }

        if (!flag) {
            return 0;
        }
        cur_vertex = size - 1;
        int max_flow = 100000;
        while (cur_vertex > 0) {
            max_flow = std::min(max_flow, edges[parents[cur_vertex]][cur_vertex].capacity -
                                edges[parents[cur_vertex]][cur_vertex].current_flow);
            cur_vertex = parents[cur_vertex];
        }
        cur_vertex = size - 1;
        while (cur_vertex > 0) {
            edges[parents[cur_vertex]][cur_vertex].current_flow += max_flow;
            edges[cur_vertex][parents[cur_vertex]].current_flow -= max_flow;
            cur_vertex = parents[cur_vertex];
        }
        return max_flow;
    }

public:
    network(int n, int m, std::ifstream& in) {
        size = n;
        edges.resize(n);
        for (int i = 0; i < n; ++i) {
            edges[i].assign(n, edge(0));
        }
        distances_from_source.resize(n);
        int cur_begin;
        int cur_end;
        int cur_capacity;
        for (int i = 0; i < m; ++i) {
            in >> cur_begin >> cur_end >> cur_capacity;
            edges[cur_begin - 1][cur_end - 1].capacity += cur_capacity;
        }
    }

    int count_max_flow() {
        int result = 0;
        int cur_flow = pass_flow();
        while (cur_flow > 0) {
            result += cur_flow;
            cur_flow = pass_flow();
        }
        return result;
    }
};

int main()
{
    int n, m;
    std::ifstream in("maxflow.in");
    std::ofstream out("maxflow.out");
    in >> n >> m;
    if (n == 1) {
        out << "0";
        return 0;
    }
    network graph = network(n, m, in);
    out << graph.count_max_flow();
    return 0;
}
