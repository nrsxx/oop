#include <iostream>
#include <string>

class node {
private:
    node* left;
    node* right;
    std::string priority;
    int num_of_descendants;

public:
    node(std::string pr) {
        left = 0;
        right = 0;
        priority = pr;
        num_of_descendants = 1;
    }
};


class treap_with_implicit_key {
private:
    node& root;
public:
    treap_with_implicit_key(std::string root_priority) {
        root = node(root_priority);
    }

};

int main()
{
    std::cout << "Hello world!" << std::endl;
    return 0;
}
