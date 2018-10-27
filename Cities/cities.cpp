//алгоритм дейкстры
//на двоичной куче

#include <iostream>
#include <vector>


class Graph {
private:
    std::vector<std::vector<int> > matrix;
    int start;
    int finish;

public:
    Graph() {
        int n;
        std::cin >> n;
        matrix.resize(n);
        for (int i = 0; i < n; ++i) {
            matrix[i].resize(n, 0);
        }
        int m;
        std::cin >> m;
        int x, y, w;
        for (int i = 0; i < m; ++i) {
            std::cin >> x;
            std::cin >> y;
            std::cin >> w;
            matrix[x][y] = w;
            matrix[y][x] = w;
        }
        std::cin >> start;
        std::cin >> finish;
    }

    int dijkstra() {
        int local_min;
        int local_min_index;
        std::vector<bool> used;
        std::vector<int> distance;
        distance.assign(matrix.size(), 1000000);
        distance[start] = 0;
        used.resize(matrix.size(), false);
        used[start] = true;
        int local = start;
        while (local != finish) {
            for (int i = 0; i < matrix.size(); ++i) {
                if ((matrix[local][i] > 0) &&
                    (distance[i] > distance[local] + matrix[local][i])) {
                    distance[i] = distance[local] + matrix[local][i];
                }
            }
            local_min = 1000000;
            local_min_index = -1;
            for (int i = 0; i < matrix.size(); ++i) {
                if ((!used[i]) && (distance[i] < local_min)) {
                    local_min = distance[i];
                    local_min_index = i;
                }
            }
            if (local_min_index >= 0) {
                local = local_min_index;
                used[local] = true;
            }
            else {
                break;
            }
        }
        return distance[finish];
    }
};


int main()
{
    Graph graph;
    int length = graph.dijkstra();
    std::cout << length;
    return 0;
}
