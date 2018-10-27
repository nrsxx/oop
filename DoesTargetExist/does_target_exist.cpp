#include <iostream>
#include <vector>

void Read_Graph(int& n, std::vector<std::vector<bool> >& Graph)
{
    std::cin >> n;
    Graph.resize(n);
    for (int cnt = 0; cnt < n; ++cnt) {
        Graph[cnt].resize(n);
    }
    int x;

    for (int cnt = 0; cnt < n; ++cnt) {
        for (int scnt = 0; scnt < n; ++scnt) {
            std::cin >> x;
            Graph[cnt][scnt] = bool(x);
        }
    }
}

bool Exist(int n, std::vector<std::vector<bool> > Graph) {
    std::vector<bool> Suitable(n, true);
    if (n == 1) {
        return false;
    }

    int good = 0;
    int a = 0;
    int b = 1;
    for (int cnt = 0; cnt < n - 1; ++cnt) {
        if ((!Graph[a][b]) || (Graph[b][a])) {
            Suitable[b] = false;
            ++b;
            good = a;
        }
        else {
            Suitable[a] = false;
            a = b;
            ++b;
            good = a;
        }
    }

    for (int cnt = 0; cnt < n; ++cnt) {
        if (cnt == good) {
            continue;
        }
        else {
            if ((!Graph[cnt][good]) || (Graph[good][cnt])) {
                return false;
            }
        }
    }
    return true;
}

int main()
{
    int n;
    std::vector<std::vector<bool> > Graph;
    Read_Graph(n, Graph);

    if (Exist(n, Graph)) {
        std::cout << "YES\n";
    }
    else {
        std::cout << "NO\n";
    }

    return 0;
}
