#include <iostream>
#include <vector>
#include <cmath>

class segmental_tree {
private:

    int get_degree(int n) {
        return std::pow(2, std::ceil(std::log10(n) / std::log10(2)));
    }

public:
    std::vector<int> tree;
    int num_of_leafs;
    segmental_tree(std::vector<int>& initial_array) {

        num_of_leafs = get_degree(initial_array.size());
        tree.assign(2 * num_of_leafs, 0);
        for (int i = 0; i < initial_array.size(); ++i) {
            tree[num_of_leafs - 1 + i] = initial_array[i];
        }

        for (int i = num_of_leafs - 2; i >= 0; --i) {
            tree[i] = std::max(tree[2 * i + 1], tree[2 * i + 2]);
        }
    }

    int get_max(int start0, int finish0) {
        int left_result = 0;
        int right_result = 0;
        int start = start0 + num_of_leafs - 1;
        int finish = finish0 + num_of_leafs - 1;

        while (start < finish) {
            if (start % 2 == 0) {
                left_result = std::max(tree[start], left_result);
                ++start;
            }
            if (finish % 2 == 1) {
                right_result = std::max(tree[finish], right_result);
                --finish;
            }
            start = (start - 1) / 2;
            finish = (finish - 2) / 2;
        }
        if (start == finish) {
            left_result = std::max(tree[start], left_result);
        }
        return std::max(left_result, right_result);
    }

    void add(int start0, int finish0, int number) {
        int start = start0 + num_of_leafs - 1;
        int finish = finish0 + num_of_leafs - 1;
        for (int i = start; i <= finish; ++i) {
                tree[i] += number;
        }
        while (start != 0) {
            start = (start - 1) / 2;
            finish = (finish - 1) / 2;
            for (int i = start; i <= finish; ++i) {
                tree[i] = std::max(tree[2 * i + 1], tree[2 * i + 2]);
            }
        }
        tree[0] = std::max(tree[1], tree[2]);
    }
};


int main()
{
    int num_of_stations;
    std::vector<int> initial;
    int capacity;
    int num_of_queries;
    std::cin >> num_of_stations;
    for (int i = 0; i < num_of_stations - 1; ++i) {
        int local;
        std::cin >> local;
        initial.push_back(local);
    }
    std::cin >> capacity;
    std::cin >> num_of_queries;
    segmental_tree tree(initial);
    for (int i = 0; i < num_of_queries; ++i) {
        int start;
        int finish;
        int number;
        std::cin >> start;
        std::cin >> finish;
        std::cin >> number;
        --finish;
        if (tree.get_max(start, finish) + number <= capacity) {
            tree.add(start, finish, number);
        } else {
            std::cout << i << " ";
        }
    }

    return 0;
}
