#include <iostream>
#include <vector>

void Read_Graph(int& n, int& m, std::vector<std::vector<bool> >& Graph)
{
    std::cin >> n;
    std::cin >> m;
    Graph.resize(n);
    for (int cnt = 0; cnt < n; ++cnt) {
        Graph[cnt].resize(n);
    }
    int a, b;

    for (int cnt = 0; cnt < m; ++cnt) {
        std::cin >> a;
        std::cin >> b;
        Graph[a][b] = true;
    }
}



int main()
{

    return 0;
}
