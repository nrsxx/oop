#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

int get_log(int n) {
    if (n == 1) {
        return 0;
    }
    return std::ceil(std::log10(n) / std::log10(2));
}

class root_tree {
private:
    int size;
    int log;
    int pow;
    std::vector<int> depthes;
    std::vector<int> logs;
    std::vector<int> pows;
    std::vector<std::vector<int> > children;
    std::vector<std::vector<int> > further_parents;

    void count_further_parents() {
        for (int i = 0; i < log; ++i) {
            further_parents[i].resize(size);
        }
        further_parents[0][0] = 0;
        for (int i = 1; i < size; ++i) {
            std::cin >> further_parents[0][i];
            children[further_parents[0][i]].push_back(i);
        }
        for (int i = 1; i < log; ++i) {
            for (int j = 0; j < size; ++j) {
                further_parents[i][j] = further_parents[i - 1][further_parents[i - 1][j]];
            }
        }
    }

    void modified_dfs(int n) {
        int s = children[n].size();
        for (int i = 0; i < s; ++i) {
                depthes[children[n][i]] = depthes[n] + 1;
                modified_dfs(children[n][i]);
        }
    }

    void fill_pows() {
        for (int i = 0; i < size; ++i) {
            logs[i] = get_log(depthes[i]);
            pows[i] = std::pow(2, logs[i] - 1);
        }
    }

public:
    root_tree(int n) {
        size = n;
        log = get_log(n);
        pow = std::pow(2, log);
        depthes.resize(n);
        depthes[0] = 0;
        children.resize(n);
        further_parents.resize(get_log(n));
        logs.resize(n);
        pows.resize(n);
    }

    void preprocessing() {
        count_further_parents();
        modified_dfs(0);
        fill_pows();
    }

    int lca(int left, int right) {
        if (depthes[left] > depthes[right]) {
            std::swap(left, right);
        }
        int local = pows[right];
        for (int i = logs[right] - 1; i >= 0; --i) {
            if (depthes[right] - depthes[left] >= local) {
                right = further_parents[i][right];
            }
            local /= 2;
        }
        if (left == right) {
            return left;
        } else {
            for (int i = logs[right] - 1; i >= 0; --i) {
                if (further_parents[i][left] != further_parents[i][right]) {
                    left = further_parents[i][left];
                    right = further_parents[i][right];
                }
            }
        }
        return further_parents[0][left];
    }
};


int main()
{
    int n;
    long long int num_of_queries;
    std::cin >> n >> num_of_queries;
    if (n == 1) {
        std::cout << "0";
        return 0;
    }
    root_tree tree(n);
    tree.preprocessing();

    int a0, a1;
    std::cin >> a0;
    std::cin >> a1;
    long long int x, y, z;
    std::cin >> x >> y >> z;
    long long int result_sum = 0;
    int cur_result = tree.lca(a0, a1);
    result_sum += cur_result;
    for (long long int i = 1; i < num_of_queries; ++i) {
        a0 = (x * a0 + y * a1 + z) % n;
        a1 = (x * a1 + y * a0 + z) % n;
        cur_result = tree.lca((a0 + cur_result) % n, a1);
        result_sum += cur_result;
    }
    std::cout << result_sum;
    return 0;
}
