
#include <iterator>
#include <forward_list>

template<typename T>
class Node {
public:
    T get() const;
    void set(T);
private:
    T data;
};

template<typename T> 
class SkipList {
public:
    SkipList();

    SkipList(const SkipList&);
    SkipList(SkipList&&);

    bool empty();
    unsigned size();
    void insert(T);
private:
    static const unsigned lines_count = 4;

    
};

template<typename T>
SkipList<T>::SkipList() : head(nullptr) {
    lines[0] = nullptr;
    lines[lines_count - 1] = head;
    for (unsigned i = 0; i < lines_count; i++) {
        head
    }
}