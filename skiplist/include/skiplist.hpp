
#include <limits>
#include <iterator>
#include <forward_list>
#include <stack>

#include <random>

// Класс монетки
// 0 - решка
// 1 - орел
class Coin {
public:
    Coin(float, unsigned);
    unsigned flip();
private:
    std::default_random_engine reng;
    std::discrete_distribution<unsigned> dstr;
};

Coin::Coin(float p, unsigned seed) : dstr({1 - p, p}), reng(seed) {}
unsigned Coin::flip() { return dstr(reng);}

template<typename T>
struct Node {    
    Node(T, unsigned);
    unsigned key;
    T data;
    std::vector<Node<T>*> forward;
};

template<typename T>
Node<T>::Node(T data, unsigned key) : data(data), key(key), forward() {}

template<typename T> 
class SkipList {
public:
    SkipList();

    SkipList(const SkipList&);
    SkipList(SkipList&&);

    const SkipList& operator=(const SkipList&);
    SkipList&& operator=(SkipList&&);

    bool empty();
    unsigned size();

    void insert(T, unsigned);
    void remove(unsigned);
    Node<T>* find(unsigned);

    void clear();
private:
    Node<T>* m_find_element(Node<T>*, unsigned);
    Node<T>* m_insert_element(Node<T>*, T, unsigned);

    unsigned size = 0;
    Node<T> head;
    Node<T> tail;

    unsigned max_level;

    Coin coin;
};

template<typename T>
SkipList<T>::SkipList() : size(0), head(T(), std::numeric_limits<unsigned>::min()), tail(T(), std::numeric_limits<unsigned>::max()), levels() {
    head.forward.push_front(*tail);
}

template<typename T>
void SkipList<T>::insert(T element, unsigned key) {
    std::vector<Node<T>*> update;
    Node<T>* iter = *head;
    for (unsigned iter_lvl = 0; iter_lvl < max_level; iter_lvl++) {
        while (iter->forward[iter_lvl] != tail && iter->forward[iter_lvl]->key < key) {
            iter = iter->forward[iter_lvl];
        }
        update.push_back(iter);
    }

    Node<T>* new_node = new Node<T>(element, key);
    // в любом случае должен указывать на tail
    for (unsigned i = 0; i < max_level; i++) {
        new_node->forward[i] = tail;
    }
    unsigned iter_lvl = max_level - 1;

    do {
        new_node->forward[iter_lvl] = update[iter_lvl]->forward[iter_lvl];
        update[iter_lvl]->forward[iter_lvl] = new_node;
    } while (iter_lvl++ >= 0 && coin.flip() == 1);
}

template<typename T>
Node<T>* SkipList<T>::find(unsigned key) {
    Node<T>* iter = *head;
    for (unsigned iter_lvl = 0; iter_lvl < max_level; iter_lvl++) {
        while (iter->forward[iter_lvl] != tail && iter->forward[iter_lvl]->key < key) {
            iter = iter->forward[iter_lvl];
        }
    }
    return iter;
}

template<typename T>
void SkipList<T>::remove(unsigned key) {
    std::vector<Node<T>*> update;
    Node<T>* iter = *head;
    for (unsigned iter_lvl = 0; iter_lvl < max_level; iter_lvl++) {
        while (iter->forward[iter_lvl] != tail && iter->forward[iter_lvl]->key < key) {
            iter = iter->forward[iter_lvl];
        }
        update.push_back(iter);
    }

    Node<T>* delete_node = iter->forward[max_level];

    for (unsigned iter_lvl = 0; iter_lvl < max_level; iter_lvl++) {
        update->forward[iter_lvl] = delete_node->forward[iter_lvl];
    }

    delete delete_node;
}

template<typename T>
void SkipList<T>::clear() {
    std::stack<Node<T>*> deleted_stack;
    Node<T>* iter = *head;
    while(iter != nullptr) {
        deleted_stack.push(iter);
        iter = iter->next[0];
    }
}