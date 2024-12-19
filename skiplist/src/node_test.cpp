
#include "skiplist.hpp"

template<typename T>
Node<T> concat_node(Node<T>& node1, Node<T>& node2) {
    std::vector<Node<int>*> line;
    line.push_back(&node1);
    line.push_back(&node2);
    Node<T> new_node(3, 3);
    new_node.forward = line;
    return new_node;
}

int main() {

    std::cout << "Copy constructor" << std::endl;

    Node<int> node1(1, 1);

    Node<int> node2(2, 2);

    node1.forward.push_back(&node2);

    Node<int> copy(node1);

    std::cout << node1 << std::endl;

    std::cout << node1.forward[0] << std::endl;
    std::cout << &node2 << std::endl;

    std::cout << "Move constructor" << std::endl;

    std::vector<Node<int>*> line;
    line.push_back(&node1);
    line.push_back(&node2);

    Node<int> move(concat_node(node1, node2));

    std::cout << move.forward[0] << std::endl;
    std::cout << &node1 << std::endl << std::endl;

    std::cout << move.forward[1] << std::endl;
    std::cout << &node2 << std::endl;

    move = std::move(node1);
    

}