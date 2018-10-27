#include <iostream>
#include <queue>
#define INF 50001

int bfs(int n, std::vector<std::vector<bool> >& Graph, int Source, int Target) {
    std::queue<int> Queue;
    Queue.push(Source);

    std::vector<int> Colour(n, 0);
    for (int cnt = 0; cnt < n; ++cnt) {
        Colour[cnt] = 0;
    }

    std::vector<int> Length(n, INF);
    Length[Source] = 0;

    while(!Queue.empty()) {
        int local_vertex = Queue.front();
        Queue.pop();
        Colour[local_vertex] = 2;

        for (int cnt = 0; cnt < n; ++cnt) {
            if (Graph[local_vertex][cnt]) {
                if (Colour[cnt] == 1) {
                    if (Length[cnt] + Length[local_vertex] > 1) {
                        return Length[local_vertex] + Length[cnt] + 1;
                    }
                }
                if (Colour[cnt] == 0) {
                    Length[cnt] = Length[local_vertex] + 1;
                    Queue.push(cnt);
                    Colour[cnt] = 1;
                }
            }
        }
    }
    return INF;
}

int main()
{
    int N, M;
    int local_source, local_target;
    int length = INF;
    std::cin >> N;
    std::cin >> M;
    std::vector<std::vector<bool> > Graph;
    Graph.resize(N);
    for (int cnt = 0; cnt < N; ++cnt) {
        Graph[cnt].resize(N);
        for (int sec_cnt = 0; sec_cnt < N; ++sec_cnt) {
            Graph[cnt][sec_cnt] = false;
        }
    }

    for (int cnt = 0; cnt < M; ++cnt) {
        std::cin >> local_source;
        std::cin >> local_target;
        Graph[local_source][local_target] = true;
        Graph[local_target][local_source] = true;
    }

    for (int cnt = 0; cnt < N; ++cnt) {
        length = std::min(bfs(N, Graph, cnt, cnt), length);
    }
    if (length == INF) {
        length = -1;
    }

    std::cout << length;
    return 0;
}
