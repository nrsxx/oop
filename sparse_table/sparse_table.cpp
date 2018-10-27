#include <iostream>
#include <vector>
#include <cmath>

int get_log(int n) {
    double log = std::log10(n) / std::log10(2);
    return std::ceil(log);
}

struct sparse_table {
    int size;
    std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > > table;
};

std::pair<std::pair<int, int>, std::pair<int, int> > get_mins(std::pair<std::pair<int, int>, std::pair<int, int> > pair1,
                                                              std::pair<std::pair<int, int>, std::pair<int, int> > pair2) {

    std::pair<std::pair<int, int>, std::pair<int, int> > answer;

    if (pair1.first.first < pair2.first.first) {
        answer.first.first = pair1.first.first;
        answer.first.second = pair1.first.second;
        if (pair1.second.first < pair2.first.first) {
            answer.second.first = pair1.second.first;
            answer.second.second = pair1.second.second;
        } else {
            answer.second.first = pair2.first.first;
            answer.second.second = pair2.first.second;
        }
    } else {
        if (pair1.first.second != pair2.first.second) {
            answer.first.first = pair2.first.first;
            answer.first.second = pair2.first.second;
            if (pair2.second.first < pair1.first.first) {
                answer.second.first = pair2.second.first;
                answer.second.second = pair2.second.second;
            } else {
                answer.second.first = pair1.first.first;
                answer.second.second = pair1.first.second;
            }
        } else {
            answer.first = pair1.first;
            if (pair2.second.first < pair1.second.first) {
                answer.second.first = pair2.second.first;
                answer.second.second = pair2.second.second;
            } else {
                answer.second.first = pair1.second.first;
                answer.second.second = pair1.second.second;
            }
        }
    }
    return answer;
}

int rmq(int i, int j, struct sparse_table& table) {
    int k = get_log(j - i + 1);
    return get_mins(table.table[k - 1][i], table.table[k - 1][j - std::pow(2, k - 1) + 1]).second.first;
}

struct sparse_table create(int size, std::vector<int>& array) {
    struct sparse_table table;
    table.size = size;
    table.table.resize(get_log(size));
    for (int i = 0; i < get_log(size); ++i){
        table.table[i].resize(size);
    }

    for (int i = 0; i < size; ++i) {
        table.table[0][i].first.first = array[i];
        table.table[0][i].first.second = i;
        table.table[0][i].second.first = 100000;
        table.table[0][i].second.second = 100000;
    }

    for (int i = 1; i < get_log(size); ++i) {
        for (int j = 0; j < size; ++j) {
            int k = std::pow(2, i - 1);
            if (j + k < size) {
                table.table[i][j] = get_mins(table.table[i - 1][j], table.table[i - 1][j + k]);
            }
        }
    }
    return table;
};


int main()
{
    int n, m;
    std::cin >> n;
    std::cin >> m;
    std::vector<int> array;
    int local;
    for (int i = 0; i < n; ++i) {
        std::cin >> local;
        array.push_back(local);
    }
    struct sparse_table table = create(n, array);

    int begin, end;
    for (int i = 0; i < m; ++i) {
        std::cin >> begin;
        std::cin >> end;
        std::cout << rmq(begin - 1, end - 1, table) << "\n";
    }
    return 0;
}
