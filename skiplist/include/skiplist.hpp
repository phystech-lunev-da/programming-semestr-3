
#include <limits>
#include <iterator>
#include <forward_list>
#include <stack>

#include <random>

#include <iostream>

#include "coin.hpp"

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
    template<typename Q>
    friend std::ostream& operator<<(std::ostream&, SkipList<Q>&);
public:
    SkipList(unsigned);
    ~SkipList();

    SkipList(const SkipList<T>&);
    SkipList(SkipList<T>&&);

    const SkipList& operator=(const SkipList<T>&);
    SkipList&& operator=(SkipList<T>&&);

    bool empty();
    int size();

    void insert(T, int);
    void remove(int);
    Node<T>* find(int);

    void build_level();

    void clear();
private:
    Node<T> head;
    Node<T> tail;

    int m_size;

    int max_level;

    Coin coin;
};

template<typename T>
SkipList<T>::SkipList(unsigned seed)
    : m_size(0), head(T(), std::numeric_limits<unsigned>::min()), 
    tail(T(), std::numeric_limits<unsigned>::max()), max_level(1), coin(0.5, seed) 
{
    for (unsigned i = 0; i < max_level; i++) {
        head.forward.push_back(&tail);
    }
    tail.forward.push_back(nullptr);
}

template<typename T>
SkipList<T>::~SkipList() {
    clear();
}

template<typename T>
SkipList<T>::SkipList(const SkipList<T>& copy) : SkipList(copy.coin.get_seed()) {
    Node<T>* iter = copy.head.forward[copy.max_level - 1];
    while (iter != &(copy.tail)) {
        insert(iter->data, iter->key);
        iter = iter->forward[copy.max_level - 1];
    }
}

template<typename T>
SkipList<T>::SkipList(SkipList<T>&& copy) {
    if (&copy == this) {
        return;
    }
    m_size = copy.m_size;
    max_level = copy.max_level;
    coin = std::move(coin);
    head = std::move(copy.head);
    tail = std::move(copy.tail);
}

template<typename T>
const SkipList<T>& SkipList<T>::operator=(const SkipList<T>& copy) {
    this->m_size = 0;
    this->max_level = 1;
    this->coin = copy.coin;
    Node<T>* iter = copy.head.forward[copy.max_level - 1];
    while (iter != &(copy.tail)) {
        insert(iter->data, iter->key);
        iter = iter->forward[copy.max_level - 1];
    }
}

template<typename T>
SkipList<T>&& SkipList<T>::operator=(SkipList<T>&& copy) {
    m_size = copy.m_size;
    max_level = copy.max_level;
    copy = std::move(copy.coin);
    head = std::move(copy.head);
    tail = std::move(copy.tail);
}

template<typename T>
bool SkipList<T>::empty() {
    return m_size == 0;
}

template<typename T>
void SkipList<T>::insert(T element, int key) {

    std::vector<Node<T>*> update;
    Node<T>* iter = &head;

    for (int iter_lvl = 0; iter_lvl < max_level; iter_lvl++) {
        while (iter->forward[iter_lvl] != &tail && iter->forward[iter_lvl]->key < key) {
            iter = iter->forward[iter_lvl];
        }
        update.push_back(iter);
    }


    if (iter->forward[max_level - 1]-> key == key) {
        iter->forward[max_level - 1]->data = element;
        return;
    }

    Node<T>* new_node = new Node<T>(element, key);
    // в любом случае должен указывать на tail
    for (int i = 0; i < max_level; i++) {
        new_node->forward.push_back(&tail);
    }

    // Выбираем случайный уровень
    // Если при испытании Бернулли выпало больше, чем уровней есть на самом деле
    // то добавляем недостающие
    int random_level;
    int coin_count = coin.sum();
    while (coin_count >= max_level) {
        build_level();
        update.insert(update.begin(), &head);
        new_node->forward.push_back(&tail);
    }
    random_level = max_level - coin_count - 1;

    // Идем в обратном направлении, добавляя ссылки на каждом уровне
    int iter_lvl = max_level - 1;
    do {
        new_node->forward[iter_lvl] = update[iter_lvl]->forward[iter_lvl];
        update[iter_lvl]->forward[iter_lvl] = new_node;
        iter_lvl--;
    } while (iter_lvl >= random_level);
    
    m_size++;
}

template<typename T>
void SkipList<T>::build_level() {
    Node<T>* iter = &head;
    while (iter != &tail) {
        iter->forward.insert(iter->forward.begin(), &tail);
        iter = iter->forward[max_level];
    }
    max_level++;
}

template<typename T>
Node<T>* SkipList<T>::find(int key) {
    Node<T>* iter = &head;
    for (int iter_lvl = 0; iter_lvl < max_level; iter_lvl++) {
        while (iter != &tail && iter->forward[iter_lvl]->key < key) {
            iter = iter->forward[iter_lvl];
        }
    }
    iter = iter->forward[max_level - 1];
    if (iter->key == key) {
        return iter;
    }
    return &tail;
}

template<typename T>
void SkipList<T>::remove(int key) {
    std::vector<Node<T>*> update;
    Node<T>* iter = &head;
    for (int iter_lvl = 0; iter_lvl < max_level; iter_lvl++) {
        while (iter->forward[iter_lvl] != &tail && iter->forward[iter_lvl]->key < key) {
            iter = iter->forward[iter_lvl];
        }
        update.push_back(iter);
    }

    Node<T>* delete_node = iter->forward[max_level-1];
    if (delete_node == &tail) {
        return;
    }

    for (int iter_lvl = 0; iter_lvl < max_level; iter_lvl++) {
        if (update[iter_lvl]->forward[iter_lvl] != delete_node) {
            continue;
        }
        update[iter_lvl]->forward[iter_lvl] = delete_node->forward[iter_lvl];
    }

    delete delete_node;

    m_size--;
}

template<typename T>
void SkipList<T>::clear() {
    std::stack<Node<T>*> deleted_stack;
    Node<T>* iter = head.forward[max_level - 1];
    while(iter != &tail) {
        deleted_stack.push(iter);
        iter = iter->forward[max_level - 1];
    }
    while (!deleted_stack.empty()) {
        Node<T>* deleted = deleted_stack.top();
        deleted_stack.pop();
        delete deleted;
    }
    for (int i = 0; i < max_level - 1; i++) {
        head.forward.pop_back();
    }
    head.forward[0] = &tail;
    m_size = 0;
    max_level = 1;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, SkipList<T>& skiplist) {
    for (unsigned iter_lvl = 0; iter_lvl < skiplist.max_level; iter_lvl++) {
        out << iter_lvl << ": " << "HEAD" << " - ";
        Node<T>* iter = skiplist.head.forward[iter_lvl];
        while (iter != &(skiplist.tail)) {
            out << iter->key << " - ";
            iter = iter->forward[iter_lvl];
        }
        out << "NIL" << std::endl;
    }
    out << std::endl;
    return out;
}