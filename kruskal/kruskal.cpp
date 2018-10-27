#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

struct edge {
    int left;
    int right;
    int weight;

    bool operator<(const edge& other) {
        return weight < other.weight;
    }
};

class dsu {
private:
    std::vector<int> parents;

public:
    dsu(int n) {
        parents.resize(n);
        for (int i = 0; i < n; ++i) {
            parents[i] = i;
        }
    }

    int get_root(int n) {
        int root = n;
        while (parents[root] != root) {
            root = parents[root];
        }
        while (parents[n] != n) {
            int j = parents[n];
            parents[n] = root;
            n = j;
        }
        return root;
    }

    bool unite(int left, int right) {
        left = get_root(left);
        right = get_root(right);
        if (rand() & 1) {
            std::swap(left, right);
        }

        if (left != right) {
            parents[left] = right;
            return true;
        }
        return false;
    }
};

int main() {

    std::ifstream in("kruskal.in");
    std::ofstream out("kruskal.out");

    int n, m;
    in >> n;
    in >> m;
    std::vector<struct edge> edges;
    edges.resize(m);

    for (int i = 0; i < m; ++i) {
        in >> edges[i].left;
        --edges[i].left;
        in >> edges[i].right;
        --edges[i].right;
        in >> edges[i].weight;
    }
    std::sort(edges.begin(), edges.end());

    dsu graph(n);
    int result = 0;
    for (int i = 0; i < m; ++i) {
        if (graph.unite(edges[i].left, edges[i].right)) {
            result += edges[i].weight;
        }
    }
    out << result;
    in.close();
    out.close();
    return 0;
}
